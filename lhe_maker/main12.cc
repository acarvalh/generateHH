/// main11.cc is a part of the PYTHIA process generator.
// Copyright (C) 2011 Torbjorn Sjostrand.
// PYTHIA is licenced under the GNU GPL version 2, see COPYING for details.
// Please respect the MCnet Guidelines, see GUIDELINES for details.

#include "Pythia8/Pythia.h"
//#include <fstream>
using namespace Pythia8;
int main() {
    
    Pythia pythia;
       string namefile[274] ={
           "L15.0kt1.5cT-0.5cg0c2g0.lhe",
           "L15.0kt1.5cT-2.0cg0c2g0.lhe",
           "L15.0kt1.5cT-3.0cg0c2g0.lhe",
           "L15.0kt1.5cT0.0cg0c2g0.lhe",
           "L15.0kt1.5cT0.5cg0c2g0.lhe",
           "L15.0kt1.5cT1.0cg0c2g0.lhe",
           "L15.0kt1.5cT2.0cg0c2g0.lhe",
           "L15.0kt1.5cT3.0cg0c2g0.lhe",
           "L15.0kt2.0cT-0.5cg0c2g0.lhe",
           "L15.0kt2.0cT-1.0cg0c2g0.lhe",
           "L15.0kt2.0cT-2.0cg0c2g0.lhe",
           "L15.0kt2.0cT-3.0cg0c2g0.lhe",
           "L15.0kt2.0cT0.0cg0c2g0.lhe",
           "L15.0kt2.0cT0.5cg0c2g0.lhe",
           "L15.0kt2.0cT1.0cg0c2g0.lhe",
           "L15.0kt2.0cT2.0cg0c2g0.lhe",
           "L15.0kt2.0cT3.0cg0c2g0.lhe",
           "L15.0kt2.5cT-0.5cg0c2g0.lhe",
           "L15.0kt2.5cT-1.0cg0c2g0.lhe",
           "L15.0kt2.5cT-2.0cg0c2g0.lhe",
           "L15.0kt2.5cT-3.0cg0c2g0.lhe",
           "L15.0kt2.5cT0.0cg0c2g0.lhe",
           "L15.0kt2.5cT0.5cg0c2g0.lhe",
           "L15.0kt2.5cT1.0cg0c2g0.lhe",
           "L15.0kt2.5cT2.0cg0c2g0.lhe",
           "L15.0kt2.5cT3.0cg0c2g0.lhe",
           "L15kt1.5cT-1cg0c2g0.lhe",
           "L1kt0.25cT-0.5cg0c2g0.lhe",
           "L1kt0.25cT0.5cg0c2g0.lhe",
           "L1kt0.25cT1.5cg0c2g0.lhe",
           "L1kt0.25cT1cg0c2g0.lhe",
           "L1kt0.25cT2cg0c2g0.lhe",
           "L1kt0.5cT2.5cg0c2g0.lhe",
           "L1kt0.75cT-0.5cg0c2g0.lhe",
           "L1kt0.75cT-1cg0c2g0.lhe",
           "L1kt0.75cT0.25cg0c2g0.lhe",
           "L1kt0.75cT0.5cg0c2g0.lhe",
           "L1kt0.75cT1cg0c2g0.lhe",
           "L1kt0.75cT2.5cg0c2g0.lhe",
           "L1kt0.75cT2cg0c2g0.lhe",
           "L1kt1.25cT2.5cg0c2g0.lhe",
           "L1kt1.5cT2.5cg0c2g0.lhe",
           "L1kt1.75cT2.5cg0c2g0.lhe",
           "L1kt1cT-0.5cg-0.2c2g-0.2.lhe",
           "L1kt1cT-0.5cg-0.2c2g0.2.lhe",
           "L1kt1cT-0.5cg-0.4c2g-0.4.lhe",
           "L1kt1cT-0.5cg-0.4c2g0.4.lhe",
           "L1kt1cT-0.5cg-0.6c2g-0.6.lhe",
           "L1kt1cT-0.5cg-0.6c2g0.6.lhe",
           "L1kt1cT-0.5cg-0.8c2g-0.8.lhe",
           "L1kt1cT-0.5cg-0.8c2g0.8.lhe",
           "L1kt1cT-0.5cg-1c2g-1.lhe",
           "L1kt1cT-0.5cg-1c2g1.lhe",
           "L1kt1cT-0.5cg0.2c2g-0.2.lhe",
           "L1kt1cT-0.5cg0.2c2g0.2.lhe",
           "L1kt1cT-0.5cg0.4c2g-0.4.lhe",
           "L1kt1cT-0.5cg0.4c2g0.4.lhe",
           "L1kt1cT-0.5cg0.6c2g-0.6.lhe",
           "L1kt1cT-0.5cg0.6c2g0.6.lhe",
           "L1kt1cT-0.5cg0.8c2g-0.8.lhe",
           "L1kt1cT-0.5cg0.8c2g0.8.lhe",
           "L1kt1cT-0.5cg0c2g-0.2.lhe",
           "L1kt1cT-0.5cg0c2g-0.4.lhe",
           "L1kt1cT-0.5cg0c2g-0.6.lhe",
           "L1kt1cT-0.5cg0c2g-0.8.lhe",
           "L1kt1cT-0.5cg0c2g-1.lhe",
           "L1kt1cT-0.5cg0c2g0.2.lhe",
           "L1kt1cT-0.5cg0c2g0.4.lhe",
           "L1kt1cT-0.5cg0c2g0.6.lhe",
           "L1kt1cT-0.5cg0c2g0.8.lhe",
           "L1kt1cT-0.5cg0c2g0.lhe",
           "L1kt1cT-0.5cg0c2g1.lhe",
           "L1kt1cT-0.5cg1c2g-1.lhe",
           "L1kt1cT-0.5cg1c2g1.lhe",
           "L1kt1cT-1.0cg1c2g1.lhe",
           "L1kt1cT-1.5cg-0.2c2g-0.2.lhe",
           "L1kt1cT-1.5cg-0.2c2g0.2.lhe",
           "L1kt1cT-1.5cg-0.4c2g-0.4.lhe",
           "L1kt1cT-1.5cg-0.4c2g0.4.lhe",
           "L1kt1cT-1.5cg-0.6c2g-0.6.lhe",
           "L1kt1cT-1.5cg-0.6c2g0.6.lhe",
           "L1kt1cT-1.5cg-0.8c2g-0.8.lhe",
           "L1kt1cT-1.5cg-0.8c2g0.8.lhe",
           "L1kt1cT-1.5cg-1c2g-1.lhe",
           "L1kt1cT-1.5cg-1c2g1.lhe",
           "L1kt1cT-1.5cg0.2c2g-0.2.lhe",
           "L1kt1cT-1.5cg0.2c2g0.2.lhe",
           "L1kt1cT-1.5cg0.4c2g-0.4.lhe",
           "L1kt1cT-1.5cg0.4c2g0.4.lhe",
           "L1kt1cT-1.5cg0.6c2g-0.6.lhe",
           "L1kt1cT-1.5cg0.6c2g0.6.lhe",
           "L1kt1cT-1.5cg0.8c2g-0.8.lhe",
           "L1kt1cT-1.5cg0.8c2g0.8.lhe",
           "L1kt1cT-1.5cg0c2g-0.2.lhe",
           "L1kt1cT-1.5cg0c2g-0.4.lhe",
           "L1kt1cT-1.5cg0c2g-0.6.lhe",
           "L1kt1cT-1.5cg0c2g-0.8.lhe",
           "L1kt1cT-1.5cg0c2g-1.lhe",
           "L1kt1cT-1.5cg0c2g0.2.lhe",
           "L1kt1cT-1.5cg0c2g0.4.lhe",
           "L1kt1cT-1.5cg0c2g0.6.lhe",
           "L1kt1cT-1.5cg0c2g0.8.lhe",
           "L1kt1cT-1.5cg0c2g0.lhe",
           "L1kt1cT-1.5cg0c2g1.lhe",
           "L1kt1cT-1.5cg1c2g-1.lhe",
           "L1kt1cT-1.5cg1c2g1.lhe",
           "L1kt1cT-1cg-0.2c2g-0.2.lhe",
           "L1kt1cT-1cg-0.2c2g0.2.lhe",
           "L1kt1cT-1cg-0.4c2g-0.4.lhe",
           "L1kt1cT-1cg-0.4c2g0.4.lhe",
           "L1kt1cT-1cg-0.6c2g-0.6.lhe",
           "L1kt1cT-1cg-0.6c2g0.6.lhe",
           "L1kt1cT-1cg-0.8c2g-0.8.lhe",
           "L1kt1cT-1cg-0.8c2g0.8.lhe",
           "L1kt1cT-1cg-1c2g-1.lhe",
           "L1kt1cT-1cg-1c2g1.lhe",
           "L1kt1cT-1cg0.2c2g-0.2.lhe",
           "L1kt1cT-1cg0.2c2g0.2.lhe",
           "L1kt1cT-1cg0.4c2g-0.4.lhe",
           "L1kt1cT-1cg0.4c2g0.4.lhe",
           "L1kt1cT-1cg0.6c2g-0.6.lhe",
           "L1kt1cT-1cg0.6c2g0.6.lhe",
           "L1kt1cT-1cg0.8c2g-0.8.lhe",
           "L1kt1cT-1cg0.8c2g0.8.lhe",
           "L1kt1cT-1cg0c2g-0.2.lhe",
           "L1kt1cT-1cg0c2g-0.4.lhe",
           "L1kt1cT-1cg0c2g-0.6.lhe",
           "L1kt1cT-1cg0c2g-0.8.lhe",
           "L1kt1cT-1cg0c2g-1.lhe",
           "L1kt1cT-1cg0c2g0.4.lhe",
           "L1kt1cT-1cg0c2g0.6.lhe",
           "L1kt1cT-1cg0c2g0.8.lhe",
           "L1kt1cT-1cg0c2g0.lhe",
           "L1kt1cT-1cg0c2g1.lhe",
           "L1kt1cT-1cg1c2g-1.lhe",
           "L1kt1cT-2.4cg0c2g-0.2.lhe",
           "L1kt1cT-2.4cg0c2g-0.4.lhe",
           "L1kt1cT-2.4cg0c2g-0.6.lhe",
           "L1kt1cT-2.4cg0c2g-0.8.lhe",
           "L1kt1cT-2.4cg0c2g0.2.lhe",
           "L1kt1cT-2.4cg0c2g0.4.lhe",
           "L1kt1cT-2.4cg0c2g0.6.lhe",
           "L1kt1cT-2.4cg0c2g0.8.lhe",
           "L1kt1cT-2.4cg0c2g1.lhe",
           "L1kt1cT-2.5cg-0.2c2g-0.2.lhe",
           "L1kt1cT-2.5cg-0.2c2g0.2.lhe",
           "L1kt1cT-2.5cg-0.4c2g-0.4.lhe",
           "L1kt1cT-2.5cg-0.4c2g0.4.lhe",
           "L1kt1cT-2.5cg-0.6c2g-0.6.lhe",
           "L1kt1cT-2.5cg-0.6c2g0.6.lhe",
           "L1kt1cT-2.5cg-0.8c2g-0.8.lhe",
           "L1kt1cT-2.5cg-0.8c2g0.8.lhe",
           "L1kt1cT-2.5cg-1c2g-1.lhe",
           "L1kt1cT-2.5cg-1c2g1.lhe",
           "L1kt1cT-2.5cg0.2c2g-0.2.lhe",
           "L1kt1cT-2.5cg0.2c2g0.2.lhe",
           "L1kt1cT-2.5cg0.4c2g-0.4.lhe",
           "L1kt1cT-2.5cg0.4c2g0.4.lhe",
           "L1kt1cT-2.5cg0.6c2g-0.6.lhe",
           "L1kt1cT-2.5cg0.6c2g0.6.lhe",
           "L1kt1cT-2.5cg0.8c2g-0.8.lhe",
           "L1kt1cT-2.5cg0.8c2g0.8.lhe",
           "L1kt1cT-2.5cg0c2g-0.2.lhe",
           "L1kt1cT-2.5cg0c2g-0.4.lhe",
           "L1kt1cT-2.5cg0c2g-0.6.lhe",
           "L1kt1cT-2.5cg0c2g-0.8.lhe",
           "L1kt1cT-2.5cg0c2g-1.lhe",
           "L1kt1cT-2.5cg0c2g0.2.lhe",
           "L1kt1cT-2.5cg0c2g0.4.lhe",
           "L1kt1cT-2.5cg0c2g0.6.lhe",
           "L1kt1cT-2.5cg0c2g0.8.lhe",
           "L1kt1cT-2.5cg0c2g0.lhe",
           "L1kt1cT-2.5cg0c2g1.lhe",
           "L1kt1cT-2.5cg1c2g-1.lhe",
           "L1kt1cT-2.5cg1c2g1.lhe",
           "L1kt1cT-2cg-0.2c2g-0.2.lhe",
           "L1kt1cT-2cg-0.2c2g0.2.lhe",
           "L1kt1cT-2cg-0.4c2g-0.4.lhe",
           "L1kt1cT-2cg-0.4c2g0.4.lhe",
           "L1kt1cT-2cg-0.6c2g-0.6.lhe",
           "L1kt1cT-2cg-0.6c2g0.6.lhe",
           "L1kt1cT-2cg-0.8c2g-0.8.lhe",
           "L1kt1cT-2cg-0.8c2g0.8.lhe",
           "L1kt1cT-2cg-1c2g-1.lhe",
           "L1kt1cT-2cg-1c2g1.lhe",
           "L1kt1cT-2cg0.2c2g-0.2.lhe",
           "L1kt1cT-2cg0.2c2g0.2.lhe",
           "L1kt1cT-2cg0.4c2g-0.4.lhe",
           "L1kt1cT-2cg0.4c2g0.4.lhe",
           "L1kt1cT-2cg0.6c2g-0.6.lhe",
           "L1kt1cT-2cg0.6c2g0.6.lhe",
           "L1kt1cT-2cg0.8c2g-0.8.lhe",
           "L1kt1cT-2cg0.8c2g0.8.lhe",
           "L1kt1cT-2cg0c2g-0.2.lhe",
           "L1kt1cT-2cg0c2g-0.6.lhe",
           "L1kt1cT-2cg0c2g-0.8.lhe",
           "L1kt1cT-2cg0c2g-1.lhe",
           "L1kt1cT-2cg0c2g0.2.lhe",
           "L1kt1cT-2cg0c2g0.4.lhe",
           "L1kt1cT-2cg0c2g0.6.lhe",
           "L1kt1cT-2cg0c2g0.8.lhe",
           "L1kt1cT-2cg0c2g0.lhe",
           "L1kt1cT-2cg0c2g1.lhe",
           "L1kt1cT-2cg1c2g-1.lhe",
           "L1kt1cT-2cg1c2g1.lhe",
           "L1kt1cT-3cg-0.2c2g-0.2.lhe",
           "L1kt1cT-3cg-0.2c2g0.2.lhe",
           "L1kt1cT-3cg-0.4c2g-0.4.lhe",
           "L1kt1cT-3cg-0.4c2g0.4.lhe",
           "L1kt1cT-3cg-0.6c2g-0.6.lhe",
           "L1kt1cT-3cg-0.6c2g0.6.lhe",
           "L1kt1cT-3cg-0.8c2g-0.8.lhe",
           "L1kt1cT-3cg-0.8c2g0.8.lhe",
           "L1kt1cT-3cg-1c2g-1.lhe",
           "L1kt1cT-3cg-1c2g1.lhe",
           "L1kt1cT-3cg0.2c2g-0.2.lhe",
           "L1kt1cT-3cg0.2c2g0.2.lhe",
           "L1kt1cT-3cg0.4c2g-0.4.lhe",
           "L1kt1cT-3cg0.4c2g0.4.lhe",
           "L1kt1cT-3cg0.6c2g-0.6.lhe",
           "L1kt1cT-3cg0.6c2g0.6.lhe",
           "L1kt1cT-3cg0.8c2g-0.8.lhe",
           "L1kt1cT-3cg0.8c2g0.8.lhe",
           "L1kt1cT-3cg0c2g-0.2.lhe",
           "L1kt1cT-3cg0c2g-0.4.lhe",
           "L1kt1cT-3cg0c2g-0.6.lhe",
           "L1kt1cT-3cg0c2g-0.8.lhe",
           "L1kt1cT-3cg0c2g-1.lhe",
           "L1kt1cT-3cg0c2g0.2.lhe",
           "L1kt1cT-3cg0c2g0.4.lhe",
           "L1kt1cT-3cg0c2g0.6.lhe",
           "L1kt1cT-3cg0c2g0.8.lhe",
           "L1kt1cT-3cg0c2g0.lhe",
           "L1kt1cT-3cg0c2g1.lhe",
           "L1kt1cT-3cg1c2g-1.lhe",
           "L1kt1cT-3cg1c2g1.lhe",
           "L1kt1cT0.15cg0.15c2g-0.15.lhe",
           "L1kt1cT0.1cg0c2g0.8.lhe",
           "L1kt1cT0.1cg0c2g0.lhe",
           "L1kt1cT0.5cg-0.2c2g-0.2.lhe",
           "L1kt1cT0.5cg-0.2c2g-0.4.lhe",
           "L1kt1cT0.5cg-0.2c2g-0.6.lhe",
           "L1kt1cT0.5cg-0.2c2g-1.lhe",
           "L1kt1cT0.5cg-0.2c2g0.2.lhe",
           "L1kt1cT0.5cg-0.2c2g0.4.lhe",
           "L1kt1cT0.5cg-0.2c2g0.6.lhe",
           "L1kt1cT0.5cg-0.2c2g0.lhe",
           "L1kt1cT0.5cg-0.2c2g1.lhe",
           "L1kt1cT0.5cg-0.4c2g-0.2.lhe",
           "L1kt1cT0.5cg-0.4c2g-0.6.lhe",
           "L1kt1cT0.5cg-0.4c2g-1.lhe",
           "L1kt1cT0.5cg-0.4c2g0.4.lhe",
           "L1kt1cT0.5cg-0.4c2g0.6.lhe",
           "L1kt1cT0.5cg-0.4c2g0.lhe",
           "L1kt1cT0.5cg-0.4c2g1.lhe",
           "L1kt1cT0.5cg-0.6c2g-0.2.lhe",
           "L1kt1cT0.5cg-0.6c2g-0.4.lhe",
           "L1kt1cT0.5cg-0.6c2g-0.6.lhe",
           "L1kt1cT0.5cg-0.6c2g-1.lhe",
           "L1kt1cT0.5cg-0.6c2g0.4.lhe",
           "L1kt1cT0.5cg-0.6c2g0.6.lhe",
           "L1kt1cT0.5cg-0.6c2g0.8.lhe",
           "L1kt1cT0.5cg-0.6c2g0.lhe",
           "L1kt1cT0.5cg-0.6c2g1.lhe",
           "L1kt1cT0.5cg-0.8c2g-0.2.lhe",
           "L1kt1cT0.5cg-0.8c2g-0.4.lhe",
           "L1kt1cT0.5cg-0.8c2g-0.6.lhe",
           "L1kt1cT0.5cg-0.8c2g0.4.lhe",
           "L1kt1cT0.5cg-0.8c2g0.8.lhe",
           "L1kt1cT0.5cg-0.8c2g0.lhe",
           "L1kt1cT0.5cg-0.8c2g1.lhe",
           "L1kt1cT0.5cg-1c2g-0.2.lhe",
           "L1kt1cT0.5cg-1c2g-0.4.lhe",
           "L1kt1cT0.5cg-1c2g-0.6.lhe"
       };
    // output CXfile
    // we want to store the list of all final state particles
    ofstream out_pythiaCX;
    // Highest precision required for jet clustering
    out_pythiaCX.precision(5);
    out_pythiaCX.open("/lustre/cmswork/carvalho/lhe_clustering/CX3.txt");
    //
    string path= "/lustre/cmswork/carvalho/lhe_clustering/";
    for(unsigned ifile=0; ifile<274; ifile++){
        //unsigned ifile=0;
        string namefile_in=path+ "all_oct_15_lhe/";// + "hh_lhe/";
        namefile_in += namefile[ifile];
        /*string namefile_in=path + "Madgraphcg";
         if(ifile==0) namefile_in += "0/MGraviton_260.lhe";
         if(ifile==1) namefile_in += "0/MGraviton_500.lhe";
         if(ifile==2) namefile_in += "1/MGraviton_260.lhe";
         if(ifile==3) namefile_in += "1/MGraviton_500.lhe";
         if(ifile==4) namefile_in += "0_0137/Graviton_Parton/MGraviton_260.lhe";
         if(ifile==5) namefile_in += "0_0137/Graviton_Parton/MGraviton_500.lhe";
         if(ifile==6) namefile_in += "0/MGraviton_260.lhe";
         if(ifile==7) namefile_in += "600.lhe";
         if(ifile==8) namefile_in += "650.lhe";
         if(ifile==9) namefile_in += "700.lhe";
         if(ifile==10) namefile_in += "750.lhe";
         */
        string namefile_out= path+"all_oct_15_ascii/"+ namefile[ifile] + ".ascii";
        
        //    string namefile_in=path + "atEightTeV_processs_patched.lhe";
        //string namefile_out=namefile_in + ".pythia";
        //namefile_in += "test-MR610.lhe";
        cout<<"\n namefile_in = "<<namefile_in<<endl;
        cout<<"\n namefile_out = "<<namefile_out<<endl;
        
        
        // output file
        // we want to store the list of all final state particles
        ofstream out_pythia;
        // Highest precision required for jet clustering
        out_pythia.precision(15);
        // Generator. We here stick with default values, but changes
        // could be inserted with readString or readFile
        // Initialize Les Houches process File run. List initialization information.
        pythia.readString("Beams:frameType = 4");
        // the analysis program
        string sfile = "Beams:LHEF ="+namefile_in;
        pythia.readString(sfile.c_str());
        out_pythia.open(namefile_out.c_str());
        // Allow for possibility of a few faulty processs.
        int nAbort = 10;
        int iAbort = 0;
        // turn of hadronization settings - for testing  
        //  pythia.readString("25:mayDecay = no");
        ////////////////////////////////////////////////////////////////////
        // read decay table
        //pythia.readString("ProcessLevel:resonanceDecays = off"); // do not decay anything
        //pythia.readString("SLHA:readFrom = 2");
        //pythia.readString("SLHA:file = Susy.txt "); // input the decay table
        ////////////////////////////////////////////////////////////////////
        pythia.readString("PartonLevel:all = off"); // Off multiple interactions
        //pythia.readString("PartonLevel:ISR = off"); // Shower on
        //pythia.readString("PartonLevel:FSR = off"); // Shower on
        //pythia.readString("PartonLevel:FSRinResonances  = off"); // Off multiple interactions
        pythia.readString("HadronLevel:all = off"); // Of hadronization
        
        pythia.init();
        
        for (int iprocess = 0; ; ++iprocess) {
            // cout<<"\n iprocess = "<<iprocess<<"\n"<<endl;
            // Generate processs, and check whether generation failed.
            if (!pythia.next()) {
                // If failure because reached end of file then exit process loop.
                if (pythia.info.atEndOfFile()) break;
                // First few failures write off as "acceptable" errors, then quit.
                if (++iAbort < nAbort) continue;
                break;
            }
            //cout<<"hi"<<endl;
            // Acess process record  pythia.process.size()
            //cout<<"Number of particles = "<<pythia.process.size()<<endl;
            vector<int> pID;
            vector<double> px;
            vector<double> py;
            vector<double> pz;
            vector<double> E;
            vector<double> M;
            vector<int> mother;
            vector<int> code;
            // Some checks on the process record
            // Check for example that at least we have two bs and two bbars
            for (int i = 0; i < pythia.process.size(); i++){
                int particle_id = pythia.process[i].id();
                int particle_status = pythia.process[i].status();
                int particle_mother = pythia.process[i].mother1();
                // save only final state particles
                if(particle_id==25){//particle_status>0
                    //cout<<i<<" "<<particle_id<<" "<<particle_mother<<" "<<particle_status<<endl;
                    double ppx= pythia.process[i].px();
                    double ppy= pythia.process[i].py();
                    double ppz= pythia.process[i].pz();
                    double EE= pythia.process[i].e();
                    double MM= pythia.process[i].m();
                    //cout<<px<<" "<<py<<" "<<pz<<" "<<E<<endl;
                    pID.push_back(particle_id);
                    px.push_back(ppx);
                    py.push_back(ppy);
                    pz.push_back(ppz);
                    E.push_back(EE);
                    M.push_back(MM);
                    mother.push_back(particle_mother);
                    code.push_back(particle_id);
                }
            }
            // Save into file
            //out_pythia<<"#"<<endl;
            //cout<<"Number of final state particles = "<<E.size()<<"\n"<<endl;
            //out_pythia<<E.size()<<endl;
            for(unsigned i=0;i<E.size();i++){
                out_pythia<<px.at(i)<<" "<<py.at(i)<<" "<<pz.at(i)<<" "<<E.at(i)<<" "<<M.at(i)<<endl;// pID.at(i)<<" "<<
            }
            
            
            // End of process loop.
        }
        
        out_pythia.close();
        
        // Give statistics. Print histogram.
        pythia.stat(); 
        cout<<namefile[ifile] << " "<<(pythia.info.sigmaGen())*1000000000.<< " "<< (pythia.info.sigmaErr())*1000000000.<<endl; 
        out_pythiaCX<<namefile[ifile] << " "<<(pythia.info.sigmaGen())*1000000000.<< " "<< (pythia.info.sigmaErr())*1000000000.<<endl;        
        
    } //for unsigned
    
    out_pythiaCX.close();
    
    // Done.
    return 0;
}
