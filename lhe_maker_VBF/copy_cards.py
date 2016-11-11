#!/usr/bin/env python
# RUN: python copy_cards.py --channel bWbj_T
import os, sys, time,math
import subprocess
from random import randint
from optparse import OptionParser
parser = OptionParser()

parser.add_option("--channel", type="str", dest="chan", help="channel: it should contain particle and chirality")
(options, args) = parser.parse_args()
channel = options.chan
#channel="bWbj_YL"

"""
mass=(800 , 1000 , 1400)
width=(10 , 20 , 30) 

base="_M800GeV_W10p"
toMass="_M"
toWidth="GeV_W"
pp="p"
"""

slash="/"
cust="_customizecards.dat"
proc="_proc_card.dat"
EM="_extramodels.dat"     
run="_run_card.dat"
run="_run_card.dat"
decay="_madspin_card.dat"

"""
fprocess = open('../../submit_'+str(channel)+'.sh', 'w')
fprocess.write('#!/bin/bash \n')

fsetup = open('../../setup_'+str(channel)+'.sh', 'w')
fsetup.write('#!/bin/bash \n')
fsetup.write('mkdir '+channel+'\n')


frun = open('../../run_'+str(channel)+'.sh', 'w')
frun.write('#!/bin/bash \n')
"""

filist = "list_VBF_HH_SM.dat"
fl = open(filist, 'r+')
linesp = fl.readlines() # get all lines as a list (array)
print "read ",filist
counter=1
par=[]
for linep in linesp:
  #for m in range(0,len(mass)):
  #for w in range(0,len(width)):
    print linep
    ll = []
    counterp =0
    tokens = linep.split()
    for token in tokens:
        num = ""
        num_char="."
        num_char2="-"
        num_char3="e"
        for char in token: 
            if char.isdigit() or (char in num_char) or (char in num_char2) or (char in num_char3): num = num + char
        try: ll.append(float(num))
        except ValueError: pass
        #if (counterp == 4) :  
        #par.append(float(ll[0]))
        #counterp += 1
    string = str(ll[0]) + " "+str(ll[1]) + " "+str(ll[2])
    print "point "+ str(counter)+" = " +string+"\n"
    #
    folderbase= "" #channel+slash
    folderbaseMW=channel+"_"+str(1)
    filecustbase =  folderbase+folderbaseMW+slash+folderbaseMW+cust
    fileprocbase =  folderbase+folderbaseMW+slash+folderbaseMW+proc
    fileEMbase =  folderbase+folderbaseMW+slash+folderbaseMW+EM
    filerunbase =  folderbase+folderbaseMW+slash+folderbaseMW+run
    filedecaybase =  folderbase+folderbaseMW+slash+folderbaseMW+decay
    #
    folder= ""
    folderMW=channel+"_"+str(counter)
    print folderbaseMW
    procMW=folderMW+proc
    filecust =  folder+folderMW+slash+folderMW+cust
    fileproc =  folder+folderMW+slash+folderMW+proc
    fileEM =  folder+folderMW+slash+folderMW+EM
    filerun =  folder+folderMW+slash+folderMW+run
    filedecay =  folder+folderMW+slash+folderMW+decay
    #
    process = subprocess.Popen(["mkdir "+folder+folderMW],shell=True,stdout=subprocess.PIPE)
    out = process.stdout.read()
    process = subprocess.Popen(["cp "+fileprocbase+" "+fileproc+"; "+\
                                "cp "+filecustbase+" "+filecust+"; "+\
                                "cp "+fileEMbase+" "+fileEM+"; "+\
                                "cp "+filedecaybase+" "+filedecay+"; "+\
                                "cp "+filerunbase+" "+filerun+"; "\
                               ],shell=True,stdout=subprocess.PIPE)
    out = process.stdout.read()
    # 
    print fileproc
    with open(fileproc, 'r+') as f:
       content = f.read()
       f.seek(0)
       f.truncate()
       f.write(content.replace('output SM_VBF_HH_1 -nojpeg','output SM_VBF_HH_'+str(counter)+' -nojpeg'))
    print filecust
    with open(filecust, 'r+') as fp:
       content = fp.read()
       fp.seek(0)
       fp.truncate()
       fp.write(content.replace('set param_card new 1 0.5','set param_card new 1 '+str(ll[1])))
    with open(filecust, 'r+') as fp1:
       content = fp1.read()
       fp1.seek(0)
       fp1.truncate()
       fp1.write(content.replace('set param_card new 2 0.5','set param_card new 2 '+str(ll[2])))
    with open(filecust, 'r+') as fp2:
       content = fp2.read()
       fp2.seek(0)
       fp2.truncate()
       fp2.write(content.replace('set param_card new 3 1.0','set param_card new 3 '+str(ll[0])))
    counter+=1
    
    #with open(filecust, 'r+') as fp:
    #   content = fp.read()
    #   fp.seek(0)
    #   fp.truncate()
    #   fp.write(content.replace('80.0', str(float(mass[m]*width[w]/100))))
    ####################################################################################
    # make scripts to run
    ###################################################################################
    """
    fprocess.write('./gridpack_generation.sh '+channel+toMass+str(mass[m])+toWidth+str(width[w])+"p cards/singleVLQ_wide/"+\
                    channel+slash+channel+toMass+str(mass[m])+toWidth+str(width[w])+'p 1nh & \n')
    dirrun=channel+slash+channel+toMass+str(mass[m])+toWidth+str(width[w])+'p'
    fsetup.write('mkdir '+dirrun+" \n"+\
                 'mv '+channel+toMass+str(mass[m])+toWidth+str(width[w])+'p_tarball.tar.xz ' +dirrun+" \n"+\
                 'cd '+dirrun+"\n"+\
                 'tar xvfJ '+channel+toMass+str(mass[m])+toWidth+str(width[w])+'p_tarball.tar.xz &\n'+\
                 'cd - \n')

    frun.write('cp cards/singleVLQ_wide/runcmsgrid_PDF4LHC.sh '+dirrun+'\n'+\
               'cd '+dirrun+"\n"+\
               './runcmsgrid.sh 30000 '+str(randint(0,10000)) +' 10 > output_'+channel+toMass+str(mass[m])+toWidth+str(width[w])+'p &\n'+\
               'cd - \n')
    """ 
#fprocess.close()
