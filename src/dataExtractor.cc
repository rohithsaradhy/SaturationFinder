// This takes the NTuples and creates the necessary 2d Histograms so we can work with them faster..
//  NTuples are event based.
// Written by Rohith Saradhy
 #include "SaturationFinder.h"



void SaturationFinder::dataExtractor()
{
  Int_t board(0),skiroc(0);
  float x(0),y(0),z(0);
  std::cout<<std::endl<<std::endl<<"Starting dataExtractor"<<std::endl;

  //Initialising all the variables...

  // For 2018 NTuples...

  std::vector<int>* Hit_Sensor_detid=0;
  std::vector<int>* Hit_Sensor_module=0;
  std::vector<int>* Hit_Sensor_layer=0;
  std::vector<int>* Hit_Sensor_chip=0;
  std::vector<int>* Hit_Sensor_channel=0;
  std::vector<float>* Hit_Sensor_x=0;
  std::vector<float>* Hit_Sensor_y=0;
  std::vector<float>* Hit_Sensor_z=0;
  std::vector<int>* Hit_Sensor_iu=0;
  std::vector<int>* Hit_Sensor_iv=0;
  std::vector<float>* Hit_Sensor_energy=0;
  std::vector<float>* Hit_Sensor_maxTS2TS3High=0;
  std::vector<float>* Hit_Sensor_maxTS2TS3Low=0;
  std::vector<float>* Hit_Sensor_amplitudeHigh=0;
  std::vector<float>* Hit_Sensor_amplitudeLow=0;
  std::vector<float>* Hit_Sensor_Tot=0;
  std::vector<float>* Hit_Sensor_time=0;
  std::vector<float>* Hit_Sensor_timeMaxHG=0;
  std::vector<float>* Hit_Sensor_timeMaxLG=0;
  std::vector<float>* Hit_Sensor_toaRise=0;
  std::vector<float>* Hit_Sensor_toaFall=0;

  //Open file and set the branch to that particular data...
  std::ostringstream filename( std::ostringstream::ate );
  filename.str("");
  filename<<DATA_LOC<<RUN_TYPE<<"/"<<ENERGY<<"GeV.root";
  if(RUN_TYPE != "other") //Specifying exact location and name...
  {
    if(ENERGY == 0)
    {
      filename.str("");
      filename<<DATA_LOC<<RUN_TYPE<<".root";
    }
  }
  else
  {
    filename.str("");
    filename<<DATA_LOC;
  }


  //Overiding previous settings...
  if(CollectFromNTuples_Run)
  {

    filename.str("");
    filename<<DATA_LOC<<"/ntuple_"<<Run_No<<".root";

  }

  std::cout<<"Opening File "<<filename.str().c_str()<<std::endl;

  if (is_file_exist(filename.str().c_str()))
  {
    TFile *file = TFile::Open(filename.str().c_str());
    TTree *T =  (TTree*)file->Get("rechitntupler/hits");



    T->SetBranchAddress("rechit_detid", &Hit_Sensor_detid);
    T->SetBranchAddress("rechit_module", &Hit_Sensor_module);
    T->SetBranchAddress("rechit_layer", &Hit_Sensor_layer);
    T->SetBranchAddress("rechit_chip", &Hit_Sensor_chip);
    T->SetBranchAddress("rechit_channel", &Hit_Sensor_channel);

    T->SetBranchAddress("rechit_x", &Hit_Sensor_x);
    T->SetBranchAddress("rechit_y", &Hit_Sensor_y);
    T->SetBranchAddress("rechit_z", &Hit_Sensor_z);
    T->SetBranchAddress("rechit_iu", &Hit_Sensor_iu);
    T->SetBranchAddress("rechit_iv", &Hit_Sensor_iv);
    T->SetBranchAddress("rechit_energy", &Hit_Sensor_energy);
    T->SetBranchAddress("rechit_maxTS2TS3High", &Hit_Sensor_maxTS2TS3High);
    T->SetBranchAddress("rechit_maxTS2TS3Low", &Hit_Sensor_maxTS2TS3Low);

    T->SetBranchAddress("rechit_amplitudeHigh", &Hit_Sensor_amplitudeHigh);
    T->SetBranchAddress("rechit_amplitudeLow", &Hit_Sensor_amplitudeLow);
    T->SetBranchAddress("rechit_Tot", &Hit_Sensor_Tot);

    T->SetBranchAddress("rechit_time", &Hit_Sensor_time);
    T->SetBranchAddress("rechit_timeMaxHG", &Hit_Sensor_timeMaxHG);
    T->SetBranchAddress("rechit_timeMaxLG", &Hit_Sensor_timeMaxLG);
    T->SetBranchAddress("rechit_toaRise", &Hit_Sensor_toaRise);
    T->SetBranchAddress("rechit_toaFall", &Hit_Sensor_toaFall);






    Int_t Max_Entries = T->GetEntries();

    std::cout<<"This is the Max entries in this ntuples :: "<<Max_Entries<<std::endl;




    for(int entry = 0; entry < Max_Entries ; entry++)
    {

      T->GetEntry(entry);
      // if(entry == (int)(Max_Entries/2) ) break;  // so it is faster for debugging

      if(entry%1000 == 0)
      {
        std::cout<<entry*100/Max_Entries <<"% \t has been completed... \r";
        std::cout.flush();
      }

      for(int i = 0; i < Hit_Sensor_layer->size();i++ )
      {

        board = Hit_Sensor_layer->at(i);
        skiroc  = Hit_Sensor_chip->at(i);
        x = Hit_Sensor_amplitudeLow->at(i);
        y = Hit_Sensor_amplitudeHigh->at(i);
        z = Hit_Sensor_Tot->at(i);


        Hist2D[board][skiroc][0]->Fill(x,y);
        Hist2D[board][skiroc][1]->Fill(z,x);
      }



    }


  }
  else
  {
    std::cout<<"Did not find the file or folder... Check Path and try again!"<<std::endl;
  }




  std::cout<<std::endl<<"Exiting dataExtractor"<<std::endl;

  return;
}
