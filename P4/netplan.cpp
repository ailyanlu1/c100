/*
 * P4
 * netplan.cpp
 * main driver for program
 * read from infile, create graph, perform operations on graph
 *
 * Author: Jay Dey	cs100vaj
 * Author: Joshua Yuen	cs100vbc
 */

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
  ifstream in( argv[1] );

  Graph *gph = new Graph();
  string temp1, temp2;
  int cost, time;

  while ( !in.eof() )
  {
    in >> temp1 >> temp2 >> cost >> time;

    // reached end of file
    if( in.eof() )
      break;

    Vertex *v1, *v2;
    
    if ( gph->findVertex(temp1) == NULL )
    { //vertex temp1 does not exist in graph
      v1 = new Vertex(temp1);
      gph->addVertex(v1);
    }
    else
      //temp1 does exist, set v1 to found vertex
      v1 = gph->findVertex(temp1);

    if ( gph->findVertex(temp2) == NULL )
    {
      //vertex temp2 does not exist in graph
      v2 = new Vertex(temp2);
      gph->addVertex(v2);
    }
    else
      //temp2 does exist, set v2 to found vertex
      v2 = gph->findVertex(temp2);

    // connect v1 and v2
    v1->addAdjVertex( v2, cost, time);
  }

  /*if ( ! in.eof() )
  {
    cerr << "There was a problem, sorry." << endl;
    return -1;
  }
  */

  in.close();
  cout << "DONE." << endl;

  // TODO: DEBUGGING
  //gph->displayGraph();
  // not actually todo, I just wanted to make it easily seen

  int gCost = gph->totalCost();
  // total cost of graph
  cout << "g total cost " << gCost << endl;

  //construct MST from graph
  Graph * mst = gph->MST();

  // TODO: DEBUGGING
  //mst->displayGraph();
  // not actually todo, I just wanted to make it easily seen
  
  int mCost = mst->totalCost();
  // total cost of mst
  cout << "mst total cost " << mCost << endl;

  //difference in cost between graph and mst
  cout << "total cost diff " << gCost - mCost << endl;

  // run dijkstra algorithm on graph and mst
  int dijG = gph->dijkstra();
  int dijM = mst->dijkstra();

  // shortest dijkstra time of graph
  cout << "g dij " << dijG << endl;
  // shortest dijkstra time of mst
  cout << "m dij " << dijM << endl;

  // difference in timecost of dijkstra between graph and mst
  cout << "dij diff " << dijM - dijG << endl;

  //complete run, end program
  return 0;
}
