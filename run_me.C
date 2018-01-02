#include<iostream>
#include "SaturationFinder.h"

void run_me()
{

  gROOT->SetBatch(kTRUE); //Not displaying anything

  SaturationFinder* a = new SaturationFinder(17,0,"All","Oct_Run","/home/rsaradhy/Work/Output/TransitionH_L/New_Data/Oct_NTuple/"); // 0i mplies that it is a allfile...
  // SaturationFinder* a = new SaturationFinder(20,0,"All","Oct_H6","/home/rsaradhy/Work/Output/TransitionH_L/New_Data/Oct_H6_NTuple/"); // 0implies that it is a allfile...


  // a->dataExtractor();
  // a->SaveHistogram();
  a->LoadHistogram();
  a->FitHistogram();
  a->FindValues();
  // a->InitializeHist2D(0,1);
  // a->Hist2D[0][0][1]->Draw();
  // a->CutOff(2,2,1);
  // a->CutOff(2,2,0);
  std::ostringstream os( std::ostringstream::ate );

  for(int i=0 ; i< 20 ; i++)
  {
    for(int j =0; j<4 ;j++)
    {
        int type_num =0;
        if(a->fitStatus[i][j][type_num]==4000)
        {
          os.str("");
          os<<"./Graphs/"<<a->fitCanvas[i][j][type_num]->GetName()<<".png";
          a->fitCanvas[i][j][type_num]->SaveAs(os.str().c_str());
        }
    }

  }

  return;
}
