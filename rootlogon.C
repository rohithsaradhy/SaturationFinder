//Setting up all the environment for the LoadMacro running....
{
	gROOT->ProcessLine(".include ./include/");
	gROOT->LoadMacro("src/dataExtractor.cc");
	gROOT->LoadMacro("src/SaturationFinder.cc");
	gROOT->LoadMacro("src/InitializeHist2D.cc");
	gROOT->LoadMacro("src/LoadHistogram.cc");
	gROOT->LoadMacro("src/SaveHistogram.cc");
	gROOT->LoadMacro("src/FitHistogram.cc");
	gROOT->LoadMacro("src/FindValues.cc");
	gROOT->LoadMacro("src/Graph_Settings.cc");





}
