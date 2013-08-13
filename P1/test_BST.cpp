#include "BST.hpp"
#include <iostream>
#include <algorithm>
#include <vector>

using namespace std;

/**
 * A simple test driver for the BST class template.
 * P1 CSE 100 2013
 * Author: P. Kube (c) 2013
 */
int main() {

  /* Create an STL vector of some ints */
  vector<int> v;
  v.push_back(3);
  v.push_back(4);
  v.push_back(1);
  v.push_back(100);
  v.push_back(-33);
  

  /* Create an instance of BST holding int */
  BST<int> b;

  /* Insert a few data items. */
  vector<int>::iterator vit = v.begin();
  vector<int>::iterator ven = v.end();
  for(; vit != ven; ++vit) {
    // all these inserts are unique, so should return a std::pair
    // with second part true
    std::pair<BST<int>::iterator,bool> pr = b.insert(*vit);
    if(! pr.second ) {
      cout << "Incorrect bool return value when inserting " << *vit << endl;
      return -1;
    }
    if(*(pr.first) != *vit) {
      cout << "Incorrect iterator return value when inserting " << *vit << endl;
      return -1;
    }  
  }

  /* Test size. */
  cout << "Size is: " << b.size() << endl;
  if(b.size() != v.size()) {
    cout << "... which is incorrect." << endl;
    return -1;
  }

  /* Test find return value. */
  vit = v.begin();
  int count = 0;
  for(; vit != ven; ++vit) {
    if(*(b.find(*vit)) != *vit) {
      cout << "Incorrect return value when finding " << *vit << endl;
      return -1;
    }
    cout << "been through " << ++count << endl;
  }
  
  /* Sort the vector, to compare with inorder iteration on the BST */
  cout << "this is v: " << *(v.begin()) << endl;
  sort(v.begin(),v.end());
  cout << "sort done" << endl;

  /* Test BST iterator; should iterate inorder */
  cout << "traversal using iterator:" << endl;
  vit = v.begin();
  BST<int>::iterator en = b.end();
  BST<int>::iterator it = b.begin();
  cout << "entering iteration" << endl;
  for(; vit != ven; ++vit) {
    cout << "iterating..." << endl;
    if(! (it != en) ) {
      cout << "entered first if" << endl;
      cout << *it << "," << *vit << ": Early termination of BST iteration." << endl;
      return -1;
    }
    cout << *it << endl;
    if(*it != *vit) {
      cout << *it << "," << *vit << ": Incorrect inorder iteration of BST." << endl;
      return -1;
    }
    ++it;
  }
  cout << "OK." << endl;

  vector<int> dup;
  dup.push_back(5);
  dup.push_back(3);
  dup.push_back(3);

  BST<int> duplicateBST;

  vector<int>::iterator bit = dup.begin();
  vector<int>::iterator ben = dup.end();
  for(; bit != ben; ++bit) {
    // all these inserts are unique, so should return a std::pair
    // with second part true
    std::pair<BST<int>::iterator,bool> br = duplicateBST.insert(*bit);
    if(br.second == false) {
      cout << "Value is duplicate " << *bit << endl;
    }
    if(*(br.first) != *bit) {
      cout << "Incorrect iterator return value when inserting " << *bit << endl;
      return -1;
    } 
  }

}
