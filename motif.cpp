#include "motif.h"
#include <fstream>
#include <iostream>
#include <cstdlib>
using namespace std;

void Motif::readMotifNames(fstream& fin) {
  fin.open("AP2.csv");                        // OPENS FILE
  if (fin.is_open()) {                        // CONFIRMS FILE OPEN
    char trash[0];                            // GETS RID OF WHITE SPACE
    fin.getline(trash, 256, ',');             // BEFORE THE SEQ NAMES
    for (int i = 0; i < 244; ++i) {           // STORES 244 MOTIF NAMES
        char tempMotifName[244];              // TEMP STORAGE FOR MOTIF NAME
        fin.getline(tempMotifName, 256, ','); // READS AND STORES IN TEMP STORAGE
        motifNames[i] = tempMotifName;        // TRANSFERS FROM TEMP TO CLASS DATA
    }
    fin.close();                              // MOTIF NAMES READ FIN CLOSED
  } else {
    cout << "Error opening file.";            // FILE NOT OPEN CORRECTLY
  }
}
