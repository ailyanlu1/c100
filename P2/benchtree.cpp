/*
 * P2
 * benchtree.cpp
 * Author: Jay Dey cs100vaj
 * Author: Joshua Yuen cs100vbc
 */

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
               " [maximum tree size] [number of runs]" << std::endl;
  }


int main (int argc, char** argv) 
{
  //incorrect usage
  if(argc != 5)
  {
    std::cout << "Amount of args: " <<argc <<std::endl;
    show_usage();
    return 1;
  }

  //parse arg 2: keys in sorted or randomized order
  int sorted = 0;
  int shuffled = 0;
  if(std::string(argv[2])== "sorted")
    sorted = 1;
  else if(std::string(argv[2])== "shuffled")
    shuffled = 1;
  else
  {
      std::cout << "2nd Arg: " <<argc <<std::endl;

    show_usage();
    return 1;
  }

  //parse arg 3: maximum size of tree
  int n = atoi( argv[3] );
  if ( n == 0 )
  {
      std::cout << "3rd arg " <<argc <<std::endl;

    show_usage();
    return 1;
  }

  //parse arg 4: number of runs
  int runs = atoi( argv[4] );
  if (runs == 0)
  {
      std::cout << "4th arg: " <<argc <<std::endl;

    show_usage();
    return 1;
  }

  std::cout<< "# Benchmarking average number of comparisons for successful find"
              "\n# Data structure: " << argv[1] << "\n"
	      "# Data: " << argv[2] << "\n"
	      "# N is powers of 2, minus 1, from 1 to " << n << "\n"
	      "# Averaging over " << runs << "runs for each N \n"
	      "#\n" 
	      "# N \t avgcomps \t stdev\n" << std::endl;
  
  /*
   * parse arg 1: type of data structure
   * bst, rst, set
   */
  if(strcmp(argv[1], "bst") == 0)
  {
    BST<countint> * bam = new BST<countint>();

    std::vector<countint> v;
    v.clear();
 
    //populate vector
    for (int i=0; i<n; i++)
      v.push_back(i);

    //shuffle if necessary
    if (shuffled == 1 && sorted != 1)
      std::random_shuffle(v.begin(), v.end());

    //insert keys into structure
    std::vector<countint>::iterator vit = v.begin();
    std::vector<countint>::iterator ven = v.end();
  
    for (vit = v.begin(); vit != ven; ++vit)
      bam->insert(*vit);

    //comparisons
    int x = 1; 
    while (x <= n)
    {
      double tot_avg = 0;
      double tot_sq_avg = 0;

      countint::clearcount();
      for (int a = 0; a < runs; a++)
      {
        for (vit = v.begin(); vit != ven; ++vit)
          bam->find(*vit);

        double avgcomps = countint::getcount() / (double)x;

        tot_avg = tot_avg + avgcomps;
        tot_sq_avg = tot_sq_avg + pow(avgcomps, 2);
      }  
        
      tot_avg = tot_avg / (double)runs;
      tot_sq_avg = tot_sq_avg / (double)runs;

      double stdev = sqrt(abs(tot_sq_avg - (pow(tot_avg, 2))));

      std::cout << x << " \t " << tot_avg << " \t " << stdev << "\n" << std::endl;
   
      //(x^2) - 1
      x = x*2+1;
    }
  }
  
  else if (strcmp(argv[1], "rst") == 0)
  {
    RST<countint> * ram = new RST<countint>();

    std::vector<countint> v;
    v.clear();
 
    //populate vector
    for (int i=0; i<n; i++)
      v.push_back(i);

    //shuffle if necessary
    if (shuffled == 1)
      std::random_shuffle(v.begin(), v.end());

    //insert keys into structure
    std::vector<countint>::iterator vit = v.begin();
    std::vector<countint>::iterator ven = v.end();
  
    for (vit = v.begin(); vit != ven; ++vit)
      ram->insert(*vit);

    //comparisons
    int x = 1; 
    while (x <= n)
    {
      double tot_avg = 0;
      double tot_sq_avg = 0;

      countint::clearcount();
      for (int a = 0; a < runs; a++)
      {
        for (vit = v.begin(); vit != ven; ++vit)
          ram->find(*vit);

        double avgcomps = countint::getcount() / (double)x;

        tot_avg = tot_avg + avgcomps;
        tot_sq_avg = tot_sq_avg + pow(avgcomps, 2);
      }
      
      tot_avg = tot_avg / (double)runs;
      tot_sq_avg = tot_sq_avg / (double)runs;

      double stdev = sqrt(abs(tot_sq_avg - (pow(tot_avg, 2))));

      std::cout << x << " \t " << tot_avg << " \t " << stdev << "\n" << std::endl;
    
      //(x^2) - 1
      x = x*2+1;
    }
  }

  else if (strcmp(argv[1], "set") == 0)
  {
    std::set<countint> * sam = new std::set<countint>();

    std::vector<countint> v;
    v.clear();
 
    //populate vector
    for (int i=0; i<n; i++)
      v.push_back(i);

    //shuffle if necessary
    if (shuffled == 1)
      std::random_shuffle(v.begin(), v.end());

    //insert keys into structure
    std::vector<countint>::iterator vit = v.begin();
    std::vector<countint>::iterator ven = v.end();
  
    for (vit = v.begin(); vit != ven; ++vit)
      sam->insert(*vit);

    //comparisons
    int x = 1; 
    while (x <= n)
    {
      double tot_avg = 0;
      double tot_sq_avg = 0;

      countint::clearcount();
      for (int a = 0; a < runs; a++)
      {
        for (vit = v.begin(); vit != ven; ++vit)
          sam->find(*vit);

        double avgcomps = countint::getcount() / (double)x;

        tot_avg = tot_avg + avgcomps;
        tot_sq_avg = tot_sq_avg + pow(avgcomps, 2);
      }

      tot_avg = tot_avg / (double)runs;
      tot_sq_avg = tot_sq_avg / (double)runs;

      double stdev = sqrt(abs(tot_sq_avg - (pow(tot_avg, 2))));

      std::cout << x << " \t " << tot_avg << " \t " << stdev << "\n" << std::endl;
    
      //x^2 - 1
      x = x*2+1;
    }
  }
  else
  {
      std::cout << "1st arg: " <<argc <<std::endl;

    show_usage();
    return 1;
  }



  //SUCCESS
  //std::cout << "\nYOU'RE A WINNER\n" << std::endl;
  return 0;
};


