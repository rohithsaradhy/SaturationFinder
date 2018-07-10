#!/bin/bash
#This is to hadd runs with same energy...

SaveLocation="/eos/user/r/rsaradhy/NTuples/2018_June_V6/"
NTupleLocation="/eos/cms/store/group/dpg_hgcal/tb_hgcal/2018/cern_h2_june/offline_analysis/ntuples/v6"

for file in ./runs/Electrons*
do
  echo $file


runs=""
while read p;
do
  # echo $p
runs=$runs" $NTupleLocation/ntuple_"$p".root"
done < $file

echo $runs
echo $file


rootName=$(echo $file | rev |  cut -d '.' -f2 | cut -d '/' -f1 | rev).root
 echo $SaveLocation$rootName $runs


done
