/*
 * P3
 * BitOutputStream.cpp
 * Implementation of BitOutputStream class
 * Allows writing of individual bits to output stream
 *
 * Author: Jay Dey cs100vaj
 * Author: Joshua Yuen cs100vbc
 */

#include "BitOutputStream.hpp"

void BitOutputStream::flush()
{
  os.put( buf );
  os.flush();
  buf = nbits = 0;
}

void BitOutputStream::writeBit( int i )
{
  // buffer is full
  if( nbits == 8 )
    flush();

  buf = buf | (i << (7 - nbits));
  nbits++;
}
