#ifndef edge_h
#define edge_h

#include <iostream>
#include "vertex.h"

using namespace std;

class Edge {
	public:
		Edge();
		~Edge(); //destructor
		Vertex* getFirst();
		void setFirst(Vertex*);
		Vertex* getSecond();
		void setSecond(Vertex*);
		int getWeight(); //return int
		void setWeight(int);
	private: //define
		Vertex* first;
		Vertex* second;
		int weight;
};

#endif
