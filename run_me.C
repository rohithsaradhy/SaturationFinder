#include<iostream>
#include "SaturationFinder.h"

void run_me()
{
  SaturationFinder* a = new SaturationFinder(20,80,"Electron","Oct_H6");
  // SaturationFinder* b = new SaturationFinder(20);

  a->dataExtractor();
  // a->SaveHistogram(80,"Electron");
  // a->LoadHistogram(80,"Electron");
  a->Hist2D[1][1][0]->Draw();

  // b->dataExtractor(50,"Electron");

  // b->Hist2D[1][1][0]->Draw();

  return;
}
