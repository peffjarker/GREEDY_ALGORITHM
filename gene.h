#ifndef GENE
#define GENE

#include <fstream>
#include <iostream>
using namespace std;

class Gene {
public:
  Gene() {
    for (int j = 0; j < 14000; ++j) {
      for (int i = 0; i < 107; ++i) {
        motifOnGene[i][j] = 0;
      }
      classOfGene[j] = "";
    }
  }
  int getMotifOnGene(const int& x, const int& y) { return motifOnGene[x][y]; }
  string getClassOfGene(const int& x) { return classOfGene[x]; }
  void updateMotifsOnGene(const int& x);
  void clearMotifsOnGene(int x);
  void clearMotifOnGene(int x, int y) { motifOnGene[x][y] = 0; }
  void readMotifsOnGene(fstream* fin);
  void totalGenesWMotif(int& x, int& y);
private:
  short motifOnGene[107][14000]; // STORES 1 AT [x][y] IF MOTIF X COVERS GENE Y
                                 // ELSE IT STORES 0 (motif X doesn't cover gene Y)
  string classOfGene[14000];     // STORES CLASS OF EACH GENE
};

#endif
