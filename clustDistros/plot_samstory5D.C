// M.Dall'Osso
// to plot the cluster in which a selected sample is, for all the different Nclus.
// .L plot_samstory5D.C+
// plot(variable, samplenumber*, sample2number* ) *see map file
// sample 1 and sample 2 must be always in the same cluster!!
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
#include <iomanip> 

// input files - parameters
//******************************************
string Totsamples = "1488";  //number of lhe files //1053
int CMenergy = 13;   //tev
int pars = 5;        //space parameters dimension
bool Privat = false; //true
int Maxtotclu = 20;  //max number of clusters

int totClus [] = {20,18,16,15,14,13,12,11,10,8,6,4,3,2}; //Nclu values for which you want the plot

string testoption = ""; //debug
string iNoption = "_13TeV";       //see 'makeDistros5D.C'
string Inputfolder = "results/LogP/";  //with cluster analysis results
TString Outfolder = "../../plots_5par_13TeV_1488/"; //to be created for final plots store - outside 'git' area
string mapNamefile = "utils/list_ascii_13TeV_1488_translate.txt"; //debug

string mapFile = "utils/map_5par_13Tev_2ndRound.dat";  //map to read sample name

//see 'makeDistros5D.C'
string folder1_st = "0-851";
string folder2_st = "852-1488";
int split = 851;

//******************************************

TString filename; 
TString mainDIR;
TString suffix;
bool initialized = false;
bool lgRIGHT = false;  //true cos
bool lgTOP = true; //false for pt, cos
std::vector< std::vector<string> > clu;
int nTotClus;

bool init() {

  //dafault file name format
  std::stringstream inputclusters;
  std::vector<string> samples;

  //set Distros_.root filename
  std::stringstream sstr;
  sstr << "../../Distros_" << pars << "p_20000ev_"<< Totsamples << "sam" << iNoption << ".root";
  filename = sstr.str();

  //read cluster result
  inputclusters << Inputfolder << "clustering_nev20k_Nclu" << nTotClus << "_50_5.asc";
//  inputclusters << Inputfolder << "res_" << pars << "p_" << CMenergy << "TeV" << testoption << "_NClu" << totClu << ".dat"; //<< testoption
  string infname = inputclusters.str();
  //cout << infname << endl;
  ifstream inresfile;
  inresfile.open(infname.c_str());
  if(!inresfile)	{      //check if file exists
    printf( "ERROR: no input file %s \n", infname.c_str());
    return false;
  }
  //std::cout << "# Start reading sample names from file" << std::endl;
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

/*string translate(string samname) {

  std::string kl, kt, c2, cg, c2g;

  if(samname.size()<25){
    std::size_t pos0 = samname.find("L");
    std::size_t pos1 = samname.find("y");
    std::size_t pos2 = samname.find("c");

    std::size_t len = pos1 - pos0 -1;
    kl = samname.substr(pos0+1,len); 
    len = pos2 - pos1 -1;
    kt = samname.substr(pos1+1,len); 
    c2 = samname.substr(pos2+1); 
    cg = "0.0";
    c2g = "0.0";

    if((pos0=kl.find("m"))<6)   kl.replace(pos0,1,"-"); //debug!
    if((pos0=kl.find("p"))<6)   kl.replace(pos0,1,"."); //debug!
    if((pos0=kt.find("m"))<6)   kt.replace(pos0,1,"-"); //debug!
    if((pos0=kt.find("p"))<6)   kt.replace(pos0,1,"."); //debug!
    if((pos0=c2.find("m"))<6)   c2.replace(pos0,1,"-"); //debug!
    if((pos0=c2.find("p"))<6)   c2.replace(pos0,1,"."); //debug!
  }
  else{
    std::size_t pos0 = samname.find("L");
    std::size_t pos1 = samname.find("y");
    std::size_t pos2 = samname.find("T");
    std::size_t pos3 = samname.find("g");
    std::size_t pos4 = samname.rfind("c");

    std::size_t len = pos1 - pos0 -1;
    kl = samname.substr(pos0+1,len); 
    len = pos2 - pos1 -2;
    kt = samname.substr(pos1+1,len); 
    len = pos3 - pos2 -2;
    c2 = samname.substr(pos2+1,len); 
    len = pos4 - pos3 -1;
    cg = samname.substr(pos3+1,len); 
    c2g = samname.substr(pos4+1); 

    if((pos0=kl.find("m"))<6)   kl.replace(pos0,1,"-"); //debug!
    if((pos0=kl.find("p"))<6)   kl.replace(pos0,1,"."); //debug!
    if((pos0=kt.find("m"))<6)   kt.replace(pos0,1,"-"); //debug!
    if((pos0=kt.find("p"))<6)   kt.replace(pos0,1,"."); //debug!
    if((pos0=c2.find("m"))<6)   c2.replace(pos0,1,"-"); //debug!
    if((pos0=c2.find("p"))<6)   c2.replace(pos0,1,"."); //debug!
    if((pos0=cg.find("m"))<6)   cg.replace(pos0,1,"-"); //debug!
    if((pos0=cg.find("p"))<6)   cg.replace(pos0,1,"."); //debug!
    if((pos0=c2g.find("m"))<6)  c2g.replace(pos0,1,"-"); //debug!
    if((pos0=c2g.find("p"))<6)  c2g.replace(pos0,1,"."); //debug!
  }

  std::stringstream name;
  name << std::setw(5); 
  name << "Kl=" << kl << ", Kt=" << kt << ", C2=" << c2 << ", Cg=" << cg << ", C2g=" << c2g;
  cout << "sample in legend: " << name.str() << endl;
  return name.str();
}*/

string translate(string samname) {

  int i = stoi(samname); //debug
  double kl =0, kt =0, c2 =0, cg =0, c2g =0;
  std::stringstream name;
  name << "";

  ifstream inf;
  inf.open(mapNamefile.c_str());
  if(!inf)	{      //check if file exists
    printf( "ERROR: no input file %s \n", mapNamefile.c_str());
    return name.str();
  }
  int j = 0;
  bool found = false;
  while(!inf.eof()){
    if(j == i-1){
      inf >> kl >> kt >> c2 >> cg >> c2g;
      found = true;
      break;
    }    
    string input;
    std::getline(inf, input);
    j++;
  }
  if(found){
    name << std::setw(5); 
    name << "Kl=" << kl << ", Kt=" << kt << ", C2=" << c2 << ", Cg=" << cg << ", C2g=" << c2g;
    cout << "BM in legend: " << name.str() << endl;
  }

  return name.str();
}

void draw_all(TPad* p, std::vector<TH1F*> h,
	  TString xTitle, double xmin, double xmax, double ymin, double ymax,
	  TString legHeader = "", bool legRIGHT = true, bool legTOP = true,
	  bool logX = false, bool logY = false, bool stat = false,
	  double scale = -9., int rebin = -1, int orbin = -1, TString option = "") {
  p->cd();
  if (logX) gPad->SetLogx();
  if (logY) gPad->SetLogy();

  double legxmin = (legRIGHT ? 0.2 : 0.63);
  double legxmax = legxmin+0.22;
  double legymin = (legTOP ? 0.75 : 0.18);
  double legymax = legymin+0.07;
  TLegend* leg = new TLegend(legxmin,legymin,legxmax,legymax);
  if (legHeader!="") leg->SetHeader(legHeader);
  leg->SetTextSize(0.07); //was 0.05
  leg->SetFillColor(0);
  leg->SetLineColor(0);

  TString options = (option=="" ? "pe" : option);
  //normalize and set y range
  ymax=0.;
  h[0]->Sumw2();  
  double norm = 1.;   
  for (size_t i=0; i<h.size(); i++) {  
    if(h[i]->GetNbinsX() != orbin) cout << "WARNING: orbin for " << h[i]->GetName() << " are " << h[i]->GetNbinsX() << endl;
    if (rebin>0) h[i]->Rebin(rebin);
    scale = norm/h[i]->Integral();
    h[i]->Scale(scale);
    if (h[i]->GetMaximum() > ymax) ymax = h[i]->GetMaximum();
  }
  for (size_t i=0; i<h.size(); i++) {
    h[i]->GetXaxis()->SetRangeUser(xmin,xmax);
    if (i==0){    //just for the first one
     h[i]->GetXaxis()->SetLabelSize(0.06);
     h[i]->GetXaxis()->SetLabelOffset(0.001);
     h[i]->GetXaxis()->SetTitle(xTitle);
     h[i]->GetXaxis()->SetTitleOffset(0.82);
     h[i]->GetXaxis()->SetTitleSize(0.07);
     h[i]->GetXaxis()->SetNdivisions(606);
     h[i]->GetYaxis()->SetTitle("");
     h[i]->GetYaxis()->SetTitleSize(0.07);
     h[i]->GetYaxis()->SetTitleOffset(3.);
     h[i]->GetYaxis()->SetLabelSize(0.06);
     h[i]->GetYaxis()->SetRangeUser(ymin,(ymax+ymax*0.1)); //debug
     h[i]->GetYaxis()->SetNdivisions(505);
    }
    if (i==1) options = options + (stat ? "sames" : "same"); //once is enought
    h[i]->Draw(options);
  }  
  leg->Draw("same");  
}

bool performancePlot1D(string thesam, string thesam2, TPad* p, int nclust, TString hName,
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
    return false;
  }
  std::vector<TH1F*>  h;   
  TFile* f = new TFile(filename);
  if (f == NULL) return false;
  
  int nc = nclust; //ehi!
  int size = clu[nc].size();
  //std::cout << "# Start reading distros from file" << std::endl;
  bool match = false;

  //searching cluster
  TH1F* histo2 = NULL;
  int nsam2 = 999;
  for(int ns=1; ns<size; ns++) { //on samples - skip benchmark.   
//debug - additional..
    if(clu[nc][ns] == thesam2){
        nsam2 = ns;
        string sample = clu[nc][ns];
        int s = stoi(sample);
        sample = sample + "_" + hName;
        TString fname = sample;
        //cout << sample.size() << endl;
        //std::cout << " Getting the sample: " << fname << std::endl;
        if(s <= split) f->cd(folder1_st.c_str()); //debug
        else f->cd(folder2_st.c_str());
        histo2 = (TH1F*)gDirectory->Get(fname); 
        histo2->SetMarkerSize(1.0);
        histo2->SetMarkerStyle(20);
        histo2->SetLineWidth(1); //2
        histo2->GetXaxis()->SetTitle(xaxis);
        histo2->GetYaxis()->SetTitle(yaxis);
        histo2->SetLineColor(kMagenta);
      }
  } //tow for needed?........

  for(int ns=0; ns<size; ns++) { //on samples
    if(clu[nc][ns] == thesam){
      bool found = false;
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
        histo->GetXaxis()->SetTitle(xaxis);
        histo->GetYaxis()->SetTitle(yaxis);
        if(nsam==ns) histo->SetLineColor(kMagenta); //kBlue
        else if (thesam2!="" && nsam==nsam2) continue; //second sample...
        else histo->SetLineColorAlpha(kYellow-5, 0.25);        
        if (!found) h.push_back(histo);
        else { 
          std::vector<TH1F*>::iterator it = h.end();  //to put the sample in the last position (before BM)
          h.insert (it-1,histo);
        }
        if(nsam==ns) found = true;
      }
      if (thesam2!="" && found){
      //to append second sample as last histo. 
      std::vector<TH1F*>::iterator it = h.end();  //to put the sample in the last position (before BM)
      h.insert (it-1,histo2);
      }
      else if(thesam2!="" && !found) cout << "sam2 not found" << endl;

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
      histo->SetLineWidth(1); //2
      histo->GetXaxis()->SetTitle(xaxis);
      histo->GetYaxis()->SetTitle(yaxis);
      h.push_back(histo);    

      cout << " Cluster:" << nc+1 << ", size:" << size << endl << endl;
      stringstream sst, sc;
      sc << "N_{clus} = "<< nTotClus; // << " - Cl" << (nc+1) ;
      TString clusterLabel = sc.str();
      sst << nc+1;   
  
      if(hName=="hcths")ymin = 1000; //debug
      else ymin = 0;

      if(h.size()>0){
        draw_all(p, h, xaxis,xmin,xmax,ymin,ymax,
  	   clusterLabel,lgRIGHT,lgTOP, logX, logY, stat, scale,rebin,orbin,option);
      }  
      else cout << "WARNING: empty cluster!" << endl;
      match = true;
      break;
    }
  }
  if(match) return true;
  else return false;
}
 
//plot call for different variables:
bool plot_pt(string thesam, string thesam2, TPad* p, int ncluster = 99, int rebin = 1, TString opt="") {
  if(!performancePlot1D(thesam,thesam2, p, ncluster-1,"pt",0.,250.,0.,800.,"pT [GeV/c]","", false, false, false,-9.,rebin,100,opt)) return false;
  return true;
}

bool plot_pzh(string thesam,string thesam2, TPad* p, int ncluster = 99, int rebin = 4, TString opt="") {
  if(!performancePlot1D(thesam,thesam2, p, ncluster-1,"pzh",0.,1000.,0.,800.,"max|p^{h}_{z} | [GeV/c]","", false, false, false,-9.,rebin,500,opt)) return false;
  return true;
}

bool plot_pzl(string thesam, string thesam2,TPad* p, int ncluster = 99, int rebin = 4, TString opt="") {
  if(!performancePlot1D(thesam,thesam2, p, ncluster-1,"pzl",-300.,500.,0.,800.,"higgs p_{z lower} [GeV]","", false, false, false,-9.,rebin,500,opt)) return false;
  return true;
}

bool plot_mhh(string thesam, string thesam2,TPad* p, int ncluster = 99, int rebin = 2, TString opt="") {
  if(!performancePlot1D(thesam,thesam2, p, ncluster-1,"mhh",240.,700.,0.,800.,"mhh [GeV/c^{2}]","", false, false, false,-9.,rebin,200,opt)) return false;
  return true;
}

bool plot_hth(string thesam, string thesam2, TPad* p, int ncluster = 99, int rebin = 2, TString opt="") {
  if(!performancePlot1D(thesam,thesam2, p, ncluster-1,"hth",0.,3.2,0.,800.,"higgs #theta","", false, false, false,-9.,rebin,200,opt)) return false;
  return true;
}

bool plot_hcth(string thesam,string thesam2, TPad* p, int ncluster = 99, int rebin = 2, TString opt="") {
  if(!performancePlot1D(thesam,thesam2, p, ncluster-1,"hcth",-1.,1.,0.,800.,"higgs cos#theta","", false, false, false,-9.,rebin,200,opt)) return false;
  return true;
}

bool plot_hths(string thesam, string thesam2, TPad* p, int ncluster = 99, int rebin = 2, TString opt="") {
  if(!performancePlot1D(thesam,thesam2, p, ncluster-1,"hths",0.,3.2,0.,800.,"higgs #theta*","", false, false, false,-9.,rebin,200,opt)) return false;
  return true;
}

bool plot_hcths(string thesam, string thesam2, TPad* p, int ncluster = 99, int rebin = 2, TString opt="") {
  if(!performancePlot1D(thesam,thesam2, p, ncluster-1,"hcths",0.,1.,1000.,3000.,"|cos#theta* |","", false, false, false,-9.,rebin,100,opt)) return false;
  return true;
}

TPad* setcanvas(string thesam,  int v){
  //debug
  string var = "";
  if(v==1) var = "pT^{h}";
  else if(v==2) var = "max#cbar pz^{h}#cbar";
  else if(v==3) var = "higgs pz lower";
  else if(v==4) var = "di-Higgs mass";
  else if(v==7) var = "higgs theta*";
  else if(v==8) var = "#cbar cos#theta*CS#cbar";

  stringstream title;  
  title << thesam << "_" << var;
  TCanvas* can = new TCanvas((TString)title.str(),(TString)title.str(),1125,700);
  can->cd();
  TPad* pad1 = new TPad("pad1","title",0.,1.,1.,0.95);
  pad1->Draw();
  TPad* pad2 = new TPad("pad2","histos",0.,1.,0.95,0.);
  pad2->Draw();
  //cout << title.str() << endl;
  pad1->cd();  
  stringstream header;
  if(Privat) header << "Private simulation 2015, #sqrt{s}=" << CMenergy << " TeV, " << Totsamples << " samples, " << translate(thesam) << ", " << var;
  else     header << "Simulation 2015, #sqrt{s}=" << CMenergy << " TeV, " << Totsamples << " samples, " << translate(thesam) << ", " << var;
  TLatex* text=new TLatex(0.03, 0.1, header.str().c_str());
  text->SetTextSize(0.4);
  text->Draw(); 

  return pad2;
}

/*std::string matchSamplename(int sam){

  string thesam = "";  
  ifstream infile;
  infile.open(mapFile.c_str());
  if(!infile)	{      //check if file exists
    printf( "ERROR: no map file %s \n", mapFile.c_str());
    return thesam;
  }
  int Nsam = 0;
  while(!infile.eof()){
    infile >> Nsam >> thesam;
    if(Nsam == sam) break;
  }
  cout << "selected sample: " << thesam << endl;
  return thesam;
}*/

//genaral function to plot all or single variable, single cluster.
void plot(int var, int sample1, int sample2 = 9999, int reb = 99, TString opt="hist") { 
// allonly: to plot all in one canvas; var: 1-pt, 2-pzh, 3-pzl, 4-mhh ;  nclu = 0 to do all the clusters

  //debug
  std::string thesam2 = "", thesample = "";
  //thesample = matchSamplename(sample1);
  //if(thesample == "") return;
  //if(sample2 != 9999) thesam2 = matchSamplename(sample2);
  if(sample1 > stoi(Totsamples)) {
    cout << "sample out of range" << endl; 
    return;
  }
  thesample = std::to_string(sample1);
  if(sample2 != 9999)  thesam2 = std::to_string(sample2);
  cout << thesample << "  " << thesam2 << endl;
 
  string app;
  std::stringstream outname;
  outname << pars << "par_" << CMenergy << "Tev" << testoption;
  int cols, rows; //debug
  int siz = sizeof(totClus)/4;
  if(siz<3)      {cols = 2; rows = 1;}
  else if(siz<5) {cols = 2; rows = 2;}
  else if(siz<7) {cols = 2; rows = 3;}
  else if(siz<9) {cols = 2; rows = 4;}
  else if(siz<13){cols = 3; rows = 4;}
  else if(siz<17){cols = 4; rows = 4;}
  else if(siz<21){cols = 5; rows = 4;}
  else { 
    cout << "ERROR: too many values for totClus" << endl;
    return;
  }

  //default rebin
  int reb1 = (reb == 99) ? 2 : reb;
  int reb2 = (reb == 99) ? 4 : reb;
  int reb3 = (reb == 99) ? 4 : reb;
  int reb4 = (reb == 99) ? 4 : reb;
  //  int reb5 = (reb == 99) ? 2 : reb;
  //  int reb6 = (reb == 99) ? 2 : reb;
  int reb7 = (reb == 99) ? 2 : reb;
  int reb8 = (reb == 99) ? 10 : reb;

  for(int v=1; v<5; v++){   //to be fixed!! - mad ordering..
    if(var != 0) v = var;
    //debug
    string variab = "";
    if(v==1) variab = "pt";
    else if(v==2) variab = "pzh";
    else if(v==3) variab = "pzl";
    else if(v==4) variab = "mhh";
    else if(v==7) variab = "thst";
    else if(v==8) variab = "cthst";

    TPad* pad2 = (TPad*)setcanvas(thesample,v);
    //pad2->Divide(5,1,0.0001,0.000000001); for the paper (one row only)
    pad2->Divide(cols,rows);

    for(int i=1; i<siz+1; i++) {
      nTotClus = totClus[i-1];
cout << nTotClus << endl;
      if(!init()) return;  //check
      int size = clu.size()-1;

      if(v == 1) {
        for(int nc=1; nc<=(size); nc++) {
           TPad* pad= (TPad*)pad2->GetPad(i);        
           if(plot_pt(thesample, thesam2, pad, nc, reb1, opt)) break;
        }
      }
      else if(v == 2) {
        for(int nc=1; nc<=(size); nc++) {
           TPad* pad= (TPad*)pad2->GetPad(i);           
          if(plot_pzh(thesample, thesam2,pad, nc, reb2, opt)) break;
        }
      }
      else if(v == 3) {
        for(int nc=1; nc<=(size); nc++) {
           TPad* pad= (TPad*)pad2->GetPad(i);           
           if(plot_pzl(thesample, thesam2,pad, nc, reb3, opt)) break;
        } 
      }
      else if(v == 4) {
        for(int nc=1; nc<=(size); nc++) {
           TPad* pad= (TPad*)pad2->GetPad(i);           
           if(plot_mhh(thesample, thesam2,pad, nc, reb4, opt)) break;
        }
      }
      else if(v == 5) {
      }
      else if(v == 6) {
      }
      else if(v == 7) {
        for(int nc=1; nc<=(size); nc++) {
           TPad* pad= (TPad*)pad2->GetPad(i);           
           if(plot_hths(thesample,thesam2, pad, nc, reb7, opt)) break;
        }
      }
      else if(v == 8) {
        for(int nc=1; nc<=(size); nc++) {
           TPad* pad= (TPad*)pad2->GetPad(i);           
           if(plot_hcths(thesample,thesam2, pad, nc, reb8, opt)) break;
        }
      }
      else cout << "wrong var value (0-8)" << endl; //debug!!

      clu.clear(); //needed!
    }//end for tot sample 
    pad2->GetCanvas()->SaveAs(Outfolder+outname.str()+"_"+variab+"_"+thesample+".png");   
    pad2->GetCanvas()->SaveAs(Outfolder+outname.str()+"_"+variab+"_"+thesample+".pdf");   
    if(var!=0) break;
  }//end var
}

