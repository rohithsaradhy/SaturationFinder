// File starts extracting data from NTuples...
// Written by Rohith Saradhy
#include "SaturationFinder.h"
#include "TSystemDirectory.h"
void SaturationFinder::CollectFromNTuples(std::string runInfoFolder)
{
  CollectFromNTuples_Run=true;
  std::ostringstream os( std::ostringstream::ate );

cout<<"Hello World"<<runInfoFolder<<endl;


std::vector<std::string> FileNames;
//Getting all files inside a directory...
TSystemDirectory* dir = new TSystemDirectory(runInfoFolder.c_str(), runInfoFolder.c_str());
 TList *files = dir->GetListOfFiles();
 if (files)
{
  TSystemFile *file; TString fname; TIter next(files);
 while ((file=(TSystemFile*)next()))
  {
     fname = file->GetName();
     if (!file->IsDirectory() && fname.EndsWith("run"))
      {
         FileNames.push_back( fname.Data());
      }
  }
 }


// For all files in that folder
// for(int i=0; i< FileNames.size(); i++)
// {
//   std::cout<<FileNames.at(i)<<std::endl;
//   os.str("");
//   os<<RUN_TYPE<<"_"<<ENERGY<<"GeV.run";
//   if(FileNames.at(i)==os.str())
//   {
//
//
//   }
// }



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
