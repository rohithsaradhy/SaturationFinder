//Setting up all the environment for the LoadMacro running....
{
	gROOT->ProcessLine(".include ./include/");
	gROOT->LoadMacro("src/dataExtractor.cc");
	gROOT->LoadMacro("src/SaturationFinder.cc");
	gROOT->LoadMacro("src/InitializeHist2D.cc");

}
