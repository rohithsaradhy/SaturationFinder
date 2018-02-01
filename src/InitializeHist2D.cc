#include "SaturationFinder.h"





void SaturationFinder::InitializeHist2D(Int_t option, bool hist)
{

  std::ostringstream histoName( std::ostringstream::ate );

  switch(option)
  {
    case 0:
    // std::cout<<"Initialising HG_LG Histograms..."<<std::endl;
    bin_start =0;
    bin_stop =3000;
    bin_change1 =200; // 160
    bin_change2 =300;

    // bin_width1 =5;
    // bin_width2 =10;
    // bin_width3 =20;

    bin_width1 =1;
    bin_width2 =1;
    bin_width3 =1;

    current_bin_low=bin_start;
    bin_total=0;

    // Y range definition
    y_Max =4000;
    y_Min = 0;
    y_bin=1;
    y_totalbins = (y_Max - y_Min)/y_bin;


    // Variable binning...
    for(int y=0;y<bin_stop;y++)
    {
      bin_total++;
      if(current_bin_low <= bin_change1)
      {
        binningX[y]=current_bin_low;
        current_bin_low +=  bin_width1;
      }
      else if(current_bin_low>bin_change1 && current_bin_low <=bin_change2)
      {
        binningX[y]=current_bin_low;
        current_bin_low +=  bin_width2;
      }
      else if( current_bin_low>bin_change2)
      {
        binningX[y]=current_bin_low;
        current_bin_low +=  bin_width3;
      }
      if(current_bin_low>=bin_stop) break;


    }

    bin_total--;

    if(!hist) break;

    for(int i=0;i<BOARD;i++)
    {
      for(int j=0;j <4;j++)
      {
        histoName.str("");
        histoName<<"Board_"<<i<<"_Ski_"<<j<<"_HighGaintoLowGain";
        Hist2D[i][j][0] = new TH2F(histoName.str().c_str(),histoName.str().c_str(),bin_total,binningX,y_totalbins,y_Min,y_Max);//bin_total,binningX,y_totalbins,y_Min,y_Max);
      }
    }

    std::cout<<"Done with the Initialising HighGaintoLowGain Histograms..."<<std::endl;
    break;

    case 1:
    // std::cout<<"Initialising LowGain to Slow TOT Histograms"<<std::endl;

    bin_start =0;
    bin_stop =3000;
    bin_change1 =505; // 160
    bin_change2 =715;

    // bin_width1 =10;
    // bin_width2 =25;
    // bin_width3 =50;

    bin_width1 =1;
    bin_width2 =1;
    bin_width3 =1;

    current_bin_low=bin_start;
    bin_total=0;

    // Y range definition
    y_Max =3000;
    y_Min = 0;
    y_bin=1;
    y_totalbins = (y_Max - y_Min)/y_bin;

    // Variable binning...
    for(int y=0;y<bin_stop;y++)
    {
      bin_total++;
      if(current_bin_low <= bin_change1)
      {
        binningX[y]=current_bin_low;
        current_bin_low +=  bin_width1;
      }
      else if(current_bin_low>bin_change1 && current_bin_low <=bin_change2)
      {
        binningX[y]=current_bin_low;
        current_bin_low +=  bin_width2;
      }
      else if( current_bin_low>bin_change2)
      {
        binningX[y]=current_bin_low;
        current_bin_low +=  bin_width3;
      }
      if(current_bin_low>=bin_stop) break;
    }

    bin_total--;

    if(!hist) break;

    for(int i=0;i<BOARD;i++)
    {
      for(int j=0;j <4;j++)
      {
        histoName.str("");
        histoName<<"Board_"<<i<<"_Ski_"<<j<<"_LowGaintoTOTSLow";
        Hist2D[i][j][1] = new TH2F(histoName.str().c_str(),histoName.str().c_str(),bin_total,binningX,y_totalbins,y_Min,y_Max);
      }
    }
    std::cout<<"Done with the Initialising LowGaintoTOTSLow Histograms..."<<std::endl;

    break;
  }
  return;
}


void SaturationFinder::InitializeDataArray()
{
  for(int board =0; board<BOARD; board++)
  {
    for (int skiroc =0; skiroc < 4; skiroc++)
    {
      for(int i=0;i<3;i++)
      {
        CF[board][skiroc][i]=0;
        CF_Err[board][skiroc][i]=0;
        CF_Intercept[board][skiroc][i]=0;
        CF_Intercept_Err[board][skiroc][i]=0;
        TP[board][skiroc][i]=0;
        TP_Err[board][skiroc][i]=0;
        fitStatus[board][skiroc][i]=0;

      }
    }
  }

  for(int i=0;i<10000;i++)
  {
    X[i] =0;
    Y[i] =0;
    errorY[i]=0;
    errorX[i]=0;

  }
}
