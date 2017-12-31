#include "SaturationFinder.h"



void SaturationFinder::FitHistogram()
{

  Int_t Hist_Entries(0);

  //For HighGain to LowGain
  for(int board = 0;board<BOARD;board++)
  {
    for(int skiroc = 0 ;skiroc<4;skiroc++)
    {

      // Making sure that histogram has enough entries to be used in the fit...
      Hist_Entries = Hist2D[board][skiroc][0]->GetEntries();
      if(Hist_Entries < 100) continue;




    }
  }



}
