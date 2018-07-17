#!/usr/bin/python
#Cdoe to return the runs and for files with run numbers...

import sys
import ROOT
from collections import defaultdict

Data=defaultdict(list)
RUN_FILE_CSV="./CERN_Beam_test_6_18_June_2018_Run_Summary.csv"




def conditionOne(run): #Condition on  changed Skiroc Gain
    if run <= 455 and run >=419:
        return False
    else:
        return True

def writeForPresentatation(data_in, nameOfFile=None): #input data as dictionary of list
    for key in data_in:
        print data_in[key]





file=open(RUN_FILE_CSV)
linesInFile = file.readlines()



def get_Runs():
    for line in linesInFile:
        Run_No = line.split(",")[1]
        Events = line.split(",")[2]
        Run_Type =line.split(",")[5]
        Particle = line.split(",")[7]
        Energy=line.split(",")[9]
        if Run_No!="" and Events!="": #Run Number has to be specified and there should be some events
            try:
                if (conditionOne(Run_No)) and (Particle == "Electrons" or Particle == "Muons" ) and (int(Events) > 1000) and Run_Type=="Beam":
                    Data[Particle+"_"+Energy+"GeV"].append(Run_No)
                    nameFile ="./runs/"+Particle+"_"+Energy+"GeV"+".run"
                    out_file = open(nameFile,"a")
                    print Run_No + " was included in "+Particle+"_"+Energy+"GeV"+".run"
                    out_file.write(Run_No+"\n")
                    out_file.close()
                    ### All Particles
                    nameFile ="./runs/All_"+Particle+".run"
                    out_file = open(nameFile,"a")
                    print Run_No + " was included in All_"+Particle+".run"
                    out_file.write(Run_No+"\n")
                    out_file.close()


            except:
                    print "$$$$$$$$$$$$$$$$"
                    print "This Line was rejected because of some reason, check the values below"
                    print "Run No:\t" + Run_No
                    print "Events:\t"+Events
                    print "Run Type:\t"+ Run_Type
                    print "Particle:\t"+Particle
                    print "Energy(GeV):\t"+Energy
                    print "$$$$$$$$$$$$$$$$"
                    print






if __name__== "__main__":
  get_Runs();
  #write in a format for presentation...
  # writeForPresentatation(Data)
