#include <iostream>
#include <cstring>
#include "vertex.h"

//Colors
#define RESET "\033[0m"
#define RED   "\033[31m"
#define BLUE  "\033[34m"

using namespace std;

Vertex* findVertex(Vertex** list, char in, int IC);
void addVertex(Vertex **list, int IC);
void removeVertex(Vertex **list, int IC);
void addEdge(Vertex **list, int IC);
void removeEdge(Vertex **list, int IC);
void PRINT(Vertex **list, int IC);
void fastPath(Vertex** list, int IC);

int main() {
  Vertex **list = new Vertex*[20];
  int edgeList[20][20];
  int IC = 0; //index counter
  cout << "Graph Creator; C++ Edition (No GUI)" << endl;
  bool running = true;
  char command[15];
  while (running == true) {
    cout << endl << "Options: AddVer, DelVer, AddEdge, DelEdge, Print, Fpath, Quit" << endl;
    cin.get(command, 15);
    cin.clear();
    cin.ignore(10000, '\n');
    if (strcmp(command, "AddVer") == 0) { //Add Vertex
      addVertex(list, IC);
      IC++;
    }
    else if (strcmp(command, "DelVer") == 0) { //Delete Vertex
      removeVertex(list, IC);
      IC--;
    }
    else if (strcmp(command, "AddEdge") == 0) { //Add Edge
      addEdge(list, IC);
    }
    else if (strcmp(command, "DelEdge") == 0) { //Delete Edge
      removeEdge(list, IC);
    }
    else if (strcmp(command, "Print") == 0) { //Print
      PRINT(list, IC);
      cout << endl;
    }
    else if (strcmp(command, "Fpath") == 0) { //Shortest path algorithm, aka Dijkstra's algorithm
      cout << "Find the fastest path between two vertexs using Dijkstra's algorithm." << endl;
      fastPath(list, IC);
    }
    else if (strcmp(command, "Quit") == 0) { //Quit
      cout << endl << "Quitting Graph Creator" << endl;
      running = false;
    }
    else {
      cout << "Invalid input, try again." << endl << endl;
    }
  }
}

Vertex* findVertex(Vertex** list, char in, int IC) { //Find Vertex, used for Removing Vertexs, Adding and Removing edges
  int i = 0;
  while (i < IC) {
    if ((list[i])->getName() == in) {
      return (list[i]);
    }
    else {
      i++;
    }
  }
  return NULL;
}

void addVertex(Vertex **list, int IC) { //Add Vertex, adds a user inputted vertex
  //New vector object
  Vertex* newPt = new Vertex();
  newPt->setIndex(IC);
  char input;
  cout << "Character for new vertex >> ";
  cin >> input;
  cin.clear();
  cin.ignore(10000, '\n');
  //Assign input value to object
  newPt->setName(input);
  //Add vertex to list
  list[IC] = newPt;
  cout << endl << "Vertex " << newPt->getName() << " added." << endl;
}

void removeVertex(Vertex **list, int IC) { //Remove Vertex, deletes a user inputted vertex
  if (list[0] == NULL) {
    cout << endl << "No vertex to delete, add some first." << endl;
    return;
  }
  char input;
  cout << "Vertex to be deleted >> ";
  cin >> input;
  cin.clear();
  cin.ignore(10000, '\n');
  Vertex* v = findVertex(list, input, IC);
  if (v == NULL) {
    cout << endl << "No vector found. Try again." << endl;
    return;
  }
  int i = v->getIndex();
  v->~Vertex(); //Remove data from vertex
  cout << "Vertex at index " << i << " removed." << endl;
  //Redo edge list for every vertex
  for (int r = 0; r < IC; r++) {
    Vertex* current = list[r];
    for (int currEdge = i; currEdge < IC; currEdge++) {
      if (currEdge == IC - 1) {
	      current->setEdge(currEdge, 0);
      }
      else {
	//Move all edges above removed index down by 1 index
	int next = currEdge + 1;
	current->setEdge(currEdge, current->getEdge(next));
      }
    }
    list[r] = current;
  }
  //Remove index from list
  list[i] = NULL;
  //move all elements that follow down by 1 index
  while (i < IC) {
    if (i == IC - 1) {
      list[i] = NULL;
      break;
    }
    list[i] = list[i + 1];
    (list[i])->setIndex(i);
    i++;
  }
  cout << endl << "Vertex deleted." << endl;
}

void PRINT(Vertex **list, int IC) { //Print, prints out adjacency matrix
  char display[21][21];  //[row][col]
  //initialize empty matrix
  for (int r = 0; r < 21; r++) {
    for (int c = 0; c < 21; c++) {
      display[r][c] = ' ';
    }
  }
  int edgeDisplay[20][20];
  int count = 0;
  //construct adjacency matrix visual
  //first row and column
  while (count < IC) {
    display[0][count+1] = (list[count])->getName();
    display[count+1][0] = (list[count])->getName();
    count++;
  }
  //create edge display list
  for (int r = 0; r < IC; r++) {
    Vertex* v = list[r];
    for (int c = 0; c < IC; c++) {
      Vertex* vr = list[c];
      if (v->getEdge(vr->getIndex()) != 0) {
	      edgeDisplay[r][c] = 'T';
      } 
      else {
	      edgeDisplay[r][c] = 'F';
      }
    }
  }
  //place edge matrix in display array
  for (int r = 0; r < IC; r++) {
    for (int c = 0; c < IC; c++) {
      display[r+1][c+1] = edgeDisplay[r][c];
    }
  }
  //display adjacency matrix
  for (int r = 0; r < 21; r++) {
    for (int c = 0; c < 21; c++) {
      if (display[r][c] == 'T' && c != 0 && r != 0) {
	      cout << BLUE << display[r][c] << RESET << '\t';
      }  
      else if (display[r][c] == 'F' && c != 0 && r != 0) {
	      cout << RED << display[r][c] << RESET << '\t';
      } 
      else {
      	cout << display[r][c] << '\t';
      }
    }
    cout << endl;
    if (display[r+1][0] == ' ') break;
  }
}

void addEdge(Vertex **list, int IC) { //Add Edge, add an edge between two given vertexs
  if(list[0] == NULL || list[1] == NULL) {
    //Need at least two verticies
    cout << endl << "Have at least two verticies first." << endl;
    return;
  }
  char input1, input2;
  cout << endl << "Which two vertexs is this edge being added to?" << endl;
  cout << "Vertex 1 >> ";
  cin >> input1;
  cin.clear();
  cin.ignore(10000, '\n');
  cout << "Vertex 2 >> ";
  cin >> input2;
  cin.clear();
  cin.ignore(10000, '\n');
  Vertex* v1 = findVertex(list, input1, IC);
  Vertex* v2 = findVertex(list, input2, IC);
  if (v1 == NULL || v2 == NULL) {
    cout << endl << "Vertexs couldn't be located. Try again." << endl;
    return;
  }
  //Assign edge value
  cout << "Edge value >> ";
  int val;
  cin >> val;
  cin.clear();
  cin.ignore(10000, '\n');
  v1->setEdge(v2->getIndex(), val);
  v2->setEdge(v1->getIndex(), val);
}

void removeEdge(Vertex **list, int IC) { //Remove Edge, delete an edge between two given vertexs
  if(list[0] == NULL || list[1] == NULL) {
    //Need at least two verticies
    cout << endl << "Have at least two vertices first." << endl;
    return;
  }
  char input1, input2;
  cout << "What vectors are connected by this edge?" << endl;
  cout << "Vertex 1 >> ";
  cin >> input1;
  cin.clear();
  cin.ignore(10000, '\n');
  cout << "Vertex 2 >> ";
  cin >> input2;
  cin.clear();
  cin.ignore(10000, '\n');
  Vertex* v1 = findVertex(list, input1, IC);
  Vertex* v2 = findVertex(list, input2, IC);
  if (v1 == NULL || v2 == NULL) {
    cout << endl << "Vertexs couldn't be located. Try again." << endl;
    return;
  }
  v1->setEdge(v2->getIndex(), 0);
  v2->setEdge(v1->getIndex(), 0);
  cout << "Edge deleted." << endl;
}

void fastPath(Vertex** list, int IC) { //Fastest/Shortest path, Dijkstra's algorithm
  if (list[0] == NULL || list[1] == NULL) {
    //Need at least two verticies
    cout << endl << "Have at least two verticies first." << endl;
    return;
  }
  char input1, input2;
  cout << "Starting Vertex >> ";
  cin >> input1;
  cin.clear();
  cin.ignore(10000, '\n');
  cout << "Ending Vertex >> ";
  cin >> input2;
  cin.clear();
  cin.ignore(10000, '\n');
  Vertex* start = findVertex(list, input1, IC);
  Vertex* end = findVertex(list, input2, IC);
  if (start == NULL || end == NULL) {
    cout << endl << "Vertexs couldn't be located. Try again." << endl;
    return;
  }
	else {
    int max = IC;
    int n = IC;
    int INFINITY = 999; //Assuming 999 as Infinity value
    int startnode = start->getIndex();
    int destnode = end->getIndex();
    int cost[max][max],distance[max],pred[max];
    int visited[max],count,mindistance,nextnode,i,j,y,z;
    for(i = 0; i < n; i++){
        for(j = 0; j < n; j++){ 
            if(list[i]->getEdge(j) == 0){
                cost[i][j] = INFINITY;
            }
            else{
                cost[i][j] = list[i]->getEdge(j);
            }
        }
     }   

    // Main functionality (Algorithm)
   for(i = 0; i < n; i++) {
      distance[i] = cost[startnode][i];
      pred[i] = startnode;
      visited[i] = 0;
   }
   distance[startnode] = 0;
   visited[startnode] = 1;
   count = 1;
   while(count < n-1) {
      mindistance = INFINITY;
      for(i = 0; i < n; i++)
         if(distance[i] < mindistance && !visited[i]) {
         mindistance = distance[i];
         nextnode = i;
      }
      visited[nextnode] = 1;
      for(i = 0; i < n; i++)
         if(!visited[i])
      if(mindistance+cost[nextnode][i] < distance[i]) {
         distance[i] = mindistance+cost[nextnode][i];
         pred[i] = nextnode;
      }
      count++;
   }
    // Printing the shortest path along with the cost
   for(i = 0; i < n; i++) {
   if(i == destnode) {
      cout << "\nDistance/Cost: " << distance[i];
      cout << "\nPath: " << list[i]->getName();
      j = i;
      do {
         j = pred[j];
         cout << "<-" << list[j]->getName();
      }
      while(j != startnode);
    }
   }
  }
}
