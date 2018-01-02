#include<iostream>
#include "SaturationFinder.h"

void run_me()
{

  gROOT->SetBatch(kTRUE); //Not displaying anything

  SaturationFinder* a = new SaturationFinder(20,80,"Electron","Oct_H6");
  // SaturationFinder* b = new SaturationFinder(20);

  a->dataExtractor();
  // a->SaveHistogram();
  // a->LoadHistogram();
  a->FitHistogram();
  a->FindValues();
  // a->InitializeHist2D(0,1);
  // a->Hist2D[1][1][0]->Draw();
  a->CutOff(2,2,1);
  a->CutOff(2,2,0);

  a->fitCanvas[2][2][0]->SaveAs("HG.png");
  a->fitCanvas[2][2][1]->SaveAs("LG.png");

  return;
}
