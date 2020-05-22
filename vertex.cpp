#include <iostream>
#include "vertex.h"

using namespace std;

Vertex::Vertex(char inLabel){
	label = inLabel;
	distance = -1;
	previous = NULL;
}

Vertex::~Vertex(){
	delete &label;
	delete &distance;
	delete previous;
}



char Vertex::getLabel(){
	return label;
}

void Vertex::setLabel(char inLabel){
	label = inLabel;
}



int Vertex::getDistance(){
	return distance;
}

void Vertex::setDistance(int inDistance){
	distance = inDistance;
}



Vertex* Vertex::getPrevious(){
	return previous;
}

void Vertex::setPrevious(Vertex* inPrevious){
	previous = inPrevious;
}
