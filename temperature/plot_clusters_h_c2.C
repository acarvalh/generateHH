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
    const int Nfile =1508;//1052;
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
    defaultStyle->SetPadBottomMargin(0.28);
    defaultStyle->SetPadLeftMargin(0.28);
    defaultStyle->SetPadRightMargin(1.28);
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
    defaultStyle->SetTitleBorderSize(0);
    //  defaultStyle->SetTitleOffset(1.1,"X");
    //  defaultStyle->SetTitleSize(0.01,"X");
    //  defaultStyle->SetTitleOffset(1.25,"Y");
    //  defaultStyle->SetTitleSize(0.05,"Y");
    //defaultStyle->SetTitleFont(42, "XYZ");
    /////// various ////////
    defaultStyle->SetNdivisions(303,"Y");
    defaultStyle->SetTitleFillColor(0);//SetTitleFillStyle(0, "Z");
    //defaultStyle->SetTitleW(0.5);
    //defaultStyle->SetTitleY(0.1);
    defaultStyle->SetTitleBorderSize(-0.1);  // For the axis titles:
    
    //    defaultStyle->SetTitleColor(1, "XYZ");
    //    defaultStyle->SetTitleFont(42, "XYZ");
    defaultStyle->SetTitleSize(0.13, "XYZ");
    //defaultStyle->SetTitleOffset(0.03);    
    // defaultStyle->SetTitleYSize(Float_t size = 0.02);
    //defaultStyle->SetTitleXOffset(0.9);
    //defaultStyle->SetTitleYOffset(1.05);
    // defaultStyle->SetTitleOffset(1.1, "Y"); // Another way to set the Offset
    
    // For the axis labels:
    //defaultStyle->SetLabelColor(1, "XYZ");
    //defaultStyle->SetLabelFont(46, "XYZ");
    defaultStyle->SetLabelOffset(0.03, "XYZ");
    defaultStyle->SetLabelSize(0.1, "XYZ");
    
    // For the axis:
    //    defaultStyle->SetAxisColor(1, "XYZ");
    defaultStyle->SetStripDecimals(kTRUE);
    defaultStyle->SetTickLength(0.03, "XYZ");
    defaultStyle->SetNdivisions(5, "Y");
    defaultStyle->SetNdivisions(5, "X");
    defaultStyle->SetNdivisions(7, "Z");    
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
    // as contino1
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
    fm15->SetLineColor(18);
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
    // as our fit
    // with 861 points
    double a[15] = {2.19989,10.514,0.303797,0.119468,1.45923,-8.93676,-1.46576,3.01393,1.52371,-5.17558,-0.722951,1.98875,0.351713,-0.89334,-0.594566};
    double kt5d=1.0;
    double kl5d=-10;
    double c25d=0.0;
    double c2g5d=0, cg5d=0;
    double norm =1.;
    // cg ===> x ==> c2
    // c2g ===> y ==> kt
    TF2 *fgm105d = new TF2("fgm105d","log(([0]*y**4 + [1]*x**2 + [2]*y**2*[16]**2 + [3]*[17]**2*[16]**2 +  [4]*[15]**2 + [5]*x*y**2 + [6]*y*[16]*y**2 + [7]*y*[16]*x + [8]*[17]*[16]*x + [9]*x*[15] + [10]*[17]*[16]*y**2 + [11]*[15]*y**2 + [12]*[16]*[17]*y*[16] + [13]*[15]*y*[16] + [14]*[17]*[15]*[16])/[18])",-4,4,0.5,2.5);
    fgm105d->SetParameter(0,a[0]);
    fgm105d->SetParameter(1,a[1]);
    fgm105d->SetParameter(2,a[2]);    
    fgm105d->SetParameter(3,a[3]);
    fgm105d->SetParameter(4,a[4]);
    fgm105d->SetParameter(5,a[5]); 
    fgm105d->SetParameter(6,a[6]);
    fgm105d->SetParameter(7,a[7]);
    fgm105d->SetParameter(8,a[8]); 
    fgm105d->SetParameter(9,a[9]);
    fgm105d->SetParameter(10,a[10]);
    fgm105d->SetParameter(11,a[11]); 
    fgm105d->SetParameter(12,a[12]);    
    fgm105d->SetParameter(13,a[13]);
    fgm105d->SetParameter(14,a[14]);
    fgm105d->SetTitle("");
    fgm105d->SetParameter(15,c2g5d); //==> c2g
    fgm105d->SetParameter(16,kl5d);
    fgm105d->SetParameter(17,cg5d); //==> cg
    fgm105d->SetParameter(18,norm);//0.013531
    fgm105d->SetMinimum(0);
    fgm105d->SetLineColor(18); 
    //////////////////////////////////////////////
    // cg ===> x ==> c2
    // c2g ===> y ==> kt
    kl5d=10;
    TF2 *fg105d = new TF2("fgm105d","log(([0]*y**4 + [1]*x**2 + [2]*y**2*[16]**2 + [3]*[17]**2*[16]**2 +  [4]*[15]**2 + [5]*x*y**2 + [6]*y*[16]*y**2 + [7]*y*[16]*x + [8]*[17]*[16]*x + [9]*x*[15] + [10]*[17]*[16]*y**2 + [11]*[15]*y**2 + [12]*[16]*[17]*y*[16] + [13]*[15]*y*[16] + [14]*[17]*[15]*[16])/[18])",-4,4,0.5,2.5);
    fg105d->SetParameter(0,a[0]);
    fg105d->SetParameter(1,a[1]);
    fg105d->SetParameter(2,a[2]);    
    fg105d->SetParameter(3,a[3]);
    fg105d->SetParameter(4,a[4]);
    fg105d->SetParameter(5,a[5]); 
    fg105d->SetParameter(6,a[6]);
    fg105d->SetParameter(7,a[7]);
    fg105d->SetParameter(8,a[8]); 
    fg105d->SetParameter(9,a[9]);
    fg105d->SetParameter(10,a[10]);
    fg105d->SetParameter(11,a[11]); 
    fg105d->SetParameter(12,a[12]);    
    fg105d->SetParameter(13,a[13]);
    fg105d->SetParameter(14,a[14]);
    fg105d->SetTitle("");
    fg105d->SetParameter(15,c2g5d); //==> c2g
    fg105d->SetParameter(16,kl5d);
    fg105d->SetParameter(17,cg5d); //==> cg
    fg105d->SetParameter(18,norm);//0.013531
    fg105d->SetMinimum(0);
    fg105d->SetLineColor(18);
    //////////////////////////////////////////////
    // cg ===> x ==> c2
    // c2g ===> y ==> kt
    kl5d=-15;
    TF2 *fgm155d = new TF2("fgm155d","log(([0]*y**4 + [1]*x**2 + [2]*y**2*[16]**2 + [3]*[17]**2*[16]**2 +  [4]*[15]**2 + [5]*x*y**2 + [6]*y*[16]*y**2 + [7]*y*[16]*x + [8]*[17]*[16]*x + [9]*x*[15] + [10]*[17]*[16]*y**2 + [11]*[15]*y**2 + [12]*[16]*[17]*y*[16] + [13]*[15]*y*[16] + [14]*[17]*[15]*[16])/[18])",-4,4,0.5,2.5);
    fgm155d->SetParameter(0,a[0]);
    fgm155d->SetParameter(1,a[1]);
    fgm155d->SetParameter(2,a[2]);    
    fgm155d->SetParameter(3,a[3]);
    fgm155d->SetParameter(4,a[4]);
    fgm155d->SetParameter(5,a[5]); 
    fgm155d->SetParameter(6,a[6]);
    fgm155d->SetParameter(7,a[7]);
    fgm155d->SetParameter(8,a[8]); 
    fgm155d->SetParameter(9,a[9]);
    fgm155d->SetParameter(10,a[10]);
    fgm155d->SetParameter(11,a[11]); 
    fgm155d->SetParameter(12,a[12]);    
    fgm155d->SetParameter(13,a[13]);
    fgm155d->SetParameter(14,a[14]);
    fgm155d->SetTitle("");
    fgm155d->SetParameter(15,c2g5d); //==> c2g
    fgm155d->SetParameter(16,kl5d);
    fgm155d->SetParameter(17,cg5d); //==> cg
    fgm155d->SetParameter(18,norm);//0.013531
    fgm155d->SetMinimum(0);
    fgm155d->SetLineColor(18); 
    //////////////////////////////////////////////
    // cg ===> x ==> c2
    // c2g ===> y ==> kt
    kl5d=15;
    TF2 *fg155d = new TF2("fg155d","log(([0]*y**4 + [1]*x**2 + [2]*y**2*[16]**2 + [3]*[17]**2*[16]**2 +  [4]*[15]**2 + [5]*x*y**2 + [6]*y*[16]*y**2 + [7]*y*[16]*x + [8]*[17]*[16]*x + [9]*x*[15] + [10]*[17]*[16]*y**2 + [11]*[15]*y**2 + [12]*[16]*[17]*y*[16] + [13]*[15]*y*[16] + [14]*[17]*[15]*[16])/[18])",-4,4,0.5,2.5);
    fg155d->SetParameter(0,a[0]);
    fg155d->SetParameter(1,a[1]);
    fg155d->SetParameter(2,a[2]);    
    fg155d->SetParameter(3,a[3]);
    fg155d->SetParameter(4,a[4]);
    fg155d->SetParameter(5,a[5]); 
    fg155d->SetParameter(6,a[6]);
    fg155d->SetParameter(7,a[7]);
    fg155d->SetParameter(8,a[8]); 
    fg155d->SetParameter(9,a[9]);
    fg155d->SetParameter(10,a[10]);
    fg155d->SetParameter(11,a[11]); 
    fg155d->SetParameter(12,a[12]);    
    fg155d->SetParameter(13,a[13]);
    fg155d->SetParameter(14,a[14]);
    fg155d->SetTitle("");
    fg155d->SetParameter(15,c2g5d); //==> c2g
    fg155d->SetParameter(16,kl5d);
    fg155d->SetParameter(17,cg5d); //==> cg
    fg155d->SetParameter(18,norm);//0.013531
    fg155d->SetMinimum(0);
    fg155d->SetLineColor(18);
    //////////////////////////////////////////////
    // cg ===> x ==> c2
    // c2g ===> y ==> kt
    kl5d=-7.5;
    TF2 *fgm855d = new TF2("fgm755d","log(([0]*y**4 + [1]*x**2 + [2]*y**2*[16]**2 + [3]*[17]**2*[16]**2 +  [4]*[15]**2 + [5]*x*y**2 + [6]*y*[16]*y**2 + [7]*y*[16]*x + [8]*[17]*[16]*x + [9]*x*[15] + [10]*[17]*[16]*y**2 + [11]*[15]*y**2 + [12]*[16]*[17]*y*[16] + [13]*[15]*y*[16] + [14]*[17]*[15]*[16])/[18])",-4,4,0.5,2.5);
    fgm755d->SetParameter(0,a[0]);
    fgm755d->SetParameter(1,a[1]);
    fgm755d->SetParameter(2,a[2]);    
    fgm755d->SetParameter(3,a[3]);
    fgm755d->SetParameter(4,a[4]);
    fgm755d->SetParameter(5,a[5]); 
    fgm755d->SetParameter(6,a[6]);
    fgm755d->SetParameter(7,a[7]);
    fgm755d->SetParameter(8,a[8]); 
    fgm755d->SetParameter(9,a[9]);
    fgm755d->SetParameter(10,a[10]);
    fgm755d->SetParameter(11,a[11]); 
    fgm755d->SetParameter(12,a[12]);    
    fgm755d->SetParameter(13,a[13]);
    fgm755d->SetParameter(14,a[14]);
    fgm755d->SetTitle("");
    fgm755d->SetParameter(15,c2g5d); //==> c2g
    fgm755d->SetParameter(16,kl5d);
    fgm755d->SetParameter(17,cg5d); //==> cg
    fgm755d->SetParameter(18,norm);//0.013531
    fgm755d->SetMinimum(0);
    fgm755d->SetLineColor(18); 
    //////////////////////////////////////////////
    // cg ===> x ==> c2
    // c2g ===> y ==> kt
    kl5d=7.5;
    TF2 *fg755d = new TF2("fg755d","log(([0]*y**4 + [1]*x**2 + [2]*y**2*[16]**2 + [3]*[17]**2*[16]**2 +  [4]*[15]**2 + [5]*x*y**2 + [6]*y*[16]*y**2 + [7]*y*[16]*x + [8]*[17]*[16]*x + [9]*x*[15] + [10]*[17]*[16]*y**2 + [11]*[15]*y**2 + [12]*[16]*[17]*y*[16] + [13]*[15]*y*[16] + [14]*[17]*[15]*[16])/[18])",-4,4,0.5,2.5);
    fg755d->SetParameter(0,a[0]);
    fg755d->SetParameter(1,a[1]);
    fg755d->SetParameter(2,a[2]);    
    fg755d->SetParameter(3,a[3]);
    fg755d->SetParameter(4,a[4]);
    fg755d->SetParameter(5,a[5]); 
    fg755d->SetParameter(6,a[6]);
    fg755d->SetParameter(7,a[7]);
    fg755d->SetParameter(8,a[8]); 
    fg755d->SetParameter(9,a[9]);
    fg755d->SetParameter(10,a[10]);
    fg755d->SetParameter(11,a[11]); 
    fg755d->SetParameter(12,a[12]);    
    fg755d->SetParameter(13,a[13]);
    fg755d->SetParameter(14,a[14]);
    fg755d->SetTitle("");
    fg755d->SetParameter(15,c2g5d); //==> c2g
    fg755d->SetParameter(16,kl5d);
    fg755d->SetParameter(17,cg5d); //==> cg
    fg755d->SetParameter(18,norm);//0.013531
    fg755d->SetMinimum(0);
    fg755d->SetLineColor(18);
    //////////////////////////////////////////////
    // cg ===> x ==> c2
    // c2g ===> y ==> kt
    kl5d=-12.5;
    TF2 *fgm1255d = new TF2("fgm1255d","log(([0]*y**4 + [1]*x**2 + [2]*y**2*[16]**2 + [3]*[17]**2*[16]**2 +  [4]*[15]**2 + [5]*x*y**2 + [6]*y*[16]*y**2 + [7]*y*[16]*x + [8]*[17]*[16]*x + [9]*x*[15] + [10]*[17]*[16]*y**2 + [11]*[15]*y**2 + [12]*[16]*[17]*y*[16] + [13]*[15]*y*[16] + [14]*[17]*[15]*[16])/[18])",-4,4,0.5,2.5);
    fgm1255d->SetParameter(0,a[0]);
    fgm1255d->SetParameter(1,a[1]);
    fgm1255d->SetParameter(2,a[2]);    
    fgm1255d->SetParameter(3,a[3]);
    fgm1255d->SetParameter(4,a[4]);
    fgm1255d->SetParameter(5,a[5]); 
    fgm1255d->SetParameter(6,a[6]);
    fgm1255d->SetParameter(7,a[7]);
    fgm1255d->SetParameter(8,a[8]); 
    fgm1255d->SetParameter(9,a[9]);
    fgm1255d->SetParameter(10,a[10]);
    fgm1255d->SetParameter(11,a[11]); 
    fgm1255d->SetParameter(12,a[12]);    
    fgm1255d->SetParameter(13,a[13]);
    fgm1255d->SetParameter(14,a[14]);
    fgm1255d->SetTitle("");
    fgm1255d->SetParameter(15,c2g5d); //==> c2g
    fgm1255d->SetParameter(16,kl5d);
    fgm1255d->SetParameter(17,cg5d); //==> cg
    fgm1255d->SetParameter(18,norm);//0.013531
    fgm1255d->SetMinimum(0);
    fgm1255d->SetLineColor(18); 
    //////////////////////////////////////////////
    // cg ===> x ==> c2
    // c2g ===> y ==> kt
    kl5d=12.5;
    TF2 *fg1255d = new TF2("fg1255d","log(([0]*y**4 + [1]*x**2 + [2]*y**2*[16]**2 + [3]*[17]**2*[16]**2 +  [4]*[15]**2 + [5]*x*y**2 + [6]*y*[16]*y**2 + [7]*y*[16]*x + [8]*[17]*[16]*x + [9]*x*[15] + [10]*[17]*[16]*y**2 + [11]*[15]*y**2 + [12]*[16]*[17]*y*[16] + [13]*[15]*y*[16] + [14]*[17]*[15]*[16])/[18])",-4,4,0.5,2.5);
    fg1255d->SetParameter(0,a[0]);
    fg1255d->SetParameter(1,a[1]);
    fg1255d->SetParameter(2,a[2]);    
    fg1255d->SetParameter(3,a[3]);
    fg1255d->SetParameter(4,a[4]);
    fg1255d->SetParameter(5,a[5]); 
    fg1255d->SetParameter(6,a[6]);
    fg1255d->SetParameter(7,a[7]);
    fg1255d->SetParameter(8,a[8]); 
    fg1255d->SetParameter(9,a[9]);
    fg1255d->SetParameter(10,a[10]);
    fg1255d->SetParameter(11,a[11]); 
    fg1255d->SetParameter(12,a[12]);    
    fg1255d->SetParameter(13,a[13]);
    fg1255d->SetParameter(14,a[14]);
    fg1255d->SetTitle("");
    fg1255d->SetParameter(15,c2g5d); //==> c2g
    fg1255d->SetParameter(16,kl5d);
    fg1255d->SetParameter(17,cg5d); //==> cg
    fg1255d->SetParameter(18,norm);//0.013531
    fg1255d->SetMinimum(0);
    fg1255d->SetLineColor(18);
    //////////////////////////////////////////////
    // cg ===> x ==> c2
    // c2g ===> y ==> kt
    kl5d=-5;
    TF2 *fgm55d = new TF2("fgm55d","log(([0]*y**4 + [1]*x**2 + [2]*y**2*[16]**2 + [3]*[17]**2*[16]**2 +  [4]*[15]**2 + [5]*x*y**2 + [6]*y*[16]*y**2 + [7]*y*[16]*x + [8]*[17]*[16]*x + [9]*x*[15] + [10]*[17]*[16]*y**2 + [11]*[15]*y**2 + [12]*[16]*[17]*y*[16] + [13]*[15]*y*[16] + [14]*[17]*[15]*[16])/[18])",-4,4,0.5,2.5);
    fgm55d->SetParameter(0,a[0]);
    fgm55d->SetParameter(1,a[1]);
    fgm55d->SetParameter(2,a[2]);    
    fgm55d->SetParameter(3,a[3]);
    fgm55d->SetParameter(4,a[4]);
    fgm55d->SetParameter(5,a[5]); 
    fgm55d->SetParameter(6,a[6]);
    fgm55d->SetParameter(7,a[7]);
    fgm55d->SetParameter(8,a[8]); 
    fgm55d->SetParameter(9,a[9]);
    fgm55d->SetParameter(10,a[10]);
    fgm55d->SetParameter(11,a[11]); 
    fgm55d->SetParameter(12,a[12]);    
    fgm55d->SetParameter(13,a[13]);
    fgm55d->SetParameter(14,a[14]);
    fgm55d->SetTitle("");
    fgm55d->SetParameter(15,c2g5d); //==> c2g
    fgm55d->SetParameter(16,kl5d);
    fgm55d->SetParameter(17,cg5d); //==> cg
    fgm55d->SetParameter(18,norm);//0.013531
    fgm55d->SetMinimum(0);
    fgm55d->SetLineColor(18); 
    //////////////////////////////////////////////
    // cg ===> x ==> c2
    // c2g ===> y ==> kt
    kl5d=5;
    TF2 *fg55d = new TF2("fg55d","log(([0]*y**4 + [1]*x**2 + [2]*y**2*[16]**2 + [3]*[17]**2*[16]**2 +  [4]*[15]**2 + [5]*x*y**2 + [6]*y*[16]*y**2 + [7]*y*[16]*x + [8]*[17]*[16]*x + [9]*x*[15] + [10]*[17]*[16]*y**2 + [11]*[15]*y**2 + [12]*[16]*[17]*y*[16] + [13]*[15]*y*[16] + [14]*[17]*[15]*[16])/[18])",-4,4,0.5,2.5);
    fg55d->SetParameter(0,a[0]);
    fg55d->SetParameter(1,a[1]);
    fg55d->SetParameter(2,a[2]);    
    fg55d->SetParameter(3,a[3]);
    fg55d->SetParameter(4,a[4]);
    fg55d->SetParameter(5,a[5]); 
    fg55d->SetParameter(6,a[6]);
    fg55d->SetParameter(7,a[7]);
    fg55d->SetParameter(8,a[8]); 
    fg55d->SetParameter(9,a[9]);
    fg55d->SetParameter(10,a[10]);
    fg55d->SetParameter(11,a[11]); 
    fg55d->SetParameter(12,a[12]);    
    fg55d->SetParameter(13,a[13]);
    fg55d->SetParameter(14,a[14]);
    fg55d->SetTitle("");
    fg55d->SetParameter(15,c2g5d); //==> c2g
    fg55d->SetParameter(16,kl5d);
    fg55d->SetParameter(17,cg5d); //==> cg
    fg55d->SetParameter(18,norm);//0.013531
    fg55d->SetMinimum(0);
    fg55d->SetLineColor(18);
    //////////////////////////////////////////////
    // cg ===> x ==> c2
    // c2g ===> y ==> kt
    kl5d=-3.5;
    TF2 *fgm355d = new TF2("fgm355d","log(([0]*y**4 + [1]*x**2 + [2]*y**2*[16]**2 + [3]*[17]**2*[16]**2 +  [4]*[15]**2 + [5]*x*y**2 + [6]*y*[16]*y**2 + [7]*y*[16]*x + [8]*[17]*[16]*x + [9]*x*[15] + [10]*[17]*[16]*y**2 + [11]*[15]*y**2 + [12]*[16]*[17]*y*[16] + [13]*[15]*y*[16] + [14]*[17]*[15]*[16])/[18])",-4,4,0.5,2.5);
    fgm355d->SetParameter(0,a[0]);
    fgm355d->SetParameter(1,a[1]);
    fgm355d->SetParameter(2,a[2]);    
    fgm355d->SetParameter(3,a[3]);
    fgm355d->SetParameter(4,a[4]);
    fgm355d->SetParameter(5,a[5]); 
    fgm355d->SetParameter(6,a[6]);
    fgm355d->SetParameter(7,a[7]);
    fgm355d->SetParameter(8,a[8]); 
    fgm355d->SetParameter(9,a[9]);
    fgm355d->SetParameter(10,a[10]);
    fgm355d->SetParameter(11,a[11]); 
    fgm355d->SetParameter(12,a[12]);    
    fgm355d->SetParameter(13,a[13]);
    fgm355d->SetParameter(14,a[14]);
    fgm355d->SetTitle("");
    fgm355d->SetParameter(15,c2g5d); //==> c2g
    fgm355d->SetParameter(16,kl5d);
    fgm355d->SetParameter(17,cg5d); //==> cg
    fgm355d->SetParameter(18,norm);//0.013531
    fgm355d->SetMinimum(0);
    fgm355d->SetLineColor(18); 
    //////////////////////////////////////////////
    // cg ===> x ==> c2
    // c2g ===> y ==> kt
    kl5d=3.5;
    TF2 *fg355d = new TF2("fg355d","log(([0]*y**4 + [1]*x**2 + [2]*y**2*[16]**2 + [3]*[17]**2*[16]**2 +  [4]*[15]**2 + [5]*x*y**2 + [6]*y*[16]*y**2 + [7]*y*[16]*x + [8]*[17]*[16]*x + [9]*x*[15] + [10]*[17]*[16]*y**2 + [11]*[15]*y**2 + [12]*[16]*[17]*y*[16] + [13]*[15]*y*[16] + [14]*[17]*[15]*[16])/[18])",-4,4,0.5,2.5);
    fg355d->SetParameter(0,a[0]);
    fg355d->SetParameter(1,a[1]);
    fg355d->SetParameter(2,a[2]);    
    fg355d->SetParameter(3,a[3]);
    fg355d->SetParameter(4,a[4]);
    fg355d->SetParameter(5,a[5]); 
    fg355d->SetParameter(6,a[6]);
    fg355d->SetParameter(7,a[7]);
    fg355d->SetParameter(8,a[8]); 
    fg355d->SetParameter(9,a[9]);
    fg355d->SetParameter(10,a[10]);
    fg355d->SetParameter(11,a[11]); 
    fg355d->SetParameter(12,a[12]);    
    fg355d->SetParameter(13,a[13]);
    fg355d->SetParameter(14,a[14]);
    fg355d->SetTitle("");
    fg355d->SetParameter(15,c2g5d); //==> c2g
    fg355d->SetParameter(16,kl5d);
    fg355d->SetParameter(17,cg5d); //==> cg
    fg355d->SetParameter(18,norm);//0.013531
    fg355d->SetMinimum(0);
    fg355d->SetLineColor(18);
    //////////////////////////////////////////////
    // cg ===> x ==> c2
    // c2g ===> y ==> kt
    kl5d=-2.4;
    TF2 *fgm245d = new TF2("fgm245d","log(([0]*y**4 + [1]*x**2 + [2]*y**2*[16]**2 + [3]*[17]**2*[16]**2 +  [4]*[15]**2 + [5]*x*y**2 + [6]*y*[16]*y**2 + [7]*y*[16]*x + [8]*[17]*[16]*x + [9]*x*[15] + [10]*[17]*[16]*y**2 + [11]*[15]*y**2 + [12]*[16]*[17]*y*[16] + [13]*[15]*y*[16] + [14]*[17]*[15]*[16])/[18])",-4,4,0.5,2.5);
    fgm245d->SetParameter(0,a[0]);
    fgm245d->SetParameter(1,a[1]);
    fgm245d->SetParameter(2,a[2]);    
    fgm245d->SetParameter(3,a[3]);
    fgm245d->SetParameter(4,a[4]);
    fgm245d->SetParameter(5,a[5]); 
    fgm245d->SetParameter(6,a[6]);
    fgm245d->SetParameter(7,a[7]);
    fgm245d->SetParameter(8,a[8]); 
    fgm245d->SetParameter(9,a[9]);
    fgm245d->SetParameter(10,a[10]);
    fgm245d->SetParameter(11,a[11]); 
    fgm245d->SetParameter(12,a[12]);    
    fgm245d->SetParameter(13,a[13]);
    fgm245d->SetParameter(14,a[14]);
    fgm245d->SetTitle("");
    fgm245d->SetParameter(15,c2g5d); //==> c2g
    fgm245d->SetParameter(16,kl5d);
    fgm245d->SetParameter(17,cg5d); //==> cg
    fgm245d->SetParameter(18,norm);//0.013531
    fgm245d->SetMinimum(0);
    fgm245d->SetLineColor(18); 
    //////////////////////////////////////////////
    // cg ===> x ==> c2
    // c2g ===> y ==> kt
    kl5d=2.4;
    TF2 *fg245d = new TF2("fg255d","log(([0]*y**4 + [1]*x**2 + [2]*y**2*[16]**2 + [3]*[17]**2*[16]**2 +  [4]*[15]**2 + [5]*x*y**2 + [6]*y*[16]*y**2 + [7]*y*[16]*x + [8]*[17]*[16]*x + [9]*x*[15] + [10]*[17]*[16]*y**2 + [11]*[15]*y**2 + [12]*[16]*[17]*y*[16] + [13]*[15]*y*[16] + [14]*[17]*[15]*[16])/[18])",-4,4,0.5,2.5);
    fg245d->SetParameter(0,a[0]);
    fg245d->SetParameter(1,a[1]);
    fg245d->SetParameter(2,a[2]);    
    fg245d->SetParameter(3,a[3]);
    fg245d->SetParameter(4,a[4]);
    fg245d->SetParameter(5,a[5]); 
    fg245d->SetParameter(6,a[6]);
    fg245d->SetParameter(7,a[7]);
    fg245d->SetParameter(8,a[8]); 
    fg245d->SetParameter(9,a[9]);
    fg245d->SetParameter(10,a[10]);
    fg245d->SetParameter(11,a[11]); 
    fg245d->SetParameter(12,a[12]);    
    fg245d->SetParameter(13,a[13]);
    fg245d->SetParameter(14,a[14]);
    fg245d->SetTitle("");
    fg245d->SetParameter(15,c2g5d); //==> c2g
    fg245d->SetParameter(16,kl5d);
    fg245d->SetParameter(17,cg5d); //==> cg
    fg245d->SetParameter(18,norm);//0.013531
    fg245d->SetMinimum(0);
    fg245d->SetLineColor(18);
    //////////////////////////////////////////////
    // cg ===> x ==> c2
    // c2g ===> y ==> kt
    kl5d=1;
    TF2 *fg15d = new TF2("fg15d","log(([0]*y**4 + [1]*x**2 + [2]*y**2*[16]**2 + [3]*[17]**2*[16]**2 +  [4]*[15]**2 + [5]*x*y**2 + [6]*y*[16]*y**2 + [7]*y*[16]*x + [8]*[17]*[16]*x + [9]*x*[15] + [10]*[17]*[16]*y**2 + [11]*[15]*y**2 + [12]*[16]*[17]*y*[16] + [13]*[15]*y*[16] + [14]*[17]*[15]*[16])/[18])",-4,4,0.5,2.5);
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
    fg15d->SetParameter(15,c2g5d); //==> c2g
    fg15d->SetParameter(16,kl5d);
    fg15d->SetParameter(17,cg5d); //==> cg
    fg15d->SetParameter(18,norm);//0.013531
    fg15d->SetMinimum(0);
    fg15d->SetLineColor(18);    
    //////////////////////////////////////////////
    // This is to plot the c2 X kt plane , the minimal cg and c2g
    // no isolines of cross sections !
    //////////////////////////////////////////////
    TLegend *leg = new TLegend(0.4,0.02,1.0,0.85);
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
    double L[1588];
    double y[1588];
    double c[1588];
    double cg[1588];
    double c2g[1588];
    double c2g[1588];
    double xsec[1588];
    double xsecerr[1588];
    //double dumb, dumb2; 
    //////////////
    ifstream parpoints("/Users/Xanda/Documents/codes/git/generateHH/fit_minut_maker/list_all_translation.txt");//("list_all_translation_t13.txt");//"list_all_translation.txt");//"list_ascii_13TeV_1483.txt"
    for (int i=0; i<Nfile; i++) { //1483
        parpoints >> L[i] >> y[i] >> c[i] >> cg[i] >> c2g[i] >> xsec[i] >> xsecerr[i];
        //if(L[i]==12.5)cout << i<< " " << L[i] << " " << y[i] << " " << c[i] << " " << cg[i] << " " << c2g[i] << endl;
    }
    parpoints.close();
    /////////////////////////////////////////////
    // by now do only 20 clusters
    
    ifstream cluster_13("LogP_1176/clustering_nev20k_Nclu13_50_5.asc");      
    ifstream cluster_20("LogP_1176/clustering_nev20k_Nclu20_50_5.asc"); 
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
        L15[i] = new TH2D (name,"", 500, -3.8., 3.8., 500, 0.1, 2.9999 );//#kappa_{#lambda} = 15        
        sprintf (name, "L10%d", i);
        L10[i] = new TH2D (name,"", 500, -3.8 , 3.8, 500, 0.1, 2.9999 ); 
        sprintf (name, "L125%d", i);
        L125[i] = new TH2D (name,"", 500, -3.8 , 3.8, 500, 0.1, 2.9999 ); 
        sprintf (name, "L75%d", i);
        L75[i] = new TH2D (name,"", 500, -3.8 , 3.8, 500, 0.1, 2.9999 );
        sprintf (name, "L5%d", i);
        L5[i] = new TH2D (name,"", 500, -3.8 , 3.8, 500, 0.1, 2.9999 );
        sprintf (name, "L35%d", i);
        L35[i] = new TH2D (name,"", 500, -3.8 , 3.8, 500, 0.1, 2.9999 );
        sprintf (name, "L24%d", i);
        L24[i] = new TH2D (name,"", 500, -3.8 , 3.8, 500, 0.1, 2.9999 );
        sprintf (name, "L1%d", i);
        L1[i] = new TH2D (name,"", 500, -3.8 , 3.8, 500, 0.1, 2.9999 );
        //
        sprintf (name, "Lm15%d", i);
        Lm15[i] = new TH2D (name,"", 500, -3.8 , 3.8, 500, 0.1, 2.9999 );
        sprintf (name, "Lm125%d", i);
        Lm125[i] = new TH2D (name,"", 500, -3.8 , 3.8, 500, 0.1, 2.9999 ); 
        sprintf (name, "Lm10%d", i);
        Lm10[i] = new TH2D (name,"", 500, -3.8 , 3.8, 500, 0.1, 2.9999 ); 
        sprintf (name, "Lm75%d", i);
        Lm75[i] = new TH2D (name,"", 500, -3.8 , 3.8, 500, 0.1, 2.9999 );
        sprintf (name, "Lm5%d", i);
        Lm5[i] = new TH2D (name,"", 500, -3.8 , 3.8, 500, 0.1, 2.9999 );
        sprintf (name, "Lm35%d", i);
        Lm35[i] = new TH2D (name,"", 500, -3.8 , 3.8, 500, 0.1, 2.9999 );
        sprintf (name, "Lm24%d", i);
        Lm24[i] = new TH2D (name,"", 500, -3.8 , 3.8, 500, 0.1, 2.9999 );  
        //
        sprintf (name, "hL15%d", i);
        hL15[i] = new TH2D (name,"", 500, -3.8 , 3.8, 500, 0.1, 2.9999 );
        sprintf (name, "hL10%d", i);
        hL10[i] = new TH2D (name,"", 500, -3.8 , 3.8, 500, 0.1, 2.9999 ); 
        sprintf (name, "hL125%d", i);
        hL125[i] = new TH2D (name,"", 500, -3.8 , 3.8, 500, 0.1, 2.9999 ); 
        sprintf (name, "hL75%d", i);
        hL75[i] = new TH2D (name,"", 500, -3.8 , 3.8, 500, 0.1, 2.9999 );
        sprintf (name, "hL5%d", i);
        hL5[i] = new TH2D (name,"", 500, -3.8 , 3.8, 500, 0.1, 2.9999 );
        sprintf (name, "hL35%d", i);
        hL35[i] = new TH2D (name,"", 500, -3.8 , 3.8, 500, 0.1, 2.9999 );
        sprintf (name, "hL24%d", i);
        hL24[i] = new TH2D (name,"", 500, -3.8 , 3.8, 500, 0.1, 2.9999 );
        sprintf (name, "hL1%d", i);
        hL1[i] = new TH2D (name,"", 500, -3.8 , 3.8, 500, 0.1, 2.9999 );
        //
        sprintf (name, "hLm15%d", i);
        hLm15[i] = new TH2D (name,"", 500, -3.8 , 3.8, 500, 0.1, 2.9999 );
        sprintf (name, "hLm125%d", i);
        hLm125[i] = new TH2D (name,"", 500, -3.8 , 3.8, 500, 0.1, 2.9999 ); 
        sprintf (name, "hLm10%d", i);
        hLm10[i] = new TH2D (name,"", 500, -3.8 , 3.8, 500, 0.1, 2.9999 ); 
        sprintf (name, "hLm75%d", i);
        hLm75[i] = new TH2D (name,"", 500, -3.8 , 3.8, 500, 0.1, 2.9999 );
        sprintf (name, "hLm5%d", i);
        hLm5[i] = new TH2D (name,"", 500, -3.8 , 3.8, 500, 0.1, 2.9999 );
        sprintf (name, "hLm35%d", i);
        hLm35[i] = new TH2D (name,"", 500, -3.8 , 3.8, 500, 0.1, 2.9999 );
        sprintf (name, "hLm24%d", i);
        hLm24[i] = new TH2D (name,"", 500, -3.8 , 3.8, 500, 0.1, 2.9999 );
    }// close define histos
    int isamp;
    
    
    
    int head20[20]= {409,425,423,430,577,1190,1109,819,807,748,1336,588,820,289,922,1251,608,777,852,1228};    
    int head13[20]= {225 ,741 ,496 ,207 ,223 ,482 ,577 ,1154 ,358 ,871 ,1068 ,622 ,73};//826, 348, 762, 298, 675, 804, 945, 335, 700, 717, 1221, 983, 1195};   
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
    //////////////////////////////////////////
    TGraph2D *gm105d = new TGraph2D(44);//(118);
    gm105d->SetMarkerStyle(20);
    gm105d->SetMarkerSize(2);
    gm105d->SetTitle("0");
    int jm10=0;
    /////////////////////////////////////////
    // fill the histos == only with cgs diff of 0
    int iclu=-1; int counter=0;
    for (int i=0; i<Nfile; i++) { // 1147
        //cout<<"nodes : "<<Nclu<<endl;
        if (Nclu==20) cluster_20 >> isamp;
        else if (Nclu==13) cluster_13 >> isamp;
        else if (Nclu==10) cluster_10 >> isamp;
        //
        for (int j=0; j<Nclu; j++) { if (isamp==head[j]) {cout << "head = " << isamp << endl; iclu++; }} 
        //
        //if (isamp> 1300) isamp = 2;
        if (L[isamp]==15 && ( cg[isamp]==0 && c2g[isamp]==0 )) {
            L15[iclu]->Fill(c[isamp],y[isamp]);
            for (int j=0; j<Nclu; j++) { if (isamp==head[j]) hL15[iclu]->Fill(c[isamp],y[isamp]);};
        } else if (L[isamp]==10 && (cg[isamp]==0 && c2g[isamp]==0)) {
            L10[iclu]->Fill(c[isamp],y[isamp]);
            for (int j=0; j<Nclu; j++) { if (isamp==head[j]) hL10[iclu]->Fill(c[isamp],y[isamp]);};
            //cout<<"clusters with lamb=10: "<<iclu<<  endl;
            if(c[isamp] =-3)cout<<"L10 "<<" "<<isamp<<" "<< c[isamp]<<" "<< y[isamp]<<" "<<endl;
        } else if (L[isamp]==12.5 && cg[isamp]==0 && c2g[isamp]==0) {
            L125[iclu]->Fill(c[isamp],y[isamp]);
            for (int j=0; j<Nclu; j++) { if (isamp==head[j]) hL125[iclu]->Fill(c[isamp],y[isamp]);};
            //cout<<" entered 12.5 " <<iclu<<" " <<counter<<" "  << isamp<< " " << L[isamp] << " " << y[isamp] << " " << c[isamp] << " " << cg[isamp] << " " << c2g[isamp]<< endl;
            //counter++;
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
            double fit3d = (fm10->Eval(c[isamp],y[isamp]));
            double fit5d = 0.013531*(fgm105d->Eval(c[isamp],y[isamp]));
            gm105d->SetPoint(jm10, c[isamp],y[isamp], 100*(fit3d - fit5d)/(fit3d)); 
            jm10++;
            //cout<<jm10<<" "<<isamp<<" "<< c[isamp]<<" "<< y[isamp]<<" "<<fit3d <<" "<< fit5d<<" diff: " <<100*(fit3d - fit5d)/(fit3d)<< endl;
        } else if (L[isamp]==-12.5 && (cg[isamp]==0 && c2g[isamp]==0)) {
            Lm125[iclu]->Fill(c[isamp],y[isamp]);
            for (int j=0; j<Nclu; j++) { if (isamp==head[j]) hLm125[iclu]->Fill(c[isamp],y[isamp]);};
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
    TLatex* text1 = new TLatex();
    text1->SetTextSize(0.12);
    text1->DrawLatex(0.5,0.5,"LHC13 ");
    text1->Draw("same");
    text1->SetTextSize(0.09);
    text1->DrawLatex(0.5,0.3,"c_{g} = c_{2g} = 0 ");
    text1->Draw("same");
/*    C1_1->SetTicks(2,2);
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
            fg15d->Draw("cont3SAME");
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
 */
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
            //f24->Draw("cont3SAME");
            fg245d->Draw("cont3SAME");
            L24[iclu]->Draw("PSAME");
        } else {
            L24[iclu]->Draw("PSAME");
        }
        leg->AddEntry(L24[iclu], lege20[iclu], "P");
        hL24[iclu]->SetMarkerColor(mc[iclu]);
        hL24[iclu]->SetMarkerStyle(mt[iclu]);
        hL24[iclu]->SetMarkerSize(2.5);
       // hL24[iclu]->Draw("PSAME");
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
            //f35->Draw("cont3SAME");
            fg355d->Draw("cont3SAME");
            L35[iclu]->Draw("PSAME");
        } else {
            L35[iclu]->Draw("PSAME");
        }
        hL35[iclu]->SetMarkerColor(mc[iclu]);
        hL35[iclu]->SetMarkerStyle(mt[iclu]);
        hL35[iclu]->SetMarkerSize(2.5);
      //  hL35[iclu]->Draw("PSAME");
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
            //f5->Draw("cont3SAME");
            fg55d->Draw("cont3SAME");
            L5[iclu]->Draw("PSAME");
        } else {
            L5[iclu]->Draw("PSAME");
        }
        hL5[iclu]->SetMarkerColor(mc[iclu]);
        hL5[iclu]->SetMarkerStyle(mt[iclu]);
        hL5[iclu]->SetMarkerSize(2.5);
      //  hL5[iclu]->Draw("PSAME");
    }
    //leg->Draw("same");
    TLatex* text = new TLatex();
    text->SetTextSize(0.08);
    text->DrawLatex(-3.2,2.7,"#kappa_{#lambda} = 5");
    text->Draw("same");  
    //////////////////////////////////////
    C1->cd(5);
    C1_5->SetTicks(2,2);
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
            //fm24->Draw("cont3SAME");
            fgm245d->Draw("cont3SAME");
            Lm24[iclu]->Draw("PSAME");
        } else {
            Lm24[iclu]->Draw("PSAME");
        }
        hLm24[iclu]->SetMarkerColor(mc[iclu]);
        hLm24[iclu]->SetMarkerStyle(mt[iclu]);
        hLm24[iclu]->SetMarkerSize(2.5);
      //  hLm24[iclu]->Draw("PSAME");
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
            //fm35->Draw("cont3SAME");
            fgm355d->Draw("cont3SAME");
            Lm35[iclu]->Draw("PSAME");
        } else {
            Lm35[iclu]->Draw("PSAME");
        }
        hLm35[iclu]->SetMarkerColor(mc[iclu]);
        hLm35[iclu]->SetMarkerStyle(mt[iclu]);
        hLm35[iclu]->SetMarkerSize(2.5);
      //  hLm35[iclu]->Draw("PSAME");
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
            //fm5->Draw("cont3SAME");
            fgm55d->Draw("cont3SAME");
            Lm5[iclu]->Draw("PSAME");
        } else {
            Lm5[iclu]->Draw("PSAME");
        }
        //leg->AddEntry(Lm15[iclu], lege20[iclu], "P");
        hLm5[iclu]->SetMarkerColor(mc[iclu]);
        hLm5[iclu]->SetMarkerStyle(mt[iclu]);
        hLm5[iclu]->SetMarkerSize(2.5);
     //   hLm5[iclu]->Draw("PSAME");
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
            //f75->Draw("cont3SAME");
            fg755d->Draw("cont3SAME");
            L75[iclu]->Draw("PSAME");
        } else {
            L75[iclu]->Draw("PSAME");
        }
        hL75[iclu]->SetMarkerColor(mc[iclu]);
        hL75[iclu]->SetMarkerStyle(mt[iclu]);
        hL75[iclu]->SetMarkerSize(2.5);
       // hL75[iclu]->Draw("PSAME");
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
            //f10->Draw("cont3SAME");
            fg105d->Draw("cont3SAME");
            L10[iclu]->Draw("PSAME");
        } else {
            L10[iclu]->Draw("PSAME");
        }
        hL10[iclu]->SetMarkerColor(mc[iclu]);
        hL10[iclu]->SetMarkerStyle(mt[iclu]);
        hL10[iclu]->SetMarkerSize(2.5);
      //  hL10[iclu]->Draw("PSAME");
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
            //f125->Draw("cont3SAME");
            fg1255d->Draw("cont3SAME");
            L125[iclu]->Draw("PSAME");
        } else {
            L125[iclu]->Draw("PSAME");
        }
        hL125[iclu]->SetMarkerColor(mc[iclu]);
        hL125[iclu]->SetMarkerStyle(mt[iclu]);
        hL125[iclu]->SetMarkerSize(2.5);
      //  hL125[iclu]->Draw("PSAME");
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
            //f15->Draw("cont3SAME");
            fg155d->Draw("cont3SAME");
            L15[iclu]->Draw("PSAME");
        } else {
            L15[iclu]->Draw("PSAME");
        }
        hL15[iclu]->SetMarkerColor(mc[iclu]);
        hL15[iclu]->SetMarkerStyle(mt[iclu]);
        hL15[iclu]->SetMarkerSize(2.5);
       // hL15[iclu]->Draw("PSAME");
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
            //fm75->Draw("cont3SAME");
            fgm755d->Draw("cont3SAME");
            Lm75[iclu]->Draw("PSAME");
        } else {
            Lm75[iclu]->Draw("PSAME");
        }
        hLm75[iclu]->SetMarkerColor(mc[iclu]);
        hLm75[iclu]->SetMarkerStyle(mt[iclu]);
        hLm75[iclu]->SetMarkerSize(2.5);
       // hLm75[iclu]->Draw("PSAME");
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
            //fm10->Draw("cont3SAME");
            fgm105d->Draw("cont3SAME");
            Lm10[iclu]->Draw("PSAME");
        } else {
            Lm10[iclu]->Draw("PSAME");
        }
        hLm10[iclu]->SetMarkerColor(mc[iclu]);
        hLm10[iclu]->SetMarkerStyle(mt[iclu]);
        hLm10[iclu]->SetMarkerSize(2.5);
       // hLm10[iclu]->Draw("PSAME");
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
            //fm125->Draw("cont3SAME");
            fgm1255d->Draw("cont3SAME");            
            Lm125[iclu]->Draw("PSAME");
        } else {
            Lm125[iclu]->Draw("PSAME");
        }
        hLm125[iclu]->SetMarkerColor(mc[iclu]);
        hLm125[iclu]->SetMarkerStyle(mt[iclu]);
        hLm125[iclu]->SetMarkerSize(2.5);
       // hLm125[iclu]->Draw("PSAME");
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
            //fm15->Draw("cont3SAME");
            fgm155d->Draw("cont3SAME");
            Lm15[iclu]->Draw("PSAME");
        } else {
            Lm15[iclu]->Draw("PSAME");
        }
        hLm15[iclu]->SetMarkerColor(mc[iclu]);
        hLm15[iclu]->SetMarkerStyle(mt[iclu]);
        hLm15[iclu]->SetMarkerSize(2.5);
        //hLm15[iclu]->Draw("PSAME");
    }
    //leg->Draw("same");
    text->SetTextSize(0.08);
    text->DrawLatex(-3.2,2.7,"#kappa_{#lambda} = -15");
    text->Draw("same");
    //////////////////////////////////
    sprintf(nameplot,"clusters5D_clu_noc2_%d_1053.png",Nclu);    
    C1->Print(nameplot);
    sprintf(nameplot,"clusters5D_clu_noc2_%d_1053.pdf",Nclu);    
    C1->Print(nameplot);
    ////////////////////////////////////////////
    //
    // comparison points / CX
    //
    /////////////////////////////////////////////
    //int nmin=0;
    //int nmax=899;
    double cross_section[1800];
    double dumb;
    double par0[1800];
    double par1[1800];
    double par2[1800];
    double par3[1800];
    double par4[1800];
    /////////////////////////////////
    // Read in the cross section values and the parameters space points
    ifstream XSvals;
    XSvals.open("/Users/Xanda/Documents/codes/git/generateHH/fit_minut_maker/list_all_translation.txt");//("/Users/Xanda/Documents/codes/git/generateHH/fit_minut_maker/all_CX_20k_opositecgw.ascii");
    for (int i=0; i<Nfile; i++) {//1147
        XSvals >> par0[i] >> par1[i] >> par2[i] >> par3[i] >> par4[i] >> cross_section[i] >> dumb;
        //cout << "For point i = " << i << "pars are " << par0[i] << " " << par1[i] << " " << par2[i] 
        //	 << " " << par3[i] << " " << par4[i] << " and xs is " << cross_section[i] << endl;
    }
    ///////////
    int j15=0,jm15=0,j10=0,jm10=0,j75=0,jm75=0,j35=0,jm35=0,j24=0,jm24=0,j125=0,jm125=0,j1=0,j5=0,jm5=0;
    TGraph2D *g15 = new TGraph2D(46);//(118);
    g15->SetMarkerStyle(20);
    g15->SetMarkerSize(1.7);
    g15->SetTitle(" #scale[2.2]{                  #kappa_{#lambda} = 15}  ; c_{2} ; #kappa_{t}");
    //
    TGraph2D *gm15 = new TGraph2D(46);//(118);
    gm15->SetMarkerStyle(20);
    gm15->SetMarkerSize(1.7);
    gm15->SetTitle(" #scale[2.2]{                  #kappa_{#lambda} = -15}  ; c_{2} ; #kappa_{t} ");
    //gm15->GetXaxis()->SetTitle("c_{2}");
    //gm15->GetYaxis()->SetTitle("#kappa_{t}");
    //
    TGraph2D *g10 = new TGraph2D(50);//(118);
    g10->SetMarkerStyle(20);
    g10->SetMarkerSize(1.7);
    g10->SetTitle(" #scale[2.2]{                  #kappa_{#lambda} = 10}  ; c_{2} ; #kappa_{t} ");
    //
    TGraph2D *gm10 = new TGraph2D(46);//(118);
    gm10->SetMarkerStyle(20);
    gm10->SetMarkerSize(1.7);
    gm10->SetTitle(" #scale[2.2]{                  #kappa_{#lambda} = -10}  ; c_{2} ; #kappa_{t} ");
    //
    TGraph2D *g75 = new TGraph2D(67);//(118);
    g75->SetMarkerStyle(20);
    g75->SetMarkerSize(1.7);
    g75->SetTitle(" #scale[2.2]{                  #kappa_{#lambda} = 7.5}  ; c_{2} ; #kappa_{t} ");
    //
    TGraph2D *gm75 = new TGraph2D(47);//(118);
    gm75->SetMarkerStyle(20);
    gm75->SetMarkerSize(1.7);
    gm75->SetTitle(" #scale[2.2]{                  #kappa_{#lambda} = -7.5}  ; c_{2} ; #kappa_{t} ");
    //
    TGraph2D *g35 = new TGraph2D(62);//(118);
    g35->SetMarkerStyle(20);
    g35->SetMarkerSize(1.7);
    g35->SetTitle(" #scale[2.2]{                  #kappa_{#lambda} = 3.5}  ; c_{2} ; #kappa_{t} ");
    //
    TGraph2D *gm35 = new TGraph2D(54);//(118);
    gm35->SetMarkerStyle(20);
    gm35->SetMarkerSize(1.7);
    gm35->SetTitle(" #scale[2.2]{                  #kappa_{#lambda} = -3.5}  ; c_{2} ; #kappa_{t} ");
    //
    TGraph2D *g125 = new TGraph2D(46);//(118);
    g125->SetMarkerStyle(20);
    g125->SetMarkerSize(1.7);
    g125->SetTitle(" #scale[2.2]{                  #kappa_{#lambda} = 12.5}  ; c_{2} ; #kappa_{t} ");
    //
    TGraph2D *gm125 = new TGraph2D(45);//(118);
    gm125->SetMarkerStyle(20);
    gm125->SetMarkerSize(1.7);
    gm125->SetTitle(" #scale[2.2]{                  #kappa_{#lambda} = -12.5}  ; c_{2} ; #kappa_{t} ");
    //
    TGraph2D *g5 = new TGraph2D(66);//(118);
    g5->SetMarkerStyle(20);
    g5->SetMarkerSize(1.7);
    g5->SetTitle(" #scale[2.2]{                  #kappa_{#lambda} = 5}  ; c_{2} ; #kappa_{t} ");
    //
    TGraph2D *gm5 = new TGraph2D(50);//(118);
    gm5->SetMarkerStyle(20);
    gm5->SetMarkerSize(1.7);
    gm5->SetTitle(" #scale[2.2]{                  #kappa_{#lambda} = -5} ; c_{2} ; #kappa_{t} ");
    //
    TGraph2D *g24 = new TGraph2D(51);//(118);
    g24->SetMarkerStyle(20);
    g24->SetMarkerSize(1.7);
    g24->SetTitle(" #scale[2.2]{                  #kappa_{#lambda} = 2.4}  ; c_{2} ; #kappa_{t} ");
    //
    TGraph2D *gm24 = new TGraph2D(50);//(118);
    gm24->SetMarkerStyle(20);
    gm24->SetMarkerSize(1.7);
    gm24->SetTitle(" #scale[2.2]{                  #kappa_{#lambda} = -2.4} ; c_{2} ; #kappa_{t} ");
    //
    TGraph2D *g1 = new TGraph2D(58);//(118);
    g1->SetMarkerStyle(20);
    g1->SetMarkerSize(1.7);
    g1->SetTitle(" #scale[2.2]{                  #kappa_{#lambda} = 1} ; c_{2} ; #kappa_{t} ");
    //
    for (unsigned int ii = 0; ii < Nfile; ii++){//1147
        if( par3[ii] ==0 && par4[ii] ==0 && par0[ii]==15.0 && par1[ii] > 0.4 && cross_section[ii] >0.00001 &&  cross_section[ii] <10000 ) {
        double fit = 0.013531*exp(fg155d->Eval(par2[ii], par1[ii]));
        //cout<<" 15 "<<j15<<" "<<ii<<" " << par2[ii]<<" "<< par1[ii]<<" "<<fit <<" "<< cross_section[ii]<<" diff: " <<(fit - cross_section[ii])/fit<< endl;
        g15->SetPoint(j15, par2[ii], par1[ii], 100*(fit - cross_section[ii])/fit); 
        j15++;
        }  
        if( par3[ii] ==0 && par4[ii] ==0 && par0[ii]==-15.0 && par1[ii] > 0.4 && cross_section[ii] >0.00001 &&  cross_section[ii] <10000 ) {
            double fit = 0.013531*exp(fgm155d->Eval(par2[ii], par1[ii]));
          ///  cout<<" -15 " <<jm15<<" "<<ii<<" " << par2[ii]<<" "<< par1[ii]<<" "<<fit <<" "<< cross_section[ii]<<" diff: " <<(fit - cross_section[ii])/fit<< endl;
            gm15->SetPoint(jm15, par2[ii], par1[ii], 100*(fit - cross_section[ii])/fit); 
            jm15++;
        }          
        if( par3[ii] ==0 && par4[ii] ==0 && par0[ii]==10.0 && cross_section[ii] >0.00001 &&  cross_section[ii] <10000 ) {
            double fit = 0.013531*exp(fg105d->Eval(par2[ii], par1[ii]));//
          //  cout<<" 10 " <<j10<<" "<<ii<<" " << par2[ii]<<" "<< par1[ii]<<" "<<fit <<" "<< cross_section[ii]<<" diff: " <<(fit - cross_section[ii])/fit<< endl;
            g10->SetPoint(j10, par2[ii], par1[ii], 100*(fit - cross_section[ii])/fit); 
            j10++;
        }  
        if( par3[ii] ==0 && par4[ii] ==0 && par0[ii]==-10.0 && cross_section[ii] >0.00001 &&  cross_section[ii] <10000 ) {
            double fit = 0.013531*exp(fgm105d->Eval(par2[ii], par1[ii]));
           // cout<<" -10 " <<jm10<<" "<<ii<<" " << par2[ii]<<" "<< par1[ii]<<" "<<fit <<" "<< cross_section[ii]<<" diff: " <<(fit - cross_section[ii])/fit<< endl;
            gm10->SetPoint(jm10, par2[ii], par1[ii], 100*(fit - cross_section[ii])/fit); 
            jm10++;
        }  
        if( par3[ii] ==0 && par4[ii] ==0 && par0[ii]==12.5 && cross_section[ii] >0.00001 &&  cross_section[ii] <10000 ) {
            double fit = 0.013531*exp(fg1255d->Eval(par2[ii], par1[ii]));
          //  cout<<" 12.5 " <<j125<<" "<<ii<<" " << par2[ii]<<" "<< par1[ii]<<" "<<fit <<" "<< cross_section[ii]<<" diff: " <<(fit - cross_section[ii])/fit<< endl;
            g125->SetPoint(j125, par2[ii], par1[ii], 100*(fit - cross_section[ii])/fit); 
            j125++;
        }  
        if( par3[ii] ==0 && par4[ii] ==0 && par0[ii]==-12.5 && par1[ii] > 0.4 && cross_section[ii] >0.00001 &&  cross_section[ii] <10000 ) {
            double fit = 0.013531*exp(fgm1255d->Eval(par2[ii], par1[ii]));
           // cout<<" -12.5 " <<jm125<<" "<<ii<<" " << par2[ii]<<" "<< par1[ii]<<" "<<fit <<" "<< cross_section[ii]<<" diff: " <<(fit - cross_section[ii])/fit<< endl;
            gm125->SetPoint(jm125, par2[ii], par1[ii], 100*(fit - cross_section[ii])/fit); 
            jm125++;
        }  
        if( par3[ii] ==0 && par4[ii] ==0 && par0[ii]==7.5 && cross_section[ii] >0.00001 &&  cross_section[ii] <10000 && par1[ii]>0.45 ) {
            double fit = 0.013531*exp(fg755d->Eval(par2[ii], par1[ii]));
            //if() cout<<" 7.5 " <<j75<<" "<<ii<<" " << par2[ii]<<" "<< par1[ii]<<" "<<fit <<" "<< cross_section[ii]<<" diff: " <<(fit - cross_section[ii])/fit<< endl;
            g75->SetPoint(j75, par2[ii], par1[ii], 100*(fit - cross_section[ii])/fit); 
            j75++;
        }  
        if( par3[ii] ==0 && par4[ii] ==0 && par0[ii]==-7.5 && cross_section[ii] >0.00001 &&  cross_section[ii] <10000 ) {
            double fit = 0.013531*exp(fgm755d->Eval(par2[ii], par1[ii]));
          //  cout<<" -7.5 " <<jm75<<" "<<ii<<" " << par2[ii]<<" "<< par1[ii]<<" "<<fit <<" "<< cross_section[ii]<<" diff: " <<(fit - cross_section[ii])/fit<< endl;
            gm75->SetPoint(jm75, par2[ii], par1[ii], 100*(fit - cross_section[ii])/fit); 
            jm75++;
        } 
        if( par3[ii] ==0 && par4[ii] ==0 && par0[ii]==3.5 && cross_section[ii] >0.00001 &&  cross_section[ii] <10000 ) {
            double fit = 0.013531*exp(fg355d->Eval(par2[ii], par1[ii]));
             if(par1[ii]<0.5) cout<<" 3.5 " <<j35<<" "<<ii<<" " << par2[ii]<<" "<< par1[ii]<<" "<<fit <<" "<< cross_section[ii]<<" diff: " <<(fit - cross_section[ii])/fit<< endl;
            g35->SetPoint(j35, par2[ii], par1[ii], 100*(fit - cross_section[ii])/fit); 
            j35++;
        }  
        if( par3[ii] ==0 && par4[ii] ==0 && par0[ii]==-3.5 && cross_section[ii] >0.00001 &&  cross_section[ii] <10000 ) {
            double fitq = 0.013531*exp(fgm355d->Eval(par2[ii], par1[ii]));
            //cout<<" -3.5 " <<jm35<<" "<<ii<<" " << par0[ii]<<" "<< par1[ii]<<" " << par2[ii]<<" "<< par3[ii]<<" "<< par4[ii]<<" "<<fitq <<" "<< cross_section[ii]<<" diff: " <<(fitq - cross_section[ii])/fitq<< endl;
            gm35->SetPoint(jm35, par2[ii], par1[ii], 100*(fitq - cross_section[ii])/fitq); 
            jm35++;
        } 
        if( par3[ii] ==0 && par4[ii] ==0 && par0[ii]==2.4 && cross_section[ii] >0.00001 &&  cross_section[ii] <10000 ) {
            double fit = 0.013531*exp(fg245d->Eval(par2[ii], par1[ii]));
          //  cout<<" 2.4 " <<j24<<" "<<ii<<" " << par2[ii]<<" "<< par1[ii]<<" "<<fit <<" "<< cross_section[ii]<<" diff: " <<(fit - cross_section[ii])/fit<< endl;
            g24->SetPoint(j24, par2[ii], par1[ii], 100*(fit - cross_section[ii])/fit); 
            j24++;
        }  
        if( par3[ii] ==0 && par4[ii] ==0 && par0[ii]==-2.4 && cross_section[ii] >0.00001 &&  cross_section[ii] <10000 ) {
            double fit = 0.013531*exp(fgm245d->Eval(par2[ii], par1[ii]));
          //  cout<<" -2.4 " <<jm24<<" "<<ii<<" " << par2[ii]<<" "<< par1[ii]<<" "<<fit <<" "<< cross_section[ii]<<" diff: " <<(fit - cross_section[ii])/fit<< endl;
            gm24->SetPoint(jm24, par2[ii], par1[ii], 100*(fit - cross_section[ii])/fit); 
            jm24++;
        } 
        if( par3[ii] ==0 && par4[ii] ==0 && par0[ii]==5 && cross_section[ii] >0.00001 &&  cross_section[ii] <10000 ) {
            double fit = 0.013531*exp(fg55d->Eval(par2[ii], par1[ii]));
          //  cout<<" 5 " <<j5<<" "<<ii<<" " << par2[ii]<<" "<< par1[ii]<<" "<<fit <<" "<< cross_section[ii]<<" diff: " <<(fit - cross_section[ii])/fit<< endl;
            g5->SetPoint(j5, par2[ii], par1[ii], 100*(fit - cross_section[ii])/fit); 
            j5++;
        }  
        if( par3[ii] ==0 && par4[ii] ==0 && par0[ii]==-5 && cross_section[ii] >0.00001 &&  cross_section[ii] <10000 ) {
            double fit = 0.013531*exp(fgm55d->Eval(par2[ii], par1[ii]));
            double diffe =100*(fit - cross_section[ii])/fit;
            //cout<<" -5 " <<jm5<<" "<<ii<<" " << par2[ii]<<" "<< par1[ii]<<" "<<fit <<" "<< cross_section[ii]<<" diff: " <<diffe<< endl;
            gm5->SetPoint(jm5, par2[ii], par1[ii], diffe); 
            jm5++;
        } 
        if( par3[ii] ==0 && par4[ii] ==0 && par0[ii]==1 && cross_section[ii] >0.00001 &&  cross_section[ii] <10000 ) {
            double fit = 0.013531*exp(fg15d->Eval(par2[ii], par1[ii]));
         //   cout<<" 1 " <<j24<<" "<<ii<<" " << par2[ii]<<" "<< par1[ii]<<" "<<fit <<" "<< cross_section[ii]<<" diff: " <<(fit - cross_section[ii])/fit<< endl;
            g1->SetPoint(j1, par2[ii], par1[ii], 100*(fit - cross_section[ii])/fit); 
            j1++;
        } 
    } // close loop in parameters 
    /////////////////////////////////////////////
    const int Number = 3;
    Double_t Red[Number]    = { 1.00, 0.00, 0.00};
    Double_t Green[Number]  = { 0.00, 1.00, 0.00};
    Double_t Blue[Number]   = { 1.00, 0.00, 1.00};
    Double_t Length[Number] = { 0.00, 0.50, 1.00 };
    Int_t nb=30;
    TColor::CreateGradientColorTable(Number,Length,Red,Green,Blue,nb);
    //
    TCanvas *c2 = new TCanvas("c2","Surfaces Drawing Options",2000,1500);
    c2->Divide(4,4); 
    c2->cd(1);
    //TLatex* text1 = new TLatex();
    text1->SetTextSize(0.18);
    text1->DrawLatex(0.5,0.5,"LHC13 ");
    text1->Draw("same");
    text1->SetTextSize(0.12);
    text1->DrawLatex(0.5,0.3,"c_{g} = c_{2g} = 0 ");
    text1->Draw("same");
    //c2_1->SetRightMargin(0.2);
    //c2_1->SetTheta(90.0-0.001);
    //c2_1->SetPhi(0.0+0.001);
    //g1->Draw("Pcolz");
    cout<<"plot 1"<<endl;
    c2->cd(2);
    c2_2->SetRightMargin(0.2);
    c2_2->SetTheta(90.0-0.001);
    c2_2->SetPhi(0.0+0.001);
    g24->Draw("Pcolz");
    cout<<"plot 2.4"<<endl;
    c2->cd(3);
    c2_3->SetRightMargin(0.2);
    c2_3->SetTheta(90.0-0.001);
    c2_3->SetPhi(0.0+0.001);
    g35->Draw("Pcolz");    
    cout<<"plot 3.5"<<endl;
    c2->cd(4);
    c2_4->SetRightMargin(0.2);
    c2_4->SetTheta(90.0-0.001);
    c2_4->SetPhi(0.0+0.001);
    g5->Draw("Pcolz");
    cout<<"plot 5"<<endl;
    c2->cd(5);
    TLatex* text2 = new TLatex();
    text2->SetTextSize(0.18);
    text2->DrawLatex(0.4,0.4,"#frac{#sigma_{fit}- #sigma_{MC}}{#sigma_{fit}} (%)"); 
    //
    c2->cd(6);
    c2_6->SetRightMargin(0.2);
    c2_6->SetTheta(90.0-0.001);
    c2_6->SetPhi(0.0+0.001);
    gm24->Draw("Pcolz");
    cout<<"plot -2.4"<<endl;
    c2->cd(7);
    c2_7->SetRightMargin(0.2);
    c2_7->SetTheta(90.0-0.001);
    c2_7->SetPhi(0.0+0.001);
    gm35->Draw("Pcolz");
    cout<<"plot -3.5"<<endl;
    c2->cd(8);
    c2_8->SetRightMargin(0.2);
    c2_8->SetTheta(90.0-0.001);
    c2_8->SetPhi(0.0+0.001);
    gm5->Draw("Pcolz");
    cout<<"plot -5"<<endl;
    //
    c2->cd(9);
    c2_9->SetRightMargin(0.2);
    c2_9->SetTheta(90.0-0.001);
    c2_9->SetPhi(0.0+0.001);
    g75->Draw("Pcolz");
    cout<<"plot 7.5"<<endl;
    c2->cd(10);
    c2_10->SetRightMargin(0.2);
    c2_10->SetTheta(90.0-0.001);
    c2_10->SetPhi(0.0+0.001);
    g10->Draw("Pcolz");
    cout<<"plot 10"<<endl;
    c2->cd(11);
    c2_11->SetRightMargin(0.2);
    c2_11->SetTheta(90.0-0.001);
    c2_11->SetPhi(0.0+0.001);
    g125->Draw("Pcolz");
    cout<<"plot 12.5"<<endl;
    c2->cd(12);
    c2_12->SetRightMargin(0.2);
    c2_12->SetTheta(90.0-0.001);
    c2_12->SetPhi(0.0+0.001);
    g15->Draw("Pcolz");
    cout<<"plot 15"<<endl;
    //
    c2->cd(13);
    c2_13->SetRightMargin(0.2);
    c2_13->SetTheta(90.0-0.001);
    c2_13->SetPhi(0.0+0.001);
    gm75->Draw("Pcolz");
    cout<<"plot -7.5"<<endl;
    c2->cd(14);
    c2_14->SetRightMargin(0.2);
    c2_14->SetTheta(90.0-0.001);
    c2_14->SetPhi(0.0+0.001);
    gm10->Draw("Pcolz");
    cout<<"plot -10"<<endl;
    c2->cd(15);
    c2_15->SetRightMargin(0.2);
    c2_15->SetTheta(90.0-0.001);
    c2_15->SetPhi(0.0+0.001);
    gm125->Draw("Pcolz");
    cout<<"plot -12.5"<<endl;
    c2->cd(16);
    c2_16->SetRightMargin(0.2);
    c2_16->SetTheta(90.0-0.001);
    c2_16->SetPhi(0.0+0.001);
    gm15->Draw("Pcolz");
    cout<<"plot -15"<<endl;
        c2->SaveAs("Diff_c2_kt_ortogonal.pdf");
    cout<<" 15 "<<j15<<" ; -15 "<<jm15<<" ; 10 "<<j10<<" ;  -10 "<<jm10<<" ; 7.5 "<<j75<<" ;  -7.5 "<<jm75<<" ; 3.5 "<<j35<<" ; -3.5 "<<jm35<<" ; 2.4 "<<j24<<" ; -2.4 "<<jm24<<"; 12.5 "<<j125<<";  -12.5 "<<jm125<<" ; 1 "<<j1<<" ; 5 "<<j5<<";  -5 "<<jm5<<endl;
}