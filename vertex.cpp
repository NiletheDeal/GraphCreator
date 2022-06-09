#include <iostream>
#include "vertex.h"

using namespace std;

Vertex::Vertex() {
  //Constructor
  name = '\0';
  int x = 0;
  while (x < 20) {
    edges[x] = 0;
    x++;
  }
}

Vertex::~Vertex() {
  //Destructor
  name = '\0';
  index = 0;
  int y = 0;
  while (y < 20) {
    edges[y] = 0;
    y++;
  }
}

//Getters
char Vertex::getName() {
  return name;
}

int Vertex::getIndex() {
  return index;
}

int Vertex::getEdge(int from) {
  return edges[from];
}

//Setters
void Vertex::setName(char newName) {
  name = newName;
}

void Vertex::setIndex(int newIndex) {
  index = newIndex;
}

void Vertex::setEdge(int from, int value) {
  edges[from] = value;
}
