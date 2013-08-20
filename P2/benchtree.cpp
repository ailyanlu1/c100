#include "RST.hpp"
#include "BST.hpp"
#include "countint.hpp"
#include "string.h"
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
  std::cerr << "./benchtree [rst / bst / set] [sorted / shuffled]"
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
    BST<countint> * bam = new BST<countint>();
  else if (strcmp(argv[1], "rst") == 0)
    RST<countint> * bam = new RST<countint>();
  else if (strcmp(argv[1], "set") == 0)
    std::set<countint> * bam = new std::set<countint>();
  else
  {
    show_usage();
    return 1;
  }

  //parse arg 3: maximum size of tree
  int n;
  if(isdigit(argv[3]))
    n = atoi (argv[3]);
  else
  {
    show_usage();
    return 1;
  }

  //parse arg 4: number of runs
  int r;
  if (isdigit(argv[4]))
    r = atoi( argv[4] );
  else
  {
    show_usage();
    return 1;
  }


  std::vector<countint> v;
  v.clear();

  //parse arg 2: keys in sorted or randomized order
  if(strcmp(argv[2], "sorted") == 0)
  {
    for (int i=0; i<n; ++i)
      v.push_back(i);
  }
  else if(strcmp(argv[2], "shuffled") == 0)
  {
    for (int i=0; i<n; ++i)
      v.push_back(i);

    std::random_shuffle(v.begin(), v.end());
  }
  else
  {
    show_usage();
    return 1;
  }

  std::vector<countint>::iterator vit = v.begin();
  std::vector<countint>::iterator ven = v.end();
  
  for (vit = v.begin(); vit != ven; ++vit)
    bam.insert(*vit);

  std::cout<< "# Benchmarking average number of comparisons for successful find"
              "\n# Data structure: " << argv[1] << "\n"
	      "# Data: " << argv[2] << "\n"
	      "# N is powers of 2, minus 1, from 1 to " << n << "\n"
	      "# Averaging over " << r << "runs for each N \n"
	      "#\n" 
	      "# N \t avgcomps \t stdev\n" << endl;
  
  //comparisons
  int x = 1;
  double tot_avg = 0;
  double tot_sq_avg = 0;
  
  while (x <= n)
  {
    countint::clearcount();
    for (int a = 0; a < r; a++)
    {
      for (vit = v.begin(); vit != ven; ++vit)
      {
        bam.find(*vit);

        double avgcomps = countint::getcount() / (double)n;

        tot_avg = tot_avg + avgcomps;
        tot_sq_avg = tot_sq_avg + pow(avgcomps, 2);
      }
    }
    tot_avg = tot_avg / r;
    tot_sq_avg = tot_sq_avg / r;

    double stdev = sqrt((tot_sq_avg - (pow(tot_avg, 2))));

    std::cout << x << " \t " << tot_avg << " \t " << stdev << "\n" << endl;
    
    x = ((x + 1) * 2) - 1;
  }

  return 1;
};
