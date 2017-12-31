#include "SaturationFinder.h"


void SaturationFinder::FindValues()
{
  for(int board=0;board < BOARD; board++)
  {
    for(int skiroc=0;skiroc < 4; skiroc++)
    {
      // CutOff(board,skiroc,0);
      // CutOff(board,skiroc,1);

    }
  }


}


void SaturationFinder::CutOff(int board, int skiroc, int type_num)
{

  switch(type_num)
  {
    case 0:
    type = "HighGaintoLowGain";
    break;
    case 1:
    type = "LowGaintoTOTSLow";
    break;
  }

  os.str("");
  os<<FIT_NAME<<"_Energy_"<<ENERGY<<"_Board_"<<board<<"_Skiroc_"<<skiroc<<"_"<<type;
  // Initialising the Canvas...
  // std::cout<<board<<"\t"<<skiroc<<"\t"<<type_num<<std::endl;
  fitCanvas[board][skiroc][type_num] = new TCanvas(os.str().c_str(),os.str().c_str(),1366,768);
  // HistProfile[board][skiroc][type_num]->Draw();
  CF[board][skiroc][type_num] = FitResultPtr[board][skiroc][type_num]->Parameter(0);
  CF_Err[board][skiroc][type_num] = FitResultPtr[board][skiroc][type_num]->ParError(0);

  CF_Intercept[board][skiroc][type_num] = FitResultPtr[board][skiroc][type_num]->Parameter(1);
  CF_Intercept_Err[board][skiroc][type_num] = FitResultPtr[board][skiroc][type_num]->ParError(1);



}
