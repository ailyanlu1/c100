#include "HCTree.hpp"
#include <queue>

/** P3
 *  Implementation of the HCTree class
 *  See: HCTree.hpp
 *  Author: Jay Dey cs100vaj
 *  Author: Joshua Yuen cs100vbc
 */

void HCTree::build(const vector<int>& freqs) {
  int i;
  for (i = 0; i < 256, i++){ //convert vector to HCNodes
    HCNode* temp = new HCNode(freqs[i], i, 0, 0, 0);
    leaves[i] = temp; //create a new vector to look up the pointers
                      //for those HCNodes based on bit value
  }

  std::priority_queue< HCNode, leaves, HCNodePtrComp> pQueue;

  while(pQueue.size() != 1){
    HCNode* temp1 = pQueue.top();
    pQueue.pop();
    HCNode* temp2 = pQueue.top();
    pQueue.pop();
    HCNode* tempR = new HCNode(temp1.count + temp2.count, temp1, temp2, 0);
    temp1.p = tempR;
    temp2.p = tempR;
    pQueue.push(tempR);
  }


}

void HCTree::encode(byte symbol, BitOutputStream& out) const {
  std::string str = encodeHelper(symbol);
  int i;
  for (i = 0; i<str.size(); i++){
    if (str[i] == 1){
      out.writeBit(1);
    }
    else{
      out.writeBit(0);
    }
  }
}

char * HCTree::encodeHelper(byte symbol){
  HCNode* temp = leaves[symbol];
  std::string sTemp;
  while (temp->p){
  if(temp == temp->p->c0){
    sTemp::append("0");
  }
  else{
    sTemp::append("1");
  }
  temp = temp->p;
  }
  return sTemp;
}

int HCTree::decode(BitInputStream& in) const {
  HCNode* temp = root;
  int bit;
  while ((bit = in.readbit()) != NULL){
    if ((temp->c0 != NULL) || (temp->c1 != NULL)){
      if (bit == 1){
        temp = temp->c1;
      }
      else {
        temp = temp->c0;
      }
    }
    else {
      return temp->symbol
    }
  }
}
