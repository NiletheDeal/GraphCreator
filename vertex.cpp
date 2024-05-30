#include <iostream>
#include "vertex.h"

using namespace std;

Vertex::Vertex() {
  name = '\0';
  index = -1;
}

Vertex::~Vertex() {
  //Destructor  
}

//Getters
char Vertex::getName() {
  return name;
}

int Vertex::getIndex() {
  return index;
}

//Setters
void Vertex::setName(char newName) {
  name = newName;
}

void Vertex::setIndex(int newIndex) {
  index = newIndex;
}
