// M. Dall'Osso
// To create root file with kin distros from ascii files.
// .L makeDistros5D.C++
// makeDistros5D()
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
int ns = 13;   //number of samples
//int ns = 5;   //number of samples
string option = "_13TeV"; //debug
const int nevBench = 100000;	  //number of ev per sample
const int nevSM = 3000000;	  //number of ev per sample

string inputPath = "";  //folder with ascii lhe files (outside 'git' area)
//string fileslist_st = "utils/list_ascii_13TeV_1593.txt"; //ascii names list !!!!!!!!!!!!!!!!
string fileslist_st = "samples_JHEP.txt"; //file 0 is a high stats SM; the others are the JHEP benchmaks
//string fileslist_st = "samples_JHEP_2_3_5_9.txt"; //file 0 is a high stats SM; the others are the JHEP benchmaks

//to be changed accordingly to lhe structure (3p, 5p,..)
//string folder1_st = "0-851";
//string folder2_st = "852-1593";
//int split = 851;

TLorentzVector P1, P2, P12, P1boost, P2boost;
bool update = false;
	
///////////////////////////////////
void makeDistros5D(){
  // we hill have only two sets of histograms
  // 0 is a high stats SM; the other the sum of JHEP benchmaks

  //out file
  TFile *out(0);
  std::stringstream sstr;
  //sstr << "Distros_" << np << "p_SM600k_sumBenchJHEP" << option;
  sstr << "Distros_" << np << "p_SM3M_sumBenchJHEP" << option;
  //sstr << "Distros_" << np << "p_SM3M_sumBenchJHEP_2_3_5_9" << option;
  string outfile = sstr.str() + ".root";
  if(!update)  { out = TFile::Open(outfile.c_str(), "RECREATE"); }  //RECREATE
  else           out = TFile::Open(outfile.c_str(), "UPDATE");   

  //TDirectory *batch1 = out->mkdir(folder1_st.c_str());
  //TDirectory *batch2 = out->mkdir(folder2_st.c_str());

  typedef event bench[nevSM];
  bench *ev = new bench[ns]; 

  char htitle2[20];
  char htitle3[20];

      //string samplename = std::to_string(nhist); // go with ordering only.
      TH1D pt[2], pt2[2], pzl[2], pzh[2], mhh[2];
      TH1D hth[2], hcth[2], hths[2], hcths[2];
      vector<TH2D *>  bin1 , bin2, bin3, bin4;
   

      for(int f=0; f<2; ++f)  { 
      string samplename = to_string(f); // go with ordering only.
      sprintf (htitle2,"%s_pt",samplename.c_str()); //debug
      pt[f].SetName(htitle2);
      pt[f].SetTitle(htitle2);
      pt[f].SetBins(100,0.,600.);

      sprintf (htitle2,"%s_pt2",samplename.c_str()); //debug
      pt2[f].SetName(htitle2);
      pt2[f].SetTitle(htitle2);
      pt2[f].SetBins(100,0.,600.);

      sprintf (htitle2,"%s_pzl",samplename.c_str());
      pzl[f].SetName(htitle2);
      pzl[f].SetTitle(htitle2);
      pzl[f].SetBins(500,-1000.,1000.); //400

      sprintf (htitle2,"%s_pzh",samplename.c_str());
      pzh[f].SetName(htitle2);
      pzh[f].SetTitle(htitle2);
      pzh[f].SetBins(500,0.,2500.);

      sprintf (htitle2,"%s_mhh",samplename.c_str());
      mhh[f].SetName(htitle2);
      mhh[f].SetTitle(htitle2);
      mhh[f].SetBins(200,0.,1000.);

      sprintf (htitle2,"%s_hth",samplename.c_str());
      hth[f].SetName(htitle2);
      hth[f].SetTitle(htitle2);
      hth[f].SetBins(200,0.,3.2); //debug

      sprintf (htitle2,"%s_hcth",samplename.c_str()); //debug
      hcth[f].SetName(htitle2);
      hcth[f].SetTitle(htitle2);
      hcth[f].SetBins(200,-1.,1.); //debug
 
      sprintf (htitle2,"%s_hths",samplename.c_str());
      hths[f].SetName(htitle2);
      hths[f].SetTitle(htitle2);
      hths[f].SetBins(200,0.,3.2); //debug

      sprintf (htitle2,"%s_hcths",samplename.c_str()); //debug
      hcths[f].SetName(htitle2);
      hcths[f].SetTitle(htitle2);
      hcths[f].SetBins(100,0.,1.); //debug

      sprintf (htitle2,"H%sbin1",samplename.c_str()); //debug
      TH2D *hdumb = new TH2D(htitle2, htitle2, 90,0.,1800.,10,-1,1.);
      bin1.push_back(hdumb);

      //Float_t binsx[14]  = { 250.,270.,300.,330.,360.,390., 420.,450.,500.,550.,600.,700.,800.,1000.}; 
      Float_t binsxM[16]  = { 247.,270.,300.,330.,360.,390., 420.,450.,500.,550.,600.,700.,800.,1000.,1500.,50000 }; 
      Float_t binsy[4]  = { -1., -0.55,0.55,1. };
      sprintf (htitle2,"H%sbin3",samplename.c_str()); //debug
      TH2D *bin3dumb = new TH2D(htitle2, htitle2,15,binsxM,3,binsy);
      bin3.push_back(bin3dumb);

      Float_t binsx[14]  = { 250.,270.,300.,330.,360.,390., 420.,450.,500.,550.,600.,700.,800.,1000. }; 
      //Float_t binsy[4]  = { -1., -0.55,0.55,1. };
      sprintf (htitle2,"H%sbin2",samplename.c_str()); //debug
      TH2D *bin2dumb = new TH2D(htitle2, htitle2,13,binsx,3,binsy);
      bin2.push_back(bin2dumb);

      Float_t binsxM2[60]  = { 250,260,270,280,290,300,310,320,330,340,
                               350,360,370,380,390,400,410,420,430,440, 
                               450,460,470,480,490,500,510,520,530,540,
                               550,560,570,580,590,600,610,620,630,640,
                               650,660,670,680,690,700,750,800,850,900,
                               950,1000,1100,1200,1300,1400,1500.,1750,2000,50000}; 
      Float_t binsySim[5]  = {  0.0,0.4,0.6,0.8, 1.0};
      sprintf (htitle3,"H%sbin4",samplename.c_str()); //debug
      TH2D *bin4dumb = new TH2D(htitle3, htitle3,59,binsxM2,4,binsySim);
      bin4.push_back(bin4dumb);

      //bin1[f].SetName(htitle2);
      //bin1[f].SetTitle(htitle2);
      //bin1[f].SetBins(90,0.,1800.,10,-1,1.); //debug
      //bin1[f].GetXaxis()->SetRange(0.,1800.);
      //bin1[f].GetYaxis()->SetRange(-1,1.);
      //bin1[f].Rebin2D(90,10,htitle2);

      //sprintf (htitle2,"%s_bin2",samplename.c_str()); //debug
      //bin2[f].SetName(htitle2);
      //bin2[f].SetTitle(htitle2);
      //bin2[f].SetBins(50,0.,1300.,5,0.,1.); //debug
      }// close declare histos

  // Reading ASCII, one file a time
  // ------------------------------
  ifstream filelist5(fileslist_st);
  ifstream infile;
  int nf = 0;
  for(int f=0; f<13; ++f) { // ns
  //for(int f=0; f<5; ++f) { // ns
    cout << "Reading file # " << f << endl;
    ostringstream fnumber;
    string filename;
    string fname;
    filelist5 >> fname;

    //fname = "ascii_" + samplename + ".txt";
    filename = inputPath+fname.c_str();
    //cout << filename << endl;
    infile.open(filename.c_str());
    if(!infile)	{      //check if file exists
	printf( "WARNING: no input file %s \n", fname.c_str());
    }
    else nf++;
     
   // 1 = higgs1; 2 = higgs2;
    int pID;
    int nev=0;
    if(f==0) nev = nevSM; else nev = nevBench;
    for (int k=0; k<nev; ++k) {  // loop on number of events
//        infile >> pID >> ev[f][k].px1 >> ev[f][k].py1 >> ev[f][k].pz1 >> ev[f][k].E1 >> ev[f][k].m1;
//        infile >> pID >> ev[f][k].px2 >> ev[f][k].py2 >> ev[f][k].pz2 >> ev[f][k].E2 >> ev[f][k].m2;
        infile >> pID >> ev[f][k].px1 >> ev[f][k].py1 >> ev[f][k].pz1 >> ev[f][k].E1 ;
        infile >> pID >> ev[f][k].px2 >> ev[f][k].py2 >> ev[f][k].pz2 >> ev[f][k].E2 ;
      }
      infile.close();    
      // in which histogram to save
      int nhist=0;
      if(f==0) nhist = 0; else nhist = 1;
      // Some preprocessing:
      // 1 - order by pt -> pthi, ptlo
      // 2 - compute dphi
      // 3 - flip sign of pzhi, pzlo if pzhi is negative
      // -----------------------------------------------
      double costheta = -99, theta = -99, thetast = -99, costhetast = -99;
      for (int k=0; k<nev; k++) {

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
        pt[nhist].Fill(ev[f][k].pt);
        pt2[nhist].Fill(ev[f][k].pt2);
        pzl[nhist].Fill(ev[f][k].pzl);
        pzh[nhist].Fill(ev[f][k].pzh);
        mhh[nhist].Fill(P12.M());

       //angle computation   
        theta = P1.Theta();  //TMath::ACos(P1.Pz()/P1.P());
        costheta = P1.CosTheta();
        hth[nhist].Fill(theta); //debug
        hcth[nhist].Fill(costheta); //debug

       //star angle computation           
        P1boost = P1;
        P12 = P1 + P2; // this is the total vectorial momenta of the system
        P1boost.Boost(-P12.BoostVector()); 
        thetast = P1boost.Theta();  
        costhetast = P1boost.CosTheta();
        hths[nhist].Fill(thetast); 		
        hcths[nhist].Fill(costhetast); 

        costhetast = P1boost.CosTheta(); // this is the costTheta
        bin1[nhist]->Fill(P12.M(),costhetast); 
        bin2[nhist]->Fill(P12.M(),costhetast); 
        bin3[nhist]->Fill(P12.M(),costhetast); 
        bin4[nhist]->Fill(P12.M(),abs(costhetast)); 
      }
      //if(f<=split) batch1->cd();
      //else batch2->cd();
     if(f ==0 || f ==12) { 
      pt[nhist].Write();
      pt2[nhist].Write();
      pzl[nhist].Write();
      pzh[nhist].Write();
      mhh[nhist].Write();
      hth[nhist].Write();
      hcth[nhist].Write();
      hths[nhist].Write();
      hcths[nhist].Write(); 
      bin1[nhist]->Write();
      bin2[nhist]->Write();    
      bin3[nhist]->Write();    
      bin4[nhist]->Write();    
      }// write only after SM and last file

    }
  cout << " " << nf << " files read" << endl;

  cout << outfile << " wrote."<< endl;
  out->Write();
  out->Close();
  delete out;
}

