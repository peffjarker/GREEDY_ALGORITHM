#ifndef GENE
#define GENE

#include <fstream>
#include <iostream>
using namespace std;

class Gene {
public:
  string getDnaSegment(const int& x) { return dnaSegment[x]; }
  int getMotifOnGene(const int& x, const int& y) { return motifOnGene[x][y]; }
  void updateMotifsOnGene(const int& x);
  void clearMotifsOnGene(int x);
  void clearMotifOnGene(int x, int y) { motifOnGene[x][y] = 0; }
  void readMotifsOnGene(fstream& fin);
  void totalGenesWMotif(int& x, int& y);
private:
  string dnaSegment[10000];
  short motifOnGene[244][10000];
};

#endif
