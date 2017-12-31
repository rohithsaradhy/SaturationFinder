#include "SaturationFinder.h"



void SaturationFinder::SaveHistogram()
{
  std::ostringstream filename( std::ostringstream::ate );
  std::ostringstream os( std::ostringstream::ate );

  filename.str("");
  filename<<"./temp_data/"<<FIT_NAME<<"_Energy_"<<ENERGY<<"_"<<RUN_TYPE<<".root";

  TFile *file = TFile::Open(filename.str().c_str(),"RECREATE");
  for(int i=0;i<BOARD;i++)
  {
    for(int j=0;j<4;j++)
    {
          os.str("");
          os<<FIT_NAME<<"_Energy_"<<ENERGY<<"_Board_"<<i<<"_Skiroc_"<<j<<"_HighGaintoLowGain";
          Hist2D[i][j][0]->Write(os.str().c_str());
          os.str("");
          os<<FIT_NAME<<"_Energy_"<<ENERGY<<"_Board_"<<i<<"_Skiroc_"<<j<<"_LowGaintoTOTSLow";
          Hist2D[i][j][1]->Write(os.str().c_str());

          std::cout<<FIT_NAME<<"_Energy_"<<ENERGY<<"_"<<RUN_TYPE<<"\t"<<"Saving  :: "<<(i*4 + j)*100/(BOARD*4 + 3)<<"% \r";
          std::cout.flush();

    }
  }
  std::cout<<std::endl;

  file->Close();

}
