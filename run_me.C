#include<iostream>
#include "SaturationFinder.h"



void run_me()
{

    gROOT->SetBatch(kTRUE); //Not displaying anything
    SaturationFinder* a;
    SaturationFinder* Oct_H2 = new SaturationFinder(17,0,"All","April","Oct_H2_TS3","/home/rsaradhy/Work/Output/TransitionH_L/Data/data_27_3_2018/H2/"); // 0 implies that it is a allfile which is kept in the root directory...
    Oct_H2->SetModuleMaps("/home/rsaradhy/Work/Output/TransitionH_L/Data/data_27_3_2018/H2/layerGeom_oct2017_h2_17layers.txt"); // Remove all '#' from this file and empty lines
    SaturationFinder* Oct_H6 = new SaturationFinder(20,0,"All","April","Oct_H6_PFA","/home/rsaradhy/Work/Output/TransitionH_L/Data/data_27_3_2018/H6/"); // 0 implies that it is a allfile which is kept in the root directory...
    Oct_H6->SetModuleMaps("/home/rsaradhy/Work/Output/TransitionH_L/Data/data_27_3_2018/H6/layerGeom_oct2017_h6_20layers.txt"); // Remove all '#' from this file and empty lines

    // SaturationFinder* a = new SaturationFinder(17,0,"HexaOutput_1535","Oct_H2_test_Electron","/home/rsaradhy/Work/Output/TransitionH_L/New_Data/Oct_NTuple/"); // 0i mplies that it is a allfile...
    // SaturationFinder* a = new SaturationFinder(20,0,"All","Oct_H6","/home/rsaradhy/Work/Output/TransitionH_L/New_Data/Oct_H6_NTuple/"); // 0 implies that it is a allfile...

    std::ostringstream os( std::ostringstream::ate );


    //
    a = Oct_H6;
    a->CreateStructure("./Analysed_data"); // Setting the root Folder for all analysed files to be dropped off and creating the structure
    a->dataExtractor(2); //Available Options are :: 0->TS3  1->TS3withCM   2->PFA
    a->SaveHistogram(); //Save histograms for faster processing later on
    a->LoadHistogram(); // Load the saved histograms...
    a->FitHistogram(); // Fit those histograms Make sure that "gROOT->SetBatch(kTRUE); //Not displaying anything" is not commented
    a->FindValues(); //Find the saturation values that we are interested in ...
    a->StoreValues(""); //Store those values with a name prefix given as the argument
    a->RetrieveValues(""); //Retrieve those values with a name prefix given as the argument
    a->FixAllValues(0); // Fix unstable values for HG-> LG
    a->FixAllValues(1); // Fix unstable values for LG-> TOT
    a->StoreValues("Final_"); //Store those values with a name prefix given as the argument


    for(int type_num=0; type_num<2; type_num++)
    {
      for(int i=0 ; i< 20 ; i++)
        {
          for(int j =0; j<4 ; j++)
            {
                if(a->fitStatus[i][j][type_num]==99999)
                {

                    os.str("");
                    if(type_num ==0 )os<<a->rootFolder<<"HG_LG/";
                    else os<<a->rootFolder<<"LG_TOT/";


                    os<<a->fitCanvas[i][j][type_num]->GetName()<<".png";
                    a->fitCanvas[i][j][type_num]->SaveAs(os.str().c_str());


                }
            }
        }

    }


    return;
}


#ifndef MAIN
#define MAIN
int main()
{
    run_me();
}
#endif
