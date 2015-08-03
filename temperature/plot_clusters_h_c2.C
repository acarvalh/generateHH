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

void plot_clusters_h_c2(int Nclu=13) {
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
    // here I want isolines of cross section
    double xs0 = 85.64;
    double alpha = 0.475;
    double beta = 0.178;//0.185;
    double A1 = -1.89;
    double A2 = -1.78;//9;
    double A3 = 1.68;//70;
    double kl=5.0;     
    //double kl=5.0;     
    // c2 ===> x 
    // kt ===> y
    // doing all in the same canvas I need to have several functions :-(
    TF2 *f15 = new TF2("f15","log(x*x + ([1]*y*y)**2 + ([2]*y*[3])**2 + [4]*x*[1]*y*y + [5]*[1]*y*y*[2]*y*[3] + [6]*x*[2]*y*[3])",-3.2,3.2,0.3,2.7);
    TF2 *f125 = new TF2("f125","log(x*x + ([1]*y*y)**2 + ([2]*y*[3])**2 + [4]*x*[1]*y*y + [5]*[1]*y*y*[2]*y*[3] + [6]*x*[2]*y*[3])",-3.2,3.2,0.3,2.7);    
    TF2 *f10 = new TF2("f10","log(x*x + ([1]*y*y)**2 + ([2]*y*[3])**2 + [4]*x*[1]*y*y + [5]*[1]*y*y*[2]*y*[3] + [6]*x*[2]*y*[3])",-3.2,3.2,0.3,2.7);
    TF2 *f75 = new TF2("f75","log(x*x + ([1]*y*y)**2 + ([2]*y*[3])**2 + [4]*x*[1]*y*y + [5]*[1]*y*y*[2]*y*[3] + [6]*x*[2]*y*[3])",-3.2,3.2,0.3,2.7);
    TF2 *f5 = new TF2("f5","log(x*x + ([1]*y*y)**2 + ([2]*y*[3])**2 + [4]*x*[1]*y*y + [5]*[1]*y*y*[2]*y*[3] + [6]*x*[2]*y*[3])",-3.2,3.2,0.3,2.7);
    TF2 *f35 = new TF2("f35","log(x*x + ([1]*y*y)**2 + ([2]*y*[3])**2 + [4]*x*[1]*y*y + [5]*[1]*y*y*[2]*y*[3] + [6]*x*[2]*y*[3])",-3.2,3.2,0.3,2.7);
    TF2 *f24 = new TF2("f24","log(x*x + ([1]*y*y)**2 + ([2]*y*[3])**2 + [4]*x*[1]*y*y + [5]*[1]*y*y*[2]*y*[3] + [6]*x*[2]*y*[3])",-3.2,3.2,0.3,2.7);
    TF2 *f1 = new TF2("f1","log(x*x + ([1]*y*y)**2 + ([2]*y*[3])**2 + [4]*x*[1]*y*y + [5]*[1]*y*y*[2]*y*[3] + [6]*x*[2]*y*[3])",-3.2,3.2,0.3,2.7);
    TF2 *fm15 = new TF2("fm15","log(x*x + ([1]*y*y)**2 + ([2]*y*[3])**2 + [4]*x*[1]*y*y + [5]*[1]*y*y*[2]*y*[3] + [6]*x*[2]*y*[3])",-3.2,3.2,0.3,2.7);
    TF2 *fm125 = new TF2("fm125","log(x*x + ([1]*y*y)**2 + ([2]*y*[3])**2 + [4]*x*[1]*y*y + [5]*[1]*y*y*[2]*y*[3] + [6]*x*[2]*y*[3])",-3.2,3.2,0.3,2.7);    
    TF2 *fm10 = new TF2("fm10","log(x*x + ([1]*y*y)**2 + ([2]*y*[3])**2 + [4]*x*[1]*y*y + [5]*[1]*y*y*[2]*y*[3] + [6]*x*[2]*y*[3])",-3.2,3.2,0.3,2.7);
    TF2 *fm75 = new TF2("fm75","log(x*x + ([1]*y*y)**2 + ([2]*y*[3])**2 + [4]*x*[1]*y*y + [5]*[1]*y*y*[2]*y*[3] + [6]*x*[2]*y*[3])",-3.2,3.2,0.3,2.7);
    TF2 *fm5 = new TF2("fm5","log(x*x + ([1]*y*y)**2 + ([2]*y*[3])**2 + [4]*x*[1]*y*y + [5]*[1]*y*y*[2]*y*[3] + [6]*x*[2]*y*[3])",-3.2,3.2,0.3,2.7);
    TF2 *fm35 = new TF2("fm35","log(x*x + ([1]*y*y)**2 + ([2]*y*[3])**2 + [4]*x*[1]*y*y + [5]*[1]*y*y*[2]*y*[3] + [6]*x*[2]*y*[3])",-3.2,3.2,0.3,2.7);
    TF2 *fm24 = new TF2("fm24","log(x*x + ([1]*y*y)**2 + ([2]*y*[3])**2 + [4]*x*[1]*y*y + [5]*[1]*y*y*[2]*y*[3] + [6]*x*[2]*y*[3])",-3.2,3.2,0.3,2.7);
    //
    f15->SetParameter(3,15.0);
    f125->SetParameter(3,12.5);
    f10->SetParameter(3,10.0);
    f75->SetParameter(3,7.5);
    f5->SetParameter(3,5.0);
    f35->SetParameter(3,3.5);
    f24->SetParameter(3,2.4);
    f1->SetParameter(3,1.0);
    fm15->SetParameter(3,-15.0);
    fm125->SetParameter(3,-12.5);
    fm10->SetParameter(3,-10.0);
    fm75->SetParameter(3,-7.5);
    fm5->SetParameter(3,-5.0);
    fm35->SetParameter(3,-3.5);
    fm24->SetParameter(3,-2.4);
    //
    f15->SetParameter(0,xs0);
    f15->SetParameter(1,alpha);
    f15->SetParameter(2,beta);
    f15->SetParameter(4,A1);
    f15->SetParameter(5,A2);
    f15->SetParameter(6,A3);    
    f15->SetContour(10);
    f15->SetLineColor(18);
    //
    f125->SetParameter(0,xs0);
    f125->SetParameter(1,alpha);
    f125->SetParameter(2,beta);
    f125->SetParameter(4,A1);
    f125->SetParameter(5,A2);
    f125->SetParameter(6,A3);    
    f125->SetContour(10);
    f125->SetLineColor(18);
    //
    f10->SetParameter(0,xs0);
    f10->SetParameter(1,alpha);
    f10->SetParameter(2,beta);
    f10->SetParameter(4,A1);
    f10->SetParameter(5,A2);
    f10->SetParameter(6,A3);    
    f10->SetContour(10);
    f10->SetLineColor(18);
    //
    f75->SetParameter(0,xs0);
    f75->SetParameter(1,alpha);
    f75->SetParameter(2,beta);
    f75->SetParameter(4,A1);
    f75->SetParameter(5,A2);
    f75->SetParameter(6,A3);    
    f75->SetContour(10);
    f75->SetLineColor(18);
    //
    f5->SetParameter(0,xs0);
    f5->SetParameter(1,alpha);
    f5->SetParameter(2,beta);
    f5->SetParameter(4,A1);
    f5->SetParameter(5,A2);
    f5->SetParameter(6,A3);    
    f5->SetContour(10);
    f5->SetLineColor(18); 
    //
    f35->SetParameter(0,xs0);
    f35->SetParameter(1,alpha);
    f35->SetParameter(2,beta);
    f35->SetParameter(4,A1);
    f35->SetParameter(5,A2);
    f35->SetParameter(6,A3);    
    f35->SetContour(10);
    f35->SetLineColor(18);
    //
    f24->SetParameter(0,xs0);
    f24->SetParameter(1,alpha);
    f24->SetParameter(2,beta);
    f24->SetParameter(4,A1);
    f24->SetParameter(5,A2);
    f24->SetParameter(6,A3);    
    f24->SetContour(10);
    f24->SetLineColor(18);
    //
    f1->SetParameter(0,xs0);
    f1->SetParameter(1,alpha);
    f1->SetParameter(2,beta);
    f1->SetParameter(4,A1);
    f1->SetParameter(5,A2);
    f1->SetParameter(6,A3);    
    f1->SetContour(10);
    f1->SetLineColor(18);
    //
    fm15->SetParameter(0,xs0);
    fm15->SetParameter(1,alpha);
    fm15->SetParameter(2,beta);
    fm15->SetParameter(4,A1);
    fm15->SetParameter(5,A2);
    fm15->SetParameter(6,A3);    
    fm15->SetContour(10);
    fm15->SetLineColor(1);
    //
    fm125->SetParameter(0,xs0);
    fm125->SetParameter(1,alpha);
    fm125->SetParameter(2,beta);
    fm125->SetParameter(4,A1);
    fm125->SetParameter(5,A2);
    fm125->SetParameter(6,A3);    
    fm125->SetContour(10);
    fm125->SetLineColor(18);
    //
    fm10->SetParameter(0,xs0);
    fm10->SetParameter(1,alpha);
    fm10->SetParameter(2,beta);
    fm10->SetParameter(4,A1);
    fm10->SetParameter(5,A2);
    fm10->SetParameter(6,A3);    
    fm10->SetContour(10);
    fm10->SetLineColor(18);
    //
    fm75->SetParameter(0,xs0);
    fm75->SetParameter(1,alpha);
    fm75->SetParameter(2,beta);
    fm75->SetParameter(4,A1);
    fm75->SetParameter(5,A2);
    fm75->SetParameter(6,A3);    
    fm75->SetContour(10);
    fm75->SetLineColor(18);
    //
    fm5->SetParameter(0,xs0);
    fm5->SetParameter(1,alpha);
    fm5->SetParameter(2,beta);
    fm5->SetParameter(4,A1);
    fm5->SetParameter(5,A2);
    fm5->SetParameter(6,A3);    
    fm5->SetContour(10);
    fm5->SetLineColor(18); 
    //
    fm35->SetParameter(0,xs0);
    fm35->SetParameter(1,alpha);
    fm35->SetParameter(2,beta);
    fm35->SetParameter(4,A1);
    fm35->SetParameter(5,A2);
    fm35->SetParameter(6,A3);    
    fm35->SetContour(10);
    fm35->SetLineColor(18);
    //
    fm24->SetParameter(0,xs0);
    fm24->SetParameter(1,alpha);
    fm24->SetParameter(2,beta);
    fm24->SetParameter(4,A1);
    fm24->SetParameter(5,A2);
    fm24->SetParameter(6,A3);    
    fm24->SetContour(10);
    fm24->SetLineColor(18);    
    ////////////////////////////////////////////////////
    //////////////////////////////////////////////
    // This is to plot the c2 X kt plane , the minimal cg and c2g
    // no isolines of cross sections !
    //////////////////////////////////////////////
    TLegend *leg = new TLegend(0.2,0.02,1.0,0.75);
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
    int mt[20]= {22,34,34,23,23,22,20,23,23,20,23,34,22}; // 13
//    int mt[20]= {34,20,34,34,23,20,34,23,23,23,20,20,23,22,23,23,20,23,34,22}; // 20
    ///////////////////////////////////////////////////
    // define the planes
    TH2D * L15[20];
    TH2D * L10[20]; 
    TH2D * L125[20]; 
    TH2D * L75[20]; 
    TH2D * L5[20]; 
    TH2D * L35[20]; 
    TH2D * L24[20];
    TH2D * L1[20];
    TH2D * Lm15[20];
    TH2D * Lm125[20];     
    TH2D * Lm10[20]; 
    TH2D * Lm5[20]; 
    TH2D * Lm75[20]; 
    TH2D * Lm35[20]; 
    TH2D * Lm24[20];
    //
    TH2D * hL15[20];
    TH2D * hL10[20]; 
    TH2D * hL125[20]; 
    TH2D * hL75[20]; 
    TH2D * hL5[20]; 
    TH2D * hL35[20]; 
    TH2D * hL24[20];
    TH2D * hL1[20];
    TH2D * hLm15[20];
    TH2D * hLm125[20];     
    TH2D * hLm10[20]; 
    TH2D * hLm75[20];     
    TH2D * hLm5[20]; 
    TH2D * hLm35[20]; 
    TH2D * hLm24[20];    
    //
    char name[100];
    for (int i=0; i<20; i++) {
        sprintf (name, "L15%d", i);
        L15[i] = new TH2D (name,"", 500, -4., 4., 500, 0., 3. );//#kappa_{#lambda} = 15        
        sprintf (name, "L10%d", i);
        L10[i] = new TH2D (name,"", 500, -4., 4., 500, 0., 3. ); 
        sprintf (name, "L125%d", i);
        L125[i] = new TH2D (name,"", 500, -4., 4., 500, 0., 3. ); 
        sprintf (name, "L75%d", i);
        L75[i] = new TH2D (name,"", 500, -4., 4., 500, 0., 3. );
        sprintf (name, "L5%d", i);
        L5[i] = new TH2D (name,"", 500, -4., 4., 500, 0., 3. );
        sprintf (name, "L35%d", i);
        L35[i] = new TH2D (name,"", 500, -4., 4., 500, 0., 3. );
        sprintf (name, "L24%d", i);
        L24[i] = new TH2D (name,"", 500, -4., 4., 500, 0., 3. );
        sprintf (name, "L1%d", i);
        L1[i] = new TH2D (name,"", 500, -4., 4., 500, 0., 3. );
        //
        sprintf (name, "Lm15%d", i);
        Lm15[i] = new TH2D (name,"", 500, -4., 4., 500, 0., 3. );
        sprintf (name, "Lm125%d", i);
        Lm125[i] = new TH2D (name,"", 500, -4., 4., 500, 0., 3. ); 
        sprintf (name, "Lm10%d", i);
        Lm10[i] = new TH2D (name,"", 500, -4., 4., 500, 0., 3. ); 
        sprintf (name, "Lm75%d", i);
        Lm75[i] = new TH2D (name,"", 500, -4., 4., 500, 0., 3. );
        sprintf (name, "Lm5%d", i);
        Lm5[i] = new TH2D (name,"", 500, -4., 4., 500, 0., 3. );
        sprintf (name, "Lm35%d", i);
        Lm35[i] = new TH2D (name,"", 500, -4., 4., 500, 0., 3. );
        sprintf (name, "Lm24%d", i);
        Lm24[i] = new TH2D (name,"", 500, -4., 4., 500, 0., 3. );  
        //
        sprintf (name, "hL15%d", i);
        hL15[i] = new TH2D (name,"", 500, -4., 4., 500, 0., 3. );
        sprintf (name, "hL10%d", i);
        hL10[i] = new TH2D (name,"", 500, -4., 4., 500, 0., 3. ); 
        sprintf (name, "hL125%d", i);
        hL125[i] = new TH2D (name,"", 500, -4., 4., 500, 0., 3. ); 
        sprintf (name, "hL75%d", i);
        hL75[i] = new TH2D (name,"", 500, -4., 4., 500, 0., 3. );
        sprintf (name, "hL5%d", i);
        hL5[i] = new TH2D (name,"", 500, -4., 4., 500, 0., 3. );
        sprintf (name, "hL35%d", i);
        hL35[i] = new TH2D (name,"", 500, -4., 4., 500, 0., 3. );
        sprintf (name, "hL24%d", i);
        hL24[i] = new TH2D (name,"", 500, -4., 4., 500, 0., 3. );
        sprintf (name, "hL1%d", i);
        hL1[i] = new TH2D (name,"", 500, -4., 4., 500, 0., 3. );
        //
        sprintf (name, "hLm15%d", i);
        hLm15[i] = new TH2D (name,"", 500, -4., 4., 500, 0., 3. );
        sprintf (name, "hLm125%d", i);
        hLm125[i] = new TH2D (name,"", 500, -4., 4., 500, 0., 3. ); 
        sprintf (name, "hLm10%d", i);
        hLm10[i] = new TH2D (name,"", 500, -4., 4., 500, 0., 3. ); 
        sprintf (name, "hLm75%d", i);
        hLm75[i] = new TH2D (name,"", 500, -4., 4., 500, 0., 3. );
        sprintf (name, "hLm5%d", i);
        hLm5[i] = new TH2D (name,"", 500, -4., 4., 500, 0., 3. );
        sprintf (name, "hLm35%d", i);
        hLm35[i] = new TH2D (name,"", 500, -4., 4., 500, 0., 3. );
        sprintf (name, "hLm24%d", i);
        hLm24[i] = new TH2D (name,"", 500, -4., 4., 500, 0., 3. );
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
        if (L[isamp]==15 && ( cg[isamp]==0 && c2g[isamp]==0 )) {
            L15[iclu]->Fill(c[isamp],y[isamp]);
            for (int j=0; j<Nclu; j++) { if (isamp==head[j]) hL15[iclu]->Fill(c[isamp],y[isamp]);};
        } else if (L[isamp]==10 && (cg[isamp]==0 && c2g[isamp]==0)) {
            L10[iclu]->Fill(c[isamp],y[isamp]);
            for (int j=0; j<Nclu; j++) { if (isamp==head[j]) hL10[iclu]->Fill(c[isamp],y[isamp]);};
            cout<<"clusters with lamb=10: "<<iclu<<  endl;
        } else if (L[isamp]==12.5 && (cg[isamp]==0 && c2g[isamp]==0)) {
            L125[iclu]->Fill(c[isamp],y[isamp]);
            for (int j=0; j<Nclu; j++) { if (isamp==head[j]) hL125[iclu]->Fill(c[isamp],y[isamp]);};
        } else if (L[isamp]==7.5 && (cg[isamp]==0 && c2g[isamp]==0)) {
            L75[iclu]->Fill(c[isamp],y[isamp]);
            for (int j=0; j<Nclu; j++) { if (isamp==head[j]) hL75[iclu]->Fill(c[isamp],y[isamp]);};
        } else if (L[isamp]==5 && (cg[isamp]==0 && c2g[isamp]==0)) {
            L5[iclu]->Fill(c[isamp],y[isamp]);
            for (int j=0; j<Nclu; j++) { if (isamp==head[j]) hL5[iclu]->Fill(c[isamp],y[isamp]);};
        } else if (L[isamp]==3.5 && (cg[isamp]==0 && c2g[isamp]==0)) {
            L35[iclu]->Fill(c[isamp],y[isamp]);
            for (int j=0; j<Nclu; j++) { if (isamp==head[j]) hL35[iclu]->Fill(c[isamp],y[isamp]);};
        } else if (L[isamp]==2.4 && (cg[isamp]==0 && c2g[isamp]==0)) {
            L24[iclu]->Fill(c[isamp],y[isamp]);
            for (int j=0; j<Nclu; j++) { if (isamp==head[j]) hL24[iclu]->Fill(c[isamp],y[isamp]);};
        } else if (
                   (L[isamp]==1 && (cg[isamp]==0 && c2g[isamp]==0) && !(c[isamp]==0 && y[isamp] ==1) )
                   //|| (L[isamp]==1 && (cg[isamp]==0.0971 && c2g[isamp]==0.00858) && (c[isamp]==0 && y[isamp] ==1) )
                   ) {
            L1[iclu]->Fill(c[isamp],y[isamp]);
            for (int j=0; j<Nclu; j++) { if (isamp==head[j]) hL1[iclu]->Fill(c[isamp],y[isamp]);};
        } // positive
        else if (L[isamp]==-15 && (cg[isamp]==0 && c2g[isamp]==0)) {
            Lm15[iclu]->Fill(c[isamp],y[isamp]);
            for (int j=0; j<Nclu; j++) { if (isamp==head[j]) hLm15[iclu]->Fill(c[isamp],y[isamp]);};
        } else if (L[isamp]==-10 && (cg[isamp]==0 && c2g[isamp]==0)) {
            Lm10[iclu]->Fill(c[isamp],y[isamp]);
            for (int j=0; j<Nclu; j++) { if (isamp==head[j]) hL10[iclu]->Fill(c[isamp],y[isamp]);};
        } else if (L[isamp]==-12.5 && (cg[isamp]==0 && c2g[isamp]==0)) {
            Lm125[iclu]->Fill(c[isamp],y[isamp]);
            for (int j=0; j<Nclu; j++) { if (isamp==head[j]) hL125[iclu]->Fill(c[isamp],y[isamp]);};
        } else if (L[isamp]==-7.5 && (cg[isamp]==0 && c2g[isamp]==0)) {
            Lm75[iclu]->Fill(c[isamp],y[isamp]);
            for (int j=0; j<Nclu; j++) { if (isamp==head[j]) hLm75[iclu]->Fill(c[isamp],y[isamp]);};
        } else if (L[isamp]==-5 && (cg[isamp]==0 && c2g[isamp]==0)) {
            Lm5[iclu]->Fill(c[isamp],y[isamp]);
            for (int j=0; j<Nclu; j++) { if (isamp==head[j]) hL5[iclu]->Fill(c[isamp],y[isamp]);};
        } else if (L[isamp]==-3.5 && (cg[isamp]==0 && c2g[isamp]==0)) {
            Lm35[iclu]->Fill(c[isamp],y[isamp]);
            for (int j=0; j<Nclu; j++) { if (isamp==head[j]) hL35[iclu]->Fill(c[isamp],y[isamp]);};
        } else if (L[isamp]==-2.4 && (cg[isamp]==0 && c2g[isamp]==0)) {
            Lm24[iclu]->Fill(c[isamp],y[isamp]);
            for (int j=0; j<Nclu; j++) { if (isamp==head[j]) hL24[iclu]->Fill(c[isamp],y[isamp]);};
        } 
    } // close for samples
    ////////////////////////////////////////
    char nameplot[40];
    TCanvas * C1 = new TCanvas ("C1","",1000,1950);
    C1->Divide(4,4,0,0);   
    //C1.SetBorderMode(0); 
    //C1.SetTopMargin(0.1);
    //////////////////////////////////////
    C1->cd(1);
    C1_1->SetTicks(2,2);
    C1_1->SetTopMargin(0.07);
    for (int iclu=0; iclu<Nclu; iclu++) {
        L1[iclu]->GetYaxis()->SetTitle("c_{2}");
        L1[iclu]->GetYaxis()->SetTitle("#kappa_{t}");
        L1[iclu]->SetLineColor(mc[iclu]);
        L1[iclu]->SetMarkerColor(mc[iclu]);
        L1[iclu]->SetMarkerStyle(mt[iclu]);
        L1[iclu]->SetMarkerSize(1.5);
        if (iclu==0) {
            L1[iclu]->Draw("P");
            f1->Draw("cont3SAME");
            L1[iclu]->Draw("PSAME");
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
    text->DrawLatex(-3.2,2.7,"#kappa_{#lambda} = 1");
    text->Draw("same");
    //////////////////////////////////////
    C1->cd(2);    
    C1_2->SetTicks(2,2);
    C1_2->SetTopMargin(0.07);
    for (int iclu=0; iclu<Nclu; iclu++) {
        L24[iclu]->GetYaxis()->SetTitle("#kappa_{t}");
        L24[iclu]->SetLineColor(mc[iclu]);
        L24[iclu]->SetMarkerColor(mc[iclu]);
        L24[iclu]->SetMarkerStyle(mt[iclu]);
        L24[iclu]->SetMarkerSize(1.5);
        if (iclu==0) {
            L24[iclu]->Draw("P");
            f24->Draw("cont3SAME");
            L24[iclu]->Draw("PSAME");
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
    text->DrawLatex(-3.2,2.7,"#kappa_{#lambda} = 2.4");
    text->Draw("same");
    //////////////////////////////////////
    C1->cd(3);
    C1_3->SetTopMargin(0.07);
    C1_3->SetTicks(2,2);
    for (int iclu=0; iclu<Nclu; iclu++) {
        L35[iclu]->SetLineColor(mc[iclu]);
        L35[iclu]->SetMarkerColor(mc[iclu]);
        L35[iclu]->SetMarkerStyle(mt[iclu]);
        L35[iclu]->SetMarkerSize(1.5);
        if (iclu==0) {
            L35[iclu]->Draw("P");
            f35->Draw("cont3SAME");
            L35[iclu]->Draw("PSAME");
        } else {
            L35[iclu]->Draw("PSAME");
        }
        hL35[iclu]->SetMarkerColor(mc[iclu]);
        hL35[iclu]->SetMarkerStyle(mt[iclu]);
        hL35[iclu]->SetMarkerSize(2.5);
        hL35[iclu]->Draw("PSAME");
    }
    //leg->Draw("same");
    TLatex* text = new TLatex();
    text->SetTextSize(0.08);
    text->DrawLatex(-3.2,2.7,"#kappa_{#lambda} = 3.5");
    text->Draw("same");  
    //////////////////////////////////////
    C1->cd(4);
    C1_4->SetTopMargin(0.07);
    C1_4->SetRightMargin(0.1);
    C1_4->SetTicks(2,2);
    for (int iclu=0; iclu<Nclu; iclu++) {
        L5[iclu]->SetLineColor(mc[iclu]);
        L5[iclu]->SetMarkerColor(mc[iclu]);
        L5[iclu]->SetMarkerStyle(mt[iclu]);
        L5[iclu]->SetMarkerSize(1.5);
        if (iclu==0) {
            L5[iclu]->Draw("P");
            f5->Draw("cont3SAME");
            L5[iclu]->Draw("PSAME");
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
    text->DrawLatex(-3.2,2.7,"#kappa_{#lambda} = 5");
    text->Draw("same");  
    //////////////////////////////////////
    C1->cd(5);
    C1_5->SetTicks(2,2);
    TLatex* text1 = new TLatex();
    text1->SetTextSize(0.12);
    text1->DrawLatex(0.2,0.87,"LHC13 ");
    text1->Draw("same");
    text1->SetTextSize(0.09);
    text1->DrawLatex(0.2,0.76,"c_{g} = c_{2g} = 0 (from 5D scan)");
    text1->Draw("same");
    leg->Draw("P");      
    //////////////////////////////////////
    C1->cd(6);
//    C1_6->SetTopMargin(0.1);
    C1_6->SetTicks(2,2);
    for (int iclu=0; iclu<Nclu; iclu++) {
        Lm24[iclu]->SetLineColor(mc[iclu]);
        Lm24[iclu]->SetMarkerColor(mc[iclu]);
        Lm24[iclu]->SetMarkerStyle(mt[iclu]);
        Lm24[iclu]->SetMarkerSize(1.5);
        if (iclu==0) {
            Lm24[iclu]->Draw("P");
            fm24->Draw("cont3SAME");
            Lm24[iclu]->Draw("PSAME");
        } else {
            Lm24[iclu]->Draw("PSAME");
        }
        hLm24[iclu]->SetMarkerColor(mc[iclu]);
        hLm24[iclu]->SetMarkerStyle(mt[iclu]);
        hLm24[iclu]->SetMarkerSize(2.5);
        hLm24[iclu]->Draw("PSAME");
    }
    //leg->Draw("same");
    TLatex* text = new TLatex();
    text->SetTextSize(0.08);
    text->DrawLatex(-3.2,2.7,"#kappa_{#lambda} = -2.4");
    text->Draw("same");
    //////////////////////////////////////
    C1->cd(7);
//    C1_7->SetTopMargin(0.1);
    C1_7->SetTicks(2,2);
    for (int iclu=0; iclu<Nclu; iclu++) {
        Lm35[iclu]->GetYaxis()->SetTitle("#kappa_{t}");
        Lm35[iclu]->SetLineColor(mc[iclu]);
        Lm35[iclu]->SetMarkerColor(mc[iclu]);
        Lm35[iclu]->SetMarkerStyle(mt[iclu]);
        Lm35[iclu]->SetMarkerSize(1.5);
        if (iclu==0) {
            //hL15[iclu]->Draw("Y+");
            Lm35[iclu]->Draw("P");
            fm35->Draw("cont3SAME");
            Lm35[iclu]->Draw("PSAME");
        } else {
            Lm35[iclu]->Draw("PSAME");
        }
        hLm35[iclu]->SetMarkerColor(mc[iclu]);
        hLm35[iclu]->SetMarkerStyle(mt[iclu]);
        hLm35[iclu]->SetMarkerSize(2.5);
        hLm35[iclu]->Draw("PSAME");
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
    text->DrawLatex(-3.2,2.7,"#kappa_{#lambda} = -3.5");
    text->Draw("same"); 
    //////////////////////////////////
    // negative
    //////////////////////////////////
    C1->cd(8);
    C1_8->SetTicks(2,2);
    C1_8->SetRightMargin(0.1);
    for (int iclu=0; iclu<Nclu; iclu++) {
        Lm5[iclu]->SetLineColor(mc[iclu]);
        Lm5[iclu]->SetMarkerColor(mc[iclu]);
        Lm5[iclu]->SetMarkerStyle(mt[iclu]);
        Lm5[iclu]->SetMarkerSize(1.5);
        if (iclu==0) {
            Lm5[iclu]->Draw("P");
            kl=-5.0;
            fm5->Draw("cont3SAME");
            Lm5[iclu]->Draw("PSAME");
        } else {
            Lm5[iclu]->Draw("PSAME");
        }
        //leg->AddEntry(Lm15[iclu], lege20[iclu], "P");
        hLm5[iclu]->SetMarkerColor(mc[iclu]);
        hLm5[iclu]->SetMarkerStyle(mt[iclu]);
        hLm5[iclu]->SetMarkerSize(2.5);
        hLm5[iclu]->Draw("PSAME");
    }
    //sprintf(nameplot,"clusters5D_L15_%d.png",Nclu);
    //leg->Draw("same");
    TLatex* text = new TLatex();
    text->SetTextSize(0.08);
    text->DrawLatex(-3.2,2.7,"#kappa_{#lambda} = -5");
    text->Draw("same");
    //////////////////////////////////////
    C1->cd(9);
    C1_9->SetTopMargin(0.025);
    C1_9->SetTicks(2,2);
    for (int iclu=0; iclu<Nclu; iclu++) {
        L75[iclu]->SetLineColor(mc[iclu]);
        L75[iclu]->SetMarkerColor(mc[iclu]);
        L75[iclu]->SetMarkerStyle(mt[iclu]);
        L75[iclu]->SetMarkerSize(1.5);
        if (iclu==0) {
            L75[iclu]->Draw("P");
            f75->Draw("cont3SAME");
            L75[iclu]->Draw("PSAME");
        } else {
            L75[iclu]->Draw("PSAME");
        }
        hL75[iclu]->SetMarkerColor(mc[iclu]);
        hL75[iclu]->SetMarkerStyle(mt[iclu]);
        hL75[iclu]->SetMarkerSize(2.5);
        hL75[iclu]->Draw("PSAME");
    }
    //leg->Draw("same");
    TLatex* text = new TLatex();
    text->SetTextSize(0.08);
    text->DrawLatex(-3.2,2.7,"#kappa_{#lambda} = 7.5");
    text->Draw("same");
    //////////////////////////////////////
    C1->cd(10);
    C1_10->SetTicks(2,2);
    C1_10->SetTopMargin(0.025);
    for (int iclu=0; iclu<Nclu; iclu++) {
        L10[iclu]->SetLineColor(mc[iclu]);
        L10[iclu]->SetMarkerColor(mc[iclu]);
        L10[iclu]->SetMarkerStyle(mt[iclu]);
        L10[iclu]->SetMarkerSize(1.5);
        if (iclu==0) {
            L10[iclu]->Draw("P");
            f10->Draw("cont3SAME");
            L10[iclu]->Draw("PSAME");
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
    text->DrawLatex(-3.2,2.7,"#kappa_{#lambda} = 10");
    text->Draw("same");
    //////////////////////////////////////
    C1->cd(11);
    //C1_10->SetRightMargin(0.1);
    C1_11->SetTicks(2,2);
    C1_11->SetTopMargin(0.025);
    for (int iclu=0; iclu<Nclu; iclu++) {
        L125[iclu]->SetLineColor(mc[iclu]);
        L125[iclu]->SetMarkerColor(mc[iclu]);
        L125[iclu]->SetMarkerStyle(mt[iclu]);
        L125[iclu]->SetMarkerSize(1.5);
        L125[iclu]->GetXaxis()->SetTitle("c_{2}");
        if (iclu==0) {
            L125[iclu]->Draw("P");
            f125->Draw("cont3SAME");
            L125[iclu]->Draw("PSAME");
        } else {
            L125[iclu]->Draw("PSAME");
        }
        hL125[iclu]->SetMarkerColor(mc[iclu]);
        hL125[iclu]->SetMarkerStyle(mt[iclu]);
        hL125[iclu]->SetMarkerSize(2.5);
        hL125[iclu]->Draw("PSAME");
    }
    //leg->Draw("same");
    text->SetTextSize(0.08);
    text->DrawLatex(-3.2,2.7,"#kappa_{#lambda} = 12.5");
    text->Draw("same");
    //////////////////////////////////
    C1->cd(12);
    C1_12->SetRightMargin(0.1);
    C1_12->SetTicks(2,2);
    C1_12->SetTopMargin(0.025);
    for (int iclu=0; iclu<Nclu; iclu++) {
        L15[iclu]->SetLineColor(mc[iclu]);
        L15[iclu]->SetMarkerColor(mc[iclu]);
        L15[iclu]->SetMarkerStyle(mt[iclu]);
        L15[iclu]->SetMarkerSize(1.5);
        L15[iclu]->GetXaxis()->SetTitle("c_{2}");
        if (iclu==0) {
            L15[iclu]->Draw("P");
            f15->Draw("cont3SAME");
            L15[iclu]->Draw("PSAME");
        } else {
            L15[iclu]->Draw("PSAME");
        }
        hL15[iclu]->SetMarkerColor(mc[iclu]);
        hL15[iclu]->SetMarkerStyle(mt[iclu]);
        hL15[iclu]->SetMarkerSize(2.5);
        hL15[iclu]->Draw("PSAME");
    }
    //leg->Draw("same");
    text->SetTextSize(0.08);
    text->DrawLatex(-3.2,2.7,"#kappa_{#lambda} = 15");
    text->Draw("same");
    //////////////////////////////////
    C1->cd(13);
    //C1_12->SetRightMargin(0.1);
    C1_13->SetTicks(2,2);
    for (int iclu=0; iclu<Nclu; iclu++) {
        Lm75[iclu]->SetLineColor(mc[iclu]);
        Lm75[iclu]->SetMarkerColor(mc[iclu]);
        Lm75[iclu]->SetMarkerStyle(mt[iclu]);
        Lm75[iclu]->SetMarkerSize(1.5);
        //Lm75[iclu]->GetXaxis()->SetTitle("c_{2}");
        if (iclu==0) {
            Lm75[iclu]->Draw("P");
            fm75->Draw("cont3SAME");
            Lm75[iclu]->Draw("PSAME");
        } else {
            Lm75[iclu]->Draw("PSAME");
        }
        hLm75[iclu]->SetMarkerColor(mc[iclu]);
        hLm75[iclu]->SetMarkerStyle(mt[iclu]);
        hLm75[iclu]->SetMarkerSize(2.5);
        hLm75[iclu]->Draw("PSAME");
    }
    //leg->Draw("same");
    text->SetTextSize(0.08);
    text->DrawLatex(-3.2,2.7,"#kappa_{#lambda} = -7.5");
    text->Draw("same");
    //////////////////////////////////
    C1->cd(14);
    C1_14->SetTicks(2,2);
    for (int iclu=0; iclu<Nclu; iclu++) {
        Lm10[iclu]->SetLineColor(mc[iclu]);
        Lm10[iclu]->SetMarkerColor(mc[iclu]);
        Lm10[iclu]->SetMarkerStyle(mt[iclu]);
        Lm10[iclu]->SetMarkerSize(1.5);
        //Lm10[iclu]->GetXaxis()->SetTitle("c_{2}");
        if (iclu==0) {
            Lm10[iclu]->Draw("P");
            fm10->Draw("cont3SAME");
            Lm10[iclu]->Draw("PSAME");
        } else {
            Lm10[iclu]->Draw("PSAME");
        }
        hLm10[iclu]->SetMarkerColor(mc[iclu]);
        hLm10[iclu]->SetMarkerStyle(mt[iclu]);
        hLm10[iclu]->SetMarkerSize(2.5);
        hLm10[iclu]->Draw("PSAME");
    }
    //leg->Draw("same");
    text->SetTextSize(0.08);
    text->DrawLatex(-3.2,2.7,"#kappa_{#lambda} = -10");
    text->Draw("same");
    //////////////////////////////////
    C1->cd(15);
    C1_15->SetTicks(2,2);
    for (int iclu=0; iclu<Nclu; iclu++) {
        Lm125[iclu]->SetLineColor(mc[iclu]);
        Lm125[iclu]->SetMarkerColor(mc[iclu]);
        Lm125[iclu]->SetMarkerStyle(mt[iclu]);
        Lm125[iclu]->SetMarkerSize(1.5);
        //Lm125[iclu]->GetXaxis()->SetTitle("c_{2}");
        if (iclu==0) {
            Lm125[iclu]->Draw("P");
            fm125->Draw("cont3SAME");
            Lm125[iclu]->Draw("PSAME");
        } else {
            Lm125[iclu]->Draw("PSAME");
        }
        hLm125[iclu]->SetMarkerColor(mc[iclu]);
        hLm125[iclu]->SetMarkerStyle(mt[iclu]);
        hLm125[iclu]->SetMarkerSize(2.5);
        hLm125[iclu]->Draw("PSAME");
    }
    //leg->Draw("same");
    text->SetTextSize(0.08);
    text->DrawLatex(-3.2,2.7,"#kappa_{#lambda} = -12.5");
    text->Draw("same");
    //////////////////////////////////
    C1->cd(16);
    C1_16->SetRightMargin(0.1);
    C1_16->SetTicks(2,2);
    for (int iclu=0; iclu<Nclu; iclu++) {
        Lm15[iclu]->SetLineColor(mc[iclu]);
        Lm15[iclu]->SetMarkerColor(mc[iclu]);
        Lm15[iclu]->SetMarkerStyle(mt[iclu]);
        Lm15[iclu]->SetMarkerSize(1.5);
        Lm15[iclu]->GetXaxis()->SetTitle("c_{2}");
        if (iclu==0) {
            Lm15[iclu]->Draw("P");   
            fm15->Draw("cont3SAME");
            Lm15[iclu]->Draw("PSAME");
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
    text->DrawLatex(-3.2,2.7,"#kappa_{#lambda} = -15");
    text->Draw("same");
    //////////////////////////////////
    sprintf(nameplot,"clusters5D_clu_noc2_%d.png",Nclu);    
    C1->Print(nameplot);
    sprintf(nameplot,"clusters5D_clu_noc2_%d.pdf",Nclu);    
    C1->Print(nameplot);
    
}