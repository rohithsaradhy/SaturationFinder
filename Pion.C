// File to analyse pion data.
#include<iostream>
#include "SaturationFinder.h"


void Pion()
{

  const int BOARD =17;
  const int Number_Energy =6;
  Energy[Number_Energy]={"100","150","200","250","300","350"}

  SaturationFinder* EnergyData[Number_Energy];

  for(int i=0;i<Number_Energy;i++)
  {
    EnergyData = new SaturationFinder(BOARD,Energy[i],"Pion","Oct_H2","/home/rsaradhy/Work/Output/TransitionH_L/New_Data/Oct_NTuple/"); // 0i mplies that it is a allfile...
    
  }



}
