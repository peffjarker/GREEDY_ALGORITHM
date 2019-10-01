#include "gene.h"
#include "motif.h"
#include <fstream>
#include <iostream>
#include <cstdlib>
using namespace std;

void Gene::readMotifsOnGene(fstream& fin) {

    char dnaSeg[25];
    char motifFound[0];

    for (int j = 0; j < 10000; ++j) {
      fin.getline(dnaSeg, 256, ',');
      dnaSegment[j] = dnaSeg;
      for (int i = 0; i < 244; ++i) {
        fin.getline(motifFound, 256, ',');
        motifOnGene[i][j] = atoi(motifFound);
      }
    }
}
void Gene::totalGenesWMotif(int& x, int& y) {
  y = 0;
  for (int i = 0; i < 10000; ++i) {
    if (getMotifOnGene(x, i)) y++;
  }
}
void Gene::updateMotifsOnGene(const int& x) {
  for (int i = 0; i < 10000; ++i) {
    if (getMotifOnGene(x, i)) clearMotifsOnGene(i);
  }
}
void Gene::clearMotifsOnGene(int x) {
  for (int i = 0; i < 244; ++i) {
    clearMotifOnGene(i, x);
  }
}
