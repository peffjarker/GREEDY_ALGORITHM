#ifndef MOTIF
#define MOTIF

#include <iostream>
#include <cstdlib>
using namespace std;

class Motif {
public:
  void readMotifNames(fstream& fin);
private:
  string motifName[244];
  int numTranscriptionBindingSites;
};

#endif
