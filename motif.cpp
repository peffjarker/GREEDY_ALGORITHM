#include "motif.h"
#include <fstream>
#include <iostream>
#include <cstdlib>
using namespace std;

void Motif::readMotifNames(fstream& fin) {
    char tempMotifName[244];                   // TEMP STORAGE FOR MOTIF NAME
    for (int i = 0; i < 244; ++i) {           // STORES 244 MOTIF NAMES
        fin.getline(tempMotifName, 256, ','); // READS AND STORES IN TEMP STORAGE
        motifName[i] = tempMotifName;         // TRANSFERS FROM TEMP TO CLASS DATA
    }
}
int Motif::getMaxMotif() {
  int indexOfMax = 0;
  int maxNum;
  for (int i = 0; i < 244; ++i) {
    if (getNumTranscriptionBindingSites(i) > getNumTranscriptionBindingSites(indexOfMax)) {
      indexOfMax = i;
      maxNum = getNumTranscriptionBindingSites(i);
    }
  }
  return indexOfMax;
}
void Motif::updateBindingSites(const int& x) {
  setNumTranscriptionBindingSites(0, x);
}
