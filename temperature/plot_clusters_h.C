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

void plot_clusters_h(int Nclu=13) {
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
    defaultStyle->SetPadTopMargin(0.08);
    defaultStyle->SetPadBottomMargin(0.15);
    defaultStyle->SetPadLeftMargin(0.15);
    defaultStyle->SetPadRightMargin(1.0);
    /////// canvas /////////
    defaultStyle->SetCanvasBorderMode(0);
    defaultStyle->SetCanvasColor(0);
    //  defaultStyle->SetCanvasDefH(600);
    //  defaultStyle->SetCanvasDefW(600);
    /////// frame //////////
    defaultStyle->SetFrameBorderMode(0);
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
    defaultStyle->SetTitleX(0.2);
    //defaultStyle->SetTitleY(0.1);
    //defaultStyle->SetTitleBorderSize(-0.1);  // For the axis titles:
    
    //    defaultStyle->SetTitleColor(1, "XYZ");
    //    defaultStyle->SetTitleFont(42, "XYZ");
    defaultStyle->SetTitleSize(0.07, "XYZ");
    
    // defaultStyle->SetTitleYSize(Float_t size = 0.02);
    //defaultStyle->SetTitleXOffset(0.9);
    //defaultStyle->SetTitleYOffset(1.05);
    // defaultStyle->SetTitleOffset(1.1, "Y"); // Another way to set the Offset
    
    // For the axis labels:
    defaultStyle->SetLabelColor(1, "XYZ");
    //defaultStyle->SetLabelFont(46, "XYZ");
    // defaultStyle->SetLabelOffset(0.007, "XYZ");
    defaultStyle->SetLabelSize(0.05, "XYZ");
    
    // For the axis:
    //    defaultStyle->SetAxisColor(1, "XYZ");
    defaultStyle->SetStripDecimals(kTRUE);
    defaultStyle->SetTickLength(0.03, "XYZ");
    defaultStyle->SetNdivisions(510, "XYZ");
    defaultStyle->cd();
    //////////////////////////////////////////////
    // as our fit
    double a[15] = {2.19668,10.5545,0.303974,0.120575,1.44119,-8.93185,-1.4652,3.02194,1.53896,-5.21019,-0.725321,1.98027,0.352949,-0.895157,-0.602566};//
                //{2.19565, 10.4153, 0.303507, 0.120167, 1.46108, -8.8842, -1.46282, 2.9955, 3.31497, -3.34163, -0.721797, 1.98807, 0.352199, -0.89178, -0.592545};
    double norm =1.;
    ////////////////////////////////////////////////////
    double kt5d=1.0;
    double kl5d=1.0;
    double c25d=0.0;
    double c2g5d=0, cg5d=0;
    // cg ===> x ==> c2
    // c2g ===> y ==> kt
    TF2 *ff15d = new TF2("ff15d","log(([0]*y**4 + [1]*x**2 + [2]*y**2*[16]**2 + [3]*[17]**2*[16]**2 +  [4]*[15]**2 + [5]*x*y**2 + [6]*y*[16]*y**2 + [7]*y*[16]*x + [8]*[17]*[16]*x + [9]*x*[15] + [10]*[17]*[16]*y**2 + [11]*[15]*y**2 + [12]*[16]*[17]*y*[16] + [13]*[15]*y*[16] + [14]*[17]*[15]*[16])/[18])",-3,3,0.5,2.5);
    ff15d->SetParameter(0,a[0]);
    ff15d->SetParameter(1,a[1]);
    ff15d->SetParameter(2,a[2]);    
    ff15d->SetParameter(3,a[3]);
    ff15d->SetParameter(4,a[4]);
    ff15d->SetParameter(5,a[5]); 
    ff15d->SetParameter(6,a[6]);
    ff15d->SetParameter(7,a[7]);
    ff15d->SetParameter(8,a[8]); 
    ff15d->SetParameter(9,a[9]);
    ff15d->SetParameter(10,a[10]);
    ff15d->SetParameter(11,a[11]); 
    ff15d->SetParameter(12,a[12]);    
    ff15d->SetParameter(13,a[13]);
    ff15d->SetParameter(14,a[14]);
    ff15d->SetTitle("");
    ff15d->SetParameter(15,c2g5d); //==> c2g
    ff15d->SetParameter(16,kl5d);
    ff15d->SetParameter(17,cg5d); //==> cg
    ff15d->SetParameter(18,norm);//0.013531
    ff15d->SetMinimum(0);
    ff15d->SetLineColor(26); 
    ////////////////////////////////////////////////////
    // as our fit 
    c25d=0.0;
    c2g5d=0; 
    cg5d=0;
    // cg ===> x ==> c2 ==> kl
    // c2g ===> y ==> kt
    TF2 *fa15d = new TF2("fa15d","log(([0]*y**4 + [1]*[17]**2 + [2]*y**2*x**2 + [3]*[15]**2*x**2 +  [4]*[15]**2 + [5]*[17]*y**2 + [6]*y*x*y**2 + [7]*[15]*x*[17] + [8]*[16]*x*[17] + [9]*[17]*y + [10]*[16]*x*[15]**2 + [11]*[16]*y**2 + [12]*x*[16]*[15]*x + [13]*[15]*[15]*x + [14]*[16]*[15])/[18])",-15.,15.,0.5,2.5);
    fa15d->SetParameter(0,a[0]);
    fa15d->SetParameter(1,a[1]);
    fa15d->SetParameter(2,a[2]);    
    fa15d->SetParameter(3,a[3]);
    fa15d->SetParameter(4,a[4]);
    fa15d->SetParameter(5,a[5]); 
    fa15d->SetParameter(6,a[6]);
    fa15d->SetParameter(7,a[7]);
    fa15d->SetParameter(8,a[8]); 
    fa15d->SetParameter(9,a[9]);
    fa15d->SetParameter(10,a[10]);
    fa15d->SetParameter(11,a[11]); 
    fa15d->SetParameter(12,a[12]);    
    fa15d->SetParameter(13,a[13]);
    fa15d->SetParameter(14,a[14]);
    fa15d->SetTitle("");
    fa15d->SetParameter(15,cg5d); 
    fa15d->SetParameter(16,c25d); // => c2
    fa15d->SetParameter(17,c2g5d);
    fa15d->SetParameter(18,norm);
    fa15d->SetMinimum(0);
    fa15d->SetLineColor(26); 
    ////////////////////////////////////////////////////
    kt5d=1.0;
    kl5d=1.0;
    c25d=0.0;
    c2g5d=0; 
    cg5d=0;
    // cg ===> x ==> c2
    // c2g ===> y ==> kt ==> c2g
    TF2 *fc15d = new TF2("fc15d","log([0]*[15]**4 + [1]*x**2 + [2]*[15]**2*[16]**2 +  [4]*y**2 + [5]*x*[15]**2 + [6]*[15]*[16]*[15]**2 + [7]*[15]*[16]*x + [9]*x*y + [11]*y*[15]**2  + [13]*y*[15]*[16])/[17]",-3.,3.,-1,1);
    fc15d->SetParameter(0,a[0]);
    fc15d->SetParameter(1,a[1]);
    fc15d->SetParameter(2,a[2]);    
    fc15d->SetParameter(3,a[3]);
    fc15d->SetParameter(4,a[4]);
    fc15d->SetParameter(5,a[5]); 
    fc15d->SetParameter(6,a[6]);
    fc15d->SetParameter(7,a[7]);
    fc15d->SetParameter(8,a[8]); 
    fc15d->SetParameter(9,a[9]);
    fc15d->SetParameter(10,a[10]);
    fc15d->SetParameter(11,a[11]); 
    fc15d->SetParameter(12,a[12]);    
    fc15d->SetParameter(13,a[13]);
    fc15d->SetParameter(14,a[14]);
    fc15d->SetTitle("");
    fc15d->SetParameter(15,kt5d); //==> kt
    fc15d->SetParameter(16,kl5d);
    //fc15d->SetParameter(17,cg5d); 
    fc15d->SetParameter(17,norm);
    fc15d->SetMinimum(0);
    fc15d->SetLineColor(26); 
    ////////////////////////////////////////////////////
    // as our fit 
    c25d=0.0;
    c2g5d=0; 
    cg5d=0;
    // cg ===> x ==> c2 ==> kl
    // c2g ===> [17] ==> kt ==>cg
    TF2 *fe15d = new TF2("fe15d","log([0]*[15]**4 + [1]*[16]**2 + [2]*[15]**2*x**2 + [3]*y**2*x**2 +  [4]*y**2 + [5]*[16]*[15]**2 + [6]*[15]*x*[15]**2 + [7]*[15]*x*[16] + [8]*y*x*[16] - [9]*[16]*y + [10]*y*x*[15]**2 - [11]*y*[15]**2 + [12]*x*y*[15]*x - [13]*y*[15]*x - [14]*y*y*x)/[17]",-15,15,-1,1);
    fe15d->SetParameter(0,a[0]);
    fe15d->SetParameter(1,a[1]);
    fe15d->SetParameter(2,a[2]);    
    fe15d->SetParameter(3,a[3]);
    fe15d->SetParameter(4,a[4]);
    fe15d->SetParameter(5,a[5]); 
    fe15d->SetParameter(6,a[6]);
    fe15d->SetParameter(7,a[7]);
    fe15d->SetParameter(8,a[8]); 
    fe15d->SetParameter(9,a[9]);
    fe15d->SetParameter(10,a[10]);
    fe15d->SetParameter(11,a[11]); 
    fe15d->SetParameter(12,a[12]);    
    fe15d->SetParameter(13,a[13]);
    fe15d->SetParameter(14,a[14]);
    fe15d->SetTitle("");
    fe15d->SetParameter(15,1.0); // kt  
    fe15d->SetParameter(16,c25d); 
    //fe15d->SetParameter(17,cg5d); // => kt
    fe15d->SetParameter(17,norm);
    fe15d->SetMinimum(0);
    fe15d->SetLineColor(26); 
    ////////////////////////////////////////////////////
    kt5d=1.0;
    kl5d=1.0;
    c25d=0.0;
    c2g5d=0; 
    cg5d=0;
    // cg ===> x ==> c2
    // c2g ===> y ==> kt ==> c2g
    TF2 *fd15d = new TF2("fd15d","log([0]*[15]**4 + [1]*x**2 + [2]*[15]**2*[16]**2 + [3]*y**2*[16]**2 +  [4]*y**2 + [5]*x*[15]**2 + [6]*[15]*[16]*[15]**2 + [7]*[15]*[16]*x + [8]*y*[16]*x - [9]*x*y + [10]*y*[16]*[15]**2 - [11]*y*[15]**2 + [12]*[16]*y*[15]*[16] - [13]*y*[15]*[16] - [14]*y*y*[16])/[17]",-3.,3.,-1.,1.);
    fd15d->SetParameter(0,a[0]);
    fd15d->SetParameter(1,a[1]);
    fd15d->SetParameter(2,a[2]);    
    fd15d->SetParameter(3,a[3]);
    fd15d->SetParameter(4,a[4]);
    fd15d->SetParameter(5,a[5]); 
    fd15d->SetParameter(6,a[6]);
    fd15d->SetParameter(7,a[7]);
    fd15d->SetParameter(8,a[8]); 
    fd15d->SetParameter(9,a[9]);
    fd15d->SetParameter(10,a[10]);
    fd15d->SetParameter(11,a[11]); 
    fd15d->SetParameter(12,a[12]);    
    fd15d->SetParameter(13,a[13]);
    fd15d->SetParameter(14,a[14]);
    fd15d->SetTitle("");
    fd15d->SetParameter(15,kt5d); //==> kt
    fd15d->SetParameter(16,kl5d);
    //fd15d->SetParameter(17,cg5d); // obsolete 
    fd15d->SetParameter(17,norm);
    fd15d->SetMinimum(0);
    fd15d->SetLineColor(26); 
    ////////////////////////////////////////////////////
    kt5d=1.0;
    kl5d=1.0;
    c25d=0.0;
    c2g5d=0; 
    cg5d=0;
    // cg ===> [17] ==> c2 ==> cg
    // c2g ===> y ==> kt ==> c2g
    TF2 *fb15d = new TF2("fb15d","log(([0]*[15]**4 + [1]*[17]**2 + [2]*[15]**2*[16]**2 + [3]*x**2*[16]**2 +  [4]*y**2 + [5]*[17]*[15]**2 + [6]*[15]*[16]*[15]**2 + [7]*[15]*[16]*[17] + [8]*x*[16]*[17] + [9]*[17]*y + [10]*x*[16]*[15]**2 + [11]*y*[15]**2 + [12]*[16]*x*[15]*[16] + [13]*y*[15]*[16] + [14]*x*y*[16])/[18])",-1.,1.,-1.,1.);
    fb15d->SetParameter(0,a[0]);
    fb15d->SetParameter(1,a[1]);
    fb15d->SetParameter(2,a[2]);    
    fb15d->SetParameter(3,a[3]);
    fb15d->SetParameter(4,a[4]);
    fb15d->SetParameter(5,a[5]); 
    fb15d->SetParameter(6,a[6]);
    fb15d->SetParameter(7,a[7]);
    fb15d->SetParameter(8,a[8]); 
    fb15d->SetParameter(9,a[9]);
    fb15d->SetParameter(10,a[10]);
    fb15d->SetParameter(11,a[11]); 
    fb15d->SetParameter(12,a[12]);    
    fb15d->SetParameter(13,a[13]);
    fb15d->SetParameter(14,a[14]);
    fb15d->SetTitle("");
    fb15d->SetParameter(15,kt5d); 
    fb15d->SetParameter(16,kl5d);
    fb15d->SetParameter(17,c25d); //==> c2 
    fb15d->SetParameter(18,norm);
    fb15d->SetMinimum(0);
    fb15d->SetLineColor(26); 
    ////////////////////////////////////////////////////
    kt5d=1.0;
    kl5d=1.0;
    c25d=0.0;
    c2g5d=0.5; 
    cg5d=0;
    // cg ===> [17] ==> c2 ==> cg
    // c2g ===> y ==> kt ==> c2g
    TF2 *fg15d = new TF2("fg15d","log(([0]*[15]**4 + [1]*[17]**2 + [2]*[15]**2*[16]**2 + [3]*x**2*[16]**2 +  [4]*y**2 + [5]*[17]*[15]**2 + [6]*[15]*[16]*[15]**2 + [7]*[15]*[16]*[17] + [8]*x*[16]*[17] + [9]*[17]*y + [10]*x*[16]*[15]**2 + [11]*y*[15]**2 + [12]*[16]*x*[15]*[16] + [13]*y*[15]*[16] + [14]*x*y*[16])/[18])",-1.,1.,-1.,1.);
    fg15d->SetParameter(0,a[0]);
    fg15d->SetParameter(1,a[1]);
    fg15d->SetParameter(2,a[2]);    
    fg15d->SetParameter(3,a[3]);
    fg15d->SetParameter(4,a[4]);
    fg15d->SetParameter(5,a[5]); 
    fg15d->SetParameter(6,a[6]);
    fg15d->SetParameter(7,a[7]);
    fg15d->SetParameter(8,a[8]); 
    fg15d->SetParameter(9,a[9]);
    fg15d->SetParameter(10,a[10]);
    fg15d->SetParameter(11,a[11]); 
    fg15d->SetParameter(12,a[12]);    
    fg15d->SetParameter(13,a[13]);
    fg15d->SetParameter(14,a[14]);
    fg15d->SetTitle("");
    fg15d->SetParameter(15,kt5d); 
    fg15d->SetParameter(16,kl5d);
    fg15d->SetParameter(17,c25d); //==> c2 
    fg15d->SetParameter(18,norm);
    fg15d->SetMinimum(0);
    fg15d->SetLineColor(26); 
    /*
    //////////////////////////////////////////////
    // This is to plot the c2 X kt plane , the minimal 
    //////////////////////////////////////////////
    //xs[i] = xs0*(c2*c2 + pow(alpha*kt*kt,2) + pow(beta*kt*kl,2) + A1*c2*alpha*kt*kt + A2*alpha*kt*kt*beta*kt*kl + A3*c2*beta*kt*kl);
    double xs0 = 85.64;
    double alpha = 0.475;
    double beta = 0.185;
    double A1 = -1.89;
    double A2 = -1.79;
    double A3 = 1.70;
    double c2=0.0;     
    // lam ===> x 
    // kt ===> y
    TF2 *f3 = new TF2("f3","log([3]*[3] + ([1]*y*y)**2 + ([2]*y*x)**2 + [4]*[3]*[1]*y*y + [5]*[1]*y*y*[2]*y*x + [6]*[3]*[2]*y*x)",-16,16,0.3,2.5);
    f3->SetParameter(0,xs0);
    f3->SetParameter(1,alpha);
    f3->SetParameter(2,beta);
    f3->SetParameter(3,c2);
    f3->SetParameter(4,A1);
    f3->SetParameter(5,A2);
    f3->SetParameter(6,A3);    
    f3->SetContour(30);
    f3->SetLineColor(18);
    //////////////////////////////////////////////
    // This is to plot the cg X c2g plane , the minimal 
    //////////////////////////////////////////////
    //xs[i] = xs0*(c2*c2 + pow(alpha*kt*kt,2) + pow(beta*kt*kl,2) + A1*c2*alpha*kt*kt + A2*alpha*kt*kt*beta*kt*kl + A3*c2*beta*kt*kl);
    double AA1 = 2.13;
    double AA2 = 10.1;
    double AA3 = 0.3;
    double A4 = 21.8;
    double A5 = 188;
    double A6 = -8.62;
    double A7 = -1.43;
    double A8 = 2.93;
    double A9 = 21;
    double A10 = 59.8;
    double A11 = -9.93;
    double A12 = -23.1;
    double A13 = 4.87;
    double A14 = 10.5;
    double A15 = 96.6;
    //
    double kt5d=1.0;
    double kl5d=1.0;
    double c25d=0.0;
    // cg ===> x 
    // c2g ===> y
    TF2 *fg = new TF2("fg","log([0]*[15]**4 + [1]*[17]**2 + [2]*[15]**2*[16]**2 + [3]*x**2*[16]**2 +  [4]*y**2 + [5]*[17]*[15]**2 + [6]*[15]*[16]*[15]**2 + [7]*[15]*[16]*[17] + [8]*x*[16]*[17] + [9]*[17]*y + [10]*x*[16]*[15]**2 + [11]*y*[15]**2 + [12]*[16]*x*[15]*[16] + [13]*y*[15]*[16] + [14]*x*y*[16])",-1,0.9,-0.75,0.75);
    fg->SetParameter(0,AA1);
    fg->SetParameter(1,AA2);
    fg->SetParameter(2,AA3);    
    fg->SetParameter(3,A4);
    fg->SetParameter(4,A5);
    fg->SetParameter(5,A6); 
    fg->SetParameter(6,A7);
    fg->SetParameter(7,A8);
    fg->SetParameter(8,A9); 
    fg->SetParameter(9,A10);
    fg->SetParameter(10,A11);
    fg->SetParameter(11,A12); 
    fg->SetParameter(12,A13);    
    fg->SetParameter(13,A14);
    fg->SetParameter(14,A15);
    //
    fg->SetParameter(15,kt5d);    
    fg->SetParameter(16,kl5d);
    fg->SetParameter(17,c25d);
    //
    fg->SetContour(30);
    fg->SetLineColor(18);
    cout<<fg->Eval(0,0) <<endl;
     */
    ////////////////////////////////////////////////////
    TLegend *leg = new TLegend(0.9,0.15,1.05,0.9);
    leg->SetFillColor(kWhite);
    leg->SetFillStyle(0);
    leg->SetBorderSize(0);
    leg->SetTextSize(0.037);
    ///////////////////////////////////////////////////////
    // legend / color / shape to 10 / 15 /20
    const char* lege20[20]={" 1"," 2"," 3"," 4"," 5"," 6"," 7"," 8"," 9"," 10",
                            " 11"," 12"," 13"," 14"," 15"," 16"," 17"," 18"," 19"," 20"}; 
    ///////////////////////////////////////////////////////
    double L[1683];
    double y[1683];
    double c2[1683];
    double cg[1683];
    double c2g[1683];
    double cx[1683];
    double cxerr[1683];
    ifstream parpoints("/Users/Xanda/Documents/codes/git/generateHH/fit_minut_maker/list_all_translation.txt");///"LogP_1593_cT05/list_all_translation.txt");
    for (int i=0; i<1508; i++) {// 1593
        parpoints >> L[i] >> y[i] >> c2[i] >> cg[i] >> c2g[i] >> cx[i] >> cxerr[i];
        //cout << i<< " " << L[i] << " " << y[i] << " " << c2[i] << " " << cg[i] << " " << c2g[i] << endl;
    }
    parpoints.close();
    //////////////////////////////
    int mc[20]= {1, 2, 3, 4, 5, 6, 7, 8, 2, 15, 28, 30, 33, 38, 40, 41, 44, 45, 46, 48};
    //    int mt[20]= {22, 20, 34, 20, 23, 34, 22, 34, 23, 23, 23, 22, 22, 23, 20, 20, 22, 23, 20, 20 }; // style
    int mt[20]= {22,34,34,23,23,22,20,23,23,20,23,34,22}; // 13
    //int mt[20]= {34,20,34,34,23,20,34,23,23,23,20,20,23,22,23,23,20,23,34,22}; // 20
    //////////////////////////////////////

  
  //ifstream cluster_10("clustering_Nclu10_20_8_8.asc");
  //ifstream cluster_15("clustering_Nclu15_20_8_8.asc");
  //ifstream cluster_20("clustering_Nclu20_20_8_8.asc");

  ifstream cluster_13("LogP_1176/clustering_nev20k_Nclu13_50_5.asc");      
  ifstream cluster_20("LogP_1593_cT05/clustering_nev20k_Nclu20_50_5.asc");   

  TH2D * clua_0[20];
  TH2D * club_0[20];
  TH2D * cluc_0[20];
  TH2D * clud_0[20];
  TH2D * clue_0[20];
  TH2D * cluf_0[20];
  TH2D * clug_0[20];

  TH2D * hclua_0[20];
  TH2D * hclub_0[20];
  TH2D * hcluc_0[20];
  TH2D * hclud_0[20];
  TH2D * hclue_0[20];
  TH2D * hcluf_0[20];
  TH2D * hclug_0[20];
    
  char name[100];
  for (int i=0; i<20; i++) {
      sprintf (name, "clua_0%d", i);
      clua_0[i] = new TH2D (name,"", 500, -17., 17., 500, 0.3, 2.7 );//c_{2} = 0
      sprintf (name, "club_0%d", i);
      club_0[i] = new TH2D (name,"", 500, -1.2, 1.2, 500, -1.2, 1.2 );//c_{2} = 0
      sprintf (name, "cluc_0%d", i);
      cluc_0[i] = new TH2D (name,"", 500, -3.5, 3.5, 500,  -1.2, 1.2  );//c_{2} = 0
      sprintf (name, "clud_0%d", i);
      clud_0[i] = new TH2D (name,"", 500, -3.5, 3.5, 500, -1.2, 1.2 );//c_{2} = 0
      sprintf (name, "clue_0%d", i);
      clue_0[i] = new TH2D (name,"", 500, -17., 17., 500, -1.2, 1.2 );//c_{2} = 0
      sprintf (name, "cluf_0%d", i);
      cluf_0[i] = new TH2D (name,"", 500,  -3.5, 3.5, 500,  0.3, 2.7 );//c_{2} = 0
      sprintf (name, "clug_0%d", i);
      clug_0[i] = new TH2D (name,"", 500, -1.1, 1.1, 500,-1.2, 1.2 );//c_{2} = 0 
      //
      sprintf (name, "hclua_0%d", i);
      hclua_0[i] = new TH2D (name,"", 500, -17., 17., 500, 0., 3. );//c_{2} = 0
      sprintf (name, "hclub_0%d", i);
      hclub_0[i] = new TH2D (name,"", 500, -1.2, 1.2, 500, -1.2, 1.2 );//c_{2} = 0
      sprintf (name, "hcluc_0%d", i);
      hcluc_0[i] = new TH2D (name,"", 500, -3.5, 3.5, 500,  -1.2, 1.2  );//c_{2} = 0
      sprintf (name, "hclud_0%d", i);
      hclud_0[i] = new TH2D (name,"", 500, -17., 17., 500, -1.2, 1.2 );//c_{2} = 0
      sprintf (name, "hclue_0%d", i);
      hclue_0[i] = new TH2D (name,"", 500, -17., 17., 500, -1.2, 1.2 );//c_{2} = 0
      sprintf (name, "hcluf_0%d", i);
      hcluf_0[i] = new TH2D (name,"", 500,  -3.5, 3.5, 500,  0., 3. );//c_{2} = 0
      sprintf (name, "hclug_0%d", i);
      hclug_0[i] = new TH2D (name,"", 500, -1.2, 1.2, 500,-1.2, 1.2 );//c_{2} = 0
  }
    int isamp;
    int head20[20]= {263,826,1073,235,339,307,1182,5,298,408,810,945,1209,677,98,1045,717,1221,983,175}; //fixtouse
    int head13[20]= {225 ,741 ,496 ,207 ,223 ,482 ,577 ,1154 ,358 ,871 ,1068 ,622 ,73};   
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
  int iclu=-1;
  for (int i=0; i<1512; i++) { //1593
    if (Nclu==20) {
      cluster_20 >> isamp;
    } else if (Nclu==15) {
      cluster_15 >> isamp;
    } else if (Nclu==13) {
        cluster_13 >> isamp;
    } else if (Nclu==10) {
      cluster_10 >> isamp;
    }
    for (int j=0; j<Nclu; j++) {if (isamp==head[j]) { cout << "head = " << isamp << endl;		iclu++;}} //
    // new cluster
      if (cg[isamp]==0 && c2g[isamp]==0 && c2[isamp]==0.0 ){
        clua_0[iclu]->Fill(L[isamp],y[isamp]);
        for (int j=0; j<Nclu; j++) { if (isamp==head[j]) hclua_0[iclu]->Fill(L[isamp],y[isamp]);};
        //if (L[isamp]==-5) cout << isamp<< " " << L[isamp] << " " << y[isamp] << " " << c2[isamp] << " " << cg[isamp] << " " << c2g[isamp] << endl;
      } 
      if (isamp==1023)  cout << isamp<< " " << L[isamp] << " " << y[isamp] << " " << c2[isamp] << " " << cg[isamp] << " " << c2g[isamp] << endl;
      if (L[isamp]==1 && c2[isamp]==0 && y[isamp]==1){
          club_0[iclu]->Fill(cg[isamp],c2g[isamp]);
          for (int j=0; j<Nclu; j++) { if (isamp==head[j]) hclub_0[iclu]->Fill(cg[isamp],c2g[isamp]);};
          //if (c2g[isamp]==-0.8)  cout << isamp<< " " << L[isamp] << " " << y[isamp] << " " << c2[isamp] << " " << cg[isamp] << " " << c2g[isamp] << endl;
      } 
      if (L[isamp]==1 && cg[isamp]==0 && y[isamp]==1){
          cluc_0[iclu]->Fill(c2[isamp],c2g[isamp]);
          for (int j=0; j<Nclu; j++) { if (isamp==head[j]) hcluc_0[iclu]->Fill(c2[isamp],c2g[isamp]);};
          //if(c2g[isamp] ==0.6 && c2[isamp]<-2) cout << isamp<< " " << L[isamp] << " " << y[isamp] << " " << c2[isamp] << " " << cg[isamp] << " " << c2g[isamp] << endl;
      } 
      if (L[isamp]==1 && y[isamp]==1 && cg[isamp]== -c2g[isamp]){
          clud_0[iclu]->Fill(c2[isamp],c2g[isamp]);
          for (int j=0; j<Nclu; j++) { if (isamp==head[j]) hclud_0[iclu]->Fill(c2[isamp],c2g[isamp]);};
          //if(c2g[isamp] ==0 && c2[isamp]<2) cout << isamp<< " " << L[isamp] << " " << y[isamp] << " " << c2[isamp] << " " << cg[isamp] << " " << c2g[isamp] << endl;
      } 
      if (y[isamp]==1 && cg[isamp]== -c2g[isamp] && c2[isamp]==0){
          clue_0[iclu]->Fill(L[isamp],cg[isamp]);
          for (int j=0; j<Nclu; j++) { if (isamp==head[j]) hclue_0[iclu]->Fill(L[isamp],cg[isamp]);};
          //if(c2g[isamp] ==0 && L[isamp] <0) cout << isamp<< " " << L[isamp] << " " << y[isamp] << " " << c2[isamp] << " " << cg[isamp] << " " << c2g[isamp] << endl;
      } 
      if (L[isamp]==1 && cg[isamp]==0 && c2g[isamp] ==0 ){
          cluf_0[iclu]->Fill(c2[isamp],y[isamp]);
          for (int j=0; j<Nclu; j++) { if (isamp==head[j]) hclue_0[iclu]->Fill(c2[isamp],y[isamp]);};
          if (y[isamp]<1 && c2[isamp]<0.5) cout << isamp<< " " << L[isamp] << " " << y[isamp] << " " << c2[isamp] << " " << cg[isamp] << " " << c2g[isamp] << endl;
      } 
      if (L[isamp]==1 && c2[isamp]==0.5 && y[isamp]==1){
        clug_0[iclu]->Fill(cg[isamp],c2g[isamp]);
        for (int j=0; j<Nclu; j++) { if (isamp==head[j]) hclug_0[iclu]->Fill(cg[isamp],c2g[isamp]);};
        //cout << isamp<< " " << L[isamp] << " " << y[isamp] << " " << c[isamp] << " " << cg[isamp] << " " << c2g[isamp] << endl;
      } 
  }

  // one per canvas
  char nameplot[40];
    //////////////////////////////////////////////////////////////////
    TCanvas * Da = new TCanvas ("Da","",600,600);
    Da->cd();
    Da->SetLogz(0);
    for (int iclua=0; iclua<Nclu; iclua++) {
        clua_0[iclua]->GetYaxis()->SetTitle("#kappa_{t}");
        clua_0[iclua]->GetXaxis()->SetTitle("#kappa_{#lambda}");
        clua_0[iclua]->SetLineColor(mc[iclua]);
        clua_0[iclua]->SetMarkerColor(mc[iclua]);
        clua_0[iclua]->SetMarkerStyle(mt[iclua]);
        clua_0[iclua]->SetMarkerSize(2.0);
        if (iclua==0) {
            clua_0[iclua]->Draw("P");
            fa15d->Draw("cont3SAME");
            Da->SetLogz(0);
            clua_0[iclua]->Draw("PSAME");
        } else {
            clua_0[iclua]->Draw("PSAME");
        }
        leg->AddEntry(clua_0[iclua], lege20[iclua], "P");  
        hclua_0[iclua]->SetMarkerColor(mc[iclua]);
        hclua_0[iclua]->SetMarkerStyle(mt[iclua]);
        hclua_0[iclua]->SetMarkerSize(3.0);
        //hclua_0[iclua]->Draw("PSAME");
        leg->Draw("same");
        TLatex* text = new TLatex();
        text->SetTextSize(0.05);
        
        text->DrawLatex(-16,2.8,"c_{2} = c_{g} = c_{2g} = 0");
        text->Draw("same");
    }
    sprintf(nameplot,"cluasters_a_%d.png",Nclu);
    Da->Print(nameplot);
    sprintf(nameplot,"cluasters_a_%d.pdf",Nclu);
    Da->Print(nameplot);
    //////////////////////////////////////////////////////////////////
    TCanvas * Db = new TCanvas ("Db","",600,600);
    Db->cd();
    Db->SetLogz(0);
    for (int iclub=0; iclub<Nclu; iclub++) {
        club_0[iclub]->GetYaxis()->SetTitle("c_{2g}");
        club_0[iclub]->GetXaxis()->SetTitle("c_{g}");
        club_0[iclub]->SetLineColor(mc[iclub]);
        club_0[iclub]->SetMarkerColor(mc[iclub]);
        club_0[iclub]->SetMarkerStyle(mt[iclub]);
        club_0[iclub]->SetMarkerSize(2.0);
        if (iclub==0) {
            club_0[iclub]->Draw("P");
            fb15d->Draw("cont3SAME");
            Db->SetLogz(0);
            club_0[iclub]->Draw("PSAME");
        } else {
            club_0[iclub]->Draw("PSAME");
        }
        //leg->AddEntry(club_0[iclub], lege20[iclub], "P");  
        hclub_0[iclub]->SetMarkerColor(mc[iclub]);
        hclub_0[iclub]->SetMarkerStyle(mt[iclub]);
        hclub_0[iclub]->SetMarkerSize(3.0);
        hclub_0[iclub]->Draw("PSAME");
        leg->Draw("same");
        TLatex* text = new TLatex();
        text->SetTextSize(0.05);
        
        text->DrawLatex(-1.15,1.3,"#kappa_{#lambda} = #kappa_{t} = 1 ; c_{2} = 0"); // L[isamp]==1 && c2[isamp]==0 && y[isamp]==1
        text->Draw("same");
    }
    sprintf(nameplot,"clubsters_b_%d.png",Nclu);
    Db->Print(nameplot);
    sprintf(nameplot,"clubsters_b_%d.pdf",Nclu);
    Db->Print(nameplot);
    //////////////////////////////////////////////////////////////////
    TCanvas * Dc = new TCanvas ("Dc","",600,600);
    Dc->cd();
    Dc->SetLogz(0);
    for (int icluc=0; icluc<Nclu; icluc++) {
        cluc_0[icluc]->GetYaxis()->SetTitle("c_{2g}");
        cluc_0[icluc]->GetXaxis()->SetTitle("c_{2}");
        cluc_0[icluc]->SetLineColor(mc[icluc]);
        cluc_0[icluc]->SetMarkerColor(mc[icluc]);
        cluc_0[icluc]->SetMarkerStyle(mt[icluc]);
        cluc_0[icluc]->SetMarkerSize(2.0);
        if (icluc==0) {
            cluc_0[icluc]->Draw("P");
            fc15d->Draw("cont3SAME");
            Dc->SetLogz(0);
            cluc_0[icluc]->Draw("PSAME");
        } else {
            cluc_0[icluc]->Draw("PSAME");
        }
        //leg->AddEntry(cluc_0[icluc], lege20[icluc], "P");  
        hcluc_0[icluc]->SetMarkerColor(mc[icluc]);
        hcluc_0[icluc]->SetMarkerStyle(mt[icluc]);
        hcluc_0[icluc]->SetMarkerSize(3.0);
        hcluc_0[icluc]->Draw("PSAME");
        leg->Draw("same");
        TLatex* text = new TLatex();
        text->SetTextSize(0.05);
        
        text->DrawLatex(-3.3,1.29,"#kappa_{t} = #kappa_{t} =1 ; c_{g} = 0"); //L[isamp]==1 && cg[isamp]==0 && y[isamp]==1
        text->Draw("same");
    }
    sprintf(nameplot,"clucsters_c_%d.png",Nclu);
    Dc->Print(nameplot);
    sprintf(nameplot,"clucsters_c_%d.pdf",Nclu);
    Dc->Print(nameplot);
    //////////////////////////////////////////////////////////////////
    TCanvas * Dd = new TCanvas ("Dd","",600,600);
    Dd->cd();
    Dd->SetLogz(0);
    for (int iclud=0; iclud<Nclu; iclud++) {
        clud_0[iclud]->GetYaxis()->SetTitle("c_{2g}");
        clud_0[iclud]->GetXaxis()->SetTitle("c_{2}");
        clud_0[iclud]->SetLineColor(mc[iclud]);
        clud_0[iclud]->SetMarkerColor(mc[iclud]);
        clud_0[iclud]->SetMarkerStyle(mt[iclud]);
        clud_0[iclud]->SetMarkerSize(2.0);
        if (iclud==0) {
            clud_0[iclud]->Draw("P");
            fd15d->Draw("cont3SAME");
            Dd->SetLogz(0);
            clud_0[iclud]->Draw("PSAME");
        } else {
            clud_0[iclud]->Draw("PSAME");
        }
        //leg->AddEntry(clud_0[iclud], lege20[iclud], "P");  
        hclud_0[iclud]->SetMarkerColor(mc[iclud]);
        hclud_0[iclud]->SetMarkerStyle(mt[iclud]);
        hclud_0[iclud]->SetMarkerSize(3.0);
        hclud_0[iclud]->Draw("PSAME");
        leg->Draw("same");
        TLatex* text = new TLatex();
        text->SetTextSize(0.05);
        
        text->DrawLatex(-3.3,1.29,"#kappa_{t} = #kappa_{t} =1 ; c_{g} = -c_{2g}"); //L[isamp]==1 && y[isamp]==1 && cg[isamp]== -c2g[isamp]
        text->Draw("same");
    }
    sprintf(nameplot,"cludsters_d_%d.png",Nclu);
    Dd->Print(nameplot);
    sprintf(nameplot,"cludsters_d_%d.pdf",Nclu);
    Dd->Print(nameplot);    
    //////////////////////////////////////////////////////////////////
    TCanvas * De = new TCanvas ("De","",600,600);
    De->cd();
    De->SetLogz(0);
    for (int iclue=0; iclue<Nclu; iclue++) {
        clue_0[iclue]->GetYaxis()->SetTitle("c_{g}");
        clue_0[iclue]->GetXaxis()->SetTitle("#kappa_{#lambda}");
        clue_0[iclue]->SetLineColor(mc[iclue]);
        clue_0[iclue]->SetMarkerColor(mc[iclue]);
        clue_0[iclue]->SetMarkerStyle(mt[iclue]);
        clue_0[iclue]->SetMarkerSize(2.0);
        if (iclue==0) {
            clue_0[iclue]->Draw("P");
            fe15d->Draw("cont3SAME");
            De->SetLogz(0);
            clue_0[iclue]->Draw("PSAME");
        } else {
            clue_0[iclue]->Draw("PSAME");
        }
        //leg->ADeEntry(clue_0[iclue], lege20[iclue], "P");  
        hclue_0[iclue]->SetMarkerColor(mc[iclue]);
        hclue_0[iclue]->SetMarkerStyle(mt[iclue]);
        hclue_0[iclue]->SetMarkerSize(3.0);
        hclue_0[iclue]->Draw("PSAME");
        leg->Draw("same");
        TLatex* text = new TLatex();
        text->SetTextSize(0.04);
        
        text->DrawLatex(-16,1.28,"#kappa_{t} = 1 ; c_{g} = - c_{2g} ; c_{2} = 0"); //y[isamp]==1 && cg[isamp]== -c2g[isamp] && c2[isamp]==0
        text->Draw("same");
    }
    sprintf(nameplot,"cluesters_e_%d.png",Nclu);
    De->Print(nameplot);
    sprintf(nameplot,"cluesters_e_%d.pdf",Nclu);
    De->Print(nameplot);
    //////////////////////////////////////////////////////////////////
    TCanvas * Df = new TCanvas ("Df","",600,600);
    Df->cd();
    Df->SetLogz(0);
    for (int icluf=0; icluf<Nclu; icluf++) {
        cluf_0[icluf]->GetYaxis()->SetTitle("#kappa_{t}");
        cluf_0[icluf]->GetXaxis()->SetTitle("c_{2}");
        cluf_0[icluf]->SetLineColor(mc[icluf]);
        cluf_0[icluf]->SetMarkerColor(mc[icluf]);
        cluf_0[icluf]->SetMarkerStyle(mt[icluf]);
        cluf_0[icluf]->SetMarkerSize(2.0);
        if (icluf==0) {
            cluf_0[icluf]->Draw("P");
            ff15d->Draw("cont3SAME");
            De->SetLogz(0);
            cluf_0[icluf]->Draw("PSAME");
        } else {
            cluf_0[icluf]->Draw("PSAME");
        }
        //leg->ADeEntry(cluf_0[icluf], lege20[icluf], "P");  c2[isamp],y[isamp]) 
        hcluf_0[icluf]->SetMarkerColor(mc[icluf]);
        hcluf_0[icluf]->SetMarkerStyle(mt[icluf]);
        hcluf_0[icluf]->SetMarkerSize(3.0);
        hcluf_0[icluf]->Draw("PSAME");
        leg->Draw("same");
        TLatex* text = new TLatex();
        text->SetTextSize(0.05);
        
        text->DrawLatex(-3.3,2.8,"#kappa_{#lambda} = 1 ; c_{g} = c_{2g} = 0"); // L[isamp]==1 && cg[isamp]== -c2g[isamp]
        text->Draw("same");
    }
    sprintf(nameplot,"clufsters_f_%d.png",Nclu);
    Df->Print(nameplot);
    sprintf(nameplot,"clufsters_f_%d.pdf",Nclu);
    Df->Print(nameplot);
    //////////////////////////////////////////////////////////////////
    TCanvas * Dg = new TCanvas ("Dg","",600,600);
    Dg->cd();
    Dg->SetLogz(0);
    for (int iclug=0; iclug<Nclu; iclug++) {
        clug_0[iclug]->GetYaxis()->SetTitle("c_{2g}");
        clug_0[iclug]->GetXaxis()->SetTitle("c_{g}");
        clug_0[iclug]->SetLineColor(mc[iclug]);
        clug_0[iclug]->SetMarkerColor(mc[iclug]);
        clug_0[iclug]->SetMarkerStyle(mt[iclug]);
        clug_0[iclug]->SetMarkerSize(2.0);
        if (iclug==0) {
            clug_0[iclug]->Draw("P");
            fg15d->Draw("cont3SAME");
            Dg->SetLogz(0);
            clug_0[iclug]->Draw("PSAME");
        } else {
            clug_0[iclug]->Draw("PSAME");
        }
        //leg->ADgEntry(clug_0[iclug], lege20[iclug], "P");  
        hclug_0[iclug]->SetMarkerColor(mc[iclug]);
        hclug_0[iclug]->SetMarkerStyle(mt[iclug]);
        hclug_0[iclug]->SetMarkerSize(3.0);
        hclug_0[iclug]->Draw("PSAME");
        leg->Draw("same");
        TLatex* text = new TLatex();
        text->SetTextSize(0.05);
        
        text->DrawLatex(-1.1,1.3,"#kappa_{t} = #kappa_{t} =1 ; c_{2} = 0.5"); //L[isamp]==1 && c2[isamp]==0.5 && y[isamp]==1
        text->Draw("same");
    }
    sprintf(nameplot,"clugsters_g_%d.png",Nclu);
    Dg->Print(nameplot);
    sprintf(nameplot,"clugsters_g_%d.pdf",Nclu);
    Dg->Print(nameplot);    

}
