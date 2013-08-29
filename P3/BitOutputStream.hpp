#ifndef BITOUTPUTSTREAM_HPP
#define BITOUTPUTSTREAM_HPP
/*
 * P3
 * BitOutputStream.hpp
 * Header file for BitOutputStream class
 * Allows writing individual bits to output stream
 * 
 * Author: Jay Dey cs100vaj
 * Author: Joshua Yuen cs100vbc
 */



#include <iostream>

class BitOutputStream
{
  private:
    char buf;   	 /* one byte buffer (8 bits) */
    int nbits; 		 /* number of bits written to buf */
    std::ostream & out;  /* reference to output stream */

  public:
    /* constructor */
    BitOutputStream( std::ostream & os ) : out(os)
    {
      buf = nbits = 0;
    }

    /* send buffer to output, clear */
    void flush();

    /*
     * Write the least significant bit of the argument to the bit buffer, 
     * and increment the bit buffer index.
     * But flush the buffer first, if it is full. 
     */
    void writeBit( int i );
};

#endif //BITOUTPUTSTREAM_HPP
