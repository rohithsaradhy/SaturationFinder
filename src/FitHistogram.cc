//Fits the Histogram from the ProfileX and then store it is FitResultPtr[][][]

#include "SaturationFinder.h"




Int_t startBin,endBin,countMe;
TGraphErrors* Graph;
TF1* flo = new TF1("flo","[0]*x+[1]"); //Setting straight line fit for Lower region
int type_num;
std::string type;




void SaturationFinder::FitHistogram()
{

  std::ostringstream os( std::ostringstream::ate );

  FitRangeMin[0] = 75;
  FitRangeMax[0] = 180;
  FitRangeMin[1] = 280;
  FitRangeMax[1] = 400;

  Int_t Hist_Entries(0);

  //For HighGain to LowGain
  type_num =0; //for H_L
  type = "HighGaintoLowGain";
  for(int board = 0;board<BOARD;board++)
  {
    for(int skiroc = 0 ;skiroc<4;skiroc++)
    {

      //FINDME...
      // if(board != 2) continue;
      // if(skiroc != 2) continue;


      // Making sure that histogram has enough entries to be used in the fit...
      Hist_Entries = Hist2D[board][skiroc][type_num]->GetEntries();
      if(Hist_Entries < 100)
      {
        os.str("");
        os<<FIT_NAME<<"_Energy_"<<ENERGY<<"_Board_"<<board<<"_Skiroc_"<<skiroc<<"_"<<type;
        std::cout<<os.str()<<std::endl<<"Skippped due to low stats ..."<<std::endl;
        continue;
      }

      // Taking the 2D profile...
      HistProfile[board][skiroc][type_num] = ((TH2F*) Hist2D[board][skiroc][type_num])->ProfileX();

      endBin=HistProfile[board][skiroc][type_num]->FindLastBinAbove(1,1); //(contentThreshold,axis#) x=1;y=2;z=3
      startBin =HistProfile[board][skiroc][type_num]->FindFirstBinAbove(1,1);//(contentThreshold,axis#) x=1;y=2;z=3

      // cout<<"Start and End Bin :: "<<startBin<<"\t"<<endBin<<endl;
      // continue;
      ErrorInY_ADC = 0;

      ErrorInX_ADC = 5;

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
        errorX[i] = ErrorInX_ADC;
        Y[i] = HistProfile[board][skiroc][type_num]->GetBinContent(i);
        // cout<<X[i]<<"\t"<<Y[i]<<endl;
      }



      Graph = new TGraphErrors(countMe,X,Y,errorX,errorY);
      FitResultPtr[board][skiroc][type_num]= Graph->Fit("flo","QSNEM","",FitRangeMin[type_num],FitRangeMax[type_num]); //E and M added for better error estimation and fitting....
      fitStatus[board][skiroc][type_num] = Graph->Fit("flo","QSNEM","",FitRangeMin[type_num],FitRangeMax[type_num]); // Fitting Status
      FitResultPtr[board][skiroc][type_num]= Graph->Fit("flo","QSNEM","",FitRangeMin[type_num],FitRangeMax[type_num]); //E and M added for better error estimation and fitting....

    }
  }



  //For Low to TOT
  type_num =1; //for H_L
  type = "LowGaintoTOTSLow";
  for(int board = 0;board<BOARD;board++)
  {
    for(int skiroc = 0 ;skiroc<4;skiroc++)
    {
      // FINDME
      // if(board !=2) continue;
      // if(skiroc != 2) continue;


      // Making sure that histogram has enough entries to be used in the fit...
      Hist_Entries = Hist2D[board][skiroc][type_num]->GetEntries();
      if(Hist_Entries < 100)
      {
        os.str("");
        os<<FIT_NAME<<"_Energy_"<<ENERGY<<"_Board_"<<board<<"_Skiroc_"<<skiroc<<"_"<<type;
        std::cout<<os.str()<<std::endl<<"Skippped due to low stats ..."<<std::endl;
        continue;
      }

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



      Graph = new TGraphErrors(countMe,X,Y,errorX,errorY);
      fitStatus[board][skiroc][type_num] = Graph->Fit("flo","QSNEM","",FitRangeMin[type_num],FitRangeMax[type_num]); // Fitting Status
      FitResultPtr[board][skiroc][type_num]= Graph->Fit("flo","QSNEM","",FitRangeMin[type_num],FitRangeMax[type_num]); //E and M added for better error estimation and fitting....


    }
  }



}
