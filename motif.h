#ifndef MOTIF
#define MOTIF

#include <cstdlib>
#include <fstream>
using namespace std;

class Motif {
public:
  string getMotifName(const int& x) { return motifName[x]; }
  int getNumTranscriptionBindingSites(const int& x) { return numTranscriptionBindingSites[x]; }
  void setNumTranscriptionBindingSites(const int& x, const int& y) { numTranscriptionBindingSites[y] = x; }
  void readMotifNames(fstream& fin);
  int getMaxMotif();
  void updateBindingSites(const int& x);
private:
  string motifName[244];                 // STORES 244 MOTIF NAMES
  int numTranscriptionBindingSites[244]; // STORES NUMBER OF GENES COVERED BY [] MOTIF
};

#endif
