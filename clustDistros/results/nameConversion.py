#from C.Gottardo - 30 Mar 2015 - python nameConversion.py
#python nameConversion.py

diz = {}						#empty dictionary

for x in range(2, 21):

	for line in open("../utils/map_5par_13TeV_1488.dat"): #to be fixed
		key = line.split("\t")[0]			#split the line, take first part as key
		value = line.split("\t")[1]			#take first part as value
		diz[key]=value					#add new entry to dictionary

	fout = open("res_5p_13TeV_1488_NClu%d.dat" %(x), "w")	#open output file
	for line in open("LogP/clustering_nev20k_Nclu%d_50_5.asc" %(x)):
		outline = ""					#empty output line
		for number in line.split():			#read every number in the line
			name = diz.get(number)			#pick the corresponding dict. string
			outline += name.strip('\n')+ ","	#add name string w/o \n add comma
		outline = outline[:-1]				#remove last comma
		fout.write(outline + "\n")			#recover \n at end of out string
		#print(x)
	fout.close()
