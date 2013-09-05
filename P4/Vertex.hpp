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
#include <vector>

using namespace std;

/* A class, instances of which are vertices in a Graph */
class Vertex
{
  private:
    string name;		/* name of current vertex (computer name) */
    Vertex * pre;		/* pointer to previous vertex */
    bool visited;		/* visited flag */
    vector<Edge> conList;	/* list of connected edges for this vertex */

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
      conList.clear();
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

    vector<Edge>& getConList()
    {
      return conList;
    }

    void printList()
    {
      for( int i=0; i<conList.size(); i++ )
      {
        Edge temp = conList[i];
	cout << "\t" << "->" << temp.getEnd()->getName() << endl;
      }
    }
    
    bool existEdge( Vertex * v )
    {
      for( int i=0; i<conList.size(); i++ )
      {
        Edge temp = conList[i];

        if( ( temp.getStart() == v ) || ( temp.getEnd() == v ) )
	    return true;
      }
      return false;
    }

    //TODO: make two-way operation, rather than calling twice
    void addAdjVertex( Vertex * adj, int cost, int time )
    {
      Edge * newEdge = new Edge( this, adj, cost, time );

      if (! existEdge( adj ) )
      {
        conList.push_back( *newEdge );
	Edge * otherEdge = new Edge( adj, this, cost, time );
	adj->conList.push_back( *otherEdge );
      }
    }

    vector<Edge> getEdges()
    {
      return conList;
    }
};
#endif // VERTEX_HPP
