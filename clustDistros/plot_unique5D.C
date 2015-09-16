// M.Dall'Osso
// To get distribution plots from clustering - 1 canvas per cluster.
// .L plot_unique5D.C+
// plot(13, 4)
//................................

#include <TROOT.h>
#include <TStyle.h>
#include <TH1F.h>
#include <TH1.h>
#include <TH2.h>
#include <TProfile.h>
#include <TFile.h>
#include <TCanvas.h>
#include <TLegend.h>
#include <TPaveStats.h>
#include <TEfficiency.h>
#include <TGraphAsymmErrors.h>
#include <TGaxis.h>
#include <iostream>
#include <TLatex.h>
#include <THStack.h>
#include <fstream>
#include <sstream>
#include <string>
#include <vector>

// input files - parameters - TO BE MODIFIED
//******************************************
string Totsamples = "1488";  //number of lhe files //1053
int CMenergy = 13;   //tev
int pars = 5;        //space parameters dimension
bool Privat = false; //true
int Maxtotclu = 20;  //max number of clusters

string testoption = ""; //debug
string iNoption = "_13TeV";       //see 'makeDistros5D.C'
string Inputfolder = "results/LogP/";  //read directly results with sample number
TString Outfolder = "../../plots_5par_13TeV_1488/"; //to be created for final plots store - outside 'git' area

//see 'makeDistros5D.C'
string folder1_st = "0-851";
string folder2_st = "852-1488";
int split = 851;

//******************************************

TString filename; 
TString mainDIR;
TString suffix;
bool initialized = false;
bool lgRIGHT = false;
bool lgTOP = true;
std::vector< std::vector<string> > clu;

bool init(int totClu) {

  //dafault file name format
  std::stringstream inputclusters;
  std::vector<string> samples;

  //set Distros_.root filename
  std::stringstream sstr;
  sstr << "../../Distros_" << pars << "p_20000ev_"<< Totsamples << "sam" << iNoption << ".root";
  filename = sstr.str();

  //read cluster result
  inputclusters << Inputfolder << "clustering_nev20k_Nclu" << totClu << "_50_5.asc";
//  inputclusters << Inputfolder << "res_" << pars << "p_" << CMenergy << "TeV" << testoption << "_NClu" << totClu << ".dat"; //<< testoption
  string infname = inputclusters.str();
  ifstream inresfile;
  inresfile.open(infname.c_str());
  if(!inresfile)	{      //check if file exists
    printf( "ERROR: no input file %s \n", infname.c_str());
    return false;
  }
  std::cout << "# Start reading sample names from file" << std::endl;
  bool stop = false;
  int i = 1;
  do{
    samples.clear();
    string input;
    std::getline(inresfile, input);
    if(input.size() == 0) {
	stop = true; //no blank line in input      
	break;
    }
    istringstream istring(input);   
   //cout << " Cluster #" << i << " -> ";
    int in;
    int j = 0;
    //while (istring.getline (in,50,',')) { //debug - check 15
    while (istring >> in) {
      //cout << in << " "; //debug
      samples.push_back(std::to_string(in));
      j++;
    }
   //cout << j << " sample" << endl;
    i++;
    if(!stop)clu.push_back(samples);    
    //cout << endl; //debug
  }while(!stop);

  //build nodes comparison
  string S = "none";
  for(unsigned int nc=0; nc<(clu.size()); nc++){
      S = clu[nc][0];
      samples.push_back(S);
  }
  clu.push_back(samples);    
  samples.clear();

  mainDIR = "/";
  suffix  = "";  
  initialized = true;
  return true;
}

void draw_all(TPad* p, std::vector<TH1F*> h,
	  TString xTitle, double xmin, double xmax, double ymin, double ymax,
	  TString legHeader = "", bool legRIGHT = true, bool legTOP = true,
	  bool logX = false, bool logY = false, bool stat = false,
	  double scale = -9., int rebin = -1, int orbin = -1, TString option = "") {

  p->cd();
  if (logX) gPad->SetLogx();
  if (logY) gPad->SetLogy();

  //needed????
  gPad->SetFrameFillColor(0);
  gPad->SetFrameBorderMode(0);
  gPad->SetFrameFillColor(0);
  gPad->SetFrameBorderMode(0);

  double legxmin = (legRIGHT ? 0.6 : 0.18);
  double legxmax = legxmin+0.20;
  double legymin = (legTOP ? 0.92 : 0.15);
  double legymax = legymin+0.08;
  TLegend* leg = new TLegend(legxmin,legymin,legxmax,legymax);
  if (legHeader!="") leg->SetHeader(legHeader);
  leg->SetTextSize(0.06);
  leg->SetFillColor(0);
  leg->SetLineColor(0);

  TString options = (option=="" ? "pe" : option);
  
  //normalize and set y range
  ymax=0.;
  h[0]->Sumw2();  
  //double norm = 10000.;     
  for (size_t i=0; i<h.size(); i++) {  
    if(h[i]->GetNbinsX() != orbin) cout << "WARNING: orbin for " << h[i]->GetName() << " are " << h[i]->GetNbinsX() << endl;
    if (rebin>0) h[i]->Rebin(rebin);
    //cout << h[i]->GetNbinsX() << endl; //debug
    //scale = norm/(h[i]->Integral());
    //h[i]->Scale(scale);
    if (h[i]->GetMaximum() > ymax) ymax = h[i]->GetMaximum();
  }
  ymax = ymax*1.10;

  for (size_t i=0; i<h.size(); i++) {
    h[i]->GetXaxis()->SetRangeUser(xmin,xmax);
    h[i]->SetMinimum(ymin);
    h[i]->SetMaximum(ymax);
    if (i==0  ){    //just for the first one && ( || i==6 || i ==11)
       h[i]->GetYaxis()->SetTitleSize(0.06);
       h[i]->GetYaxis()->SetTitleOffset(1);
       h[i]->GetYaxis()->SetLabelSize(0.05);
       h[i]->GetYaxis()->SetLabelOffset(0.8);
    }
    if (i==0){ //11 || i==12 || i==13
       h[i]->GetXaxis()->SetTitleSize(0.06);
       h[i]->GetXaxis()->SetTitleOffset(1);
       h[i]->GetXaxis()->SetLabelSize(0.05);
       h[i]->GetYaxis()->SetLabelOffset(0.8);
    }
    if (i==1) options = options + (stat ? "sames" : "same"); //once is enought
    h[i]->Draw(options);
  }  
  leg->Draw("same");  
  //p->Update();
}

/*void draw_all_ratio(TPad* p, std::vector<TH1F*> h,
	  TString xTitle, double xmin, double xmax, TString legHeader = "", 
          bool legRIGHT = true, bool legTOP = true, bool logX = false, bool stat = false, 
          int rebin = -1, TString option = "") { //int orbin = -1,

  p->cd();
  if (logX) gPad->SetLogx();
  double legxmin = (legRIGHT ? 0.6 : 0.18);
  double legxmax = legxmin+0.20;
  double legymin = (legTOP ? 0.80 : 0.15);
  double legymax = legymin+0.10;
  TLegend* leg = new TLegend(legxmin,legymin,legxmax,legymax);
  if (legHeader!="") leg->SetHeader(legHeader);
  leg->SetTextSize(0.06);
  leg->SetFillColor(0);
  leg->SetLineColor(0);

  TString options = (option=="" ? "pe" : option);
  
  if (rebin>0) h[h.size()-1]->Rebin(rebin); //to rebin benchmark before divide
  for (size_t i=0; i<h.size(); i++) {
    //if(h[i]->GetNbinsX() != orbin) cout << "WARNING: orbin for " << h[i]->GetName() << " are " << h[i]->GetNbinsX() << endl;
    if (rebin>0 && i<(h.size()-1)) h[i]->Rebin(rebin);
    TH1F* ratio = (TH1F*)h[i]->Clone("ratio_"+i);
    ratio->Sumw2();
    ratio->Divide(h[h.size()-1]); //benchmark is at the end.

    if (logX) gPad->SetLogx();
    ratio->SetMarkerStyle(20+i);
    ratio->SetMarkerSize(1.0); //1.2
    ratio->GetXaxis()->SetRangeUser(xmin,xmax);
    ratio->SetMinimum(-0.1);
    ratio->SetMaximum(3.5);
    if (i==0){    //just for the first one
     ratio->GetXaxis()->SetLabelSize(0.07);
     ratio->GetXaxis()->SetTitle(xTitle);
     ratio->GetXaxis()->SetTitleOffset(1);
     ratio->GetXaxis()->SetTitleSize(0.06);
     ratio->GetYaxis()->SetTitle("ratio");
     ratio->GetYaxis()->SetTitleSize(0.06);
     ratio->GetYaxis()->SetTitleOffset(1.3);
     ratio->GetYaxis()->SetLabelSize(0.05);
    }
    if (i==1) options = options + (stat ? "sames" : "same"); //once is enought
    ratio->Draw(options);
  }
  leg->Draw("same");
}*/

void performancePlot1D(TPad* p, int nclust, TString hName,
		       double xmin, double xmax, double ymin, double ymax,
		       TString xaxis, TString yaxis, bool logX = false, bool logY = false,
		       bool stat = false, double scale = -9.,
		       int rebin = -1, int orbin = -1,
		       TString option = "")
{

  gROOT ->Reset();
  //=========  settings ====================
  gROOT->SetStyle("Plain");
 
  //  if (!initialized) init(inputclusters);
  //=============================================
  if(nclust < 0  || nclust >= (int)clu.size()){
    std::cout << "ERROR: bad ncluster value(" << nclust+1 << "), ncluster between 1 " << "and " << clu.size() << std::endl;
    return;
  }
  std::vector<TH1F*>  h;   
  TFile* f = new TFile(filename);
  if (f == NULL) return;
  
  //debug  
 // cout << (sizeof(L)/sizeof(std::string)) << " " << (sizeof(Y)/sizeof(std::string))<< " "  << (sizeof(C2)/sizeof(std::string)) << endl;

  int nc = nclust; //ehi!
  int size = clu[nc].size();
  //std::cout << "# Start reading distros from file" << std::endl;
  for(int nsam=1; nsam<size; nsam++) { //on samples - skip benchmark.   
    TH1F* histo = NULL;
    string sample = clu[nc][nsam];
    int s = stoi(sample);
    sample = sample + "_" + hName;
    TString fname = sample;
    //cout << sample.size() << endl;
    //std::cout << " Getting the sample: " << fname << std::endl;
    if(s <= split) f->cd(folder1_st.c_str()); //debug
    else f->cd(folder2_st.c_str());
    histo = (TH1F*)gDirectory->Get(fname); 
    histo->SetMarkerSize(1.0);
    histo->SetMarkerStyle(20);
    histo->SetLineWidth(1); //2
    histo->SetLineColorAlpha(kBlue, 0.25);
    histo->GetXaxis()->SetTitle(xaxis);
    histo->GetYaxis()->SetTitle(yaxis);
    h.push_back(histo);
  }
  //to append benchmark as last histo. 
  TH1F* histo = NULL;
  string sample = clu[nc][0];
  int s = stoi(sample);
  sample = sample + "_" + hName;
  TString fname = sample;
  //cout << sample.size() << endl;
  std::cout << " Getting the benchmark: " << fname << std::endl;
  if(s <= split) f->cd(folder1_st.c_str()); //debug
  else f->cd(folder2_st.c_str());
  histo = (TH1F*)gDirectory->Get(fname); 
  histo->SetMarkerSize(1.0);
  histo->SetMarkerStyle(20);
  histo->SetLineColor(kRed);
  histo->SetLineWidth(2);
  histo->GetXaxis()->SetTitle(xaxis);
  histo->GetYaxis()->SetTitle(yaxis);
  h.push_back(histo);

  cout << " Cluster size: " << size << " sample" << endl << endl;
  stringstream sst, sc;
  sc << "CLUSTER " << (nc+1) << " - " << "#samples: " << size;
  TString clusterLabel = sc.str();
  sst << nc+1;   
  
 if(hName=="hcths")ymin = 1000; //debug
 else ymin = 0;

 if(h.size()>0){
         draw_all(p, h, xaxis,xmin,xmax,ymin,ymax,
  	   clusterLabel,lgRIGHT,lgTOP, logX, logY, stat, scale,rebin,orbin,option);
 }  
 else cout << "WARNING: empty cluster!" << endl;

}
 
//plot call for different variables:
void plot_pt( TPad* p, int ncluster = 99, int rebin = 1, TString opt="") {
  performancePlot1D( p, ncluster-1,"pt",0.,450.,0.,800.,"pT^{h} [GeV]","", false, false, false,-9.,rebin,100,opt);
}

void plot_pzh( TPad* p, int ncluster = 99, int rebin = 4, TString opt="") {
  performancePlot1D( p, ncluster-1,"pzh",0.,1000.,0.,800.,"max#cbar pz^{h}#cbar [GeV]","", false, false, false,-9.,rebin,500,opt);
}

void plot_pzl( TPad* p, int ncluster = 99, int rebin = 4, TString opt="") {
  performancePlot1D( p, ncluster-1,"pzl",-300.,500.,0.,800.,"higgs p_{z lower} [GeV]","", false, false, false,-9.,rebin,500,opt);
}

void plot_mhh( TPad* p, int ncluster = 99, int rebin = 2, TString opt="") {
  performancePlot1D( p, ncluster-1,"mhh",240.,900.,0.,800.,"m_{hh} [GeV]","", false, false, false,-9.,rebin,200,opt);
}

void plot_hth( TPad* p, int ncluster = 99, int rebin = 2, TString opt="") {
  performancePlot1D( p, ncluster-1,"hth",0.,3.2,0.,800.,"higgs #theta","", false, false, false,-9.,rebin,200,opt);
}

void plot_hcth( TPad* p, int ncluster = 99, int rebin = 2, TString opt="") {
  performancePlot1D( p, ncluster-1,"hcth",-1.,1.,0.,800.,"higgs cos#theta","", false, false, false,-9.,rebin,200,opt);
}

void plot_hths( TPad* p, int ncluster = 99, int rebin = 2, TString opt="") {
  performancePlot1D( p, ncluster-1,"hths",0.,3.2,0.,800.,"higgs #theta*","", false, false, false,-9.,rebin,200,opt);
}

void plot_hcths( TPad* p, int ncluster = 99, int rebin = 2, TString opt="") {
  performancePlot1D( p, ncluster-1,"hcths",0.,1.,0.,800.,"#cbar cos#theta*#cbar","", false, false, false,-9.,rebin,100,opt);
}

TPad* setcanvas( int N, string var){

  stringstream title;  
  title << N << "clus_" << var;
  TCanvas* can = new TCanvas((TString)title.str(),(TString)title.str(),1125,700); //debug!
  can->cd();
  TPad* pad1 = new TPad("pad1","title",0.,1.,1.,0.95);
  pad1->Draw();
  TPad* pad2 = new TPad("pad2","histos",0.,0.95,1.,0.);
  pad2->Draw();

  pad1->cd();  
  stringstream header;
  if(Privat) header << "Private simulation 2015, #sqrt{s}=" << CMenergy << " TeV, " << Totsamples << " samples, " << N << " clusters, " << var; //testoption << ", " <<
  else     header << "Simulation 2015, #sqrt{s}=" << CMenergy << " TeV, " << Totsamples << " samples, " << N << " clusters, " << var; //testoption << ", " <<
  TLatex* text=new TLatex(0.03, 0.1, header.str().c_str());
  text->SetTextSize(0.5);
  text->Draw(); 

  return pad2;
}

//genaral function to plot all or single variable, single cluster.
void plot(int totclu = 20, int var = 0, int reb = 99, TString opt="hist") { 
// allonly: to plot all in one canvas; var: 1-pt, 2-pzh, 3-pzl, 4-mhh ;  nclu = 0 to do all the clusters

  bool doall = false;
  if(totclu == 0) doall = true;
  int totNclu;
  string app;

  for(int i=10; i<=Maxtotclu; i++) { //mintotclu .. continued!
    if(i==16) continue; //issue with that file.. debug
    if(!doall) totNclu = totclu;
    else   totNclu = i;

    std::stringstream outname;
    outname << pars << "par_" << CMenergy << "Tev_Nclu" << totNclu << testoption;

    //default rebin
    int reb1 = (reb == 99) ? 2 : reb;
    int reb2 = (reb == 99) ? 4 : reb;
    int reb3 = (reb == 99) ? 4 : reb;
    int reb4 = (reb == 99) ? 4 : reb;
    //  int reb5 = (reb == 99) ? 2 : reb;
    //  int reb6 = (reb == 99) ? 2 : reb;
    int reb7 = (reb == 99) ? 2 : reb;
    int reb8 = (reb == 99) ? 10 : reb;

    if(!init(totNclu)) return;     
  
    cout << clu.size() << endl; //DEBUG
    int size = clu.size()-1;
    int cols, rows; //debug
    app = "all";
    if(size<3)      {cols = 2; rows = 1;}
    else if(size<5) {cols = 2; rows = 2;}
    else if(size<7) {cols = 3; rows = 2;}
    else if(size<9) {cols = 4; rows = 2;}
    else if(size<13){cols = 4; rows = 3;}
    else if(size<16){cols = 5; rows = 3;}
    else if(size<21){cols = 5; rows = 4;}
    else return;
  
    if(var == 1 || var == 0) {
      TPad* pad2 = (TPad*)setcanvas(totNclu,"pT^{h}");
      pad2->Divide(cols,rows);
      for(int nc=1; nc<=(size); nc++) {
           TPad* pad= (TPad*)pad2->GetPad(nc);           
           plot_pt( pad, nc, reb1, opt);
      }
      pad2->GetCanvas()->SaveAs(Outfolder+outname.str()+"_pt_"+app+".png");
      pad2->GetCanvas()->SaveAs(Outfolder+outname.str()+"_pt_"+app+".pdf");
    }
    if(var == 2 ) { //|| var == 0
      TPad* pad2 = (TPad*)setcanvas(totNclu,"max#cbar pz^{h}#cbar");
      pad2->Divide(cols,rows);
      for(int nc=1; nc<=(size); nc++) {
           TPad* pad= (TPad*)pad2->GetPad(nc);           
           plot_pzh( pad, nc, reb2, opt);
      }
      pad2->GetCanvas()->SaveAs(Outfolder+outname.str()+"_pzh_"+app+".png");
      pad2->GetCanvas()->SaveAs(Outfolder+outname.str()+"_pzh_"+app+".pdf");
    }
    if(var == 3 ) { //|| var == 0
      TPad* pad2 = (TPad*)setcanvas(totNclu,"higgs p_{z lower}");
      pad2->Divide(cols,rows,10.,0);
      for(int nc=1; nc<=(size); nc++) {
           TPad* pad= (TPad*)pad2->GetPad(nc);           
           plot_pzl( pad, nc, reb3, opt);
      }
      pad2->GetCanvas()->SaveAs(Outfolder+outname.str()+"_pzl_"+app+".png");
      pad2->GetCanvas()->SaveAs(Outfolder+outname.str()+"_pzl_"+app+".pdf");
    }
    if(var == 4 || var == 0) {
      TPad* pad2 = (TPad*)setcanvas(totNclu,"di-Higgs mass");
      pad2->Divide(cols,rows);
      for(int nc=1; nc<=(size); nc++) {
           TPad* pad= (TPad*)pad2->GetPad(nc);           
           plot_mhh( pad, nc, reb4, opt);
      }
      pad2->GetCanvas()->SaveAs(Outfolder+outname.str()+"_mhh_"+app+".png");
      pad2->GetCanvas()->SaveAs(Outfolder+outname.str()+"_mhh_"+app+".pdf");
    }
    else if(var == 5) {

    }
    else if(var == 6) {

    }
    else if(var == 7) {
      TPad* pad2 = (TPad*)setcanvas(totNclu,"higgs #theta*");
      pad2->Divide(cols,rows);
      for(int nc=1; nc<=(size); nc++) {
           TPad* pad= (TPad*)pad2->GetPad(nc);           
           plot_hths( pad, nc, reb7, opt);
      }
      pad2->GetCanvas()->SaveAs(Outfolder+outname.str()+"_hths_"+app+".png");
      pad2->GetCanvas()->SaveAs(Outfolder+outname.str()+"_hths_"+app+".pdf");
    }
    if(var == 8 || var == 0) {
      TPad* pad2 = (TPad*)setcanvas(totNclu,"#cbar cos#theta*CS#cbar");
      pad2->Divide(cols,rows);
      for(int nc=1; nc<=(size); nc++) {
           TPad* pad= (TPad*)pad2->GetPad(nc);           
           plot_hcths( pad, nc, reb8, opt);
      }
      pad2->GetCanvas()->SaveAs(Outfolder+outname.str()+"_hcths_"+app+".png");
      pad2->GetCanvas()->SaveAs(Outfolder+outname.str()+"_hcths_"+app+".pdf");
    }
    else if(var != 1 && var != 2 && var != 3) cout << "wrong var value (0-8)" << endl; //debug!!
   
    clu.clear();
    if(!doall) return;

  }//end for  
}
