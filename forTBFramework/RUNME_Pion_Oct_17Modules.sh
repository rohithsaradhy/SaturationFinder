#!/bin/bash
#Shell script to repeat the runs for Oct runs for Pion
#Written by Rohith Saradhy

Eng50=(1781 1782 1785 1786 1787 1788 1790 1791 1792 1793)

Eng100=(1762 1763 1764 1765 1771 1772 1773 1775 1776 1777 1778 1779)

Eng120=(1824 1825 1826 1709 1710 1711 1714 1715 1719 1720 1723 1724 1725 1726 1727 1728 1729 1730 1731 1732 1733)

Eng150=()

Eng200=()

Eng250=()

Eng300=()

Eng350=()



# Making the directories to keep the individual files...
mkdir ./Output/100
mkdir ./Output/150
mkdir ./Output/200
mkdir ./Output/250
mkdir ./Output/300
mkdir ./Output/350


#unpacker configuration files
unpack="unpack2017_LaterRuns_cfg.py"
#rawhit analyser configuration files
# analyse="rawhitprod2017_cfg_analyseTHEM.py"
analyse="rawhitprod2017_cfg.py"



#unpack the files if true. Otherwise just get them through the analyser....
unpack_rawFiles=false

if [ "$unpack_rawFiles" = true ] ; then
    echo -e "Unpacking is Switched On... \n"
fi



for RN in "${Eng100[@]}"
do
  if [ "$unpack_rawFiles" = true ] ; then
      cmsRun $unpack runNumber=$RN
  fi
  cmsRun $analyse runNumber=$RN
  mv ./Output/*$RN.root ./Output/100/$RN.root
done
hadd ./Output/100GeV.root ./Output/100/*


for RN in "${Eng150[@]}"
do
  if [ "$unpack_rawFiles" = true ] ; then
      cmsRun $unpack runNumber=$RN
  fi
  cmsRun $analyse runNumber=$RN
  mv ./Output/*$RN.root ./Output/150/$RN.root
done
hadd ./Output/150GeV.root ./Output/150/*


for RN in "${Eng200[@]}"
do
  if [ "$unpack_rawFiles" = true ] ; then
      cmsRun $unpack runNumber=$RN
  fi
  cmsRun $analyse runNumber=$RN
  mv ./Output/*$RN.root ./Output/200/$RN.root
done
hadd ./Output/200GeV.root ./Output/200/*


for RN in "${Eng250[@]}"
do
  if [ "$unpack_rawFiles" = true ] ; then
      cmsRun $unpack runNumber=$RN
  fi
  cmsRun $analyse runNumber=$RN
  mv ./Output/*$RN.root ./Output/250/$RN.root
done
hadd ./Output/250GeV.root ./Output/250/*



for RN in "${Eng300[@]}"
do
  if [ "$unpack_rawFiles" = true ] ; then
      cmsRun $unpack runNumber=$RN
  fi

  cmsRun $analyse runNumber=$RN
  mv ./Output/*$RN.root ./Output/300/$RN.root
done
hadd ./Output/300GeV.root ./Output/300/*




for RN in "${Eng350[@]}"
do
  if [ "$unpack_rawFiles" = true ] ; then

      cmsRun $unpack runNumber=$RN
  fi
  cmsRun $analyse runNumber=$RN
  mv ./Output/*$RN.root ./Output/350/$RN.root
done
hadd ./Output/350GeV.root ./Output/350/*


# Adding all those runs together with HAdd to get the data for each energy....
