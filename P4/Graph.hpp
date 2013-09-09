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
#include <utility>
#include <iterator>
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
      for (int i = 0; i< (int)vList.size(); i++){
        /*vector<Edge> E = vList[i]->getEdges();
	for(int j = 0; j< (int)E.size(); j++){
	  delete &(E[j]);
	}
	E.clear();*/
	delete vList[i];
	vList[i]=NULL;
      }
      vList.clear();
    }

    /* find min spanning tree */
    Graph* MST();

    /* Dijkstra's shortest path method */
    std::pair<Edge*, Vertex*> dkHelper(Vertex* curr);
    int dijkstra();
    
    /* print list of vertices and connected edges */
    void displayGraph();		

    /* total stats of graph */
    int totalCost();
    int totalTime();

    /* clear visited flags for all vertices */
    void reset();

    /* add vertex newV to vList */
    void addVertex( Vertex * newV );
    Vertex* findVertex( string name );
};

#endif //GRAPH_HPP
