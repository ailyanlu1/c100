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
  for( int i=0; i<(int)vList.size(); i++ )
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
  for( int i=0; i<(int)vList.size(); i++ )
  {
    vector<Edge> e = vList[i]->getEdges();
    // for each edge from current vector
    for( int j=0; j<(int)e.size(); j++ )
    {
      //Edge temp = e[i];
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
  for( int i=0; i<(int)vList.size(); i++ )
  {
    vector< Edge> e = vList[i]->getEdges();
    // for each edge from current vector
    for( int j=0; j<(int)e.size(); j++ )
    {
      //Edge temp = e[i];
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
  for( int i=0; i<(int)vList.size(); i++ )
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
  for( int i=0; i<(int)vList.size(); i++ )
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

  for( int i=0; i<(int)eList.size(); i++ )
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

      for( int j=0; j<(int)destList.size(); j++ )
        pQueue.push( destList[j] );
    }

  }
  return kenny;
}

//Selects Edge with lowest time(distance) for the input vertex
std::pair<Edge*, Vertex*> Graph::dkHelper(Vertex* curr){
  Edge * pEdge = NULL;
  vector<Edge> eList = curr->getEdges();
  int tDist = std::numeric_limits<int>::max();
  for (int i=0; i<(int)eList.size(); i++){
    if (eList[i].getEnd()->isVisited() == false && tDist > eList[i].getTime()){
      tDist = eList[i].getTime();
      pEdge = &(eList[i]);
    }
  }
  if (pEdge != NULL){
    return std::pair<Edge*, Vertex*>(pEdge, pEdge->getStart());
  }
  else{
    //cout << "pEdge NULL, Exiting DK" << endl;
    Vertex * nullVert = NULL;
    return std::pair<Edge*, Vertex*>(pEdge, nullVert);
  }
  eList.clear();
}

int Graph::dijkstra()
{
  int sd = 0;
  //For loop cycles through all vertices, running dijkstra's on all of them.
  for ( int x = 0; x<(int)vList.size(); x++ ){
    int totalTime = 0;
    this->reset();
    //create and initialize current vertex, associated iterators
    vector<Vertex*> visited;
    Vertex * curr = vList[x];
    curr->setDist(0);
    curr->setPre( NULL ); //keep an eye on this
    curr->setVisited(true);
    visited.push_back(curr);
    vector<Vertex*>::iterator visIter = visited.begin();
    vector<Vertex*>::iterator visEn = visited.end();
    
    //set all other vertex distances to "infinity"
    for( int i=0; i<(int)vList.size(); i++ ){
      if (i == x)
        continue;
      else
	vList[i]->setDist(std::numeric_limits<int>::max()); 
    }
    
    //cycle through all visited vertices looking for lowest new unvisited
    //edge
    while (visited.size() != vList.size()){
      std::pair<Edge*, Vertex*> pr1;
      std::pair<Edge*, Vertex*> pr2;
      int count = 0;
      for (; visIter != visEn; ++visIter){
        pr1 = dkHelper(*visIter);
        if (pr1.first == NULL){
	  //all neighbor Vertices have been visited for curr
	  if (count != 0){
  	    count++;
	  }
          continue;
        }
        if (count == 0){
	  pr2 = pr1;
	  count++;
        }
	if ( (pr2.first->getTime() + pr2.second->getDist()) > (pr1.first->getTime() + pr1.second->getDist())){
	  pr2 = pr1;
        }
      }
      //set the vertex visited, set its distance, and push it into vector.
      pr2.first->getEnd()->setVisited(true);
      pr2.first->getEnd()->setPre(pr2.second);
      pr2.first->getEnd()->setDist(pr2.first->getTime() + pr2.first->getEnd()->getPre()->getDist());
      visited.push_back(pr2.first->getEnd());
      //reset iterators for newly bigger vector.
      visIter = visited.begin();
      visEn = visited.end();
    }
    for(int i = 0; i < (int)visited.size(); i++){
      totalTime = visited[i]->getDist() + totalTime;
    }
    sd = sd + totalTime;
  }
  return sd;
}
