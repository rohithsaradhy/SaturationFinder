//Setting up all the environment for the LoadMacro running....
{
	gROOT->ProcessLine(".include ./include/");
	gROOT->LoadMacro("src/dataExtractor.cc");
	gROOT->LoadMacro("src/SaturationFinder.cc");
	gROOT->LoadMacro("src/InitializeHist2D.cc");
	gROOT->LoadMacro("src/Save_Load_Hist.cc");
	gROOT->LoadMacro("src/Store_Retrieve.cc");
	gROOT->LoadMacro("src/FitHistogram.cc");
	gROOT->LoadMacro("src/FindValues.cc");
	gROOT->LoadMacro("src/Graph_Settings.cc");
	gROOT->LoadMacro("src/FixAllValues.cc");
	gROOT->LoadMacro("src/CollectFromNTuples.cc");





}
