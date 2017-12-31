#ifndef SATURATIONFINDER_H
#define SATURATIONFINDER_H

#include "string.h"
#include<iostream>
#include "TH2F.h"
#include <sstream>
#include "TFile.h"
#include "TCanvas.h"
#include "TRandom.h"


const Int_t allocateMemory = 30;

class SaturationFinder
{

  private:
    int BOARD = 0;
    float ENERGY = 0;
    std::string RUN_TYPE = ""; // options :: {Electron,Pion,All,All_Electron,All_Pion}
    std::string FIT_NAME = ""; // Prefix to plots and datafiles....
  public:
    TH2F* Hist2D[allocateMemory][4][3];
    TFitResultPtr FitResultPtr[allocateMemory][4][3];
    TProfile* HistProfile[allocateMemory][4][3];
    TCanvas* fitCanvas[allocateMemory][4][3];

    SaturationFinder(int, float, std::string, std::string);
    ~SaturationFinder();
    void getInfo();
    void dataExtractor();
    void InitializeHist2D(Int_t);
    void SaveHistogram();
    void LoadHistogram();

    void FitHistogram();
    void CutOff();





};
#endif
