#include "gene.h"
#include "motif.h"
#include <fstream>
#include <iostream>
#include <cstdlib>
using namespace std;

void Gene::readMotifsFoundOnGene(fstream& fin) {

    char dnaSeg[25];
    char motifFound[0];

    for (int j = 0; j < 10000; ++j) {
      fin.getline(dnaSeg, 256, ',');
      dnaSegment[j] = dnaSeg;
      for (int i = 0; i < 244; ++i) {
        fin.getline(motifFound, 256, ',');
        motifFoundOnGene[i][j] = atoi(motifFound);
      }
    }
}
int Gene::totalMotifsFoundInGene(int& x, int& y) {
  x = 0;
  for (int i = 0; i < 10000; ++i) {
    if (isMotifFoundOnGene(i, y)) x++;
  }
}
