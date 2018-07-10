#include<iostream>
#include "SaturationFinder.h"



void plot_Stability_CF()
{

  gROOT->SetBatch(kTRUE); //Not displaying anything
  SaturationFinder* a;
  SaturationFinder* b;
  SaturationFinder* c;
  SaturationFinder* Oct_H2_TS3 = new SaturationFinder(17,0,"All","April","Oct_H2_TS3","/home/rsaradhy/Work/Output/TransitionH_L/Data/data_27_3_2018/H2/"); // 0 implies that it is a allfile which is kept in the root directory...
  SaturationFinder* Oct_H2_TS3_CM = new SaturationFinder(17,0,"All","April","Oct_H2_TS3_CM","/home/rsaradhy/Work/Output/TransitionH_L/Data/data_27_3_2018/H2/"); // 0 implies that it is a allfile which is kept in the root directory...
  SaturationFinder* Oct_H2_PFA = new SaturationFinder(17,0,"All","April","Oct_H2_PFA","/home/rsaradhy/Work/Output/TransitionH_L/Data/data_27_3_2018/H2/"); // 0 implies that it is a allfile which is kept in the root directory...
  SaturationFinder* Oct_H6_TS3 = new SaturationFinder(20,0,"All","April","Oct_H6_TS3","/home/rsaradhy/Work/Output/TransitionH_L/Data/data_27_3_2018/H6/"); // 0 implies that it is a allfile which is kept in the root directory...
  SaturationFinder* Oct_H6_TS3_CM = new SaturationFinder(20,0,"All","April","Oct_H6_TS3_CM","/home/rsaradhy/Work/Output/TransitionH_L/Data/data_27_3_2018/H6/"); // 0 implies that it is a allfile which is kept in the root directory...
  SaturationFinder* Oct_H6_PFA = new SaturationFinder(20,0,"All","April","Oct_H6_PFA","/home/rsaradhy/Work/Output/TransitionH_L/Data/data_27_3_2018/H6/"); // 0 implies that it is a allfile which is kept in the root directory...


  std::ostringstream os( std::ostringstream::ate );



  // TCanvas* H2_TP_Canvas = new TCanvas("H2_TP","H2_TP",1366,768);
  TCanvas* CF_Canvas = new TCanvas("CF","CF",1366,768);
  TMultiGraph* mg = new TMultiGraph();




  std::ostringstream graphHeader( std::ostringstream::ate );
  std::ostringstream outputFile( std::ostringstream::ate );

  a=Oct_H2_TS3_CM; //post CM
  b=Oct_H2_PFA; // Pulse Fit
  c=Oct_H2_TS3; //pre CM
  outputFile.str();
  outputFile<<"./Analysed_data/April/H2_CF_Stability.png";
  graphHeader.str("");
  graphHeader<<"H2 Octorber Run";

  a->CreateStructure("./Analysed_data");
  a->RetrieveValues("");
  // a->RetrieveValues("Final_"); //Store those values with a name prefix given as the argument


  float X[100],Y[100],X_Err[100],Y_Err[100];
  int count=0;
  for(int board=0;board<a->BOARD;board++)
  {
    for(int skiroc=0;skiroc<4;skiroc++)
    {
      X[count] = count;
      X_Err[count] = 0;
      Y[count] = a->CF[board][skiroc][0];
      Y_Err[count] = a->CF_Err[board][skiroc][0];
      count++;
    }
  }

  TGraph* Graph = new TGraphErrors(count,X,Y,X_Err,Y_Err);
  Graph->SetName("RedOne");
  Graph->SetTitle("");

  Graph->SetMarkerStyle(22);
  Graph->SetMarkerColor(kRed);
  Graph->SetMarkerSize(3);
  mg->Add(Graph);






  a = b;
  a->CreateStructure("./Analysed_data");
  a->RetrieveValues("");
  // a->RetrieveValues("Final_"); //Store those values with a name prefix given as the argument



  count = 0;
  for(int board=0;board<a->BOARD;board++)
  {
    for(int skiroc=0;skiroc<4;skiroc++)
    {
      X[count] = count;
      X_Err[count] = 0;
      Y[count] = a->CF[board][skiroc][0];
      Y_Err[count] = a->CF_Err[board][skiroc][0];
      count++;
    }
  }

  TGraph* Graph2 = new TGraphErrors(count,X,Y,X_Err,Y_Err);
  Graph2->SetName("BlueOne");
  Graph2->SetTitle("");
  Graph2->SetMarkerStyle(20);
  Graph2->SetMarkerColor(kBlue);
  Graph2->SetMarkerSize(2);
  mg->Add(Graph2);

  a = c;
  a->CreateStructure("./Analysed_data");
  a->RetrieveValues("");

  count = 0;
  for(int board=0;board<a->BOARD;board++)
  {
    for(int skiroc=0;skiroc<4;skiroc++)
    {
      X[count] = count;
      X_Err[count] = 0;
      Y[count] = a->CF[board][skiroc][0];
      Y_Err[count] = a->CF_Err[board][skiroc][0];
      count++;
    }
  }

  TGraph* Graph3 = new TGraphErrors(count,X,Y,X_Err,Y_Err);
  Graph3->SetName("GreenOne");
  Graph3->SetTitle("");
  Graph3->SetMarkerStyle(34);
  Graph3->SetMarkerColor(kGreen);
  Graph3->SetMarkerSize(2);
  mg->Add(Graph3);

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
  legend->SetHeader(graphHeader.str().c_str(),"C");
  legend->AddEntry("GreenOne","TS3 pre CM subtraction","ep");
  legend->AddEntry("RedOne","TS3 after CM subtraction","eP");
  legend->AddEntry("BlueOne","Pulse Fit Amplitude","ep");
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

  gPad->SaveAs(outputFile.str().c_str());




  return;
}


#ifndef MAIN
#define MAIN
int main()
{
  plot_Stability_CF();
}
#endif
