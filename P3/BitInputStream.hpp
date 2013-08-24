/*
 * P3
 * BitInputStream.hpp
 * Allows reading of individual bits
 *
 * Author: Jay Dey cs100vaj
 * Author: Joshua Yuen cs100vbc
 */

#ifndef BITINPUTSTREAM_HPP
#define BITINPUTSTREAM_HPP

#include <iostream>

class BitInputStream
{
  private:
    char buf;		/* one byte buffer (8 bits) */
    int nbits;		/* Number of bits read from buf */
    std::istream & in;	/* input stream */

  public:
    /* constructor */
    BitInputStream( std::istream & is ) : in(is)
    {
      buf = 0;
      nbits = 8;
    }

    /* fill buffer from input */
    void fill();

    /* Read the next bit from the bit buffer.
     * Fill the buffer from the input stream first if needed.
     * Return bit read
     */
    int readBit();
}

#endif //BITINPUTSTREAM_HPP
