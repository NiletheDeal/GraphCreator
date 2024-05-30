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
  //Setters
  void setName(char);
  void setIndex(int);
 private:
  char name;
  int index;
};
#endif
