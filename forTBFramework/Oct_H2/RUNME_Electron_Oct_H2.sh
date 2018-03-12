#!/bin/bash
# This is for Electrons in the October Run...
#Written by Rohith Saradhy


Eng20=(1647 1648 1649)

Eng32=(1641 1642 1643 1646)

Eng50=(1634 1639)

Eng80=(1632 1637)

Eng90=(1651 1652)
# Eng150=(1194)
#
# Eng200=(1305) #//Ign-> 113,114

# Eng250=(1187 1188 1297)

# Eng300=(1189 1296)

#unpacker configuration files
unpack="unpack2017_LaterRuns_cfg.py"
#rawhit analyser configuration files
# analyse="rawhitprod2017_cfg.py"
analyse="rawhitprod_Oct_H2.py"


# unpack_rawFiles=true
unpack_rawFiles=false


if [ "$unpack_rawFiles" = true ] ; then
    echo -e "Unpacking is Switched On... \n"
  else
    echo -e "Unpacking is Switched Off... \n"
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
