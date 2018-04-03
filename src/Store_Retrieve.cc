#include<SaturationFinder.h>



void SaturationFinder::StoreValues(std::string prefixName)
{

  std::ostringstream os( std::ostringstream::ate );
  std::ofstream fs;
  os.str("");
  os<<rootFolder<<prefixName<<FIT_NAME<<"_HG_LG_Datbase.txt";
  fs.open(os.str().c_str());
  fs<<std::fixed;
  int type_num =0;
  for(int board=0;board<BOARD;board++)
  {
    for(int skiroc=0; skiroc < 4; skiroc++)
    {

      fs <<std::setprecision(2)<<board<<"\t"<<skiroc<<"\t"<< CF[board][skiroc][type_num]<<"\t"<<CF_Err[board][skiroc][type_num]
      <<"\t"<<CF_Intercept[board][skiroc][type_num]<<"\t"<<CF_Intercept_Err[board][skiroc][type_num]<<"\t"
      <<TP[board][skiroc][type_num]<<"\t"<<TP_Err[board][skiroc][type_num]<<std::endl;
    }
  }
  std::cout<<"Data Written to :"<<os.str()<<std::endl;
  fs.close();



  os.str("");
  os<<rootFolder<<prefixName<<FIT_NAME<<"_LG_TOT_Datbase.txt";
  fs.open (os.str().c_str());
  fs<<std::fixed;
  type_num =1;
  for(int board=0;board<BOARD;board++)
  {
    for(int skiroc=0; skiroc < 4; skiroc++)
    {

      fs <<std::setprecision(2)<<board<<"\t"<<skiroc<<"\t"<< CF[board][skiroc][type_num]<<"\t"<<CF_Err[board][skiroc][type_num]
      <<"\t"<<CF_Intercept[board][skiroc][type_num]<<"\t"<<CF_Intercept_Err[board][skiroc][type_num]<<"\t"
      <<TP[board][skiroc][type_num]<<"\t"<<TP_Err[board][skiroc][type_num]<<std::endl;
    }
  }
  std::cout<<"Data Written to :"<<os.str()<<std::endl;
  fs.close();


}

void SaturationFinder::RetrieveValues(std::string prefixName)
{

    std::ostringstream os( std::ostringstream::ate );
    int brd,ski,type_num;
    float cf,cf_e,cf_int,cf_int_e,tp,tp_e;
    std::fstream fs;


    type_num =0;
    os.str("");
    os<<rootFolder<<prefixName<<FIT_NAME<<"_HG_LG_Datbase.txt";
    fs.open (os.str().c_str(), std::fstream::in | std::fstream::out | std::fstream::app);
    while(!fs.eof())
    {

      fs>>brd>>ski>>cf>>cf_e>>cf_int>>cf_int_e>>tp>>tp_e;
      // std::cout<<brd<<"\t"<<ski<<"\t"<<fs.eof()<<std::endl;

      CF[brd][ski][type_num] = cf;
      CF_Err[brd][ski][type_num] = cf_e;
      CF_Intercept[brd][ski][type_num] = cf_int;
      CF_Intercept_Err[brd][ski][type_num] = cf_int_e;
      TP[brd][ski][type_num] = tp;
      TP_Err[brd][ski][type_num] = tp_e;



    }
    std::cout<<"Values have been retrieved into the arrays for HG_LG"<<std::endl;
    fs.close();


    type_num =1;
    os.str("");
    os<<rootFolder<<prefixName<<FIT_NAME<<"_LG_TOT_Datbase.txt";
    fs.open (os.str().c_str(), std::fstream::in | std::fstream::out | std::fstream::app);
    while(!fs.eof())
    {

      fs>>brd>>ski>>cf>>cf_e>>cf_int>>cf_int_e>>tp>>tp_e;
      // std::cout<<brd<<"\t"<<ski<<"\t"<<fs.eof()<<std::endl;

      CF[brd][ski][type_num] = cf;
      CF_Err[brd][ski][type_num] = cf_e;
      CF_Intercept[brd][ski][type_num] = cf_int;
      CF_Intercept_Err[brd][ski][type_num] = cf_int_e;
      TP[brd][ski][type_num] = tp;
      TP_Err[brd][ski][type_num] = tp_e;



    }
    std::cout<<"Values have been retrieved into the arrays for LG_TOT"<<std::endl;
    fs.close();
}
