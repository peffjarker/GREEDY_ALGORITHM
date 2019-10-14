#include "motif.h"

// READS THE MOTIF NAMES FROM INPUT AND STORES THEM INTO motifName[i]
void Motif::readMotifNames(fstream* fin) {
    char tempMotifName[107];                  // TEMP STORAGE FOR MOTIF NAME
    for (int i = 0; i < 107; ++i) {           // STORES 244 MOTIF NAMES
        fin -> getline(tempMotifName, 256, ','); // READS AND STORES IN TEMP STORAGE
        motifName[i] = tempMotifName;         // TRANSFERS FROM TEMP TO CLASS DATA
    }
}
// RETURNS THE INDEX OF THE MAX MOTIF
int Motif::getMaxMotif() {
  int indexOfMax = 0;
  int maxNum;
  for (int i = 0; i < 107; ++i) {
    if (getNumTranscriptionBindingSites(i) > getNumTranscriptionBindingSites(indexOfMax)) {
      indexOfMax = i;
      maxNum = getNumTranscriptionBindingSites(i);
    }
  }
  return indexOfMax;
}
// CLEARS THE NUMBER OF BINDING SITES FOR A MOTIF (called after motif is added
// to coverage set.)
void Motif::updateBindingSites(const int& x) {
  setNumTranscriptionBindingSites(0, x);
}
