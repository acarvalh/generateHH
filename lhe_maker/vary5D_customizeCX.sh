#!/bin/bash

###############################################
# turn off the automatic htmal open
#sed -i -e 's/# automatic_html_opening = True/automatic_html_opening = False/g' Cards/me5_configuration.txt
#change the number of events to 3
#sed -i -e 's/.*[0-9]* = nevents.*/  20000 = nevents \! Number of unweighted events requested /g' Cards/run_card.dat
#change the minimum distance between jets
#change the CM energy to 2Tev
#sed -i -E -e 's/[0-9]*.*=.*ebeam1/6500     = ebeam1/g' Cards/run_card.dat
#sed -i -E -e 's/[0-9]*.*=.*ebeam2/6500     = ebeam2/g' Cards/run_card.dat
# change the Higgs mass to 125 Gev
#sed -i -E -e 's/25 [0-9]+?\.?[0-9]+?.* .*MH/25 1.25000e+02 \# MH/g' Cards/param_card.dat

# change LR
#sed -i -E -e 's/25 [0-9]+?\.?[0-9]+?.* .*MH/25 1.25000e+02 \# MH/g' Cards/param_card.dat
################################################


counterline=0
# read the input file
while read line; do 
  let counterline=counterline+1
  # read a line and parse it
  #echo -e "$line\n"; 
  arr=$(echo $line | tr ";" "\n")  
  #echo "${arr[$1]}"
  #echo "${arr[$2]}"
  #echo "${arr[$3]}"
  #echo "${arr[$4]}\n"
  counter=100
  for x in $arr
  do
    #echo "$x"
    #echo "$counter"
    if [ $counter == 100 ]; then kl="$x" ; fi
    if [ $counter == 101 ]; then kt="$x" ; fi
    if [ $counter == 102 ]; then c2="$x" ; fi
    if [ $counter == 103 ]; then cg="$x" ; fi
    if [ $counter == 104 ]; then c2g="$x" ; fi
    counter=$((counter+1))
  #i++
  done  
  echo "$kl" " " "$kt" " " "$c2" " " "$cg" " " "$c2g" " " "$counterline" "4b_node_${counterline}_customizecards.dat"
  #change the parameters  
  #30 -1.000000e+00 # c2 
  #31 1.000000e+00 # a1 
  #32 1.000000e+00 # a2 
  #188 1.000000e+00 # ctr 
  #189 1.000000e+00 # cy 
cp customize_example.dat customize_toCX/4b_node_${counterline}_customizecards.dat

sed -i -E -e "s/set param_card bsm 30 .*/set param_card bsm 30 ${c2}/g" customize_toCX/4b_node_$line_customizecards.dat
sed -i -E -e "s/set param_card bsm 31 .*/set param_card bsm 31 $cg/g" customize_toCX/4b_node_$line_customizecards.dat
sed -i -E -e "s/set param_card bsm 32 */set param_card bsm 32 $c2g/g" customize_toCX/4b_node_$line_customizecards.dat
sed -i -E -e "s/set param_card bsm 188 .*/set param_card bsm 188 $kl/g" customize_toCX/4b_node_$line_customizecards.dat
sed -i -E -e "s/set param_card bsm 189 .*/set param_card bsm 189 $kt/g" customize_toCX/4b_node_$line_customizecards.dat
  # generate events 
#./bin/generate_events 0 L${kl}kt${kt}cT${c2}cg${cg}c2g${c2g} run1
# gunzip Events/L${kl}kt${kt}cT${c2}cg${cg}c2g${c2g}/unweighted_events.lhe.gz 
  #take the CX
#echo "${kl}" "${kt}" "${c2}" "${cg}" "${c2g}" "$(grep -E '\#  Integrated weight \(pb\)  \:  ' Events/L${kl}kt${kt}cT${c2}cg${cg}c2g${c2g}/unweighted_events.lhe)" >> ../hh_lhe/CX_8TeV.txt
# mv Events/L${kl}kt${kt}cT${c2}cg${cg}c2g${c2g}/unweighted_events.lhe ../hh_lhe/L${kl}kt${kt}cT${c2}cg${cg}c2g${c2g}.lhe
#rm -r Events/L${kl}kt${kt}cT${c2}cg${cg}c2g${c2g}
done < AllpointstoCX.txt



#vary on xi
#for xi in 0.166667 1 1.1;
#do


  #vary on the masses
#for (( i = 0 ; i <${#MR[@]} ; i++ )); do
# ${#MR[@]} ; i++ )); do
    #echo "${aa[$i]}"  "${bb[$i]}"  "${b3[$i]}" "${d3m5[$i]}"  "${d4m5[$i]}"

    #change the parameters
#    sed -i -E -e "s/ 9000001 [0-9]+?\.?[0-9]+?.* \# ImFmeio/ 9000001 ${ImFmeio[$i]} \# ImFmeio/g" Cards/param_card.dat
#   sed -i -E -e "s/ 9000003 [0-9]+?\.?[0-9]+?.* \# ReFmeio/ 9000003 ${ReFmeio[$i]} \# ReFmeio/g" Cards/param_card.dat
#   sed -i -E -e "s/ 35 [0-9]+?\.?[0-9]+?.* \# MH02/ 35 ${MR[$i]} \# MH02/g" Cards/param_card.dat

    #generate the events
#    ./bin/generate_events 0 MR_${MR[$i]}_on run1

#    gunzip Events/MR_${MR[$i]}_on/unweighted_events.lhe.gz 
#    mv Events/MR_${MR[$i]}_on/unweighted_events.lhe Radion_bbtata_LR3tevLHC8/MR_${MR[$i]}_on.lhe


    #take the CX
    #echo "a" "${aa[$i]}" "$(grep -E '\#  Integrated weight \(pb\)  \:  [0-9]+?.*?' Events/a_${aa[$i]}_m4/a_${aa[$i]}_m4.lhe)"
    #echo "a" "${aa[$i]}" "$(grep -E '\#  Integrated weight \(pb\)  \:  [0-9]+?.*?' Events/a01/a01.lhe)" >> teste.txt

#    sed -i -e 's/ 8   0/ 8   100/g' Radion_bbtata_LR3tevLHC8/MR_${MR[$i]}_on.lhe
#    sed -i -e 's/ 9   0/ 9   100/g' Radion_bbtata_LR3tevLHC8/MR_${MR[$i]}_on.lhe

    #take the CX
#    echo "MR" "${MR[$i]}" "$(grep -E '\#  Integrated weight \(pb\)  \:  ' Radion_bbtata_LR3tevLHC8/MR_${MR[$i]}_on.lhe)" >> Radion_bbtata_LR3tevLHC8/CX_LR3tev_LHC100.txt

#  done
#done
