#include "SaturationFinder.h"



void SaturationFinder::SaveHistogram(float Energy, std::string Run_Type)
{
  std::ostringstream filename( std::ostringstream::ate );
  std::ostringstream os( std::ostringstream::ate );

  filename.str("");
  filename<<"./temp_data/"<<Energy<<"_"<<Run_Type<<".root";

  TFile *file = TFile::Open(filename.str().c_str(),"RECREATE");
  for(int i=0;i<BOARD;i++)
  {
    for(int j=0;j<4;j++)
    {
          os.str("");
          os<<Energy<<"_Board_"<<i<<"_Skiroc_"<<j<<"_HighGaintoLowGain";
          Hist2D[i][j][0]->Write(os.str().c_str());
          os.str("");
          os<<Energy<<"_Board_"<<i<<"_Skiroc_"<<j<<"_LowGaintoTOTSLow";
          Hist2D[i][j][1]->Write(os.str().c_str());

    }
  }

  file->Close();

}
