/*
 execute
 root > .L FitBinc_SMplane.C+
 root > FitBinc_SMplane()
 */
#include "TH2.h"
#include "TF1.h"
#include "TF2.h"
#include "TF3.h"
#include "TH1.h"
#include "TH3.h"
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
#include "TFolder.h"
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

static int Npoints=296;
static int nmin;
static int nmax;
static double cross_sectiontotal[297];
static double cross_section[297];
static double cross_sectionerr[297];
static double par0[297];
static double par1[297];
static double par2[297];
static double par3[297];
static double par4[297];

static double par0r[297];
static double par1r[297];
static double par2r[297];
static double par3r[297];
static double par4r[297];

static double errNBSM[297];
static double errNSM[297];
double effSM;
double effSum;
double SMxs =  0.013531; // 1 0.017278;// 14 0.0041758;// 8tev  ; //  in pb as MG model says 1; //
////////////////////////////////////////////////////////////////////////////////////////////
/*
extern "C" void Likelihood(int& npar, double* grad, double& fval, double* xval, int flag) {
  //  cout << "In likelihood" << endl;
  // xval[0:14] are the parameters
  double flike=0.;
  double A1 = xval[0];
  double A3 = xval[1];
  double A7 = xval[2];
  for (int i=nmin; i<nmax; i++) {
    double kt = par1[i]; 
    double kl = par0[i]; 
    double xs = (
       A1*pow(kt,4)+ 
       (A3*pow(kt,2))*pow(kl,2)+
       (A7*kt*kl)*pow(kt,2));
    double error = 0.0001*cross_section[i]+errNBSM-errNSM; 
    flike += -0.5*pow((xs-cross_section[i])/error,2);
  }
  fval = -flike;
}
*/
////////////////////////////////////////////////////////////////////////////////////////////
extern "C" void Likelihood(int& npar, double* grad, double& fval, double* xval, int flag) {
  //  cout << "In likelihood" << endl;
  // xval[0:14] are the parameters
  double flike=0.;
 // 1 0.017278;// 14 0.0041758;// 8tev  ; //  in pb as MG model says 1; //
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
    double cg = par3[i]; 
    double c2g= par4[i];  
    double xs = (
       A1*pow(kt,4)+ 
       A2*pow(c2,2)+
       (A3*pow(kt,2)+A4*pow(cg,2))*pow(kl,2)+
       A5*pow(c2g,2)+
       (A6*c2+A7*kt*kl)*pow(kt,2)+
       (A8*kt*kl+A9*cg*kl)*c2+
       A10*c2*c2g+
       (A11*cg*kl+A12*c2g)*pow(kt,2)+
       (A13*kl*cg+A14*c2g)*kt*kl+A15*cg*c2g*kl);
    double error;
    if (i==0) error =0.0001*cross_section[i];
    else error = cross_section[i]*0.01+errNBSM[i]-errNSM[i]+0.001; //;
    flike += -0.5*pow((xs-cross_section[i])/error,2); // if (xs > 0) 
  }
  fval = -flike;
}
////////////////////////////////////////////////////////////////////////////////////////////
void FitBinc_SMplane (int nminx = 0, int nmaxx = 1507, int nmintest = 0, int nmaxtest = 1507) { 
  nmin=nminx;
  nmax=nmaxx;
  if (nmin<0) nmin=0;
  if (nmax>Npoints) nmax=Npoints;
  ////////////////////////////////////////////////////////////////////////////////////
  // Read in the cross section values and the parameters space points
  ifstream XSvals;
  XSvals.open("tableToFitA3andA7.txt");//"14TeV_CX_5k_opositecgw.ascii");// "8TeV_CX_5k_opositecgw.ascii");//
  for (int i=0; i<297; i++)  XSvals >> par0r[i] >> par1r[i] >> par2r[i] >> par3r[i] >> par4r[i]  >> cross_sectiontotal[i] ;
  cout << "********************** ************************" << endl;
  ////////////////////////////////////////////////////////////////////////////////////
  // read SM to normalize
  // read efficiencies in bins
  //TFile *fSM = new TFile("Distros_lambdaOnly_5p_50000ev_52sam_13TeV_JHEP_50K.root");
  //fSM->cd("lamdaOnly");
  //TH1D * h1SM = (TH1D*) fSM->Get("21_bin1");

  ofstream myfile;
  myfile << " npoints  mhh cost EffSM a1 a2 a3 a4 a5 a6 a7 a8 a9 a10 a11 a12 a13 a14 a15 Erra1 Erra2 Erra3 Erra4 Erra5 Erra6 Erra7 Erra8 Erra9 Erra10 Erra11 Erra12 Erra13 Erra14 Erra15" <<endl;
  //myfile << counter << " "<< h1SM->GetXaxis()->FindBin(mhh)<<" "<< h1SM->GetYaxis()->FindBin(cost)  <<" "<<a[0]<<" "<<a[1]<<" "<<a[2]<<" "<<a[3]<<" "<<a[4]<<" "<<a[5]<<" "<<a[6]<<" "<<a[7]<<" "<<a[8]<<" "<<a[9]<<" "<<a[10]<<" "<<a[11]<<" "<<a[12]<<" "<<a[13]<<" "<<a[14]<<endl;
  //myfile.open ("coefficientsByBin_A1A3A7.txt");
  myfile.open ("coefficientsByBin_extended_3M_costHHSim_19-4.txt");
  TFile *f = new TFile("../clustDistros/Distros_5p_SM3M_toRecursive_5D_13TeV.root"); // ("Distros_5p_SM100k_toRecursive_13TeV.root");
  TFile *fSM = new TFile("../clustDistros/Distros_5p_SM3M_sumBenchJHEP_13TeV.root");
  //TH1D * h1SM = (TH1D*) fSM->Get("H0bin2");
  //TH1D * h1Sum = (TH1D*) fSM->Get("H1bin2");
  //TH1D * h1SM = (TH1D*) fSM->Get("H0bin3"); // extended bins
  //TH1D * h1Sum = (TH1D*) fSM->Get("H1bin3");
  TH1D * h1SM = (TH1D*) fSM->Get("H0bin4"); // simmetric cost*HH
  TH1D * h1Sum = (TH1D*) fSM->Get("H1bin4");
  // fix SM
  h1SM->Draw("colz");
  double neventsBSM;
  cout<<"Start fit "<<endl;
  //for(int mhh =1 ; mhh< 13+1; mhh++){ // 1-91
  //  for(int cost =1 ; cost< 3+1; cost++){ // 0 -10
  char htitle2[90];
  for(int mhh =0 ; mhh< 59; mhh++){ // 1-91
    for(int cost =0 ; cost< 4; cost++){ // 0 -10
      ofstream myfileErr;
      sprintf (htitle2,"Logs/Log_binMhh%d_binCosthh%d.txt",mhh,cost);
      myfileErr.open (htitle2);
      int counter = 1; // the 0 will be SM
      effSum = (h1Sum->GetBinContent(mhh+1,cost+1)); ///(h1Sum->Integral()      /1200.0
      effSM = ((h1SM->GetBinContent(mhh+1,cost+1))) ;//30; ///(h1SM->Integral()) /10.0)/300.0
      for(int i = 0; i< Npoints; i++){
        ////////////////////////////////////////////////////////////////////////////////
        
        if( i<=105    ) {//and par0r[i] !=0 and (par2r[i] ==0 and par3r[i] ==0 and par4r[i] ==0 and i!=32) // i<104 and (par2r[i] ==0 and par3r[i] ==0 and par4r[i] ==0 and i!=32) ){ // 1507 //
        //const char * htitle = Form("H%dbin2",i+1); // skip the 0
        const char * htitle = Form("H%dbin4",i+1); // skip the 0
        TH1D * h1 = (TH1D*) f->Get(htitle);
        //cout<< h1->GetXaxis()->GetNbins()<<endl;
        if(mhh==0 && cost==0 && i==0) {neventsBSM=h1->Integral(); }// h1->Draw("colz"); 
        double effBSM = ((h1->GetBinContent(mhh+1,cost+1)));///(h1->Integral())  /5.0
        //if (effBSM >0) errNBSM = cross*(sqrt(h1->GetBinContent(mhh+1,cost+1))/(h1->GetBinContent(mhh+1,cost+1)) )/(h1->GetBinContent(mhh+1,cost+1));
        //errNSM = cross*(sqrt(h1SM->GetBinContent(mhh+1,cost+1))/(h1SM->GetBinContent(mhh+1,cost+1)) )/(h1SM->GetBinContent(mhh+1,cost+1));
        if( effSM > 0  ) { // ignore if zero , or too few
           double cross =cross_sectiontotal[i]*effBSM/((effSM)*SMxs)*(300/5);
           if (effBSM > 0) {
               errNBSM[counter] = (cross_sectiontotal[i]/SMxs)*(sqrt(effBSM)/5)*(300/effSM);
               errNSM[counter] = (cross_sectiontotal[i]/SMxs)*(sqrt(effSM)*300)/(effSM*effSM)*(effBSM/5)/2;
           } else {
               errNBSM[counter] = cross_sectiontotal[i]*(sqrt(3)/5)*(300/effSM)/2;
               errNSM[counter] = (cross_sectiontotal[i]/SMxs)*(sqrt(effSM)*300)/(effSM*effSM)*(3/5)/2;
           }
           cross_section[counter] = cross;
           par0[counter]= par0r[i];
           par1[counter]= par1r[i];
           par2[counter]= par2r[i];
           par3[counter]= par3r[i];
           par4[counter]= par4r[i];
           cout<<i<<" "<<cross_section[counter]<< " " <<cross<<" "<< cross_sectiontotal[i]<<" " <<" " <<neventsBSM<< " "
               << " " <<par0[counter]<<" "<< " " <<par1[counter]<<" "<< " "<<effBSM<<" " <<effSM<<" "<<(cross_section[counter]*0.01+errNBSM[counter]-errNSM[counter]+0.001)  <<" "<<errNBSM[counter]<<" " <<errNSM[counter] <<endl;
           myfileErr<<i<<" "<<par0[counter]<<" "<< " " <<par1[counter]<<" "<<par2[counter]<<" "<< " " <<par3[counter]<<" "<<par4[counter]<<" "
                    <<cross_section[counter]<< " " <<cross<<" "<< cross_sectiontotal[i]<<" " 
                     <<effBSM<<" " <<effSM<<" "<<(cross_section[counter]*0.01+errNBSM[counter]-errNSM[counter]+0.001)  <<" "<<errNBSM[counter]<<" " <<errNSM[counter] <<endl;
           counter++;
        } 
      } 
      
      //////////////////////////////////////////////////////////////////////
        if( i>104   ) {//  (par2r[i] ==0 and par3r[i] ==0 and par4r[i] ==0 and i!=32) ){ // 1507 //
        const char * htitle = Form("H%dbin4",i+1); // skip the 0
        TH1D * h1 = (TH1D*) f->Get(htitle);
        //cout<< h1->GetXaxis()->GetNbins()<<endl;
        double effBSM = ((h1->GetBinContent(mhh+1,cost+1)));///(h1->Integral())  /50.0
        if( effSM > 0 ) { // ignore if zero , or too few
           double cross =cross_sectiontotal[i]*effBSM/((effSM)*SMxs)*(300/5);
           if (effBSM > 0) {
               errNBSM[counter] = (cross_sectiontotal[i]/SMxs)*(sqrt(effBSM)/5)*(300/effSM);
               errNSM[counter] = (cross_sectiontotal[i]/SMxs)*(sqrt(effSM)*300)/(effSM*effSM)*(effBSM/5)/2;
           } else {
               errNBSM[counter] = cross_sectiontotal[i]*(sqrt(3)/5)*(300/effSM)/2;
               errNSM[counter] = (cross_sectiontotal[i]/SMxs)*(sqrt(effSM)*300)/(effSM*effSM)*(3/5)/2;
           }
           cross_section[counter] = cross;
           par0[counter]= par0r[i];
           par1[counter]= par1r[i];
           par2[counter]= par2r[i];
           par3[counter]= par3r[i];
           par4[counter]= par4r[i];
           cout<<i<<" "<<cross_section[counter]<< " " <<cross<<" " << cross_sectiontotal[i]<<" " <<" " <<neventsBSM<< " "
               << " " <<par0[counter]<<" "<< " " <<par1[counter]<<" "<< " "<<effBSM<<" " <<effSM<<" "<<(cross_section[counter]*0.01+errNBSM[counter]-errNSM[counter]+0.001)  <<" "<<errNBSM[counter]<<" " <<errNSM[counter] <<endl;
           myfileErr<<i<<" "<<par0[counter]<<" "<< " " <<par1[counter]<<" "<<par2[counter]<<" "<< " " <<par3[counter]<<" "<<par4[counter]<<" "
                    <<cross_section[counter]<< " " <<cross<<" "<< cross_sectiontotal[i]<<" " 
                     <<effBSM<<" " <<effSM<<" "<<(cross_section[counter]*0.01+errNBSM[counter]-errNSM[counter]+0.001)  <<" "<<errNBSM[counter]<<" " <<errNSM[counter] <<endl;
           counter++;
        } 
      }
      //////////////////////////////////////////////////////////////////////
      } // close to i
       myfileErr.close();
       cross_section[0] = 1.0;
       par0[0]= 1.0;
       par1[0]= 1.0;
       par2[0]= 0.0;
       par3[0]= 0.0;
       par4[0]= 0.0;
       errNBSM[0] = 0.0;
       errNSM[0] = 0.0;

      if(counter>0) {
        ///////////////////////////////////////////////////////////////////////////////////
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
       arglis[0]=1;
       // Sets the strategy to be used in calculating first and second derivatives 
       // and in certain minimization methods. 1 is default
       rmin.mnexcm("SET STR", arglis, 1, iflag);
       // Set fit parameters
       double Start[15];
       double Step[15]; 
       double Min[15]; 
       double Max[15];  
       for (int i=0; i<15; i++) {
         Start[i]=1.;
         Step[i]=1;
         Min[i]=-100000;
         Max[i]=+100000;
       }
       //TString parnamEj[3]={"A1","A3","A7"};
       //for (int i=0; i<3; i++)  rmin.mnparm(i, parnamEj[i],  Start[i], Step[i], Min[i], Max[i], iflag);

       TString parnamEj[15]={"A1","A2","A3","A4","A5","A6","A7","A8","A9","A10","A11","A12","A13","A14","A15"};
       for (int i=0; i<15; i++)  rmin.mnparm(i, parnamEj[i],  Start[i], Step[i], Min[i], Max[i], iflag);
       // Instructs Minuit to call subroutine FCN with the value of IFLAG
       //rmin.mnexcm("call fcn", arglis, 1, iflag); // command executed normally
       // Causes minimization of the function by the method of Migrad
       rmin.mnexcm("mini", arglis, 0, iflag);
       // Read results
       //double a[3], err[3], pmin, pmax;
       //int ivar;
       //for (int i=0; i<3; i++) rmin.mnpout (i, parnamEj[i], a[i], err[i], pmin, pmax, ivar);
       double a[15], err[15], pmin, pmax;
       int ivar;
       for (int i=0; i<15; i++) rmin.mnpout (i, parnamEj[i], a[i], err[i], pmin, pmax, ivar);
       // End of program
       // --------------
       gROOT->Time();
       /*
       cout<<endl<<" To mathematica: "<<endl;
       cout<<"{"<<a[0]<<","<<a[1]<<","<<a[2]<<endl; // ","<<a[3]<<","<<a[4]<<","<<a[5]<<","
                //<<a[6]<<","<<a[7]<<","<<a[8]<<","<<a[9]<<","<<a[10]<<","<<a[11]<<","
                //<<a[12]<<","<<a[13]<<","<<a[14]<<"}"<<endl;
    //cout<<endl<<" To mathematica (errors): "<<endl;
    //cout<<"{"<<err[0]<<","<<err[1]<<","<<err[2]<<","<<err[3]<<","<<err[4]<<","<<err[5]<<","<<err[6]<<","
    //         <<err[7]<<","<<err[8]<<","<<err[9]<<","<<err[10]<<","<<err[11]<<","<<err[12]<<","<<err[13]<<","<<err[14]<<"}"<<endl;
   
    cout<<"npoints "<<counter<<endl;
    myfile << counter<< "\t" << h1SM->GetXaxis()->GetBinCenter(mhh)<<"\t"<< h1SM->GetYaxis()->GetBinCenter(cost)  <<"\t"<<effSM<<  "\t"<<effSum <<"\t"
           <<a[0]<<"\t"<<a[1]<<"\t"<<a[2]<<"\t"<<err[0]<<"\t"<<err[1]<<"\t"<<err[2]
           //<<err[4]<<" "<<err[5]<<" "<<err[6]<<" "<<err[7]<<" "<<err[8]<<" "
           //<<err[9]<<" "<<err[10]<<" "<<err[11]<<" "<<err[12]<<" "<<err[13]<<" "<<err[14]
           <<endl;
       */
       cout<<endl<<" To mathematica: "<<endl;
       cout<<"{"<<a[0]<<","<<a[1]<<","<<a[2]<<","<<a[3]<<","<<a[4]<<","<<a[5]<<","
                <<a[6]<<","<<a[7]<<","<<a[8]<<","<<a[9]<<","<<a[10]<<","<<a[11]<<","
                <<a[12]<<","<<a[13]<<","<<a[14]<<"}"<<endl;
    cout<<endl<<" To mathematica (errors): "<<endl;
    cout<<"{"<<err[0]<<","<<err[1]<<","<<err[2]<<","<<err[3]<<","<<err[4]<<","<<err[5]<<","<<err[6]<<","
             <<err[7]<<","<<err[8]<<","<<err[9]<<","<<err[10]<<","<<err[11]<<","<<err[12]<<","<<err[13]<<","<<err[14]<<"}"<<endl;
   
    cout<<"npoints "<<counter<<endl;
    myfile << counter<< "\t" << h1SM->GetXaxis()->GetBinCenter(mhh+1)<<"\t"<< h1SM->GetYaxis()->GetBinCenter(cost+1)  <<"\t"<<effSM<<  "\t"<<effSum <<"\t"
           <<a[0]<<" "<<a[1]<<" "<<a[2]<<" "<<a[3]<<" "<<a[4]<<" "<<a[5]<<" "
           <<a[6]<<" "<<a[7]<<" "<<a[8]<<" "<<a[9]<<" "<<a[10]<<" "<<a[11]<<" "<<a[12]<<" "
           <<a[13]<<" "<<a[14]<<" " <<err[0]<<" "<<err[1]<<" "<<err[2]<<" "<<err[3]<<" "
           <<err[4]<<" "<<err[5]<<" "<<err[6]<<" "<<err[7]<<" "<<err[8]<<" "
           <<err[9]<<" "<<err[10]<<" "<<err[11]<<" "<<err[12]<<" "<<err[13]<<" "<<err[14]<<endl;

  } // close if counter
  else     myfile << counter <<" "<<effSM<<  " "<< h1SM->GetXaxis()->GetBinCenter(mhh+1)<<" "<< h1SM->GetYaxis()->GetBinCenter(cost+1)  <<" 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 "<<endl;


    } // close cost bin
  } // close mhh bin
  myfile.close();
  cout <<"nevents SM "<<h1SM->Integral()<<" " <<h1Sum->Integral()<<" BSM "<<neventsBSM<<endl;
  cout<< h1SM->GetXaxis()->GetNbins()<<" "<<h1SM->GetYaxis()->GetNbins()<<endl;
}  








