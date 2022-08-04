#include "simplegraph.h"

#include <fstream>
#include <iostream>
#include <list>
#include <vector>

using namespace std;

int main(int argc, char** argv) {
  if (argc < 2) {
    cerr << "args: input-file-name\n";
    return 1;
  }

  Graph g(argv[1]);

  g.Print();

  g.Traverse();

  return 0;
}