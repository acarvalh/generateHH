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
    double L[1483];
    double y[1483];
    double c[1483];
    double cg[1483];
    double c2g[1483];
    ifstream parpoints("list_ascii_13TeV_1483.txt");
    for (int i=0; i<1483; i++) {
        parpoints >> L[i] >> y[i] >> c[i] >> cg[i] >> c2g[i];
        cout << i<< " " << L[i] << " " << y[i] << " " << c[i] << " " << cg[i] << " " << c2g[i] << endl;
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

  ifstream cluster_13("LogP/clustering_nev20k_Nclu13_50_5.asc");      
  ifstream cluster_20("LogP/clustering_nev20k_Nclu20_50_5.asc");   

  TH2D * clu_0[20];
    TH2D * clucg_0[20];
    TH2D * hclu_0[20];
    TH2D * hclucg_0[20];

  char name[100];
  for (int i=0; i<20; i++) {
    sprintf (name, "clu_0%d", i);
    clu_0[i] = new TH2D (name,"", 500, -20., 20., 500, 0., 3. );//c_{2} = 0
    sprintf (name, "clucg_0%d", i);
    clucg_0[i] = new TH2D (name,"", 500, -1.1, 1.1, 500, -1., 1. );//c_{2} = 0
      //
      sprintf (name, "hclu_0%d", i);
      hclu_0[i] = new TH2D (name,"", 500, -20., 20., 500, 0., 3. );//c_{2} = 0
      sprintf (name, "hclucg_0%d", i);
      hclucg_0[i] = new TH2D (name,"", 500, -1.1, 1.1, 500, -1., 1. );//c_{2} = 0
  }
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
  int iclu=-1;
  for (int i=0; i<1483; i++) {
    if (Nclu==20) {
      cluster_20 >> isamp;
    } else if (Nclu==15) {
      cluster_15 >> isamp;
    } else if (Nclu==13) {
        cluster_13 >> isamp;
    } else if (Nclu==10) {
      cluster_10 >> isamp;
    }
    for (int j=0; j<Nclu; j++) {if (isamp==head[j]) {	cout << "head = " << isamp << endl;	iclu++;}}
    // new cluster
    if (cg[isamp]==0 && c2g[isamp]==0 && c[isamp]==0.0){
      clu_0[iclu]->Fill(L[isamp],y[isamp]);
      for (int j=0; j<Nclu; j++) { if (isamp==head[j]) hclu_0[iclu]->Fill(L[isamp],y[isamp]);};
      //cout << isamp<< " " << L[isamp] << " " << y[isamp] << " " << c[isamp] << " " << cg[isamp] << " " << c2g[isamp] << endl;
    } else if (L[isamp]==1 && y[isamp]==1 && c[isamp]==0.0){
        clucg_0[iclu]->Fill(cg[isamp],c2g[isamp]);
        for (int j=0; j<Nclu; j++) { if (isamp==head[j]) hclucg_0[iclu]->Fill(cg[isamp],c2g[isamp]);};
        //cout << isamp<< " " << L[isamp] << " " << y[isamp] << " " << c[isamp] << " " << cg[isamp] << " " << c2g[isamp] << endl;
    } 
  }

  // one per canvas

    
  TCanvas * D5 = new TCanvas ("D5","",600,600);
  D5->cd();
        D5->SetLogz(0);
  for (int iclu=0; iclu<Nclu; iclu++) {
      clu_0[iclu]->GetYaxis()->SetTitle("#kappa_{t}");
      clu_0[iclu]->GetXaxis()->SetTitle("#kappa_{#lambda}");
    clu_0[iclu]->SetLineColor(mc[iclu]);
    clu_0[iclu]->SetMarkerColor(mc[iclu]);
    clu_0[iclu]->SetMarkerStyle(mt[iclu]);
    clu_0[iclu]->SetMarkerSize(2.0);
    if (iclu==0) {
      clu_0[iclu]->Draw("P");
        f3->Draw("cont3SAME");
            D5->SetLogz(0);
        clu_0[iclu]->Draw("PSAME");
    } else {
        clu_0[iclu]->Draw("PSAME");
    }
        leg->AddEntry(clu_0[iclu], lege20[iclu], "P");  
      hclu_0[iclu]->SetMarkerColor(mc[iclu]);
    hclu_0[iclu]->SetMarkerStyle(mt[iclu]);
    hclu_0[iclu]->SetMarkerSize(3.0);
    hclu_0[iclu]->Draw("PSAME");
      leg->Draw("same");
      TLatex* text = new TLatex();
      text->SetTextSize(0.04);

      text->DrawLatex(-17,2.8,"c_{2} = 0");
      text->Draw("same");
  }
  char nameplot[40];
    sprintf(nameplot,"clusters13_c0_%d.png",Nclu);
    D5->Print(nameplot);
    sprintf(nameplot,"clusters13_c0_%d.pdf",Nclu);
    D5->Print(nameplot);
    /////////////////////////////////////////////////////
    TCanvas * D6 = new TCanvas ("D6","",600,600);
    D6->cd();
    for (int iclu=0; iclu<Nclu; iclu++) {
        clucg_0[iclu]->GetYaxis()->SetTitle("c_{2g}");
        clucg_0[iclu]->GetXaxis()->SetTitle("c_{g}");
        clucg_0[iclu]->SetLineColor(mc[iclu]);
        clucg_0[iclu]->SetMarkerColor(mc[iclu]);
        clucg_0[iclu]->SetMarkerStyle(mt[iclu]);
        clucg_0[iclu]->SetMarkerSize(2.0);
        if (iclu==0) {
            clucg_0[iclu]->Draw("P");
            //fg->Draw("cont3SAME");
            clucg_0[iclu]->Draw("PSAME");
        } else {
            clucg_0[iclu]->Draw("PSAME");
        }
        //leg->AddEntry(clu_0[iclu], lege20[iclu], "P");  
        hclucg_0[iclu]->SetMarkerColor(mc[iclu]);
        hclucg_0[iclu]->SetMarkerStyle(mt[iclu]);
        hclucg_0[iclu]->SetMarkerSize(3.0);
        hclucg_0[iclu]->Draw("PSAME");
        leg->Draw("same");
        TLatex* text = new TLatex();
        text->SetTextSize(0.04);
        text->DrawLatex(0.1,0.85,"#kappa_{#lambda} = 1, #kappa_{t} = 1, c_{2} = 0 ");
        text->Draw("same");
        text->SetTextSize(0.04);
        //text->DrawLatex(-0.95,-0.85,"#sigma_{hh}^{min} = 0.7 x SM ");
        text->Draw("same");
        text->SetTextSize(0.04);
        //text->DrawLatex(-0.95,-0.9,"#sigma_{hh}^{max} = 100 x SM ");
        //text->Draw("same");
        
    }
    char nameplot[40];
    sprintf(nameplot,"clusters_c0cg_%d.png",Nclu);
    D6->Print(nameplot);
    sprintf(nameplot,"clusters_c0cg_%d.pdf",Nclu);
    D6->Print(nameplot);
}
