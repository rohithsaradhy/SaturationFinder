#include<iostream>
#include "SaturationFinder.h"



void plot()
{

  // gROOT->SetBatch(kTRUE); //Not displaying anything

  SaturationFinder* Oct_H6 = new SaturationFinder(20,0,"All","Oct_H6","/home/rsaradhy/Work/Output/TransitionH_L/New_Data/Oct_H6_NTuple/"); // 0implies that it is a allfile...
  SaturationFinder* Oct_H2 = new SaturationFinder(17,0,"All","Oct_H2","/home/rsaradhy/Work/Output/TransitionH_L/New_Data/Oct_NTuple/"); // 0i mplies that it is a allfile...

  SaturationFinder* Oct_H2_TS3 = new SaturationFinder(17,0,"All","Oct_H2_TS3","/home/rsaradhy/Work/Output/TransitionH_L/New_Data/Oct_NTuple/"); // 0i mplies that it is a allfile...
  SaturationFinder* Oct_H6_TS3 = new SaturationFinder(20,0,"All","Oct_H6_TS3","/home/rsaradhy/Work/Output/TransitionH_L/New_Data/Oct_H6_NTuple/"); // 0implies that it is a allfile...


  std::ostringstream os( std::ostringstream::ate );


  // Oct_H2->dataExtractor();
  // Oct_H2->SaveHistogram("./temp_data/");
  // Oct_H2->LoadHistogram("./temp_data/");
  // Oct_H2->FitHistogram();
  // Oct_H2->FindValues();
  // Oct_H2->StoreValues("./temp_data/");
  Oct_H2->RetrieveValues("./temp_data/");

  // Oct_H6->dataExtractor();
  // Oct_H6->SaveHistogram("./temp_data/");
  // Oct_H6->LoadHistogram("./temp_data/");
  // Oct_H6->FitHistogram();
  // Oct_H6->FindValues();
  // Oct_H6->StoreValues("./temp_data/");
  Oct_H6->RetrieveValues("./temp_data/");


  // Oct_H2_TS3->dataExtractor();
  // Oct_H2_TS3->SaveHistogram("./temp_data/");
  // Oct_H2_TS3->LoadHistogram("./temp_data/");
  // Oct_H2_TS3->FitHistogram();
  // Oct_H2_TS3->FindValues();
  // Oct_H2_TS3->StoreValues("./temp_data/");
  Oct_H2_TS3->RetrieveValues("./temp_data/");

  // Oct_H6_TS3->dataExtractor();
  // Oct_H6_TS3->SaveHistogram("./temp_data/");
  // Oct_H6_TS3->LoadHistogram("./temp_data/");
  // Oct_H6_TS3->FitHistogram();
  // Oct_H6_TS3->FindValues();
  // Oct_H6_TS3->StoreValues("./temp_data/");
  Oct_H6_TS3->RetrieveValues("./temp_data/");

  TCanvas* H2_CF_Canvas = new TCanvas("H2_CF","H2_CF",1366,768);
  // TCanvas* H2_TP_Canvas = new TCanvas("H2_TP","H2_TP",1366,768);
  TMultiGraph* mg = new TMultiGraph();

  float X[100],Y[100],X_Err[100],Y_Err[100];
  int count=0;
  for(int board=0;board<17;board++)
  {
    for(int skiroc=0;skiroc<4;skiroc++)
    {
      X[count] = count;
      X_Err[count] = 0;
      Y[count] = Oct_H6->CF[board][skiroc][0];
      Y_Err[count] = Oct_H6->CF_Err[board][skiroc][0];
      count++;
    }
  }

  TGraph* H2_CF_Graph = new TGraphErrors(count,X,Y,X_Err,Y_Err);
  H2_CF_Graph->SetName("PulseFit");
  H2_CF_Graph->SetTitle("");

  H2_CF_Graph->SetMarkerStyle(22);
  H2_CF_Graph->SetMarkerColor(kRed);
  H2_CF_Graph->SetMarkerSize(3);
  mg->Add(H2_CF_Graph);







  count = 0;
  for(int board=0;board<17;board++)
  {
    for(int skiroc=0;skiroc<4;skiroc++)
    {
      X[count] = count;
      X_Err[count] = 0;
      Y[count] = Oct_H6_TS3->CF[board][skiroc][0];
      Y_Err[count] = Oct_H6_TS3->CF_Err[board][skiroc][0];
      count++;
    }
  }

  TGraph* H2_CF_Graph2 = new TGraphErrors(count,X,Y,X_Err,Y_Err);
  H2_CF_Graph2->SetName("TS3");
  H2_CF_Graph2->SetTitle("");
  H2_CF_Graph2->SetMarkerStyle(20);
  H2_CF_Graph2->SetMarkerColor(kBlue);
  H2_CF_Graph2->SetMarkerSize(3);
  mg->Add(H2_CF_Graph2);

  mg->Draw("AP");

  TLegend* legend ;
  TLatex* tex ;
  TPaveText* label2;
  TPaveText* label1;
  label1  = new TPaveText(0.5434462,0.9077253,0.6958763,0.9663805,"brNDC");
  label1->SetBorderSize(0);
  label1->SetFillStyle(0);
  label1->SetTextAlign(12);
  label1->SetTextSize(0.059);
  label1->SetTextFont (62);
  label1->AddText("HGCAL test beam, Oct 2017");
  label1->Draw("same");

  label2  = new TPaveText(0.09278351,0.9077253,0.3048601,0.9663805,"brNDC");
  label2->SetBorderSize(0);
  label2->SetFillStyle(0);
  label2->SetTextAlign(12);
  label2->SetTextSize(0.080);
  label2->SetTextFont (62);
  label2->AddText("CMS Preliminary");
  label2->Draw("same");

  legend = new TLegend(0.1391753,0.75,0.3004418,0.89,NULL,"brNDC");
  legend->SetHeader("H6 Octorber Run","C");
  legend->AddEntry("PulseFit","With Pulse Fitting","eP");
  legend->AddEntry("TS3","Time Sample 3","ep");
  legend->SetTextFont(62);
  legend->Draw();

  gPad->Update();

  // mg->GetYaxis()->SetRangeUser(1000,3011);
  mg->GetYaxis()->SetRangeUser(3,15);
  mg->GetYaxis()->SetLabelFont(62);
  mg->GetYaxis()->SetTitleSize(0.048);
  mg->GetYaxis()->SetTitleFont(62);
  // mg->GetYaxis()->SetTitleOffset(1.5);

  mg->GetXaxis()->SetLabelFont(62);
  mg->GetXaxis()->SetTitleFont(62);
  mg->GetXaxis()->SetTitleSize(0.048);
  // mg->GetXaxis()->SetRangeUser(-10,53);
  mg->GetXaxis()->SetRangeUser(-10,85);
  mg->GetXaxis()->SetTitle("Board*4 + Skiroc");
  mg->GetYaxis()->SetTitle("Conversion Factor (LG #rightarrow HG)");
  // mg->GetYaxis()->SetTitle("Transition Point (HG #rightarrow LG)");
  gPad->Update();
  gPad->SetGridx();
  gPad->SetGridy();




  return;
}


#ifndef MAIN
#define MAIN
int main()
{
  plot();
}
#endif
