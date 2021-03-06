// This takes the NTuples and creates the necessary 2d Histograms so we can work with them faster..
//  NTuples are event based.
// Written by Rohith Saradhy
 #include "SaturationFinder.h"



void SaturationFinder::dataExtractor(int Options)
{
  Int_t board(0),skiroc(0);
  float x(0),y(0),z(0);
  std::cout<<std::endl<<std::endl<<"Starting dataExtractor"<<std::endl;

  //Initialising all the variables...
  std::vector<int>* Hit_Sensor_Channel=0;
  std::vector<int>* Hit_Sensor_Layer=0;
  std::vector<int>* Hit_Sensor_Skiroc=0;
  std::vector<int>* Hit_Sensor_Cell_Type=0;
  // Cell Information Old
	std::vector<float>* Hit_Sensor_Cell_X=0;
	std::vector<float>* Hit_Sensor_Cell_Y=0;
  std::vector<float>* Hit_Sensor_Cell_HG =0;
	std::vector<float>* Hit_Sensor_Cell_HG_Sub=0;
  std::vector<float>* Hit_Sensor_Cell_LG = 0;
	std::vector<float>* Hit_Sensor_Cell_LG_Sub=0;
	std::vector<float>* Hit_Sensor_Cell_ToT_Slow=0;
	std::vector<float>* Hit_Sensor_Cell_ToA_Fall=0;
	std::vector<float>* Hit_Sensor_Cell_ToA_Rise=0;
 //
 //  // Cell Information with PulseFit
  std::vector<float>* Hit_Sensor_Cell_HG_Amplitude=0;
  std::vector<float>* Hit_Sensor_Cell_HG_Amplitude_Error=0;
  std::vector<float>* Hit_Sensor_Cell_HG_Tmax=0;
  std::vector<float>* Hit_Sensor_Cell_HG_Chi2=0;
  std::vector<float>* Hit_Sensor_Cell_HG_Tmax_Error=0;
  std::vector<int>* Hit_Sensor_Cell_HG_Status=0;
  std::vector<int>* Hit_Sensor_Cell_HG_NCalls=0;
 // // Same thing for LG
  std::vector<float>* Hit_Sensor_Cell_LG_Amplitude=0;
  std::vector<float>* Hit_Sensor_Cell_LG_Amplitude_Error=0;
  std::vector<float>* Hit_Sensor_Cell_LG_Tmax=0;
  std::vector<float>* Hit_Sensor_Cell_LG_Chi2=0;
  std::vector<float>* Hit_Sensor_Cell_LG_Tmax_Error=0;
  std::vector<int>* Hit_Sensor_Cell_LG_Status=0;
  std::vector<int>* Hit_Sensor_Cell_LG_NCalls=0;


  //Open file and set the branch to that particular data...
  std::ostringstream filename( std::ostringstream::ate );
  filename.str("");
  filename<<DATA_LOC<<RUN_TYPE<<"/"<<ENERGY<<"GeV.root";
  if(ENERGY == 0)
  {
    filename.str("");
    filename<<DATA_LOC<<RUN_TYPE<<".root";
  }
  std::cout<<"Opening File "<<filename.str().c_str()<<std::endl;
  TFile *file = TFile::Open(filename.str().c_str());
  TTree *T =  (TTree*)file->Get("pulseshapeplotter/T");



  T->SetBranchAddress("Hit_Sensor_Channel", &Hit_Sensor_Channel);
  T->SetBranchAddress("Hit_Sensor_Layer", &Hit_Sensor_Layer);
  T->SetBranchAddress("Hit_Sensor_Skiroc", &Hit_Sensor_Skiroc);
  T->SetBranchAddress("Hit_Sensor_Cell_Type", &Hit_Sensor_Cell_Type);


	T->SetBranchAddress("Hit_Sensor_Cell_X", &Hit_Sensor_Cell_X);
	T->SetBranchAddress("Hit_Sensor_Cell_Y", &Hit_Sensor_Cell_Y);
	T->SetBranchAddress("Hit_Sensor_Cell_HG", &Hit_Sensor_Cell_HG);
  T->SetBranchAddress("Hit_Sensor_Cell_HG_Sub", &Hit_Sensor_Cell_HG_Sub);
  T->SetBranchAddress("Hit_Sensor_Cell_LG", &Hit_Sensor_Cell_LG);
  T->SetBranchAddress("Hit_Sensor_Cell_LG_Sub", &Hit_Sensor_Cell_LG_Sub);
	T->SetBranchAddress("Hit_Sensor_Cell_ToT_Slow", &Hit_Sensor_Cell_ToT_Slow);
	T->SetBranchAddress("Hit_Sensor_Cell_ToA_Fall", &Hit_Sensor_Cell_ToA_Fall);
	T->SetBranchAddress("Hit_Sensor_Cell_ToA_Rise", &Hit_Sensor_Cell_ToA_Rise);

  T->SetBranchAddress("Hit_Sensor_Cell_HG_Amplitude", &Hit_Sensor_Cell_HG_Amplitude);
  T->SetBranchAddress("Hit_Sensor_Cell_HG_Amplitude_Error", &Hit_Sensor_Cell_HG_Amplitude_Error);
  T->SetBranchAddress("Hit_Sensor_Cell_HG_Tmax", &Hit_Sensor_Cell_HG_Tmax);
  T->SetBranchAddress("Hit_Sensor_Cell_HG_Tmax_Error", &Hit_Sensor_Cell_HG_Tmax_Error);
  T->SetBranchAddress("Hit_Sensor_Cell_HG_Chi2", &Hit_Sensor_Cell_HG_Chi2);
  T->SetBranchAddress("Hit_Sensor_Cell_HG_Status", &Hit_Sensor_Cell_HG_Status);
  T->SetBranchAddress("Hit_Sensor_Cell_HG_NCalls", &Hit_Sensor_Cell_HG_NCalls);

  T->SetBranchAddress("Hit_Sensor_Cell_LG_Amplitude", &Hit_Sensor_Cell_LG_Amplitude);
  T->SetBranchAddress("Hit_Sensor_Cell_LG_Amplitude_Error", &Hit_Sensor_Cell_LG_Amplitude_Error);
  T->SetBranchAddress("Hit_Sensor_Cell_LG_Tmax", &Hit_Sensor_Cell_LG_Tmax);
  T->SetBranchAddress("Hit_Sensor_Cell_LG_Tmax_Error", &Hit_Sensor_Cell_LG_Tmax_Error);
  T->SetBranchAddress("Hit_Sensor_Cell_LG_Chi2", &Hit_Sensor_Cell_LG_Chi2);
  T->SetBranchAddress("Hit_Sensor_Cell_LG_Status", &Hit_Sensor_Cell_LG_Status);
  T->SetBranchAddress("Hit_Sensor_Cell_LG_NCalls", &Hit_Sensor_Cell_LG_NCalls);


  Int_t Max_Entries = T->GetEntries();

  std::cout<<Max_Entries<<std::endl;




  InitializeHist2D(0,1);
  InitializeHist2D(1,1);

  switch(Options)
  {
    case 0:
      std::cout<<" Histograms filled using TS3 without CM sub\n";
    break;

    case 1:
    std::cout<<" Histograms filled using TS3 with CM sub \n";
    break;

    case 2:
    std::cout<<" Histograms filled using TS3 with PFA\n";
    break;
  }




  for(int entry = 0; entry < Max_Entries ; entry++)
  {


    T->GetEntry(entry);

    // if(entry == (int)(Max_Entries/2) ) break;  // so it is faster for debugging

    if(entry%1000 == 0)
    {
      std::cout<<entry*100/Max_Entries <<"% \t has been completed... \r";
      std::cout.flush();
    }

    for(int i = 0; i < Hit_Sensor_Cell_LG->size();i++ )
    {
      board = Hit_Sensor_Layer->at(i);
      skiroc  = Hit_Sensor_Skiroc->at(i);

      switch(Options)
      {
        case 0:
        x = Hit_Sensor_Cell_LG->at(i);
        y = Hit_Sensor_Cell_HG->at(i);
        z = Hit_Sensor_Cell_ToT_Slow->at(i);
        break;

        case 1:
        x = Hit_Sensor_Cell_LG->at(i) - Hit_Sensor_Cell_LG_Sub->at(i);
        y = Hit_Sensor_Cell_HG->at(i) - Hit_Sensor_Cell_HG_Sub->at(i);
        z = Hit_Sensor_Cell_ToT_Slow->at(i);
        break;

        case 2:
        x = Hit_Sensor_Cell_LG_Amplitude->at(i);
        y = Hit_Sensor_Cell_HG_Amplitude->at(i);
        z = Hit_Sensor_Cell_ToT_Slow->at(i);
        if(Hit_Sensor_Cell_HG_Status->at(i)!=0 || Hit_Sensor_Cell_LG_Status->at(i)!=0) continue;

        break;
      }

      Hist2D[board][skiroc][0]->Fill(x,y);
      Hist2D[board][skiroc][1]->Fill(z,x);
    }


  }





  std::cout<<"Exiting dataExtractor"<<std::endl;

  return;
}
