/*
 * File: RST.hpp
 * Author: Joshua Yuen cs100vbc
 * Author: Jay Dey cs100vaj
 */

#ifndef RST_HPP
#define RST_HPP
#include "BST.hpp"
#include "countint.hpp"

template <typename Data>
class RST : public BST<Data>
{

public:

  //TODO: implement this function!
  virtual std::pair<typename BST<Data>::iterator,bool> insert(const Data& item)
  {
    if(!this->root)
    {
      srand(time(NULL));
    }
    std::pair <typename BST<Data>::iterator,bool> pa = 
      BST<Data>::insert(item);
    if ( pa.second == false ){
      return pa;
    }
    BSTNode<Data>* x = pa.first.curr;
    x->info = rand();
    bubbleUp(x);
    return pa;
  }

  void bubbleUp( BSTNode<Data>* newNode )
  {
    while ( (newNode->parent != NULL) && 
         (newNode->parent->info < newNode->info))
    {
      BSTNode<Data>* p = newNode->parent;
      BSTNode<Data>* grandp = newNode->parent->parent;
      if (grandp == NULL){
        if (p->left == newNode){
          p=rotateWithLeftChild(p);
	  this->root = newNode;
	  newNode->parent = NULL;
        }
        else{
          p=rotateWithRightChild(p);
	  this->root = newNode;
	  newNode->parent = NULL;
        }
      }
      else if (grandp->left == p){
	p->parent = grandp;
	if (p->left == newNode){
          p=rotateWithLeftChild(p);
	  grandp->left = p;

        }
        else{
          p=rotateWithRightChild(p);
	  grandp->left = p;
        }

      }
      else{
	if (p->left == newNode){
          p=rotateWithLeftChild(p);
	  grandp->right = p;
	  p->parent = grandp;

        }
        else{
          p=rotateWithRightChild(p);
	  grandp->right = p;
	  p->parent = grandp;

        }
      }
    }
  }

  BSTNode<Data>* rotateWithLeftChild(BSTNode<Data> * p)
  {
    BSTNode<Data>* x = p->left;
    p->left = x->right;
    if (x->right)
      x->right->parent = p;

    x->right = p;
    p->parent = x;

    return x;
  }

  BSTNode<Data>* rotateWithRightChild(BSTNode<Data> * p)
  {
    BSTNode<Data>* x = p->right;
    p->right = x->left;
    if (x->left)
      x->left->parent = p;

    x->left = p;
    p->parent = x;

    return x;
  }

};

#endif // RST_HPP
