ROOTALL=`root-config --cflags --libs`


output: main.o dataExtractor.o SaturationFinder.o InitializeHist2D.o
	g++   main.o dataExtractor.o SaturationFinder.o InitializeHist2D.o -o output $(ROOTALL)

main.o: src/main.cpp include/main.h
	gcc -Iinclude  $(ROOTALL) -fpic -c  src/main.cpp

dataExtractor.o: src/dataExtractor.cc include/SaturationFinder.h src/InitializeHist2D.cc
	gcc -Iinclude $(ROOTALL) -fpic -c src/dataExtractor.cc

SaturationFinder.o: src/SaturationFinder.cc include/SaturationFinder.h
	gcc -Iinclude $(ROOTALL) -fpic -c src/SaturationFinder.cc

InitializeHist2D.o: src/InitializeHist2D.cc include/SaturationFinder.h
	gcc -Iinclude $(ROOTALL) -fpic -c src/InitializeHist2D.cc

clean:
	rm *.o output
