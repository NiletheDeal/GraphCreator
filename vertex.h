#ifndef VERTEX_H
#define VERTEX_H

using namespace std;

class Vertex {
 public:
  Vertex();
  ~Vertex();
  //Getters
  char getName();
  int getIndex();
  int getEdge(int);
  //Setters
  void setName(char);
  void setIndex(int);
  void setEdge(int, int);
 private:
  char name;
  int index;
  int edges[20];
};
#endif
