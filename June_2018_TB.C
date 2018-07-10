
#include<iostream>
#include "SaturationFinder.h"


//Written by Rohith Saradhy

void June_2018_TB()
{
  gROOT->SetBatch(kTRUE); //Not displaying anything

  std::cout<<"Hello World"<<std::endl;

  SaturationFinder* a = new SaturationFinder(30,0,"other","June_2018_TB","June_2018","/home/rsaradhy/Work/Output/TransitionH_L/Data/test/ntuple_381.root");

  a->CreateStructure("./Analysed_data"); // Setting the root Folder for all analysed files to be dropped off and creating the structure ;
  // if(a->FIT_NAME == "Oct_H6_PFA" || a->FIT_NAME == "Oct_H2_PFA" ) a->cutoff[0] = 5;
  a->dataExtractor();
  a->SaveHistogram(); //Save histograms for faster processing later on
  // a->LoadHistogram(); // Load the saved histograms...
  a->FitHistogram(); // Fit those histograms Make sure that "gROOT->SetBatch(kTRUE); //Not displaying anything" is not commented
  a->FindValues(); //Find the saturation values that we are interested in ...
  a->StoreValues(""); //Store those values with a name prefix given as the argument
  // a->RetrieveValues("");
  a->SaveGraphs();//Save those graphs...


  return;
}
