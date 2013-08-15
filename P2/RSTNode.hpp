/*
 * File: RSTNode.hpp
 * Author: Joshua Yuen cs100vbc
 * Author: Jay Dey cs100vaj
 */

#ifndef RSTNODE_HPP
#define RSTNODE_HPP
#include "BSTNode.hpp"
#include <stdlib.h>

template <typename Data>
class RSTNode : public BSTNode<Data>
{

protected:

  unsigned int priority;

public:
  //TODO: implement this constructor
  RSTNode(Data const & d) : BSTNode<Data>(d)
  {
    priority = rand(); //maybe need to bound this somehow?
    this->info = priority;
  }

};

#endif // RSTNODE_HPP
