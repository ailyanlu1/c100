#ifndef BSTNODE_HPP
#define BSTNODE_HPP
#include <iostream>
#include <iomanip>


/** This class template defines a node type for the BST container.
 *  Note that all members are public. So, the BST implementation should
 *  take care not to expose any BSTNode objects.
 */
template<typename Data>
class BSTNode {

public:

  /** Member variables. */
  BSTNode<Data>* parent;
  BSTNode<Data>* left;
  BSTNode<Data>* right;
  const Data data;  // the const Data in this node
  int info;  // variable used in advanced algorithms 

  /** Constructor.  Initialize a BSTNode with the given Data item,
   *  no parent, and no children.
   */
  BSTNode(const Data & d): data(d) {
    left = right = parent = nullptr;
  }

  ~BSTNode()
  {
    delete (*this)->left;
    delete (*this)->right;
    delete (*this);
    (*this)->left = NULL;
    (*this)->right = NULL;
    (*this) = NULL;
  }

  /** Return the inorder successor of this BSTNode in a BST,
   *  or nullptr if none.
   *  PRECONDITION: this BSTNode is a node in a BST.
   *  POSTCONDITION:  the BST is unchanged.
   *  RETURNS: the BSTNode that is the inorder successor of this BSTNode,
   *  or nullptr if there is none.
   */ // TODO
  BSTNode<Data>* successor() {
    new BSTNode<Data> tmpNode1;
    new BSTNOde<Data> tmpNode2;
    //case 1: right child of current node exists
    if (this->right) {
      tmpNode1 = this->right;
      while (tmpNode1->left) { //find leftmost child
        tmpNode1 = tmpNode1->left;
      }
    }
    //case 2: no right child
    else {
      tmpNode2 = this;
      while((tmpNode1 = tmpNode2->parent)) { //climb
        //when you find the parent has left decendent tmpNode2, stop.
        if(tmpNode1->left == tmpNode2){          
          break;
        }
        tmpNode2 = tmpNode1;
      }
    }
    return tmpNode1;
  }
}; 

/** Overload operator<< to insert a BSTNode's fields in an ostream. */
template <typename Data>
std::ostream & operator<<(std::ostream& stm, const BSTNode<Data> & n) {
  stm << '[';
  stm << std::setw(10) << &n;                 // address of the BSTNode
  stm << "; p:" << std::setw(10) << n.parent; // address of its parent
  stm << "; l:" << std::setw(10) << n.left;   // address of its left child
  stm << "; r:" << std::setw(10) << n.right;  // address of its right child
  stm << "; i:" << std::setw(10) << n.info;   // its info field
  stm << "; d:" << n.data;                    // its data field
  stm << ']';
  return stm;
}

#endif // BSTNODE_HPP
