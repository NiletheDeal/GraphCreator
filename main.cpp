#include <iostream>
#include <cstring>

using namespace std;

int main() {
  cout << "Graph Creator; C++ Edition (No GUI)" << endl << endl;
  bool running = true;
  char command[15];
  while (running == true) {
    cout << "Options: AddVer, DelVer, AddEdge, DelEdge, Fpath, Quit" << endl;
    cin.get(command, 15);
    cin.clear();
    cin.ignore(10000, '\n');
    if (strcmp(command, "AddVer") == 0) { //Add Vertex

    }
    else if (strcmp(command, "DelVer") == 0) { //Delete Vertex

    }
    else if (strcmp(command, "AddEdge") == 0) { //Add Edge

    }
    else if (strcmp(command, "DelEdge") == 0) { //Delete Edge

    }
    else if (strcmp(command, "Fpath") == 0) { //Shortest path algorithm, aka Dijkstra's algorithm

    }
    else if (strcmp(command, "Quit") == 0) { //Quit

    }
    else {
      cout << "Invalid input, try again." << endl << endl;
    }
  }
}
