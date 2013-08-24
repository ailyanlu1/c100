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
    cerr << "Incorrect arguments" << endl;
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

    if( ! in.good() ) break;

    ++freq[ch];
    empty = false;
  }

    bytesize++;
  }

  if( ! in.eof() )
  {
    cerr << "I got 99 problems, and file reading is one." << endl;
    return -1;
  }

  in.close();
  cout << "DONE." << endl;
  in.clear();

  // infile info
  for( int i=0; i<freq.size(); i++ )
  {
    if( freqs[i] != 0 )
      symcount++;
  }

  cout << "Found " << symcount << "unique symbols in input file." << endl;
  cout << "\tFile size: " << bytesize << " bytes." << endl;

  // build Huffman Tree
  cout << "Building Huffman Tree... " << end;

  HCTree tree;
  if( !empty )
    tree.build(freq);

  cout << "DONE." << endl;

  // open out file for writing
  ofstream out;
  out.open( argv[2], ios::binary );
  cout << "Writing to file: " << argv[2] << "... " << end;

  // file header
  if( out.is_open() )
    for( int i=0; i<freq.size(); i++ )
      out << freq[i] << " " << end;

  out.flush();

  BitOutputStream os = BitOutputStream( out );
  in.open( argv[1], ios::binary );

  if( !empty )
  {
    for( int j=0; j<bytesize; j++ )
    {
      ch = in.get();

      if( !in.good() ) break;
      
      tree.encode( ch, os );
    }
  }

  os.flush();
  in.close();
  out.close();

  cout << "DONE." << endl;

  // outfile info
  ifstream in2;
  in2.open( argv[2] );

  while( in2.is_open() )
  {
    ch = in2.get();
    
    if( !in2.good() ) break;

    compsize++;
  }

  if( !in2.eof() )
  {
    cerr << "I got 99 problems, and file reading is one." << endl;
    return -1;
  }

  in2.close();
  
  cout << "Output file has size: " << compsize << " bytes." << endl;

  double ratio = 0;
  if( filesize != 0 && compsize != 0 )
    ratio = (double)compsize / (double)filesize;

  cout << "Compression rate: " << ratio << endl;

  return 0;
  //END COMPRESS PROCESS
}
