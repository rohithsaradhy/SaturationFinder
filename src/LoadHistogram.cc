#include "SaturationFinder.h"

void SaturationFinder::LoadHistogram(float Energy, std::string Run_Type)
{
  std::ostringstream filename( std::ostringstream::ate );
  std::ostringstream os( std::ostringstream::ate );

  filename.str("");
  filename<<"./temp_data/"<<Energy<<"_"<<Run_Type<<".root";

  TH2F* temp;
  TH2F* temp1;


  TFile *file = TFile::Open(filename.str().c_str()); //Do not close the TFile Object. Canvas will be empty.
  for(int i=0;i<BOARD;i++)
  {
    for(int j=0;j<4;j++)
    {
      os.str("");
      os<<Energy<<"_Board_"<<i<<"_Skiroc_"<<j<<"_HighGaintoLowGain";
      gDirectory->GetObject(os.str().c_str(),Hist2D[i][j][0]);
      Hist2D[i][j][0]->SetDirectory(0) ; //Keep the Hist stay after file close...
      os.str("");
      os<<Energy<<"_Board_"<<i<<"_Skiroc_"<<j<<"_LowGaintoTOTSLow";
      gDirectory->GetObject(os.str().c_str(),Hist2D[i][j][1] );
      Hist2D[i][j][1]->SetDirectory(0) ;

    }
  }

  file->Close();
}
