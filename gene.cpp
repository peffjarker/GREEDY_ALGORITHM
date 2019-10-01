#include "gene.h"
#include "motif.h"
#include <fstream>
#include <iostream>
#include <cstdlib>
using namespace std;

void Gene::read_record() {
  // Create file pointer object
  fstream fin;

  Motif motifNames;
  motifNames.readMotifNames(fin);
  readMotifsFoundOnGene(fin);
}
void Gene::readMotifsFoundOnGene(fstream& fin) {

  fin.open("AP2.csv");                       // OPENS FILE

  if (fin.is_open()) {                       // CONFIRMS FILE OPEN
    char trash[0];                           // GETS RID OF WHITE SPACE
    fin.getline(trash, 256, ',');            // BEFORE THE SEQ NAMES

    for (int i = 0; i < 244; ++i) {
      char tempMotifName[244];              // TEMP STORAGE FOR MOTIF NAME
      fin.getline(tempMotifName, 256, ','); // READS AND STORES IN TEMP STORAGE
    }

    for (int j = 0; j < 10000; ++j) {
      char dnaSeg[25];
      fin.getline(dnaSeg, 256, ',');
      dnaSegment[j] = dnaSeg;
      char motifFound[0];
      cout << dnaSegment[j] << endl;

      for (int i = 0; i < 244; ++i) {
        fin.getline(motifFound, 256, ',');
        motifFoundOnGene[j][i] = atoi(motifFound);
        cout << motifFoundOnGene[i];
      }
    }
    fin.close();

  } else {

    cout << "Error opening file.";

  }
};
