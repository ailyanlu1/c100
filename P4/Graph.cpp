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
#include <queue>
#include <limits>
#include <vector>

/* constructors defined in Graph.hpp */


void Graph::displayGraph()
{
  for( int i=0; i<vList.size(); i++ )
  {
    cout<<"Vertex " <<vList[i]->getName()<< " has the following edges: "<<endl;
    vList[i]->printList();
  }
}

/*
 * cost of entire graph
 */
int Graph::totalCost()
{
  this->reset();
  int total = 0;

  // for each vertex in graph
  for( int i=0; i<vList.size(); i++ )
  {
    vector<Edge> e = vList[i]->getEdges();
    // for each edge from current vector
    for( int j=0; j<e.size(); j++ )
    {
      Edge temp = e[i];
      // if end vertex not yet visited
      if ( vList[i]->isVisited() == e[j].getEnd()->isVisited() )
        total = total + e[j].getCost();
    }

    // vertex visited, move along now
    vList[i]->setVisited(true);
  }
  return total;
}

/* 
 * total time of entire graph
 */
int Graph::totalTime()
{
  this->reset();
  int total = 0;

  // for each vertex in graph
  for( int i=0; i<vList.size(); i++ )
  {
    vector< Edge> e = vList[i]->getEdges();
    // for each edge from current vector
    for( int j=0; j<e.size(); j++ )
    {
      Edge temp = e[i];
      // if end vertex not yet visited
      if ( vList[i]->isVisited() == e[j].getEnd()->isVisited() )
        total = total + e[i].getTime();
    }

    // vertex visited, move along now
    vList[i]->setVisited(true);
  }
  return total;
}

/* 
 * clear status of all vertices 
 */
void Graph::reset()
{
  for( int i=0; i<vList.size(); i++ )
    vList[i]->setVisited( false );
}

/* 
 * add vertex to vList 
 */
void Graph::addVertex( Vertex * ve )
{
  vList.push_back( ve );
}

/* 
 * search for vertex by name 
 */
Vertex* Graph::findVertex( string id )
{
  for( int i=0; i<vList.size(); i++ )
    if( vList[i]->getName() == id )
      return vList[i];

  return NULL;
}

Graph* Graph::MST()
{
  //all vertices unvisited
  this->reset();

  Vertex * v = vList[0];
  v->setPre( NULL );
  v->setVisited( true );
  vector<Edge> eList = v->getEdges();

  priority_queue< Edge, vector<Edge>, EdgeCostCompare > pQueue;

  for( int i=0; i<eList.size(); i++ )
    pQueue.push( eList[i] );

  Graph * kenny = new Graph();
  while( ! pQueue.empty() )
  {
    //pop edge with lowest cost
    Edge e = pQueue.top();
    pQueue.pop();

    Vertex* begin = e.getStart();
    Vertex* end = e.getEnd();

    //if destination vertex not yet visited
    if( end->isVisited() != true )
    {
      //set start as pre vertex for end, mark visited
      end->setPre( begin );
      end->setVisited( true );
      vector<Edge> destList = end->getEdges();

      Vertex* v1 = new Vertex( begin->getName() );
      Vertex* v2 = new Vertex( end->getName() );

      //put vertices in kenny
      if( kenny->findVertex( v1->getName() ) == NULL ) 
        kenny->addVertex( v1 );
      else
        v1 = kenny->findVertex( v1->getName() );

      if( kenny->findVertex( v2->getName() ) == NULL )
        kenny->addVertex( v2 );
      else
        v2 = kenny->findVertex( v2->getName() );

      v1->addAdjVertex( v2, e.getCost(), e.getTime() );

      for( int j=0; j<destList.size(); j++ )
        pQueue.push( destList[j] );
    }
  }
  return kenny;
}

int Graph::dijkstra()
{
/*
  this->reset();
  int transtime = 0;
  Vertex * here = vList[0];
  here->dist = 0;
  here->setPre( NULL );
  //Vertex * temp;
  //temp->dist = std::numeric_limits<int>::max();
  //temp->setVisited( false );

  vector<Edge> eList = here->getEdges();
  priority_queue< Edge, vector<Edge>, EdgeTimeCompare > pQueue;

  for( int i=0; i<eList.size(); i++ )
    pQueue.push( eList[i] );

  while( !pQueue.empty() )
  {
    Edge e = pQueue.top();
    pQueue.pop();

    if( here->isVisited() == false )
    {
      transtime = transtime + e.getTime();
      here->setVisited( true );
    }
    else
    {
      for( int i=0; i<eList.size(); i++ )
        here->dist = here->dist + eList[i].getTime();
    }
  }
  return transtime;
*/

  this->reset();
  vector<Vertex*> unvList = vList;
  Vertex * curr = vList[0];
  curr->dist = 0;
  curr->setPre( NULL );

  for( int i=1; i<unvList.size(); i++ ){
    unvList[i]->dist = -1;
  }

  int tentDist=0;
  while (unVList.size() != 0){
    vector<Edge> eList = curr->getEdges();
    Vertex * tVert;
    Vertex * pVert;
    for (int i=0; i<eList.size(); i++){
      if (tentDist == 0 || tentDist > eList[i].time){
        tentDist = eList[i]->end->dist = eList[i].time + curr->dist;
	tVert = eList[i]->end;
	if (pVert != NULL){
	  pVert->dist =-1;
	}
	pVert = tVert;
      }
    }
    curr->setVisited(true);
    unVList.erase(i);
    if (tentDist == -1){
      break;
    }
    curr = tVert;
  }
}
