#!/bin/bash
# subshell-test.sh

###############################################
# 
cp vary5D.sh pp_hh_5par
mkdir hh_lhe
mkdir logs
#
################################################

for i in 1 2 3 4 5 6 7 8 9 10 11 12 13 14 15 16 17 ; do 
# 18 19 20 21 22 23 24 25 26 27 28 29 30 31 32 33 34 35 36 37 38 39 40 41 42 43 44 45 46 47 48 49 
# 
  cp -r pp_hh_5par pp_hh_5par_$i
  cp mini_togenerate20/mini_togenerate_ktXc2_${i}_.dat pp_hh_5par_$i/mini_togenerate_ktXc2.dat
#################################################################
  cd pp_hh_5par_$i 
  ls mini_togenerate_ktXc2*
  #. ./vary5D.sh >> log_$i.txt &
  chmod +x vary5D.sh 
  #screen -d -m -S "teste" vary5D.sh
  #nohup vary5D.sh #>> log_$i.txt 
  #echo ". ./vary5D.sh" | at now 
  . ./vary5D.sh > ../logs/log_${i}.txt &
  cd ..
  #rm -r pp_hh_5par_$i/Events/*
done
#rm -r pp_hh_5par_*