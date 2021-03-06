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
    int dist; 

  public:

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

    /* helper methods for access to private attributes */
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

    int getDist()
    {
      return dist;
    }

    void setDist(int nDist)
    {
      dist = nDist;
    }

    void setPre( Vertex * newPre )
    {
      pre = newPre;
    }
    
    vector<Edge>& getEdges()
    {
      return conList;
    }

    /* output list of edges connected to this vertex */
    void printList()
    {
      int size = (int)conList.size();
      for( int i=0; i<size; i++ )
      {
        Edge temp = conList[i];
	cout << "\t" << "->" << temp.getEnd()->getName() << endl;
      }
    }
    
    /* check if edge already exists in this conList */
    bool existEdge( Vertex * v )
    {
      int size = (int)conList.size();
      for( int i=0; i<size; i++ )
      {
        Edge temp = conList[i];

        if( ( temp.getStart() == v ) || ( temp.getEnd() == v ) )
	    return true;
      }
      return false;
    }

    /* adds adj as connected vertex through new edge
     * adds edge to conList for this, as well as vice versa for adj
     */
    void addAdjVertex( Vertex * adj, int cost, int time )
    {
      Edge newEdge( this, adj, cost, time );

      if (! existEdge( adj ) )
      {
        conList.push_back( newEdge );
	Edge otherEdge( adj, this, cost, time );
	adj->conList.push_back( otherEdge );
      }
      else if ( this->name == adj->name ){
        conList.push_back( newEdge );
      }
    }
};
#endif // VERTEX_HPP
