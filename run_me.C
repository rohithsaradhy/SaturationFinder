#include<iostream>
#include "SaturationFinder.h"



void run_me()
{


  // SaturationFinder* a = new SaturationFinder(17,0,"All","Oct_H2_test_TS3","/home/rsaradhy/Work/Output/TransitionH_L/New_Data/Oct_NTuple/"); // 0i mplies that it is a allfile...
  // SaturationFinder* a = new SaturationFinder(17,0,"All","Oct_H2_test","/home/rsaradhy/Work/Output/TransitionH_L/New_Data/Oct_NTuple/"); // 0i mplies that it is a allfile...
  // SaturationFinder* a = new SaturationFinder(17,0,"All_Pion","Oct_H2_test_Pion","/home/rsaradhy/Work/Output/TransitionH_L/New_Data/Oct_NTuple/"); // 0i mplies that it is a allfile...
  SaturationFinder* a = new SaturationFinder(17,0,"All_Electron","Oct_H2_test_Electron","/home/rsaradhy/Work/Output/TransitionH_L/New_Data/Oct_NTuple/"); // 0i mplies that it is a allfile...
  // SaturationFinder* a = new SaturationFinder(17,0,"All_Electron","Oct_H2_test_Electron","/home/rsaradhy/Work/Output/TransitionH_L/New_Data/Oct_NTuple/"); // 0i mplies that it is a allfile...
  // SaturationFinder* a = new SaturationFinder(20,0,"All","Oct_H6","/home/rsaradhy/Work/Output/TransitionH_L/New_Data/Oct_H6_NTuple/"); // 0implies that it is a allfile...

  std::ostringstream os( std::ostringstream::ate );

  gROOT->SetBatch(kTRUE); //Not displaying anything
  //
  // a->InitializeHist2D(2,1);
  a->dataExtractor();
  // a->SaveHistogram("./temp_data/");
  // a->Hist2D[1][2][0]->Draw();
  // a->Hist2D[1][2][1]->Draw();
  // a->LoadHistogram("./temp_data/");


  a->FitHistogram();
  a->FindValues();


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
  for(int i=0 ; i< 20 ; i++)
  {
    for(int j =0; j<4 ;j++)
    {
        for(int type_num=0;type_num<2;type_num++)
        {
          if(a->fitStatus[i][j][type_num]==99999) // Checking whether the fit was possible with enought events...

          {
            os.str("");
            if(type_num ==0 )os<<"./Graphs/HG_LG/"<<a->fitCanvas[i][j][type_num]->GetName()<<".png";
            else os<<"./Graphs/LG_TOT/"<<a->fitCanvas[i][j][type_num]->GetName()<<".png";
            a->fitCanvas[i][j][type_num]->SaveAs(os.str().c_str());
            // a->fitCanvas[i][j][0]->SaveAs(os.str().c_str());
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
