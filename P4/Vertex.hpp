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

    bool isVisited()
    {
      return visited;
    }

    void setVisited( bool status )
    {
      visited = status;
    }

    string getName()
    {
      return name;
    }

    Vertex* getPre()
    {
      return pre;
    }

    void setPre( Vertex * newPre )
    {
      pre = newPre;
    }

    vector<Edge>& getEdgeList()
    {
      return edgeList;
    }

    void printList()
    {
      for( int i=0; i<edgeList.size(); i++ )
      {
        Edge temp = edgeList[i];
	cout << "\t" << name << "->" << temp.getEnd()->getName() << endl;
      }
    }
    
    bool checkDupEdge( Edge * e )
    {
      for( int i=0; i<edgeList.size(); i++ )
      {
        Edge temp = edgeList[i];

        if( ( temp->getStart()->getName() == e.getStart()->getName() ) &&
	    ( temp->getEnd()->getName() == e.getEnd()->getName() ) )
	    return true;
      }
      return false;
    }

    void addAdjVertex( Vertex * adj, int cost, int time );
    {
      Edge * newEdge = new Edge( this, adj, cost, time );

      if (! checkDupEdge( newEdge ) )
        edgeList.push_back( *newEdge );
    }
};
#endif // VERTEX_HPP
