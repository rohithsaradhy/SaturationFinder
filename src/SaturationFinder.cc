#include "SaturationFinder.h"


SaturationFinder::SaturationFinder()
{
  std::cout<< "Hope that we already intialised the board number"<<std::endl;

}



SaturationFinder::SaturationFinder(int board)
{

  BOARD = board;
  std::cout<<"Total Number of Boards is "<<BOARD<<std::endl;



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
