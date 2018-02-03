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
analyse="rawhitprod2017_cfg_analyseTHEM.py"


unpack_rawFiles=false

if [ "$unpack_rawFiles" = true ] ; then
    echo -e "Unpacking is Switched On... \n"
fi

mkdir ./Output/20
mkdir ./Output/32
mkdir ./Output/50
mkdir ./Output/80
# mkdir ./Output/90

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


# for RN in "${Eng90[@]}"
# do
#   if [ "$unpack_rawFiles" = true ] ; then
#       cmsRun $unpack runNumber=$RN
#   fi
#   cmsRun $analyse runNumber=$RN
#   mv ./Output/*$RN.root ./Output/90/$RN.root
# done
# hadd ./Output/90GeV.root ./Output/90/*


mkdir./Output/Electrons
mv  ./Output/* ./Output/Electrons
