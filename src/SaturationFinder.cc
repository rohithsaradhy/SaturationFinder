#include "SaturationFinder.h"


SaturationFinder::SaturationFinder(int board,float energy, std::string run_type, std::string fit_name, std::string data_loc)
{

  BOARD = board;
  ENERGY = energy;
  RUN_TYPE = run_type;
  FIT_NAME = fit_name;
  DATA_LOC = data_loc;


  getInfo();



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
    std::cout<<"Fit Name :"<<FIT_NAME<<std::endl;
    std::cout<<"Data Location Folder:"<<DATA_LOC;
    std::cout<<std::endl<<"$$$$$$$$$$$$$$$$$$$$$$$$$$$$"<<std::endl;

    return ;


}
