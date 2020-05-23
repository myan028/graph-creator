#include <cstring>
#include <iostream>
#include <stdlib.h>
#include <fstream>
#include <cmath>
#include <vector>
#include <map>
#include "vertex.h"
#include "edge.h"

using namespace std;

/*
Code by Michael Yan, 5/15/20
This code runs a graph creator that can create directed weighted edge
as well as identify the shortest path. Utilizes Dijkstra's Algorithm.
*/



vector<Vertex*> vertices; //new vector system instead of purely nodes //easy searching and manipulate
vector<Edge*> edges;



void addVertex(char name){ //add vertex
	Vertex* current = new Vertex(name);
	
	bool exists = false;
	
	vector<Vertex*>::iterator it;
	
	for(it = vertices.begin(); it != vertices.end(); it++){
		if ((*it)->getLabel() == name){ //found
			exists = true;
		}
	}
	
	if(exists == false){ //add
		vertices.push_back(current);
		cout << "\nAdded vertex." << endl;
	}
	else{ //already exists
		cout << "\nThat vertex already exists." << endl;
	}
}



void addEdge(char name1, char name2, int weight){ //add edge
	Edge* current = new Edge();
	
	Vertex* first = NULL;
	Vertex* second = NULL;
	
	bool exists = false;

	vector<Vertex*>::iterator it;
	for (it = vertices.begin(); it != vertices.end(); it++){ //find the first and second vertices
		if((*it)->getLabel() == name1){
			first = *it;
		}
		if((*it)->getLabel() == name2){
			second = *it;
		}
	}

	if (first == second){
		cout << endl << "A vertex cannot be connected to itself. " << endl;
		return;
	}
  
	vector<Edge*>::iterator ite;
	
	for(ite = edges.begin(); ite != edges.end(); ite++){
		if(((*ite)->getFirst() == first && (*ite)->getSecond() == second)){
			exists = true;
		}
	}

	if(first != NULL && second != NULL && !exists){ //if no current edge and first and second exist
		current->setFirst(first);
		current->setSecond(second);
		current->setWeight(weight);
		
		edges.push_back(current);
		
		cout << "\nAdded edge" << endl;
	}
	else if(exists){
		cout << "\nEdge already exists." << endl;
	}
	else{ 
		cout << "\nVertex not found." << endl;
	}
}



void deleteEdge(char name1, char name2, bool user){ //remove edge
	if(edges.empty()){
		if(user){
			cout << "\nThere are no edges." << endl;
		}
		return;
	}

	Vertex* first = NULL;
	Vertex* second = NULL;

	vector<Vertex*>::iterator it;
	vector<Edge*>::iterator ite;

	for (it = vertices.begin(); it != vertices.end(); it++){
		if ((*it) -> getLabel() == name1){
			first = *it;
		}

		if((*it) -> getLabel() == name2){
			second = *it;
		}
	}

	if(first == second){
		cout << "\nA vertex cannot be connected to itself." << endl;
		return;
	}

	for (ite = edges.begin(); ite != edges.end(); ite++) {//removing edge from vector
		if (((*ite) -> getFirst() == first && (*ite) -> getSecond() == second)){
			edges.erase(ite);
			if(user){
				cout << "\nThe edge has been removed." << endl;
			}
			return;
		}
	}

	if (first != NULL && second != NULL && user){ //if edge doesn't exist
		cout << "\nThis edge does not exists." << endl;
	}
	
	else{ //first or last doesn't exist
		if(user){
			cout << "\nVertex not found." << endl;	
		}
	}
}



void deleteVertex(char label){ //remove vertex
	vector<Vertex*>::iterator it;
	vector<Edge*>::iterator ite;
	
	bool hasEdge = false;
	char yesno;

	if(vertices.empty()){ //if vector is empty
		cout << "\nThere are no vertices." << endl;
		return;
	}

	for(it = vertices.begin(); it != vertices.end(); it++){ //going through the vertices vector to find the vertex
		if((*it)->getLabel() == label){
			for(ite = edges.begin(); ite != edges.end(); ite++){
				if((*ite)->getFirst() == *it || (*ite)->getSecond() == *it){
					hasEdge = true;
				}
			}
			if(hasEdge){
				cout << "\nThat vertex is connected to an edge, would you still like to delete it? Type 'y' or 'n': ";
				cin >> yesno;
				cin.clear();
				cin.ignore(9999, '\n');
				if (yesno == 'y') {
					bool finished = false;
					while(!finished){
						for(ite = edges.begin(); ite != edges.end(); ite++){
							if(ite == edges.end() - 1){
								finished = true;
							}

							if((*ite) -> getFirst() == *it || (*ite) -> getSecond() == *it){ //if exists, remove both edge from and to that vertex
								deleteEdge((*ite)->getFirst()->getLabel(), (*ite)->getSecond()->getLabel(), false);
								deleteEdge((*ite)->getSecond()->getLabel(), (*ite)->getFirst()->getLabel(), false);
								break;
							}
						}
					}
					vertices.erase(it); //delete vertex at it
					cout << "\nVertex removed." << endl; 
					return;
				}
				else{
					cout << "\nVertex not removed." << endl;
					return;
				}
			}
			else{
				vertices.erase(it);
				cout << "\nVertex removed." << endl;
				return;
			}
		}
	}

	cout << "\nNo vertex found with that name." << endl;
  
}


//Dijkstra's algorithm HE



void printAdjacency(){ //matrix print algorithm
	
	cout << endl;
	
	if(vertices.empty()){ //if there are no vertices
		cout << "\nThere are no vertices." << endl;
		return;
	}

	cout << "	";
	
	vector<Vertex*>::iterator it;
	
	for(it = vertices.begin(); it != vertices.end(); it++){
		cout << (*it)->getLabel() << "	"; //format spacing
	}
	
	cout << endl;

	vector<Vertex*>::iterator iter; //iterators
	vector<Edge*>::iterator ite;
	
	for (it = vertices.begin(); it != vertices.end(); it++){ 
		cout << (*it)->getLabel() << "	"; //format spacing
			for(iter = vertices.begin(); iter != vertices.end(); iter++){
			bool connected = false;
			if(iter == it) {//vertices cannot be connected to themselves
				cout << "( )"; //if print nothing
				connected = true;
			}
			else{
				for(ite = edges.begin(); ite != edges.end(); ite++){
					if((*ite) -> getFirst() == *it){
						if((*ite) -> getSecond() == *iter){ //if edge in column-row vertices
							cout << (*ite) -> getWeight();
							connected = true;
						}
					}
				}
			}

			if (!connected){
				cout << "( )"; //no connections //print blank spot
			}

			cout << "	";
		}
		cout << endl;
	}
}



int main(){

	int numInput;
	char charInput;
	char charInput2;
	
	char char1;

	while(true){
		
		cout << "Enter a command: ";
		cout << "'av' to add vertex, 'ae' to add an edge, 'rv' to remove a vertex, 're' to remove an edge, 'print' to print the adjacency matrix, or 'exit' to exit the program."; << endl;
		
		cout << "Enter a command: ";
		
		char* command = new char[10];
		cin.getline(command, 10);
		cin.clear();
		//cin.ignore(9999, '\n');

		if(strcmp(command, "av") == 0){ //add vertex
			cout << "\nName the vertex: ";
			cin >> char1;
			cin.clear();
			cin.ignore(9999, '\n');
			addVertex(char1);
		}
		
		else if(strcmp(command, "ae") == 0){//add edge
			cout << "\nEnter the first vertex: ";
			cin >> char1;
			cin.clear();
			cin.ignore(9999, '\n');
			cout << "\nEnter the second vertex: ";
			cin >> charInput2;
			cin.clear();
			cin.ignore(9999, '\n');
			cout << "\nGive the edge a weight: ";
			cin >> numInput;
			cin.clear();
			cin.ignore(9999, '\n');
			addEdge(char1, charInput2, numInput);
		}
		
		else if(strcmp(command, "rv") == 0){//remove vertex
			cout << "\nEnter the vertex: " ;
			cin >> char1;
			cin.clear();
			cin.ignore(9999, '\n');
			deleteVertex(char1);
		}
		
		else if(strcmp(command, "re") == 0){//remove edge
			cout << "\nEnter the first vertex: " ;
			cin >> char1;
			cin.clear();
			cin.ignore(9999, '\n');
			cout << "\nEnter the second vertex: ";
			cin >> charInput2;
			cin.clear();
			cin.ignore(9999, '\n');
			deleteEdge(char1, charInput2, true);
		}
		
		else if (strcmp(command, "print") == 0){ //print matrix
			printAdjacency();
		}
		
		else if(strcmp(command, "exit") == 0){ //quit program
			
			break;
		}
		else{ //if command is unrecognzied
			cout << "\nThat command is not supported." << endl;
		}
	}
}