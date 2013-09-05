#include <fstream>
#include <iostream>
#include <string.h>
#include <stdio.h>
#include "Graph.hpp"
#include "Vertex.hpp"
#include "Edge.hpp"

using namespace std;

int main( int argc, char* argv[] )
{
  // command line args check
  if( argc != 2)
  {
    cerr << "Incorrect arguments" << endl;
    cerr << "Usage: ./netplan infile" << endl;
    return 1;
  }

  // file read
  cout << "Reading from file: " << argv[1] << "... ";

  Graph *gph = new Graph();
  string temp1, temp2;
  int cost, time;
  ifstream in ( argv[1]);

  //if (in.is_open())
  //{
    while ( !in.eof() )
    {
      //getline(in, line);
      in >> temp1 >> temp2 >> cost >> time;
      if( in.eof() )
        break;
      //char * pch;
      //pch = strtok (line, " ");
      Vertex *v1, *v2;
      if ( gph->findVertex(temp1) == NULL )
      {
        v1 = new Vertex(temp1);
	gph->addVertex(v1);
      }
      else
        v1 = gph->findVertex(temp1);

      //pch = strtok (line, " ");
      if ( gph->findVertex(temp2) == NULL )
      {
        v2 = new Vertex(temp2);
	gph->addVertex(v2);
      }
      else
        v2 = gph->findVertex(temp2);

      //int cost = strtok (line, " ");
      //int time = strtok (line, " ");
      v1->addAdjVertex( v2, cost, time);
    }
    /*if ( ! in.eof() )
    {
      cerr << "There was a problem, sorry." << endl;
      return -1;
    }
  }*/
    in.close();
    in.clear();
    cout << "DONE." << endl;

  gph->displayGraph();

  cout << "g total cost " << gph->totalCost() << endl;

  Graph * mst = gph->MST();
  mst->displayGraph();
  cout << "mst total cost " << mst->totalCost() << endl;

  cout << "total cost diff " << gph->totalCost()-mst->totalCost() << endl;

  //Graph dGph = gph.dijkstra();
  //Graph *dMst = mst->dijkstra();
  int dijG = gph->dijkstra();
  int dijM = mst->dijkstra();

  cout << "g dij " << dijG << endl;

  cout << "m dij " << dijM << endl;

  //cout << dGph->totalTime()-dMst->totalTime() << endl;
  cout << "dij diff " << dijG - dijM << endl;

  return 0;
}
