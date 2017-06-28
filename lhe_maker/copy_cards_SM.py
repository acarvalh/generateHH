#!/usr/bin/env python
# RUN: python copy_cards.py 
import os, sys, time,math
import subprocess
from random import randint
from optparse import OptionParser
parser = OptionParser()

#channel="bWbj_YL"


base="GF_HH_"
slash="/"

cust="_customizecards.dat"
proc="_proc_card.dat"
EM="_extramodels.dat"     
run="_run_card.dat"
run="_run_card.dat"

filecustbase =  base+"0"+slash+base+"0"+cust
fileprocbase =  base+"0"+slash+base+"0"+proc
fileEMbase =    base+"0"+slash+base+"0"+EM
filerunbase =   base+"0"+slash+base+"0"+run

fprocess = open('submit_hhToRecursive.sh', 'w')
fprocess.write('#!/bin/bash \n')

fsetup = open('setup_hhToRecursive.sh', 'w')
fsetup.write('#!/bin/bash \n')
fsetup.write('mkdir GF_HH/ \n')

frun = open('run_hhToRecursive.sh', 'w')
frun.write('#!/bin/bash \n')

################################################
#
################################################
copies=20
for countline in range(0,copies):
    Vkl = float(1.0)
    Vkt=float(1.0)
    Vc2=float(0.0)
    Vcg=float(0.0)
    Vc2g=float(0.0)
    ########################################
    print str(Vkl)+" "+str(Vkt)+" "+str(Vc2)+" "+str(Vcg)+" "+str(Vc2g)
    filecust =  base+str(countline)+slash+base+str(countline)+cust
    fileproc =  base+str(countline)+slash+base+str(countline)+proc
    fileEM =    base+str(countline)+slash+base+str(countline)+EM
    filerun =   base+str(countline)+slash+base+str(countline)+run
    print filecust+" "+filecustbase
    process = subprocess.Popen(["mkdir "+base+str(countline)],shell=True,stdout=subprocess.PIPE)
    out = process.stdout.read()
    process = subprocess.Popen(["cp "+fileprocbase+" "+fileproc+"; "+\
                                "cp "+filecustbase+" "+filecust+"; "+\
                                "cp "+fileEMbase+" "+fileEM+"; "+\
                                "cp "+filerunbase+" "+filerun+"; "\
                               ],shell=True,stdout=subprocess.PIPE)
    out = process.stdout.read()
    print fileproc
    with open(fileproc, 'r+') as f:
       content = f.read()
       f.seek(0)
       f.truncate()
       f.write(content.replace(base+"0", base+str(countline)))
    print filecust
    
    with open(filecust, 'r+') as fp:
       content = fp.read()
       fp.seek(0)
       fp.truncate()
       fp.write(content.replace('set param_card bsm 188 1.0', 'set param_card bsm 188 '+str(Vkl)))
    fp.close()
    with open(filecust, 'r+') as fp:
       content = fp.read()
       fp.seek(0)
       fp.truncate()
       fp.write(content.replace('set param_card bsm 189 1.0', 'set param_card bsm 189 '+str(Vkt)))
    fp.close()
    with open(filecust, 'r+') as fp:
       content = fp.read()
       fp.seek(0)
       fp.truncate()
       fp.write(content.replace('set param_card bsm 30 0.0', 'set param_card bsm 30 '+str(Vc2)))
    fp.close()
    with open(filecust, 'r+') as fp:
       content = fp.read()
       fp.seek(0)
       fp.truncate()
       fp.write(content.replace('set param_card bsm 31 0.0', 'set param_card bsm 31 '+str(Vcg)))
    fp.close()
    with open(filecust, 'r+') as fp:
       content = fp.read()
       fp.seek(0)
       fp.truncate()
       fp.write(content.replace('set param_card bsm 32 0.0', 'set param_card bsm 32 '+str(Vc2g)))
    ####################################################################################
    # make scripts to run
    ###################################################################################
    fprocess.write('./gridpack_generation.sh '+base+str(countline)+" cards/GF_HH/"+base+str(countline)+' 1nh & \n')
    dirrun='GF_HH/'+base+str(countline)
    fsetup.write('mkdir '+dirrun+" \n"+\
                 'mv '+base+str(countline)+'_tarball.tar.xz ' +dirrun+" \n"+\
                 'cd '+dirrun+"\n"+\
                 'tar xvfJ '+base+str(countline)+'_tarball.tar.xz &\n'+\
                 'cd - \n')
    frun.write('cp runcmsgrid_PDF4LHC.sh '+dirrun+'\n'+\
               'cd '+dirrun+"\n"+\
               './runcmsgrid.sh 500000 '+str(randint(0,10000)) +' 10 > output_'+base+str(countline)+'.txt &\n'+\
               'cd - \n')
    countline+=1    
fprocess.close()    
fsetup.close()
frun.close()
