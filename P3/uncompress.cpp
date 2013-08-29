/*
 * P3
 * uncompress.cpp
 * Main driver for decopmression process
 *
 * Author: Jay Dey cs100vaj
 * Author: Joshua Yuen cs100vbc
 */

#include <fstream>
#include <iostream>
#include "HCTree.hpp"

using namespace std;

int main( int argc, char* argv[] )
{
  if( argc != 3 )
  {
    cerr << "Incorrect arguments." << endl;
    cerr << "Usage: ./uncompress infile outfile" << endl;
    return 1;
  }

  cout << "Reading header from file: " << argv[1] << "... ";

  vector<int> freq(256);
  ifstream in;
  in.open( argv[1], ios::binary );

  int symbols = 0, bytesize = 0, compsize = 0;
  bool empty = true;
  unsigned char ch;
  int num;

  if( in.is_open() && in.good() )
  {
    for( int i=0; i<freq.size(); i++ )
    {
      in >> num;
      freq[i] = num;
      bytesize = bytesize + num;
    }
  }

  cout << "DONE." << endl;

  /* report outfile stats */
  for( int i=0; i<freq.size(); i++ )
    if( freq[i] != 0 )
    {
      //cerr << "counting symbols" << endl;
      symbols++;
      empty = false;
    }

  if( symbols == 0 )
    empty = true;

  cout << "Uncompressed file will have " << symbols << " unique symbols and"
          " size " << bytesize << " bytes." << endl;

  /* build Huffman tree */
  cout << "Building Huffman tree... ";

  HCTree tree;
  if( !empty )
  {
    //cerr << "not empty, building" <<  endl;
    tree.build( freq );
  }

  cout << "DONE." << endl;

  /* Write uncompressed data to outfile */
  BitInputStream is = BitInputStream( in );
  ofstream out;
  out.open( argv[2], ios::binary );

  cout << "Writing to file: " << argv[2] << "... ";

  if ( !empty )
    for( int i=0; i<bytesize; i++ )
    {
      out << (byte)tree.decode( is );
      //cerr << (byte)tree.decode( is );
    }

  cout << "DONE." << endl;

  in.close();
  out.close();

  in.clear();
  in.open( argv[1], ios::binary );

  /* infile stats */
  while( in.is_open() )
  {
    ch = in.get();

    if( !in.good() ) break;

    compsize++;
  }
  if( !in.eof() )
  {
    cerr << "There was a problem, sorry." << endl;
    return -1;
  }

  in.close();
  double ratio = 0;
  if( bytesize != 0 && compsize != 0 )
    ratio = (double)bytesize / (double)compsize;

  cout << "Uncompression ratio: " << ratio << endl;

  return 0;
}

//EOF uncompress.cpp
