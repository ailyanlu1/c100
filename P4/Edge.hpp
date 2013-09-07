#ifndef EDGE_HPP
#define EDGE_HPP

/*
 * P4
 * Edge.hpp
 * Implementation of Edge class for Graph
 *
 * Author: Jay Dey cs100vaj
 * Author: Joshua Yuen cs100vbc
 */

//#include "Vertex.hpp"
class Vertex;
#include <iostream>

using namespace std;

/* A class, whose instances are edges in Graph */
class Edge
{
  private:
    Vertex * start;		// start node of this edge
    Vertex * end;		// end node of this edge
    int cost;			// cost of this edge, specified by infile
    int time;			// timecost of this edge

  public:
    /* constructor */
    Edge( Vertex * st, Vertex * en, int inCost, int inTime )
    {
      start = st;
      end = en;
      cost = inCost;
      time = inTime;
    }

    /* helper methods for access to private attributes */
    Vertex* getStart()
    {
      return start;
    }

    Vertex* getEnd()
    {
      return end;
    }

    int getCost()
    {
      return cost;
    }

    int getTime()
    {
      return time;
    }
};

/* operator overloads for priority queue */
class EdgeCostCompare
{
  public:
    bool operator()( Edge e1, Edge e2 )
    {
      return ( e1.getCost() > e2.getCost() );
    }
};

class EdgeTimeCompare
{
  public:
    bool operator()( Edge e1, Edge e2 )
    {
      return ( e1.getTime() > e2.getTime() );
    }
};
#endif // EDGE_HPP
