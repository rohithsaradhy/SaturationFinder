#include "SaturationFinder.h"

void SaturationFinder::FixAllValues(int type_num)
{
  TH1F* CF_Hist;
  TH1F* CF_Intercept_Hist;
  TH1F* TP_Hist;

  int bin_CF;
  int bin_CF2;
  int min_CF;
  int max_CF;
  int bin_CF_Int;
  int bin_CF_Int2;
  int min_CF_Int;
  int max_CF_Int;
  int bin_TP;
  int bin_TP2;
  int min_TP;
  int max_TP;
  float CF_Threshold;
  float CF_Intercept_Threshold;
  float TP_Threshold;


  switch (type_num) {
    case 0:
     bin_CF = 20;
     bin_CF2 = 100;
     min_CF =6;
     max_CF =11;
     bin_CF_Int = 10;
     bin_CF_Int2 = 100;
     min_CF_Int =50;
     max_CF_Int =150;
     bin_TP = 20;
     bin_TP2 = 3000;
     min_TP =800;
     max_TP =3500;
     CF_Threshold =2;
     CF_Intercept_Threshold =1000;
     TP_Threshold=300;
    break;
    case 1:
     bin_CF = 20;
     bin_CF2 = 100;
     min_CF =1;
     max_CF =5;
     bin_CF_Int = 10;
     bin_CF_Int2 = 100;
     min_CF_Int =-400;
     max_CF_Int =400;
     bin_TP = 100;
     bin_TP2 = 3000;
     min_TP =400;
     max_TP =3500;
     CF_Threshold =2;
     CF_Intercept_Threshold = 1000;
     TP_Threshold=300;
    break;
  }
  CF_Hist = new TH1F("ConversionFact","ConversionFact",bin_CF,min_CF,max_CF);
  CF_Intercept_Hist = new TH1F("ConversionFact_Intercept","ConversionFact_Intercept",bin_CF_Int,min_CF_Int,max_CF_Int);
  TP_Hist = new TH1F("TransitionPoint","TransitionPoint",bin_TP,min_TP,max_TP);

  for(int board =0; board<BOARD;board++)
  {
    for(int skiroc=0; skiroc < 4; skiroc++)
    {

      if (CF[board][skiroc][type_num] > 0) CF_Hist->Fill(CF[board][skiroc][type_num]);
      if(CF_Intercept[board][skiroc][type_num] >0) CF_Intercept_Hist->Fill(CF_Intercept[board][skiroc][type_num]);
      if (TP[board][skiroc][type_num] > 0) TP_Hist->Fill(TP[board][skiroc][type_num]);
    }
  }


  // CF_Hist->Draw();
  // CF_Intercept_Hist->Draw();
  // TP_Hist->Draw();

  float ModeValueCF = CF_Hist->GetBinLowEdge(CF_Hist->GetMaximumBin());
  float ModeValueCF_Intercept = CF_Intercept_Hist->GetBinLowEdge(CF_Intercept_Hist->GetMaximumBin());
  float ModeValueTP = TP_Hist->GetBinLowEdge(TP_Hist->GetMaximumBin());



  delete CF_Hist;
  delete CF_Intercept_Hist;
  delete TP_Hist;


  CF_Hist = new TH1F("ConversionFact","ConversionFact",bin_CF2,min_CF,max_CF);
  CF_Intercept_Hist = new TH1F("ConversionFact_Intercept","ConversionFact_Intercept",bin_CF_Int2,min_CF_Int,max_CF_Int);
  TP_Hist = new TH1F("TransitionPoint","TransitionPoint",bin_TP2,min_TP,max_TP);


  for(int board =0; board<BOARD;board++)
  {
    for(int skiroc=0; skiroc < 4; skiroc++)
    {
      if(fabs(CF[board][skiroc][type_num] - ModeValueCF) <= CF_Threshold)
      {
        CF_Hist->Fill(CF[board][skiroc][type_num]);
      }

      if(fabs(CF_Intercept[board][skiroc][type_num] - ModeValueCF_Intercept) <= CF_Intercept_Threshold)
      {
        CF_Intercept_Hist->Fill(CF_Intercept[board][skiroc][type_num]);
      }


      if(fabs(TP[board][skiroc][type_num] - ModeValueTP) <= TP_Threshold)
      {
        TP_Hist->Fill(TP[board][skiroc][type_num]);
      }
    }
  }

  // CF_Hist->Draw();
  // CF_Intercept_Hist->Draw();
  // TP_Hist->Draw();


  float Mean_CF=CF_Hist->GetMean(),
  RMS_CF=CF_Hist->GetMeanError(),
  Mean_CF_Intercept = CF_Intercept_Hist->GetMean(),
  RMS_CF_Intercept = CF_Intercept_Hist->GetMeanError(),
  Mean_TP=TP_Hist->GetMean(),
  RMS_TP=TP_Hist->GetMeanError();

  std::cout<<Mean_CF<<"\t"<<Mean_CF_Intercept<<"\t"<<Mean_TP<<std::endl;
  // std::cout<<RMS_CF<<"\t"<<RMS_CF_Intercept<<"\t"<<RMS_TP<<std::endl;

  int touch;

  for(int board =0; board<BOARD;board++)
  {
    for(int skiroc=0; skiroc < 4; skiroc++)
    {
      touch =0; // reset every cycle
      if (fabs(CF[board][skiroc][type_num] - ModeValueCF) >= CF_Threshold)
      {
        touch =1;
        CF[board][skiroc][type_num] =Mean_CF;
        CF_Err[board][skiroc][type_num] =RMS_CF;
      }


      if (fabs(CF_Intercept[board][skiroc][type_num] - ModeValueCF_Intercept) >= CF_Intercept_Threshold)
      {
        touch=+2;
        CF_Intercept[board][skiroc][type_num] =Mean_CF_Intercept;
        CF_Intercept_Err[board][skiroc][type_num] =RMS_CF_Intercept;
      }


      if (fabs(TP[board][skiroc][type_num] - ModeValueTP) >= TP_Threshold)
      {
        touch=+4;
        TP[board][skiroc][type_num] =Mean_TP;
        TP_Err[board][skiroc][type_num] =RMS_TP;
      }

      Touched[board][skiroc][type_num] = touch;
   }



  }












}
