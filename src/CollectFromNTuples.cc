// File starts extracting data from NTuples...
// Written by Rohith Saradhy
#include "SaturationFinder.h"
#include "TSystemDirectory.h"
void SaturationFinder::CollectFromNTuples(std::string runInfoFolder)
{
  CollectFromNTuples_Run=true;
  std::ostringstream os( std::ostringstream::ate );



std::cout<<"Run files are taken from the following folder:"<<runInfoFolder<<std::endl;


if(ENERGY==0 && RUN_TYPE=="All")
{
  std::cout<<"Have not written code for all type... please fix this as this will not proceed further... ERROR!!!! Check CollectFromNTuples"<<std::endl;
  exit(1);
}
else if(ENERGY==0)
{
  std::fstream fs;
  os.str("");
  os<<runInfoFolder<<"/All_"<<RUN_TYPE<<".run";
  std::cout<<"Collecting Run Numbers from "<<os.str()<<std::endl;
  fs.open (os.str().c_str(), std::fstream::in | std::fstream::out | std::fstream::app);
  while(fs>>Run_No)
  {
    std::cout<<"Collecting From Run No: "<<Run_No<<std::endl;
    dataExtractor();
  }
  std::cout<<"Values have been retrieved into the arrays for HG_LG"<<std::endl;
  fs.close();

}
else
{
  //Collect Energy runs...
      std::fstream fs;
      os.str("");
      os<<runInfoFolder<<"/"<<RUN_TYPE<<"_"<<ENERGY<<"GeV.run";
      fs.open (os.str().c_str(), std::fstream::in | std::fstream::out | std::fstream::app);
      while(fs>>Run_No)
      {
        std::cout<<"Collecting From Run No: "<<Run_No<<std::endl;
        dataExtractor();
      }
      std::cout<<"Values have been retrieved into the arrays for HG_LG"<<std::endl;
      fs.close();

}





}
