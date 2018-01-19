//Fits the Histogram from the ProfileX and then store it is FitResultPtr[][][]

#include "SaturationFinder.h"




Int_t startBin,endBin,countMe;
TGraphErrors* Graph[2];
TF1* flo; //Setting straight line fit for Lower region
int type_num;
std::string type;




void SaturationFinder::FitHistogram()
{

  std::ostringstream os( std::ostringstream::ate );

  FitRangeMin[0] = 110;
  FitRangeMax[0] = 200;
  FitRangeMin[1] = 300;
  FitRangeMax[1] = 400;
  ErrorInY_ADC[0] = 100;
  ErrorInX_ADC[0] = 5;
  ErrorInY_ADC[1] = 50;
  ErrorInX_ADC[1] = 5;
  Int_t Hist_Entries(0);

  //For HighGain to LowGain
  type_num =0; //for H_L
  type = "HighGaintoLowGain";
  for(int board = 0;board<BOARD;board++)
  {
    for(int skiroc = 0 ;skiroc<4;skiroc++)
    {

      //FINDME...
      // if(board != 1) continue;
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


      countMe=0;
      for(int i= startBin;i<=endBin;i++)
      {
        if(HistProfile[board][skiroc][type_num]->GetBinContent(i)<10) continue;
        if(HistProfile[board][skiroc][type_num]->GetBinCenter(i)>=1000) break;
        X[countMe] = HistProfile[board][skiroc][type_num]->GetBinCenter(i);
        errorY[countMe] = sqrt(pow(HistProfile[board][skiroc][type_num]->GetBinError(i),2) + pow(ErrorInY_ADC[type_num],2));
        // errorY[i] = sqrt(pow(HistProfile[board][skiroc][type_num]->GetBinError(i),2));

        // cout<<errorY[i]<<endl;
        errorX[countMe] = ErrorInX_ADC[type_num];
        Y[countMe] = HistProfile[board][skiroc][type_num]->GetBinContent(i);
        // cout<<X[i]<<"\t"<<Y[i]<<endl;
        countMe++;
      }


      flo = new TF1("flo","[0]*x+[1]");
      Graph[type_num] = new TGraphErrors(countMe,X,Y,errorX,errorY);
      FitResultPtr[board][skiroc][type_num]= Graph[type_num]->Fit("flo","QSN","",FitRangeMin[type_num],FitRangeMax[type_num]); //E and M added for better error estimation and fitting....
      fitStatus[board][skiroc][type_num] = (int)FitResultPtr[board][skiroc][type_num];

    }
  }



  //For Low to TOT
  type_num =1; //for L_T
  type = "LowGaintoTOTSLow";
  flo = new TF1("flo","[0]*x+[1]");
  for(int board = 0;board<BOARD;board++)
  {
    for(int skiroc = 0 ;skiroc<4;skiroc++)
    {
      // FINDME
      // if(board !=0) continue;
      // if(skiroc != 1) continue;


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

      countMe=0;
      for(int i= startBin;i<=endBin;i++)
      {
        if(HistProfile[board][skiroc][type_num]->GetBinContent(i)<10) continue;
        if(HistProfile[board][skiroc][type_num]->GetBinCenter(i)>=1000) break;
        X[countMe] = HistProfile[board][skiroc][type_num]->GetBinCenter(i);
        Y[countMe] = HistProfile[board][skiroc][type_num]->GetBinContent(i);
        errorY[countMe] = sqrt(pow(HistProfile[board][skiroc][type_num]->GetBinError(i),2) + pow(ErrorInY_ADC[type_num],2));
        // errorY[i] = sqrt(pow(HistProfile[board][skiroc][type_num]->GetBinError(i),2));
        errorX[countMe] = ErrorInX_ADC[type_num];

        // cout<<X[i]<<"\t"<<Y[i]<<endl;
        // cout<<setprecision(3)<<errorX[countMe]<<"\t"<<errorY[countMe]<<"\t"<<HistProfile[board][skiroc][type_num]->GetBinError(i)<<"\t"<<X[i]<<"\t"<<Y[i]<<endl;
        countMe++;
      }


      flo = new TF1("flo","[0]*x+[1]");
      Graph[type_num] = new TGraphErrors(countMe,X,Y,errorX,errorY);
      // FindFitRanges(type_num);
      FitResultPtr[board][skiroc][type_num] = Graph[type_num]->Fit("flo","SNQ","",FitRangeMin[type_num],FitRangeMax[type_num]); //E and M added for better error estimation and fitting....
      fitStatus[board][skiroc][type_num] = (int)FitResultPtr[board][skiroc][type_num];//Graph->Fit("flo","QSNEM","",FitRangeMin[type_num],FitRangeMax[type_num]); // Fitting Status


    }
  }



}



void SaturationFinder::FindFitRanges(int type_num)
{
  float max = FitRangeMin[type_num],min=FitRangeMax[type_num];
  float min_width_fit = 80;
  float fit_increment =5;
  float Chi_Sqr(0),MinimizeMe(1000000);

  for(float high=min+min_width_fit;high<max;high+=fit_increment)
  {
    for(float low=min;low<(high-min_width_fit); low+= fit_increment)
    {
      Graph[type_num]->Fit("flo","SNQEM","",low,high);
      Chi_Sqr = (Graph[type_num]->GetFunction("flo")->GetChisquare()/Graph[type_num]->GetFunction("flo")->GetNDF());
      if(Chi_Sqr < MinimizeMe)
      {
        MinimizeMe = Chi_Sqr;
        FitRangeMin[type_num] =low;
        FitRangeMax[type_num] =high;
      }
    }
  }

}
