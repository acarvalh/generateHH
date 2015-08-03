#include <iostream>
#include <sstream>
#include <fstream>

#include "TStopwatch.h"

#include "TFile.h"
#include "TH1D.h"
#include "TProfile.h"
#include "TCanvas.h"
#include "TString.h"
#include "TStyle.h"
#include "TChain.h"
#include "TH2.h"
#include "TH1.h"
#include "TF1.h"
#include "TTree.h"
#include "TKey.h"
#include "TMath.h"
#include "TRandom.h"
#include "TRandom3.h"
#include "Riostream.h"
#include "TVirtualFitter.h"
#include <stdio.h>
#include <math.h>

#include "Math/GoFTest.h"

void plot_clusters_mincg(int Nclu=20) {
////////////////////////////////////////////////////
    TStyle *defaultStyle = new TStyle("defaultStyle","Default Style");
    //gStyle->SetOptStat(0);
    //  defaultStyle->SetOptStat(0000);
    //  defaultStyle->SetOptFit(000); 
    //  defaultStyle->SetPalette(1);
    ////////////////////////
    defaultStyle->SetOptStat(0); // remove info box
    /////// pad ////////////
    defaultStyle->SetPadBorderMode(1);
    defaultStyle->SetPadBorderSize(1);
    defaultStyle->SetPadColor(0);
    defaultStyle->SetPadTopMargin(0.18);
    defaultStyle->SetPadBottomMargin(0.2);
    defaultStyle->SetPadLeftMargin(0.18);
    defaultStyle->SetPadRightMargin(1.18);
    /////// canvas /////////
    defaultStyle->SetCanvasBorderMode(1);
    defaultStyle->SetCanvasColor(0);
    //  defaultStyle->SetCanvasDefH(600);
    //  defaultStyle->SetCanvasDefW(600);
    /////// frame //////////
    defaultStyle->SetFrameBorderMode(1);
    defaultStyle->SetFrameBorderSize(1);
    defaultStyle->SetFrameFillColor(0); 
    defaultStyle->SetFrameLineColor(1);
    /////// label //////////
    //  defaultStyle->SetLabelOffset(0.005,"XY");
    //  defaultStyle->SetLabelSize(0.05,"XY");
    //defaultStyle->SetLabelFont(46,"XY");
    /////// title //////////
    //defaultStyle->SetTitleW(0.6);
    //defaultStyle->GetTitleBorderSize(0);
    //  defaultStyle->SetTitleOffset(1.1,"X");
    //  defaultStyle->SetTitleSize(0.01,"X");
    //  defaultStyle->SetTitleOffset(1.25,"Y");
    //  defaultStyle->SetTitleSize(0.05,"Y");
    //defaultStyle->SetTitleFont(42, "XYZ");
    /////// various ////////
    defaultStyle->SetNdivisions(303,"Y");
    defaultStyle->SetTitleFillColor(0);//SetTitleFillStyle(0, "Z");
    defaultStyle->SetTitleX(0.4);
    //defaultStyle->SetTitleY(0.1);
    //defaultStyle->SetTitleBorderSize(-0.1);  // For the axis titles:
    
    //    defaultStyle->SetTitleColor(1, "XYZ");
    //    defaultStyle->SetTitleFont(42, "XYZ");
    defaultStyle->SetTitleSize(0.1, "XYZ");
    
    // defaultStyle->SetTitleYSize(Float_t size = 0.02);
    //defaultStyle->SetTitleXOffset(0.9);
    //defaultStyle->SetTitleYOffset(1.05);
    // defaultStyle->SetTitleOffset(1.1, "Y"); // Another way to set the Offset
    
    // For the axis labels:
    defaultStyle->SetLabelColor(1, "XYZ");
    //defaultStyle->SetLabelFont(46, "XYZ");
    // defaultStyle->SetLabelOffset(0.007, "XYZ");
    defaultStyle->SetLabelSize(0.08, "XYZ");
    
    // For the axis:
    //    defaultStyle->SetAxisColor(1, "XYZ");
    defaultStyle->SetStripDecimals(kTRUE);
    defaultStyle->SetTickLength(0.03, "XYZ");
    defaultStyle->SetNdivisions(510, "XYZ");
    defaultStyle->cd();
    //////////////////////////////////////////////
    // This is to plot the c2 X kt plane , the minimal cg and c2g
    // no isolines of cross sections !
    //////////////////////////////////////////////
    TLegend *leg = new TLegend(0.25,0.2,0.95,0.8);
    leg->SetFillColor(16);
    leg->SetNColumns(5);
    leg->SetFillStyle(0);
    leg->SetBorderSize(0.2);
    leg->SetTextSize(0.07);
    ///////////////////////////////////////////////////////
    // legend / color / shape to 10 / 15 /20
    // do for 20 first
    const char* lege20[20]={" 1"," 2"," 3"," 4"," 5"," 6"," 7"," 8"," 9"," 10",
                            " 11"," 12"," 13"," 14"," 15"," 16"," 17"," 18"," 19"," 20"}; 
    ///////////////////////////////////////////////////////
    double L[1483];
    double y[1483];
    double c[1483];
    double cg[1483];
    double c2g[1483];
    //////////////
    ifstream parpoints("list_ascii_13TeV_1483.txt");
    for (int i=0; i<1483; i++) {
      parpoints >> L[i] >> y[i] >> c[i] >> cg[i] >> c2g[i];
      cout << i<< " " << L[i] << " " << y[i] << " " << c[i] << " " << cg[i] << " " << c2g[i] << endl;
    }
    parpoints.close();
    /////////////////////////////////////////////
    // by now do only 20 clusters
    ifstream cluster_20("LogP/clustering_nev20k_Nclu20_50_5.asc");     
    ifstream cluster_13("LogP/clustering_nev20k_Nclu13_50_5.asc");   
    /////////////////////////////////////////////
    // color and geometric codes
    int mc[20]= {1, 2, 3, 4, 5, 6, 7, 8, 2, 15, 28, 30, 33, 38, 40, 41, 44, 45, 46, 48};
//    int mt[20]= {22, 20, 34, 20, 23, 34, 22, 34, 23, 23, 23, 22, 22, 23, 20, 20, 22, 23, 20, 20 }; // style
//    int mt[20]= {22,34,34,23,23,22,20,23,23,20,23,34,22}; // 13
   int mt[20]= {34,20,34,34,23,20,34,23,23,23,20,20,23,22,23,23,20,23,34,22}; // 20
    ///////////////////////////////////////////////////
    // define the planes
    TH2D * L15[20];
    TH2D * L10[20]; 
    TH2D * L5[20]; 
    TH2D * L24[20];
    TH2D * L1[20];
    TH2D * Lm15[20];
    TH2D * Lm10[20]; 
    TH2D * Lm5[20]; 
    TH2D * Lm24[20];
    //
    TH2D * hL15[20];
    TH2D * hL10[20]; 
    TH2D * hL5[20]; 
    TH2D * hL24[20];    
    TH2D * hL1[20];
    TH2D * hLm15[20];
    TH2D * hLm10[20]; 
    TH2D * hLm5[20]; 
    TH2D * hLm24[20];
    char name[100];
    for (int i=0; i<20; i++) {
        sprintf (name, "L15%d", i);
        L15[i] = new TH2D (name,"", 500, -6., 8., 500, 0., 3. );//#kappa_{#lambda} = 15        
        sprintf (name, "L10%d", i);
        L10[i] = new TH2D (name,"", 500, -6., 8., 500, 0., 3. ); 
        sprintf (name, "L5%d", i);
        L5[i] = new TH2D (name,"", 500, -6., 8., 500, 0., 3. );
        sprintf (name, "L24%d", i);
        L24[i] = new TH2D (name,"", 500, -6., 8., 500, 0., 3. );
        sprintf (name, "L1%d", i);
        L1[i] = new TH2D (name,"", 500, -6., 8., 500, 0., 3. );
        //
        sprintf (name, "Lm15%d", i);
        Lm15[i] = new TH2D (name,"", 500, -6., 8., 500, 0., 3. );
        sprintf (name, "Lm10%d", i);
        Lm10[i] = new TH2D (name,"", 500, -6., 8., 500, 0., 3. ); 
        sprintf (name, "Lm5%d", i);
        Lm5[i] = new TH2D (name,"", 500, -6., 8., 500, 0., 3. );
        sprintf (name, "Lm24%d", i);
        Lm24[i] = new TH2D (name,"", 500, -6., 8., 500, 0., 3. );  
        //
        sprintf (name, "hL15%d", i);
        hL15[i] = new TH2D (name,"", 500, -6., 8., 500, 0., 3. );
        sprintf (name, "hL10%d", i);
        hL10[i] = new TH2D (name,"", 500, -6., 8., 500, 0., 3. ); 
        sprintf (name, "hL5%d", i);
        hL5[i] = new TH2D (name,"", 500, -6., 8., 500, 0., 3. );
        sprintf (name, "hL24%d", i);
        hL24[i] = new TH2D (name,"", 500, -6., 8., 500, 0., 3. );
        sprintf (name, "hL1%d", i);
        hL1[i] = new TH2D (name,"", 500, -6., 8., 500, 0., 3. );
        //
        sprintf (name, "hLm15%d", i);
        hLm15[i] = new TH2D (name,"", 500, -6., 8., 500, 0., 3. );
        sprintf (name, "hLm10%d", i);
        hLm10[i] = new TH2D (name,"", 500, -6., 8., 500, 0., 3. ); 
        sprintf (name, "hLm5%d", i);
        hLm5[i] = new TH2D (name,"", 500, -6., 8., 500, 0., 3. );
        sprintf (name, "hLm24%d", i);
        hLm24[i] = new TH2D (name,"", 500, -6., 8., 500, 0., 3. );
    }// close define histos
    int isamp;
    int head20[20]= {263,826,1073,235,339,307,1182,5,298,408,810,945,1209,677,98,1045,717,1221,983,175}; 
    int head13[20]= {826, 348, 762, 298, 675, 804, 945, 335, 700, 717, 1221, 983, 1195};   
    int head[20];
    for (int i=0; i<Nclu; i++) {
        if (Nclu==20) {
            head[i]=head20[i];
        } else if (Nclu==13) {
            head[i]=head13[i];
        } else if (Nclu==10) {
            head[i]=head10[i];
        }
    }// close do heads
    /////////////////////////////////////////
    // fill the histos == only with cgs diff of 0
    int iclu=-1;
    for (int i=0; i<1483; i++) {
        if (Nclu==20) cluster_20 >> isamp;
        else if (Nclu==13) cluster_13 >> isamp;
        else if (Nclu==10) cluster_10 >> isamp;
        //
        for (int j=0; j<Nclu; j++) { if (isamp==head[j]) {cout << "head = " << isamp << endl; iclu++;}} 
        //
        if (L[isamp]==15 && ( cg[isamp]!=0 || c2g[isamp]!=0 )) {
           L15[iclu]->Fill(c[isamp],y[isamp]);
           for (int j=0; j<Nclu; j++) { if (isamp==head[j]) hL15[iclu]->Fill(c[isamp],y[isamp]);};
        } else if (L[isamp]==10 && (cg[isamp]!=0 || c2g[isamp]!=0)) {
            L10[iclu]->Fill(c[isamp],y[isamp]);
            for (int j=0; j<Nclu; j++) { if (isamp==head[j]) hL10[iclu]->Fill(c[isamp],y[isamp]);};
        } else if (L[isamp]==5 && (cg[isamp]!=0 || c2g[isamp]!=0)) {
            L5[iclu]->Fill(c[isamp],y[isamp]);
            for (int j=0; j<Nclu; j++) { if (isamp==head[j]) hL5[iclu]->Fill(c[isamp],y[isamp]);};
        } else if (L[isamp]==2.4 && (cg[isamp]!=0 || c2g[isamp]!=0)) {
            L24[iclu]->Fill(c[isamp],y[isamp]);
            for (int j=0; j<Nclu; j++) { if (isamp==head[j]) hL24[iclu]->Fill(c[isamp],y[isamp]);};
        } else if (
                   (L[isamp]==1 && (cg[isamp]!=0 && c2g[isamp]!=0) && !(c[isamp]==0 && y[isamp] ==1) )
                   || (L[isamp]==1 && (cg[isamp]==0.0971 && c2g[isamp]==0.00858) && (c[isamp]==0 && y[isamp] ==1) )
                   ) {
            L1[iclu]->Fill(c[isamp],y[isamp]);
            for (int j=0; j<Nclu; j++) { if (isamp==head[j]) hL1[iclu]->Fill(c[isamp],y[isamp]);};
        } // positive
        else if (L[isamp]==-15 && (cg[isamp]!=0 || c2g[isamp]!=0)) {
            Lm15[iclu]->Fill(c[isamp],y[isamp]);
            for (int j=0; j<Nclu; j++) { if (isamp==head[j]) hLm15[iclu]->Fill(c[isamp],y[isamp]);};
        } else if (L[isamp]==-10 && (cg[isamp]!=0 || c2g[isamp]!=0)) {
            Lm10[iclu]->Fill(c[isamp],y[isamp]);
            for (int j=0; j<Nclu; j++) { if (isamp==head[j]) hL10[iclu]->Fill(c[isamp],y[isamp]);};
        } else if (L[isamp]==-5 && (cg[isamp]!=0 || c2g[isamp]!=0)) {
            Lm5[iclu]->Fill(c[isamp],y[isamp]);
            for (int j=0; j<Nclu; j++) { if (isamp==head[j]) hLm5[iclu]->Fill(c[isamp],y[isamp]);};
        } else if (L[isamp]==-2.4 && (cg[isamp]!=0 || c2g[isamp]!=0)) {
            Lm24[iclu]->Fill(c[isamp],y[isamp]);
            for (int j=0; j<Nclu; j++) { if (isamp==head[j]) hL24[iclu]->Fill(c[isamp],y[isamp]);};
        } 
    } // close for samples
    ////////////////////////////////////////
      char nameplot[40];
    TCanvas * C1 = new TCanvas ("C1","",1250,550);
    C1->Divide(5,2,0,0);   
    //C1.SetBorderMode(0); 
    //C1.SetTopMargin(0.1);
    //////////////////////////////////////
    C1->cd(1);
        C1_1->SetTicks(2,2);
    C1_1->SetTopMargin(0.1);
    for (int iclu=0; iclu<Nclu; iclu++) {
        L1[iclu]->GetYaxis()->SetTitle("c_{2}");
        L1[iclu]->GetYaxis()->SetTitle("#kappa_{t}");
        L1[iclu]->SetLineColor(mc[iclu]);
        L1[iclu]->SetMarkerColor(mc[iclu]);
        L1[iclu]->SetMarkerStyle(mt[iclu]);
        L1[iclu]->SetMarkerSize(1.5);
        if (iclu==0) {
            L1[iclu]->Draw("P");
        } else {
            L1[iclu]->Draw("PSAME");
        }
        leg->AddEntry(L1[iclu], lege20[iclu], "P");
        hL1[iclu]->SetMarkerColor(mc[iclu]);
        hL1[iclu]->SetMarkerStyle(mt[iclu]);
        hL1[iclu]->SetMarkerSize(2.5);
        hL1[iclu]->Draw("PSAME");
    }
    //sprintf(nameplot,"clusters5D_L15_%d.png",Nclu);
    TLatex* text = new TLatex();
    text->SetTextSize(0.08);
    text->DrawLatex(-5.2,2.7,"#kappa_{#lambda} = 1");
    text->Draw("same");
    //////////////////////////////////////
    C1->cd(2);    
        C1_2->SetTicks(2,2);
    C1_2->SetTopMargin(0.1);
    for (int iclu=0; iclu<Nclu; iclu++) {
        L24[iclu]->GetYaxis()->SetTitle("#kappa_{t}");
        L24[iclu]->SetLineColor(mc[iclu]);
        L24[iclu]->SetMarkerColor(mc[iclu]);
        L24[iclu]->SetMarkerStyle(mt[iclu]);
        L24[iclu]->SetMarkerSize(1.5);
        if (iclu==0) {
            L24[iclu]->Draw("P");
        } else {
            L24[iclu]->Draw("PSAME");
        }
        //leg->AddEntry(L15[iclu], lege20[iclu], "P");
        hL24[iclu]->SetMarkerColor(mc[iclu]);
        hL24[iclu]->SetMarkerStyle(mt[iclu]);
        hL24[iclu]->SetMarkerSize(2.5);
        hL24[iclu]->Draw("PSAME");
    }
    //sprintf(nameplot,"clusters5D_L15_%d.png",Nclu);
    //leg->Draw("same");    
    TLatex* text = new TLatex();
    text->SetTextSize(0.08);
    text->DrawLatex(-5.2,2.7,"#kappa_{#lambda} = 2.4");
    text->Draw("same");
    //////////////////////////////////////
    C1->cd(3);
    C1_3->SetTopMargin(0.1);
    C1_3->SetTicks(2,2);
    for (int iclu=0; iclu<Nclu; iclu++) {
        L5[iclu]->SetLineColor(mc[iclu]);
        L5[iclu]->SetMarkerColor(mc[iclu]);
        L5[iclu]->SetMarkerStyle(mt[iclu]);
        L5[iclu]->SetMarkerSize(1.5);
        if (iclu==0) {
            L5[iclu]->Draw("P");
        } else {
            L5[iclu]->Draw("PSAME");
        }
        hL5[iclu]->SetMarkerColor(mc[iclu]);
        hL5[iclu]->SetMarkerStyle(mt[iclu]);
        hL5[iclu]->SetMarkerSize(2.5);
        hL5[iclu]->Draw("PSAME");
    }
    //leg->Draw("same");
    TLatex* text = new TLatex();
    text->SetTextSize(0.08);
    text->DrawLatex(-5.2,2.7,"#kappa_{#lambda} = 5");
    text->Draw("same");
    //////////////////////////////////////
    C1->cd(4);
    C1_4->SetTopMargin(0.1);
    C1_4->SetTicks(2,2);
    for (int iclu=0; iclu<Nclu; iclu++) {
        L10[iclu]->SetLineColor(mc[iclu]);
        L10[iclu]->SetMarkerColor(mc[iclu]);
        L10[iclu]->SetMarkerStyle(mt[iclu]);
        L10[iclu]->SetMarkerSize(1.5);
        if (iclu==0) {
            L10[iclu]->Draw("P");
        } else {
            L10[iclu]->Draw("PSAME");
        }
        hL10[iclu]->SetMarkerColor(mc[iclu]);
        hL10[iclu]->SetMarkerStyle(mt[iclu]);
        hL10[iclu]->SetMarkerSize(2.5);
        hL10[iclu]->Draw("PSAME");
    }
    //leg->Draw("same");
    TLatex* text = new TLatex();
    text->SetTextSize(0.08);
    text->DrawLatex(-5.2,2.7,"#kappa_{#lambda} = 10");
    text->Draw("same");
    //////////////////////////////////////
    C1->cd(5);
        C1_5->SetTopMargin(0.1);
    C1_5->SetRightMargin(0.1);
    C1_5->SetTicks(2,2);
    for (int iclu=0; iclu<Nclu; iclu++) {
        L15[iclu]->GetYaxis()->SetTitle("#kappa_{t}");
        L15[iclu]->SetLineColor(mc[iclu]);
        L15[iclu]->SetMarkerColor(mc[iclu]);
        L15[iclu]->SetMarkerStyle(mt[iclu]);
        L15[iclu]->SetMarkerSize(1.5);
        if (iclu==0) {
            //hL15[iclu]->Draw("Y+");
            L15[iclu]->Draw("P");
        } else {
            L15[iclu]->Draw("PSAME");
        }
        hL15[iclu]->SetMarkerColor(mc[iclu]);
        hL15[iclu]->SetMarkerStyle(mt[iclu]);
        hL15[iclu]->SetMarkerSize(2.5);
        hL15[iclu]->Draw("PSAME");
    }
    // seccond axis
    //TGaxis *axis6 = new TGaxis(8,0,8,3,0,3,50510,"+L");
    //axis6->SetName("axis6");
    //axis6->SetLabelSize(0.1);
    //axis6->SetTextFont(72);
    //axis6->Draw("same");    
    //leg->Draw("same");
    TLatex* text = new TLatex();
    text->SetTextSize(0.08);
    text->DrawLatex(-5.2,2.7,"#kappa_{#lambda} = 15");
    text->Draw("same");
    //////////////////////////////////////
    C1->cd(6);
        C1_6->SetTicks(2,2);
    TLatex* text1 = new TLatex();
    text1->SetTextSize(0.07);
    text1->DrawLatex(0.2,0.9,"LHC13");
    text1->Draw("same");
    text1->SetTextSize(0.06);
    text1->DrawLatex(0.2,0.81,"(c_{g},c_{2g}) < (1,1) when min(#sigma_{hh})");
    text1->Draw("same");
    leg->Draw("P");   
    //////////////////////////////////
    // negative
    //////////////////////////////////
    C1->cd(7);
        C1_7->SetTicks(2,2);
    for (int iclu=0; iclu<Nclu; iclu++) {
        Lm24[iclu]->SetLineColor(mc[iclu]);
        Lm24[iclu]->SetMarkerColor(mc[iclu]);
        Lm24[iclu]->SetMarkerStyle(mt[iclu]);
        Lm24[iclu]->SetMarkerSize(1.5);
        if (iclu==0) {
            Lm24[iclu]->Draw("P");
        } else {
            Lm24[iclu]->Draw("PSAME");
        }
        //leg->AddEntry(Lm15[iclu], lege20[iclu], "P");
        hLm24[iclu]->SetMarkerColor(mc[iclu]);
        hLm24[iclu]->SetMarkerStyle(mt[iclu]);
        hLm24[iclu]->SetMarkerSize(2.5);
        hLm24[iclu]->Draw("PSAME");
    }
    //sprintf(nameplot,"clusters5D_L15_%d.png",Nclu);
    //leg->Draw("same");
    TLatex* text = new TLatex();
    text->SetTextSize(0.08);
    text->DrawLatex(-5.2,2.7,"#kappa_{#lambda} = -2.4");
    text->Draw("same");
    //////////////////////////////////////
    C1->cd(8);
        C1_8->SetTicks(2,2);
    for (int iclu=0; iclu<Nclu; iclu++) {
        Lm5[iclu]->SetLineColor(mc[iclu]);
        Lm5[iclu]->SetMarkerColor(mc[iclu]);
        Lm5[iclu]->SetMarkerStyle(mt[iclu]);
        Lm5[iclu]->SetMarkerSize(1.5);
        if (iclu==0) {
            Lm5[iclu]->Draw("P");
        } else {
            Lm5[iclu]->Draw("PSAME");
        }
        hLm5[iclu]->SetMarkerColor(mc[iclu]);
        hLm5[iclu]->SetMarkerStyle(mt[iclu]);
        hLm5[iclu]->SetMarkerSize(2.5);
        hLm5[iclu]->Draw("PSAME");
    }
    //leg->Draw("same");
    TLatex* text = new TLatex();
    text->SetTextSize(0.08);
    text->DrawLatex(-5.2,2.7,"#kappa_{#lambda} = -5");
    text->Draw("same");
    //////////////////////////////////////
    C1->cd(9);
        C1_9->SetTicks(2,2);
    for (int iclu=0; iclu<Nclu; iclu++) {
        Lm10[iclu]->SetLineColor(mc[iclu]);
        Lm10[iclu]->SetMarkerColor(mc[iclu]);
        Lm10[iclu]->SetMarkerStyle(mt[iclu]);
        Lm10[iclu]->SetMarkerSize(1.5);
        if (iclu==0) {
            Lm10[iclu]->Draw("P");
        } else {
            Lm10[iclu]->Draw("PSAME");
        }
        hLm10[iclu]->SetMarkerColor(mc[iclu]);
        hLm10[iclu]->SetMarkerStyle(mt[iclu]);
        hLm10[iclu]->SetMarkerSize(2.5);
        hLm10[iclu]->Draw("PSAME");
    }
    //leg->Draw("same");
    TLatex* text = new TLatex();
    text->SetTextSize(0.08);
    text->DrawLatex(-5.2,2.7,"#kappa_{#lambda} = -10");
    text->Draw("same");
    //////////////////////////////////////
    C1->cd(10);
        C1_10->SetRightMargin(0.1);
        C1_10->SetTicks(2,2);
    for (int iclu=0; iclu<Nclu; iclu++) {
        Lm15[iclu]->SetLineColor(mc[iclu]);
        Lm15[iclu]->SetMarkerColor(mc[iclu]);
        Lm15[iclu]->SetMarkerStyle(mt[iclu]);
        Lm15[iclu]->SetMarkerSize(1.5);
        Lm15[iclu]->GetXaxis()->SetTitle("c_{2}");
        if (iclu==0) {
            Lm15[iclu]->Draw("P");
        } else {
            Lm15[iclu]->Draw("PSAME");
        }
        hLm15[iclu]->SetMarkerColor(mc[iclu]);
        hLm15[iclu]->SetMarkerStyle(mt[iclu]);
        hLm15[iclu]->SetMarkerSize(2.5);
        hLm15[iclu]->Draw("PSAME");
    }
    //leg->Draw("same");
    text->SetTextSize(0.08);
    text->DrawLatex(-5.2,2.7,"#kappa_{#lambda} = -15");
    text->Draw("same");
    //////////////////////////////////
    sprintf(nameplot,"clusters5D_clu_%d.png",Nclu);    
    C1->Print(nameplot);
    sprintf(nameplot,"clusters5D_clu_%d.pdf",Nclu);    
    C1->Print(nameplot);    
}
/*
  

    

  char name[100];
  for (int i=0; i<20; i++) {
    sprintf (name, "L15%d", i);
    L15[i] = new TH2D (name,"c = -3", 500, -20., 20., 500, 0., 3. );
    sprintf (name, "clu_m2%d", i);
    clu_m2[i] = new TH2D (name,"c = -2", 500, -20., 20., 500, 0., 3. );
    sprintf (name, "clu_m1%d", i);
    clu_m1[i] = new TH2D (name,"c = -1", 500, -20., 20., 500, 0., 3. );
    sprintf (name, "clu_m05%d", i);
    clu_m05[i] = new TH2D (name,"c = -0.5", 500, -20., 20., 500, 0., 3. );
    sprintf (name, "clu_0%d", i);
    clu_0[i] = new TH2D (name,"", 500, -20., 20., 500, 0., 3. );//c_{2} = 0
    sprintf (name, "clu_p05%d", i);
    clu_p05[i] = new TH2D (name,"c = 0.5", 500, -20., 20., 500, 0., 3. );
    sprintf (name, "clu_p1%d", i);
    clu_p1[i] = new TH2D (name,"c = 1", 500, -20., 20., 500, 0., 3. );
    sprintf (name, "clu_p2%d", i);
    clu_p2[i] = new TH2D (name,"c = 2", 500, -20., 20., 500, 0., 3. );
    sprintf (name, "clu_p3%d", i);
    clu_p3[i] = new TH2D (name,"c = 3", 500, -20., 20., 500, 0., 3. );
    //
    sprintf (name, "hL15%d", i);
    hL15[i] = new TH2D (name,"c = -3", 500, -20., 20., 500, 0., 3. );
    sprintf (name, "hclu_m2%d", i);
    hclu_m2[i] = new TH2D (name,"c = -2", 500, -20., 20., 500, 0., 3. );
    sprintf (name, "hclu_m1%d", i);
    hclu_m1[i] = new TH2D (name,"c = -1", 500, -20., 20., 500, 0., 3. );
    sprintf (name, "hclu_m05%d", i);
    hclu_m05[i] = new TH2D (name,"c = -0.5", 500, -20., 20., 500, 0., 3. );
    sprintf (name, "hclu_0%d", i);
    hclu_0[i] = new TH2D (name,"c = 0", 500, -20., 20., 500, 0., 3. );
    sprintf (name, "hclu_p05%d", i);
    hclu_p05[i] = new TH2D (name,"c = 0.5", 500, -20., 20., 500, 0., 3. );
    sprintf (name, "hclu_p1%d", i);
    hclu_p1[i] = new TH2D (name,"c = 1", 500, -20., 20., 500, 0., 3. );
    sprintf (name, "hclu_p2%d", i);
    hclu_p2[i] = new TH2D (name,"c = 2", 500, -20., 20., 500, 0., 3. );
    sprintf (name, "hclu_p3%d", i);
    hclu_p3[i] = new TH2D (name,"c = 3", 500, -20., 20., 500, 0., 3. );
  }

  int isamp;
  int head20[20]= { 143, 224, 43, 200, 343, 190, 290, 60, 354, 191, 175, 594, 398, 
		    130, 265, 145, 314, 327, 443, 496};
  int head15[15]= { 224, 165, 343, 190, 60, 191, 365, 364, 130, 291, 145, 314, 327, 443, 496};
  int head10[10]= { 343, 190, 60, 364, 291, 217, 222, 335, 443, 338};
  int head[20];
  for (int i=0; i<Nclu; i++) {
    if (Nclu==20) {
      head[i]=head20[i];
    } else if (Nclu==15) {
      head[i]=head15[i];
    } else if (Nclu==10) {
      head[i]=head10[i];
    }
  }

  int iclu=-1;
  for (int i=0; i<1483; i++) {
    if (Nclu==20) {
      cluster_20 >> isamp;
    } else if (Nclu==15) {
      cluster_15 >> isamp;
    } else if (Nclu==10) {
      cluster_10 >> isamp;
    }
    for (int j=0; j<Nclu; j++) {
      if (isamp==head[j]) {
	cout << "head = " << isamp << endl;
	iclu++;
      }
    }
    // new cluster
    if (c[isamp]==-3) {
      L15[iclu]->Fill(L[isamp],y[isamp]);
      for (int j=0; j<Nclu; j++) { if (isamp==head[j]) hL15[iclu]->Fill(L[isamp],y[isamp]);};
    } else if (c[isamp]==-2) {
      clu_m2[iclu]->Fill(L[isamp],y[isamp]);
      for (int j=0; j<Nclu; j++) { if (isamp==head[j]) hclu_m2[iclu]->Fill(L[isamp],y[isamp]);};
    } else if (c[isamp]==-1) {
      clu_m1[iclu]->Fill(L[isamp],y[isamp]);
      for (int j=0; j<Nclu; j++) { if (isamp==head[j]) hclu_m1[iclu]->Fill(L[isamp],y[isamp]);};
    } else if (c[isamp]==-0.5) {
      clu_m05[iclu]->Fill(L[isamp],y[isamp]);
      for (int j=0; j<Nclu; j++) { if (isamp==head[j]) hclu_m05[iclu]->Fill(L[isamp],y[isamp]);};
    } else if (c[isamp]==0) {
      clu_0[iclu]->Fill(L[isamp],y[isamp]);
      for (int j=0; j<Nclu; j++) { if (isamp==head[j]) hclu_0[iclu]->Fill(L[isamp],y[isamp]);};
    } else if (c[isamp]==0.5) {
      clu_p05[iclu]->Fill(L[isamp],y[isamp]);
      for (int j=0; j<Nclu; j++) { if (isamp==head[j]) hclu_p05[iclu]->Fill(L[isamp],y[isamp]);};
    } else if (c[isamp]==1) {
      clu_p1[iclu]->Fill(L[isamp],y[isamp]);
      for (int j=0; j<Nclu; j++) { if (isamp==head[j]) hclu_p1[iclu]->Fill(L[isamp],y[isamp]);};
    } else if (c[isamp]==2) {
      clu_p2[iclu]->Fill(L[isamp],y[isamp]);
      for (int j=0; j<Nclu; j++) { if (isamp==head[j]) hclu_p2[iclu]->Fill(L[isamp],y[isamp]);};
    } else if (c[isamp]==3) {
      clu_p3[iclu]->Fill(L[isamp],y[isamp]);
      for (int j=0; j<Nclu; j++) { if (isamp==head[j]) hclu_p3[iclu]->Fill(L[isamp],y[isamp]);};
    }
  }

  TCanvas * C1 = new TCanvas ("C1","",600,600);
  C1->Divide(3,3);
  C1->cd(1);
  for (int iclu=0; iclu<Nclu; iclu++) {
    L15[iclu]->SetLineColor(mc[iclu]);
    L15[iclu]->SetMarkerColor(mc[iclu]);
    L15[iclu]->SetMarkerStyle(mt[iclu]);
    L15[iclu]->SetMarkerSize(1.5);
    if (iclu==0) {
      L15[iclu]->Draw("P");
    } else {
      L15[iclu]->Draw("PSAME");
    }
    hL15[iclu]->SetMarkerColor(mc[iclu]);
    hL15[iclu]->SetMarkerStyle(mt[iclu]);
    hL15[iclu]->SetMarkerSize(2.5);
    hL15[iclu]->Draw("PSAME");
  }
  C1->cd(2);
  for (int iclu=0; iclu<Nclu; iclu++) {
    clu_m2[iclu]->SetLineColor(mc[iclu]);
    clu_m2[iclu]->SetMarkerColor(mc[iclu]);
    clu_m2[iclu]->SetMarkerStyle(mt[iclu]);
    clu_m2[iclu]->SetMarkerSize(1.5);
    if (iclu==0) {
      clu_m2[iclu]->Draw("P");
    } else {
      clu_m2[iclu]->Draw("PSAME");
    }
    hclu_m2[iclu]->SetMarkerColor(mc[iclu]);
    hclu_m2[iclu]->SetMarkerStyle(mt[iclu]);
    hclu_m2[iclu]->SetMarkerSize(2.5);
    hclu_m2[iclu]->Draw("PSAME");
  }
  C1->cd(3);
  for (int iclu=0; iclu<Nclu; iclu++) {
    clu_m1[iclu]->SetLineColor(mc[iclu]);
    clu_m1[iclu]->SetMarkerColor(mc[iclu]);
    clu_m1[iclu]->SetMarkerStyle(mt[iclu]);
    clu_m2[iclu]->SetMarkerSize(1.5);
    if (iclu==0) {
      clu_m1[iclu]->Draw("P");
    } else {
      clu_m1[iclu]->Draw("PSAME");
    }
    hclu_m1[iclu]->SetMarkerColor(mc[iclu]);
    hclu_m1[iclu]->SetMarkerStyle(mt[iclu]);
    hclu_m1[iclu]->SetMarkerSize(2.5);
    hclu_m1[iclu]->Draw("PSAME");
  }
  C1->cd(4);
  for (int iclu=0; iclu<Nclu; iclu++) {
    clu_m05[iclu]->SetLineColor(mc[iclu]);
    clu_m05[iclu]->SetMarkerColor(mc[iclu]);
    clu_m05[iclu]->SetMarkerStyle(mt[iclu]);
    clu_m05[iclu]->SetMarkerSize(1.5);
    if (iclu==0) {
      clu_m05[iclu]->Draw("P");
    } else {
      clu_m05[iclu]->Draw("PSAME");
    }
    hclu_m05[iclu]->SetMarkerColor(mc[iclu]);
    hclu_m05[iclu]->SetMarkerStyle(mt[iclu]);
    hclu_m05[iclu]->SetMarkerSize(2.5);
    hclu_m05[iclu]->Draw("PSAME");
  }
  C1->cd(5);
  for (int iclu=0; iclu<Nclu; iclu++) {
    clu_0[iclu]->SetLineColor(mc[iclu]);
    clu_0[iclu]->SetMarkerColor(mc[iclu]);
    clu_0[iclu]->SetMarkerStyle(mt[iclu]);
    clu_0[iclu]->SetMarkerSize(1.5);
    if (iclu==0) {
      clu_0[iclu]->Draw("P");
    } else {
      clu_0[iclu]->Draw("PSAME");
    }
    hclu_0[iclu]->SetMarkerColor(mc[iclu]);
    hclu_0[iclu]->SetMarkerStyle(mt[iclu]);
    hclu_0[iclu]->SetMarkerSize(2.5);
    hclu_0[iclu]->Draw("PSAME");
  }
  C1->cd(6);
  for (int iclu=0; iclu<Nclu; iclu++) {
    clu_p05[iclu]->SetLineColor(mc[iclu]);
    clu_p05[iclu]->SetMarkerColor(mc[iclu]);
    clu_p05[iclu]->SetMarkerStyle(mt[iclu]);
    clu_p05[iclu]->SetMarkerSize(1.5);
    if (iclu==0) {
      clu_p05[iclu]->Draw("P");
    } else {
      clu_p05[iclu]->Draw("PSAME");
    }
    hclu_p05[iclu]->SetMarkerColor(mc[iclu]);
    hclu_p05[iclu]->SetMarkerStyle(mt[iclu]);
    hclu_p05[iclu]->SetMarkerSize(2.5);
    hclu_p05[iclu]->Draw("PSAME");
  }
  C1->cd(7);
  for (int iclu=0; iclu<Nclu; iclu++) {
    clu_p1[iclu]->SetLineColor(mc[iclu]);
    clu_p1[iclu]->SetMarkerColor(mc[iclu]);
    clu_p1[iclu]->SetMarkerStyle(mt[iclu]);
    clu_p1[iclu]->SetMarkerSize(1.5);
    if (iclu==0) {
      clu_p1[iclu]->Draw("P");
    } else {
      clu_p1[iclu]->Draw("PSAME");
    }
    hclu_p1[iclu]->SetMarkerColor(mc[iclu]);
    hclu_p1[iclu]->SetMarkerStyle(mt[iclu]);
    hclu_p1[iclu]->SetMarkerSize(2.5);
    hclu_p1[iclu]->Draw("PSAME");
  }
  C1->cd(8);
  for (int iclu=0; iclu<Nclu; iclu++) {
    clu_p2[iclu]->SetLineColor(mc[iclu]);
    clu_p2[iclu]->SetMarkerColor(mc[iclu]);
    clu_p2[iclu]->SetMarkerStyle(mt[iclu]);
    clu_p2[iclu]->SetMarkerSize(1.5);
    if (iclu==0) {
      clu_p2[iclu]->Draw("P");
    } else {
      clu_p2[iclu]->Draw("PSAME");
    }
    hclu_p2[iclu]->SetMarkerColor(mc[iclu]);
    hclu_p2[iclu]->SetMarkerStyle(mt[iclu]);
    hclu_p2[iclu]->SetMarkerSize(2.5);
    hclu_p2[iclu]->Draw("PSAME");
  }
  C1->cd(9);
  for (int iclu=0; iclu<Nclu; iclu++) {
    clu_p3[iclu]->SetLineColor(mc[iclu]);
    clu_p3[iclu]->SetMarkerColor(mc[iclu]);
    clu_p3[iclu]->SetMarkerStyle(mt[iclu]);
      clu_p2[iclu]->SetMarkerSize(1.5);
    if (iclu==0) {
      clu_p3[iclu]->Draw("P");
    } else {
      clu_p3[iclu]->Draw("PSAME");
    }
    hclu_p3[iclu]->SetMarkerColor(mc[iclu]);
    hclu_p3[iclu]->SetMarkerStyle(mt[iclu]);
    hclu_p3[iclu]->SetMarkerSize(2.5);
    hclu_p3[iclu]->Draw("PSAME");
  }

  // one per canvas

    
  TCanvas * D1 = new TCanvas ("D1","",600,600);
  D1->cd();
  for (int iclu=0; iclu<Nclu; iclu++) {
    L15[iclu]->SetLineColor(mc[iclu]);
    L15[iclu]->SetMarkerColor(mc[iclu]);
    L15[iclu]->SetMarkerStyle(mt[iclu]);
    L15[iclu]->SetMarkerSize(1.5);
      
    //if (Nclu==20)
      leg->AddEntry(clu_0[iclu], lege20[iclu], "P");  
    //else if (Nclu==15) leg->AddEntry(clu_0[iclu], lege15[iclu], "P"); 
    //else if (Nclu==10) leg->AddEntry(clu_0[iclu], lege20[iclu], "P"); 
          
    if (iclu==0) {
      L15[iclu]->Draw("P");
    } else {
      L15[iclu]->Draw("PSAME");
    }
    hL15[iclu]->SetMarkerColor(mc[iclu]);
    hL15[iclu]->SetMarkerStyle(mt[iclu]);
    hL15[iclu]->SetMarkerSize(2.5);
    hL15[iclu]->Draw("PSAME");
  }
  char nameplot[40];
  sprintf(nameplot,"clusters_cm3_%d.png",Nclu);
    leg->Draw("same");
  D1->Print(nameplot);

  TCanvas * D2 = new TCanvas ("D2","",600,600);
  D2->cd(1);
  for (int iclu=0; iclu<Nclu; iclu++) {
    clu_m2[iclu]->SetLineColor(mc[iclu]);
    clu_m2[iclu]->SetMarkerColor(mc[iclu]);
    clu_m2[iclu]->SetMarkerStyle(mt[iclu]);
      clu_p2[iclu]->SetMarkerSize(1.5);
    if (iclu==0) {
      clu_m2[iclu]->Draw("P");
    } else {
      clu_m2[iclu]->Draw("PSAME");
    }
    hclu_m2[iclu]->SetMarkerColor(mc[iclu]);
    hclu_m2[iclu]->SetMarkerStyle(mt[iclu]);
    hclu_m2[iclu]->SetMarkerSize(2.5);
    hclu_m2[iclu]->Draw("PSAME");
  }
  sprintf(nameplot,"clusters_cm2_%d.png",Nclu);
    leg->Draw("same");
  D2->Print(nameplot);

  TCanvas * D3 = new TCanvas ("D3","",600,600);
  D3->cd();
  for (int iclu=0; iclu<Nclu; iclu++) {
    clu_m1[iclu]->SetLineColor(mc[iclu]);
    clu_m1[iclu]->SetMarkerColor(mc[iclu]);
    clu_m1[iclu]->SetMarkerStyle(mt[iclu]);
    clu_m1[iclu]->SetMarkerSize(1.5);
    if (iclu==0) {
      clu_m1[iclu]->Draw("P");
    } else {
      clu_m1[iclu]->Draw("PSAME");
    }
    hclu_m1[iclu]->SetMarkerColor(mc[iclu]);
    hclu_m1[iclu]->SetMarkerStyle(mt[iclu]);
    hclu_m1[iclu]->SetMarkerSize(2.5);
    hclu_m1[iclu]->Draw("PSAME");
  }
  sprintf(nameplot,"clusters_cm1_%d.png",Nclu);
    leg->Draw("same");
  D3->Print(nameplot);

  TCanvas * D4 = new TCanvas ("D4","",600,600);
  D4->cd();
  for (int iclu=0; iclu<Nclu; iclu++) {
    clu_m05[iclu]->SetLineColor(mc[iclu]);
    clu_m05[iclu]->SetMarkerColor(mc[iclu]);
    clu_m05[iclu]->SetMarkerStyle(mt[iclu]);
    clu_m05[iclu]->SetMarkerSize(1.5);
    if (iclu==0) {
      clu_m05[iclu]->Draw("P");
    } else {
      clu_m05[iclu]->Draw("PSAME");
    }
    hclu_m05[iclu]->SetMarkerColor(mc[iclu]);
    hclu_m05[iclu]->SetMarkerStyle(mt[iclu]);
    hclu_m05[iclu]->SetMarkerSize(2.5);
    hclu_m05[iclu]->Draw("PSAME");
  }
  sprintf(nameplot,"clusters_cm05_%d.png",Nclu);
    leg->Draw("same");
  D4->Print(nameplot);

  TCanvas * D5 = new TCanvas ("D5","",600,600);
  D5->cd();
  for (int iclu=0; iclu<Nclu; iclu++) {
      clu_0[iclu]->GetYaxis()->SetTitle("#kappa_{t}");
      clu_0[iclu]->GetXaxis()->SetTitle("#kappa_{#lambda}");
    clu_0[iclu]->SetLineColor(mc[iclu]);
    clu_0[iclu]->SetMarkerColor(mc[iclu]);
    clu_0[iclu]->SetMarkerStyle(mt[iclu]);
    clu_0[iclu]->SetMarkerSize(1.5);
    if (iclu==0) {
      clu_0[iclu]->Draw("P");
        f2->Draw("cont3SAME");

    } else {
        clu_0[iclu]->Draw("PSAME");
    }
    hclu_0[iclu]->SetMarkerColor(mc[iclu]);
    hclu_0[iclu]->SetMarkerStyle(mt[iclu]);
    hclu_0[iclu]->SetMarkerSize(2.5);
    hclu_0[iclu]->Draw("PSAME");
      leg->Draw("same");
      leg->Draw("same");
      TLatex* text = new TLatex();
      text->SetTextSize(0.04);

      text->DrawLatex(-17,2.8,"c_{2} = 0");
      text->Draw("same");
  }
  sprintf(nameplot,"clusters_c0_%d.png",Nclu);
    leg->Draw("same");
  D5->Print(nameplot);

  TCanvas * D6 = new TCanvas ("D6","",600,600);
  D6->cd();
  for (int iclu=0; iclu<Nclu; iclu++) {
    clu_p05[iclu]->SetLineColor(mc[iclu]);
    clu_p05[iclu]->SetMarkerColor(mc[iclu]);
    clu_p05[iclu]->SetMarkerStyle(mt[iclu]);
    clu_p05[iclu]->SetMarkerSize(1.5);
    if (iclu==0) {
      clu_p05[iclu]->Draw("P");
    } else {
      clu_p05[iclu]->Draw("PSAME");
    }
    hclu_p05[iclu]->SetMarkerColor(mc[iclu]);
    hclu_p05[iclu]->SetMarkerStyle(mt[iclu]);
    hclu_p05[iclu]->SetMarkerSize(2.5);
    hclu_p05[iclu]->Draw("PSAME");
  }
  sprintf(nameplot,"clusters_cp05_%d.png",Nclu);
    leg->Draw("same");
  D6->Print(nameplot);

  TCanvas * D7 = new TCanvas ("D7","",600,600);
  D7->cd();
  for (int iclu=0; iclu<Nclu; iclu++) {
    clu_p1[iclu]->SetLineColor(mc[iclu]);
    clu_p1[iclu]->SetMarkerColor(mc[iclu]);
    clu_p1[iclu]->SetMarkerStyle(mt[iclu]);
    clu_p1[iclu]->SetMarkerSize(1.5);
    if (iclu==0) {
      clu_p1[iclu]->Draw("P");
    } else {
      clu_p1[iclu]->Draw("PSAME");
    }
    hclu_p1[iclu]->SetMarkerColor(mc[iclu]);
    hclu_p1[iclu]->SetMarkerStyle(mt[iclu]);
    hclu_p1[iclu]->SetMarkerSize(2.5);
    hclu_p1[iclu]->Draw("PSAME");
  }
  sprintf(nameplot,"clusters_cp1_%d.png",Nclu);
    leg->Draw("same");
  D7->Print(nameplot);

  TCanvas * D8 = new TCanvas ("D8","",600,600);
  D8->cd();
  for (int iclu=0; iclu<Nclu; iclu++) {
    clu_p2[iclu]->SetLineColor(mc[iclu]);
    clu_p2[iclu]->SetMarkerColor(mc[iclu]);
    clu_p2[iclu]->SetMarkerStyle(mt[iclu]);
    clu_p2[iclu]->SetMarkerSize(1.5);
    if (iclu==0) {
      clu_p2[iclu]->Draw("P");
    } else {
      clu_p2[iclu]->Draw("PSAME");
    }
    hclu_p2[iclu]->SetMarkerColor(mc[iclu]);
    hclu_p2[iclu]->SetMarkerStyle(mt[iclu]);
    hclu_p2[iclu]->SetMarkerSize(2.5);
    hclu_p2[iclu]->Draw("PSAME");
  }
  sprintf(nameplot,"clusters_cp2_%d.png",Nclu);
    leg->Draw("same");
  D8->Print(nameplot);

  TCanvas * D9 = new TCanvas ("D9","",600,600);
  D9->cd();
  for (int iclu=0; iclu<Nclu; iclu++) {
    clu_p3[iclu]->SetLineColor(mc[iclu]);
    clu_p3[iclu]->SetMarkerColor(mc[iclu]);
    clu_p3[iclu]->SetMarkerStyle(mt[iclu]);
    clu_p3[iclu]->SetMarkerSize(1.5);
    if (iclu==0) {
      clu_p3[iclu]->Draw("P");
    } else {
      clu_p3[iclu]->Draw("PSAME");
    }
    hclu_p3[iclu]->SetMarkerColor(mc[iclu]);
    hclu_p3[iclu]->SetMarkerStyle(mt[iclu]);
    hclu_p3[iclu]->SetMarkerSize(2.5);
    hclu_p3[iclu]->Draw("PSAME");
  }
  sprintf(nameplot,"clusters_cp3_%d.png",Nclu);
  sprintf(nameplot,"clusters_cp3_%d.png",Nclu);
    leg->Draw("same");
  D9->Print(nameplot);


}
*/