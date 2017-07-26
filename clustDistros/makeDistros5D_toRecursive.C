// M. Dall'Osso
// To create root file with kin distros from ascii files.
// .L makeDistros5D_toRecursive.C++
// makeDistros5D_toRecursive()
/////////////

#include <iostream>
#include <fstream>
#include <sstream>
#include <cmath>
#include <algorithm>
#include <vector>
#include <string>
#include <stdlib.h>
#include <sys/time.h>
#include "TRandom.h"
#include "TH1D.h"
#include "TH2D.h"
#include "TFile.h"
#include "TLorentzVector.h"
#include "TTree.h"

using namespace std;

struct event {
  double px1, py1, pz1, E1, m1;
  double px2, py2, pz2, E2, m2;
  double pt, pt2, pzh, pzl, M; 
};
		
struct benchmark {
  vector <double> pp;		//distances from other elements
  int N;			//number of "neighbours" (see later)
  vector <int> Nloc;		//location of "neigbours"
  int tracker;			//label of the benchmark 
};

// input files - parameters - TO BE CHANGED
//******************************************
int np = 5;	 //number of parameters
const int ns = 297;   //number of samples
string option = "_13TeV"; //debug
const int nev = 50000;	  //number of ev per sample

string inputPath = "/eos/user/a/acarvalh/asciiHH_tofit/GF_HH_toRecursive/GF_HH_";  //folder with ascii lhe files (outside 'git' area)
//string inputPath = "GluonF_HH_toRecursive_lhe/GF_HH_";  //folder with ascii lhe files (outside 'git' area)
//string inputPath = "/lustre/cmswork/carvalho/CMSSW_8_0_18/src/genproductions/bin/MadGraph5_aMCatNLO/GluonF_HH_toRecursive_lhe/GF_HH_";  //folder with ascii lhe files (outside 'git' area) 
//string fileslist_st = "utils/list_toRecursive.txt"; //ascii names list !!!!!!!!!!!!!!!!

//to be changed accordingly to lhe structure (3p, 5p,..)
//string folder1_st = "0-851";
//string folder2_st = "852-1593";
//int split = 851;

TLorentzVector P1, P2, P12, P1boost, P2boost;
bool update = false;
		
///////////////////////////////////
void makeDistros5D_toRecursive(){
  // we hill have only two sets of histograms
  // 0 is a high stats SM; the other the sum of JHEP benchmaks

  //out file
  TFile *out(0);
  std::stringstream sstr;
  sstr << "Distros_" << np << "p_SM3M_toRecursive_5D" << option;
  string outfile = sstr.str() + ".root";
  if(!update)  { out = TFile::Open(outfile.c_str(), "RECREATE"); }  //RECREATE
  else           out = TFile::Open(outfile.c_str(), "UPDATE");   

  //TDirectory *batch1 = out->mkdir(folder1_st.c_str());
  //TDirectory *batch2 = out->mkdir(folder2_st.c_str());

  typedef event bench[nev];
  bench *ev = new bench[ns]; 
      char htitle2[296];
  char htitle3[296];
  for(int f=0; f<ns; ++f)  { 


      //string samplename = std::to_string(nhist); // go with ordering only.
      TH1D pt, pt2, pzl, pzh, mhh;
      TH1D hth, hcth, hths, hcths;
      TH2D bin1;
   
      string samplename = to_string(f); // go with ordering only.
      sprintf (htitle2,"%s_pt",samplename.c_str()); //debug
      pt.SetName(htitle2);
      pt.SetTitle(htitle2);
      pt.SetBins(100,0.,600.);

      sprintf (htitle2,"%s_pt2",samplename.c_str()); //debug
      pt2.SetName(htitle2);
      pt2.SetTitle(htitle2);
      pt2.SetBins(100,0.,600.);

      sprintf (htitle2,"%s_pzl",samplename.c_str());
      pzl.SetName(htitle2);
      pzl.SetTitle(htitle2);
      pzl.SetBins(500,-1000.,1000.); //400

      sprintf (htitle2,"%s_pzh",samplename.c_str());
      pzh.SetName(htitle2);
      pzh.SetTitle(htitle2);
      pzh.SetBins(500,0.,2500.);

      sprintf (htitle2,"%s_mhh",samplename.c_str());
      mhh.SetName(htitle2);
      mhh.SetTitle(htitle2);
      mhh.SetBins(200,0.,1000.);

      sprintf (htitle2,"%s_hth",samplename.c_str());
      hth.SetName(htitle2);
      hth.SetTitle(htitle2);
      hth.SetBins(200,0.,3.2); //debug

      sprintf (htitle2,"%s_hcth",samplename.c_str()); //debug
      hcth.SetName(htitle2);
      hcth.SetTitle(htitle2);
      hcth.SetBins(200,-1.,1.); //debug
 
      sprintf (htitle2,"%s_hths",samplename.c_str());
      hths.SetName(htitle2);
      hths.SetTitle(htitle2);
      hths.SetBins(200,0.,3.2); //debug

      sprintf (htitle2,"%s_hcths",samplename.c_str()); //debug
      hcths.SetName(htitle2);
      hcths.SetTitle(htitle2);
      hcths.SetBins(100,0.,1.); //debug

      //sprintf (htitle2,"H%sbin1",samplename.c_str()); //debug
      //TH2D *hdumb = new TH2D(htitle2, htitle2, 90,0.,1800.,10,-1,1.);
      //bin1.push_back(hdumb);
      //bin1[f].SetName(htitle2);
      //bin1[f].SetTitle(htitle2);
      //bin1[f].SetBins(90,0.,1800.,10,-1,1.); //debug
      //bin1[f].GetXaxis()->SetRange(0.,1800.);
      //bin1[f].GetYaxis()->SetRange(-1,1.);
      //bin1[f].Rebin2D(90,10,htitle2);

      sprintf (htitle2,"%s_bin1",samplename.c_str()); //debug
      bin1.SetName(htitle2);
      bin1.SetTitle(htitle2);
      bin1.SetBins(90,0.,1800.,10,-1,1.); //debug

      //Float_t binsx[14]  = { 250.,270.,300.,330.,360.,390., 420.,450.,500.,550.,600.,700.,800.,1000.}; 
      Float_t binsxM[16]  = { 247.,270.,300.,330.,360.,390., 420.,450.,500.,550.,600.,700.,800.,1000.,1500.,50000 }; 
      Float_t binsy[4]  = { -1., -0.55,0.55,1. };
      sprintf (htitle2,"H%sbin3",samplename.c_str()); //debug
      TH2D *bin3 = new TH2D(htitle2, htitle2,15,binsxM,3,binsy);

      Float_t binsx[14]  = { 250.,270.,300.,330.,360.,390., 420.,450.,500.,550.,600.,700.,800.,1000.}; 
      //Float_t binsx[17]  = { 250.,260.,270.,290.,300.,330.,360.,390., 420.,450.,500.,550.,600.,700.,800.,1000.,1500 }; 
      sprintf (htitle2,"H%sbin2",samplename.c_str()); //debug
      TH2D *bin2 = new TH2D(htitle2, htitle2,13,binsx,3,binsy);

      /*
      Float_t binsxM2[85]  = { 250,255,260,265,270,275,280,285,290,295,
                               300,305,310,315,320,325,330,335,340,345,
                               350,355,360,365,370,375,380,385,390,395,
                               400,405,410,415,420,425,430,435,440,445, 
                               450,455,460,465,470,475,480,485,490,495,
                               500,510,520,530,540,550,560,570,580,590,
                               600,610,620,630,640,650,660,670,680,690,
                               700,750,800,850,900,950,1000,1100,1200,1300,
                               1400,1500,1750,2000,50000}; 
      Float_t binsySim[4]  = { 0.0,0.4,0.6, 1.0 };
      sprintf (htitle3,"H%sbin4",samplename.c_str()); //debug
      TH2D *bin4 = new TH2D(htitle3, htitle3,84,binsxM2,3,binsySim);
      */
      Float_t binsxM2[60]  = { 250,260,270,280,290,300,310,320,330,340,
                               350,360,370,380,390,400,410,420,430,440, 
                               450,460,470,480,490,500,510,520,530,540,
                               550,560,570,580,590,600,610,620,630,640,
                               650,660,670,680,690,700,750,800,850,900,
                               950,1000,1100,1200,1300,1400,1500.,1750,2000,50000}; 
      Float_t binsySim[5]  = {  0.0,0.4,0.6,0.8, 1.0};
      sprintf (htitle3,"H%sbin4",samplename.c_str()); //debug
      TH2D *bin4 = new TH2D(htitle3, htitle3,59,binsxM2,4,binsySim);


      //}// close declare histos
  cout<<"histos declared"<<endl;
  // Reading ASCII, one file a time
  // ------------------------------
  //ifstream filelist5(fileslist_st);
  ifstream infile;
  int nf = 0;
  //for(int f=0; f<ns; ++f) { // ns
    
    cout << "Reading file # " << f << endl;
    ///////////////////////////
    // to read from the list file
    /////////////////////////////
    //ostringstream fnumber;
    //string filename;
    //string fname;
    //filelist5 >> fname;
    //fname = "ascii_" + samplename + ".txt";
    //filename = inputPath+fname.c_str();
    /////////////////////////////////
    // to construct the filename
    ////////////////////////////////
    string filename;
    if(f==0) {filename = "/afs/cern.ch/work/a/acarvalh/eoserase/GF_3M.decayed"; }
    else {
    std::stringstream sstr1;
    sstr1 << f;
    filename = inputPath+sstr1.str() +".lhe.decayed";
    }
    cout << filename << endl;
    infile.open(filename.c_str());
    if(!infile)	{      //check if file exists
	printf( "WARNING: no input file %s \n", filename.c_str());
    }
    else nf++;
   // 1 = higgs1; 2 = higgs2;
    int pID;
    int Nev = 0;
    if(f==0) Nev = 3000000; else Nev = nev; 
    for (int k=0; k<Nev; ++k) {  // loop on number of events
        infile >> pID >> ev[f][k].px1 >> ev[f][k].py1 >> ev[f][k].pz1 >> ev[f][k].E1 ;
        infile >> pID >> ev[f][k].px2 >> ev[f][k].py2 >> ev[f][k].pz2 >> ev[f][k].E2 ;
      }
      infile.close();    
      // in which histogram to save
      int nhist=f;
      //if(f==0) nhist = 0; else nhist = 1;
      // Some preprocessing:
      // 1 - order by pt -> pthi, ptlo
      // 2 - compute dphi
      // 3 - flip sign of pzhi, pzlo if pzhi is negative
      // -----------------------------------------------
      double costheta = -99, theta = -99, thetast = -99, costhetast = -99;
      for (int k=0; k<Nev; k++) {

        ev[f][k].pt  = sqrt(pow(ev[f][k].px1,2)+pow(ev[f][k].py1,2));
        ev[f][k].pt2 = sqrt(pow(ev[f][k].px2,2)+pow(ev[f][k].py2,2));
        ev[f][k].pzh = ev[f][k].pz1;
        ev[f][k].pzl = ev[f][k].pz2;

        P1.SetPxPyPzE(ev[f][k].px1,ev[f][k].py1,ev[f][k].pz1,ev[f][k].E1);
        P2.SetPxPyPzE(ev[f][k].px2,ev[f][k].py2,ev[f][k].pz2,ev[f][k].E2);
        P12 = P1 + P2;
       // if(k==nev-1) cout << samplename << "  " << ev[f][k].px2 << "  " << ev[f][k].py2 << "  " << ev[f][k].pz2 << "  " << ev[f][k].E2 << endl;

        if (fabs(ev[f][k].pzh)<fabs(ev[f][k].pzl)) {
	  ev[f][k].pzh=ev[f][k].pz2;
  	  ev[f][k].pzl=ev[f][k].pz1;
        }
        if (ev[f][k].pzh<0) {
	  ev[f][k].pzh=-ev[f][k].pzh;
  	  ev[f][k].pzl=-ev[f][k].pzl;
        }
       //Fill histos
        pt.Fill(ev[f][k].pt);
        pt2.Fill(ev[f][k].pt2);
        pzl.Fill(ev[f][k].pzl);
        pzh.Fill(ev[f][k].pzh);
        mhh.Fill(P12.M());

       //angle computation   
        theta = P1.Theta();  //TMath::ACos(P1.Pz()/P1.P());
        costheta = P1.CosTheta();
        hth.Fill(theta); //debug
        hcth.Fill(costheta); //debug

       //star angle computation           
        P1boost = P1;
        P12 = P1 + P2; // this is the total vectorial momenta of the system
        P1boost.Boost(-P12.BoostVector()); 
        thetast = P1boost.Theta();  
        costhetast = P1boost.CosTheta();
        hths.Fill(thetast); 		
        hcths.Fill(costhetast); 

        costhetast = P1boost.CosTheta(); // this is the costTheta
        bin1.Fill(P12.M(),costhetast); 
        bin2->Fill(P12.M(),costhetast); 
        bin3->Fill(P12.M(),costhetast); 
        bin4->Fill(P12.M(),abs(costhetast)); 
        //bin2[nhist].Fill(P12.M(),costhetast); 
      }
      //if(f<=split) batch1->cd();
      //else batch2->cd();
    // if(f ==0 || f ==12) { 
      pt.Write();
      pt2.Write();
      pzl.Write();
      pzh.Write();
      mhh.Write();
      hth.Write();
      hcth.Write();
      hths.Write();
      hcths.Write(); 
      bin1.Write();
      bin2->Write();
      bin3->Write();
      bin4->Write();
      //bin2[nhist].Write();    
      }// write only after SM and last file

    //}
  cout << " " << ns << " files read" << endl;

  cout << outfile << " wrote."<< endl;
  out->Write();
  out->Close();
  delete out;
}

