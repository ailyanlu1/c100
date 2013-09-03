#ifndef VERTEX_HPP
#define VERTEX_HPP

/*
 * P4
 * Vertex.hpp
 * Implementation of Vertex class for Graph
 *
 * Author: Jay Dey cs100vaj
 * Author: Joshua Yuen cs100vbc
 */

#include "Edge.hpp"
#include <iostream>
#include <string>


using namespace std;

/* A class, instances of which are vertices in a Graph */
class Vertex
{
  private:
    string name;		/* name of current vertex (computer name) */
    Vertex * pre;		/* pointer to previous vertex */
    bool visited;		/* visited flag */
    vector<Edge> edgeList;	/* list of connected edges for this vertex */

  public:
    int dist;

    /* constructor */
    Vertex( string id )
    {
      name = id;
      visited = false;
    }

    /* destructor */
    ~Vertex()
    {
      edgeList.clear();
    }

};
#endif // VERTEX_HPP
