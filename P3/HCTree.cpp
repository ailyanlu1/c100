#include "HCTree.hpp"
#include <queue>

/** P3
 *  Implementation of the HCTree class
 *  See: HCTree.hpp
 *  Author: Jay Dey cs100vaj
 *  Author: Joshua Yuen cs100vbc
 */

void HCTree::build(const vector<int>& freqs) {
  for (int i = 0; i < 256, i++){ //convert vector to HCNodes
    HCNode* temp = new HCNode(freqs[i], i, 0, 0, 0);
    leaves[i] = temp; //create a new vector to look up the pointers
                      //for those HCNodes based on bit values
  }

std::priority_queue< HCNode, leaves, HCNodePtrComp> pQueue;



}

void HCTree::encode(byte symbol, BitOutputStream& out) const {

}

int HCTree::decode(BitInputStream& in) const {

}
