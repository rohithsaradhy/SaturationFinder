#include<iostream>
#include<string>
#include "SaturationFinder.h"



void run_me()
{


  // SaturationFinder* a = new SaturationFinder(17,0,"All","Oct_H2_test_TS3","/home/rsaradhy/Work/Output/TransitionH_L/New_Data/Oct_NTuple/"); // 0i mplies that it is a allfile...
  // SaturationFinder* a = new SaturationFinder(17,0,"All","Oct_H2_test","/home/rsaradhy/Work/Output/TransitionH_L/New_Data/Oct_NTuple/"); // 0i mplies that it is a allfile...
  // SaturationFinder* a = new SaturationFinder(17,0,"All_Pion","Oct_H2_test_Pion","/home/rsaradhy/Work/Output/TransitionH_L/New_Data/Oct_NTuple/"); // 0i mplies that it is a allfile...
  // SaturationFinder* a = new SaturationFinder(17,0,"All_Electron_new_test","Oct_H2_test_Electron","/home/rsaradhy/Work/Output/TransitionH_L/New_Data/Oct_NTuple/"); // 0i mplies that it is a allfile...
  // SaturationFinder* a = new SaturationFinder(17,0,"HexaOutput_1652","Oct_H2_test_Electron","/home/rsaradhy/Work/Output/TransitionH_L/New_Data/Oct_NTuple/"); // 0i mplies that it is a allfile...
  // SaturationFinder* a = new SaturationFinder(17,0,"All_Electron","Oct_H2_test_Electron","/home/rsaradhy/Work/Output/TransitionH_L/New_Data/Oct_NTuple/"); // 0i mplies that it is a allfile...
  // SaturationFinder* a = new SaturationFinder(20,0,"All","Oct_H6","/home/rsaradhy/Work/Output/TransitionH_L/New_Data/Oct_H6_NTuple/"); // 0implies that it is a allfile...


  std::ostringstream os( std::ostringstream::ate );
  SaturationFinder* a = new SaturationFinder(17,0,"HexaOutput_1652","Oct_H2_test_Electron","/home/rsaradhy/Work/Output/TransitionH_L/New_Data/Oct_NTuple/"); // 0i mplies that it is a allfile...
  // SaturationFinder* a = new SaturationFinder(20,0,"HexaOutput_1756","Oct_H2_test_Electron","/home/rsaradhy/Work/Output/TransitionH_L/New_Data/Oct_NTuple/"); // 0i mplies that it is a allfile...

  gROOT->SetBatch(kTRUE); //Not displaying anything
  //
  // a->InitializeHist2D(2,1);
  gStyle->SetOptStat(0);
  a->dataExtractor();

  TH2F* mg = a->Hist2D[2][0][0];
  mg->SetTitle("Layer 3 Skiroc 0 Module #71 Post CM Sub Cell 1340");
  mg->GetXaxis()->SetTitle("Low Gain (ADC Counts)");
  mg->GetXaxis()->SetLabelFont(62);
  mg->GetXaxis()->SetTitleFont(62);
  mg->GetXaxis()->SetTitleSize(0.048);
  mg->GetXaxis()->SetTitleOffset(1.0);
  mg->GetXaxis()->SetRangeUser(0,800);



  mg->GetYaxis()->SetTitle("High Gain (ADC Counts)");
  mg->GetYaxis()->SetLabelFont(62);
  mg->GetYaxis()->SetTitleFont(62);
  mg->GetYaxis()->SetTitleSize(0.048);
  mg->GetYaxis()->SetTitleOffset(1);
  // mg->GetYaxis()->SetRangeUser(0,2000);


  mg->Draw("");

  // gPad->SaveAs("./XY.png");


  // a->SaveHistogram("./temp_data/");
  // a->Hist2D[1][2][1]->Draw();
  // a->LoadHistogram("./temp_data/");


  // a->FitHistogram();
  // a->FindValues();


  // int i =1,j=2,type_num=0;
  // os.str("");
  // if(type_num ==0 )os<<"./Graphs/HG_LG/"<<a->fitCanvas[i][j][type_num]->GetName()<<".png";
  // else os<<"./Graphs/LG_TOT/"<<a->fitCanvas[i][j][type_num]->GetName()<<".png";
  // a->fitCanvas[i][j][type_num]->SaveAs(os.str().c_str());


  // a->RetrieveValues("./temp_data/");
  // a->StoreValues("./temp_data/");
  // a->FixAllValues(0);
  // a->FixAllValues(1);
  // a->StoreValues("./temp_data/Final_");


  // b->FitHistogram();
  // b->FindValues();
  // a->InitializeHist2D(0,1);
  // a->Hist2D[0][0][1]->Draw();
  // a->CutOff(2,2,1);
  // a->CutOff(2,2,0);
  // std::cout<<a->fitStatus[0][1][1]<<std::endl;
  // a->fitCanvas[0][1][1]->SaveAs("./temp.png");
  // a->fitCanvas[0][1][0]->SaveAs("./temp1.png");
  // //
  TCanvas* c1;
  for(int i=0 ; i< 20 ; i++)
  {
    for(int j =0; j<4 ;j++)
    {
        for(int type_num=0;type_num<1;type_num++)
        {
          if(a->fitStatus[i][j][type_num]==99999) // Checking whether the fit was possible with enought events...

          {
            os.str("");
            if(type_num ==0 )os<<"./Graphs/HG_LG/"<<a->fitCanvas[i][j][type_num]->GetName()<<".png";
            else os<<"./Graphs/LG_TOT/"<<a->fitCanvas[i][j][type_num]->GetName()<<".png";
            // a->fitCanvas[i][j][type_num]->SaveAs(os.str().c_str());
            // a->fitCanvas[i][j][0]->SaveAs(os.str().c_str());

            a->fitCanvas[i][j][type_num]->SaveAs(os.str().c_str());
            // c1= new TCanvas("2D Histogram","2D Histogram",1366,768);
            // c1->cd();
            // a->Hist2D[i][j][type_num]->SetTitle("");
            // a->Hist2D[i][j][type_num]->Draw();
            // c1->SaveAs(os.str().c_str());


          }

        }
    }

  }


  return;
}


#ifndef MAIN
#define MAIN
int main()
{
  run_me();
}
#endif
