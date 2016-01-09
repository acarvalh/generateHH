// main12.cc is a part of the PYTHIA process generator.
// Copyright (C) 2015 Torbjorn Sjostrand.
// PYTHIA is licenced under the GNU GPL version 2, see COPYING for details.
// Please respect the MCnet Guidelines, see GUIDELINES for details.

// This is a simple test program.
// It illustrates how Les Houches process File input can be used in PYTHIA.
// It uses two LHE files, ttbar.lhe and ttbar2.lhe, which are combined
// using Beams:newLHEFsameInit = on to skip new initialization second time.
// Then the second file is viewed as a simple continuation of the first,
// just split for practical reasons, rather than as a separate new run
// with a new set of processes.
// In the first file top decays have been performed, in the second not,
// and are instead handled by the internal PYTHIA resonance-decay machinery.
// Furthermore the internal top production processes are switched on and
// mixed in, giving an unrealistic "double up" total top cross section.
// Much of this of course is not intended to be realistic,
// but rather illustrates several tricks that can be useful.

#include "Pythia8/Pythia.h"
using namespace Pythia8;
int main() {
    
    // Generator. We here stick with default values, but changes
    // could be inserted with readString or readFile.
    Pythia pythia;
    
    string path= "/Users/Xanda/Documents/programs/generateHH/hh_lhe_V1_50k";
    for(unsigned ifile=0; ifile<13; ifile++){
    //unsigned ifile=0;
        
        string namefile_in=path;//+"";
        if(ifile==0) namefile_in += "/L-15.0kt1.25cT6.0cg-0.0467c2g-0.5150.lhe";
        if(ifile==1) namefile_in += "/L-15.0kt2.0cT6.0cg-0.1680c2g-0.5180.lhe";
        if(ifile==2) namefile_in += "/L1.0kt0.5cT4.0cg-1.0c2g-0.3780.lhe";
        if(ifile==3) namefile_in += "/L1.0kt1.0cT0cg0c2g0.lhe";
        if(ifile==4) namefile_in += "/L10.0kt1.5cT-1.0cg-0.0956c2g0.1240.lhe";
        if(ifile==5) namefile_in += "/L10.0kt2.25cT2.0cg-0.2130c2g-0.0893.lhe";
        if(ifile==6) namefile_in += "/L15.0kt0.5cT1.0cg-0.0743c2g-0.0668.lhe";
        if(ifile==7) namefile_in += "/L15.0kt1.5cT-3.0cg-0.0816c2g0.3010.lhe";
        if(ifile==8) namefile_in += "/L2.4kt1.25cT2.0cg-0.2560c2g-0.1480.lhe";
        if(ifile==9) namefile_in += "/L2.4kt2.25cT2.0cg-0.0616c2g-0.1200.lhe";
        if(ifile==10) namefile_in += "/L5.0kt2.25cT3.0cg0c2g0.lhe";
        if(ifile==11) namefile_in += "/L7.5kt2.0cT0.5cg0c2g0.lhe";
        if(ifile==12) namefile_in += "/L7.5kt2.5cT-0.5cg0c2g0.lhe";
        //unsigned ifile=0;
        /*
        if(ifile==0) namefile_in += "300theta0.0001cHt0.0001.lhe";
        if(ifile==1) namefile_in += "300theta1.26cHt0.9520903415905158.lhe";
        if(ifile==2) namefile_in += "400theta0.0001cHt1.lhe";
        if(ifile==3) namefile_in += "260theta0.66cHt0.6131168519734338.lhe";
        if(ifile==4) namefile_in += "300theta0.0001cHt1.lhe";
        if(ifile==5) namefile_in += "350theta0.66cHt0.6131168519734338.lhe";
        if(ifile==6) namefile_in += "400theta0.66cHt0.6131168519734338.lhe";
        if(ifile==7) namefile_in += "260theta0.96cHt0.8191915683009983.lhe";
        if(ifile==8) namefile_in += "300theta0.66cHt0.6131168519734338.lhe";
        if(ifile==9) namefile_in += "350theta0.96cHt0.8191915683009983.lhe";
        if(ifile==10) namefile_in += "400theta0.96cHt0.8191915683009983.lhe";
        if(ifile==11) namefile_in += "260theta1.26cHt0.9520903415905158.lhe";
        if(ifile==12) namefile_in += "300theta0.96cHt0.8191915683009983.lhe";
        if(ifile==13) namefile_in += "350theta1.26cHt0.9520903415905158.lhe";
        if(ifile==14) namefile_in += "400theta1.26cHt0.9520903415905158.lhe";
         */
        /*    string namefile_in=path;// + "pp_hh_vbf_";
    if(ifile==0) namefile_in += "L-12.5y1.0c1.0.lhe";
    if(ifile==1) namefile_in += "L-15kt0.5cT-3cg-0.121c2g0.234.lhe";
    if(ifile==2) namefile_in += "L-15kt1.25cT5cg-0.0667c2g-0.433.lhe";
    if(ifile==3) namefile_in += "L-15kt1.75cT2cg-0.206c2g-0.19.lhe";
    if(ifile==4) namefile_in += "L-15kt1.cT2cg-0.0898c2g-0.184.lhe";
    if(ifile==5) namefile_in += "L-15kt2.cT5cg-0.188c2g-0.436.lhe";
    if(ifile==6) namefile_in += "L-1kt1.25cT-2cg-1.c2g0.192.lhe";
    if(ifile==7) namefile_in += "L1.0y2.5c2.0.lhe";
    if(ifile==8) namefile_in += "L1.kt0.5cT3cg-0.905c2g-0.243.lhe";
    if(ifile==9) namefile_in += "L1.kt0.75cT0cg0.0329c2g0.00516.lhe";
    if(ifile==10) namefile_in += "L1.kt1.cT0cg0.0971c2g0.266.lhe";
    if(ifile==11) namefile_in += "L1.kt2.25cT2cg0.216c2g-0.126.lhe";
    if(ifile==12) namefile_in += "L10.0y0.5c3.0.lhe";
    if(ifile==13) namefile_in += "L10kt1.5cT-2cg-0.0656c2g0.206.lhe";
    if(ifile==14) namefile_in += "L10kt1.5cT4cg-0.246c2g-0.286.lhe";
    if(ifile==15) namefile_in += "L10kt1.75cT-1cg-0.107c2g0.134.lhe";
    if(ifile==16) namefile_in += "L10kt2.25cT1cg-0.183c2g-0.00731.lhe";
    if(ifile==17) namefile_in += "L12.5y2.5c-2.0.lhe";
    if(ifile==18) namefile_in += "L15.0y1.0c0.0.lhe";
    if(ifile==19) namefile_in += "L15kt0.5cT0cg-0.0543c2g0.0151.lhe";
    if(ifile==20) namefile_in += "L15kt1.5cT-2cg-0.102c2g0.219.lhe";
    if(ifile==21) namefile_in += "L15kt1.cT-1cg-0.0815c2g0.116.lhe";
    if(ifile==22) namefile_in += "L2.4kt1.25cT1cg-0.131c2g-0.066.lhe";
    if(ifile==23) namefile_in += "L2.4kt1.75cT1cg-0.056c2g-0.0536.lhe";
    if(ifile==24) namefile_in += "L2.4kt2.25cT1cg0.0634c2g-0.0379.lhe";
    if(ifile==25) namefile_in += "L3.5y1.25c0.0.lhe";
    if(ifile==26) namefile_in += "L3.5y1.25c1.0.lhe";
    if(ifile==27) namefile_in += "L5.0y1.5c0.0.lhe";
    if(ifile==28) namefile_in += "L5.0y2.25c2.0.lhe";
    if(ifile==29) namefile_in += "L5.kt1.25cT0cg-0.0781c2g0.0218.lhe";
    if(ifile==30) namefile_in += "L5.kt1.75cT0cg-0.0721c2g0.0364.lhe";
    if(ifile==31) namefile_in += "L5.kt2.5cT0cg-0.0233c2g0.0648.lhe";
    if(ifile==32) namefile_in += "L5.y1.0c3.0.lhe";
    if(ifile==33) namefile_in += "L5.y2.5c-2.0.lhe";
    if(ifile==34) namefile_in += "L7.5y2.0c0.0.lhe";
    if(ifile==35) namefile_in += "L7.5y2.0c3.0.lhe";
    if(ifile==36) namefile_in += "L7.5y2.5c3.0.lhe";
    if(ifile==37) namefile_in += "L1.0y1.0c0.0.lhe";
 */
    
    string namefile_out=namefile_in + ".shower";
    
    //    string namefile_in=path + "atEightTeV_processs_patched.lhe";
    //string namefile_out=namefile_in + ".pythia";
    //namefile_in += "test-MR610.lhe";
    cout<<"\n namefile_in = "<<namefile_in<<endl;
    cout<<"\n namefile_out = "<<namefile_out<<endl;
    
    
    // output file
    // we want to store the list of all final state particles
    ofstream out_pythia;
    // Highest precision required for jet clustering
    out_pythia.precision(6);
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
    //pythia.readString("processLevel:resonanceDecays = off"); // do not decay anything
    //pythia.readString("SLHA:readFrom = 2");
    //pythia.readString("SLHA:file = Susy.txt "); // input the decay table
    // decays
    //pythia.readString("25:mayDecay = no"); 
    pythia.readString("5:onMode = off");
    //pythia.readString("25:onIfMatch = 5 -5"); // e ve
    ////////////////////////////////////////////////////////////////////
    //pythia.readString("PartonLevel:MI = off"); // Off multiple interactions
    //pythia.readString("PartonLevel:ISR = off"); // Shower on
    //pythia.readString("PartonLevel:FSR = off"); // Shower on
    //pythia.readString("PartonLevel:FSRinResonances  = off"); // Off multiple interactions
    pythia.readString("PartonLevel:all = on"); // Shower on
    pythia.readString("HadronLevel:all = off"); // Of hadronization
    cout<<"hi"<<endl;
    pythia.init();
    cout<<"hi"<<endl;
    for (int iprocess = 0;  ; ++iprocess) {
        //cout<<"\n iprocess = "<<iprocess<<"\n"<<endl;
        // Generate processs, and check whether generation failed.
        if (!pythia.next()) {
            // If failure because reached end of file then exit process loop.
            if (pythia.info.atEndOfFile()) break;
            // First few failures write off as "acceptable" errors, then quit.
            if (++iAbort < nAbort) continue;
            break;
        }
        
        // Acess process record  pythia.process.size()
        //cout<<"Number of particles = "<<pythia.process.size()<<endl;
        vector<int> pID;
        vector<double> px;
        vector<double> py;
        vector<double> pz;
        vector<double> E;
        vector<int> mother;
        vector<int> code;
        // Some checks on the process record
        ///////////////////////////////////////////////////////////////////////
        // Check for example that at least we have two bs and two bbars
        for (int i = 0; i < pythia.event.size(); i++){
            int particle_id = pythia.event[i].id();
            int particle_status = pythia.event[i].status();
            int particle_mother = pythia.event[i].mother1();
            // save only final state particles
            if(particle_status>0 ){ // || particle_id == 25
                //cout<<i<<" "<<particle_id<<" "<<particle_mother<<" "<<particle_status<<endl;
                double ppx= pythia.event[i].px();
                double ppy= pythia.event[i].py();
                double ppz= pythia.event[i].pz();
                double EE= pythia.event[i].e();
                //cout<<px<<" "<<py<<" "<<pz<<" "<<E<<endl;
                pID.push_back(particle_id);
                px.push_back(ppx);
                py.push_back(ppy);
                pz.push_back(ppz);
                E.push_back(EE);
                mother.push_back(particle_mother);
                code.push_back(particle_id);
            }
        }
        ///////////////////////////////////////////////////////////////////////
        // save the two gen level higgses
        ///////////////////////////////////////////////////////////////////////
        vector<int> pIDp;
        vector<double> pxp;
        vector<double> pyp;
        vector<double> pzp;
        vector<double> Ep;
        vector<int> motherp;
        vector<int> codep;
        for (int i = 0; i < pythia.process.size(); i++){
            int particle_id = pythia.process[i].id();
            int particle_status = pythia.process[i].status();
            int particle_mother = pythia.process[i].mother1();
            // save only final state particles
            if(particle_status>0 || particle_id == 25){ // 
                //cout<<i<<" "<<particle_id<<" "<<particle_mother<<" "<<particle_status<<endl;
                double ppx= pythia.process[i].px();
                double ppy= pythia.process[i].py();
                double ppz= pythia.process[i].pz();
                double EE= pythia.process[i].e();
                //cout<<px<<" "<<py<<" "<<pz<<" "<<E<<endl;
                pIDp.push_back(particle_id);
                pxp.push_back(ppx);
                pyp.push_back(ppy);
                pzp.push_back(ppz);
                Ep.push_back(EE);
                motherp.push_back(particle_mother);
                codep.push_back(particle_id);
            }
        }
        ///////////////////////////////////////////////////////////////////////
        // Save into file
        out_pythia<<"#"<<endl;
        //cout<<"Number of final state particles = "<<E.size()<<"\n"<<endl;
        // the two first higgses are the gen level ones
        out_pythia<<E.size()+2<<endl;
        for(unsigned i=0;i<2;i++){
            out_pythia<<pIDp.at(i)<<" "<<pxp.at(i)<<" "<<pyp.at(i)<<" "<<pzp.at(i)<<" "<<Ep.at(i)<<" "<<endl;
        }
        for(unsigned i=0;i<E.size();i++){
            out_pythia<<pID.at(i)<<" "<<px.at(i)<<" "<<py.at(i)<<" "<<pz.at(i)<<" "<<E.at(i)<<" "<<endl;
        }
        ///////////////////////////////////////////////////////////////////////        
    } // End of process loop.
    
    out_pythia.close();
    
    // Give statistics. Print histogram.
    pythia.stat();
    
    
    } //for unsigned
    
    // Done.
    return 0;
}
