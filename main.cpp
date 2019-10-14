#include <iomanip>
#include <string>
#include "motif.h"
#include "gene.h"
#include <vector>

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

void decisionTree(vector<int> startIndex, vector<int>& outputLeft, vector<int>& outputRight, Gene* data);

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
    double tL = 0;
    double tR = 0;
    double pL = 0;
    double pR = 0;
    double posWithMotif;
    double negWithMotif;
    double posWithoutMotif;
    double negWithoutMotif;
    double pJtL = 0;
    double pJtR = 0;
    double negAbs = 0;
    double posAbs = 0;
    double summation = 0;
    double goodness = 0;
    double maxGoodness = 0;
    int indexOfMaxGoodness = 0;

    // FINDS TL AND TR OF EACH MOTIF
    for (int i = 0; i < 107; ++i) {
      tL = 0;
      tR = 0;
      posWithMotif = 0;
      negWithMotif = 0;
      posWithoutMotif = 0;
      negWithoutMotif = 0;
      negAbs = 0;
      posAbs = 0;
      summation = 0;
      goodness = 0;

      for (int j = 0; j < 14000; ++j) {
          if (data -> getMotifOnGene(i,j) == 1) {
            tL++;
            if (data -> getClassOfGene(j) == "1") {
              posWithMotif++;
            } else {
              negWithMotif++;
            }
          } else if (data -> getMotifOnGene(i,j) == 0) {
            tR++;
            if (data -> getClassOfGene(j) == "1") {
              posWithoutMotif++;
            } else {
              negWithoutMotif++;
            }
          }
      }
      pL = tL/14000;
      pR = tR/14000;
      negAbs = abs(negWithMotif/tL - negWithoutMotif/tR);
      posAbs = abs(posWithMotif/tL - posWithoutMotif/tR);
      summation = negAbs + posAbs;
      goodness = 2*(pL)*(pR)*summation;
      if (goodness > maxGoodness) {
        maxGoodness = goodness;
        indexOfMaxGoodness = i;
      }
      cout << "Motif " << i << " tL: " << tL << " tR: " << tR
           << " pL: "  << pL
           << " pR: "  << pR
           << " goodness: " << goodness
           << endl;
    }
    cout << "Max goodness: " << maxGoodness << endl;

    vector<int> leftIndex;
    vector<int> rightIndex;
    for (int j = 0; j < 14000; ++j) {
        if (data -> getMotifOnGene(indexOfMaxGoodness,j) == 1) {
          leftIndex.push_back(j);
        } else if (data -> getMotifOnGene(indexOfMaxGoodness,j) == 0) {
          rightIndex.push_back(j);
        }
    }

    for (int j = 0; j < rightIndex.size(); ++j) {
      cout << data -> getClassOfGene(rightIndex[j]);
    }

    cout << endl;
    for (int j = 0; j < leftIndex.size(); ++j) {
      cout << data -> getClassOfGene(leftIndex[j]);
    }

    vector<int> leftLeftIndex;
    vector<int> rightLeftIndex;

    decisionTree(leftIndex, leftLeftIndex, rightLeftIndex, data);

    for (int j = 0; j < rightLeftIndex.size(); ++j) {
      cout << data -> getClassOfGene(rightLeftIndex[j]);
    }

    cout << endl;
    for (int j = 0; j < leftLeftIndex.size(); ++j) {
      cout << data -> getClassOfGene(leftLeftIndex[j]);
    }



  } else {
    // ERROR IF INPUT FILE NOT FOUND
    cout << "Error opening file." << endl;
  }
  data -> ~Gene();
  fin -> close();
  fin -> ~fstream();
  return 0;
}

void decisionTree(vector<int> startIndex, vector<int>& outputLeft, vector<int>& outputRight, Gene* data) {
  double maxGoodness = 0;
  int indexOfMaxGoodness = 0;
  for (int i = 0; i < 107; ++i) {
    double tL = 0;
    double tR = 0;
    double pR = 0;
    double pL = 0;
    double posWithMotif = 0;
    double negWithMotif = 0;
    double posWithoutMotif = 0;
    double negWithoutMotif = 0;
    double negAbs = 0;
    double posAbs = 0;
    double summation = 0;
    double goodness = 0;

    for (int j = 0; j < startIndex.size(); ++j) {
        if (data -> getMotifOnGene(i,startIndex[j]) == 1) {
          tL++;
          if (data -> getClassOfGene(startIndex[j]) == "1") {
            posWithMotif++;
          } else {
            negWithMotif++;
          }
        } else if (data -> getMotifOnGene(i,startIndex[j]) == 0) {
          tR++;
          if (data -> getClassOfGene(startIndex[j]) == "1") {
            posWithoutMotif++;
          } else {
            negWithoutMotif++;
          }
        }
    }
    pL = tL/14000;
    pR = tR/14000;
    negAbs = abs(negWithMotif/tL - negWithoutMotif/tR);
    posAbs = abs(posWithMotif/tL - posWithoutMotif/tR);
    summation = negAbs + posAbs;
    goodness = 2*(pL)*(pR)*summation;
    if (goodness > maxGoodness) {
      maxGoodness = goodness;
      indexOfMaxGoodness = i;
    }
    cout << "Motif " << i << " tL: " << tL << " tR: " << tR
         << " pL: "  << pL
         << " pR: "  << pR
         << " goodness: " << goodness
         << endl;
  }

  cout << "Max goodness: " << maxGoodness << endl;
  for (int j = 0; j < 14000; ++j) {
      if (data -> getMotifOnGene(indexOfMaxGoodness,j) == 1) {
        outputLeft.push_back(j);
      } else if (data -> getMotifOnGene(indexOfMaxGoodness,j) == 0) {
        outputRight.push_back(j);
      }
  }
}
