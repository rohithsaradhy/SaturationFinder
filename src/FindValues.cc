#include "SaturationFinder.h"

void SaturationFinder::FindValues()
{
  cutoff[0] =5;
  cutoff[1] =7;
  std::string type;


  for(int board=0;board < BOARD; board++)
  {
    for(int skiroc=0;skiroc < 4; skiroc++)
    {


      // cout<<board<<'\t'<<skiroc<<"\t"<<0<<"\t"<<fitStatus[board][skiroc][0]<<endl;
      CutOff(board,skiroc,0);
      // cout<<board<<'\t'<<skiroc<<"\t"<<1<<"\t"<<fitStatus[board][skiroc][1]<<endl;
      CutOff(board,skiroc,1);

    }
  }


}


void SaturationFinder::CutOff(int board, int skiroc, int type_num)
{

  std::string type;
  std::ostringstream os( std::ostringstream::ate );


  // if(fitStatus[board][skiroc][type_num]>100 && fitStatus[board][skiroc][type_num]< 10000 )
  if(fitStatus[board][skiroc][type_num]==4000)
  {
  // std::cout<<"fit Status ::"<<fitStatus[board][skiroc][type_num]<<std::endl;
  switch(type_num)
  {
    case 0:
    type = "HighGaintoLowGain";
    break;
    case 1:
    type = "LowGaintoTOTSLow";
    break;
  }

  InitializeHist2D(type_num, 0); // Setting histogram edges according to type.

  os.str("");
  os<<FIT_NAME<<"_Energy_"<<ENERGY<<"_Board_"<<board<<"_Skiroc_"<<skiroc<<"_"<<type;
  // Initialising the Canvas...
  fitCanvas[board][skiroc][type_num] = new TCanvas(os.str().c_str(),os.str().c_str(),1366,768);
  fitCanvas[board][skiroc][type_num]->cd();

  //Storing Fit results...
  CF[board][skiroc][type_num] = FitResultPtr[board][skiroc][type_num]->Parameter(0);
  CF_Err[board][skiroc][type_num] = FitResultPtr[board][skiroc][type_num]->ParError(0);

  CF_Intercept[board][skiroc][type_num] = FitResultPtr[board][skiroc][type_num]->Parameter(1);
  CF_Intercept_Err[board][skiroc][type_num] = FitResultPtr[board][skiroc][type_num]->ParError(1);


  TProfile* pfX = HistProfile[board][skiroc][type_num];
  float lookFrom = 190;
  float yE[4];
  float slope = CF[board][skiroc][type_num];
  float slopeErr = CF_Err[board][skiroc][type_num];
  float intercept = CF_Intercept[board][skiroc][type_num] ;
  float interceptErr = CF_Intercept_Err[board][skiroc][type_num];
  float dmx=0;
  float y_err=0;
  float x[10000],y[10000],z[10000],u[10000], v[10000],w[10000],zx[10000], wx[10000],r[10000],rx[10000], y_co;

  int counter=0,N=0,zN=0,wN=0,rN=0;


  int bin_min = pfX->FindFirstBinAbove(1,1);//(contentThreshold,axis#) x=1;y=2;z=3
  int bin_max = pfX->FindLastBinAbove(1,1); //(contentThreshold,axis#) x=1;y=2;z=3

  float scaling_factor=y_Max/100;



  for (int i=bin_min;i<bin_max;i++)
  {
    if(pfX->GetBinContent(i)<10) continue; // Don't record this condition...
    x[N] = binningX[i];
    y[N] = pfX->GetBinContent(i);
    errorY[i] = sqrt(pow(pfX->GetBinError(i),2) + pow(ErrorInY_ADC[type_num],2));
    errorX[i] = ErrorInX_ADC[type_num];

    if(x[N]>=FitRangeMin[type_num] && x[N]<=FitRangeMax[type_num])
    {
      z[zN] = slope*(x[N]) + intercept;
      zx[zN] = x[N];
      zN++;
    }
    else
    {
      w[wN] = slope*(x[N]) + intercept;
      wx[wN]= x[N];
      wN++;

    }


    u[N] = (((slope*(x[N]) + intercept)-y[N])/y[N]) *100* scaling_factor; // 40 is the magic scalling factor

    if(x[N] >= 100)// Plotting the Residue
    {
      r[rN] = u[N];
      rx[rN] = x[N];
      rN++;
    }

    //Just checking for certain values....
    // if((N==5 || N==6 )&&(iski == 3))
    // {
    //   cout<<endl<<"You should look here.... ->"<<u[N]/40<<endl;
    // }

    v[N] = cutoff[type_num]*scaling_factor; // Place to change the cutoff[type_num]; 40 is the magic scalling factor....
    if(u[N]>cutoff[type_num]*scaling_factor && x[N] >lookFrom)
    {
      counter++;
      if(counter==1)
      {
        y_co = slope*(x[N]) + intercept;
        //Calculating Error...
        //My method...
        dmx = sqrt(pow( (slopeErr/slope),2) + pow((0/x[N]),2) ) * slope * x[N] ;
        y_err = sqrt(pow(dmx,2) + pow(interceptErr,2));
        // cout<<"interceptErr ="<<interceptErr<<endl;
        //Rajdeep's  method to calculate errors ...
        // cout<<"The central value is "<<y_co<<endl;
        yE[0] = (slope + slopeErr)*x[N] +(intercept+interceptErr);
        // cout<<endl<<yE[0]<<endl;
        yE[0] = fabs(yE[0] - y_co);
        // cout<<"Ye[0] is "<<yE[0]<<endl;

        yE[1] = (slope - slopeErr)*x[N] +(intercept-interceptErr);
        // cout<<yE[1]<<endl;
        yE[1] = fabs(yE[1] - y_co);
        // cout<<"Ye[1] is "<<yE[1]<<endl;

        yE[2] = (slope - slopeErr)*x[N] +(intercept+interceptErr);
        // cout<<yE[2]<<endl;
        yE[2] = fabs(yE[2] - y_co);
        // cout<<"Ye[2] is "<<yE[2]<<endl;

        yE[3] = (slope + slopeErr)*x[N] +(intercept-interceptErr);
        // cout<<yE[3]<<endl;
        yE[3] = fabs(yE[3] - y_co);
        // cout<<"Ye[3] is "<<yE[3]<<endl;

        // cout<<y_co<<endl;
        // cout<<endl<<"Error in Y my Method is: "<<y_err<<endl<<"Error in Y Rajdeep Method is "<<yE[Max_Index(yE)]<<" with Index as: "<<Max_Index(yE)<<endl;

        //Choosing Rajdeeps Method...
        y_err = yE[Max_Index(yE)];
      }
    }
    N++;
  }

  TP[board][skiroc][type_num] = y_co;
  TP_Err[board][skiroc][type_num]= y_err;




  mg = new TMultiGraph();
  grph[0] = new TGraphErrors(N,x,y,errorX,errorY);
  grph[0]->SetName("X-Profile");
  grph[0]->SetMarkerStyle(20);
  grph[0]->SetMarkerColor(1);
  grph[0]->SetMarkerSize(1.4);
  mg->Add(grph[0],"p");

  grph[1] = new TGraph(zN,zx,z);
  grph[1]->SetName("Fit Function");
  grph[1]->SetMarkerStyle(21);
  grph[1]->SetLineColor(2);
  grph[1]->SetLineWidth(4);
  mg->Add(grph[1],"l");

  grph[4] = new TGraph(wN,wx,w);
  grph[4]->SetName("Fit Line");
  grph[4]->SetMarkerStyle(21);
  grph[4]->SetLineColor(2);
  grph[4]->SetLineStyle(7);
  grph[4]->SetLineWidth(4);
  mg->Add(grph[4],"l");

  grph[3] = new TGraph(N,x,v);
  grph[3]->SetName("Cutoff Threshold of the Residual");
  grph[3]->SetMarkerStyle(1);
  grph[3]->SetLineColor(kBlue);
  grph[3]->SetLineWidth(4);
  mg->Add(grph[3],"l");





  grph[2] = new TGraph(rN,rx,r);
  // grph[2] = new TGraph(N,x,u);
  grph[2]->SetName("Relative Residual");
  grph[2]->SetMarkerStyle(22);
  grph[2]->SetMarkerColor(3);
  grph[2]->SetMarkerSize(1.5);
  mg->Add(grph[2],"p");



  Graph_Settings(board,skiroc,type_num);
}
else
{
  std::cout<<"Fitting status not = 4000, skipping :: \t";
  std::cout<<"Board_"<<board<<"_Skiroc_"<<skiroc<<"_type_num_"<<0<<"_FitStatus_"<<fitStatus[board][skiroc][type_num]<<std::endl;

}

}

int SaturationFinder::Max_Index(float* value)
{
  float biggest;
  biggest = 0;
  int j=0;
  for(int i=0;i<4;i++)
  {
    if(value[i]>biggest)
    {
      biggest = value[i];
      j=i;
    }

  }
  return j;

}
