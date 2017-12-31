#include "SaturationFinder.h"

void SaturationFinder::LoadHistogram()
{
  std::ostringstream filename( std::ostringstream::ate );
  std::ostringstream os( std::ostringstream::ate );

  filename.str("");
  filename<<"./temp_data/"<<ENERGY<<"_"<<RUN_TYPE<<".root";

  TH2F* temp;
  TH2F* temp1;


  TFile *file = TFile::Open(filename.str().c_str()); //Do not close the TFile Object. Canvas will be empty.
  for(int i=0;i<BOARD;i++)
  {
    for(int j=0;j<4;j++)
    {
      os.str("");
      os<<ENERGY<<"_Board_"<<i<<"_Skiroc_"<<j<<"_HighGaintoLowGain";
      gDirectory->GetObject(os.str().c_str(),Hist2D[i][j][0]);
      Hist2D[i][j][0]->SetDirectory(0) ; //Keep the Hist stay after file close...
      os.str("");
      os<<ENERGY<<"_Board_"<<i<<"_Skiroc_"<<j<<"_LowGaintoTOTSLow";
      gDirectory->GetObject(os.str().c_str(),Hist2D[i][j][1] );
      Hist2D[i][j][1]->SetDirectory(0) ;

      std::cout<<ENERGY<<"\t"<<RUN_TYPE<<"\t"<<"Loading... \t "<<(i*4 + j)*100/(BOARD*4 + 3)<<"\r";
      std::cout.flush();

    }
  }

  file->Close();
}
