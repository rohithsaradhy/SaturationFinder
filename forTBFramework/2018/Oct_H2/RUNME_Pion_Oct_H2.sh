#!/bin/bash
#Shell script to repeat the runs for Oct runs for Pion
#Written by Rohith Saradhy

Eng100=(1535 1536 1537 1573 1574 1577 1578 1579 1580 1581 1582 1583 1584 1585)

Eng150=(1538 1539 1540 1541 1542 1543 1544 1545 1546 1547 1548 1549 1550 1551)

Eng200=(1602 1603 1604 1605 1606 1607 1608 1609 1610 1611 1613 1614 1615) #//Ign-> 113,114

Eng250=(1535 1552 1553 1554 1555 1556 1557 1558 1559 1560 1563 1564 1565 1566 1567 1587 1588 1589 1590 1593 1594 1595 1596 1597)

Eng300=(1618 1619 1620 1621 1622 1623 1624 1626 1627 1628 1629 1630)

Eng350=(1500 1501 1502 1503 1504 1505 1506 1507 1508 1509 1510 1511)





#unpacker configuration files
unpack="unpack2017_LaterRuns_cfg.py"
#rawhit analyser configuration files
analyse="rawhitprod_Oct_H2.py"
# analyse="rawhitprod2017_cfg.py"
output="./Output/H2/Pion" # Make sure that in the analyse file the Output is set to ./Output/H2/

# Making the directories to keep the individual files...
mkdir -p $output/100
mkdir -p $output/150
mkdir -p $output/200
mkdir -p $output/250
mkdir -p $output/300
mkdir -p $output/350


#unpack the files if true. Otherwise just get them through the analyser....
unpack_rawFiles=false

if [ "$unpack_rawFiles" = true ] ; then
    echo -e "Unpacking is Switched On... \n"
  else
    echo -e "Unpacking is Switched Off... \n"
fi


# for RN in "${Eng100[@]}"
# do
#   if [ "$unpack_rawFiles" = true ] ; then
#       cmsRun $unpack runNumber=$RN
#   fi
#   cmsRun $analyse runNumber=$RN
#   mv $output/../*$RN.root $output/100/$RN.root
# done
# hadd $output/100GeV.root $output/100/*
#
#
# for RN in "${Eng150[@]}"
# do
#   if [ "$unpack_rawFiles" = true ] ; then
#       cmsRun $unpack runNumber=$RN
#   fi
#   cmsRun $analyse runNumber=$RN
#   mv $output/../*$RN.root $output/150/$RN.root
# done
#
#
# for RN in "${Eng200[@]}"
# do
#   if [ "$unpack_rawFiles" = true ] ; then
#       cmsRun $unpack runNumber=$RN
#   fi
#   cmsRun $analyse runNumber=$RN
#   mv $output/../*$RN.root $output/200/$RN.root
# done
#
#
# for RN in "${Eng250[@]}"
# do
#   if [ "$unpack_rawFiles" = true ] ; then
#       cmsRun $unpack runNumber=$RN
#   fi
#   cmsRun $analyse runNumber=$RN
#   mv $output/../*$RN.root $output/250/$RN.root
# done



for RN in "${Eng300[@]}"
do
  if [ "$unpack_rawFiles" = true ] ; then
      cmsRun $unpack runNumber=$RN
  fi

  cmsRun $analyse runNumber=$RN
  mv $output/../*$RN.root $output/300/$RN.root
done


for RN in "${Eng350[@]}"
do
  if [ "$unpack_rawFiles" = true ] ; then

      cmsRun $unpack runNumber=$RN
  fi
  cmsRun $analyse runNumber=$RN
  mv $output/../*$RN.root $output/350/$RN.root
done


# Adding all those runs together with HAdd to get the data for each energy....
hadd -f $output/150GeV.root $output/150/*
hadd -f $output/200GeV.root $output/200/*
hadd -f $output/250GeV.root $output/250/*
hadd -f $output/300GeV.root $output/300/*
hadd -f $output/350GeV.root $output/350/*
