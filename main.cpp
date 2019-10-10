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
7. Add that motif to the coverage set
8. Output that motif name and the number of genes it covers
9. Removes
*/

int main() {

  Gene data;
  Motif names;
  fstream fin;
  string setCover;
  int indexOfMaxMotif;
  int total = 0;
  int delta = 50;                            // DELTA 50/10000 = .5%
  int y = 0;
  fin.open("AP2.csv");                       // OPENS FILE

  if (fin.is_open()) {                       // CONFIRMS FILE OPEN
    char trash[0];                           // GETS RID OF WHITE SPACE
    fin.getline(trash, 256, ',');            // BEFORE THE SEQ NAMES
    names.readMotifNames(fin);               // READS AND SETS 244 MOTIF NAMES
    data.readMotifsOnGene(fin);              // READS AND SETS DATA FOR MOTIF COVERAGE
                                             // FOR ALL 10000 GENES
    for (int i = 0; i < 244; ++i) {                // Y IS INCREMENTED in totalGenesWMotif [0:10000]
      data.totalGenesWMotif(i, y);                 // FINDS TOTAL GENES COVERED BY MOTIF[i]
      names.setNumTranscriptionBindingSites(y, i); // USES TOTAL FOUND SET COVERAGE TO ALL MOTIFS
    }
    do {
      // END CASE: IF THERE IS NOT A MOTIF THAT COVERS MORE THAN THE DELTA
      // (in this case delta = 50), IT OUTPUTS THE FINAL RESULTS AND EXITS
      if (names.getNumTranscriptionBindingSites(names.getMaxMotif()) < delta) {
        cout << "\nThe total number of genes covered is " << total << endl;
        return 0;
      } else {
        // THERE IS A MOTIF THAT COVERS MORE THAN DELTA
        // THE PROGRAM ADDS COVERAGE OF REMAINING GENES FOR THAT MOTIF
        // OUTPUTS WHICH MOTIF AND THE NUMBER OF REMAINING GENES IT COVERS
        total += names.getNumTranscriptionBindingSites(names.getMaxMotif());
        cout << names.getMotifName(names.getMaxMotif()) << " covers: "
             << names.getNumTranscriptionBindingSites(names.getMaxMotif())
             << " genes" << endl;
        // AFTER MOTIF IS OUTPUTTED, THAT MOTIF AND GENE NEED TO BE REMOVED
        // FROM CONSIDERATION, THE FOLLOWING TWO FUNCTIONS CLEAR EXISTING DATA
        // FOR MOTIFS THAT WERE ADDED TO THE COVERAGE SET AND THE GENES THOSE
        // MOTIFS COVER
        data.updateMotifsOnGene(names.getMaxMotif());
        names.updateBindingSites(names.getMaxMotif());
        for (int i = 0; i < 244; ++i) {
          // RECALCULATES THE MOTIF COVERAGE (not including motif added to
          // coverage set and genes covered by that motif) AND SETS numTranscriptionBindingSites
          data.totalGenesWMotif(i, y);
          names.setNumTranscriptionBindingSites(y, i);
        }
      }
    } while(1); // THIS WHILE LOOP RUNS UNTIL IT IS RETURNED INTERALLY
  } else {
    // ERROR IF INPUT FILE NOT FOUND
    cout << "Error opening file." << endl;
  }
  fin.close();
  return 0;
}
