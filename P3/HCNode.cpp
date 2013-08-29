/*
 * P3
 * HCNode.cpp
 * implementation of HCNode operator overload
 *
 * Author: Jay Dey cs100vaj
 * Author: joshua Yuen cs100vbc
 */

#include "HCNode.hpp"

bool HCNode::operator<(const HCNode& other)
{
  return (! (count < other.count) );
}
