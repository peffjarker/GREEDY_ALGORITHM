#ifndef GENE
#define GENE

#include <fstream>
using namespace std;

class Gene {
public:
  void read_record();
  void readMotifsFoundOnGene(fstream& fin);
private:
  short motifFoundOnGene[244][10000];
};

#endif
