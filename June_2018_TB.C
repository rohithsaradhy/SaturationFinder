
#include<iostream>
#include "SaturationFinder.h"


//Written by Rohith Saradhy

void June_2018_TB()
{
  gROOT->SetBatch(kTRUE); //Not displaying anything

  std::string runFileFolder="./forTBFramework/2018/get_Runs/runs/";

  std::cout<<"Hello World"<<std::endl;

  SaturationFinder* a;
  const int numOfEnergy = 6;
  int Energy[numOfEnergy] = {150,100,80,50,30,10};
  // for (int i=0;i<numOfEnergy;i++)
  // {
  //   a = new SaturationFinder(30,Energy[i],"Electrons","June_2018_TB","June_2018","/eos/cms/store/group/dpg_hgcal/tb_hgcal/2018/cern_h2_june/offline_analysis/ntuples/v6");
  //   a->SetModuleMaps("forTBFramework/2018/layerGeom_june2018_h2_28layers.txt");
  //   a->CreateStructure("/eos/user/r/rsaradhy/www/June2018/"); // Setting the root Folder for all analysed files to be dropped off and creating the structure ;
  //   a->CollectFromNTuples(runFileFolder);
  //   a->SaveHistogram(); //Save histograms for faster processing later on
  //   // a->LoadHistogram(); // Load the saved histograms...
  //   a->FitHistogram(); // Fit those histograms Make sure that "gROOT->SetBatch(kTRUE); //Not displaying anything" is not commented
  //   a->FindValues(); //Find the saturation values that we are interested in ...
  //   a->StoreValues(""); //Store those values with a name prefix given as the argument
  //   // a->RetrieveValues("");
  //   a->SaveGraphs();//Save those graphs into the rootFolder set/created by CreateStructure Method...
  // }




  a = new SaturationFinder(30,0,"Electrons","June_2018_TB","June_2018","/eos/cms/store/group/dpg_hgcal/tb_hgcal/2018/cern_h2_june/offline_analysis/ntuples/v6");
  a->CreateStructure("/eos/user/r/rsaradhy/www/June2018/");
  a->SetModuleMaps("forTBFramework/2018/layerGeom_june2018_h2_28layers.txt");
  a->CollectFromNTuples(runFileFolder);
  a->SaveHistogram(); //Save histograms for faster processing later on
  // a->LoadHistogram(); // Load the saved histograms...
  a->FitHistogram(); // Fit those histograms Make sure that "gROOT->SetBatch(kTRUE); //Not displaying anything" is not commented
  a->FindValues(); //Find the saturation values that we are interested in ...
  a->StoreValues(""); //Store those values with a name prefix given as the argument
  // a->RetrieveValues("");
  a->SaveGraphs();//Save those graphs into the rootFolder set/created by CreateStructure Method...




  return;
}
