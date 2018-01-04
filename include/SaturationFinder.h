#ifndef SATURATIONFINDER_H
#define SATURATIONFINDER_H

#include "string.h"
#include<iostream>
#include "math.h"
#include "TH2F.h"
#include <sstream>
#include "TFile.h"
#include "TCanvas.h"
#include "TRandom.h"
#include "TROOT.h"
#include "TRint.h"
#include <string>
#include "TTree.h"
#include "TH2F.h"
#include <vector>
#include "TMultiGraph.h"
#include "TGraph.h"
#include "TLegend.h"
#include "TPaveText.h"
#include "TGaxis.h"
#include "TFitResult.h"
#include "TProfile.h"
#include "TGraphErrors.h"
#include "TF1.h"
#include <sstream>
#include<fstream>



const Int_t allocateMemory = 30;

class SaturationFinder
{

  private:
    int BOARD = 0;
    float ENERGY = 0;
    std::string RUN_TYPE = ""; // options :: {Electron,Pion,All,All_Electron,All_Pion}
    std::string FIT_NAME = ""; // Prefix to plots and datafiles....
    std::string DATA_LOC = ""; // Prefix to plots and datafiles....
    //For InitializeHist2D method...
    Double_t bin_start=0;
    Double_t bin_stop=0;
    Double_t bin_change1=0;
    Double_t bin_change2=0;

    Double_t bin_width1=0;
    Double_t bin_width2=0;
    Double_t bin_width3=0;

    Double_t current_bin_low=0;
    Int_t bin_total=0;
    Double_t binningX[10000];
    Double_t y_Max=0;
    Double_t y_Min=0;
    Double_t y_bin=0;
    Double_t y_totalbins=0;
    // End InitializeHist2D ...

    // For FitHistogram
    float X[10000];
    float Y[10000];
    float errorY[10000];
    float errorX[10000];
    float ErrorInX_ADC[2];
    float ErrorInY_ADC[2];
    float FitRangeMax[2];
    float FitRangeMin[2];
    //End Fit Histogram

    // For FindValues
    TMultiGraph* mg;
    TGraph* grph[5];
    TGaxis* A;
    float cutoff[2];
    // End FindValues


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
    void InitializeDataArray();
    void dataExtractor();
    void InitializeHist2D(Int_t option,bool hist);
    void SaveHistogram(std::string rootFolder);
    void StoreValues(std::string rootFolder); // Storing Final Values...
    void RetrieveValues(std::string rootFolder); // Retriving Final Values...
    void LoadHistogram(std::string rootFolder);

    void FitHistogram();
    void FindValues();
    void CutOff(int board, int skiroc, int type_num);
    int Max_Index(float* value);
    void Graph_Settings(int board, int skiroc,int type_num);
    void FixAllValues(int type_num);









};
#endif
