Code to Study Gain Switching in HGCal detector.

Create NTuples using the HGCalTB Framework ( by using the ntuples created by HGCalTB framework here:https://github.com/CMS-HGCAL/TestBeam/blob/CERN_TestBeam_2017_Ipbus/Reco/plugins/RecHitsNtuplizer.cc )


---------------
Old Notes... Readme needs to be updated!
---------------

Once you have them, hadd the NTuples to create All.root file with energy file of both Electron and Pion runs.

Then you can create a pointer to SaturationFinder that can call methods defined in ./include/SaturationFinder.h and use them to manipulate data and find the desired values.


In the constructor you have to set the fit name and number of boards along with the folder in which you have your NTuples stored.

SaturationFinder( Total_Boards,0,"All","FIT_NAME or Prefix","rootFolder");


These are the methods you have to call to get the final data

1) dataExtractor -> Loads the necessary 2D Histograms  to memory from NTuples (Check this file for fill criteria)

Check InitializeHist2D.cc file to set  the binning  of the Histogram.

2) SaveHistogram/LoadHistogram -> Once you have loaded 2D Histogram from memory, use this to save those select Histograms to root files which are faster to access. After you save once, you can skip running dataExtractor unless you want to change the binning.

3) FitHistogram will take the TProfile and fit those function. Fit Function is defined here...

4)FindValues method will find the saturation values and conversion factors and load them to the corresponding arrays which are public arrays.

5) StoreValues/RetrieveValues will save/load those saturation values and conversion factors into text file.

6) FixAllValues(int type_num) will fix the values which are too far from the mean. Check ./src/FixAllValues.cc for more info. You have to do it for both HG->LG and LG->Total.  Set argument as 0 for HG_LG and set it to 1 for LG_TOT.

7) You can store it into a different file by changing the rootfolder name.

For working example take a look at run_me.C.

Once you have set your rootFolder which contains the NTuples, run it as "root -l run_me.C", this should create the files in ./temp_data. Make sure such a folder exists before running the programme.

NOTE: Don't  set gROOT->SetBatch(kTRUE) to gROOT->SetBatch(kFALSE). Especially when you are using methods such as  FitHistogram and FindValues. This will try to draw all the 70 Histograms on your display. Do not comment it out either.
