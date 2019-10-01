#ifndef GENE
#define GENE

#include <fstream>
using namespace std;

class Gene {
public:
  void readMotifsFoundOnGene(fstream& fin);
  int totalMotifsFoundInGene(int& x, int& y);
  bool isMotifFoundOnGene(const int& i, const int& y) { return motifFoundOnGene[y][i]; }
private:
  string dnaSegment[10000];
  short motifFoundOnGene[244][10000];
};

#endif
