#!/bin/bash
# This is for Electrons in the October Run...
#Written by Rohith Saradhy


Eng20=(1809 1810 1811 1812 1813)

Eng32=(1803 1804 1805 1806 1807)

Eng50=(1797 1798 1799 1800 1801)

Eng80=(1751 1754 1756 1757 1758 1759)

Eng90=()
# Eng150=(1194)
#
# Eng200=(1305) #//Ign-> 113,114

# Eng250=(1187 1188 1297)

# Eng300=(1189 1296)

# unpacker configuration files
unpack="unpack2017_LaterRuns_cfg.py"
#rawhit analyser configuration files
# analyse="rawhitprod2017_cfg.py"
analyse="rawhitprod2017_cfg_analyseTHEM.py"


unpack_rawFiles=false

if [ "$unpack_rawFiles" = true ] ; then
    echo -e "Unpacking is Switched On... \n"
fi

mkdir ./Output/20
mkdir ./Output/32
mkdir ./Output/50
mkdir ./Output/80
mkdir ./Output/90

# mkdir ./Output/150
# mkdir ./Output/200
# mkdir ./Output/250
# mkdir ./Output/300



for RN in "${Eng20[@]}"
do
  if [ "$unpack_rawFiles" = true ] ; then
      cmsRun $unpack runNumber=$RN
  fi
  cmsRun $analyse runNumber=$RN
  mv ./Output/*$RN.root ./Output/20/$RN.root
done
hadd ./Output/20GeV.root ./Output/20/*




for RN in "${Eng32[@]}"
do
  if [ "$unpack_rawFiles" = true ] ; then
      cmsRun $unpack runNumber=$RN
  fi
  cmsRun $analyse runNumber=$RN
  mv ./Output/*$RN.root ./Output/32/$RN.root
done
hadd ./Output/32GeV.root ./Output/32/*


for RN in "${Eng50[@]}"
do
  if [ "$unpack_rawFiles" = true ] ; then
      cmsRun $unpack runNumber=$RN
  fi
  cmsRun $analyse runNumber=$RN
  mv ./Output/*$RN.root ./Output/50/$RN.root
done
hadd ./Output/50GeV.root ./Output/50/*




for RN in "${Eng80[@]}"
do
  if [ "$unpack_rawFiles" = true ] ; then
      cmsRun $unpack runNumber=$RN
  fi
  cmsRun $analyse runNumber=$RN
  mv ./Output/*$RN.root ./Output/80/$RN.root
done
hadd ./Output/80GeV.root ./Output/80/*


for RN in "${Eng90[@]}"
do
  if [ "$unpack_rawFiles" = true ] ; then
      cmsRun $unpack runNumber=$RN
  fi
  cmsRun $analyse runNumber=$RN
  mv ./Output/*$RN.root ./Output/90/$RN.root
done
hadd ./Output/90GeV.root ./Output/90/*
