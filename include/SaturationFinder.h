#ifndef SATURATIONFINDER_H
#define SATURATIONFINDER_H

#include "string.h"
#include<iostream>
#include "TH2F.h"
#include <sstream>
#include "TFile.h"


class SaturationFinder
{

  private:
    int BOARD = 0;
  public:
    TH2F* Hist2D[30][4][3];
    SaturationFinder();
    ~SaturationFinder();
    SaturationFinder(int board);
    void dataExtractor(float, std::string);
    void InitializeHist2D(Int_t);





};
#endif
