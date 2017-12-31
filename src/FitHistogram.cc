//Fits the Histogram from the ProfileX and then store it is FitResultPtr[][][]

#include "SaturationFinder.h"


float X[10000],Y[10000],errorY[10000],errorX[10000];
float ErrorInY_ADC;
Int_t startBin,endBin,countMe;
TGraphErrors* grph ;
TF1* flo = new TF1("flo","[0]*x+[1]"); //Setting straight line fit for Lower region
float FitRangeMax[2],FitRangeMin[2];


void SaturationFinder::FitHistogram()
{
  // gROOT->SetBatch(kTRUE); //Not displaying anything

  FitRangeMin[0] = 75;
  FitRangeMax[0] = 180;
  FitRangeMin[1] = 250;
  FitRangeMax[1] = 400;

  Int_t Hist_Entries(0);

  std::ostringstream os( std::ostringstream::ate );


  //For HighGain to LowGain
  int type_num =0; //for H_L
  std::string type = "HighGaintoLowGain";
  for(int board = 0;board<BOARD;board++)
  {
    for(int skiroc = 0 ;skiroc<4;skiroc++)
    {

      //Selections...
      if(board != 1) continue;
      if(skiroc != 2) continue;


      // Making sure that histogram has enough entries to be used in the fit...
      Hist_Entries = Hist2D[board][skiroc][type_num]->GetEntries();
      if(Hist_Entries < 100)
      {
        os.str("");
        os<<FIT_NAME<<"_Energy_"<<ENERGY<<"_Board_"<<board<<"_Skiroc_"<<skiroc<<"_"<<type;
        std::cout<<os.str()<<std::endl<<"Skippped due to low stats ..."<<std::endl;
        continue;
      }

      os.str("");
      os<<FIT_NAME<<"_Energy_"<<ENERGY<<"_Board_"<<board<<"_Skiroc_"<<skiroc<<"_"<<type;
      // Initialising the Canvas...
      fitCanvas[board][skiroc][type_num] = new TCanvas(os.str().c_str(),os.str().c_str(),1366,768);
      // Taking the 2D profile...
      HistProfile[board][skiroc][type_num] = ((TH2F*) Hist2D[board][skiroc][type_num])->ProfileX();

      endBin=HistProfile[board][skiroc][type_num]->FindLastBinAbove(1,1); //(contentThreshold,axis#) x=1;y=2;z=3
      startBin =HistProfile[board][skiroc][type_num]->FindFirstBinAbove(1,1);//(contentThreshold,axis#) x=1;y=2;z=3

      // cout<<"Start and End Bin :: "<<startBin<<"\t"<<endBin<<endl;
      // continue;
      ErrorInY_ADC = 0;
      countMe=0;
      for(int i= startBin;i<=endBin;i++)
      {
        if(HistProfile[board][skiroc][type_num]->GetBinContent(i)<10) continue;
        if(HistProfile[board][skiroc][type_num]->GetBinCenter(i)>1000) break;
        countMe++;
        X[i] = HistProfile[board][skiroc][type_num]->GetBinCenter(i);
        errorY[i] = sqrt(pow(HistProfile[board][skiroc][type_num]->GetBinError(i),2) + pow(ErrorInY_ADC,2));
        // errorY[i] = sqrt(pow(HistProfile[board][skiroc][type_num]->GetBinError(i),2));

        // cout<<errorY[i]<<endl;
        errorX[i] = 5;
        Y[i] = HistProfile[board][skiroc][type_num]->GetBinContent(i);
        // cout<<X[i]<<"\t"<<Y[i]<<endl;
      }



      grph = new TGraphErrors(countMe,X,Y,errorX,errorY);
      FitResultPtr[board][skiroc][type_num]= grph->Fit("flo","QSNEM","",FitRangeMin[type_num],FitRangeMax[type_num]); //E and M added for better error estimation and fitting....

    }
  }



  //For Low to TOT
  int type_num =1; //for H_L
  std::string type = "LowGaintoTOTSLow";
  for(int board = 0;board<BOARD;board++)
  {
    for(int skiroc = 0 ;skiroc<4;skiroc++)
    {

      if(board != 1) continue;
      if(skiroc != 2) continue;


      // Making sure that histogram has enough entries to be used in the fit...
      Hist_Entries = Hist2D[board][skiroc][type_num]->GetEntries();
      if(Hist_Entries < 100)
      {
        os.str("");
        os<<FIT_NAME<<"_Energy_"<<ENERGY<<"_Board_"<<board<<"_Skiroc_"<<skiroc<<"_"<<type;
        std::cout<<os.str()<<std::endl<<"Skippped due to low stats ..."<<std::endl;
        continue;
      }

      os.str("");
      os<<FIT_NAME<<"_Energy_"<<ENERGY<<"_Board_"<<board<<"_Skiroc_"<<skiroc<<"_"<<type;
      // Initialising the Canvas...
      fitCanvas[board][skiroc][type_num] = new TCanvas(os.str().c_str(),os.str().c_str(),1366,768);
      // Taking the 2D profile...
      HistProfile[board][skiroc][type_num] = ((TH2F*) Hist2D[board][skiroc][type_num])->ProfileX();

      endBin=HistProfile[board][skiroc][type_num]->FindLastBinAbove(1,1); //(contentThreshold,axis#) x=1;y=2;z=3
      startBin =HistProfile[board][skiroc][type_num]->FindFirstBinAbove(1,1);//(contentThreshold,axis#) x=1;y=2;z=3

      // cout<<"Start and End Bin :: "<<startBin<<"\t"<<endBin<<endl;
      // continue;
      ErrorInY_ADC = 0;
      countMe=0;
      for(int i= startBin;i<=endBin;i++)
      {
        if(HistProfile[board][skiroc][type_num]->GetBinContent(i)<10) continue;
        if(HistProfile[board][skiroc][type_num]->GetBinCenter(i)>1000) break;
        countMe++;
        X[i] = HistProfile[board][skiroc][type_num]->GetBinCenter(i);
        errorY[i] = sqrt(pow(HistProfile[board][skiroc][type_num]->GetBinError(i),2) + pow(ErrorInY_ADC,2));
        // errorY[i] = sqrt(pow(HistProfile[board][skiroc][type_num]->GetBinError(i),2));

        // cout<<errorY[i]<<endl;
        errorX[i] = 5;
        Y[i] = HistProfile[board][skiroc][type_num]->GetBinContent(i);
        // cout<<X[i]<<"\t"<<Y[i]<<endl;
      }



      grph = new TGraphErrors(countMe,X,Y,errorX,errorY);
      FitResultPtr[board][skiroc][type_num]= grph->Fit("flo","QSNEM","",FitRangeMin[type_num],FitRangeMax[type_num]); //E and M added for better error estimation and fitting....

    }
  }



}
