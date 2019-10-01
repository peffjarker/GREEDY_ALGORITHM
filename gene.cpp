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
      cout << dnaSeg << endl;
      for (int i = 0; i < 244; ++i) {
        fin.getline(motifFound, 256, ',');
        motifFoundOnGene[i][j] = atoi(motifFound);
        cout << motifFoundOnGene[i][j];
      }
      cout << endl;
    }
}
