/*
 * File: RST.hpp
 * Author: Joshua Yuen cs100vbc
 * Author: Jay Dey cs100vaj
 */

#ifndef RST_HPP
#define RST_HPP
#include "BST.hpp"

template <typename Data>
class RST : public BST<Data>
{

public:

  //TODO: implement this function!
  virtual std::pair<typename BST<Data>::iterator,bool> insert(const Data& item)
  {

  }

  RSTNode<Data>* rotateWithLeftChild(RSTNode<Data> * p)
  {

  }

  RSTNode<Data>* rotateWithRightChild(RSTNode<Data> * p)
  {

  }

};

#endif // RST_HPP
