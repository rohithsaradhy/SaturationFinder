// This takes the NTuples and creates the necessary 2d Histograms so we can work with them faster..
//  NTuples are event based.
// Written by Rohith Saradhy
#include "SaturationFinder.h"



void SaturationFinder::dataExtractor()
{
    Int_t board(0),skiroc(0);
    float x(0),y(0),z(0);
    std::cout<<std::endl<<std::endl<<"Starting dataExtractor"<<std::endl;

    //Initialising all the variables...
    // std::vector<int>* Hit_Sensor_Event;
    std::vector<int>* Hit_Sensor_Channel=0;
    std::vector<int>* Hit_Sensor_Layer=0;
    std::vector<int>* Hit_Sensor_Skiroc=0;
    std::vector<int>* Hit_Sensor_Cell_Type=0;

    // Cell Information Old
    std::vector<float>* Hit_Sensor_Cell_X=0;
    std::vector<float>* Hit_Sensor_Cell_Y=0;
    std::vector<float>* Hit_Sensor_Cell_HG =0;
    std::vector<float>* Hit_Sensor_Cell_HG_Sub=0;
    std::vector<float>* Hit_Sensor_Cell_LG = 0;
    std::vector<float>* Hit_Sensor_Cell_LG_Sub=0;
    std::vector<float>* Hit_Sensor_Cell_ToT_Slow=0;
    std::vector<float>* Hit_Sensor_Cell_ToA_Fall=0;
    std::vector<float>* Hit_Sensor_Cell_ToA_Rise=0;
//
//  // Cell Information with PulseFit
    std::vector<float>* Hit_Sensor_Cell_HG_Amplitude=0;
    std::vector<float>* Hit_Sensor_Cell_HG_Amplitude_Error=0;
    std::vector<float>* Hit_Sensor_Cell_HG_Tmax=0;
    std::vector<float>* Hit_Sensor_Cell_HG_Chi2=0;
    std::vector<float>* Hit_Sensor_Cell_HG_Tmax_Error=0;
    std::vector<int>* Hit_Sensor_Cell_HG_Status=0;
    std::vector<int>* Hit_Sensor_Cell_HG_NCalls=0;
// // Same thing for LG
    std::vector<float>* Hit_Sensor_Cell_LG_Amplitude=0;
    std::vector<float>* Hit_Sensor_Cell_LG_Amplitude_Error=0;
    std::vector<float>* Hit_Sensor_Cell_LG_Tmax=0;
    std::vector<float>* Hit_Sensor_Cell_LG_Chi2=0;
    std::vector<float>* Hit_Sensor_Cell_LG_Tmax_Error=0;
    std::vector<int>* Hit_Sensor_Cell_LG_Status=0;
    std::vector<int>* Hit_Sensor_Cell_LG_NCalls=0;

    // For CM Subtracted amplitudes
    std::vector<float>* Hit_Sensor_Cell_HG_Amplitude_CM=0;
    std::vector<float>* Hit_Sensor_Cell_HG_Amplitude_Error_CM=0;
    std::vector<float>* Hit_Sensor_Cell_HG_Tmax_CM=0;
    std::vector<float>* Hit_Sensor_Cell_HG_Chi2_CM=0;
    std::vector<float>* Hit_Sensor_Cell_HG_Tmax_Error_CM=0;
    std::vector<int>* Hit_Sensor_Cell_HG_Status_CM=0;
    std::vector<int>* Hit_Sensor_Cell_HG_NCalls_CM=0;
// Same thing for LG
    std::vector<float>* Hit_Sensor_Cell_LG_Amplitude_CM=0;
    std::vector<float>* Hit_Sensor_Cell_LG_Amplitude_Error_CM=0;
    std::vector<float>* Hit_Sensor_Cell_LG_Tmax_CM=0;
    std::vector<float>* Hit_Sensor_Cell_LG_Chi2_CM=0;
    std::vector<float>* Hit_Sensor_Cell_LG_Tmax_Error_CM=0;
    std::vector<int>* Hit_Sensor_Cell_LG_Status_CM=0;
    std::vector<int>* Hit_Sensor_Cell_LG_NCalls_CM=0;

    //Open file and set the branch to that particular data...
    std::ostringstream filename( std::ostringstream::ate );
    filename.str("");
    filename<<DATA_LOC<<RUN_TYPE<<"/"<<ENERGY<<"GeV.root";
    if(ENERGY == 0)
    {
        filename.str("");
        filename<<DATA_LOC<<RUN_TYPE<<".root";
    }
    std::cout<<"Opening File "<<filename.str().c_str()<<std::endl;
    TFile *file = TFile::Open(filename.str().c_str());
    TTree *T =  (TTree*)file->Get("pulseshapeplotter/T");



    // T->SetBranchAddress("Hit_Sensor_Event", &Hit_Sensor_Event); For some reason, this doesn't work...
    T->SetBranchAddress("Hit_Sensor_Channel", &Hit_Sensor_Channel);
    T->SetBranchAddress("Hit_Sensor_Layer", &Hit_Sensor_Layer);
    T->SetBranchAddress("Hit_Sensor_Skiroc", &Hit_Sensor_Skiroc);
    T->SetBranchAddress("Hit_Sensor_Cell_Type", &Hit_Sensor_Cell_Type);


    T->SetBranchAddress("Hit_Sensor_Cell_X", &Hit_Sensor_Cell_X);
    T->SetBranchAddress("Hit_Sensor_Cell_Y", &Hit_Sensor_Cell_Y);
    T->SetBranchAddress("Hit_Sensor_Cell_HG", &Hit_Sensor_Cell_HG);
    T->SetBranchAddress("Hit_Sensor_Cell_HG_Sub", &Hit_Sensor_Cell_HG_Sub);
    T->SetBranchAddress("Hit_Sensor_Cell_LG", &Hit_Sensor_Cell_LG);
    T->SetBranchAddress("Hit_Sensor_Cell_LG_Sub", &Hit_Sensor_Cell_LG_Sub);
    T->SetBranchAddress("Hit_Sensor_Cell_ToT_Slow", &Hit_Sensor_Cell_ToT_Slow);
    T->SetBranchAddress("Hit_Sensor_Cell_ToA_Fall", &Hit_Sensor_Cell_ToA_Fall);
    T->SetBranchAddress("Hit_Sensor_Cell_ToA_Rise", &Hit_Sensor_Cell_ToA_Rise);

    T->SetBranchAddress("Hit_Sensor_Cell_HG_Amplitude", &Hit_Sensor_Cell_HG_Amplitude);
    T->SetBranchAddress("Hit_Sensor_Cell_HG_Amplitude_Error", &Hit_Sensor_Cell_HG_Amplitude_Error);
    T->SetBranchAddress("Hit_Sensor_Cell_HG_Tmax", &Hit_Sensor_Cell_HG_Tmax);
    T->SetBranchAddress("Hit_Sensor_Cell_HG_Tmax_Error", &Hit_Sensor_Cell_HG_Tmax_Error);
    T->SetBranchAddress("Hit_Sensor_Cell_HG_Chi2", &Hit_Sensor_Cell_HG_Chi2);
    T->SetBranchAddress("Hit_Sensor_Cell_HG_Status", &Hit_Sensor_Cell_HG_Status);
    T->SetBranchAddress("Hit_Sensor_Cell_HG_NCalls", &Hit_Sensor_Cell_HG_NCalls);

    T->SetBranchAddress("Hit_Sensor_Cell_LG_Amplitude", &Hit_Sensor_Cell_LG_Amplitude);
    T->SetBranchAddress("Hit_Sensor_Cell_LG_Amplitude_Error", &Hit_Sensor_Cell_LG_Amplitude_Error);
    T->SetBranchAddress("Hit_Sensor_Cell_LG_Tmax", &Hit_Sensor_Cell_LG_Tmax);
    T->SetBranchAddress("Hit_Sensor_Cell_LG_Tmax_Error", &Hit_Sensor_Cell_LG_Tmax_Error);
    T->SetBranchAddress("Hit_Sensor_Cell_LG_Chi2", &Hit_Sensor_Cell_LG_Chi2);
    T->SetBranchAddress("Hit_Sensor_Cell_LG_Status", &Hit_Sensor_Cell_LG_Status);
    T->SetBranchAddress("Hit_Sensor_Cell_LG_NCalls", &Hit_Sensor_Cell_LG_NCalls);


    T->SetBranchAddress("Hit_Sensor_Cell_HG_Amplitude_CM", &Hit_Sensor_Cell_HG_Amplitude_CM);
    T->SetBranchAddress("Hit_Sensor_Cell_HG_Amplitude_Error_CM", &Hit_Sensor_Cell_HG_Amplitude_Error_CM);
    T->SetBranchAddress("Hit_Sensor_Cell_HG_Tmax_CM", &Hit_Sensor_Cell_HG_Tmax_CM);
    T->SetBranchAddress("Hit_Sensor_Cell_HG_Tmax_Error_CM", &Hit_Sensor_Cell_HG_Tmax_Error_CM);
    T->SetBranchAddress("Hit_Sensor_Cell_HG_Chi2_CM", &Hit_Sensor_Cell_HG_Chi2_CM);
    T->SetBranchAddress("Hit_Sensor_Cell_HG_Status_CM", &Hit_Sensor_Cell_HG_Status_CM);
    T->SetBranchAddress("Hit_Sensor_Cell_HG_NCalls_CM", &Hit_Sensor_Cell_HG_NCalls_CM);

    T->SetBranchAddress("Hit_Sensor_Cell_LG_Amplitude_CM", &Hit_Sensor_Cell_LG_Amplitude_CM);
    T->SetBranchAddress("Hit_Sensor_Cell_LG_Amplitude_Error_CM", &Hit_Sensor_Cell_LG_Amplitude_Error_CM);
    T->SetBranchAddress("Hit_Sensor_Cell_LG_Tmax_CM", &Hit_Sensor_Cell_LG_Tmax_CM);
    T->SetBranchAddress("Hit_Sensor_Cell_LG_Tmax_Error_CM", &Hit_Sensor_Cell_LG_Tmax_Error_CM);
    T->SetBranchAddress("Hit_Sensor_Cell_LG_Chi2_CM", &Hit_Sensor_Cell_LG_Chi2_CM);
    T->SetBranchAddress("Hit_Sensor_Cell_LG_Status_CM", &Hit_Sensor_Cell_LG_Status_CM);
    T->SetBranchAddress("Hit_Sensor_Cell_LG_NCalls_CM", &Hit_Sensor_Cell_LG_NCalls_CM);


    Int_t Max_Entries = T->GetEntries();

    std::cout<<Max_Entries<<std::endl;




    InitializeHist2D(0,1);
    InitializeHist2D(1,1);

    TH1F* Hist1=new TH1F("Hist1","Hist1",115,-400,600);
    TH2F* XY=new TH2F("XY","Hexaboard Hits",16,-8,8,16,-8,8);

    int count =0;
    for(int entry = 0; entry < Max_Entries ; entry++)
    {


        T->GetEntry(entry);
        //
        if(entry%1000 == 0)
        {
            std::cout<<entry*100/Max_Entries <<"% \t has been completed... \r";
            std::cout.flush();
        }



        for(int i = 0; i < Hit_Sensor_Cell_HG_Sub->size(); i++ )
        {

            board = Hit_Sensor_Layer->at(i);
            skiroc  = Hit_Sensor_Skiroc->at(i);

            // x = Hit_Sensor_Cell_LG_Amplitude->at(i);
            // x = Hit_Sensor_Cell_LG_Amplitude_CM->at(i);
            // x = Hit_Sensor_Cell_LG->at(i) - Hit_Sensor_Cell_LG_Sub->at(i);


            // y = Hit_Sensor_Cell_HG_Amplitude->at(i);
            // y = Hit_Sensor_Cell_HG_Amplitude_CM->at(i);
            // y = Hit_Sensor_Cell_HG->at(i) - Hit_Sensor_Cell_HG_Sub->at(i);
            z = Hit_Sensor_Cell_ToT_Slow->at(i);
            x = Hit_Sensor_Cell_LG->at(i) - Hit_Sensor_Cell_LG_Sub->at(i);
            y = Hit_Sensor_Cell_HG->at(i) - Hit_Sensor_Cell_HG_Sub->at(i);
            // if(Hit_Sensor_Cell_HG_Amplitude_CM->at(i) >100)
            // if(Hit_Sensor_Cell_HG_Amplitude->at(i) <100)
            // if(1)


            if(Hit_Sensor_Cell_Type->at(i) == 2 )
            {

                Hist2D[board][skiroc][1]->Fill(z,x);
                if(board == 2 && skiroc == 0 && entry < 100)
                cout<<"Event:"<<entry<<"\t Channel:"<<Hit_Sensor_Channel->at(i)<<"\t CM_Sub_HG="<<Hit_Sensor_Cell_HG_Sub->at(i)<<"\t CM_Sub_LG="<<Hit_Sensor_Cell_LG_Sub->at(i)<<endl;



                // if(board == 1 && skiroc ==2)
                // if(board == 2 && skiroc ==0)
                // if(1)
                if(board == 2 && skiroc == 0 && entry < 100)
                {
                    // cout<<"Event:"<<entry<<"\t Channel:"<<Hit_Sensor_Channel->at(i)<<"\t CM_Sub_HG="<<Hit_Sensor_Cell_HG->at(i)<<"\t CM_Sub_LG="<<Hit_Sensor_Cell_LG->at(i)<<endl;
                    // Hist2D[Hit_Sensor_Cell_Type->at(i)][0][0]->Fill(x,y);

                    if(1)
                        // if(!(( Hit_Sensor_Cell_X->at(i) >5 && Hit_Sensor_Cell_Y->at(i)<-2) || Hit_Sensor_Cell_X->at(i) >6 ))

                        // if(!(Hit_Sensor_Cell_X->at(i) <-4 && Hit_Sensor_Cell_Y->at(i)>3)) //bad one for 71
                        // if(( Hit_Sensor_Cell_X->at(i) >5 && Hit_Sensor_Cell_Y->at(i)<-2)) // bad one for 55

                        // if(( Hit_Sensor_Cell_X->at(i) <2 && Hit_Sensor_Cell_Y->at(i)<-3)) // normal channels
                    {

                        // if((Hit_Sensor_Cell_X->at(i) <-5&&  Hit_Sensor_Cell_Y->at(i)<-2)) // 1340 The Good Cell Type 2
                        if((Hit_Sensor_Cell_X->at(i) <-5 && Hit_Sensor_Cell_Y->at(i)>2)) // 1193 The Good Cell Type 2
                        {
                            // Hist1->Fill(Hit_Sensor_Cell_HG_Sub->at(i));
                            XY->Fill(Hit_Sensor_Cell_X->at(i),Hit_Sensor_Cell_Y->at(i));
                            Hist1->Fill(Hit_Sensor_Cell_LG_Sub->at(i));
                            Hist2D[2][0][0]->Fill(x,y);
                        }
                    }
                }
            }



        }


    }

    Hist1->SetTitle("");
    TH1F* mg;
    mg = Hist1;
    mg->SetTitle("Common Mode Noise for Cell 1193");
    mg->GetXaxis()->SetTitle("Common Mode Noise on LG ADC");
    mg->GetXaxis()->SetLabelFont(62);
    mg->GetXaxis()->SetTitleFont(62);
    mg->GetXaxis()->SetTitleSize(0.048);
    mg->GetXaxis()->SetTitleOffset(1.0);


    mg->GetYaxis()->SetTitle("Counts");
    mg->GetYaxis()->SetLabelFont(62);
    mg->GetYaxis()->SetTitleFont(62);
    mg->GetYaxis()->SetTitleSize(0.048);
    mg->GetYaxis()->SetTitleOffset(1);
    mg->Draw("");
    gPad->SaveAs("./XY.png");
    //

    //
    // TH2F* mg = XY;
    // mg->SetTitle("Layer 2");
    // mg->GetXaxis()->SetTitle("X (cm)");
    // mg->GetXaxis()->SetLabelFont(62);
    // mg->GetXaxis()->SetTitleFont(62);
    // mg->GetXaxis()->SetTitleSize(0.048);
    // mg->GetXaxis()->SetTitleOffset(1.0);
    //
    //
    // mg->GetYaxis()->SetTitle("Y (cm)");
    // mg->GetYaxis()->SetLabelFont(62);
    // mg->GetYaxis()->SetTitleFont(62);
    // mg->GetYaxis()->SetTitleSize(0.048);
    // mg->GetYaxis()->SetTitleOffset(1);
    // mg->Draw("colztext");
    // gPad->SaveAs("./XY.png");






    std::cout<<"Exiting dataExtractor"<<std::endl;

    return;
}
