#!/usr/bin/env python 
import os, sys, time,math


#set param_card new 1 1.0
#set param_card new 2 0.5
#set param_card new 3 0.5

filist = "list_VBF_HH_SM.dat"
fl = open(filist, 'w')
for ii in range(1, 64):
 fipoints = "SM_VBF_HH_"+str(ii)+"/SM_VBF_HH_"+str(ii)+"_customizecards.dat"
 fp = open(fipoints, 'r+')
 linesp = fp.readlines() # get all lines as a list (array)
 par = []
 for linep in linesp:
    #print linep
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
        if (counterp == 4) :  par.append(float(ll[1]))
        counterp += 1
 string = str(par[0]) + " "+str(par[1]) + " "+str(par[2])
 print "point "+ str(ii)+" = " +string
 fl.write(string+"\n")
 fp.close()
fl.close()
