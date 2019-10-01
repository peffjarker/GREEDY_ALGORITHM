#ifndef MOTIF
#define MOTIF

#include <iostream>
#include <cstdlib>
using namespace std;

class Motif {
public:
  string getMotifName(const int& x) { return motifName[x]; }
  int getNumTranscriptionBindingSites(const int& x) { return numTranscriptionBindingSites[x]; }
  void setNumTranscriptionBindingSites(int& x, int& y) { numTranscriptionBindingSites[y] = x; }
  void readMotifNames(fstream& fin);
  int getMaxMotif();
private:
  string motifName[244];
  int numTranscriptionBindingSites[244];
};

#endif
