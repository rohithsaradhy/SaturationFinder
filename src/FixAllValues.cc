#include "SaturationFinder.h"

void SaturationFinder::FixAllValues(int type_num)
{
  TH1F* CF_Hist;
  TH1F* TP_Hist;
  CF_Hist = new TH1F("ConversionFact","ConversionFact",500,6,11);
  TP_Hist = new TH1F("TransitionPoint","TransitionPoint",40,800,3500);





  for(int board =0; board<BOARD;board++)
  {
    for(int skiroc=0; skiroc < 4; skiroc++)
    {

      if (CF[board][skiroc][0] > 0) CF_Hist->Fill(CF[board][skiroc][0]);

      if (TP[board][skiroc][0] > 0) TP_Hist->Fill(TP[board][skiroc][0]);
    }
  }

  // CF_Hist->Draw();
  TP_Hist->Draw();
  // cout<<hist->

}
