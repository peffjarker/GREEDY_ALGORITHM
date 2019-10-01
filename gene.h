#ifndef GENE
#define GENE

#include <fstream>
using namespace std;

class Gene {
public:
  void read_record();
  void readMotifsFoundOnGene(fstream& fin);
private:
  string dnaSegment[10000];
  int motifFoundOnGene[244];
};

#endif
