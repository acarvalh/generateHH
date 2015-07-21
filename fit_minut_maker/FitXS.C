/////////////////////
/*
 authors:
 Tommaso Dorigo
 Alexandra Oliveira
 */
/*
 execute
 root > .L FitXS.C+
 root > FitXS()
 */

#include "TH2.h"
#include "TF1.h"
#include "TF2.h"
#include "TH1.h"
#include "TH1D.h"
#include "TProfile.h"
#include "TStyle.h"
#include "TCanvas.h" 
#include "TPad.h" 
#include "TFile.h"
#include "TMath.h"
#include "TMinuit.h"
#include "TColor.h"
#include "TROOT.h"
#include "TLatex.h"
// Others
#include "TStopwatch.h"
#include <vector>
#include "TFile.h"
#include "TH1D.h"
#include "TH2D.h"
#include "TH3D.h"
#include "TProfile.h"
#include "TCanvas.h"
#include "TString.h"
#include "TStyle.h"
#include "TChain.h"
#include "TH2.h"
#include "TH1.h"
#include "TF1.h"
#include "TF3.h"
#include "TTree.h"
#include "TKey.h"
#include "TMath.h"
#include "TRandom.h"
#include "TRandom3.h"
#include "Riostream.h"
#include "TVirtualFitter.h"
#include <stdio.h>
#include <math.h>
#include "TGraph2D.h"
#include "Math/GoFTest.h"

#include <iostream>
#include <sstream>
#include <fstream>

using namespace std;

static int Npoints=1431;
static int nmin;
static int nmax;
static double cross_section[1500];
static double par0[1500];
static double par1[1500];
static double par2[1500];
static double par3[1500];
static double par4[1500];

extern "C" void Likelihood(int& npar, double* grad, double& fval, double* xval, int flag) {
  //  cout << "In likelihood" << endl;
  // xval[0:14] are the parameters

  double flike=0.;
    double SMxs = 0.013531; // 1 ; //  in pb as MG model says 1; //
  double A1 = xval[0];
  double A2 = xval[1];
  double A3 = xval[2];
  double A4 = xval[3];
  double A5 = xval[4];
  double A6 = xval[5];
  double A7 = xval[6];
  double A8 = xval[7];
  double A9 = xval[8];
  double A10 = xval[9];
  double A11 = xval[10];
  double A12 = xval[11];
  double A13 = xval[12];
  double A14 = xval[13];
  double A15 = xval[14];
  for (int i=nmin; i<nmax; i++) {
    double kt = par1[i];
    double kl = par0[i];
    double c2 = par2[i];
      double cg =  par3[i]; //  par3[i]; //
    double c2g=  par4[i]; // par4[i]; // 
    double xs = SMxs*(
       A1*pow(kt,4)+ 
       A2*pow(c2,2)+
       (A3*pow(kt,2)+A4*pow(cg,2))*pow(kl,2)+
       A5*pow(c2g,2)+
       (A6*c2+A7*kt*kl)*pow(kt,2)+
       (A8*kt*kl+A9*cg*kl)*c2+
       A10*c2*c2g+
       (A11*cg*kl+A12*c2g)*pow(kt,2)+
       (A13*kl*cg+A14*c2g)*kt*kl+A15*cg*c2g*kl);
    double error = 0.1*cross_section[i]; // 0.102*cross_section[i];
    flike += -0.5*pow((xs-cross_section[i])/error,2);
    
    // Add penalty term
    for (int ikt=0; ikt<6; ikt++) {
      double kt=0.5+ikt*0.4;
      for (int ikl=0; ikl<6; ikl++) {
	double kl=-20+8*ikl;
	for (int ic2=0; ic2<6; ic2++) {
	  double c2=-10+ic2*4;
	  for (int icg=0; icg<6; icg++) {
	    double cg=icg*1.2-3;
	    for (int ic2g=0; ic2g<6; ic2g++) {
	      double c2g=ic2g*1.2-3;
	      double xs = 	A1*pow(kt,4)+ 
				A2*pow(c2,2)+
				(A3*pow(kt,2)+A4*pow(cg,2))*pow(kl,2)+
				A5*pow(c2g,2)+
				(A6*c2+A7*kt*kl)*pow(kt,2)+
				(A8*kt*kl+A9*cg*kl)*c2+
				A10*c2*c2g+
				(A11*cg*kl+A12*c2g)*pow(kt,2)+
				(A13*kl*cg+A14*c2g)*kt*kl+A15*cg*c2g*kl;
	      //if (xs<0) flike += exp(-1000*xs);
	    }
	  }	  
	}
      }
    }
  }
  fval = -flike;
}


void FitXS (int nminx, int nmaxx) {
    ////////////////////////////////////////////////////
    // ftp://root.cern.ch/root/doc/ROOTUsersGuideHTML/ch09s05.html
    TStyle *defaultStyle = new TStyle("defaultStyle","Default Style");
    //gStyle->SetOptStat(0);
    //  defaultStyle->SetOptStat(0000);
    //  defaultStyle->SetOptFit(000); 
    //  defaultStyle->SetPalette(1);
    ////////////////////////
    defaultStyle->SetOptStat(0); // remove info box
    /////// pad ////////////
    defaultStyle->SetPadBorderMode(0);
    defaultStyle->SetPadBorderSize(3);
    defaultStyle->SetPadColor(0);
    defaultStyle->SetPadTopMargin(0.08);
    defaultStyle->SetPadBottomMargin(0.16);
    //defaultStyle->SetPadRightMargin(2.8);
    //defaultStyle->SetPadLeftMargin(0.16);
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
    //defaultStyle->SetTitleX(0.2);
    //defaultStyle->SetTitleY(0.1);
    //defaultStyle->SetTitleBorderSize(-0.1);  // For the axis titles:
    
    //    defaultStyle->SetTitleColor(1, "XYZ");
    //    defaultStyle->SetTitleFont(42, "XYZ");
    defaultStyle->SetTitleSize(0.06, "XYZ");
    
    // defaultStyle->SetTitleYSize(0.08);
    //defaultStyle->SetTitleXOffset(0.9);
    //defaultStyle->SetTitleYOffset(1.05);
    defaultStyle->SetTitleOffset(0.8, "XY"); // Another way to set the Offset
    
    // For the axis labels:
    defaultStyle->SetLabelColor(1, "XYZ");
    //defaultStyle->SetLabelFont(46, "XYZ");
    //defaultStyle->SetLabelOffset(0.07, "XYZ");
    defaultStyle->SetLabelSize(0.05, "XYZ");
    
    // For the axis:
    //    defaultStyle->SetAxisColor(1, "XYZ");
    defaultStyle->SetStripDecimals(kTRUE);
    defaultStyle->SetTickLength(0.03, "XYZ");
    defaultStyle->SetNdivisions(5, "XYZ");
    //    defaultStyle->SetPadTickX(1);   // To get tick marks on the opposite side of the frame
    //    defaultStyle->SetPadTickY(1);
    defaultStyle->cd();

    ///////////////////////////////////////////

  nmin=nminx;
  nmax=nmaxx;
  if (nmin<0) nmin=0;
  if (nmax>Npoints) nmax=Npoints;
  // Read in the cross section values and the parameters space points
  ifstream XSvals;
  XSvals.open("all_CX.ascii");
  for (int i=nmin; i<nmax; i++) {
    XSvals >> par0[i] >> par1[i] >> par2[i] >> par3[i] >> par4[i] >> cross_section[i];
    //cout << "For point i = " << i << "pars are " << par0[i] << " " << par1[i] << " " << par2[i] 
    //	 << " " << par3[i] << " " << par4[i] << " and xs is " << cross_section[i] << endl;
  }
  
  cout << "**********************************************" << endl;
  
  // Likelihood maximization
  // -----------------------  
  // Minuit routine
  TMinuit rmin(2);
  rmin.SetFCN(Likelihood);
  // Main initialization member function for MINUIT
  rmin.mninit(5,6,7);
  // Parameters needed to be unambiguous with MINOS
  int iflag=0; // You can use this for selection
  double arglis[4];
  //arglis[0]=2;
  arglis[0]=1;
  // Sets the strategy to be used in calculating first and second derivatives 
  // and in certain minimization methods. 1 is default
  rmin.mnexcm("SET STR", arglis, 1, iflag);
  // Set fit parameters
  
    double Start[15]  ={ 0.030642286182762914, 0.1502216514258229, 0.004287943879883482, 0.0016389029559123376, 0.01930407853512356, -0.12540818099961384, -0.02048425705808435,  0.04246248185144494, 0.02590360491719489,  -0.05255851386689693,  -0.010393610828707423,  0.02770339496466713,  0.005468667874225809,  -0.011297300064522649,  -0.02261561923548796}; // cx in pb
  //  double Start[15] = {2.2646, 1.102, 0.316898, 16, 192, -3, -1, 1, 7, 15, -8, -23, 4, 9, 200}; // normalized to SM
    double Step[15];// ={ 0.01, 0.01, 0.01, 0.01, 0.01, 0.01, 0.01, 0.01, 0.01, 0.01, 0.01, 0.01, 0.01, 0.01, 0.01 }; //={0.01};
  double Min[15]; // ={-3.1415926};
  double Max[15]; // = {3.1415926}; 
  for (int i=0; i<15; i++) {
    //Start[i]=1.;
    Step[i]=1;
    Min[i]=-100000;
    Max[i]=+100000;
  }
  TString parnamEj[15]={"A1","A2","A3","A4","A5","A6","A7","A8","A9","A10","A11","A12","A13","A14","A15"};
  for (int i=0; i<15; i++) {
    rmin.mnparm(i, parnamEj[i],  Start[i], Step[i], Min[i], Max[i], iflag);
  }
  // Instructs Minuit to call subroutine FCN with the value of IFLAG
  rmin.mnexcm("call fcn", arglis, 1, iflag); // command executed normally
  // Causes minimization of the function by the method of Migrad
  rmin.mnexcm("mini", arglis, 0, iflag);
  // Read results
  double a[15], err[15], pmin, pmax;
  int ivar;
  for (int i=0; i<15; i++) {
    rmin.mnpout (i, parnamEj[i], a[i], err[i], pmin, pmax, ivar);
  }

  // End of program
  // --------------
  gROOT->Time();
    cout<<endl<<" Making plots "<<endl;
    cout<<"$A_1$ = "<<a[0]<<" & $A_2$ = "<<a[1]<<" & $A_3$ = "<<a[2]<<" & $A_4$ = "<<a[3]<<" & $A_5$ = "<<a[4]<< " \\ "<<endl;
    cout<<"$A_6$ = "<<a[5]<<" $A_7$ =  "<<a[6]<<" & $A_8$ =  "<<a[7]<<" & $A_9$ =  "<<a[8]<<" & $A_{10}$ =  "<<a[9]<< " \\ "<<endl;
    cout<<"$A_{11}$ =  "<<a[10]<<"& $A_{12}$ = "<<a[11]<<" & $A_{13}$ =  "<<a[12]<<" & $A_{14}$ =  "<<a[13]<<" & $A_{15}$ =  "<<a[14]<< " \\ "<<endl;
    /////////////////
    // plot the CX 
    ////////////////
    // 
    double norm = 1;// 0.013531;// 
    double kt5d=1.0;
    double kl5d=1.0;
    double c25d=0.0;
    double mincg = -2.99, maxcg=2.99;
    // cg ===> x 
    // c2g ===> y
    TF2 *fg2 = new TF2("fg","([0]*[15]**4 + [1]*[17]**2 + [2]*[15]**2*[16]**2 + [3]*x**2*[16]**2 +  [4]*y**2 + [5]*[17]*[15]**2 + [6]*[15]*[16]*[15]**2 + [7]*[15]*[16]*[17] + [8]*x*[16]*[17] + [9]*[17]*y + [10]*x*[16]*[15]**2 + [11]*y*[15]**2 + [12]*[16]*x*[15]*[16] + [13]*y*[15]*[16] + [14]*x*y*[16])/[18]",mincg,maxcg,mincg,maxcg);
    fg2->SetParameter(0,a[0]);
    fg2->SetParameter(1,a[1]);
    fg2->SetParameter(2,a[2]);    
    fg2->SetParameter(3,a[3]);
    fg2->SetParameter(4,a[4]);
    fg2->SetParameter(5,a[5]); 
    fg2->SetParameter(6,a[6]);
    fg2->SetParameter(7,a[7]);
    fg2->SetParameter(8,a[8]); 
    fg2->SetParameter(9,a[9]);
    fg2->SetParameter(10,a[10]);
    fg2->SetParameter(11,a[11]); 
    fg2->SetParameter(12,a[12]);    
    fg2->SetParameter(13,a[13]);
    fg2->SetParameter(14,a[14]);
    fg2->SetTitle("");
    fg2->SetParameter(15,kt5d);    
    fg2->SetParameter(16,kl5d);
    fg2->SetParameter(17,c25d);
    fg2->SetParameter(18,norm); //0.013531
    fg2->SetMinimum(0);
    ////////////////////////////////
    kt5d=1.0;
    kl5d=10.0;
    c25d=0.0;
    // cg ===> x 
    // c2g ===> y
    TF2 *fg10 = new TF2("fg10","([0]*[15]**4 + [1]*[17]**2 + [2]*[15]**2*[16]**2 + [3]*x**2*[16]**2 +  [4]*y**2 + [5]*[17]*[15]**2 + [6]*[15]*[16]*[15]**2 + [7]*[15]*[16]*[17] + [8]*x*[16]*[17] + [9]*[17]*y + [10]*x*[16]*[15]**2 + [11]*y*[15]**2 + [12]*[16]*x*[15]*[16] + [13]*y*[15]*[16] + [14]*x*y*[16])/[18]",mincg,maxcg,mincg,maxcg);
    fg10->SetParameter(0,a[0]);
    fg10->SetParameter(1,a[1]);
    fg10->SetParameter(2,a[2]);    
    fg10->SetParameter(3,a[3]);
    fg10->SetParameter(4,a[4]);
    fg10->SetParameter(5,a[5]); 
    fg10->SetParameter(6,a[6]);
    fg10->SetParameter(7,a[7]);
    fg10->SetParameter(8,a[8]); 
    fg10->SetParameter(9,a[9]);
    fg10->SetParameter(10,a[10]);
    fg10->SetParameter(11,a[11]); 
    fg10->SetParameter(12,a[12]);    
    fg10->SetParameter(13,a[13]);
    fg10->SetParameter(14,a[14]);
    fg10->SetTitle("");
    fg10->SetParameter(15,kt5d);    
    fg10->SetParameter(16,kl5d);
    fg10->SetParameter(17,c25d);
    fg10->SetParameter(18,norm);// 0.013531
    fg10->SetMinimum(0);
    ////////////////////////////////
    kt5d=1.0;
    kl5d=-10.0;
    c25d=0.0;
    // cg ===> x 
    // c2g ===> y
    TF2 *fgm10 = new TF2("fgm10","([0]*[15]**4 + [1]*[17]**2 + [2]*[15]**2*[16]**2 + [3]*x**2*[16]**2 +  [4]*y**2 + [5]*[17]*[15]**2 + [6]*[15]*[16]*[15]**2 + [7]*[15]*[16]*[17] + [8]*x*[16]*[17] + [9]*[17]*y + [10]*x*[16]*[15]**2 + [11]*y*[15]**2 + [12]*[16]*x*[15]*[16] + [13]*y*[15]*[16] + [14]*x*y*[16])/[18]",mincg,maxcg,mincg,maxcg);
    fgm10->SetParameter(0,a[0]);
    fgm10->SetParameter(1,a[1]);
    fgm10->SetParameter(2,a[2]);    
    fgm10->SetParameter(3,a[3]);
    fgm10->SetParameter(4,a[4]);
    fgm10->SetParameter(5,a[5]); 
    fgm10->SetParameter(6,a[6]);
    fgm10->SetParameter(7,a[7]);
    fgm10->SetParameter(8,a[8]); 
    fgm10->SetParameter(9,a[9]);
    fgm10->SetParameter(10,a[10]);
    fgm10->SetParameter(11,a[11]); 
    fgm10->SetParameter(12,a[12]);    
    fgm10->SetParameter(13,a[13]);
    fgm10->SetParameter(14,a[14]);
    fgm10->SetTitle("");
    fgm10->SetParameter(15,kt5d);    
    fgm10->SetParameter(16,kl5d);
    fgm10->SetParameter(17,c25d);
    fgm10->SetParameter(18,norm);//0.013531
    fgm10->SetMinimum(0);
    //
    cout<<endl<<"Value of the formula in SM point: 0.013531 pb"<<a[0]<<endl;
    cout<<"teste funcao cg , c2g : 0,0 "<< fg2->Eval(0,0)<<endl;
    cout<<"teste funcao cg , c2g : -1,1  "<<  fg2->Eval(-1,1)<<endl;
    cout<<"teste funcao cg , c2g : 1,-1  "<<  fg2->Eval(-1,1)<<endl;
    cout<<" "<<endl;
    ////////////////////////////////////////////////////
    double cg=0.0;
    double c2g=0.0;
    c25d=0.0;
    // cg ===> x  ===> kl
    // c2g ===> y ===> kt
    TF2 *SM0 = new TF2("SM0","(([0]*y**4 + [1]*[17]**2 + [2]*y**2*x**2 + [3]*[15]**2*x**2 +  [4]*[15]**2 + [5]*[17]*y**2 + [6]*y*x*y**2 + [7]*[15]*x*[17] + [8]*[16]*x*[17] + [9]*[17]*y + [10]*[16]*x*[15]**2 + [11]*[16]*y**2 + [12]*x*[16]*[15]*x + [13]*[15]*[15]*x + [14]*[16]*[15])/[18])",-20,20,0.5,2.5);
    SM0->SetParameter(0,a[0]);
    SM0->SetParameter(1,a[1]);
    SM0->SetParameter(2,a[2]);    
    SM0->SetParameter(3,a[3]);
    SM0->SetParameter(4,a[4]);
    SM0->SetParameter(5,a[5]); 
    SM0->SetParameter(6,a[6]);
    SM0->SetParameter(7,a[7]);
    SM0->SetParameter(8,a[8]); 
    SM0->SetParameter(9,a[9]);
    SM0->SetParameter(10,a[10]);
    SM0->SetParameter(11,a[11]); 
    SM0->SetParameter(12,a[12]);    
    SM0->SetParameter(13,a[13]);
    SM0->SetParameter(14,a[14]);
    SM0->SetTitle("");
    SM0->SetParameter(15,cg); //==>y     
    SM0->SetParameter(16,c2g);//==>x
    SM0->SetParameter(17,c25d);
    SM0->SetParameter(18,norm);// 0.013531
    SM0->SetMinimum(0);
    //
    cout<<endl<<"Value of the formula in SM point: 0.013531 pb "<<endl;
    cout<<"teste funcao kl , kt : 1,1 "<< SM0->Eval(1,1)<<endl;
    cout<<"teste funcao kl , kt : -10, 1  "<<  SM0->Eval(-10,1)<<endl;
    cout<<"teste funcao kl , kt : 10, 1  "<<  SM0->Eval(10,1)<<endl;
    ////////////////////////////////
    kt5d=1.0;
    kl5d=1.0;
    c25d=0.0;
    // cg ===> x ==> c2
    // c2g ===> y ==> kt
    TF2 *l1 = new TF2("l1","([0]*y**4 + [1]*x**2 + [2]*y**2*[16]**2 + [3]*[17]**2*[16]**2 +  [4]*[15]**2 + [5]*x*y**2 + [6]*y*[16]*y**2 + [7]*y*[16]*x + [8]*[17]*[16]*x + [9]*x*[15] + [10]*[17]*[16]*y**2 + [11]*[15]*y**2 + [12]*[16]*[17]*y*[16] + [13]*[15]*y*[16] + [14]*[17]*[15]*[16])/[18]",-4,4,0.5,2.5);
    l1->SetParameter(0,a[0]);
    l1->SetParameter(1,a[1]);
    l1->SetParameter(2,a[2]);    
    l1->SetParameter(3,a[3]);
    l1->SetParameter(4,a[4]);
    l1->SetParameter(5,a[5]); 
    l1->SetParameter(6,a[6]);
    l1->SetParameter(7,a[7]);
    l1->SetParameter(8,a[8]); 
    l1->SetParameter(9,a[9]);
    l1->SetParameter(10,a[10]);
    l1->SetParameter(11,a[11]); 
    l1->SetParameter(12,a[12]);    
    l1->SetParameter(13,a[13]);
    l1->SetParameter(14,a[14]);
    l1->SetTitle("");
    l1->SetParameter(15,c2g); //==> c2g
    l1->SetParameter(16,kl5d);
    l1->SetParameter(17,cg); //==> cg
    l1->SetParameter(18,norm);//0.013531
    //l1->->SetRange(1e1,0.1,1e3,1);
    //l1->SetMaximum(4e2);
    l1->SetMinimum(0);
    //
    cout<<endl<<"Value of the formula in SM point: 0.013531 pb"<<a[0]<<endl;
    cout<<"teste funcao cg , c2g : 0,0 "<< l1->Eval(0,1)<<endl;
    cout<<"teste funcao cg , c2g : -1,1  "<<  l1->Eval(-1,1)<<endl;
    cout<<"teste funcao cg , c2g : 1,-1  "<<  l1->Eval(-1,1)<<endl;
    cout<<" "<<endl;
    ////////////////////////////////
    kt5d=1.0;
    kl5d=0.0;
    c25d=0.0;
    // cg ===> x ==> c2
    // c2g ===> y ==> kt
    TF2 *l0 = new TF2("l0","([0]*y**4 + [1]*x**2 + [2]*y**2*[16]**2 + [3]*[17]**2*[16]**2 +  [4]*[15]**2 + [5]*x*y**2 + [6]*y*[16]*y**2 + [7]*y*[16]*x + [8]*[17]*[16]*x + [9]*x*[15] + [10]*[17]*[16]*y**2 + [11]*[15]*y**2 + [12]*[16]*[17]*y*[16] + [13]*[15]*y*[16] + [14]*[17]*[15]*[16])/[18]",-4,4,0.5,2.5);
    l0->SetParameter(0,a[0]);
    l0->SetParameter(1,a[1]);
    l0->SetParameter(2,a[2]);    
    l0->SetParameter(3,a[3]);
    l0->SetParameter(4,a[4]);
    l0->SetParameter(5,a[5]); 
    l0->SetParameter(6,a[6]);
    l0->SetParameter(7,a[7]);
    l0->SetParameter(8,a[8]); 
    l0->SetParameter(9,a[9]);
    l0->SetParameter(10,a[10]);
    l0->SetParameter(11,a[11]); 
    l0->SetParameter(12,a[12]);    
    l0->SetParameter(13,a[13]);
    l0->SetParameter(14,a[14]);
    l0->SetTitle("");
    l0->SetParameter(15,c2g); //==> c2g
    l0->SetParameter(16,kl5d);
    l0->SetParameter(17,cg); //==> cg
    l0->SetParameter(18,norm);//0.013531
    l0->SetMinimum(0);
    //
    cout<<endl<<"Value of the formula in SM point: 0.013531 pb"<<a[0]<<endl;
    cout<<"teste funcao cg , c2g : 0,0 "<< l0->Eval(0,1)<<endl;
    cout<<"teste funcao cg , c2g : -1,1  "<<  l0->Eval(-1,1)<<endl;
    cout<<"teste funcao cg , c2g : 1,-1  "<<  l0->Eval(-1,1)<<endl;
    cout<<" "<<endl;
    ////////////////////////////////
    kt5d=1.0;
    kl5d=2.4;
    c25d=0.0;
    // cg ===> x ==> c2
    // c2g ===> y ==> kt
    TF2 *l24 = new TF2("l24","([0]*y**4 + [1]*x**2 + [2]*y**2*[16]**2 + [3]*[17]**2*[16]**2 +  [4]*[15]**2 + [5]*x*y**2 + [6]*y*[16]*y**2 + [7]*y*[16]*x + [8]*[17]*[16]*x + [9]*x*[15] + [10]*[17]*[16]*y**2 + [11]*[15]*y**2 + [12]*[16]*[17]*y*[16] + [13]*[15]*y*[16] + [14]*[17]*[15]*[16])/[18]",-4,4,0.5,2.5);
    l24->SetParameter(0,a[0]);
    l24->SetParameter(1,a[1]);
    l24->SetParameter(2,a[2]);    
    l24->SetParameter(3,a[3]);
    l24->SetParameter(4,a[4]);
    l24->SetParameter(5,a[5]); 
    l24->SetParameter(6,a[6]);
    l24->SetParameter(7,a[7]);
    l24->SetParameter(8,a[8]); 
    l24->SetParameter(9,a[9]);
    l24->SetParameter(10,a[10]);
    l24->SetParameter(11,a[11]); 
    l24->SetParameter(12,a[12]);    
    l24->SetParameter(13,a[13]);
    l24->SetParameter(14,a[14]);
    l24->SetTitle("");
    l24->SetParameter(15,c2g); //==> c2g
    l24->SetParameter(16,kl5d);
    l24->SetParameter(17,cg); //==> cg
    l24->SetParameter(18,norm);//0.013531
    l24->SetMinimum(0);
    //
    cout<<endl<<"Value of the formula in SM point: 0.013531 pb"<<a[0]<<endl;
    cout<<"teste funcao cg , c2g : 0,0 "<< l24->Eval(0,1)<<endl;
    cout<<"teste funcao cg , c2g : -1,1  "<<  l24->Eval(-1,1)<<endl;
    cout<<"teste funcao cg , c2g : 1,-1  "<<  l24->Eval(-1,1)<<endl;
    cout<<" "<<endl;
    ////////////////////////////////
    kt5d=1.0;
    kl5d=5.0;
    c25d=0.0;
    // cg ===> x ==> c2
    // c2g ===> y ==> kt
    TF2 *l5 = new TF2("l5","([0]*y**4 + [1]*x**2 + [2]*y**2*[16]**2 + [3]*[17]**2*[16]**2 +  [4]*[15]**2 + [5]*x*y**2 + [6]*y*[16]*y**2 + [7]*y*[16]*x + [8]*[17]*[16]*x + [9]*x*[15] + [10]*[17]*[16]*y**2 + [11]*[15]*y**2 + [12]*[16]*[17]*y*[16] + [13]*[15]*y*[16] + [14]*[17]*[15]*[16])/[18]",-4,4,0.5,2.5);
    l5->SetParameter(0,a[0]);
    l5->SetParameter(1,a[1]);
    l5->SetParameter(2,a[2]);    
    l5->SetParameter(3,a[3]);
    l5->SetParameter(4,a[4]);
    l5->SetParameter(5,a[5]); 
    l5->SetParameter(6,a[6]);
    l5->SetParameter(7,a[7]);
    l5->SetParameter(8,a[8]); 
    l5->SetParameter(9,a[9]);
    l5->SetParameter(10,a[10]);
    l5->SetParameter(11,a[11]); 
    l5->SetParameter(12,a[12]);    
    l5->SetParameter(13,a[13]);
    l5->SetParameter(14,a[14]);
    l5->SetTitle("");
    l5->SetParameter(15,c2g); //==> c2g
    l5->SetParameter(16,kl5d);
    l5->SetParameter(17,cg); //==> cg
    l5->SetParameter(18,norm);//0.013531
    l5->SetMinimum(0);
    //
    cout<<endl<<"Value of the formula in SM point: 0.013531 pb"<<a[0]<<endl;
    cout<<"teste funcao cg , c2g : 0,0 "<< l5->Eval(0,1)<<endl;
    cout<<"teste funcao cg , c2g : -1,1  "<<  l5->Eval(-1,1)<<endl;
    cout<<"teste funcao cg , c2g : 1,-1  "<<  l5->Eval(-1,1)<<endl;
    cout<<" "<<endl;
    ////////////////////////////////
    kt5d=1.0;
    kl5d=10.0;
    c25d=0.0;
    // cg ===> x ==> c2
    // c2g ===> y ==> kt
    TF2 *l10 = new TF2("l10","([0]*y**4 + [1]*x**2 + [2]*y**2*[16]**2 + [3]*[17]**2*[16]**2 +  [4]*[15]**2 + [5]*x*y**2 + [6]*y*[16]*y**2 + [7]*y*[16]*x + [8]*[17]*[16]*x + [9]*x*[15] + [10]*[17]*[16]*y**2 + [11]*[15]*y**2 + [12]*[16]*[17]*y*[16] + [13]*[15]*y*[16] + [14]*[17]*[15]*[16])/[18]",-4,4,0.5,2.5);
    l10->SetParameter(0,a[0]);
    l10->SetParameter(1,a[1]);
    l10->SetParameter(2,a[2]);    
    l10->SetParameter(3,a[3]);
    l10->SetParameter(4,a[4]);
    l10->SetParameter(5,a[5]); 
    l10->SetParameter(6,a[6]);
    l10->SetParameter(7,a[7]);
    l10->SetParameter(8,a[8]); 
    l10->SetParameter(9,a[9]);
    l10->SetParameter(10,a[10]);
    l10->SetParameter(11,a[11]); 
    l10->SetParameter(12,a[12]);    
    l10->SetParameter(13,a[13]);
    l10->SetParameter(14,a[14]);
    l10->SetTitle("");
    l10->SetParameter(15,c2g); //==> c2g
    l10->SetParameter(16,kl5d);
    l10->SetParameter(17,cg); //==> cg
    l10->SetParameter(18,norm);//0.013531
    l10->SetMinimum(0);
    //
    cout<<endl<<"Value of the formula in SM point: 0.013531 pb"<<a[0]<<endl;
    cout<<"teste funcao cg , c2g : 0,0 "<< l10->Eval(0,1)<<endl;
    cout<<"teste funcao cg , c2g : -1,1  "<<  l10->Eval(-1,1)<<endl;
    cout<<"teste funcao cg , c2g : 1,-1  "<<  l10->Eval(-1,1)<<endl;
    cout<<" "<<endl;
    ////////////////////////////////
    kt5d=1.0;
    kl5d=-2.4;
    c25d=0.0;
    // cg ===> x ==> c2
    // c2g ===> y ==> kt
    TF2 *lm24 = new TF2("lm24","([0]*y**4 + [1]*x**2 + [2]*y**2*[16]**2 + [3]*[17]**2*[16]**2 +  [4]*[15]**2 + [5]*x*y**2 + [6]*y*[16]*y**2 + [7]*y*[16]*x + [8]*[17]*[16]*x + [9]*x*[15] + [10]*[17]*[16]*y**2 + [11]*[15]*y**2 + [12]*[16]*[17]*y*[16] + [13]*[15]*y*[16] + [14]*[17]*[15]*[16])/[18]",-4,4,0.5,2.5);
    lm24->SetParameter(0,a[0]);
    lm24->SetParameter(1,a[1]);
    lm24->SetParameter(2,a[2]);    
    lm24->SetParameter(3,a[3]);
    lm24->SetParameter(4,a[4]);
    lm24->SetParameter(5,a[5]); 
    lm24->SetParameter(6,a[6]);
    lm24->SetParameter(7,a[7]);
    lm24->SetParameter(8,a[8]); 
    lm24->SetParameter(9,a[9]);
    lm24->SetParameter(10,a[10]);
    lm24->SetParameter(11,a[11]); 
    lm24->SetParameter(12,a[12]);    
    lm24->SetParameter(13,a[13]);
    lm24->SetParameter(14,a[14]);
    lm24->SetTitle("");
    lm24->SetParameter(15,c2g); //==> c2g
    lm24->SetParameter(16,kl5d);
    lm24->SetParameter(17,cg); //==> cg
    lm24->SetParameter(18,norm);//0.013531
    lm24->SetMinimum(0);
    //
    cout<<endl<<"Value of the formula in SM point: 0.013531 pb"<<a[0]<<endl;
    cout<<"teste funcao cg , c2g : 0,0 "<< lm24->Eval(0,1)<<endl;
    cout<<"teste funcao cg , c2g : -1,1  "<<  lm24->Eval(-1,1)<<endl;
    cout<<"teste funcao cg , c2g : 1,-1  "<<  lm24->Eval(-1,1)<<endl;
    cout<<" "<<endl;
    ////////////////////////////////
    kt5d=1.0;
    kl5d=-5.0;
    c25d=0.0;
    // cg ===> x ==> c2
    // c2g ===> y ==> kt
    TF2 *lm5 = new TF2("lm5","([0]*y**4 + [1]*x**2 + [2]*y**2*[16]**2 + [3]*[17]**2*[16]**2 +  [4]*[15]**2 + [5]*x*y**2 + [6]*y*[16]*y**2 + [7]*y*[16]*x + [8]*[17]*[16]*x + [9]*x*[15] + [10]*[17]*[16]*y**2 + [11]*[15]*y**2 + [12]*[16]*[17]*y*[16] + [13]*[15]*y*[16] + [14]*[17]*[15]*[16])/[18]",-4,4,0.5,2.5);
    lm5->SetParameter(0,a[0]);
    lm5->SetParameter(1,a[1]);
    lm5->SetParameter(2,a[2]);    
    lm5->SetParameter(3,a[3]);
    lm5->SetParameter(4,a[4]);
    lm5->SetParameter(5,a[5]); 
    lm5->SetParameter(6,a[6]);
    lm5->SetParameter(7,a[7]);
    lm5->SetParameter(8,a[8]); 
    lm5->SetParameter(9,a[9]);
    lm5->SetParameter(10,a[10]);
    lm5->SetParameter(11,a[11]); 
    lm5->SetParameter(12,a[12]);    
    lm5->SetParameter(13,a[13]);
    lm5->SetParameter(14,a[14]);
    lm5->SetTitle("");
    lm5->SetParameter(15,c2g); //==> c2g
    lm5->SetParameter(16,kl5d);
    lm5->SetParameter(17,cg); //==> cg
    lm5->SetParameter(18,norm);//0.013531
    lm5->SetMinimum(0);
    //
    cout<<endl<<"Value of the formula in SM point: 0.013531 pb"<<a[0]<<endl;
    cout<<"teste funcao cg , c2g : 0,0 "<< lm5->Eval(0,1)<<endl;
    cout<<"teste funcao cg , c2g : -1,1  "<<  lm5->Eval(-1,1)<<endl;
    cout<<"teste funcao cg , c2g : 1,-1  "<<  lm5->Eval(-1,1)<<endl;
    cout<<" "<<endl;
    ////////////////////////////////
    kt5d=1.0;
    kl5d=-10.0;
    c25d=0.0;
    // cg ===> x ==> c2
    // c2g ===> y ==> kt
    TF2 *lm10 = new TF2("lm10","([0]*y**4 + [1]*x**2 + [2]*y**2*[16]**2 + [3]*[17]**2*[16]**2 +  [4]*[15]**2 + [5]*x*y**2 + [6]*y*[16]*y**2 + [7]*y*[16]*x + [8]*[17]*[16]*x + [9]*x*[15] + [10]*[17]*[16]*y**2 + [11]*[15]*y**2 + [12]*[16]*[17]*y*[16] + [13]*[15]*y*[16] + [14]*[17]*[15]*[16])/[18]",-4,4,0.5,2.5);
    lm10->SetParameter(0,a[0]);
    lm10->SetParameter(1,a[1]);
    lm10->SetParameter(2,a[2]);    
    lm10->SetParameter(3,a[3]);
    lm10->SetParameter(4,a[4]);
    lm10->SetParameter(5,a[5]); 
    lm10->SetParameter(6,a[6]);
    lm10->SetParameter(7,a[7]);
    lm10->SetParameter(8,a[8]); 
    lm10->SetParameter(9,a[9]);
    lm10->SetParameter(10,a[10]);
    lm10->SetParameter(11,a[11]); 
    lm10->SetParameter(12,a[12]);    
    lm10->SetParameter(13,a[13]);
    lm10->SetParameter(14,a[14]);
    lm10->SetTitle("");
    lm10->SetParameter(15,c2g); //==> c2g
    lm10->SetParameter(16,kl5d);
    lm10->SetParameter(17,cg); //==> cg
    lm10->SetParameter(18,norm);//0.013531
    lm10->SetMinimum(0);
    //
    cout<<endl<<"Value of the formula in SM point: 0.013531 pb"<<a[0]<<endl;
    cout<<"teste funcao cg , c2g : 0,0 "<< lm10->Eval(0,1)<<endl;
    cout<<"teste funcao cg , c2g : -1,1  "<<  lm10->Eval(-1,1)<<endl;
    cout<<"teste funcao cg , c2g : 1,-1  "<<  lm10->Eval(-1,1)<<endl;
    cout<<" "<<endl;
    ///////////////////////////////////////////////////////////////
    // Draw this function in pad1 with Gouraud shading option
    TCanvas *c1 = new TCanvas("c1","Surfaces Drawing Options",1500,2500);
    const int Number = 3;
    Double_t Red[Number]    = { 1.00, 0.00, 0.00};
    Double_t Green[Number]  = { 0.00, 1.00, 0.00};
    Double_t Blue[Number]   = { 1.00, 0.00, 1.00};
    Double_t Length[Number] = { 0.00, 0.50, 1.00 };
    Int_t nb=30;
    TColor::CreateGradientColorTable(Number,Length,Red,Green,Blue,nb);
    ////////////////////////////
    TLatex* text = new TLatex();
    text->SetTextSize(0.09);
    c1->SetLogz(0);
    //////////////////////////////////////
    c1->Divide(3,4);   
    c1->cd(1);
    //c1_1->SetLogz();
    //c1->SetTicks(0,0);
    //c1->SetRightMargin(0.15);
    //c1->SetLeftMargin(0.15);
    //c1->SetBottomMargin(0.02);
    fg2->Draw("colz1");
    text->DrawLatex(-0.85,-0.8,"#kappa_{#lambda} = 1, #kappa_{t} = 1,  c_{2} = 0");
    //-----------------
    c1->cd(2);
    //c1_1->SetLogz();
    //c1_2->SetTicks(0,0);
    //c1_2->SetRightMargin(0.15);
    //c1_2->SetLeftMargin(0.15);
    //c1_2->SetBottomMargin(0.02);
    fg10->Draw("colz1");
    text->DrawLatex(-0.85,-0.8,"#kappa_{#lambda} = 10, #kappa_{t} = 1,  c_{2} = 0");
    //-----------------
    c1->cd(3);
    //c1_1->SetLogz();
    //c1_2->SetTicks(0,0);
    //c1_2->SetRightMargin(0.15);
    //c1_2->SetLeftMargin(0.15);
    //c1_2->SetBottomMargin(0.02);
    fgm10->Draw("colz1");
    text->DrawLatex(-0.85,-0.8,"#kappa_{#lambda} = -10, #kappa_{t} = 1,  c_{2} = 0");
    //text->SetTextSize(0.08);
    //text->SetTextColor(0);
    //text->DrawLatex(-0.85.,-0.8,"#kappa_{#lambda} = 2.4, #kappa_{t} = 1,  c_{2} = 0");
    c1->cd(4);
    //c1_1->SetLogz();
    //c1_2->SetTicks(0,0);
    //c1_2->SetRightMargin(0.15);
    //c1_2->SetLeftMargin(0.15);
    //c1_2->SetBottomMargin(0.02);
    SM0->Draw("colz1");
    text->DrawLatex(-3.,0.7,"c_{2} = c_{g}  = c_{2} = 0");  
    //text->SetTextSize(0.08);
    //text->SetTextColor(0);
    //text->DrawLatex(-0.85.,-0.8,"#kappa_{#lambda} = 2.4, #kappa_{t} = 1,  c_{2} = 0");
    c1->cd(5);
    //c1_5->SetTicks(0,0);
    //c1_2->SetRightMargin(0.15);
    //c1_2->SetLeftMargin(0.15);
    //c1_2->SetBottomMargin(0.02);
    l1->Draw("colz1");
    text->DrawLatex(-3.,0.7,"#kappa_{#lambda} = 1, c_{g}  = c_{2} = 0");  
    c1->cd(6);
    //c1_5->SetTicks(0,0);
    //c1_2->SetRightMargin(0.15);
    //c1_2->SetLeftMargin(0.15);
    //c1_2->SetBottomMargin(0.02);
    l0->Draw("colz1");
    text->DrawLatex(-3.,0.7,"#kappa_{#lambda} = c_{g}  = c_{2} = 0");  
    //text->SetTextSize(0.08);
    //text->SetTextColor(0);
    //text->DrawLatex(-0.85.,-0.8,"#kappa_{#lambda} = 2.4, #kappa_{t} = 1,  c_{2} = 0");   
    c1->cd(7);
    //c1_5->SetTicks(0,0);
    //c1_2->SetRightMargin(0.15);
    //c1_2->SetLeftMargin(0.15);
    //c1_2->SetBottomMargin(0.02);
    l24->Draw("colz");
    text->DrawLatex(-3.,0.7,"#kappa_{#lambda} = 2.4, c_{g}  = c_{2} = 0");  
    //text->SetTextSize(0.08);
    //text->SetTextColor(0);
    //text->DrawLatex(-0.85.,-0.8,"#kappa_{#lambda} = 2.4, #kappa_{t} = 1,  c_{2} = 0");  
    c1->cd(8);
    //c1_5->SetTicks(0,0);
    //c1_2->SetRightMargin(0.15);
    //c1_2->SetLeftMargin(0.15);
    //c1_2->SetBottomMargin(0.02);
    l5->Draw("colz1");
    text->DrawLatex(-3.,0.7,"#kappa_{#lambda} = 5, c_{g}  = c_{2} = 0");  
    //text->SetTextSize(0.08);
    //text->SetTextColor(0);
    //text->DrawLatex(-0.85.,-0.8,"#kappa_{#lambda} = 2.4, #kappa_{t} = 1,  c_{2} = 0");  
    c1->cd(9);
    //c1_5->SetTicks(0,0);
    //c1_2->SetRightMargin(0.15);
    //c1_2->SetLeftMargin(0.15);
    //c1_2->SetBottomMargin(0.02);
    l10->Draw("colz1");
    text->DrawLatex(-3.,0.7,"#kappa_{#lambda} = 10, c_{g}  = c_{2} = 0");  
    //text->DrawLatex(-3,1,"SM plane in log scale");
    //text->SetTextSize(0.08);
    //text->SetTextColor(0);
    //text->DrawLatex(-0.85.,-0.8,"#kappa_{#lambda} = 2.4, #kappa_{t} = 1,  c_{2} = 0");  
    c1->cd(10);
    //c1_5->SetTicks(0,0);
    //c1_2->SetRightMargin(0.15);
    //c1_2->SetLeftMargin(0.15);
    //c1_2->SetBottomMargin(0.02);
    lm24->Draw("colz1");
    text->DrawLatex(-3.,0.7,"#kappa_{#lambda} = -2.4, c_{g}  = c_{2} = 0");  
    c1->cd(11);
    //c1_5->SetTicks(0,0);
    //c1_2->SetRightMargin(0.15);
    //c1_2->SetLeftMargin(0.15);
    //c1_2->SetBottomMargin(0.02);
    lm5->Draw("colz1");
    text->DrawLatex(-3.,0.7,"#kappa_{#lambda} = -5, c_{g}  = c_{2} = 0");  
    c1->cd(12);
    //c1_5->SetTicks(0,0);
    //c1_2->SetRightMargin(0.15);
    //c1_2->SetLeftMargin(0.15);
    //c1_2->SetBottomMargin(0.02);
    lm10->Draw("colz1");
    //text->DrawLatex(-3,1,"SM plane in log scale");
    //text->SetTextSize(0.08);
    //text->SetTextColor(0);
    text->DrawLatex(-3.,0.7,"#kappa_{#lambda} = -10, c_{g}  = c_{2} = 0");  
    c1->SaveAs("C2Fit.pdf");
    

}


