// M. Dall'Osso
// To create root file with kin distros from ascii files.
// .L makeDistros5D_envelope.C++
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
const int nc = 12;	 //number of clusters
int ns = 7;// 1507;   //number of samples
string option = "_13TeV"; //debug
const int nev = 20000;	  //number of ev per sample

string inputPath = "/Users/Xanda/Documents/codes/git/generateHH/envelopeShapes/doOutlayers/hh_lhe/";  //folder with ascii lhe files (outside 'git' area)

string fileslist_st1[12] = {"doOutlayers/outlayers_JHEP1.txt", "doOutlayers/outlayers_JHEP2.txt", "doOutlayers/outlayers_JHEP3.txt", "doOutlayers/outlayers_JHEP4.txt", "doOutlayers/outlayers_JHEP5.txt","doOutlayers/outlayers_JHEP6.txt", "doOutlayers/outlayers_JHEP7.txt", "doOutlayers/outlayers_JHEP8.txt", "doOutlayers/outlayers_JHEP9.txt",
    "doOutlayers/outlayers_JHEP10.txt","doOutlayers/outlayers_JHEP11.txt", "doOutlayers/outlayers_JHEP12.txt"}; 
string folder1_st[12] = {"clu1", "clu2", "clu3", "clu4", "clu5", "clu6", "clu7", "clu8","clu9", "clu10", "clu11", "clu12"};


/*string fileslist_st1 = "outlayers_JHEP1.txt"; //ascii names list !!!!!!!!!!!!!!!!
string fileslist_st2 = "outlayers_JHEP2.txt"; 
string fileslist_st3 = "outlayers_JHEP3.txt"; 
string fileslist_st4 = "outlayers_JHEP4.txt"; 
string fileslist_st5 = "outlayers_JHEP5.txt"; 
string fileslist_st6 = "outlayers_JHEP6.txt"; 
string fileslist_st7 = "outlayers_JHEP7.txt"; 
string fileslist_st8 = "outlayers_JHEP8.txt"; 
string fileslist_st9 = "outlayers_JHEP9.txt"; 

//to be changed accordingly to lhe structure (3p, 5p,..)
string folder1_st = "clu1";
string folder2_st = "clu2";
string folder3_st = "clu3";
string folder4_st = "clu4";
string folder5_st = "clu5";
string folder6_st = "clu6";
string folder7_st = "clu7";
string folder8_st = "clu8";
string folder9_st = "clu9";
int split = 851;
*/

TLorentzVector P1, P2, P12, P1boost, P2boost;
bool update = false;
		
///////////////////////////////////
void makeDistros5D_envelope(){

  //out file
  TFile *out(0);
  std::stringstream sstr;
  sstr << "Distros_envelope_" << np << "p_" << nev << "ev_"<< ns << "sam" << option;
  string outfile = sstr.str() + ".root";
  if(!update)  { out = TFile::Open(outfile.c_str(), "RECREATE"); }  //RECREATE
  else           out = TFile::Open(outfile.c_str(), "UPDATE");   

//  TDirectory *batch1[nc];
//  for ( int f=0; f<nc; ++f) batch1[f] = out->mkdir(folder1_st[f].c_str());
    
    /*
  TDirectory *batch1 = out->mkdir(folder1_st.c_str());
  TDirectory *batch2 = out->mkdir(folder2_st.c_str());
  TDirectory *batch3 = out->mkdir(folder3_st.c_str());
  TDirectory *batch4 = out->mkdir(folder4_st.c_str());
  TDirectory *batch5 = out->mkdir(folder5_st.c_str());
  TDirectory *batch6 = out->mkdir(folder6_st.c_str());    
  TDirectory *batch7 = out->mkdir(folder7_st.c_str());
  TDirectory *batch8 = out->mkdir(folder8_st.c_str());
  TDirectory *batch9 = out->mkdir(folder9_st.c_str());
    */
    
  typedef event bench[nev];
  bench *ev = new bench[ns]; 

  char htitle2[20];

  // Reading ASCII, one file a time
  // ------------------------------
  //ifstream filelist1[nc];
  //for ( int f=0; f<nc; ++f) filelist1.at(f)(fileslist_st1[f]);

/*
  ifstream filelist1(fileslist_st1);
  ifstream filelist2(fileslist_st2);
  ifstream filelist3(fileslist_st3);
  ifstream filelist4(fileslist_st4);
  ifstream filelist5(fileslist_st5);
  ifstream filelist6(fileslist_st6);
  ifstream filelist7(fileslist_st7);
  ifstream filelist8(fileslist_st8);
  ifstream filelist9(fileslist_st9);
 */
    
  ifstream infile;
  TDirectory *batch1;
  int nf = 0;
  for(int j=0; j<nc; ++j) {
   
    ifstream filelist1(fileslist_st1[j]);
    cout << "Reading cluster # " << fileslist_st1[j] << endl;
      cout<<endl;
    batch1 = out->mkdir(folder1_st[j].c_str());
    //batch1[j].open();
    // make the  name of the file
    vector <string> constname;
    string filename;
    for(int f=0; f<ns; ++f) {
        
        string samplename;// = std::to_string(f); // go with ordering only.
        samplename = std::to_string(f);
        // actually make the path
        ostringstream fnumber;
        for(int k=0; k<5; ++k){
           string fname;
           filelist1 >> fname;
           cout<<fname<<" ";
           constname.push_back(fname);
        }
        std::stringstream sstr;
        sstr << "L" << constname.at(0) << "kt" << constname.at(1) << "cT"<< constname.at(2) << "cg" << constname.at(3) << "c2g" << constname.at(4);
        string outfile = sstr.str() + ".lhe.decayed";
        cout<<outfile<<endl<<endl;
        constname.clear();
         // go with ordering only.
        //fname = "ascii_" + samplename + ".txt";
        filename = inputPath+outfile;
        //cout << filename << endl;
        infile.open(filename.c_str());
        if(!infile) {printf( "WARNING: no input file %s \n", filename.c_str()); } 
        else {nf++; 
     
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

        //star angle computation           
        P1boost = P1;
        //P2boost = P2;
        //minus needed? ...
        P1boost.Boost(-P12.BoostVector()); //equal to (-P1.px()/P1.e(),-P1.py()/P1.e(),-P1.pz()/P1.e())
        thetast = P1boost.Theta();  //equal to TMath::ACos(P1.Pz()/P1.P());
        costhetast = P1boost.CosTheta();
        hths.Fill(thetast); 		//debug
        hcths.Fill(abs(costhetast)); //debug

        bin1.Fill(P12.M(),costhetast);
        bin2.Fill(P12.M(),costhetast);
      }
      //if(f<=split) 
      batch1->cd();
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
      } // if there is file
      
    }
  cout << " " << nf << " files read " << endl;
        
  } // close for cluster folder

//  cout << outfile << " wrote."<< endl;
  out->Write();
  out->Close();
  cout<<"Wrote on "<<outfile<<endl;
  delete out;
}

