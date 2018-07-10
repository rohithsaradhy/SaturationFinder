#include "SaturationFinder.h"
#include <sys/stat.h>

bool SaturationFinder::dirExists(const char *path)
{
    struct stat info;

    if(stat( path, &info ) != 0)
        return 0;
    else if(info.st_mode & S_IFDIR)
        return 1;
    else
        return 0;
}


bool SaturationFinder::is_file_exist(const char *fileName)
{
    std::ifstream infile(fileName);
    return infile.good();
}


SaturationFinder::SaturationFinder(int board,float energy,std::string run_type, std::string analysis_id,std::string fit_name, std::string data_loc)
{

  BOARD = board;
  ENERGY = energy;
  RUN_TYPE = run_type; //All, Electron, Pion
  ANALYSIS_ID =analysis_id; // Prefix for analysis
  FIT_NAME = fit_name; // The name that will Appear on the graphs

  DATA_LOC = data_loc;

  //Default values
  FitRangeMin[0] = 75;
  FitRangeMax[0] = 180;
  FitRangeMin[1] = 300;
  FitRangeMax[1] = 400;

  cutoff[0] =3;
  cutoff[1] =7;
  lookFrom[0] = 190;
  lookFrom[1] = 410;

  getInfo();

  InitializeDataArray();

  InitializeHist2D(0,1);
  InitializeHist2D(1,1);



}


SaturationFinder::~SaturationFinder()
{
  for(int i=0;i<BOARD;i++)
  {
    for(int j=0;j <4;j++)
    {
      delete Hist2D[i][j][1];
      delete Hist2D[i][j][0] ;
    }
  }
}

void SaturationFinder::getInfo()
{
    std::cout<<std::endl<<"$$$$$$$$$$$$$$$$$$$$$$$$$$$$"<<std::endl;
    std::cout<<"Information about this object"<<std::endl;
    std::cout<<std::endl<<"$$$$$$$$$$$$$$$$$$$$$$$$$$$$"<<std::endl;
    std::cout<<"Energy :"<<ENERGY<<std::endl;
    std::cout<<"Total Boards :"<<BOARD<<std::endl;
    std::cout<<"Run Type :"<<RUN_TYPE<<std::endl;
    std::cout<<"Analysis_ID :"<<ANALYSIS_ID<<std::endl;
    std::cout<<"Fit Name :"<<FIT_NAME<<std::endl;
    std::cout<<"Data Location Folder:"<<DATA_LOC;
    std::cout<<std::endl<<"$$$$$$$$$$$$$$$$$$$$$$$$$$$$"<<std::endl;

    return ;
}

void SaturationFinder::makeDir(const char *path)
{
  if(!dirExists(path))
  {
    std::cout<<"Creating directory:: "<<path<<" $$$$$$$"<<std::endl;
    std::cout<<"Created directory with status "<<mkdir(path,ACCESSPERMS)<<std::endl;
  }
}

void SaturationFinder::CreateStructure(const char * path)
{
  std::ostringstream os( std::ostringstream::ate );
  std::ostringstream os1( std::ostringstream::ate );
  std::ostringstream os2( std::ostringstream::ate );

  if((RUN_TYPE == "All" || RUN_TYPE == "other") && ENERGY == 0)
  {
    os.str("");
    makeDir(path);
    os<<path<<"/"<<ANALYSIS_ID;
    makeDir(os.str().c_str());
    os<<"/"<<FIT_NAME<<"/";
    rootFolder = os.str();
    makeDir(os.str().c_str());
    os1<<os.str();
    os<<"HG_LG/";
    makeDir(os.str().c_str());
    os1<<"LG_TOT/";
    makeDir(os1.str().c_str());
  }
  else if(ENERGY != 0)
  {
    os.str("");
    makeDir(path);
    os<<path<<"/"<<ANALYSIS_ID;
    makeDir(os.str().c_str());
    os<<"/"<<FIT_NAME<<"/";
    makeDir(os.str().c_str());
    os<<"ParticleWise/";
    makeDir(os.str().c_str());
    os<<""<<RUN_TYPE<<"/";
    makeDir(os.str().c_str());
    os1.str("");
    os1<<os.str();
    os1<<"Stability/";
    makeDir(os1.str().c_str());
    os2<<os1.str();
    os1<<"HG_LG/";
    makeDir(os1.str().c_str());
    os2<<"LG_TOT/";
    makeDir(os2.str().c_str());


    os1.str("");
    os<<""<<ENERGY<<"/";
    rootFolder = os.str();
    makeDir(os.str().c_str());
    os1<<os.str();
    os<<"HG_LG/";
    makeDir(os.str().c_str());
    os1<<"LG_TOT/";
    makeDir(os1.str().c_str());
  }

}

void SaturationFinder::SetModuleMaps(const char * path)
{

  std::cout<<"Path Selected is :: "<<path<<std::endl;
  std::ostringstream os( std::ostringstream::ate );


  std::string module ="";
  std::string a = "";
  std::string b = "";
  std::fstream fs;
  int brd=0 ,iter=0;



  os.str("");
  os<<path;
  fs.open (os.str().c_str(), std::fstream::in | std::fstream::out | std::fstream::app);
  std::string stuff;
  getline(fs,stuff);
  while(!fs.eof())
  {

    fs>>b>>a>>a>>a>>a>>module;
    std::stringstream int_str(module);
    int_str >> Module[brd];
    brd++;

  }

  std::cout<<"No: of boards that we collected is "<<brd-1<<std::endl;
  fs.close();


}



void SaturationFinder::SaveGraphs()
{
  std::ostringstream os( std::ostringstream::ate );


  std::cout<<std::endl<<"$$$$$$$$$$$$$$$$$$$$$$$$$$$$"<<std::endl;
  std::cout<<"Saving the Files to: "<<rootFolder<<std::endl;
  std::cout<<std::endl<<"$$$$$$$$$$$$$$$$$$$$$$$$$$$$"<<std::endl;

  for(int type_num=0; type_num<2; type_num++) //type_num is for HG_LG and LG_TOT
  {
    for(int brd=0 ; brd< BOARD ; brd++)
      {
        for(int ski =0; ski<SKIROC ; ski++)
          {
              if(fitStatus[brd][ski][type_num]==99999)
              {

                  os.str("");
                  if(type_num ==0 )os<<rootFolder<<"HG_LG/";
                  else os<<rootFolder<<"LG_TOT/";


                  os<<fitCanvas[brd][ski][type_num]->GetName()<<".png";
                  fitCanvas[brd][ski][type_num]->SaveAs(os.str().c_str());


              }
          }
      }

  }
}
