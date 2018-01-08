#include<iostream>
#include "SaturationFinder.h"



void run_me()
{

  // gROOT->SetBatch(kTRUE); //Not displaying anything

  // SaturationFinder* a = new SaturationFinder(17,0,"All","Oct_Run","/home/rsaradhy/Work/Output/TransitionH_L/New_Data/Oct_NTuple/"); // 0i mplies that it is a allfile...
  SaturationFinder* a = new SaturationFinder(20,0,"All","Oct_H6","/home/rsaradhy/Work/Output/TransitionH_L/New_Data/Oct_H6_NTuple/"); // 0implies that it is a allfile...

  std::ostringstream os( std::ostringstream::ate );


  // a->dataExtractor();
  // a->SaveHistogram("./temp_data/");
  // a->LoadHistogram("./temp_data/");
  // a->FitHistogram();
  // a->FindValues();
  // a->StoreValues("./temp_data/");
  a->RetrieveValues("./temp_data/");
  a->FixAllValues(1);
  // a->FixAllValues(0);

  std::cout<<a->CF[8][0][0]<<std::endl;
  a->StoreValues("./temp_data/Final_");

  // b->FitHistogram();
  // b->FindValues();
  // a->InitializeHist2D(0,1);
  // a->Hist2D[0][0][1]->Draw();
  // a->CutOff(2,2,1);
  // a->CutOff(2,2,0);
  // std::cout<<a->fitStatus[0][1][1]<<std::endl;
  // a->fitCanvas[0][1][1]->SaveAs("./temp.png");
  // a->fitCanvas[0][1][0]->SaveAs("./temp1.png");
  //
  // for(int i=0 ; i< 20 ; i++)
  // {
  //   for(int j =0; j<4 ;j++)
  //   {
  //       for(int type_num=1;type_num<2;type_num++)
  //       {
  //         if(a->fitStatus[i][j][type_num]==4000)
  //         {
  //           os.str("");
  //           os<<"./Graphs/LG_TOT/"<<a->fitCanvas[i][j][type_num]->GetName()<<".png";
  //           a->fitCanvas[i][j][type_num]->SaveAs(os.str().c_str());
  //         }
  //
  //         // if(a->fitStatus[i][j][type_num]==4000)
  //         // {
  //         //   os.str("");
  //         //   os<<"./Graphs/"<<a->fitCanvas[i][j][type_num]->GetName()<<".png";
  //         //   a->fitCanvas[i][j][type_num]->SaveAs(os.str().c_str());
  //         // }
  //
  //       }
  //   }
  //
  // }


  return;
}


#ifndef MAIN
#define MAIN
int main()
{
  run_me();
}
#endif
