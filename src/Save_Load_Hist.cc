#include "SaturationFinder.h"



void SaturationFinder::SaveHistogram(std::string rootFolder)
{
    std::ostringstream filename( std::ostringstream::ate );
    std::ostringstream os( std::ostringstream::ate );

    filename.str("");
    filename<<rootFolder<<FIT_NAME<<"_Energy_"<<ENERGY<<"_"<<RUN_TYPE<<".root";

    TFile *file = TFile::Open(filename.str().c_str(),"RECREATE");
    for(int i=0; i<BOARD; i++)
    {
        for(int j=0; j<4; j++)
        {
            os.str("");
            os<<FIT_NAME<<"_Energy_"<<ENERGY<<"_Board_"<<i<<"_Skiroc_"<<j<<"_HighGaintoLowGain";
            Hist2D[i][j][0]->Write(os.str().c_str());
            os.str("");
            os<<FIT_NAME<<"_Energy_"<<ENERGY<<"_Board_"<<i<<"_Skiroc_"<<j<<"_LowGaintoTOTSLow";
            Hist2D[i][j][1]->Write(os.str().c_str());

            std::cout<<FIT_NAME<<"_Energy_"<<ENERGY<<"_"<<RUN_TYPE<<"\t"<<"Saving  :: "<<(i*4 + j)*100/(BOARD*4 + 3)<<"% \r";
            std::cout.flush();

        }
    }
    std::cout<<std::endl;

    file->Close();

}



void SaturationFinder::LoadHistogram(std::string rootFolder)
{
    std::ostringstream filename( std::ostringstream::ate );
    std::ostringstream os( std::ostringstream::ate );

    filename.str("");
    filename<<rootFolder<<FIT_NAME<<"_Energy_"<<ENERGY<<"_"<<RUN_TYPE<<".root";


    TFile *file = TFile::Open(filename.str().c_str()); //Do not close the TFile Object. Canvas will be empty.
    for(int i=0; i<BOARD; i++)
    {
        for(int j=0; j<4; j++)
        {
            os.str("");
            os<<FIT_NAME<<"_Energy_"<<ENERGY<<"_Board_"<<i<<"_Skiroc_"<<j<<"_HighGaintoLowGain";
            gDirectory->GetObject(os.str().c_str(),Hist2D[i][j][0]);
            Hist2D[i][j][0]->SetDirectory(0) ; //Keep the Hist stay after file close...
            os.str("");
            os<<FIT_NAME<<"_Energy_"<<ENERGY<<"_Board_"<<i<<"_Skiroc_"<<j<<"_LowGaintoTOTSLow";
            gDirectory->GetObject(os.str().c_str(),Hist2D[i][j][1] );
            Hist2D[i][j][1]->SetDirectory(0) ;

            std::cout<<FIT_NAME<<"_Energy_"<<ENERGY<<"_"<<RUN_TYPE<<"\t"<<"Loading :: "<<(i*4 + j)*100/(BOARD*4 + 3)<<"% \r";
            std::cout.flush();

        }
    }
    std::cout<<std::endl;

    file->Close();
}
