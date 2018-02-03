#!/bin/bash
#Shell script to repeat the runs for Oct runs for Pion
#Written by Rohith Saradhy

Eng50=(1998 1999 2000 2001 2002 2003 2004 2005 2006 2007 2008 2009 2010 2011 2012 2013 2014 2015 1915 1916 1917 1918 1919 1892 1893 1894 1895)

Eng100=(1988 1989 1990 1991 1992 1993 1994 1995 1996 1997 1877 1878 1879 1881 1882 1883 1884 1885 1886 1887 1888 1889 1890)

Eng120=(1977 1978 1979 1980 1981 1982 1983 1984 1985 1986 1987 1902 1903 1904 1905 1906 1907 1908 1909 1910 1911 1912 1913 1830 1831 1832 1833 1834 1835 1836 1837 1838 1839 1840 1841 1842 1843 1844 1845 1846 1847 1848 1849 1850)

# Eng150=()
#
# Eng200=()
#
# Eng250=()
#
# Eng300=()
#
# Eng350=()



# Making the directories to keep the individual files...
mkdir ./Output/50
mkdir ./Output/100
mkdir ./Output/120
# mkdir ./Output/150
# mkdir ./Output/200
# mkdir ./Output/250
# mkdir ./Output/300
# mkdir ./Output/350


#unpacker configuration files
unpack="unpack2017_LaterRuns_cfg.py"
#rawhit analyser configuration files
# analyse="rawhitprod2017_cfg_analyseTHEM.py"
analyse="rawhitprod2017_cfg_analyseTHEM.py"



#unpack the files if true. Otherwise just get them through the analyser....
unpack_rawFiles=false

if [ "$unpack_rawFiles" = true ] ; then
    echo -e "Unpacking is Switched On... \n"
fi

for RN in "${Eng50[@]}"
do
  if [ "$unpack_rawFiles" = true ] ; then
      cmsRun $unpack runNumber=$RN
  fi
  cmsRun $analyse runNumber=$RN
  mv ./Output/*$RN.root ./Output/50/$RN.root
done
hadd ./Output/50GeV.root ./Output/50/*


for RN in "${Eng100[@]}"
do
  if [ "$unpack_rawFiles" = true ] ; then
      cmsRun $unpack runNumber=$RN
  fi
  cmsRun $analyse runNumber=$RN
  mv ./Output/*$RN.root ./Output/100/$RN.root
done
hadd ./Output/100GeV.root ./Output/100/*

for RN in "${Eng120[@]}"
do
  if [ "$unpack_rawFiles" = true ] ; then
      cmsRun $unpack runNumber=$RN
  fi
  cmsRun $analyse runNumber=$RN
  mv ./Output/*$RN.root ./Output/120/$RN.root
done
hadd ./Output/120GeV.root ./Output/120/*



# for RN in "${Eng150[@]}"
# do
#   if [ "$unpack_rawFiles" = true ] ; then
#       cmsRun $unpack runNumber=$RN
#   fi
#   cmsRun $analyse runNumber=$RN
#   mv ./Output/*$RN.root ./Output/150/$RN.root
# done
# hadd ./Output/150GeV.root ./Output/150/*
#
#
# for RN in "${Eng200[@]}"
# do
#   if [ "$unpack_rawFiles" = true ] ; then
#       cmsRun $unpack runNumber=$RN
#   fi
#   cmsRun $analyse runNumber=$RN
#   mv ./Output/*$RN.root ./Output/200/$RN.root
# done
# hadd ./Output/200GeV.root ./Output/200/*
#
#
# for RN in "${Eng250[@]}"
# do
#   if [ "$unpack_rawFiles" = true ] ; then
#       cmsRun $unpack runNumber=$RN
#   fi
#   cmsRun $analyse runNumber=$RN
#   mv ./Output/*$RN.root ./Output/250/$RN.root
# done
# hadd ./Output/250GeV.root ./Output/250/*
#
#
#
# for RN in "${Eng300[@]}"
# do
#   if [ "$unpack_rawFiles" = true ] ; then
#       cmsRun $unpack runNumber=$RN
#   fi
#
#   cmsRun $analyse runNumber=$RN
#   mv ./Output/*$RN.root ./Output/300/$RN.root
# done
# hadd ./Output/300GeV.root ./Output/300/*
#
#
#
#
# for RN in "${Eng350[@]}"
# do
#   if [ "$unpack_rawFiles" = true ] ; then
#
#       cmsRun $unpack runNumber=$RN
#   fi
#   cmsRun $analyse runNumber=$RN
#   mv ./Output/*$RN.root ./Output/350/$RN.root
# done
# hadd ./Output/350GeV.root ./Output/350/*


# Adding all those runs together with HAdd to get the data for each energy....


mkdir./Output/Pions
mv  ./Output/* ./Output/Pions
