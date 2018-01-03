ROOTALL=`root-config --cflags --libs`


output: run_me.o dataExtractor.o SaturationFinder.o InitializeHist2D.o FitHistogram.o FindValues.o Save_Load_Hist.o Store_Retrieve.o Graph_Settings.o
	g++   run_me.o dataExtractor.o SaturationFinder.o InitializeHist2D.o FitHistogram.o FindValues.o Save_Load_Hist.o Store_Retrieve.o Graph_Settings.o -o output $(ROOTALL)

run_me.o: ./run_me.C include/SaturationFinder.h
	gcc -Iinclude  $(ROOTALL) -fpic -c  ./run_me.C

dataExtractor.o: src/dataExtractor.cc include/SaturationFinder.h src/InitializeHist2D.cc
	gcc -Iinclude $(ROOTALL) -fpic -c src/dataExtractor.cc

SaturationFinder.o: src/SaturationFinder.cc include/SaturationFinder.h
	gcc -Iinclude $(ROOTALL) -fpic -c src/SaturationFinder.cc

InitializeHist2D.o: src/InitializeHist2D.cc include/SaturationFinder.h
	gcc -Iinclude $(ROOTALL) -fpic -c src/InitializeHist2D.cc

FitHistogram.o: src/FitHistogram.cc include/SaturationFinder.h
	gcc -Iinclude $(ROOTALL) -fpic -c src/FitHistogram.cc

FindValues.o: src/FindValues.cc include/SaturationFinder.h
		gcc -Iinclude $(ROOTALL) -fpic -c src/FindValues.cc

Save_Load_Hist.o: src/Save_Load_Hist.cc include/SaturationFinder.h
		gcc -Iinclude $(ROOTALL) -fpic -c src/Save_Load_Hist.cc

Store_Retrieve.o: src/Store_Retrieve.cc include/SaturationFinder.h
		gcc -Iinclude $(ROOTALL) -fpic -c src/Store_Retrieve.cc

Graph_Settings.o: src/Graph_Settings.cc include/SaturationFinder.h
		gcc -Iinclude $(ROOTALL) -fpic -c src/Graph_Settings.cc



clean:
	rm *.o output
