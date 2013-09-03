#ifndef GRAPH_HPP
#define GRAPH_HPP

/*
 * P4
 * Graph.hpp
 * Header file for Graph class
 *
 * Author: Jay Dey cs100vaj
 * Author: Joshua Yuen cs100vbc
 */

#include <string>
#include <vector>
#include "Edge.hpp"
#include "Vertex.hpp"

using namespace std;

class Graph
{
  private:
    vector<Vertex *> vList;		/* list of vertices */
    bool cycle;				/* cycle detection flag */

  public:
    /* Constructor */
    Graph()
    {
      cycle = false;
    }

    /* Destructor */
    ~Graph()
    {
      for (int i=0; i<vList.size(); i++)
        delete vList[i];

      vList.clear();
    }

    /* find min spanning tree */
    Graph* MST();

    /* Dijkstra's shortest path method */
    Graph* dijkstra();
    
    /* print list of vertices and connected edges */
    void displayGraph();		

    /* total cost of graph */
    int totalCost();

    /* clear visited flags for all vertices */
    void reset();


    void addVertex( Vertex * newV );
    Vertex* findVertex( string name );
};

#endif //GRAPH_HPP
