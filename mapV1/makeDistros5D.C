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
int ns = 12;// 1507;   //number of samples
string option = "_13TeV"; //debug
const int nev = 500000;	  //number of ev per sample

string inputPath = "";  //folder with ascii lhe files (outside 'git' area)
string fileslist_st = "benchmarks_vJHEP.txt"; //ascii names list !!!!!!!!!!!!!!!!

//to be changed accordingly to lhe structure (3p, 5p,..)
string folder1_st = "0-851";
string folder2_st = "852-1593";
int split = 851;

TLorentzVector P1, P2, P12, P1boost, P2boost;
bool update = false;
		
///////////////////////////////////
void makeDistros5D(){

  //out file
  TFile *out(0);
  std::stringstream sstr;
  sstr << "Distros_" << np << "p_" << nev << "ev_"<< ns << "sam" << option;
  string outfile = sstr.str() + "_JHEP_500K.root";
  if(!update)  { out = TFile::Open(outfile.c_str(), "RECREATE"); }  //RECREATE
  else           out = TFile::Open(outfile.c_str(), "UPDATE");   

  //TDirectory *batch1 = out->mkdir(folder1_st.c_str());
  //TDirectory *batch2 = out->mkdir(folder2_st.c_str());

  typedef event bench[nev];
  bench *ev = new bench[ns]; 

  char htitle2[20];

  // Reading ASCII, one file a time
  // ------------------------------
  ifstream filelist5(fileslist_st);
  ifstream infile;
  int nf = 0;
  for(int f=0; f<ns; ++f) {
    //cout << "Reading file # " << f << endl;
    ostringstream fnumber;
    string filename;
    string fname;
    string samplename = std::to_string(f); // go with ordering only.
    filelist5 >> fname;
    //to extract samplename
    /*//debug!!!!
    int len = 0;
    if(f<851) len = fname.length()-10 - fname.find("L");
    else len = fname.length()-4 - fname.find("L");
    samplename = fname.substr(fname.find("L"), len);
    */
    //if(f==0 || f==851 || f==852){
    //  cout << samplename << endl;
    //    }

    //fname = "ascii_" + samplename + ".txt";
    filename = inputPath+fname.c_str();
    //cout << filename << endl;
    infile.open(filename.c_str());
    if(!infile)	{      //check if file exists
	printf( "WARNING: no input file %s \n", fname.c_str());
    }
    else nf++;
     
   // 1 = higgs1; 2 = higgs2;
    for (int k=0; k<nev; ++k) {  // loop on number of events
        infile >> ev[f][k].px1 >> ev[f][k].py1 >> ev[f][k].pz1 >> ev[f][k].E1 >> ev[f][k].m1;
        infile >> ev[f][k].px2 >> ev[f][k].py2 >> ev[f][k].pz2 >> ev[f][k].E2 >> ev[f][k].m2;
      }
      infile.close();    

      TH1D pt, pt2, pzl, pzh, mhh;
      TH1D hth, hcth, hths, hcths;
      TH2D bin1, bin2;

      sprintf (htitle2,"%s_pt",samplename.c_str()); //debug
      pt.SetName(htitle2);
      pt.SetTitle(htitle2);
      pt.SetBins(60,0.,1200.);

      sprintf (htitle2,"%s_pt2",samplename.c_str()); //debug
      pt2.SetName(htitle2);
      pt2.SetTitle(htitle2);
      pt2.SetBins(110,0.,1200.);

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
      //mhh.SetTitle(htitle2);
      mhh.SetMinimum(0.1);;
      mhh.SetBins(60,0.,1800.);
      

      sprintf (htitle2,"%s_hth",samplename.c_str());
      hth.SetName(htitle2);
      hth.SetTitle(htitle2);
      hth.SetBins(200,0.,3.2); //debug

      sprintf (htitle2,"%s_hcth",samplename.c_str()); //debug
      hcth.SetName(htitle2);
      hcth.SetTitle(htitle2);
      hcth.SetBins(10,-1.,1.); //debug
 
      sprintf (htitle2,"%s_hths",samplename.c_str());
      hths.SetName(htitle2);
      hths.SetTitle(htitle2);
      hths.SetBins(200,0.,3.2); //debug

      sprintf (htitle2,"%s_hcths",samplename.c_str()); //debug
      hcths.SetName(htitle2);
      hcths.SetTitle(htitle2);
      hcths.SetBins(5,0.,1.); //debug

      sprintf (htitle2,"%s_bin1",samplename.c_str()); //debug
      bin1.SetName(htitle2);
      bin1.SetTitle(htitle2);
      bin1.SetBins(90,0.,1800.,10,-1,1.); //debug
      
      sprintf (htitle2,"%s_bin2",samplename.c_str()); //debug
      bin2.SetName(htitle2);
      bin2.SetTitle(htitle2);
      bin2.SetBins(90,0.,1800.,10,-1,1.); //debug
      
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

        //theta = P2.Theta();  //TMath::ACos(P1.Pz()/P1.P());
        // costheta = P2.CosTheta();
        // hth.Fill(theta); //debug
        // hcth.Fill(costheta); //debug

       //star angle computation           
        P1boost = P1;
        //P2boost = P2;
        //minus needed? ...
        P1boost.Boost(-P12.BoostVector()); //equal to (-P1.px()/P1.e(),-P1.py()/P1.e(),-P1.pz()/P1.e())
        //P2boost.Boost(-P12.BoostVector()); //equal to (-P2.px()/P2.e(),-P2.py()/P2.e(),-P2.pz()/P2.e())

        thetast = P1boost.Theta();  //equal to TMath::ACos(P1.Pz()/P1.P());
        costhetast = P1boost.CosTheta();
//        if (costhetast< 0) costhetast *= -1; //to get abs
        hths.Fill(thetast); 		//debug
        hcths.Fill(abs(costhetast)); //debug

//        thetast = P2boost.Theta();
//        costhetast = P2boost.CosTheta();
//        if (P12.pz()< 0) costhetast *= -1; //to get abs
//        hths.Fill(thetast); 		//debug
//        hcths.Fill(abs(costhetast)); //debug

//        if(k==0) cout << samplename << "  " << P12.M() << "  " << ev[f][k].M <<endl; 	
        bin1.Fill(P12.M(),costhetast);
        bin2.Fill(P12.M(),costhetast);
      }
      //if(f<=split) batch1->cd();
      //else batch2->cd();
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
      bin2.Write();
      
    }
  cout << " " << nf << " files read" << endl;

//  cout << outfile << " wrote."<< endl;
  out->Write();
  out->Close();
  delete out;
}

