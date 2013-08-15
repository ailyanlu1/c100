/*
 * File: RSTNode.hpp
 * Author: Joshua Yuen cs100vbc
 * Author: Jay Dey cs100vaj
 */

#ifndef RSTNODE_HPP
#define RSTNODE_HPP
#include "BSTNode.hpp"

template <typename Data>
class RSTNode : public BSTNode<Data>
{
public:
  //TODO: implement this constructor
  RSTNode(Data const & d) : BSTNode<Data>(d)
  {
    
  }

};

#endif // RSTNODE_HPP
