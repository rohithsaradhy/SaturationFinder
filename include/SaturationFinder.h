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
    std::string DATA_LOC = ""; // Prefix to plots and datafiles....


  public:
    TH2F* Hist2D[allocateMemory][4][3];
    TFitResultPtr FitResultPtr[allocateMemory][4][3];
    TProfile* HistProfile[allocateMemory][4][3];
    TCanvas* fitCanvas[allocateMemory][4][3];

    int fitStatus[allocateMemory][4][3];
    float CF[allocateMemory][4][3];
    float CF_Err[allocateMemory][4][3];
    float CF_Intercept[allocateMemory][4][3];
    float CF_Intercept_Err[allocateMemory][4][3];
    float TP[allocateMemory][4][3];
    float TP_Err[allocateMemory][4][3];




    SaturationFinder(int board,float energy, std::string run_type, std::string fit_name, std::string data_loc);
    ~SaturationFinder();
    void getInfo();
    void dataExtractor();
    void InitializeHist2D(Int_t option,bool hist);
    void SaveHistogram();
    void LoadHistogram();

    void FitHistogram();
    void FindValues();
    void CutOff(int board, int skiroc, int type_num);
    int Max_Index(float* value);
    void Graph_Settings(int board, int skiroc,int type_num);








};
#endif
