#include "RST.hpp"
#include "countint.hpp"
#include <cmath>
#include <iostream>
#include <algorithm>
#include <vector>
#include <set>

using namespace std;

/**
 * A simple benchmarking program for RST.
 */
static void show_usage()
{
  std::cerr << "./benchtree [rst, bst, set] [sorted, shuffled]"
               " [maximum tree size] [number of runs]" << endl;
}

int main (int argc, char** argv) 
{
  if(argc != 5)
  {
    show_usage();
    return 1;
  }

  // parse arg 1: type of structure
  if(strcmp(argv[1], "bst") == 0)
  {
    BST<countint> * bam = new BST<countint>();
  }
  else if (strcmp(argv[1], "rst") == 0)
  {
    RST<countint> * bam = new RST<countint>();
  }
  else if (strcmp(argv[1], "set") == 0)
  {
    std::set<countint> * bam = new std::set<countint>();
  }
  else
  {
    show_usage();
    return 1;
  }

  //parse arg 2: keys in sorted or randomized order
  if(strcmp(argv[2], "sorted") == 0)
  {
    std::vector<countint> v;
    v.clear();
  }
  else if(strcmp(argv[2], "shuffled") == 0)
  {

  }
  else
  {
    show_usage();
    return 1;
  }

  //parse arg 3: maximum size of tree
  if(isdigit(argv[3]))
  {
    int n = atoi (argv[3]);
  }
  else
  {
    show_usage();
    return 1;
  }

  //parse arg 4: number of runs
  if (isdigit(argv[4]))
  {
    int r = atoi( argv[4] );
  }
  else
  {
    show_usage();
    return 1;
  }
}
