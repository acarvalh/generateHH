#!/usr/bin/env python
import os, subprocess, sys
from array import array
from ROOT import *
from math import sqrt, sin, cos, tan, exp
import numpy as np
from collections import OrderedDict
from optparse import OptionParser
import gzip
import fileinput
workingDir = os.getcwd()

def run_cmd(command):
  print "%s'" % command
  p = subprocess.Popen(command, shell = True, stdout = subprocess.PIPE, stderr = subprocess.PIPE)
  stdout, stderr = p.communicate()
  return stdout

dprocs = OrderedDict()
dprocs["SM"]         = ["generate g g > h h / g b ta+ Tfake [noborn=QCD] Ctthh^2=0", "ASM"]
dprocs["kt^4"]       = ["generate g g > h h / g b ta+ Tfake [noborn=QCD] Ctthh^2=0 NP^2=0 QED^2=4", "A1"]
dprocs["c2^2"]       = ["generate g g > h h / g b ta+ Tfake [noborn=QCD] Ctthh^2=2 NP^2=0 QED^2=0", "A2"]
dprocs["kt^2 kl^2"]  = ["generate g g > h h / g b ta+ Tfake [noborn=QCD] Ctthh^2=0 NP^2=2 QED^2=2", "A3"]
dprocs["cg^2 kl^2"]  = ["generate g g > h h / g b ta+ t [noborn=QCD] Ctthh^2=0 QCD^2=6", "A4"]
dprocs["c2g^2"]      = ["generate g g > h h / g b ta+ t h [noborn=QCD]", "A5"]
dprocs["c2 kt^2"]    = ["generate g g > h h / g b ta+ Tfake [noborn=QCD] Ctthh^2=1 NP^2=0 QED^2=2", "A6"]
dprocs["kl kt^3"]    = ["generate g g > h h / g b ta+ Tfake [noborn=QCD] Ctthh^2=0 NP^2=1 QED^2=3", "A7"]
dprocs["kt kl c2"]   = ["generate g g > h h / g b ta+   [noborn=QCD] Ctthh^2=1  QED^2=1 NP^2=1 QCD^2=4", "A8"]
dprocs["cg kl c2"]   = ["generate g g > h h / g b ta+   [noborn=QCD] Ctthh^2=1  QED^2=0 NP^2=1 QCD^2=5", "A9"]
dprocs["c2 c2g"]     = ["generate g g > h h / g b ta+   [noborn=QCD] Ctthh^2=1  QED^2=0 NP^2=0", "A10"]
dprocs["cg kl kt^2"] = ["generate g g > h h / g b ta+   [noborn=QCD] Ctthh^2=0  NP^2=1 QCD^2=5 QED^2=2", "A11"]
dprocs["c2g kt^2"]   = ["generate g g > h h / g b ta+   [noborn=QCD] Ctthh^2=0  NP^2=0", "A12"]
dprocs["kl^2 cg kt"] = ["generate g g > h h / g b ta+   [noborn=QCD] Ctthh^2=0  NP^2=2 QED^2=1 QCD^2=5", "A13"]
dprocs["c2g kt kl"]  = ["generate g g > h h / g b ta+   [noborn=QCD] Ctthh^2=0  NP^2=1 QCD^2=6 QED^2=1", "A14"]
dprocs["cg c2g kl"]  = ["generate g g > h h / g b ta+ t [noborn=QCD] Ctthh^2=0  NP^2=1", "A15"]

energy = "_14TeV"
## to launch MG
if 0 > 1 :
    ### change automatic html open on mg config
    for line in fileinput.input("MG5_aMC_v2_6_3_2/input/mg5_configuration.txt", inplace=True):
        if "automatic_html_opening" in line :
            line.rstrip().replace(line, "automatic_html_opening = False")

    pp = open("launch"+energy+".sh","w")
    pp.write("#!/bin/bash \n\n")
    pp.write("cd ../PrivateProduction/CMSSW_9_3_9_patch1/src/ \n")
    pp.write("eval `scram runtime -sh`\n")
    pp.write("cd -\n\n")
    for key in dprocs.keys() :
        filey = open("launch_"+dprocs[key][1]+energy+".sh","w")
        filey.write("import model loop_sm_lambda\n")
        filey.write(dprocs[key][0]+"\n")
        filey.write("output "+dprocs[key][1]+energy+"\n")
        filey.write("launch "+dprocs[key][1]+energy+"\n")
        filey.write("set nevents 500000\n")
        filey.write("set ebeam1 6500.0\n")
        filey.write("set ebeam2 6500.0\n")
        if "A12" in dprocs[key][1] : filey.write("set MLStabThres	1.000000d-01")
        filey.write("done\n")
        filey.close()
        pp.write("./MG5_aMC_v2_6_3_2/bin/mg5_aMC launch_"+dprocs[key][1]+energy+".sh &\n")
    pp.close()

## to collect results
if 1 > 0 :
    delphesfFolder = "/afs/cern.ch/work/a/acarvalh/delphes_main/Delphes_CMS/"
    run_cmd("mkdir lhe_results")
    CX = open("CX"+energy+".txt","w")
    submit = open(delphesfFolder+"submit_GF_HH_"+energy+".sh","w")
    submit.write('#!/bin/sh\n\n')
    for key in  dprocs.keys():
        #run_cmd("cp %s/Events/run_01/unweighted_events.lhe.gz lhe_results/%s_14TeV.lhe.gz" % (dprocs[key][1], dprocs[key][1]))
        run_cmd("cp %s/Events/run_01/unweighted_events.lhe.gz lhe_results/%s.lhe.gz" % (dprocs[key][1]+energy, dprocs[key][1]+energy))
        with gzip.open("lhe_results/%s.lhe.gz" % (dprocs[key][1]+energy) , 'r') as in_file:
            for line in in_file:
                if "Integrated weight (pb)" in line :
                    print (dprocs[key][1], line.split(" ")[13].replace("\n",""))
                    CX.write(dprocs[key][1]+" "+line.split(" ")[13])
                    break
        submit.write("gunzip -f %s/lhe_results/%s_14TeV.lhe.gz\n" % (workingDir,dprocs[key][1]))
        submit.write("./DelphesLHEF cards/gen_card.tcl %s/lhe_results/%s.root %s/lhe_results/%s.lhe \n\n" % (workingDir,dprocs[key][1]+energy, workingDir,dprocs[key][1]+energy))
    submit.close()
    CX.close()

#Channel 1 has encountered a fraction of of numerically unstable loop matrix element computations
# gunzip /afs/cern.ch/work/a/acarvalh/GridPacks/loop_MG_HH/lhe_results/A2_14TeV.lhe.gz ;./DelphesLHEF cards/gen_card.tcl /afs/cern.ch/work/a/acarvalh/GridPacks/loop_MG_HH/lhe_results/A2_14TeV.root /afs/cern.ch/work/a/acarvalh/GridPacks/loop_MG_HH/lhe_results/A2_14TeV.lhe.gz
# python analysis_gen.py --input lhe_results/A2_14TeV.root
