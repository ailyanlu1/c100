/*
 * P3
 * compress.cpp
 * main driver for compression process
 * Author: Jay Dey cs100vaj
 * Author: Joshua Yuen cs100vbc
 */

#include <fstream>
#include <iostream>
#include "HCTree.hpp"

using namespace std;

int main( int argc, char* argv[] )
{
  // command line args check
  if( argc != 3 )
  {
    cerr << "Incorrect args" << endl;
    cerr << "Usage: ./compress infile outfile" << endl;
    return 1;
  }

  // file read
  cout << "Reading from file: " << argv[1] << "... " << end;

  vector<int> freq(256);
  ifstream in;
  in.open( argv[1], ios::binary );
  
  int symcount = 0, bytesize = 0; compsize = 0;

  bool empty = true;
  char ch;

  while( 1 )
  {
    ch = in.get();

    if( ! in.good() )
      break;

    for( int i=0; i < freq.size(); i++ )
    {
      if( ch == i )
      {
        ++freq[i];
	empty = false;
      }
    }

    bytesize++;
  }

  if( ! in.eof() )
  {
    cerr << "There was a problem, sorry." << endl;
    return -1;
  }

  in.close();
  cout << "DONE." << endl;

  // file info
  for( int i=0; i<freq.size(); i++ )
  {
    if( freqs[i] != 0 )
      symcount++;
  }

  cout << "Found " << symcount << "unique symbols in input file." << endl;
  cout << "\tFile size: " << bytesize << " bytes." << endl;

  //build Huffman Tree
  cout << "Building Huffman Tree... " << end;

  HCTree tree;
  if( !empty )
    tree.build(freq);

  cout << "DONE." << endl;

  // write to file
  ofstream out;
  out.open( argv[2], ios::binary );
  cout << "Writing to file: " << argv[2] << "... " << end;

}
