#include <iostream>
#include <cstdlib>
#include <iomanip>
#include <fstream>
using namespace std;

class Motif {
public:
  void readMotifNames(fstream& fin) {
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
  void readTranscriptionBindingSites(fstream& fin) {

  }
private:
  string motifNames[244];                       // STORES 244 MOTIF SEQ NAMES
  int numTranscriptionBindingSites[10000];
};

class Gene {
public:
  string getDnaSegment() { return dnaSegment; }
  void read_record() {

    // Create file pointer object
    fstream fin;

    Motif motifNames;
    motifNames.readMotifNames(fin);
    readMotifsFoundOnGene(fin);

  }
  void readMotifsFoundOnGene(fstream& fin) {

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
        dnaSegment = dnaSeg;
        char motifFound[0];
        cout << dnaSegment << endl;

        for (int i = 0; i < 244; ++i) {
          fin.getline(motifFound, 256, ',');
          motifFoundOnGene[i] = atoi(motifFound);
          cout << motifFoundOnGene[i];
        }
      }
      fin.close();

    } else {

      cout << "Error opening file.";

    }
};
private:
  string dnaSegment;
  int motifFoundOnGene[244];
};

int main() {

  Gene genes;

  genes.read_record();

  return 0;

}

void read_record() {



}
