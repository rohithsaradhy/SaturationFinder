// File to analyse pion data.
#include<iostream>
#include<string>
#include "SaturationFinder.h"
using namespace std;

void Electron()
{
  std::string run_type = "Electron";
  std::ostringstream os( std::ostringstream::ate );
  gROOT->SetBatch(kTRUE); //Not displaying anything




    // const int BOARD =17;
    // const int Number_Energy =5;
    // float StaggeringFactor=2;
    // std::string Analysis_ID = "April_24";
    // SaturationFinder* EnergyData[Number_Energy];
    // float Energy[Number_Energy]={20,32,50,80,90};
    // string Fit_Name[3]  = {"Oct_H2_TS3","Oct_H2_TS3_CM","Oct_H2_PFA"};
    // std::string dataFolder = "/home/rsaradhy/Work/Output/TransitionH_L/Data/data_27_3_2018/H2/";
    //

    const int BOARD =20;
    const int Number_Energy =4;
    float StaggeringFactor=2;
    std::string Analysis_ID = "April_24";
    SaturationFinder* EnergyData[Number_Energy];
    float Energy[Number_Energy]={20,32,50,80};
    string Fit_Name[3]  = {"Oct_H6_TS3","Oct_H6_TS3_CM","Oct_H6_PFA"};
    std::string dataFolder = "/home/rsaradhy/Work/Output/TransitionH_L/Data/data_27_3_2018/H6/";




  for (int iter = 0; iter <3 ; iter++) //running through different
  {




  for(int i=0;i<Number_Energy;i++)
  {
    EnergyData[i] = new SaturationFinder(BOARD,Energy[i],run_type,Analysis_ID,Fit_Name[iter],dataFolder); // 0i mplies that it is a allfile...
    EnergyData[i]->CreateStructure("./Analysed_data");
  }



  // //Extracting all the data and saving it in
  bool enableDataExtraction =1;
  if(enableDataExtraction)
  {
    for(int i=0;i<Number_Energy;i++)
    {
      EnergyData[i]->dataExtractor(iter); //Available Options are :: 0->TS3  1->TS3withCM   2->PFA
      EnergyData[i]->SaveHistogram();
    }
  }

  //Loading all the data
  bool enableFindValues =1;
  for(int i=0;i<Number_Energy;i++)
  {

    if(enableFindValues)
    {
      if(!enableDataExtraction) EnergyData[i]->LoadHistogram();
      EnergyData[i]->FitHistogram();
      EnergyData[i]->FindValues();
      EnergyData[i]->StoreValues(""); //Store those values with a name prefix given as the argument

    }
    else
    {
      EnergyData[i]->RetrieveValues("");  //Store those values with a name prefix given as the argument
    }

  }

    std::map<int,Color_t> skiColor = {
        {0,kRed},
        {1,kBlue},
        {2,kGreen},
        {3,kBlack}
    };

    //For ConverstionFactor
    TCanvas* CF_Canvas[BOARD][2];
    TGraphErrors* CF_Graph[BOARD][4][2]; // Board Skiroc Type
    TMultiGraph* CF_MG[BOARD][2];
    float CF[Number_Energy],CF_Err[Number_Energy],CF_Energy[Number_Energy];
    for(int type_num=0; type_num<2; type_num++)
    {

        for(int board=0; board<BOARD; board++)
        {
            os.str("");
            //Settings for LG and HG
            switch(type_num)
            {
            case 0:
                os<<"HGtoLG_CF_Brd_"<<board<<"_"<<run_type;
                break;
            case 1:
                os<<"LGtoTOT_CF_Brd_"<<board<<"_"<<run_type;
                break;
            }

            // cout<<os.str()<<endl;
            CF_Canvas[board][type_num] = new TCanvas(os.str().c_str(),os.str().c_str(),1366,768);
            CF_Canvas[board][type_num]->cd();
            CF_MG[board][type_num] = new TMultiGraph();

            for(int skiroc=0; skiroc<4; skiroc++)
            {
                for(int energy=0; energy<Number_Energy; energy++)
                {
                    CF[energy] = EnergyData[energy]->CF[board][skiroc][type_num];
                    CF_Energy[energy] = Energy[energy] + StaggeringFactor*(skiroc-1.5);
                    CF_Err[energy] = EnergyData[energy]->CF_Err[board][skiroc][type_num];
                }
                CF_Graph[board][skiroc][type_num] = new TGraphErrors(Number_Energy,CF_Energy,CF,0,CF_Err);
                os.str("");
                os<<"Skiroc"<<skiroc;
                CF_Graph[board][skiroc][type_num]->SetName(os.str().c_str());
                CF_Graph[board][skiroc][type_num]->SetTitle("");
                CF_Graph[board][skiroc][type_num]->SetMarkerStyle(20);
                CF_Graph[board][skiroc][type_num]->SetMarkerSize(2);
                CF_Graph[board][skiroc][type_num]->SetMarkerColor(skiColor[skiroc]);
                CF_Graph[board][skiroc][type_num]->SetLineWidth(2);

                CF_MG[board][type_num]->Add(CF_Graph[board][skiroc][type_num]);
            }

            CF_MG[board][type_num]->Draw("AP");

            switch (type_num)
            {

                TLegend* legend ;
                TLatex* tex ;
                TPaveText* label2;
                TPaveText* label1;
            case 0:
                CF_MG[board][type_num]->GetXaxis()->SetTitle("Energy(GeV)");
                CF_MG[board][type_num]->GetYaxis()->SetTitle("Conversion Factor (LG #rightarrow HG)");

                CF_MG[board][type_num]->GetYaxis()->SetLabelFont(62);
                CF_MG[board][type_num]->GetYaxis()->SetTitleSize(0.048);
                CF_MG[board][type_num]->GetYaxis()->SetTitleFont(62);
                // CF_MG[board][type_num]->GetYaxis()->SetTitleOffset(1.5);

                CF_MG[board][type_num]->GetXaxis()->SetLabelFont(62);
                CF_MG[board][type_num]->GetXaxis()->SetTitleFont(62);
                CF_MG[board][type_num]->GetXaxis()->SetTitleSize(0.048);
                // CF_MG[board][type_num]->GetXaxis()->SetTitleOffset(1.5);
                CF_MG[board][type_num]->GetYaxis()->SetRangeUser(0,18);


                legend = new TLegend(0.1391753,0.6351931,0.3004418,0.8927039,NULL,"brNDC");
                os.str("");
                os<<"Board "<<board;
                legend->SetHeader(os.str().c_str());
                legend->AddEntry("Skiroc0","Skiroc 0","lep");
                legend->AddEntry("Skiroc1","Skiroc 1","lep");
                legend->AddEntry("Skiroc2","Skiroc 2","lep");
                legend->AddEntry("Skiroc3","Skiroc 3","lep");
                legend->SetTextFont(62);
                legend->Draw();
                //Setting the Labels and texts

                tex = new TLatex(20.6221,2,"Results at the same energy are staggered");
                tex->SetLineWidth(2);
                tex->Draw();

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

                break;

            case 1:
                CF_MG[board][type_num]->GetXaxis()->SetTitle("Energy(GeV)");
                CF_MG[board][type_num]->GetYaxis()->SetTitle("Conversion Factor (TOTSlow #rightarrow LG)");


                CF_MG[board][type_num]->GetYaxis()->SetLabelFont(62);
                CF_MG[board][type_num]->GetYaxis()->SetTitleSize(0.048);
                CF_MG[board][type_num]->GetYaxis()->SetTitleFont(62);
                // CF_MG[board][type_num]->GetYaxis()->SetTitleOffset(1.5);

                CF_MG[board][type_num]->GetXaxis()->SetLabelFont(62);
                CF_MG[board][type_num]->GetXaxis()->SetTitleFont(62);
                CF_MG[board][type_num]->GetXaxis()->SetTitleSize(0.048);
                // CF_MG[board][type_num]->GetXaxis()->SetTitleOffset(1.5);
                CF_MG[board][type_num]->GetYaxis()->SetRangeUser(0,8);


                legend = new TLegend(0.1391753,0.6351931,0.3004418,0.8927039,NULL,"brNDC");
                os.str("");
                os<<"Board "<<board;
                legend->SetHeader(os.str().c_str());
                legend->AddEntry("Skiroc0","Skiroc 0","lep");
                legend->AddEntry("Skiroc1","Skiroc 1","lep");
                legend->AddEntry("Skiroc2","Skiroc 2","lep");
                legend->AddEntry("Skiroc3","Skiroc 3","lep");
                legend->SetTextFont(62);
                legend->Draw();
                //Setting the Labels and texts

                tex = new TLatex(20.6221,1,"Results at the same energy are staggered");
                tex->SetLineWidth(2);
                tex->Draw();

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

                break;

            }

            gPad->SetGridx();
            gPad->SetGridy();

            gPad->Update();

        }
    }




    //For Transition Point...
    TCanvas* TP_Canvas[BOARD][2];
    TGraphErrors* TP_Graph[BOARD][4][2]; // Board Skiroc Type
    TMultiGraph* TP_MG[BOARD][2];
    float TP[Number_Energy],TP_Err[Number_Energy],TP_Energy[Number_Energy];
    for(int type_num=0; type_num<2; type_num++)
    {

        for(int board=0; board<BOARD; board++)
        {
            os.str("");
            //Settings for LG and HG
            switch(type_num)
            {
            case 0:
                os<<"HGtoLG_TP_Brd_"<<board<<"_"<<run_type;
                break;
            case 1:
                os<<"LGtoTOT_TP_Brd_"<<board<<"_"<<run_type;
                break;
            }

            // cout<<os.str()<<endl;
            TP_Canvas[board][type_num] = new TCanvas(os.str().c_str(),os.str().c_str(),1366,768);
            TP_Canvas[board][type_num]->cd();
            TP_MG[board][type_num] = new TMultiGraph();

            for(int skiroc=0; skiroc<4; skiroc++)
            {
                for(int energy=0; energy<Number_Energy; energy++)
                {
                    TP[energy] = EnergyData[energy]->TP[board][skiroc][type_num];
                    TP_Energy[energy] = Energy[energy] + StaggeringFactor*(skiroc-1.5);
                    TP_Err[energy] = EnergyData[energy]->TP_Err[board][skiroc][type_num];
                }
                TP_Graph[board][skiroc][type_num] = new TGraphErrors(Number_Energy,TP_Energy,TP,0,TP_Err);
                os.str("");
                os<<"Skiroc"<<skiroc;
                TP_Graph[board][skiroc][type_num]->SetName(os.str().c_str());
                TP_Graph[board][skiroc][type_num]->SetTitle("");
                TP_Graph[board][skiroc][type_num]->SetMarkerStyle(20);
                TP_Graph[board][skiroc][type_num]->SetMarkerSize(2);
                TP_Graph[board][skiroc][type_num]->SetMarkerColor(skiColor[skiroc]);
                TP_Graph[board][skiroc][type_num]->SetLineWidth(2);

                TP_MG[board][type_num]->Add(TP_Graph[board][skiroc][type_num]);
            }

            TP_MG[board][type_num]->Draw("AP");

            switch (type_num)
            {

                TLegend* legend ;
                TLatex* tex ;
                TPaveText* label2;
                TPaveText* label1;
            case 0:
                TP_MG[board][type_num]->GetXaxis()->SetTitle("Energy(GeV)");
                TP_MG[board][type_num]->GetYaxis()->SetTitle("Transition Point (HG #rightarrow LG)");

                TP_MG[board][type_num]->GetYaxis()->SetLabelFont(62);
                TP_MG[board][type_num]->GetYaxis()->SetTitleSize(0.048);
                TP_MG[board][type_num]->GetYaxis()->SetTitleFont(62);
                // TP_MG[board][type_num]->GetYaxis()->SetTitleOffset(1.5);

                TP_MG[board][type_num]->GetXaxis()->SetLabelFont(62);
                TP_MG[board][type_num]->GetXaxis()->SetTitleFont(62);
                TP_MG[board][type_num]->GetXaxis()->SetTitleSize(0.048);
                // TP_MG[board][type_num]->GetXaxis()->SetTitleOffset(1.5);
                TP_MG[board][type_num]->GetYaxis()->SetRangeUser(0,4000);


                legend = new TLegend(0.1391753,0.6351931,0.3004418,0.8927039,NULL,"brNDC");
                os.str("");
                os<<"Board "<<board;
                legend->SetHeader(os.str().c_str());
                legend->AddEntry("Skiroc0","Skiroc 0","lep");
                legend->AddEntry("Skiroc1","Skiroc 1","lep");
                legend->AddEntry("Skiroc2","Skiroc 2","lep");
                legend->AddEntry("Skiroc3","Skiroc 3","lep");
                legend->SetTextFont(62);
                legend->Draw();
                //Setting the Labels and texts

                tex = new TLatex(20.5683,500.43,"Results at the same energy are staggered");
                tex->SetLineWidth(2);
                tex->Draw();

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

                break;

            case 1:
                TP_MG[board][type_num]->GetXaxis()->SetTitle("Energy(GeV)");
                TP_MG[board][type_num]->GetYaxis()->SetTitle("Transition Point (LG #rightarrow TOTSlow)");


                TP_MG[board][type_num]->GetYaxis()->SetLabelFont(62);
                TP_MG[board][type_num]->GetYaxis()->SetTitleSize(0.048);
                TP_MG[board][type_num]->GetYaxis()->SetTitleFont(62);
                // TP_MG[board][type_num]->GetYaxis()->SetTitleOffset(1.5);

                TP_MG[board][type_num]->GetXaxis()->SetLabelFont(62);
                TP_MG[board][type_num]->GetXaxis()->SetTitleFont(62);
                TP_MG[board][type_num]->GetXaxis()->SetTitleSize(0.048);
                // TP_MG[board][type_num]->GetXaxis()->SetTitleOffset(1.5);
                TP_MG[board][type_num]->GetYaxis()->SetRangeUser(700,2400);


                legend = new TLegend(0.7172312,0.1630901,0.8807069,0.4792561,NULL,"brNDC");
                os.str("");
                os<<"Board "<<board;
                legend->SetHeader(os.str().c_str());
                legend->AddEntry("Skiroc0","Skiroc 0","lep");
                legend->AddEntry("Skiroc1","Skiroc 1","lep");
                legend->AddEntry("Skiroc2","Skiroc 2","lep");
                legend->AddEntry("Skiroc3","Skiroc 3","lep");
                legend->SetTextFont(62);
                legend->Draw();
                //Setting the Labels and texts

                tex = new TLatex(20.5683,1000.43,"Results at the same energy are staggered");
                tex->SetLineWidth(2);
                tex->Draw();

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

                break;

            }

            gPad->SetGridx();
            gPad->SetGridy();

            gPad->Update();

        }
    }




    std::string type[2]={"HG_LG","LG_TOT"};

      //Saving the Analysed Plots
      for(int type_num=0;type_num<2;type_num++)
      {
        for(int board=0;board<BOARD;board++)
        {
          os.str("");
          os<<EnergyData[0]->rootFolder<<"../Stability/"<<type[type_num]<<"/"<<Fit_Name[iter]<<"_"<<TP_Canvas[board][type_num]->GetName()<<".png";
          TP_Canvas[board][type_num]->SaveAs(os.str().c_str());
          os.str("");
          os<<EnergyData[0]->rootFolder<<"../Stability/"<<type[type_num]<<"/"<<Fit_Name[iter]<<"_"<<CF_Canvas[board][type_num]->GetName()<<".png";
          CF_Canvas[board][type_num]->SaveAs(os.str().c_str());

        }

      }



    // Saving the fit Plots... Not FIt and Find Values should be uncommented above...
    // Saving the fit Plots... Not FIt and Find Values should be uncommented above...
    if(enableFindValues)
    {
      SaturationFinder* a;
        for(int energyNum=0; energyNum<Number_Energy; energyNum++)
        {
          a = EnergyData[energyNum];
            for(int board=0; board<BOARD; board++)
            {
                for(int skiroc=0; skiroc<4; skiroc++)
                {
                    for(int type_num=0; type_num<2; type_num++)
                    {
                      if(a->fitStatus[board][skiroc][type_num]==99999)
                      {

                          os.str("");
                          if(type_num ==0 )os<<a->rootFolder<<"HG_LG/";
                          else os<<a->rootFolder<<"LG_TOT/";


                          os<<a->fitCanvas[board][skiroc][type_num]->GetName()<<".png";
                          a->fitCanvas[board][skiroc][type_num]->SaveAs(os.str().c_str());


                      }
                    }

                }

            }
        }
     }




}
}
