#include <iostream>
#include <cstring>
#include <stdlib.h>
#include <fstream>
#include "vertex.h"
#include "edge.h"

using namespace std;

/*
Code by Michael Yan, 5/15/20
This code runs a graph creator that can create directed weighted edge
as well as identify the shortest path. Utilizes Dijkstra's Algorithm.
*/

int main(){
	while(true){
		cout << "\nEnter a command:" << endl;
		
		char* command = new char[10];
		cin.getline(command, 10);
		cin.clear();
		//cin.ignore(9999, '\n');

		if(strcmp(command, "add") == 0){ //add vertex
			bool vertexEdge;
			if()
		}

		else if(strcmp(command, "exit") == 0){ //exit program
			break;
		}

		else{ //if command is unrecognzied
			cout << "\nThat command is not supported." << endl;
		}
		

	}
	return 0;
}