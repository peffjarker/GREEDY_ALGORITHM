#include <iomanip>
#include <string>
#include "motif.h"
#include "gene.h"
#include <vector>
#include <numeric>
#include <map>
/*
Main - driver function
1. Declares variables and opens input file
2. Opens input file "AP2.csv" and reads a single trash input to get to correct data
3. Reads and sets motifName[]
4. Reads and sets data for motifOnGene[][]
5. Calculates total genes covered by each motif
6. Finds motif with largest numTranscriptionBindingSites[]
7. Add that motif to the feature set
8. Output that motif name and the number of genes it covers
9. Removes that motif and the genes it covers from matrix motifOnGene[][]
10. Finds the motif with next largest numTranscriptionBindingSites
11. Checks if the next largest value is greater than delta, if true, loops back to step 7
12. If false, it outputs the total number of genes covered and exits
*/

void decisionTree(vector<int>& startIndex, Gene* data, map<int,vector<int>>& tree, const int curNode, map<int,pair<int,int>>& maxGoodnessMap);

int main() {
  void *mem = malloc(sizeof(Gene));
  Gene* data = new (mem) Gene();
  Motif names;
  void *memFin = malloc(sizeof(fstream));
  fstream* fin = new (memFin) fstream;
  int total = 0;
  int delta = 500;                            // DELTA 50/10000 = .5%
  int y = 0;                                 // USED AS A VARIABLE GENE COVERAGE IN MOTIFS
  fin -> open("training2.csv");
  if (fin -> is_open()) {                       // CONFIRMS FILE OPEN
    char trash[0];                           // GETS RID OF WHITE SPACE
    fin -> getline(trash, 256, ',');            // BEFORE THE SEQ NAMES
    names.readMotifNames(fin);               // READS AND SETS 244 MOTIF NAMES
    data -> readMotifsOnGene(fin);              // READS AND SETS DATA FOR MOTIF FEATURE
                                             // FOR ALL 10000 GENES
    for (int i = 0; i < 107; ++i) {                // Y IS INCREMENTED in totalGenesWMotif [0:10000]
      data -> totalGenesWMotif(i, y);                 // FINDS TOTAL GENES COVERED BY MOTIF[i]
      names.setNumTranscriptionBindingSites(y, i); // USES TOTAL FOUND SET FEATURE TO ALL MOTIFS
    }



    map<int, std::vector<int>> tree;
    map<int,pair<int,int>> maxGoodnessMap;
    int curNode = 1;
    std::vector<int> startIndex(14000) ; // vector with 100 ints.
    std::iota (std::begin(startIndex), std::end(startIndex), 0); // Fill with 0, 1, ..., 14000.
    tree.insert(std::pair<int,std::vector<int>>(1,startIndex)); //intialize first node of tree


   // decisionTree(startIndex, data, tree, curNode);
    //curNode++;
    //cout << tree[1].pop();


    //for(int i = curNode; i < 20; i++)
      decisionTree(tree[curNode], data, tree, curNode, maxGoodnessMap);//create tree


      cout<< "           HOW TO READ THE DATA" << endl;  //our super fancy gui
      cout<< "~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~"<<endl;
      cout<< "Outputted is a list of the nodes in the tree."<<endl;
      cout<< "To visualize it, place each node in order on the tree from left to right."<<endl;
      cout<< "Since its a binary tree, each level, will have 2^n nodes, where n=level"<<endl;
      cout<< "e.g. \n  1\n  /\\ \n 2  3\n/\\  /\\\n4 5 6 7"<<endl<<endl;
    for(auto mapIt = begin(maxGoodnessMap); mapIt != end(maxGoodnessMap); ++mapIt)//iterator to output data
      {

           std::cout << mapIt-> first << ": \n Name of motif: " << names.getMotifName((mapIt-> second).first) << "\n Number of genes in group: " <<(mapIt-> second).second;

          /*for(auto c : mapIt->second)
          {
              std::cout << c << " ";
          }*/

          std::cout << std::endl<<endl;
      }



  } else {
    // ERROR IF INPUT FILE NOT FOUND
    cout << "Error opening file." << endl;
  }
  data -> ~Gene();
  fin -> close();
  fin -> ~fstream();
  return 0;
}


void decisionTree(vector<int>& startIndex, Gene* data, map<int,vector<int>>& tree, const int curNode, map<int,pair<int,int>>& maxGoodnessMap) {

  int curNodeLeft = curNode*2;
  int curNodeRight = curNode*2+1;
    bool allSameClass = true;
    int firstValue = startIndex[0];
    for (int i = 0; i < startIndex.size(); ++i) {
      if (stoi(data -> getClassOfGene(startIndex[i])) != firstValue) {
        allSameClass = false;
      }
    }//ways to halt tree making process
    if (allSameClass){//if group has all same class
      //cout << "HOLY SHIT WE GOT TO HERE!!!!!!!!!!!!!!!!!!!!!!!!!!!: " <<curNode<< endl << endl;
      return;
    }
    if (startIndex.size() < 2){//if group only has one membber {
      //cout << "Fuck it big enough: " << curNode << endl <<endl;
      return;
    }
    if (curNode > 14000){//if 14000 leaf nodes exist {
      //cout << "CurNode greater than 14000: " <<curNode<< endl<<endl;
      return;
    }
    vector<int> outputLeft;
    vector<int> outputRight;
    double maxGoodness = 0;
    int indexOfMaxGoodness = 0;
    for (int i = 0; i < 107; ++i) { //calculate phi for each motif
      double tL = 0;
      double tR = 0;
      double pR = 0;
      double pL = 0;
      double posWithMotif = 0;
      double negWithMotif = 0;
      double posWithoutMotif = 0;
      double negWithoutMotif = 0;
      double negAbs = 0;
      double posAbs = 0;
      double summation = 0;
      double goodness = 0;

      for (int j = 0; j < startIndex.size(); ++j) {
          if (data -> getMotifOnGene(i,startIndex[j]) == 1) {
            tL++;
            if (data -> getClassOfGene(startIndex[j]) == "1") {
              posWithMotif++;
            } else {
              negWithMotif++;
            }
          } else if (data -> getMotifOnGene(i,startIndex[j]) == 0) {
            tR++;
            if (data -> getClassOfGene(startIndex[j]) == "1") {
              posWithoutMotif++;
            } else {
              negWithoutMotif++;
            }
          }
      }
      pL = tL/startIndex.size();
      pR = tR/startIndex.size();
      negAbs = abs(negWithMotif/tL - negWithoutMotif/tR);
      posAbs = abs(posWithMotif/tL - posWithoutMotif/tR);
      summation = negAbs + posAbs;
      goodness = 2*(pL)*(pR)*summation;
      if (goodness > maxGoodness) {
        maxGoodness = goodness;
        indexOfMaxGoodness = i;
      }

      if (maxGoodness <= 0.0005) return;

    }


    //startIndex.push_back(indexOfMaxGoodness);
    maxGoodnessMap.insert(pair<int,pair<int,int>>(curNode,make_pair(indexOfMaxGoodness,startIndex.size())));
    //cout << "startIndex[indexOfMaxGoodness] = " << startIndex.back() << endl;
    for (int j = 0; j < startIndex.size(); ++j) {//make left node
        if (data -> getMotifOnGene(indexOfMaxGoodness,startIndex[j]) == 1) {
          outputLeft.push_back(startIndex[j]);
          //cout << "Left: " << j <<  outputLeft.back() << endl;
        } else if (data -> getMotifOnGene(indexOfMaxGoodness,startIndex[j]) == 0) {//make right node
          outputRight.push_back(startIndex[j]);
          //cout << "Right: " << j << outputRight.back() <<endl;
        }
    }
    //cout << startIndex.size() << endl;
    //cout << outputLeft.size() << endl;
    //cout << outputRight.size() << endl;
    tree.insert(std::pair<int,std::vector<int>>(curNodeLeft,outputLeft));
    tree.insert(std::pair<int,std::vector<int>>(curNodeRight,outputRight));
    decisionTree(tree[curNodeLeft], data, tree, curNodeLeft, maxGoodnessMap); //recusive for each node
    decisionTree(tree[curNodeRight], data, tree, curNodeRight, maxGoodnessMap);
}
