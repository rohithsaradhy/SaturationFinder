
#include "main.h"
#include "SaturationFinder.h"

using namespace std;


int main()
{
  SaturationFinder* a = new SaturationFinder(20);

  a->dataExtractor(80,"Electron");


  return 0;


}
