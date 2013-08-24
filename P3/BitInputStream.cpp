/*
 * P3
 * BitInputStream.cpp
 * Implementation of BitInputStream class
 *
 * Author: Jay Dey cs100vaj
 * Author: Joshua Yuen cs100vbc
 */

#include "BitInputStream.hpp"

void BitInputStream::fill()
{
  buf = in.get();
  nbits = 0;
}

int BitInputStream::readBit()
{
  // all bits in buffer are read
  if( nbits == 8 )
    fill();

  // get bit at appropriate location
  int bit = 1 & (buf >> (7 - nbits));
  nbits++;

  return bit;
}
