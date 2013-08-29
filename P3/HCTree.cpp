#include "HCTree.hpp"
#include "HCNode.hpp"
#include <queue>
#include <string>
#include "BitInputStream.hpp"
#include "BitOutputStream.hpp"

/** P3
 *  Implementation of the HCTree class
 *  See: HCTree.hpp
 *  Author: Jay Dey cs100vaj
 *  Author: Joshua Yuen cs100vbc
 */

HCTree::~HCTree()
{
  clear(root);
}


void HCTree::clear(HCNode* node)
{
  if (node == NULL) return;

  clear(node->c0);
  clear(node->c1);
  delete node;
}

void HCTree::build(const vector<int>& freqs) {
  priority_queue<HCNode*, vector<HCNode*>, HCNodePtrComp> pQueue;


  for (int i = 0; i < 256; i++){ //convert vector to HCNodes
    //cerr << "beginning build" << endl;
    HCNode* temp = new HCNode(freqs[i], i);
    leaves[i] = temp; //create a new vector to look up the pointers
                      //for those HCNodes based on bit value
    pQueue.push(temp);
    //cerr << "pushed" << endl;
  }

  while(pQueue.size() > 1){
    HCNode* temp1 = pQueue.top();
    pQueue.pop();
    HCNode* temp2 = pQueue.top();
    pQueue.pop();
    HCNode* tempR = new HCNode(temp1->count + temp2->count, 0, temp1, temp2);
    temp1->p = tempR;
    temp2->p = tempR;
    pQueue.push(tempR);
  }
  root = pQueue.top();
}

string HCTree::encodeHelper(byte symbol) const {
  HCNode* temp = leaves[(int)symbol];
  string sTemp;
  while (temp->p){
  if(temp == temp->p->c0){
    sTemp.append("0");
  }
  else{
    sTemp.append("1");
  }
  temp = temp->p;
  }
  return sTemp;
}

void HCTree::encode(byte symbol, BitOutputStream& out) const {
  string str = encodeHelper(symbol);
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


int HCTree::decode(BitInputStream& in) const {
  HCNode* temp = root;
  int bit;
  while (bit = in.readBit()){
    if ((temp->c0) && (temp->c1)){
      if (bit == 1){
        temp = temp->c1;
      }
      else {
        temp = temp->c0;
      }
    }
    else {
      return temp->symbol;
    }
  }
}

