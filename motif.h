#ifndef MOTIF
#define MOTIF

#include <iostream>
#include <cstdlib>
using namespace std;

class Motif {
public:
  void readMotifNames(fstream& fin);
private:
  string motifNames[244];
  int numTranscriptionBindingSites[244];
};

#endif
