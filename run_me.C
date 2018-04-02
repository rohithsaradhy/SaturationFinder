#include<iostream>
#include "SaturationFinder.h"
#include <sys/stat.h>

int dirExists(const char *path)
{
    struct stat info;

    if(stat( path, &info ) != 0)
        return 0;
    else if(info.st_mode & S_IFDIR)
        return 1;
    else
        return 0;
}


void run_me()
{

    gROOT->SetBatch(kTRUE); //Not displaying anything

    SaturationFinder* a = new SaturationFinder(17,0,"All","Oct_H2","/home/rsaradhy/Work/Output/TransitionH_L/Data/data_27_3_2018/H2/"); // 0 implies that it is a allfile which is kept in the root directory...
    // SaturationFinder* a = new SaturationFinder(20,0,"All","Oct_H6","/home/rsaradhy/Work/Output/TransitionH_L/Data/data_27_3_2018/H6/"); // 0 implies that it is a allfile which is kept in the root directory...
    // SaturationFinder* a = new SaturationFinder(17,0,"HexaOutput_1535","Oct_H2_test_Electron","/home/rsaradhy/Work/Output/TransitionH_L/New_Data/Oct_NTuple/"); // 0i mplies that it is a allfile...

    // SaturationFinder* a = new SaturationFinder(20,0,"All","Oct_H6","/home/rsaradhy/Work/Output/TransitionH_L/New_Data/Oct_H6_NTuple/"); // 0 implies that it is a allfile...

    std::ostringstream os( std::ostringstream::ate );
    int status;
    //
    a->dataExtractor();
    a->SaveHistogram("./temp_data/");
    a->LoadHistogram("./temp_data/");
    a->FitHistogram();
    a->FindValues();
    a->StoreValues("./temp_data/");
    a->RetrieveValues("./temp_data/");
    a->FixAllValues(0);
    a->FixAllValues(1);
    a->StoreValues("./temp_data/Final_");


    // b->FitHistogram();
    // b->FindValues();
    // a->InitializeHist2D(0,1);
    // a->Hist2D[0][0][1]->Draw();
    // a->CutOff(2,2,1);
    // a->CutOff(2,2,0);
    // std::cout<<a->fitStatus[0][1][1]<<std::endl;
    // a->fitCanvas[0][1][1]->SaveAs("./temp.png");
    // a->fitCanvas[0][1][0]->SaveAs("./temp1.png");
    // //

    string rootGraphsFolder;
    rootGraphsFolder = "./Graphs/April/";
    status = mkdir(rootGraphsFolder.c_str(),ACCESSPERMS); // For some reason, it wont createbeyond the second folder. so manually creating
    rootGraphsFolder = "./Graphs/April/H2/";
    status = mkdir(rootGraphsFolder.c_str(),ACCESSPERMS); // For some reason, it wont createbeyond the second folder. so manually creating
    rootGraphsFolder = "./Graphs/April/H2/TS3withCM/";
    status = mkdir(rootGraphsFolder.c_str(),ACCESSPERMS); // For some reason, it wont createbeyond the second folder. so manually creating

    for(int i=0 ; i< 20 ; i++)
    {
        for(int j =0; j<4 ; j++)
        {
            for(int type_num=0; type_num<2; type_num++)
            {
                if(a->fitStatus[i][j][type_num]==99999)
                {
                    os.str("");

                    if(type_num ==0 )os<<rootGraphsFolder<<"HG_TOT/";
                    else os<<rootGraphsFolder<<"LG_TOT/";

                    //Make a directory if it is not already there.
                    // os.str("./hello/sdf/");
                    if(!dirExists(os.str().c_str()))
                    {
                        std::cout<<"Creating Directory "<<os.str()<<std::endl;
                        status = mkdir(os.str().c_str(),ACCESSPERMS);
                        std::cout<<"Created Directory with status "<<status <<std::endl;
                    }

                    os<<a->fitCanvas[i][j][type_num]->GetName()<<".png";
                    std::cout<<"Saving the file into "<<os.str()<<std::endl;


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
