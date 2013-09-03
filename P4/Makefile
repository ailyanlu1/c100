# makefile for CSE 100 P4

CC=g++
CXXFLAGS=-g
LDFLAGS=-g

all: netplan

netplan: Graph.o

Graph.o: Graph.hpp Vertex.hpp Edge.hpp

## Vertex.o: Vertex.hpp

## Edge.o: Edge.hpp

clean:
	rm -f netplan *.o core*

purify:
	prep purify
	purify -cache-dir=$HOME g++ netplan.cpp Graph.cpp -o netplan
