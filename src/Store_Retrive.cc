#include<SaturationFinder.h>



void SaturationFinder::StoreValues(std::string rootFolder)
{

  std::ostringstream os( std::ostringstream::ate );
  std::ofstream fs;
  os.str("");
  os<<rootFolder<<"HG_LG_Datbase.txt";
  fs.open(os.str().c_str());
  fs<<std::fixed;
  int type_num =0;
  for(int board=0;board<BOARD;board++)
  {
    for(int skiroc=0; skiroc < 4; skiroc++)
    {

      fs <<setprecision(2)<<board<<"\t"<<skiroc<<"\t"<< CF[board][skiroc][type_num]<<"\t"<<CF_Err[board][skiroc][type_num]
      <<"\t"<<CF_Intercept[board][skiroc][type_num]<<"\t"<<CF_Intercept_Err[board][skiroc][type_num]<<"\t"
      <<TP[board][skiroc][type_num]<<"\t"<<TP_Err[board][skiroc][type_num]<<endl;
    }
  }
  std::cout<<"Data Written to :"<<os.str()<<std::endl;
  fs.close();



  os.str("");
  os<<rootFolder<<"LG_TOT_Datbase.txt";
  fs.open (os.str().c_str());
  fs<<std::fixed;
  type_num =1;
  for(int board=0;board<BOARD;board++)
  {
    for(int skiroc=0; skiroc < 4; skiroc++)
    {

      fs <<setprecision(2)<<board<<"\t"<<skiroc<<"\t"<< CF[board][skiroc][type_num]<<"\t"<<CF_Err[board][skiroc][type_num]
      <<"\t"<<CF_Intercept[board][skiroc][type_num]<<"\t"<<CF_Intercept_Err[board][skiroc][type_num]<<"\t"
      <<TP[board][skiroc][type_num]<<"\t"<<TP_Err[board][skiroc][type_num]<<endl;
    }
  }
  std::cout<<"Data Written to :"<<os.str()<<std::endl;
  fs.close();


}

void SaturationFinder::RetriveValues(std::string rootFolder)
{


}
