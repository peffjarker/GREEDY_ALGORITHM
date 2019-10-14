#include <iomanip>
#include <string>
#include "motif.h"
#include "gene.h"

/*
Main - driver function
1. Declares variables and opens input file
2. Opens input file "AP2.csv" and reads a single trash input to get to correct data
3. Reads and sets motifName[]
4. Reads and sets data for motifOnGene[][]
5. Calculates total genes covered by each motif
6. Finds motif with largest numTranscriptionBindingSites[]
7. Add that motif to the feature set
8. Output that motif name and the number of genes it covers
9. Removes that motif and the genes it covers from matrix motifOnGene[][]
10. Finds the motif with next largest numTranscriptionBindingSites
11. Checks if the next largest value is greater than delta, if true, loops back to step 7
12. If false, it outputs the total number of genes covered and exits
*/


int main() {
  void *mem = malloc(sizeof(Gene));
  Gene* data = new (mem) Gene();
  Motif names;
  void *memFin = malloc(sizeof(fstream));
  fstream* fin = new (memFin) fstream;
  int total = 0;
  int delta = 500;                            // DELTA 50/10000 = .5%
  int y = 0;                                 // USED AS A VARIABLE GENE COVERAGE IN MOTIFS
  fin -> open("training2.csv");
  if (fin -> is_open()) {                       // CONFIRMS FILE OPEN
    char trash[0];                           // GETS RID OF WHITE SPACE
    fin -> getline(trash, 256, ',');            // BEFORE THE SEQ NAMES
    names.readMotifNames(fin);               // READS AND SETS 244 MOTIF NAMES
    data -> readMotifsOnGene(fin);              // READS AND SETS DATA FOR MOTIF FEATURE
                                             // FOR ALL 10000 GENES
    for (int i = 0; i < 107; ++i) {                // Y IS INCREMENTED in totalGenesWMotif [0:10000]
      data -> totalGenesWMotif(i, y);                 // FINDS TOTAL GENES COVERED BY MOTIF[i]
      names.setNumTranscriptionBindingSites(y, i); // USES TOTAL FOUND SET FEATURE TO ALL MOTIFS
    }

    int tmpNegClasses = 0;
    int indexOfMaxMotif = 0;
    int positiveClassesFromMaxMotif = 0;

    for (int i = 0; i < 107; ++i) {
      int tmpPosClasses = 0;
      tmpNegClasses = 0;
      for (int j = 0; j < 14000; ++j) {
        if (data -> getMotifOnGene(i,j) == 1 && data -> getClassOfGene(j) == "1") {
          tmpPosClasses++;
          tmpNegClasses++;
        }
      }
      if (tmpPosClasses > positiveClassesFromMaxMotif) {
        indexOfMaxMotif = i;
        positiveClassesFromMaxMotif = tmpPosClasses;
      }
    }

    cout << names.getMotifName(indexOfMaxMotif) << " has " << positiveClassesFromMaxMotif
         << " positive classes" << " & " << tmpNegClasses << " negative classes." << endl;

    return 0;

  } else {
    // ERROR IF INPUT FILE NOT FOUND
    cout << "Error opening file." << endl;
  }
  data -> ~Gene();
  fin -> close();
  fin -> ~fstream();
  return 0;
}
