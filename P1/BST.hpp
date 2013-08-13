/**
 * The BST class
 * P1 CSE 100 2013
 * Author: Jay Dey
 * uid: cs100vaj
 * Author: Joshua Yuen
 * uid: cs100vbc
 */

#ifndef BST_HPP
#define BST_HPP
#include "BSTNode.hpp"
#include "BSTIterator.hpp"
#include <utility> // for std::pair

template<typename Data>
class BST {

protected:

  /** Pointer to the root of this BST, or nullptr if the BST is empty */
  BSTNode<Data>* root;

  /** Number of Data items stored in this BST. */
  unsigned int isize;


public:

  /** iterator is an aliased typename for BSTIterator<Data>. */
  typedef BSTIterator<Data> iterator;

  /** Default constructor.
      Initialize an empty BST.
   */
  BST() : root(nullptr), isize(0) 
  {
  }


  /** Default destructor.
   *  It is virtual, to allow appropriate destruction of subclass objects.
   *  Delete every node in this BST.
   */ // TODO
  virtual ~BST() 
  {
     //may need to delete isize, iterator as well...
     delete this->root;
     this->root = NULL;
  }

  /** Insert a Data item in the BST.
   *  Return a pair, with the pair's first member set to an
   *  iterator pointing to either the newly inserted element
   *  or to the equivalent element already in the set.
   *  The pair's second element is set to true
   *  if a new element was inserted or false if an
   *  equivalent element already existed.
   */ // TODO
  virtual std::pair<iterator,bool> insert(const Data& item) 
  {
    bool inserted;
    /*
     * If root is null, create a new BSTNode<Data> object, and
     * an iterator pointing to that object.
     */
    if (this->root == NULL){
      this->root = new BSTNode<Data>(item);
      BSTIterator<Data> iter = BSTIterator<Data>(this->root);
      inserted = true;
      ++isize;
      return std::make_pair(iter,inserted);
    }
    /*
     * Otherwise, go down the tree to find the correct place to
     * insert a new node containing the data passed in through item.
     * Then set the relevant pointers in parent and child and return
     * an iterator pointing at the new node.
     */
    BSTNode<Data>* temp = this->root;
    BSTNode<Data>* tempParent = NULL;
    bool right_side;
    while (temp != NULL)
    {
      if (temp->data > item)
      {
        tempParent = temp;
	right_side = false;
        temp = temp->left;
      }
      else if (temp->data < item)
      {
        tempParent = temp;
	right_side = true;
        temp = temp->right;
      }
      else //if a node with an equivalent data value is already in the
      {    //tree, return an iterator pointing to it, and set inserted false
        inserted = false;
        return std::make_pair(iterator(temp), inserted);
      }      
    }
    temp = new BSTNode<Data>(item);
    temp->parent = tempParent;
    if (right_side)
      tempParent->right = temp;
    else
      tempParent->left = temp;
    inserted = true;
    ++isize;
    return std::make_pair(iterator(temp),inserted);
  }


  /** Find a Data item in the BST.
   *  Return an iterator pointing to the item, or the end
   *  iterator if the item is not in the BST.
   */ // TODO
  iterator find(const Data& item) const 
  {
    /*
     * Start at the root, and search for the appropriate node.
     * Then return an iterator pointing to the item.
     */
    BSTNode<Data>* temp = this->root;
    while (temp != NULL){
      if (temp->data > item){
        temp = temp->left;
      }
      else if (temp->data < item){
        temp = temp->right;
      }
      else {
        return iterator(temp);
      }
    } 
    return end(); //if item not found, return the end iterator. 
  }

  
  /** Return the number of items currently in the BST.
   */ // TODO
  unsigned int size() const 
  {
    return isize;
  }

  /** Remove all elements from this BST, and destroy them,
   *  leaving this BST with a size of 0.
   */ // TODO
  void clear() 
  {
    delete this->root;
    this->root = NULL;
    isize = 0;
  }

  /** Return true if the BST is empty, else false.
   */ // TODO
  bool empty() const 
  {
    return ( isize == 0 );
  }

  /** Return an iterator pointing to the first item in the BST.
   */ // TODO
  iterator begin() const 
  {
    BSTNode<Data>* temp = this->root;
    while (temp->left)
      temp = temp->left; //find leftmost node

    return iterator(temp); //return iterator pointing at it
  }

  /** Return an iterator pointing past the last item in the BST.
   */
  iterator end() const 
  {
    return typename BST<Data>::iterator(nullptr);
  }

  

 };


#endif //BST_HPP
