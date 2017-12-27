#include<iostream>
#include "SaturationFinder.h"

void run_me()
{
  SaturationFinder* a = new SaturationFinder(20);

  a->dataExtractor(80,"Electron");

  return;
}
