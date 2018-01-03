#include<SaturationFinder.h>
void SaturationFinder::Graph_Settings(int board, int skiroc,int type_num)
{
  std::ostringstream os( std::ostringstream::ate );

  TLegend* legend;
  TPaveText* label1;
  TPaveText* label2;
  switch(type_num)
  {
    case 0:
    gPad->DrawFrame(80,-250,1000,y_Max); // (x1,y1,x2,y2)
    mg->Draw("L");



    //Set Graph Axis Titles
    mg->GetXaxis()->SetTitle("Low Gain (ADC Counts)");
    mg->GetXaxis()->SetLabelFont(62);
    mg->GetXaxis()->SetTitleFont(62);
    mg->GetXaxis()->SetTitleSize(0.048);
    mg->GetXaxis()->SetTitleOffset(1.0);


    mg->GetYaxis()->SetTitle("<High Gain (ADC Counts)>");
    mg->GetYaxis()->SetLabelFont(62);
    mg->GetYaxis()->SetTitleFont(62);
    mg->GetYaxis()->SetTitleSize(0.048);
    mg->GetYaxis()->SetTitleOffset(.8);






    A = new TGaxis(1000,0,1000,y_Max,0,100,10,"+L"); //(x1,y1,x2,y2,minrange,maxrange,scale)
    A->SetTitle("Residual in Percent");
    A->SetLabelFont(62);
    A->SetTitleFont(62);
    A->SetTitleOffset(1.0);



    // A->SetLabelSize(0.03);
    // A->SetTitleSize(0.03);
    // A->SetTitleOffset(1.2);
    A->Draw();


    //Creating Legends
    legend = new TLegend(0.5537555,0.1773963,0.8762887,0.5622318,NULL,"brNDC");
    legend->SetTextFont(62);
    legend->SetTextSize(0.03443329);
    legend->AddEntry("X-Profile","<HG> vs LG","p");
    os.str("");
    os<<std::fixed;
    os<<std::setprecision(1);

    os<<"Fit = "<<CF[board][skiroc][type_num]<<"#timesLG ";
    if(CF_Intercept[board][skiroc][type_num] > 0) os<<" + "<<CF_Intercept[board][skiroc][type_num];
    else os<<CF_Intercept[board][skiroc][type_num];


    legend->AddEntry("Fit Function",os.str().c_str(),"l");
    legend->AddEntry("Relative Residual","Residual = #frac{Fit-<HG>}{<HG>}","p");
    os.str("");
    os<<"Residual Threshold = "<<cutoff[type_num]<<"%";
    legend->AddEntry("Cutoff Threshold of the Residual",os.str().c_str(),"l");
    legend->SetTextSize(0.030);
    // legend->SetText
    legend->Draw("same");
    //Setting the Labels
    label2  = new TPaveText(0.09278351,0.9077253,0.3048601,0.9663805,"brNDC");
    label2->SetBorderSize(0);
    label2->SetFillStyle(0);
    label2->SetTextAlign(12);
    label2->SetTextSize(0.080);
    label2->SetTextFont (62);
    label2->AddText("CMS Preliminary");
    label2->Draw("same");

    label1  = new TPaveText(0.5434462,0.9077253,0.6358763,0.9663805,"brNDC");
    label1->SetBorderSize(0);
    label1->SetFillStyle(0);
    label1->SetTextAlign(12);
    label1->SetTextSize(0.059);
    label1->SetTextFont (62);
    label1->AddText("HGCAL test beam, Sept 2017");
    label1->Draw("same");


    // Setting X and Y Grid
    gPad->SetGridx();
    gPad->SetGridy();

    gPad->Update();

    break;

    case 1:
    gPad->DrawFrame(50,-250,1000,y_Max); // (x1,y1,x2,y2)
    mg->Draw("L");
    //Set Graph Axis Titles
    mg->GetXaxis()->SetTitle("TOTSlow");
    mg->GetXaxis()->SetLabelFont(62);
    mg->GetXaxis()->SetTitleFont(62);
    mg->GetXaxis()->SetTitleSize(0.048);
    mg->GetXaxis()->SetTitleOffset(1.0);


    mg->GetYaxis()->SetTitle("<Low Gain (ADC Counts)>");
    mg->GetYaxis()->SetLabelFont(62);
    mg->GetYaxis()->SetTitleFont(62);
    mg->GetYaxis()->SetTitleSize(0.048);
    mg->GetYaxis()->SetTitleOffset(.8);
    A = new TGaxis(1000,0,1000,y_Max,0,100,10,"+L"); //(x1,y1,x2,y2,minrange,maxrange,scale)
    A->SetTitle("Residual in Percent");
    A->SetLabelFont(62);
    A->SetTitleFont(62);
    A->SetTitleOffset(1.0);



    // A->SetLabelSize(0.03);
    // A->SetTitleSize(0.03);
    // A->SetTitleOffset(1.2);
    A->Draw();


    //Creating Legends
    legend = new TLegend(0.5537555,0.1773963,0.8762887,0.5622318,NULL,"brNDC");
    legend->SetTextFont(62);
    legend->SetTextSize(0.03443329);
    legend->AddEntry("X-Profile","<LG> vs TOTSlow","p");
    os.str("");
    os<<std::fixed;
    os<<std::setprecision(1);

    os<<"Fit = "<<CF[board][skiroc][type_num]<<"#timesTOT";
    if(CF_Intercept[board][skiroc][type_num] >= 0) os<<"  + "<<CF_Intercept[board][skiroc][type_num];
    else os<<CF_Intercept[board][skiroc][type_num];


    legend->AddEntry("Fit Function",os.str().c_str(),"l");
    legend->AddEntry("Relative Residual","Residual = #frac{Fit-<LG>}{<LG>}","p");
    os.str("");
    os<<"Residual Threshold = "<<cutoff[type_num]<<"%";
    legend->AddEntry("Cutoff Threshold of the Residual",os.str().c_str(),"l");
    legend->SetTextSize(0.030);
    // legend->SetText
    legend->Draw("same");
    //Setting the Labels
    label2  = new TPaveText(0.09278351,0.9077253,0.3048601,0.9663805,"brNDC");
    label2->SetBorderSize(0);
    label2->SetFillStyle(0);
    label2->SetTextAlign(12);
    label2->SetTextSize(0.080);
    label2->SetTextFont (62);
    label2->AddText("CMS Preliminary");
    label2->Draw("same");

    label1  = new TPaveText(0.5434462,0.9077253,0.6358763,0.9663805,"brNDC");
    label1->SetBorderSize(0);
    label1->SetFillStyle(0);
    label1->SetTextAlign(12);
    label1->SetTextSize(0.059);
    label1->SetTextFont (62);
    label1->AddText("HGCAL test beam, Sept 2017");
    label1->Draw("same");


    // Setting X and Y Grid
    gPad->SetGridx();
    gPad->SetGridy();

    gPad->Update();

    break;

  }
}
