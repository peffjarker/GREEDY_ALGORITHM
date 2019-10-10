#include "gene.h"
#include "motif.h"

// READS THE MOTIFS FOUND ON EACH GENE FROM INPUT AND STORES INTO
// motifOnGene[i][j]
void Gene::readMotifsOnGene(fstream& fin) {

    char dnaSeg[25];
    char motifFound[0];

    for (int j = 0; j < 10000; ++j) {         // RUNS FOR 10000 LINES OF INPUT
      fin.getline(dnaSeg, 256, ',');
      dnaSegment[j] = dnaSeg;
      for (int i = 0; i < 244; ++i) {         // CHECK 244 MOTIFS ON jth LINE OF INPUT
        fin.getline(motifFound, 256, ',');
        motifOnGene[i][j] = atoi(motifFound); // CONVERTS CH ARRAY TO INT, SETS MATRIX
      }
    }
}
// FINDS THE NUMBER OF GENES COVERED BY EACH MOTIF
void Gene::totalGenesWMotif(int& x, int& y) {
  y = 0;
  for (int i = 0; i < 10000; ++i) {
    if (getMotifOnGene(x, i)) y++;
  }
}
// FUNCTION IS GIVEN A MOTIF, X THEN CHECKS ALL GENES FOR THAT MOTIF at motifOnGene[x][i]
// IF VALUE IS 1, IT CALLS clearMotifOnGene(i)
void Gene::updateMotifsOnGene(const int& x) {
  for (int i = 0; i < 10000; ++i) {
    if (getMotifOnGene(x, i)) clearMotifsOnGene(i);
  }
}
// THIS FUNCTION WORKS WITH updateMotifsOnGene(x) WHEN A SPECIFIC MOTIF COVERS A
// GENE. WHEN THIS FUNCTION IS CALLED THE MOTIFS ON A GENE ARE ALL SET TO 0 TO
// REMOVE IT FROM POSSIBILITY FOR THE NEXT MOTIF WITH MAX COVERAGE
void Gene::clearMotifsOnGene(int x) {
  for (int i = 0; i < 244; ++i) {
    clearMotifOnGene(i, x);
  }
}
