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
    if (this->root == NULL){
      this->root = new BSTNode<Data>(item);
      BSTIterator<Data>* iter = new BSTIterator<Data>(this->root);
      inserted = true;
      ++isize;
      return std::make_pair(*iter,inserted);
    }
    BSTIterator<Data>* iter = new BSTIterator<Data>(this->root);
    while (iter->curr != NULL){
      if (iter->curr->data > item){
        iter->curr = iter->curr->left;
      }
      else if (iter->curr->data < item){
        iter->curr = iter->curr->right;
      }
      else { //iter->curr->value == item
        inserted = false;
        ++isize;
        return std::make_pair(*iter, inserted);
      }      
    }
    iter->curr = new BSTNode<Data>(item);
    inserted = true;
    ++isize;
    return std::make_pair(*iter,inserted);
  }


  /** Find a Data item in the BST.
   *  Return an iterator pointing to the item, or the end
   *  iterator if the item is not in the BST.
   */ // TODO
  iterator find(const Data& item) const 
  {
    if (this->root == NULL){
      BSTIterator<Data>* iter = new BSTIterator<Data>(this->root);
      return *iter;
    }
    BSTIterator<Data>* iter = new BSTIterator<Data>(this->root);
    while (iter->curr != NULL && iter->curr->data != item){
      if (iter->curr->data > item){
        iter->curr = iter->curr->left;
      }
      if (iter->curr->data < item){
        iter->curr = iter->curr->right;
      }
    }
    return *iter;          
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
    BSTNode<Data>* temp = new BSTNode<Data>(this->root);
    while (temp->left)
      temp = temp->left;

    return new BSTIterator<Data>(temp);
  }

  /** Return an iterator pointing past the last item in the BST.
   */
  iterator end() const 
  {
    return typename BST<Data>::iterator(nullptr);
  }

  

 };


#endif //BST_HPP
