#include "HCTree.hpp"
#include "HCNode.hpp"
#include <queue>
#include <stack>
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

void HCTree::build(const vector<int>& freqs) 
{
  priority_queue<HCNode*, vector<HCNode*>, HCNodePtrComp> pQueue;

  for (int i = 0; i < 256; i++){ 
    //convert vector to HCNodes
    if( freqs[i] )
    {
      HCNode* temp = new HCNode(freqs[i], (byte)i);
      leaves[i] = temp; //create a new vector to look up the pointers
                      //for those HCNodes based on bit value
      pQueue.push(temp);
    }
  }

  //to account for cases in which there's only one leaf
  if ( pQueue.size() == 1)
    pQueue.push(new HCNode(0, 0));

  
  while(pQueue.size() > 1){
    //pop two nodes with lowest count
    HCNode* temp1 = pQueue.top();
    pQueue.pop();
    HCNode* temp2 = pQueue.top();
    pQueue.pop();
    //give them a parent node (new tree is born!)
    HCNode* tempR = new HCNode(temp1->count + temp2->count, 0, temp1, temp2);
    temp1->p = tempR;
    temp2->p = tempR;
    /*
     * put the new root node back into the stack to keep building tree
     * from ground up
     */
    pQueue.push(tempR);
  }
  //make sure last element left in priority queue is set to root
  root = pQueue.top();
}

void HCTree::encode(byte symbol, BitOutputStream& out) const {
  HCNode * temp = leaves[symbol];
  stack<int> code;

  while( temp != root )
  {
    // current is 0 child of parent
    if( temp->p->c0 == temp )
      code.push(0);
    // current is 1 child of parent
    if( temp->p->c1 == temp )
      code.push(1);

    temp = temp->p;
  }

  while( !code.empty() )
  {
    //write out the bits
    out.writeBit( code.top() );
    code.pop();
  }
}


int HCTree::decode(BitInputStream& in) const {
  HCNode* temp = root;
  int bit;

  /*
   * Go down the tree until you hit the correct leaf node described by the 
   * encoded bits
   */
  while ( (temp->c0) && (temp->c1) )
  {
    bit = in.readBit();

    if (bit == 1)
      temp = temp->c1;
    else 
      temp = temp->c0;
  }
  return temp->symbol;
   
}
