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
    if ( BST<Data>::find(item) )
      return std::make_pair( BST<Data>::find(item), false );

    RSTNode<Data> newNode = new RSTNode<Data>(item);
    repair(newNode);

    
  }

  void repair( RSTNode<Data>* newNode )
  {
    while ( (newNode->parent != NULL) && 
           (newNode->priority > ((RSTNode<Data>*)(newNode->parent))->priority))
    {
      
    }
  }

  RSTNode<Data>* rotateWithLeftChild(RSTNode<Data> * p)
  {
    BSTNode<Data>* x = p->left;
    p->left = x->right;
    if (x->right)
      x->right->parent = p;

    x->right = p;
    p->parent = x;

    return (RSTNode<Data>*)x;
  }

  RSTNode<Data>* rotateWithRightChild(RSTNode<Data> * p)
  {
    BSTNode<Data>* x = p->right;
    p->right = x->left;
    if (x->left)
      x->left->parent = p;

    x->left = p;
    p->parent = x;

    return (RSTNode<Data>*)x;
  }

};

#endif // RST_HPP
