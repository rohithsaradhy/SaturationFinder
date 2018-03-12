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

output="./Output/H2/Electron" # Make sure that in the analyse file the Output is set to ./Output/H2/



# unpack_rawFiles=true
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
mkdir -p $output/90


for RN in "${Eng20[@]}"
do
  if [ "$unpack_rawFiles" = true ] ; then
      cmsRun $unpack runNumber=$RN
  fi
  cmsRun $analyse runNumber=$RN
  mv $output/../*$RN.root $output/20/$RN.root
done
hadd $output/20GeV.root $output/20/*




for RN in "${Eng32[@]}"
do
  if [ "$unpack_rawFiles" = true ] ; then
      cmsRun $unpack runNumber=$RN
  fi
  cmsRun $analyse runNumber=$RN
  mv $output/../*$RN.root $output/32/$RN.root
done
hadd $output/32GeV.root $output/32/*


for RN in "${Eng50[@]}"
do
  if [ "$unpack_rawFiles" = true ] ; then
      cmsRun $unpack runNumber=$RN
  fi
  cmsRun $analyse runNumber=$RN
  mv $output/../*$RN.root $output/50/$RN.root
done
hadd $output/50GeV.root $output/50/*




for RN in "${Eng80[@]}"
do
  if [ "$unpack_rawFiles" = true ] ; then
      cmsRun $unpack runNumber=$RN
  fi
  cmsRun $analyse runNumber=$RN
  mv $output/../*$RN.root $output/80/$RN.root
done
hadd $output/80GeV.root $output/80/*


for RN in "${Eng90[@]}"
do
  if [ "$unpack_rawFiles" = true ] ; then
      cmsRun $unpack runNumber=$RN
  fi
  cmsRun $analyse runNumber=$RN
  mv $output/../*$RN.root $output/90/$RN.root
done
hadd $output/90GeV.root $output/90/*
