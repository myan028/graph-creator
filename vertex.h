#ifndef vertex_h
#define vertex_h

#include <iostream>

using namespace std;

class Vertex {
	public:
		Vertex(char);
		~Vertex(); //destructor
		char getLabel();
		int getDistance(); //return int
		Vertex* getPrevious();
		void setLabel(char);
		void setDistance(int);
		void setPrevious(Vertex*);
	private:
		char label;
		int distance;
		Vertex* previous;
};

#endif
