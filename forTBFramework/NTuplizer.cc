// Based on PulseShapePlotter...

#include <iostream>
#include "TH1F.h"
#include "TH2F.h"
#include "TH2Poly.h"
#include "TTree.h"
#include <fstream>
#include <sstream>
#include <vector>
// user include files
#include "FWCore/Framework/interface/Frameworkfwd.h"
#include "FWCore/Framework/interface/one/EDAnalyzer.h"
#include "FWCore/Framework/interface/Event.h"
#include "FWCore/Framework/interface/MakerMacros.h"
#include "FWCore/ParameterSet/interface/ParameterSet.h"
#include "FWCore/ServiceRegistry/interface/Service.h"

#include "CommonTools/UtilAlgos/interface/TFileService.h"

#include "HGCal/DataFormats/interface/HGCalTBRawHitCollection.h"
#include "HGCal/DataFormats/interface/HGCalTBDetId.h"
#include "HGCal/DataFormats/interface/HGCalTBElectronicsId.h"
#include "HGCal/CondObjects/interface/HGCalElectronicsMap.h"
#include "HGCal/CondObjects/interface/HGCalCondObjectTextIO.h"
#include "HGCal/Geometry/interface/HGCalTBGeometryParameters.h"
#include "HGCal/Reco/interface/CommonMode.h"
#include "HGCal/Reco/interface/PulseFitter.h"

#include <iomanip>
#include <set>




class NTuplizer : public edm::one::EDAnalyzer<edm::one::SharedResources>
{
public:
  explicit NTuplizer(const edm::ParameterSet&);
  ~NTuplizer();
  static void fillDescriptions(edm::ConfigurationDescriptions& descriptions);
private:
  virtual void beginJob() override;
  void analyze(const edm::Event& , const edm::EventSetup&) override;
  virtual void endJob() override;

  std::string m_electronicMap;
  struct {
    HGCalElectronicsMap emap_;
  } essource_;
  double m_commonModeThreshold; //currently not use (need to implement the "average" option in CommonMode.cc)

  edm::EDGetTokenT<HGCalTBRawHitCollection> m_HGCalTBRawHitCollection;

  TTree *T;
  int m_evtID;
  void ClearTreeVectors();
  // Cell ID
  std::vector<int> Hit_Sensor_Event;
  std::vector<int> Hit_Sensor_Channel;
  std::vector<int> Hit_Sensor_Layer;
  std::vector<int> Hit_Sensor_Skiroc;
  // Cell Information Old
	std::vector<float> Hit_Sensor_Cell_X;
	std::vector<float> Hit_Sensor_Cell_Y;
  std::vector<float> Hit_Sensor_Cell_HG;
	std::vector<float> Hit_Sensor_Cell_HG_Sub;
  std::vector<float> Hit_Sensor_Cell_LG;
	std::vector<float> Hit_Sensor_Cell_LG_Sub;
	std::vector<float> Hit_Sensor_Cell_ToT_Slow;
	std::vector<float> Hit_Sensor_Cell_ToA_Fall;
	std::vector<float> Hit_Sensor_Cell_ToA_Rise;

  // Cell Information with PulseFit
  std::vector<float> Hit_Sensor_Cell_HG_Amplitude;
  std::vector<float> Hit_Sensor_Cell_HG_Amplitude_Error;
  std::vector<float> Hit_Sensor_Cell_HG_Tmax;
  std::vector<float> Hit_Sensor_Cell_HG_Chi2;
  std::vector<float> Hit_Sensor_Cell_HG_Tmax_Error;
  std::vector<int> Hit_Sensor_Cell_HG_Status;
  std::vector<int> Hit_Sensor_Cell_HG_NCalls;
 // Same thing for LG
  std::vector<float> Hit_Sensor_Cell_LG_Amplitude;
  std::vector<float> Hit_Sensor_Cell_LG_Amplitude_Error;
  std::vector<float> Hit_Sensor_Cell_LG_Tmax;
  std::vector<float> Hit_Sensor_Cell_LG_Chi2;
  std::vector<float> Hit_Sensor_Cell_LG_Tmax_Error;
  std::vector<int> Hit_Sensor_Cell_LG_Status;
  std::vector<int> Hit_Sensor_Cell_LG_NCalls;



  // Cell Information with PulseFit With commonModeNoise Subtraction
  std::vector<float> Hit_Sensor_Cell_HG_Amplitude_CM;
  std::vector<float> Hit_Sensor_Cell_HG_Amplitude_Error_CM;
  std::vector<float> Hit_Sensor_Cell_HG_Tmax_CM;
  std::vector<float> Hit_Sensor_Cell_HG_Chi2_CM;
  std::vector<float> Hit_Sensor_Cell_HG_Tmax_Error_CM;
  std::vector<int> Hit_Sensor_Cell_HG_Status_CM;
  std::vector<int> Hit_Sensor_Cell_HG_NCalls_CM;
 // Same thing for LG
  std::vector<float> Hit_Sensor_Cell_LG_Amplitude_CM;
  std::vector<float> Hit_Sensor_Cell_LG_Amplitude_Error_CM;
  std::vector<float> Hit_Sensor_Cell_LG_Tmax_CM;
  std::vector<float> Hit_Sensor_Cell_LG_Chi2_CM;
  std::vector<float> Hit_Sensor_Cell_LG_Tmax_Error_CM;
  std::vector<int> Hit_Sensor_Cell_LG_Status_CM;
  std::vector<int> Hit_Sensor_Cell_LG_NCalls_CM;




  ////////////////////
  HGCalTBTopology IsCellValid;
  HGCalTBCellVertices TheCell;
  std::vector<std::pair<double, double>> CellXY;
  std::pair<double, double> CellCentreXY;

  bool m_eventPlotter = 0;
  int m_sensorsize = 128;


};

NTuplizer::NTuplizer(const edm::ParameterSet& iConfig) :
  m_electronicMap(iConfig.getUntrackedParameter<std::string>("ElectronicMap","HGCal/CondObjects/data/map_CERN_Hexaboard_OneLayers_May2017.txt")),
  m_commonModeThreshold(iConfig.getUntrackedParameter<double>("CommonModeThreshold",100))
{
  m_HGCalTBRawHitCollection = consumes<HGCalTBRawHitCollection>(iConfig.getParameter<edm::InputTag>("InputCollection"));
  m_evtID=0;
  usesResource("TFileService");
  edm::Service<TFileService> fs;
  T=fs->make<TTree>("T","NTuples with PulseShape...");
  T->Branch("Hit_Sensor_Event", &Hit_Sensor_Event);
  T->Branch("Hit_Sensor_Channel", &Hit_Sensor_Channel);
  T->Branch("Hit_Sensor_Layer", &Hit_Sensor_Layer);
  T->Branch("Hit_Sensor_Skiroc", &Hit_Sensor_Skiroc);

	T->Branch("Hit_Sensor_Cell_X", &Hit_Sensor_Cell_X);
	T->Branch("Hit_Sensor_Cell_Y", &Hit_Sensor_Cell_Y);
	T->Branch("Hit_Sensor_Cell_HG", &Hit_Sensor_Cell_HG);
  T->Branch("Hit_Sensor_Cell_HG_Sub", &Hit_Sensor_Cell_HG_Sub);
  T->Branch("Hit_Sensor_Cell_LG", &Hit_Sensor_Cell_LG);
	T->Branch("Hit_Sensor_Cell_LG_Sub", &Hit_Sensor_Cell_LG_Sub);
	T->Branch("Hit_Sensor_Cell_ToT_Slow", &Hit_Sensor_Cell_ToT_Slow);
	T->Branch("Hit_Sensor_Cell_ToA_Fall", &Hit_Sensor_Cell_ToA_Fall);
	T->Branch("Hit_Sensor_Cell_ToA_Rise", &Hit_Sensor_Cell_ToA_Rise);

  T->Branch("Hit_Sensor_Cell_HG_Amplitude", &Hit_Sensor_Cell_HG_Amplitude);
  T->Branch("Hit_Sensor_Cell_HG_Amplitude_Error", &Hit_Sensor_Cell_HG_Amplitude_Error);
  T->Branch("Hit_Sensor_Cell_HG_Tmax", &Hit_Sensor_Cell_HG_Tmax);
  T->Branch("Hit_Sensor_Cell_HG_Tmax_Error", &Hit_Sensor_Cell_HG_Tmax_Error);
  T->Branch("Hit_Sensor_Cell_HG_Chi2", &Hit_Sensor_Cell_HG_Chi2);
  T->Branch("Hit_Sensor_Cell_HG_Status", &Hit_Sensor_Cell_HG_Status);
  T->Branch("Hit_Sensor_Cell_HG_NCalls", &Hit_Sensor_Cell_HG_NCalls);

  T->Branch("Hit_Sensor_Cell_LG_Amplitude", &Hit_Sensor_Cell_LG_Amplitude);
  T->Branch("Hit_Sensor_Cell_LG_Amplitude_Error", &Hit_Sensor_Cell_LG_Amplitude_Error);
  T->Branch("Hit_Sensor_Cell_LG_Tmax", &Hit_Sensor_Cell_LG_Tmax);
  T->Branch("Hit_Sensor_Cell_LG_Tmax_Error", &Hit_Sensor_Cell_LG_Tmax_Error);
  T->Branch("Hit_Sensor_Cell_LG_Chi2", &Hit_Sensor_Cell_LG_Chi2);
  T->Branch("Hit_Sensor_Cell_LG_Status", &Hit_Sensor_Cell_LG_Status);
  T->Branch("Hit_Sensor_Cell_LG_NCalls", &Hit_Sensor_Cell_LG_NCalls);

  T->Branch("Hit_Sensor_Cell_HG_Amplitude_CM", &Hit_Sensor_Cell_HG_Amplitude_CM);
  T->Branch("Hit_Sensor_Cell_HG_Amplitude_Error_CM", &Hit_Sensor_Cell_HG_Amplitude_Error_CM);
  T->Branch("Hit_Sensor_Cell_HG_Tmax_CM", &Hit_Sensor_Cell_HG_Tmax_CM);
  T->Branch("Hit_Sensor_Cell_HG_Tmax_Error_CM", &Hit_Sensor_Cell_HG_Tmax_Error_CM);
  T->Branch("Hit_Sensor_Cell_HG_Chi2_CM", &Hit_Sensor_Cell_HG_Chi2_CM);
  T->Branch("Hit_Sensor_Cell_HG_Status_CM", &Hit_Sensor_Cell_HG_Status_CM);
  T->Branch("Hit_Sensor_Cell_HG_NCalls_CM", &Hit_Sensor_Cell_HG_NCalls_CM);

  T->Branch("Hit_Sensor_Cell_LG_Amplitude_CM", &Hit_Sensor_Cell_LG_Amplitude_CM);
  T->Branch("Hit_Sensor_Cell_LG_Amplitude_Error_CM", &Hit_Sensor_Cell_LG_Amplitude_Error_CM);
  T->Branch("Hit_Sensor_Cell_LG_Tmax_CM", &Hit_Sensor_Cell_LG_Tmax_CM);
  T->Branch("Hit_Sensor_Cell_LG_Tmax_Error_CM", &Hit_Sensor_Cell_LG_Tmax_Error_CM);
  T->Branch("Hit_Sensor_Cell_LG_Chi2_CM", &Hit_Sensor_Cell_LG_Chi2_CM);
  T->Branch("Hit_Sensor_Cell_LG_Status_CM", &Hit_Sensor_Cell_LG_Status_CM);
  T->Branch("Hit_Sensor_Cell_LG_NCalls_CM", &Hit_Sensor_Cell_LG_NCalls_CM);

  std::cout << iConfig.dump() << std::endl;
}


NTuplizer::~NTuplizer()
{

}

void NTuplizer::beginJob()
{
  HGCalCondObjectTextIO io(0);
  edm::FileInPath fip(m_electronicMap);
  if (!io.load(fip.fullPath(), essource_.emap_)) {
    throw cms::Exception("Unable to load electronics map");
  };
}

void NTuplizer::analyze(const edm::Event& event, const edm::EventSetup& setup)
{

  ClearTreeVectors();

  usesResource("TFileService");
  edm::Service<TFileService> fs;
  std::map<int,TH1F*>  hMapHG,hMapLG;
  std::ostringstream os( std::ostringstream::ate );

  edm::Handle<HGCalTBRawHitCollection> hits;
  event.getByToken(m_HGCalTBRawHitCollection, hits);

  CommonMode cm(essource_.emap_); //default is common mode per chip using the median
  cm.Evaluate( hits );
  std::map<int,commonModeNoise> cmMap=cm.CommonModeNoiseMap();
  PulseFitter fitter(0,150);
  for( auto hit : *hits ){
    HGCalTBElectronicsId eid( essource_.emap_.detId2eid(hit.detid().rawId()) );
    if( essource_.emap_.existsEId(eid) ){
      int iski=hit.skiroc();
      float highGain,lowGain;
      float subHG[NUMBER_OF_TIME_SAMPLES],subLG[NUMBER_OF_TIME_SAMPLES];
      for( int it=0; it<NUMBER_OF_TIME_SAMPLES; it++ ){
      	subHG[it]=0;
      	subLG[it]=0;
      }
      switch ( hit.detid().cellType() ){
      case 0 :
      	for( int it=0; it<NUMBER_OF_TIME_SAMPLES; it++ ){
      	  subHG[it]=cmMap[iski].fullHG[it];
      	  subLG[it]=cmMap[iski].fullLG[it];
      	}
      	break;
      case 2 :
      	for( int it=0; it<NUMBER_OF_TIME_SAMPLES; it++ ){
      	  subHG[it]=cmMap[iski].halfHG[it];
      	  subLG[it]=cmMap[iski].halfLG[it];
      	}
      	break;
      case 3 :
      	for( int it=0; it<NUMBER_OF_TIME_SAMPLES; it++ ){
      	  subHG[it]=cmMap[iski].mouseBiteHG[it];
      	  subLG[it]=cmMap[iski].mouseBiteLG[it];
      	}
      	break;
      case 4 : for( int it=0; it<NUMBER_OF_TIME_SAMPLES; it++ ){
       	  subHG[it]=cmMap[iski].outerHG[it];
       	  subLG[it]=cmMap[iski].outerLG[it];
       	}
       	break;
      case 5 : for( int it=0; it<NUMBER_OF_TIME_SAMPLES; it++ ){
       	  subHG[it]=cmMap[iski].mergedHG[it];
       	  subLG[it]=cmMap[iski].mergedLG[it];
        }
        break;
      }
      int iboard=hit.skiroc()/HGCAL_TB_GEOMETRY::N_SKIROC_PER_HEXA;
      int ichan=hit.channel();
      std::vector<double> hg,lg,hg_CM,lg_CM,time;
      for( int it=0; it<NUMBER_OF_TIME_SAMPLES; it++ ){
	highGain=hit.highGainADC(it)-subHG[it];
	lowGain=hit.lowGainADC(it)-subLG[it];
  hg.push_back(hit.highGainADC(it));
  lg.push_back(hit.lowGainADC(it));
	hg_CM.push_back(highGain);
  lg_CM.push_back(lowGain);
	time.push_back(25*it+12.5);
      }
      float en2=hit.highGainADC(2)-subHG[2];
      float en3=hit.highGainADC(3)-subHG[3];
      float en4=hit.highGainADC(4)-subHG[4];
      float en6=hit.highGainADC(6)-subHG[6];
      if( en2<en3 && en3>en6 && en4>en6 && en3>20 ){
	//std::cout << iboard << " " << iski%HGCAL_TB_GEOMETRY::N_SKIROC_PER_HEXA << " " << ichan << "\t" << en2 << " " << en3 << " " << en4 << " " << en6 << std::endl;
  PulseFitterResult fithg;
	PulseFitterResult fithg_CM;
	fitter.run( time,hg,fithg,8. );
  fitter.run( time,hg_CM,fithg_CM,8. );

  PulseFitterResult fitlg;
	PulseFitterResult fitlg_CM;
  fitter.run( time,lg,fitlg,2. );
	fitter.run( time,lg_CM,fitlg_CM,2. );

  //Cell X and Y
  // if(!m_eventPlotter||!IsCellValid.iu_iv_valid(hit.detid().layer(), hit.detid().sensorIU(), hit.detid().sensorIV(), hit.detid().iu(), hit.detid().iv(), m_sensorsize))  continue;

  CellCentreXY=TheCell.GetCellCentreCoordinatesForPlots(hit.detid().layer(), hit.detid().sensorIU(), hit.detid().sensorIV(), hit.detid().iu(), hit.detid().iv(), m_sensorsize);
  double iux = (CellCentreXY.first < 0 ) ? (CellCentreXY.first + HGCAL_TB_GEOMETRY::DELTA) : (CellCentreXY.first - HGCAL_TB_GEOMETRY::DELTA) ;
  double iuy = (CellCentreXY.second < 0 ) ? (CellCentreXY.second + HGCAL_TB_GEOMETRY::DELTA) : (CellCentreXY.second - HGCAL_TB_GEOMETRY::DELTA);
  // End Cell X and Y

  //DataFilling
  if(fithg.amplitude > 100)
{
  Hit_Sensor_Event.push_back(m_evtID);
  Hit_Sensor_Layer.push_back(iboard);
  Hit_Sensor_Channel.push_back(ichan);
  Hit_Sensor_Skiroc.push_back(iski%HGCAL_TB_GEOMETRY::N_SKIROC_PER_HEXA);

  Hit_Sensor_Cell_X.push_back(iux);
  Hit_Sensor_Cell_Y.push_back(iuy);
  Hit_Sensor_Cell_HG.push_back(hit.highGainADC(3));
  Hit_Sensor_Cell_HG_Sub.push_back(subHG[3]);
  Hit_Sensor_Cell_LG.push_back(hit.lowGainADC(3));
  Hit_Sensor_Cell_LG_Sub.push_back(subLG[3]);
  Hit_Sensor_Cell_ToT_Slow.push_back( hit.totSlow() );
  Hit_Sensor_Cell_ToA_Fall.push_back( hit.toaFall() );
  Hit_Sensor_Cell_ToA_Rise.push_back( hit.toaRise() );


  Hit_Sensor_Cell_HG_Amplitude.push_back(fithg.amplitude);
  Hit_Sensor_Cell_HG_Tmax.push_back(fithg.tmax);
  Hit_Sensor_Cell_HG_Chi2.push_back(fithg.chi2);
  Hit_Sensor_Cell_HG_Amplitude_Error.push_back(fithg.erroramplitude);
  Hit_Sensor_Cell_HG_Tmax_Error.push_back(fithg.errortmax);
  Hit_Sensor_Cell_HG_Status.push_back(fithg.status);
  Hit_Sensor_Cell_HG_NCalls.push_back(fithg.ncalls);


  Hit_Sensor_Cell_LG_Amplitude.push_back(fitlg.amplitude);
  Hit_Sensor_Cell_LG_Tmax.push_back(fitlg.tmax);
  Hit_Sensor_Cell_LG_Chi2.push_back(fitlg.chi2);
  Hit_Sensor_Cell_LG_Amplitude_Error.push_back(fitlg.erroramplitude);
  Hit_Sensor_Cell_LG_Tmax_Error.push_back(fitlg.errortmax);
  Hit_Sensor_Cell_LG_Status.push_back(fitlg.status);
  Hit_Sensor_Cell_LG_NCalls.push_back(fitlg.ncalls);



  Hit_Sensor_Cell_HG_Amplitude_CM.push_back(fithg_CM.amplitude);
  Hit_Sensor_Cell_HG_Tmax_CM.push_back(fithg_CM.tmax);
  Hit_Sensor_Cell_HG_Chi2_CM.push_back(fithg_CM.chi2);
  Hit_Sensor_Cell_HG_Amplitude_Error_CM.push_back(fithg_CM.erroramplitude);
  Hit_Sensor_Cell_HG_Tmax_Error_CM.push_back(fithg_CM.errortmax);
  Hit_Sensor_Cell_HG_Status_CM.push_back(fithg_CM.status);
  Hit_Sensor_Cell_HG_NCalls_CM.push_back(fithg_CM.ncalls);


  Hit_Sensor_Cell_LG_Amplitude_CM.push_back(fitlg_CM.amplitude);
  Hit_Sensor_Cell_LG_Tmax_CM.push_back(fitlg_CM.tmax);
  Hit_Sensor_Cell_LG_Chi2_CM.push_back(fitlg_CM.chi2);
  Hit_Sensor_Cell_LG_Amplitude_Error_CM.push_back(fitlg_CM.erroramplitude);
  Hit_Sensor_Cell_LG_Tmax_Error_CM.push_back(fitlg_CM.errortmax);
  Hit_Sensor_Cell_LG_Status_CM.push_back(fitlg_CM.status);
  Hit_Sensor_Cell_LG_NCalls_CM.push_back(fitlg_CM.ncalls);
}

      }
    }


  } // Hits Loop End
  T->Fill();
  m_evtID++;
}

void NTuplizer::ClearTreeVectors(){

  Hit_Sensor_Event.clear();
  Hit_Sensor_Layer.clear();
  Hit_Sensor_Channel.clear();
  Hit_Sensor_Skiroc.clear();

  Hit_Sensor_Cell_X.clear();
  Hit_Sensor_Cell_Y.clear();
  Hit_Sensor_Cell_HG.clear();
  Hit_Sensor_Cell_HG_Sub.clear();
  Hit_Sensor_Cell_LG.clear();
  Hit_Sensor_Cell_LG_Sub.clear();
  Hit_Sensor_Cell_ToT_Slow.clear();
  Hit_Sensor_Cell_ToA_Fall.clear();
  Hit_Sensor_Cell_ToA_Rise.clear();


  Hit_Sensor_Cell_HG_Amplitude.clear();
  Hit_Sensor_Cell_HG_Tmax.clear();
  Hit_Sensor_Cell_HG_Chi2.clear();
  Hit_Sensor_Cell_HG_Amplitude_Error.clear();
  Hit_Sensor_Cell_HG_Tmax_Error.clear();
  Hit_Sensor_Cell_HG_Status.clear();
  Hit_Sensor_Cell_HG_NCalls.clear();

  Hit_Sensor_Cell_LG_Amplitude.clear();
  Hit_Sensor_Cell_LG_Tmax.clear();
  Hit_Sensor_Cell_LG_Chi2.clear();
  Hit_Sensor_Cell_LG_Amplitude_Error.clear();
  Hit_Sensor_Cell_LG_Tmax_Error.clear();
  Hit_Sensor_Cell_LG_Status.clear();
  Hit_Sensor_Cell_LG_NCalls.clear();


  Hit_Sensor_Cell_HG_Amplitude_CM.clear();
  Hit_Sensor_Cell_HG_Tmax_CM.clear();
  Hit_Sensor_Cell_HG_Chi2_CM.clear();
  Hit_Sensor_Cell_HG_Amplitude_Error_CM.clear();
  Hit_Sensor_Cell_HG_Tmax_Error_CM.clear();
  Hit_Sensor_Cell_HG_Status_CM.clear();
  Hit_Sensor_Cell_HG_NCalls_CM.clear();

  Hit_Sensor_Cell_LG_Amplitude_CM.clear();
  Hit_Sensor_Cell_LG_Tmax_CM.clear();
  Hit_Sensor_Cell_LG_Chi2_CM.clear();
  Hit_Sensor_Cell_LG_Amplitude_Error_CM.clear();
  Hit_Sensor_Cell_LG_Tmax_Error_CM.clear();
  Hit_Sensor_Cell_LG_Status_CM.clear();
  Hit_Sensor_Cell_LG_NCalls_CM.clear();


}

void NTuplizer::endJob()
{
}

void NTuplizer::fillDescriptions(edm::ConfigurationDescriptions& descriptions)
{
  edm::ParameterSetDescription desc;
  desc.setUnknown();
  descriptions.addDefault(desc);
}

DEFINE_FWK_MODULE(NTuplizer);
