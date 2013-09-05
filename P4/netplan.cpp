#include <fstream>
#include <iostream>
#include "Graph.hpp"

using namespace std;

int main( int argc, char* argv[] )
{
  // command line args check
  if( argc != 2)
  {
    cerr << "Incorrect arguments" << endl;
    cerr << "Usage: ./netplan file" << endl;
    return 1;
  }

  // file read
  cout << "Reading from file: " << argv[1] << "... ";

  Graph gph = new Graph();
  string line;
  ifstream in ( argv[1]);

  if (in.is_open()){
    while ( in.good() ){
      getline(in, line);
      char * pch;
      pch = strtok (str, " ");
      if ( gph.findVertex(pch) == NULL ){
        Vertex* temp = new Vertex(pch);
	gph.addVertex(temp);
      }
      pch = strotk (str, " ");
      if ( gph.findVertex(pch) == NULL ){
        Vertex* temp1 = new Vertex(pch);
	gph.addVertex(temp);
      }
      int cost = strtok (str, " ");
      int time = strotk (str, " ");
      temp.addAdjVertex( temp1, cost, time);
      }
    }
    if ( ! in.eof() )
    {
      cerr << "There was a problem, sorry." << endl;
      return -1;
    }

    in.close();
    in.clear();
  }

  cout << gph.totalCost() << endl;

  Graph mst = gph.MST();
  
  cout << mst.totalCost() << endl;

  cout << gph.totalCost()-mst.totalCost() << endl;

  Graph dGph = gph.dijkstra();
  Graph dMst = mst.dijkstra();

  cout << dGph.totalTime() << endl;

  cout << dMst.totalTime() << endl;

  cout << dGph.totalTime()-dMst.totalTime() << endl;

  return 0;
}
