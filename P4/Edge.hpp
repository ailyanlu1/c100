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

#include "Vertex.hpp"

using namespace std;

/* A class, whose instances are edges in Graph */
class Edge
{
  private:
    Vertex * start;
    Vertex * end;
    int cost;
    int time;

  public:
    /* constructor */
    Edge( Vertex * st, Vertex * en, int inCost, int inTime )
    {
      start = st;
      end = en;
      cost = inCost;
      time = inTime;
    }

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

#endif // EDGE_HPP