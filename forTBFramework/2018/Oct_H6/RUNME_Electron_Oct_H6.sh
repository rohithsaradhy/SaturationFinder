#!/bin/bash
# This is for Electrons in the October Run...
#Written by Rohith Saradhy


Eng20=(1967 1968 1969 1970 1971)
Eng32=(1960 1961  1962 1963 1964 1965)
Eng50=(1954 1955 1956 1957 1958)
Eng80=(1947 1948 1949 1950 1951 1952)



# unpacker configuration files
unpack="unpack2017_LaterRuns_cfg.py"
#rawhit analyser configuration files
# analyse="rawhitprod2017_cfg.py"
analyse="rawhitprod_Oct_H6.py"
output="./Output/H6/Electron" # Make sure that in the analyse file the Output is set to ./Output/H6/



unpack_rawFiles=false

if [ "$unpack_rawFiles" = true ] ; then
    echo -e "Unpacking is Switched On... \n"
  else
    echo -e "Unpacking is Switched Off... \n"
fi

mkdir -p $output/20
mkdir -p $output/32
mkdir -p $output/50
mkdir -p $output/80




for RN in "${Eng20[@]}"
do
  if [ "$unpack_rawFiles" = true ] ; then
      cmsRun $unpack runNumber=$RN
  fi
  cmsRun $analyse runNumber=$RN
  mv $output/../*$RN.root $output/20/$RN.root
done




for RN in "${Eng32[@]}"
do
  if [ "$unpack_rawFiles" = true ] ; then
      cmsRun $unpack runNumber=$RN
  fi
  cmsRun $analyse runNumber=$RN
  mv $output/../*$RN.root $output/32/$RN.root
done


for RN in "${Eng50[@]}"
do
  if [ "$unpack_rawFiles" = true ] ; then
      cmsRun $unpack runNumber=$RN
  fi
  cmsRun $analyse runNumber=$RN
  mv $output/../*$RN.root $output/50/$RN.root
done




for RN in "${Eng80[@]}"
do
  if [ "$unpack_rawFiles" = true ] ; then
      cmsRun $unpack runNumber=$RN
  fi
  cmsRun $analyse runNumber=$RN
  mv $output/../*$RN.root $output/80/$RN.root
done

# Adding All files together...
hadd -f $output/20GeV.root $output/20/*
hadd -f $output/32GeV.root $output/32/*
hadd -f $output/50GeV.root $output/50/*
hadd -f $output/80GeV.root $output/80/*
