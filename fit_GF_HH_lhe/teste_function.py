#!/usr/bin/env python
#!/usr/bin/env python
# RUN: python teste_function.py  --LHC 13 --kl 1 --kt 1 --c2 0 --cg 0 --c2g 0

##########################################
# It tests with simulation to: 
# 13 (42)  -10.	0.5	0	0	0 : python teste_function.py  --LHC 13 --kl -10 --kt 0.5 --c2 0 --cg 0 --c2g 0
# 14 (9) 0.0001	2.25	0	0	0 : python teste_function.py  --LHC 13 --kl 0.0001 --kt 2.25 --c2 0 --cg 0 --c2g 0

from array import array
import math
import bisect
from optparse import OptionParser
import numpy as np
import ROOT
#from rootpy.plotting import Hist, HistStack, Legend, Canvas
#from rootpy.root2array import fill_hist_with_ndarray
import matplotlib
matplotlib.use('PS')   # generate postscript output by default
import matplotlib.pyplot as plt
#plt.style.use('seaborn-deep')

parser = OptionParser()
parser.add_option("--LHC", type="int", dest="lhc", help="LHC CM energy in TeV")
parser.add_option("--kl", type="float", dest="kll", help="LHC CM energy in TeV")
parser.add_option("--kt", type="float", dest="ktt", help="LHC CM energy in TeV")
parser.add_option("--c2", type="float", dest="c22", help="LHC CM energy in TeV")
parser.add_option("--cg", type="float", dest="cgg", help="LHC CM energy in TeV")
parser.add_option("--c2g", type="float", dest="c2gg", help="LHC CM energy in TeV")
(options, args) = parser.parse_args()
print "LHC @ %s TeV" % options.lhc
print " "
CM =options.lhc 
kl = options.kll
kt = options.ktt
c2 = options.c22
cg = options.cgg
c2g = options.c2gg
######################################################
# Declare the function
####################################################
def functionGF(kl,kt,c2,cg,c2g,A):
    return A[0]*kt**4 + A[1]*c2**2 + (A[2]*kt**2 + A[3]*cg**2)*kl**2  + A[4]*c2g**2 + ( A[5]*c2 + A[6]*kt*kl )*kt**2  + (A[7]*kt*kl + A[8]*cg*kl )*c2 + A[9]*c2*c2g  + (A[10]*cg*kl + A[11]*c2g)*kt**2+ (A[12]*kl*cg + A[13]*c2g )*kt*kl + A[14]*cg*c2g*kl
###############################
# read the GF coeficients in 15 2D matrices
# 90 bins in mhh from 0 to 1800 GeV (20 GeV wide)
# 9 bins in cost* from -1 to 1 (0.2 wide)
############################### 
#filne = "teste.txt"
filne = "coefficientsByBin.txt"
f = open(filne, 'r+')
lines = f.readlines() # get all lines as a list (array)
#[[element] * numcols] * numrows
effSM = np.zeros((9, 90)) #  [[0]*90]*9
effSum = np.zeros((9, 90)) #  [[0]*90]*9
MHH = np.zeros((9, 90)) #  [[0]*90]*9
COSTS = np.zeros((9, 90)) #  [[0]*90]*9
A1 = np.zeros((9, 90)) #  [[0]*90]*9
A2 = np.zeros((9, 90)) #  [[0]*90]*9
A3 = np.zeros((9, 90)) #  [[0]*90]*9
A4 = np.zeros((9, 90)) #  [[0]*90]*9
A5 = np.zeros((9, 90)) #  [[0]*90]*9
A6 = np.zeros((9, 90)) #  [[0]*90]*9
A7 = np.zeros((9, 90)) #  [[0]*90]*9
A8 = np.zeros((9, 90)) #  [[0]*90]*9
A9 = np.zeros((9, 90)) #  [[0]*90]*9
A10 = np.zeros((9, 90)) #  [[0]*90]*9
A11 = np.zeros((9, 90)) #  [[0]*90]*9
A12 = np.zeros((9, 90)) #  [[0]*90]*9
A13 = np.zeros((9, 90)) #  [[0]*90]*9
A14 = np.zeros((9, 90)) #  [[0]*90]*9
A15 = np.zeros((9, 90)) #  [[0]*90]*9
# Iterate over each line, printing each line and then move to the next
for line in  lines:
    l = []
    tokens = line.split()
    for token in tokens:
        num = ""
        num_char = "."
        num2 = "e"
        num3 = "-"
        for char in token: 
            #print char
            if (char.isdigit() or (char in num_char) or (char in num2) or (char in num3)): num = num + char
        try: 
           l.append(float(num))
        except ValueError: pass
    #print str(len(l))
    if (len(l)==35 ):
       #print line
       #print str(l[0])+" "+str(int(l[3]/20))+" "+str(int((1+l[4])/0.2))+" "+str(l[3])+" "+str(l[4])
       MHH[int((1+l[4])/0.2)][int(l[3]/20)] = l[3] 
       COSTS[int((1+l[4])/0.2)][int(l[3]/20)] = l[4] 
       effSM[int((1+l[4])/0.2)][int(l[3]/20)] = l[1]
       effSum[int((1+l[4])/0.2)][int(l[3]/20)] = l[2]
       A1[int((1+l[4])/0.2)][int(l[3]/20)] = l[5]
       A2[int((1+l[4])/0.2)][int(l[3]/20)] = l[6]
       A3[int((1+l[4])/0.2)][int(l[3]/20)] = l[7]
       A4[int((1+l[4])/0.2)][int(l[3]/20)] = l[8]
       A5[int((1+l[4])/0.2)][int(l[3]/20)] = l[9]
       A6[int((1+l[4])/0.2)][int(l[3]/20)] = l[10]
       A7[int((1+l[4])/0.2)][int(l[3]/20)] = l[11]
       A8[int((1+l[4])/0.2)][int(l[3]/20)] = l[12]
       A9[int((1+l[4])/0.2)][int(l[3]/20)] = l[13]
       A10[int((1+l[4])/0.2)][int(l[3]/20)] = l[14]
       A11[int((1+l[4])/0.2)][int(l[3]/20)] = l[15]
       A12[int((1+l[4])/0.2)][int(l[3]/20)] = l[16]
       A13[int((1+l[4])/0.2)][int(l[3]/20)] = l[17]
       A14[int((1+l[4])/0.2)][int(l[3]/20)] = l[18]
       A15[int((1+l[4])/0.2)][int(l[3]/20)] = l[19]
       #print str(COSTS[int((1+l[4])/0.2)][int(l[3]/20)])+" "+str(l[4])+" "+str(A1[int((1+l[4])/0.2)][int(l[3]/20)])
f.close()
###############################
# read the events and fill histograms with weights
# calculate mhh and cost* and find the bin
############################### 
xsSM = 0.013531 # 37.95
A13tev = [2.09078, 10.1517, 0.282307, 0.101205, 1.33191, -8.51168, -1.37309, 2.82636, 1.45767, -4.91761, -0.675197, 1.86189, 0.321422, -0.836276, -0.568156]
##############################
# declare arrays of numbers to check if SM
#if kl == 1 and kt == 1 and c2 ==0 and cg == 0 and c2g ==0 :
if 1>0 : 
  XSSMcalc = np.zeros((9*90)) 
  EffMcalc = np.zeros((9*90)) 
  counter=0
  countzeros=0
  for j in  range(0,90):
    for i in  range(0,9):
      A = [A1[i][j],A2[i][j],A3[i][j],A4[i][j],A5[i][j],A6[i][j],A7[i][j],A8[i][j],A9[i][j],A10[i][j],A11[i][j],A12[i][j],A13[i][j],A14[i][j],A15[i][j]]
      if functionGF(kl,kt,c2,cg,c2g,A13tev) > 0 :
        numerator=(float((effSM[i][j]*functionGF(kl,kt,c2,cg,c2g,A)/functionGF(kl,kt,c2,cg,c2g,A13tev)))-float(effSM[i][j]))
        denominator=(float((effSM[i][j]*functionGF(kl,kt,c2,cg,c2g,A)/functionGF(kl,kt,c2,cg,c2g,A13tev)))+float(effSM[i][j])) 
        if denominator > 0 : 
           EffMcalc[counter] = numerator/denominator
           XSSMcalc[counter] = functionGF(kl,kt,c2,cg,c2g,A) 
           #print str(EffMcalc[counter])+" "+str(XSSMcalc[counter])
           counter+=1
        else : countzeros+=1
      else : countzeros+=1
    #print (i,j)
    #print A
    #print str(functionGF(kl,kt,c2,cg,c2g,A13tev)) +" "+str(functionGF(kl,kt,c2,cg,c2g,A)) +" "+str(effSM[i][j]*functionGF(kl,kt,c2,cg,c2g,A)/functionGF(kl,kt,c2,cg,c2g,A13tev))+" "+str(effSM[i][j])+" "+str(effSum[i][j])+" "+str(MHH[i][j])+" "+str(COSTS[i][j])
  print "lost bins: "+str(countzeros)
  print "active bins: "+str(counter)
  ##############################
  # declare histograms to check SM point
  bin_size = 0.005; min_edge = 0; max_edge = 1
  N = (max_edge-min_edge)/bin_size; Nplus1 = N + 1
  bin_list = np.linspace(min_edge, max_edge, Nplus1)
  plt.xlim(min_edge, max_edge)
  plt.yscale('log', nonposy='clip')
  plt.hist(XSSMcalc, bin_list)
  plt.title(" In the SM ")
  plt.xlabel("Value")
  plt.ylabel("R_{HH}^i")
  plt.show()
  plt.savefig("RHH_kl_"+str(kl)+"_kl_"+str(kt)+"_c2_"+str(c2)+"_cg_"+str(cg)+"_c2g_" +str(c2g)+".eps")
  plt.cla()   # Clear axis
  plt.clf()   # Clear figure
  plt.close() # Close a figure window
  bin_size = 0.005; min_edge = -1; max_edge = 1
  N = (max_edge-min_edge)/bin_size; Nplus1 = N + 1
  bin_list = np.linspace(min_edge, max_edge, Nplus1) 
  plt.xlim(min_edge, max_edge)
  plt.yscale('log', nonposy='clip')
  plt.hist(EffMcalc, bin_list)
  plt.title(" In the SM ")
  plt.xlabel("Value")
  plt.ylabel("(eff[A]-EffMC)/(eff[A]+EffMC)")
  plt.show()
  plt.savefig("Binprediction_kl_"+str(kl)+"_kt_"+str(kt)+"_c2_"+str(c2)+"_cg_"+str(cg)+"_c2g_" +str(c2g)+".eps")
  plt.cla()   # Clear axis
  plt.clf()   # Clear figure
  plt.close() # Close a figure window
###############################
# read the events and construct shapes
############################### 
pathBSM="/afs/cern.ch/work/a/acarvalh/public/toAnamika/GF_HH_BSM/"
countline=0
countevent=0
counteventSM=0
countevent13=0
countevent14=0
Px = np.zeros((2)) 
Py = np.zeros((2)) 
Pz = np.zeros((2)) 
En = np.zeros((2))  
CalcMhh = np.zeros((1200000))
CalcCost = np.zeros((1200000))
CalcWeight = np.zeros((1200000))
###################################################
# take test histogram to compare
CalcMhh0 = np.zeros((100000))
CalcCost0 = np.zeros((100000))
#
CalcMhh13 = np.zeros((50000))
CalcCost13 = np.zeros((50000))
#
CalcMhh14 = np.zeros((50000))
CalcCost14 = np.zeros((50000))
# 0 is SM and 
# 13 (42)  -10.	0.5	0	0	0
# 14 (9) 0.0001	2.25	0	0	0
##################################################
for sam in  range(0,15):
 #counteventperfile=0
 sample="GF_HH_"+str(sam)+".lhe.decayed"
 filne = pathBSM+sample
 f = open(filne, 'r+')
 lines = f.readlines() # get all lines as a list (array)
 for line in  lines:
    l = []
    tokens = line.split()
    for token in tokens:
        num = ""
        num_char = "."
        num2 = "e"
        num3 = "-"
        for char in token: 
            #print char
            if (char.isdigit() or (char in num_char) or (char in num2) or (char in num3)): num = num + char
        try: 
           l.append(float(num))
        except ValueError: pass
    #print line
    if countline < 2 :
       Px[countline] = l[1] 
       Py[countline] = l[2]
       Pz[countline] = l[3]
       En[countline] = l[4]
    countline+=1
    if countline==2 :
       if abs(Px[0])!= abs(Px[1]) : print "error parsing ascii file"
       countline=0
       #CalcMhh[countevent] = math.sqrt( (En[0]+En[1])**2 - (Px[0]+Px[1])**2 - (Py[0]+Py[1])**2 - (Pz[0]+Pz[1])**2 )
       #CalcWeight[countevent] = 1./100000
       P1 = ROOT.TLorentzVector()
       P1.SetPxPyPzE(Px[0],Py[0],Pz[0],En[0])
       P2 = ROOT.TLorentzVector()
       P1.SetPxPyPzE(Px[1],Py[1],Pz[1],En[1])
       SUM = ROOT.TLorentzVector()
       SUM.SetPxPyPzE(Px[0]+Px[1],Py[0]+Py[1],Pz[0]+Pz[1],En[0]+En[1])
       mhhroot=SUM.M()
       #print P1.M()
       P1boost = P1
       #P12 = P1 + P2 # this is the total vectorial momenta of the system
       P1boost.Boost(-SUM.BoostVector())
       costhetast = float(P1boost.CosTheta())
       #print str(mhhroot)+ " "+str(costhetast)+" the bin corrdinates are: "+str(int(mhhroot/20))+" "+str(int((1+costhetast)/0.2))
       binmhh=int((mhhroot)/20)
       bincost=int((0.8+costhetast)/0.2)
       if binmhh < 90 :
         if sam ==0 and kl == 1 and kt == 1 and c2 ==0 and cg == 0 and c2g ==0 :
             CalcMhh0[counteventSM] = float(mhhroot)
             CalcCost0[counteventSM] = float(costhetast)
             counteventSM+=1
         if sam ==13 and kl == -10 and kt == 0.5 and c2 ==0 and cg == 0 and c2g ==0 :
             CalcMhh13[countevent13] = float(mhhroot)
             CalcCost13[countevent13] = float(costhetast)
             countevent13+=1
         if sam ==14 and kl == 0.0001 and kt == 2.25 and c2 ==0 and cg == 0 and c2g ==0 :
             CalcMhh14[countevent14] = float(mhhroot)
             CalcCost14[countevent14] = float(costhetast)
             countevent14+=1
         if sam >0 and sam < 13 :
           if effSum[bincost][binmhh] > 0 and A1[bincost][binmhh] > 0: 
             CalcMhh[countevent] = float(mhhroot)
             CalcCost[countevent] = float(costhetast)
             A = [A1[bincost][binmhh],A2[bincost][binmhh],A3[bincost][binmhh],A4[bincost][binmhh],A5[bincost][binmhh],\
              A6[bincost][binmhh],A7[bincost][binmhh],A8[bincost][binmhh],A9[bincost][binmhh],A10[bincost][binmhh],\
              A11[bincost][binmhh],A12[bincost][binmhh],A13[bincost][binmhh],A14[bincost][binmhh],A15[bincost][binmhh]]
             effBSM = float(effSM[bincost][binmhh]*functionGF(kl,kt,c2,cg,c2g,A)/functionGF(kl,kt,c2,cg,c2g,A13tev))
             CalcWeight[countevent] = effBSM/float(effSum[bincost][binmhh])
             countevent+=1
print countevent
###################################################
# Draw the histograms
bin_size = 30; min_edge = 200; max_edge = 1000
N = (max_edge-min_edge)/bin_size; Nplus1 = N + 1
bin_list = np.linspace(min_edge, max_edge, Nplus1)
plt.xlim(min_edge, max_edge)
#plt.yscale('log', nonposy='clip')
if kl == 1 and kt == 1 and c2 ==0 and cg == 0 and c2g ==0 :  plt.hist(CalcMhh0, bin_list , normed=1,  histtype='bar', label='simulated', color= 'b', edgecolor='b', lw=3)
if kl == -10 and kt == 0.5 and c2 ==0 and cg == 0 and c2g ==0 : plt.hist(CalcMhh13, bin_list , normed=1,  histtype='bar', label='simulated', color= 'b', edgecolor='b', lw=3)
if kl == 0.0001 and kt == 2.25 and c2 ==0 and cg == 0 and c2g ==0 : plt.hist(CalcMhh14, bin_list , normed=1,  histtype='bar', label='simulated', color= 'b', edgecolor='b', lw=3)
plt.hist(CalcMhh, bin_list, weights=CalcWeight , normed=1, histtype='bar', label='reweigted', fill=False, color= 'k', edgecolor='k')
plt.legend(loc='upper right')
plt.show()
plt.title(" In  kl =="+str(kl)+", kt =="+str(kt)+", c2 =="+str(c2)+", cg =="+str(cg)+", c2g ==" +str(c2g) )
plt.xlabel("Mhh (GeV)")
plt.ylabel("events")
plt.show()
plt.savefig("Mhh_kl_"+str(kl)+"_kt_"+str(kt)+"_c2_"+str(c2)+"_cg_"+str(cg)+"_c2g_" +str(c2g)+".eps")
plt.cla()   # Clear axis
plt.clf()   # Clear figure
plt.close() # Close a figure window
bin_size = 0.1; min_edge = -1; max_edge = 1
N = (max_edge-min_edge)/bin_size; Nplus1 = N + 1
bin_list = np.linspace(min_edge, max_edge, Nplus1)
plt.xlim(min_edge, max_edge)
#plt.yscale('log', nonposy='clip')
if kl == 1 and kt == 1 and c2 ==0 and cg == 0 and c2g ==0 : plt.hist(CalcCost0, bin_list , normed=1,  histtype='bar', label='simulated', color= 'b', edgecolor='b', lw=3)
if kl == -10 and kt == 0.5 and c2 ==0 and cg == 0 and c2g ==0 : plt.hist(CalcCost13, bin_list , normed=1,  histtype='bar', label='simulated', color= 'b', edgecolor='b', lw=3)
if kl == 0.0001 and kt == 2.25 and c2 ==0 and cg == 0 and c2g ==0 : plt.hist(CalcCost14, bin_list , normed=1,  histtype='bar', label='simulated', color= 'b', edgecolor='b', lw=3)
plt.hist(CalcCost, bin_list, weights=CalcWeight , normed=1, histtype='bar', label='reweigted', fill=False, color= 'k', edgecolor='k', lw=3)
plt.title(" In  kl =="+str(kl)+"and kt =="+str(kt)+"and c2 =="+str(c2)+"and cg =="+str(cg)+"and c2g ==" +str(c2g) )
plt.legend(loc='upper right')
plt.xlabel("Cost*")
plt.ylabel("events")
plt.show()
plt.savefig("CostS_kl_"+str(kl)+"_kt_"+str(kt)+"_c2_"+str(c2)+"_cg_"+str(cg)+"_c2g_" +str(c2g)+".eps")
plt.cla()   # Clear axis
plt.clf()   # Clear figure
plt.close() # Close a figure window
##########################################
#hcostS = ROOT.TH1F("hcostS", "costS", 50, -1, 1)
#hcostS = Hist(-1, 1, 50, title='costS', markersize=0)
#fill_hist_with_ndarray(hcostS, CalcCost)
#hcostS.draw()
#hcostS.save()

#fig = plt.gcf()
#plot_url = py.plot_mpl(fig, filename='mpl-basic-histogram')

#ii=1
#j=16
#A2 = [A1[ii][j],A2[ii][j],A3[ii][j],A4[ii][j],A5[ii][j],A6[ii][j],A7[ii][j],A8[ii][j],A9[ii][j],A10[ii][j],A11[ii][j],A12[ii][j],A13[ii][j],A14[ii][j],A14[ii][j]]
#print (ii,j)
#print A2
#print str(functionGF(kl,kt,c2,cg,c2g,A13tev)) +" "+str(functionGF(kl,kt,c2,cg,c2g,A2)) +" "+str(effSM[ii][j]*functionGF(kl,kt,c2,cg,c2g,A2)/functionGF(kl,kt,c2,cg,c2g,A13tev))+" "+str(effSM[ii][j]) +" "+str(effSum[ii][j])+" "+str(MHH[ii][j])+" "+str(COSTS[ii][j])


#0.999997 0.00049582676505 2.0002e-05 12.0012 133.9524
#0.999997 9.54905045385e-05 1.0001e-05 6.0006 87.62316

