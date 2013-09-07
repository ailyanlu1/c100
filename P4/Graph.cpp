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
  for( int i=0; (unsigned)i<vList.size(); i++ )
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
  for( int i=0; (unsigned)i<vList.size(); i++ )
  {
    vector<Edge> e = vList[i]->getEdges();
    // for each edge from current vector
    for( int j=0; (unsigned)j<e.size(); j++ )
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
  for( int i=0; (unsigned)i<vList.size(); i++ )
  {
    vector< Edge> e = vList[i]->getEdges();
    // for each edge from current vector
    for( int j=0; (unsigned)j<e.size(); j++ )
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
  for( int i=0; (unsigned)i<vList.size(); i++ )
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
  for( int i=0; (unsigned)i<vList.size(); i++ )
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

  for( int i=0; (unsigned)i<eList.size(); i++ )
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

      for( int j=0; (unsigned)j<destList.size(); j++ )
        pQueue.push( destList[j] );
    }
  }
  return kenny;
}

std::pair<Vertex*,int> Graph::dkHelper(Vertex* curr){
  cout << " " << endl;
  cout << "EnterDK " << endl;
  cout << "Name: "<< curr->getName() << endl;
  vector<Edge> eList = curr->getEdges();
  Vertex * tVert;
  Vertex * pVert;
  int tDist = std::numeric_limits<int>::max();
  for (int i=0; (unsigned)i<eList.size(); i++){
    if (eList[i].getEnd()->isVisited() == false && 
      (tDist == std::numeric_limits<int>::max() || 
      tDist > eList[i].getTime())){
      cout <<"Dest: "<< eList[i].getEnd()->getName() << endl;
      cout <<"VertexTime: "<< eList[i].getTime() << endl;
      tDist = eList[i].getTime();
      //eList[i].getEnd()->dist = eList[i].getTime();
      //eList[i].getEnd()->setPre(eList[i].getStart());
      pVert = tVert = eList[i].getEnd();
    }
  }
  cout << "ChosenDest: " << pVert->getName() << endl;
  cout << "ChosenDestDist: " << tDist << endl;
  cout << "ExitDK " << endl;
  cout << " " << endl;
  return std::make_pair(pVert, tDist);
}

int Graph::dijkstra()
{
  int sd = 0;
  for ( int x = 0; (unsigned)x<vList.size(); x++ ){
    int totalTime = 0;
    this->reset();
    vector<Vertex*> visited;
    Vertex * curr = vList[x];
    curr->dist = 0;
    curr->setPre( NULL );
    curr->setVisited(true);
    visited.push_back(curr);
    cout << "InitialName: " << curr->getName() << endl;
    vector<Vertex*>::iterator visIter = visited.begin();
    vector<Vertex*>::iterator visEn = visited.end();
  
    for( int i=0; (unsigned)i<vList.size(); i++ ){
      if (i == x)
        continue;
      else
        //set all vertice distances to "infinity"    
	vList[i]->dist = std::numeric_limits<int>::max(); 
    }
    
    std::pair<Vertex*, int> pr1;
    std::pair<Vertex*, int> pr2;
    while (visited.size() != vList.size()){
      int count = 0;
      for (; visIter != visEn; ++visIter){
        pr1 = dkHelper(*visIter);
        if (count == 0){
          pr2 = pr1;
        }
        cout << " " << endl;
        cout << "Begin Loop" << endl;
        cout << "LoopName: " <<pr1.first->getName() << endl;
        if (pr1.first == NULL || pr1.second == -1){
        //all neighbor Vertices have been visited for curr
  	count++;
  	cout << "Shit's Happenin' " << endl;
          continue;
        }
        int comp1 = pr2.second;
        int comp2 = pr1.second;
        cout << "LoopInDist: " << pr1.second << endl;
        cout << "LoopLowDist: " << pr2.second << endl;
        if (comp1 > comp2){
          pr2 = pr1;
  	cout << "LoopNewLowDist: " << pr2.second << endl;
        }
        count++;
        cout << "Endloop " << endl;
        cout << " " <<endl;
      }
      
      count = 0;
      //set the vector visited, set its distance, and push it into vector.
      cout << " " << endl;
      cout << "Finalname: " << pr2.first->getName() << endl;
      pr2.first->setVisited(true);
      cout << "PreName: " << pr2.first->getPre()->getName() << endl;
      cout << "Pre: " << pr2.first->getPre()->dist << endl;
      pr2.first->dist = pr2.second + pr2.first->getPre()->dist;
      totalTime = pr2.second + totalTime;
      cout << "totalTime: " << totalTime << endl;
      cout << " " << endl;
      visited.push_back(pr2.first);
      //reset iterators for newly bigger vector.
      visIter = visited.begin();
      visEn = visited.end();
    }
    //cout << "totalTime: " << totalTime << endl;
    sd = sd + totalTime;
  }
  return sd;
}


