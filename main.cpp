#include <iostream>
#include <cstdlib>
#include <iomanip>
#include <fstream>
#include "motif.h"
#include "gene.h"
using namespace std;

int main() {

  Gene data;
  Motif names;
  fstream fin;
  fin.open("AP2.csv");                       // OPENS FILE

  if (fin.is_open()) {                       // CONFIRMS FILE OPEN
    char trash[0];                           // GETS RID OF WHITE SPACE
    fin.getline(trash, 256, ',');            // BEFORE THE SEQ NAMES
    names.readMotifNames(fin);
    data.readMotifsFoundOnGene(fin);
    int x = 0;
    for (int i = 0; i < 244; ++i) {
      data.totalMotifsFoundInGene(x, i);
      names.setNumTranscriptionBindingSites(x, i);
      cout << names.getMotifName(i) << ": " << names.getNumTranscriptionBindingSites(i) << endl;
    }

    cout << "The motif with most transcription binding sites is " << names.getMotifName(names.getMaxMotif())
         << " with " << names.getNumTranscriptionBindingSites(names.getMaxMotif()) << " binding sites." << endl;
  } else {
    cout << "Error opening file." << endl;
  }

  return 0;

}
