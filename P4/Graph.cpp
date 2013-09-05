/*
 * P4
 * Graph.cpp
 * Implementation of Graph class
 *
 * Author: Jay Dey 	cs100vaj
 * Author: Joshua Yuen	cs100vbc
 */

#include "Graph.hpp"
#include <iostream>

/* constructors defined in Graph.hpp */


void Graph::displayGraph()
{
  for( int i=0; i<vList.size(); i++ )
  {
    cout<<"Vertex " <<vList[i]->getName()<< " has the following edges: "<<endl;
    vList[i]->printList();
  }
}

int Graph::totalCost()
{
  int total = 0;

  // for each vertex in graph
  for( int i=0; i<vList.size(); i++ )
  {
    vector< Edge> e = vList[i]->getConList();
    // for each edge from current vector
    for( int j=0; j<e.size(); j++ )
    {
      Edge temp = e[i];
      // if end vertex not yet visited
      if ( vList[i]->getStatus() == e[j].getEnd()->getStatus() )
        total = total + e[i].getCost();
    }

    // vertex visited, move along now
    vList[i]->setStatus(true);
  }
}

/* clear status of all vertices */
void Graph::reset()
{
  for( int i=0; i<vList.size(); i++ )
    vList[i]->setStatus( false );
}

/* add vertex to vList */
void Graph::addVertex( Vertex * ve )
{
  vList.push_back( ve );
}

/* search for vertex by name */
Vertex* Graph::findVertex( string id )
{
  for( int i=0; i<vList.size(); i++ )
    if( vList[i]->getName() == id )
      return vList[i];

  return NULL;
}

Graph* Graph::MST()
{

}

Graph* Graph::dijkstra()
{

}
