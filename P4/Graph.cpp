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

//Adding in Edge Support
std::pair<Edge*, Vertex*> Graph::dkHelper(Vertex* curr, vector<Edge> eList){
  cout << " " << endl;
  cout << "EnterDK " << endl;
  //cout << "Name: "<< curr->getName() << endl;
  Edge * pEdge = NULL;
  int tDist = std::numeric_limits<int>::max();
  for (int i=0; (unsigned)i<eList.size(); i++){
      //cout << "here" << endl;
    if (eList[i].getEnd()->isVisited() == false && tDist > eList[i].getTime()){
      /*cout <<"Beg: " << eList[i].getStart()->getName() << endl;
      cout <<"Dest: "<< eList[i].getEnd()->getName() << endl;
      cout <<"EdgeTime: "<< eList[i].getTime() << endl;*/
      //cout << i << "th time through loop" << endl;
      tDist = eList[i].getTime();
      pEdge = &(eList[i]);
    }
  }
  cout << "ExitDK " << endl;
  cout << " " << endl;
  if (pEdge != NULL){
    return std::make_pair(pEdge, pEdge->getStart());
  }
  else{
    Vertex * nullVert = NULL;
    return std::make_pair(pEdge, nullVert);
  }
}

int Graph::dijkstra()
{
  int sd = 0;
  for ( int x = 0; x<(int)vList.size(); x++ ){
    int totalTime = 0;
    this->reset();
    vector<Vertex*> visited;
    Vertex * curr = vList[x];
    curr->dist = 0;
    curr->setPre( NULL ); //keep an eye on this
    curr->setVisited(true);
    visited.push_back(curr);
    cout << "InitialName: " << curr->getName() << endl;
    vector<Vertex*>::iterator visIter = visited.begin();
    vector<Vertex*>::iterator visEn = visited.end();
  
    for( int i=0; i<(int)vList.size(); i++ ){
      if (i == x)
        continue;
      else
        //set all other vertice distances to "infinity"    
	vList[i]->dist = std::numeric_limits<int>::max(); 
    }
    
    std::pair<Edge*, Vertex*> pr1;
    std::pair<Edge*, Vertex*> pr2;
    while (visited.size() != vList.size()){
      int count = 0;
      for (; visIter != visEn; ++visIter){
        //cout << " " << endl;
        //cout << "Begin Loop" << endl;
	//cout << "Begin Name: " << (*visIter)->getName() << endl;
	vector<Edge> eList = (*visIter)->getEdges();
        pr1 = dkHelper(*visIter, eList);
	//cout << "here2" << endl;
        if (pr1.first == NULL){
          //all neighbor Vertices have been visited for curr
	  if (count != 0){
  	    count++;
	  }
  	  //cout << "All neighbor vertices have been visited " << endl;
          continue;
        }
        if (count == 0){
	  //cout << "Count is 0" << endl;
	  //cout << "pr1f start: " << pr1.second->getName() << endl;
          //cout << "pr1f end: " << pr1.first->getEnd()->getName() << endl;
	  //cout << "pr1f strt: " << pr1.first->getStart()->getName() << endl;
	  //cout << "pr1s: " << pr1.second << endl;
	  //cout << "pr2.first: " << pr2.first->getStart()->getName() << endl;
	  //cout << "pr2s: " << pr2.second << endl;
          pr2 = pr1;
	  //cout << "done assigning" << endl;
        }
	else
	  //cout << "Count is not 0" << endl;
	//cout << "LoopBegName: " << pr1.first->getStart()->getName() << endl;
        //cout << "LoopInDist: " << pr1.second << endl;
        //cout << "LoopLowDist: " << pr2.second << endl;
        if (pr2.first->getTime() > pr1.first->getTime()){
          pr2 = pr1;
  	  cout << "LoopNewLowDist: " << pr2.second << endl;
        }
        count++;
        //cout << "Endloop " << endl;
        //cout << " " <<endl;
      }
      count = 0;
      //set the vertex visited, set its distance, and push it into vector.
      cout << " " << endl;
      cout << "FinalDest: " << pr2.first->getEnd()->getName() << endl;
      cout << "FinalBeg: " << pr2.second->getName() << endl;
      //cout << "FinalBeg: " << (*visIter)->getName() << endl;
      pr2.first->getEnd()->setVisited(true);
      pr2.first->getEnd()->setPre(pr2.second);
      //pr2.first->getEnd()->setPre(*visIter);
      cout << "PreName: " << pr2.first->getEnd()->getPre()->getName() << endl;
      pr2.first->getEnd()->dist = pr2.first->getTime() + pr2.first->getEnd()->getPre()->dist;
      cout << "PreDist: " << pr2.first->getEnd()->getPre()->dist << endl;
      totalTime = pr2.first->getEnd()->dist + totalTime;
      cout << "totalTime: " << totalTime << endl;
      cout << " " << endl;
      visited.push_back(pr2.first->getEnd());
      //reset iterators for newly bigger vector.
      visIter = visited.begin();
      visEn = visited.end();
    }
    //cout << "totalTime: " << totalTime << endl;
    sd = sd + totalTime;
  }
  return sd;
}
