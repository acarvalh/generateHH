// This version of the code (which compares the kinematics of benchmark points for hhbbbb analysis)
// deals with a 2d poisson likelihood based on mass and costhetastar
//
// To compile: g++ -g `root-config --libs --cflags` FCL2D_X.cpp -o FCL2D_X

#include <iostream>
#include <fstream>
#include <sstream>
#include <cmath>
#include <algorithm>
#include <vector>
#include <string>
#include <sys/time.h>
#include "TRandom.h"
#include "TH1D.h"
#include "TH2D.h"
#include "TFile.h"

using namespace std;

const int Nmax=20000;

// plots to do
struct event {double px1, py1, pz1; double px2, py2, pz2; double mass, costh;};
		
double Factorial(unsigned int n) {return(n<=1 ? 1. : n*Factorial(n-1));}
double logFactorial(unsigned int n) {return(n<=1 ? 0. : log(n)+logFactorial(n-1));}

std::string TimeStamp() {
  char buffer[13];
  time_t t;			//declare time_t variable
  time(&t);			//get current time
  tm r = * localtime(&t);	//returns time into a calendar format
  strftime(buffer, sizeof(buffer), "%X", localtime_r(&t, &r));	//chooses the right format
  char result[1000] = {0};
  std::sprintf(result, "%s", buffer);
  return result;
}

const int ns =1593;// 1478;// 1176;//636;// 847+636;		//number of files
int nev = 20000; 	//number of events 
int nclu=10;
int gen=5;              // gen=1 is first set of lhe files, gen=2 is second set, gen=3 is both together 
                        // gen=4 is 13 TeV data
                        // gen=5 is new 13 TeV grid
int S1min=0;
int S1max=ns-1;
int Nvarbinmass=50;
int Nvarbincosth=5.;

//string outputPath =     //"/lustre/cmswork/dallosso/hh2bbbb/non-resonant/clusterAnalysis/";
//  "/afs/cern.ch/work/d/dorigo/hhbbbb/13TeV";
string outputPath = "output";
//string inputPath1 = "/Users/Xanda/Documents/codes/clustering/ascii_lhe/SCENARIO2/";

bool update = false;
		
///////////////////////////////////
int main(int argc, char *argv[]) {

  TH1D * Mass[ns];
  TH1D * Costh[ns];
  double minMass=200.;
  double maxMass=1600.;
  double minCosth=0.;
  double maxCosth=1.;
  char namehist[40];
  for (int i=0; i<ns; i++) {
    sprintf(namehist,"Mass_%d", i);
    Mass[i] = new TH1D(namehist, namehist, 200, minMass, maxMass);
    sprintf(namehist,"Costh_%d", i);
    Costh[i] = new TH1D(namehist, namehist, 200, minCosth, maxCosth);
  } // close declare histos

  bool readfile = false;

  typedef event bench[Nmax];
  bench *ev = new bench[ns]; 

  // command line arguments 
  //-----------------------------
  string nsamples(""), TTtimes("");

  for (int i = 0; i < argc; i++){
    if (!strcmp(argv[i],"-h")) {
      cout << "List of arguments:" << endl;
      cout << "-nev number of events" << endl;
      cout << "-smin initial sample" << endl;
      cout << "-smax final sample" << endl;
      cout << "-nbinmass number of bins per variable mass (in 0:1500)" << endl;
      cout << "-nbincosth number of bins per variable costh" << endl;
      // cout << "-gen set 1 or set 2 of LHE files, or both (3), or 13 TeV " << endl;
      cout << "-u   update existing root file" << endl;
      return 0;
    }
    else if (!strcmp(argv[i],"-nev")) {nev = atoi(argv[++i]);}
    else if (!strcmp(argv[i],"-smin")) {S1min=atoi(argv[++i]);}
    else if (!strcmp(argv[i],"-smax")) {S1max=atoi(argv[++i]);}
    else if (!strcmp(argv[i],"-nbinmass")) {Nvarbinmass=atoi(argv[++i]);}
    else if (!strcmp(argv[i],"-nbincosth")) {Nvarbincosth=atoi(argv[++i]);}
    // else if (!strcmp(argv[i],"-gen")) {gen=atoi(argv[++i]);}
    else if (!strcmp(argv[i],"-u"))   {update = true;} //
    
  }  
  gen=5;
  int knev = nev/1000;
  std::stringstream sstr;
  sstr << "/rootfiles/LogP_ev" << knev << "k_"<< Nvarbinmass << "x" << Nvarbincosth << ".root";
  string outfile = outputPath + sstr.str();
  // Reading ASCII, one file a time
  // ------------------------------
  string filelist="list_all.txt";
  ifstream in1; in1.open(filelist.c_str());
  string name; 
  string namecom;
  cout<< " test "<<filelist<<endl;
  //string cgen; in1>>cgen;
  ifstream infile;
  int nf = 0;
  for(int f=0; f<ns; ++f) {//
    // read filelist
    in1 >> name ;
    //namecom = "/Users/Xanda/Documents/codes/clustering/ascii_lhe/"+name;
    namecom = name;
    cout << "Reading file # "<< f<<" " << namecom << endl;
    infile.open(namecom.c_str());
    double dummy1, dummy2,dummy3, dummy4,dummy5;
    for (int k=0; k<Nmax; ++k) {  // loop on number of events - debug (max fixed?..)
      //infile >> ev[f][k].px1 >> ev[f][k].py1 >> ev[f][k].pz1;
      //cout <<ev[f][k].px1 <<" "<< ev[f][k].py1  <<" "<< ev[f][k].pz1<<endl;
      //if (gen==2 || (gen==3 && f>53) || gen>=4) infile >> dummy1 >> dummy2;
      //infile >> dummy1 >> dummy2;
      //infile >> ev[f][k].px2 >> ev[f][k].py2 >> ev[f][k].pz2;
      //if (gen==2 || (gen==3 && f>53) || gen>=4) infile >> dummy1 >> dummy2;
      infile >> ev[f][k].px1 >> ev[f][k].py1 >> ev[f][k].pz1 >> dummy4 >> dummy5;
        //cout<<dummy1<<endl;
      if (fabs(ev[f][k].px1)>10000 || fabs(ev[f][k].py1)>10000 || fabs(ev[f][k].pz1)>10000) cout << "**********************************" << endl;
      if (fabs(ev[f][k].px2)>10000 || fabs(ev[f][k].py2)>10000 || fabs(ev[f][k].pz2)>10000) cout << "**********************************" << endl;
    }
    //fnumber.clear();	//clear eventual error flags
    //fnumber.str("");	//resetting fnumber
    infile.close();    

    // Some preprocessing:
    // 1 - order by pt -> pthi, ptlo
    // 2 - compute dphi
    // 3 - flip sign of pzhi, pzlo if pzhi is negative
    // -----------------------------------------------
    for (int k=0; k<Nmax; k++) {
      double pt1 = sqrt(ev[f][k].px1*ev[f][k].px1+ev[f][k].py1*ev[f][k].py1);
      double pt2 = sqrt(ev[f][k].px2*ev[f][k].px2+ev[f][k].py2*ev[f][k].py2);
      double spx = ev[f][k].px1+ev[f][k].px2;
      double spy = ev[f][k].py1+ev[f][k].py2;
      double spz = ev[f][k].pz1+ev[f][k].pz2;
      double e1 = sqrt(ev[f][k].px1*ev[f][k].px1+ev[f][k].py1*ev[f][k].py1+ev[f][k].pz1*ev[f][k].pz1+125.*125.);
      double e2 = sqrt(ev[f][k].px2*ev[f][k].px2+ev[f][k].py2*ev[f][k].py2+ev[f][k].pz2*ev[f][k].pz2+125.*125.);
      double sen = e1+e2;
      ev[f][k].mass = sqrt(sen*sen-spx*spx-spy*spy-spz*spz);
      Mass[f]->Fill(ev[f][k].mass);
      double pcm = spz;
      double ecm = sqrt(ev[f][k].mass*ev[f][k].mass+pcm*pcm);
      double beta = pcm/ecm;
      double gamma = 1/sqrt(1-beta*beta);
      double pzstar1 = ev[f][k].pz1*gamma-gamma*beta*e1;
      double costh = pzstar1/sqrt(pt1*pt1+pzstar1*pzstar1);
      ev[f][k].costh=fabs(costh); // NNBB left-right symmetry implied
      Costh[f]->Fill(ev[f][k].costh);
    }
    nf++;
  }
    in1.close();
  cout << " " << nf << " files read" << endl;

//   DEBUG - READING PROOF
  cout << "Printing files" << endl;
  for (int f=0; f<ns; ++f){
    for (int k=19999; k<20000; ++k) {
      cout << ev[f][k].px1 << "\t" << ev[f][k].py1 << "\t" << ev[f][k].pz1 << endl;
      cout << ev[f][k].px2 << "\t" << ev[f][k].py2 << "\t" << ev[f][k].pz2 << endl;
      // cout << ev[f][k].pt << "\t" << ev[f][k].pzh << "\t" << ev[f][k].pzl << endl;
    }
  }
  cout << "END" << endl;  
      
  TH1D Ptotal[ns];
  for (int i=0; i<ns; i++) {
    char htitle2[20];
    sprintf (htitle2,"Pvalues_all_%i",i);
    Ptotal[i].SetName(htitle2);
    Ptotal[i].SetTitle(htitle2);
    Ptotal[i].SetBins(100,0.,1.);
  }
  TH1D totP;
  totP.SetName("totP");
  totP.SetTitle("totP");
  totP.SetBins(101,-0.005,1.005);
  TH2D Clu;
  Clu.SetName("Clu");
  Clu.SetTitle("Clu");
  Clu.SetBins(ns,0.,(float)ns,ns,0.,(float)ns);
  TH1D DThis;
  DThis.SetName("DThis");
  DThis.SetTitle("DThis");
  DThis.SetBins(100,0.,500000.);
  TH1D DThis12;
  DThis12.SetName("DThis12");
  DThis12.SetTitle("DThis12");
  DThis12.SetBins(100,0.,500000.);


  double largenumber=10000000;
  double * pvall = new double [ns*ns];
  double ** pvalue = new double*[ns];
  for (int i=0; i<ns;i++) {
    pvalue[i]=pvall+i*ns;
  }
  // double pvalue[ns][ns]; // will not fill diagonal elements
  for (int i=0; i<ns; i++) {
    for (int j=0; j<ns; j++) {
      pvalue[i][j]=largenumber;
    }
  }

  char namepvaluefile[100];
  sprintf(namepvaluefile,"./LogP/LogP_%dk_%d_%d.asc",knev,Nvarbinmass,Nvarbincosth);
  ofstream pvaluefile(namepvaluefile);
  
  // START COMPUTATION
  // -----------------
  cout << " Starting with " << ns << " samples, " << nev << " events " << endl;
  cout << endl << " Begin p-values computation" << endl;
  
  const int Nvbmass=Nvarbinmass;
  const int Nvbcosth=Nvarbincosth;
  const int Ntotbin=Nvbmass*Nvbcosth;
  int Matrix1[Ntotbin];
  int Matrix2[Ntotbin];
  // distance calculation between each element of a benchmark pair
  for (int S1=S1min; S1<S1max; S1++) {
    cout << "Doing sample " << S1 << endl;

    double massintegral=0;
    double costhintegral=0;
    double massbinhig[Nvbmass];
    double costhbinhig[Nvbcosth];
    massbinhig[Nvbmass-1]=maxMass;
    costhbinhig[Nvbcosth-1]=maxCosth;
    int imassbin=0;
    int icosthbin=0;
    for (int i=0; i<200; i++) {
      // I want to do Nvb bins in mass, uniformly populated,
      // so I sum bins until I get nev/Nvb intervals
      massintegral+=Mass[S1]->GetBinContent(i);
      if (massintegral>=(double)(nev*(imassbin+1))/(double)Nvbmass) {
	massbinhig[imassbin]=minMass+(double)(i+1)*(maxMass-minMass)/200.;
	imassbin++;
      }
      costhintegral+=Costh[S1]->GetBinContent(i);
      if (costhintegral>=(double)(nev*(icosthbin+1))/(double)Nvbcosth) {
	costhbinhig[icosthbin]=minCosth+(double)(i+1)*(maxCosth-minCosth)/200.;
	icosthbin++;
      }
    }

    for (int i=0; i<Ntotbin; i++) { Matrix1[i]=0; }
    for (int i=0; i<nev; i++) {
      int imass=-1;
      int icosth=-1;
      for (int ibin=0; ibin<Nvbmass; ibin++) {
	if (ev[S1][i].mass<massbinhig[ibin] && imass<0) imass=ibin; 
      }
      for (int ibin=0; ibin<Nvbcosth; ibin++) {
	if (ev[S1][i].costh<costhbinhig[ibin] && icosth<0) icosth=ibin;
      }
      if (imass==-1) imass=Nvbmass-1;
      if (icosth==-1) icosth=Nvbcosth-1;
      Matrix1[imass*Nvbcosth+icosth]++;
    }
    for (int S2=S1+1; S2<ns; S2++) { // ns; S2++) {       
      if (S2/100==0.01*S2) cout << "Testing against sample " << S2 <<endl;
      for (int i=0; i<Ntotbin; i++) { Matrix2[i]=0; }
      for (int i=0; i<nev; i++) {
	int imass=-1;
	int icosth=-1;
	for (int ibin=0; ibin<Nvbmass; ibin++) {
	  if (ev[S2][i].mass<massbinhig[ibin] && imass<0) imass=ibin; 
	}
	for (int ibin=0; ibin<Nvbcosth; ibin++) {
	  if (ev[S2][i].costh<costhbinhig[ibin] && icosth<0) icosth=ibin;
	}
	if (imass==-1) imass=Nvbmass-1;
	if (icosth==-1) icosth=Nvbcosth-1;
	Matrix2[imass*Nvbcosth+icosth]++;
      }
      // Calculate likelihood of partition using poisson approximation
      // P(bin) = exp(-n1-n2)*[(n1+n2)/2]^(n1+n2)/(n1!n2!)
      // Ptot = Prod(P(bin))
      // -------------------------------------------------------------
      double lnptot=0;
      double maxn=0;
      for (int i=0; i<Ntotbin; i++) {
	double n1=Matrix1[i];
	double n2=Matrix2[i];
	double logfacn1=logFactorial(n1);
	double logfacn2=logFactorial(n2);
	double logfacn1n2=logFactorial(n1+n2);
	double pmulti = (n1+n2)/(2*nev);
	if (n1+n2>0) {
	  // Poissonian:
	  // lnptot +=(n1+n2)*log((n1+n2)/2.)-logfacn1-logfacn2;
	  // Multinomial logp (apart from 2log nev! factor)
	  // lnptot += (n1+n2)*log(pmulti)-logfacn1-logfacn2;
	  // Binomial logp (correctly factors out ancillary statistics n1+n2)
	  lnptot += logfacn1n2 - logfacn1 - logfacn2 + (n1+n2)*log(0.5);
	}
      }
      totP.Fill(lnptot);
      pvalue[S1][S2]=lnptot;
      pvalue[S2][S1]=lnptot;
      pvalue[S1][S1]=1.;
      pvalue[S2][S2]=1.; 
      //cout << "[" << TimeStamp() << "] ";
      // printf("p-value %i-%i = %.4f \n", S1, S2, pvalue[S1][S2] );
      Ptotal[S1].Fill(pvalue[S1][S2]);
      Ptotal[S2].Fill(pvalue[S1][S2]);
      //P12.Fill(0.5+S1,0.5+S2,pvalue[S1][S2]);
      //P12.Fill(0.5+S2,0.5+S1,pvalue[S1][S2]);
      
      // Write data on file
      //cout << "about to write" <<endl;
      pvaluefile << S1 << " " << S2 << " " << pvalue[S1][S2] << endl;
      //cout << "written" << endl;
      
    } //end S2 
  } // end S1
  
  //delete all the data
  delete ev;  //needed?
  
  // END OF COMPUTATION
  //-----------------------------
  pvaluefile.close();

  //-----------------------------------
  // start re-ordering and selection
  //-----------------------------------
    
  if (S1min==0 && S1max==ns-1) {
    cout << endl;
    cout << " Cluster analysis" << endl;
    cout << " ----------------" << endl;
    cout << endl;
    
    // Start by defining a matrix of clusters and samples belonging to it
    double highvalue=10000000.;
    int Clus[ns][ns];
    int NinClus[ns];
    int head[ns];
    int done[ns];
    // start of loop
    for (int Nwanted=20; Nwanted>1; Nwanted--) { // we explore 6 possible results
      for (int i=0; i<ns; i++) {
	Clus[i][0]=i;
	head[i]=-1;
	done[i]=-1;
	for (int j=1; j<ns; j++) {
	  Clus[i][j]=-1;
	}
	NinClus[i]=1;
      }
      int Nclus_nonempty=ns;
      int iclumaxemin=-1;
      while (Nclus_nonempty>Nwanted) { // we continue to group together until we meet the requirement of Nwanted
	double max_emin_all=-highvalue; // we want to find the maximum of the minimum e within a prospective cluster
	// We first look for singletons to associate to clusters
	int jmax;
	int iclumaxemin_max=-1;
	for (int j=0; j<ns; j++) { // loop on samples
	  if (done[j]==-1 && NinClus[j]<2) { // this sample is not assigned yet (nb at the start all are "clusters of 1" 
	    // but not assigned yet)
	    //cout << j << " ";
	    double max_emin=-highvalue; 
	    double emin;
	    for (int i=0; i<ns; i++) { // Loop on clusters and find dmin for each element to one cluster
	      if (NinClus[i]>0 && Clus[i][0]!=j) {
		emin = highvalue;
		for (int k=0; k<NinClus[i]; k++) {
		  if (emin>pvalue[j][Clus[i][k]]) {
		    emin=pvalue[j][Clus[i][k]];
		  }
		  //cout << "j,Clus[i][k]=" << j << "," << Clus[i][k] << " emin=" << emin << 
		  // " pvalue = " << pvalue[j][Clus[i][k]] << endl;
		} // now we know what is the worst agreement between j and elements in cluster i, emin
		if (emin>max_emin) {
		  max_emin=emin; 
		  iclumaxemin=i; // we note the cluster which would be best to aggregate j with
		}
	      }
	    } // end loop on clusters
	    // now we know to which cluster (iclumaxemin) to associate sample j
	    if (max_emin>max_emin_all) {
	      max_emin_all=max_emin;
	      jmax=j;
	      iclumaxemin_max=iclumaxemin; 
	    }
	  }
	}
	//cout << "After sample/cluster matchin we have jmax=" << jmax << " and max_emin_all=" << max_emin_all << endl;
	
	// Now we give a look at whether two clusters can be merged instead
	// ----------------------------------------------------------------
	//cout << "prima di cluclu" << jmax << " " << max_emin_all << endl;
	for (int j=0; j<ns; j++) {
	  if (NinClus[j]>1) {
	    double max_emin=-highvalue; 
	    double emin;
	    for (int k=0; k<ns; k++) { // Loop on clusters and find dmin for each element to one cluster
	      if (NinClus[k]>1 && k!=j) {
		emin = highvalue;
		for (int j2=0; j2<NinClus[j]; j2++) {
		  for (int k2=0; k2<NinClus[k]; k2++) {
		    if (emin>pvalue[Clus[j][j2]][Clus[k][k2]]) {
		      emin=pvalue[Clus[j][j2]][Clus[k][k2]];
		    }
		    //cout << "j2,k2=" << Clus[j][j2] << "," << Clus[k][k2] << " emin=" 
		    //     << emin << " pvalue = " << pvalue[Clus[j][j2]][Clus[k][k2]] << endl;
		  }
		} // now we know what is the worst agreement between elements in cluster j and elements in cluster k, emin
		if (emin>max_emin) {
		  max_emin=emin; 
		  iclumaxemin=k; // we note the cluster which would be best to aggregate j with
		}
	      }
	    } // end loop on clusters
	    // now we know to which cluster (iclumaxemin) to associate cluster j
	    if (max_emin>max_emin_all) {
	      max_emin_all=max_emin;
	      jmax=j;
	      iclumaxemin_max=iclumaxemin; 
	    }
	  }
	}
	//cout << "After clu/clu matchin we have jmax=" << jmax << " and max_emin_all=" << max_emin_all << endl;
	// ok we have chosen the best association. The sample or cluster jmax is the one to associate,
	// and the cluster to be associated with is iclumaxemin_max.
	// -------------------------------------------------------------------------------------------
	if (NinClus[jmax]==1) { // sample-cluster
	  Clus[iclumaxemin_max][NinClus[iclumaxemin_max]]=jmax; // add element to matrix
	  NinClus[iclumaxemin_max]++;
	  done[jmax]=iclumaxemin_max;
	  NinClus[jmax]=0; // this is no longer a cluster, but an element of another one
	  cout << "We associate sample " << jmax << " to cluster " << iclumaxemin_max 
	       << " which has now " << NinClus[iclumaxemin_max] << " members: ";
	  for (int k=0; k<NinClus[iclumaxemin_max]; k++) { cout << Clus[iclumaxemin_max][k] << " "; }; cout << endl;
	} else if (NinClus[jmax]>1) { // more complex, we are merging two clusters
	  for (int k=0; k<NinClus[jmax]; k++) {
	    Clus[iclumaxemin_max][NinClus[iclumaxemin_max]+k]=Clus[jmax][k];
	  }
	  NinClus[iclumaxemin_max]+=NinClus[jmax];
	  NinClus[jmax]=0;
	  done[jmax]=iclumaxemin_max;
	  cout << "We associate cluster " << jmax << " to cluster " << iclumaxemin_max 
	       << " which has now " << NinClus[iclumaxemin_max] << " members: ";
	  for (int k=0; k<NinClus[iclumaxemin_max]; k++) { cout << Clus[iclumaxemin_max][k] << " "; }; cout << endl;
	} 
	// recompute number of clusters still non empty
	Nclus_nonempty=0;
	for (int k=0; k<ns; k++) {
	  if (NinClus[k]>0) Nclus_nonempty++;
	}
	//      cout << Nclus_nonempty << endl;
      } // end while still too many clusters around
      
      // Determine who's the benchmark in each cluster
      // ---------------------------------------------
      double emin_this=highvalue;
      for (int j=0; j<ns; j++) {
	if (NinClus[j]>0) {
	  double emin_max=-highvalue;
	  for (int i=0; i<NinClus[j]; i++) {
	    emin_this=highvalue;
	    for (int k=0; k<NinClus[j]; k++) {
	      if (k!=i) {
		if (emin_this>pvalue[Clus[j][i]][Clus[j][k]]) emin_this=pvalue[Clus[j][i]][Clus[j][k]];
	      }
	    }
	    if (emin_this>emin_max) {
	      emin_max=emin_this;
	      head[j]=Clus[j][i];
	    }
	  }
	}
      }
      
      // Dump clustering for this Nwanted
      // --------------------------------
      int i_nonempty=0;
      cout << endl;
      cout << "For Nwanted = " << Nwanted << ": " << endl;
      for (int j=0; j<ns; j++) {
	if (NinClus[j]>0) {
	  cout << "  Cluster # " << i_nonempty << " - head = " << head[j] << "; members =";
	  i_nonempty++;
	  for (int k=0; k<NinClus[j]; k++) {
	    if (Clus[j][k]!=head[j]) cout << " " << Clus[j][k];
	  }
	  cout << endl;
	} 
      }
      
      char nameclu[100];
      sprintf(nameclu,"./LogP/clustering_nev%dk_Nclu%d_%d_%d.asc",knev,Nwanted,Nvarbinmass,Nvarbincosth);
      ofstream clufile (nameclu);
      char namebenchmark[100];
      sprintf(namebenchmark,"./LogP/clustering_benchmarks_%dk_Nclu%d_%d_%d.asc",knev,Nwanted,Nvarbinmass,Nvarbincosth);
      ofstream benchmarkfile (namebenchmark);
      i_nonempty=0;
      char namemacro[100];
      sprintf (namemacro,"./rootfiles/LogP/Plot_clusters_%dk_Nclu%d_%d_%d.C",knev,Nwanted,Nvarbinmass,Nvarbincosth);
      char namemacroshort[100];
      sprintf (namemacroshort,"Plot_clusters_%dk_Nclu%d_%d_%d",knev,Nwanted,Nvarbinmass,Nvarbincosth);
      ofstream macrofile (namemacro);
      macrofile << "void " << namemacroshort<< "() {" << endl;
      macrofile << "  TCanvas * C = new TCanvas (\"C\", \"\", 600,600);" << endl;
      int xd,yd;
      if (Nwanted<=6) {
	xd=2;
	yd=3;
      } else {
	yd=Nwanted/4+1;
	xd=4;
      }
      macrofile << "  C->Divide(" << xd << "," << yd << ");" << endl;
      for (int j=0; j<ns; j++) {
	if (NinClus[j]>0) {
	  i_nonempty++;
	  clufile << head[j];
	  benchmarkfile << head[j] << endl;
	  macrofile << "  C->cd(" << i_nonempty << ");" <<endl;
	  for (int k=0; k<NinClus[j]; k++) {
	    if (Clus[j][k]!=head[j]) {
	      clufile << " " << Clus[j][k];
	      Clu.Fill(head[j]+0.5,Clus[j][k]+0.5); // fill also head/head
	    } else {
	      Clu.Fill(head[j]+0.5,Clus[j][k]+0.5); // fill also head/head
	      macrofile << "  Mass_" << Clus[j][k] << "->SetLineColor(kRed);" << endl;
	      // Fill macro to graph pt distributions
	    }
	    if (k==0) {
	      macrofile << "  Mass_" << Clus[j][k] << "->Draw();" << endl;
	    } else { 
	      macrofile << "  Mass_" << Clus[j][k] << "->Draw(\"SAME\");" << endl;
	    }
	  }
	  macrofile << "Mass_" << head[j] << "->Draw(\"SAME\");" << endl;
	  clufile << endl;
	} 
      }
      macrofile << "  TCanvas * C2 = new TCanvas (\"C2\", \"\", 600,600);" << endl;
      macrofile << "  C2->Divide(" << xd << "," << yd << ");" << endl;
      i_nonempty=0;
      for (int j=0; j<ns; j++) {
	if (NinClus[j]>0) {
	  i_nonempty++;
	  macrofile << "  C2->cd(" << i_nonempty << ");" <<endl;
	  for (int k=0; k<NinClus[j]; k++) {
	    if (Clus[j][k]==head[j]) {
	      macrofile << "  Costh_" << Clus[j][k] << "->SetLineColor(kRed);" << endl;
	    }
	    if (k==0) {
	      macrofile << "  Costh_" << Clus[j][k] << "->Draw();" << endl;
	    } else { 
	      macrofile << "  Costh_" << Clus[j][k] << "->Draw(\"SAME\");" << endl;
	    }
	  }
	  macrofile << "Costh_" << head[j] << "->Draw(\"SAME\");" << endl;
	  clufile << endl;
	} 
      }
      clufile.close(); 
      benchmarkfile.close();
      macrofile << "} " << endl;
      macrofile.close();
    } // end loop on nwanted
    
    
    // rebin histos
    //    for (int i=0; i<ns; i++) {
    //      Mass[i]->Rebin(5);
    //      Costh[i]->Rebin(5);
    //    }
    
    // for the selected benchmarks I plot all the pvalues
    //TH1D PHisto[final_dim];
    TFile *out(0);
    char nameroot[100];
    sprintf(nameroot,"./rootfiles/LogP_%dk_%d_%d.root",knev,Nvarbinmass,Nvarbincosth);
    if(!update)  { out = TFile::Open(nameroot, "RECREATE"); }  
    else           out = TFile::Open(nameroot, "UPDATE");   
    
    //   for (int i=0; i<final_dim; ++i) {
    //     char htitle[20];
    //     sprintf (htitle,"pvalues_%i",i);
    //     PHisto[i].SetName(htitle);
    //     PHisto[i].SetTitle(htitle);
    //     PHisto[i].SetBins(100, 0, 1.0);
    //     for(int j=0; j<(int)bb[i].pp.size(); ++j) {
    //       PHisto[i].Fill(bb[i].pp[j]);
    //     }
    //     PHisto[i].Write();   
    //   }
    //P12.Write();
    Clu.Write();
    DThis.Write();
    DThis12.Write();
    totP.Write();
    for (int i=0; i<ns; i++) {
      Ptotal[i].Write();
      Mass[i]->Write();
      Costh[i]->Write();
    }
    cout << endl;
    out->Close();

  } // if smin smax 0 635

  return 0;
}


