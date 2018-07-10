#include<iostream>
#include "SaturationFinder.h"



void plot_ModuleStability_CF()
{

  gROOT->SetBatch(kTRUE); //Not displaying anything
  SaturationFinder* a[6];
  SaturationFinder* Oct_H2_TS3 = new SaturationFinder(17,0,"All","April","Oct_H2_TS3","/home/rsaradhy/Work/Output/TransitionH_L/Data/data_27_3_2018/H2/"); // 0 implies that it is a allfile which is kept in the root directory...
  SaturationFinder* Oct_H2_TS3_CM = new SaturationFinder(17,0,"All","April","Oct_H2_TS3_CM","/home/rsaradhy/Work/Output/TransitionH_L/Data/data_27_3_2018/H2/"); // 0 implies that it is a allfile which is kept in the root directory...
  SaturationFinder* Oct_H2_PFA = new SaturationFinder(17,0,"All","April","Oct_H2_PFA","/home/rsaradhy/Work/Output/TransitionH_L/Data/data_27_3_2018/H2/"); // 0 implies that it is a allfile which is kept in the root directory...
  SaturationFinder* Oct_H6_TS3 = new SaturationFinder(20,0,"All","April","Oct_H6_TS3","/home/rsaradhy/Work/Output/TransitionH_L/Data/data_27_3_2018/H6/"); // 0 implies that it is a allfile which is kept in the root directory...
  SaturationFinder* Oct_H6_TS3_CM = new SaturationFinder(20,0,"All","April","Oct_H6_TS3_CM","/home/rsaradhy/Work/Output/TransitionH_L/Data/data_27_3_2018/H6/"); // 0 implies that it is a allfile which is kept in the root directory...
  SaturationFinder* Oct_H6_PFA = new SaturationFinder(20,0,"All","April","Oct_H6_PFA","/home/rsaradhy/Work/Output/TransitionH_L/Data/data_27_3_2018/H6/"); // 0 implies that it is a allfile which is kept in the root directory...


  std::ostringstream os( std::ostringstream::ate );


  std::ostringstream graphHeader( std::ostringstream::ate );
  std::ostringstream outputFile( std::ostringstream::ate );

  a[0]=Oct_H2_TS3_CM; //post CM
  a[1]=Oct_H2_PFA; // Pulse Fit
  a[2]=Oct_H2_TS3; //pre CM
  a[3]=Oct_H6_TS3_CM; //post CM
  a[4]=Oct_H6_PFA; // Pulse Fit
  a[5]=Oct_H6_TS3; //pre CM

  outputFile.str();
  outputFile<<"./Analysed_data/April/Comparison_CF.png";
  graphHeader.str("");
  graphHeader<<"Comparisons of Conversion Factors";


  // a->RetrieveValues("Final_"); //Store those values with a name prefix given as the argument


  float X[100],Y[100],X_Err[100],Y_Err[100];
  TGraph* Graph[6];


  std::map<int,int> indexModule;
  int index=0;
  for(int i=0; i<a[5]->BOARD;i++)
  {
      a[5]->CreateStructure("./Analysed_data");
      a[5]->RetrieveValues("");
      indexModule[a[5]->Module[i]] = index;
      index++;
  }


  for(int i=0; i<6;i++)
  {
    a[i]->CreateStructure("./Analysed_data");
    a[i]->RetrieveValues("");
    int count=0;
    for(int board=0;board<a[i]->BOARD;board++)
    {
      for(int skiroc=0;skiroc<4;skiroc++)
      {
        X[count] = indexModule[a[i]->Module[board]]*4 + skiroc;
        X_Err[count] = 0;
        Y[count] = a[i]->CF[board][skiroc][0];
        Y_Err[count] = a[i]->CF_Err[board][skiroc][0];
        count++;
      }
    }
    Graph[i]=new TGraphErrors(count,X,Y,X_Err,Y_Err);

  }

  Graph[0]->SetName("0");
  Graph[0]->SetTitle("");
  Graph[0]->SetMarkerStyle(20);
  Graph[0]->SetMarkerColor(kRed);
  Graph[0]->SetMarkerSize(2);

  Graph[1]->SetName("1");
  Graph[1]->SetTitle("");
  Graph[1]->SetMarkerStyle(21);
  Graph[1]->SetMarkerColor(kRed);
  Graph[1]->SetMarkerSize(2);

  Graph[2]->SetName("2");
  Graph[2]->SetTitle("");
  Graph[2]->SetMarkerStyle(22);
  Graph[2]->SetMarkerColor(kRed);
  Graph[2]->SetMarkerSize(2);
  Graph[3]->SetName("3");
  Graph[3]->SetTitle("");
  Graph[3]->SetMarkerStyle(20);
  Graph[3]->SetMarkerColor(kBlack);
  Graph[3]->SetMarkerSize(2);
  Graph[4]->SetName("4");
  Graph[4]->SetTitle("");
  Graph[4]->SetMarkerStyle(21);
  Graph[4]->SetMarkerColor(kBlack);
  Graph[4]->SetMarkerSize(2);
  Graph[5]->SetName("5");
  Graph[5]->SetTitle("");
  Graph[5]->SetMarkerStyle(22);
  Graph[5]->SetMarkerColor(kBlack);
  Graph[5]->SetMarkerSize(2);

  TMultiGraph* mg = new TMultiGraph();
  TMultiGraph* mg1 = new TMultiGraph();
  TMultiGraph* mg2 = new TMultiGraph();

  mg->Add(Graph[0]);
  mg->Add(Graph[3]);
  mg1->Add(Graph[1]);
  mg1->Add(Graph[4]);
  mg2->Add(Graph[2]);
  mg2->Add(Graph[5]);



  TCanvas* Canvas = new TCanvas("CF","CF",1366,768);
  TCanvas* Canvas1 = new TCanvas("CF1","CF1",1366,768);
  TCanvas* Canvas2 = new TCanvas("CF2","CF1",1366,768);
  TLegend* legend ;
  TLatex* tex ;
  TPaveText* label2;
  TPaveText* label1;

  Canvas->cd();
  mg->Draw("AP");
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
  legend->AddEntry("0","H2::TS3 post CM subtraction","ep");
  // legend->AddEntry("1","H2::Pulse Fit Amplitude","ep");
  // legend->AddEntry("2","H2::TS3 pre CM subtraction","eP");
  legend->AddEntry("3","H6::TS3 post CM subtraction","eP");
  // legend->AddEntry("4","H6::Pulse Fit Amplitude","ep");
  // legend->AddEntry("5","H6::TS3 pre CM subtraction","ep");
  legend->SetTextFont(62);
  legend->Draw();

  // a[0]=Oct_H2_TS3_CM; //post CM
  // a[1]=Oct_H2_PFA; // Pulse Fit
  // a[2]=Oct_H2_TS3; //pre CM
  // a[3]=Oct_H6_TS3_CM; //post CM
  // a[4]=Oct_H6_PFA; // Pulse Fit
  // a[5]=Oct_H6_TS3; //pre CM
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
  mg->GetXaxis()->SetRangeUser(-10,1000);
  mg->GetXaxis()->SetTitle("ModuleMap + 4* Skiroc");
  mg->GetYaxis()->SetTitle("Conversion Factor (LG #rightarrow HG)");
  // mg->GetYaxis()->SetTitle("Transition Point (HG #rightarrow LG)");
  gPad->Update();
  gPad->SetGridx();
  gPad->SetGridy();

  gPad->SaveAs("Canvas.png");


  Canvas1->cd();
  mg1->Draw("AP");
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
  // legend->AddEntry("0","H2::TS3 post CM subtraction","ep");
  legend->AddEntry("1","H2::Pulse Fit Amplitude","ep");
  // legend->AddEntry("2","H2::TS3 pre CM subtraction","eP");
  // legend->AddEntry("3","H6::TS3 post CM subtraction","eP");
  legend->AddEntry("4","H6::Pulse Fit Amplitude","ep");
  // legend->AddEntry("5","H6::TS3 pre CM subtraction","ep");
  legend->SetTextFont(62);
  legend->Draw();

  // a[0]=Oct_H2_TS3_CM; //post CM
  // a[1]=Oct_H2_PFA; // Pulse Fit
  // a[2]=Oct_H2_TS3; //pre CM
  // a[3]=Oct_H6_TS3_CM; //post CM
  // a[4]=Oct_H6_PFA; // Pulse Fit
  // a[5]=Oct_H6_TS3; //pre CM
  gPad->Update();

  // mg->GetYaxis()->SetRangeUser(1000,3011);
  mg1->GetYaxis()->SetRangeUser(3,15);
  mg1->GetYaxis()->SetLabelFont(62);
  mg1->GetYaxis()->SetTitleSize(0.048);
  mg1->GetYaxis()->SetTitleFont(62);
  // mg->GetYaxis()->SetTitleOffset(1.5);

  mg1->GetXaxis()->SetLabelFont(62);
  mg1->GetXaxis()->SetTitleFont(62);
  mg1->GetXaxis()->SetTitleSize(0.048);
  // mg->GetXaxis()->SetRangeUser(-10,53);
  mg1->GetXaxis()->SetRangeUser(-10,1000);
  mg1->GetXaxis()->SetTitle("ModuleMap + 4* Skiroc");
  mg1->GetYaxis()->SetTitle("Conversion Factor (LG #rightarrow HG)");
  // mg->GetYaxis()->SetTitle("Transition Point (HG #rightarrow LG)");
  gPad->Update();
  gPad->SetGridx();
  gPad->SetGridy();

  gPad->SaveAs("Canvas1.png");


  Canvas2->cd();
  mg2->Draw("AP");
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
  // legend->AddEntry("0","H2::TS3 post CM subtraction","ep");
  // legend->AddEntry("1","H2::Pulse Fit Amplitude","ep");
  legend->AddEntry("2","H2::TS3 pre CM subtraction","eP");
  // legend->AddEntry("3","H6::TS3 post CM subtraction","eP");
  // legend->AddEntry("4","H6::Pulse Fit Amplitude","ep");
  legend->AddEntry("5","H6::TS3 pre CM subtraction","ep");
  legend->SetTextFont(62);
  legend->Draw();

  // a[0]=Oct_H2_TS3_CM; //post CM
  // a[1]=Oct_H2_PFA; // Pulse Fit
  // a[2]=Oct_H2_TS3; //pre CM
  // a[3]=Oct_H6_TS3_CM; //post CM
  // a[4]=Oct_H6_PFA; // Pulse Fit
  // a[5]=Oct_H6_TS3; //pre CM
  gPad->Update();

  // mg->GetYaxis()->SetRangeUser(1000,3011);
  mg2->GetYaxis()->SetRangeUser(3,15);
  mg2->GetYaxis()->SetLabelFont(62);
  mg2->GetYaxis()->SetTitleSize(0.048);
  mg2->GetYaxis()->SetTitleFont(62);
  // mg->GetYaxis()->SetTitleOffset(1.5);

  mg2->GetXaxis()->SetLabelFont(62);
  mg2->GetXaxis()->SetTitleFont(62);
  mg2->GetXaxis()->SetTitleSize(0.048);
  // mg->GetXaxis()->SetRangeUser(-10,53);
  mg2->GetXaxis()->SetRangeUser(-10,1000);
  mg2->GetXaxis()->SetTitle("ModuleMap + 4* Skiroc");
  mg2->GetYaxis()->SetTitle("Conversion Factor (LG #rightarrow HG)");
  // mg->GetYaxis()->SetTitle("Transition Point (HG #rightarrow LG)");
  gPad->Update();
  gPad->SetGridx();
  gPad->SetGridy();

  gPad->SaveAs("Canvas2.png");






  return;
}


#ifndef MAIN
#define MAIN
int main()
{
  plot_ModuleStability_CF();
}
#endif
