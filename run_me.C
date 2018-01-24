#include<iostream>
#include "SaturationFinder.h"



void run_me()
{
  SaturationFinder* Oct_H6 = new SaturationFinder(20,0,"All","Oct_H6","/home/rsaradhy/Work/Output/TransitionH_L/New_Data/Oct_H6_NTuple/"); // 0implies that it is a allfile...
  SaturationFinder* Oct_H2 = new SaturationFinder(17,0,"All","Oct_H2","/home/rsaradhy/Work/Output/TransitionH_L/New_Data/Oct_NTuple/"); // 0i mplies that it is a allfile...

  SaturationFinder* Oct_H2_TS3 = new SaturationFinder(17,0,"All","Oct_H2_TS3","/home/rsaradhy/Work/Output/TransitionH_L/New_Data/Oct_NTuple/"); // 0i mplies that it is a allfile...
  SaturationFinder* Oct_H6_TS3 = new SaturationFinder(20,0,"All","Oct_H6_TS3","/home/rsaradhy/Work/Output/TransitionH_L/New_Data/Oct_H6_NTuple/"); // 0implies that it is a allfile...


  std::ostringstream os( std::ostringstream::ate );
  gROOT->SetBatch(kTRUE); //Not displaying anything
  bool enableDataExtraction =1;
  // Oct_H2->dataExtractor();
  // TCanvas* c1 = new TCanvas("Checking Stuff","Checking Stuff",1366,768);
  // Oct_H2->Hist2D[12][0][0]->Draw();

  bool Fill_Type = 0;//1-> PS and 0-> TS3
  if(true) // All the stuff...
  {
    if(Fill_Type)
    {
      if(enableDataExtraction)
      {
        Oct_H2->dataExtractor();
        Oct_H2->SaveHistogram("./temp_data/");
        Oct_H6->dataExtractor();
        Oct_H6->SaveHistogram("./temp_data/");
      }
      else
      {
        Oct_H2->LoadHistogram("./temp_data/");
        Oct_H6->LoadHistogram("./temp_data/");
      }

        Oct_H2->FitHistogram();
        Oct_H2->FindValues();
        Oct_H2->StoreValues("./temp_data/");
        Oct_H2->RetrieveValues("./temp_data/");

        Oct_H6->FitHistogram();
        Oct_H6->FindValues();
        Oct_H6->StoreValues("./temp_data/");
        Oct_H6->RetrieveValues("./temp_data/");
    }
    else
    {
      if(enableDataExtraction)
      {
        Oct_H2_TS3->dataExtractor();
        Oct_H2_TS3->SaveHistogram("./temp_data/");
        Oct_H6_TS3->dataExtractor();
        Oct_H6_TS3->SaveHistogram("./temp_data/");
      }
      else
      {
        Oct_H2_TS3->LoadHistogram("./temp_data/");
        Oct_H6_TS3->LoadHistogram("./temp_data/");
      }

      Oct_H2_TS3->FitHistogram();
      Oct_H2_TS3->FindValues();
      Oct_H2_TS3->StoreValues("./temp_data/");
      Oct_H2_TS3->RetrieveValues("./temp_data/");

      Oct_H6_TS3->FitHistogram();
      Oct_H6_TS3->FindValues();
      Oct_H6_TS3->StoreValues("./temp_data/");
      Oct_H6_TS3->RetrieveValues("./temp_data/");
    }



  SaturationFinder* a[4] = {Oct_H2,Oct_H6,Oct_H2_TS3,Oct_H6_TS3};
  for(int i=0 ; i< 20 ; i++)
  {
    for(int j =0; j<4 ;j++)
    {
        for(int type_num=0;type_num<2;type_num++)
        {
          for(int k=0;k<4;k++)
          {
            if(a[k]->fitStatus[i][j][type_num]==99999 )
            {
              os.str("");
              if(type_num ==0 )
              {
                os<<"./Graphs/"<<a[k]->FIT_NAME<<"/HG_LG/"<<a[k]->fitCanvas[i][j][type_num]->GetName()<<".png";
              }
              else
              {
                os<<"./Graphs/"<<a[k]->FIT_NAME<<"/LG_TOT/"<<a[k]->fitCanvas[i][j][type_num]->GetName()<<".png";
              }
              a[k]->fitCanvas[i][j][type_num]->SaveAs(os.str().c_str());
            }
          }

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
