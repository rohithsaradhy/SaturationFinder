#!/bin/bash
#Shell script to repeat the runs for Oct runs for Pion
#Written by Rohith Saradhy

Eng50=(1998 1999 2000 2001 2002 2003 2004 2005 2006 2007 2008 2009 2010 2011 2012 2013 2014 2015 1915 1916 1917 1918 1919 1892 1893 1894 1895)

Eng100=(1988 1989 1990 1991 1992 1993 1994 1995 1996 1997 1877 1878 1879 1881 1882 1883 1884 1885 1886 1887 1888 1889 1890)

Eng120=(1977 1978 1979 1980 1981 1982 1983 1984 1985 1986 1987 1902 1903 1904 1905 1906 1907 1908 1909 1910 1911 1912 1913 1830 1831 1832 1833 1834 1835 1836 1837 1838 1839 1840 1841 1842 1843 1844 1845 1846 1847 1848 1849 1850)






#unpacker configuration files
unpack="unpack2017_LaterRuns_cfg.py"
#rawhit analyser configuration files
# analyse="rawhitprod2017_cfg_analyseTHEM.py"
analyse="rawhitprod_Oct_H6.py"
output="./Output/H6/Pion" # Make sure that in the analyse file the Output is set to ./Output/H6/


# Making the directories to keep the individual files...
mkdir -p $output/50
mkdir -p $output/100
mkdir -p $output/120


#unpack the files if true. Otherwise just get them through the analyser....
unpack_rawFiles=false

if [ "$unpack_rawFiles" = true ] ; then
    echo -e "Unpacking is Switched On... \n"
  else
    echo -e "Unpacking is Switched Off... \n"
fi

for RN in "${Eng50[@]}"
do
  if [ "$unpack_rawFiles" = true ] ; then
      cmsRun $unpack runNumber=$RN
  fi
  cmsRun $analyse runNumber=$RN
  mv $output/../*$RN.root $output/50/$RN.root
done


for RN in "${Eng100[@]}"
do
  if [ "$unpack_rawFiles" = true ] ; then
      cmsRun $unpack runNumber=$RN
  fi
  cmsRun $analyse runNumber=$RN
  mv $output/../*$RN.root $output/100/$RN.root
done

for RN in "${Eng120[@]}"
do
  if [ "$unpack_rawFiles" = true ] ; then
      cmsRun $unpack runNumber=$RN
  fi
  cmsRun $analyse runNumber=$RN
  mv $output/../*$RN.root $output/120/$RN.root
done



# Adding all those runs together with HAdd to get the data for each energy....

hadd -f $output/50GeV.root $output/50/*
hadd -f $output/100GeV.root $output/100/*
hadd -f $output/120GeV.root $output/120/*
