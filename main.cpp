#include <iostream>
#include <cstdlib>
#include <iomanip>
#include <fstream>
#include <string>
#include "motif.h"
#include "gene.h"
using namespace std;

int main() {

  Gene data;
  Motif names;
  fstream fin;
  string setCover;
  int indexOfMaxMotif;
  int total = 0;
  fin.open("AP2.csv");                       // OPENS FILE

  if (fin.is_open()) {                       // CONFIRMS FILE OPEN
    char trash[0];                           // GETS RID OF WHITE SPACE
    fin.getline(trash, 256, ',');            // BEFORE THE SEQ NAMES
    names.readMotifNames(fin);
    data.readMotifsOnGene(fin);

  int y = 0;
  for (int i = 0; i < 244; ++i) {
    data.totalGenesWMotif(i, y);
    names.setNumTranscriptionBindingSites(y, i);
  }

  do {
    if (names.getNumTranscriptionBindingSites(names.getMaxMotif()) == 0) {
      return 0;
    } else {
      total += names.getMaxMotif();
      cout << "Motif " << names.getMotifName(names.getMaxMotif()) << " covers "
           << names.getNumTranscriptionBindingSites(names.getMaxMotif())
           << " genes." << endl;
      data.updateMotifsOnGene(names.getMaxMotif());
      names.updateBindingSites(names.getMaxMotif());
      for (int i = 0; i < 244; ++i) {
        data.totalGenesWMotif(i, y);
        names.setNumTranscriptionBindingSites(y, i);
      }
    }
  } while(1);

  } else {

    cout << "Error opening file." << endl;

  }

  fin.close();
  return 0;

}
