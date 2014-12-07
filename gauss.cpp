/*
  name: gauss.cpp
  Program to simulate diffusion in synapse with a gaussian step random walk.
  The program requires c++11.
*/
#include <vector>
#include <random>
#include <algorithm>
#include <cmath>
#include <fstream>
#include <iostream>
#include <time.h>

using namespace std;


int main()
{
  int N = 1e4;
  double dt = 1e-3;
  double T = 1;
  vector<double> particles;
  double std = sqrt(2*dt);
  
  //RNG&PDF
  default_random_engine generator;
  normal_distribution<double> distribution(0,1);
  
  //initial state:
  particles.resize(N,0);
  
  double eps = 1e-14;

  clock_t start = clock();
  //time loop
  for(double t = 0; t<T; t+=dt)
    {
      int add = 0;
      //particle loop
      for(auto it = particles.begin(); it!=particles.end(); it++)
        {
          //draw random step
          double step = std*distribution(generator);
          
          //add particle at 0 if particle moves from 0
          add += (*it < eps);
          
          //step
          *it += step;
          
          //remove particle if it moves to < 0 or >= 1
          if ((*it < eps)||(*it >= 1)) 
            {
              swap(*it,particles.back());
              particles.pop_back();
              it--;              
              continue;
            }
        }
      //add the new particles
      particles.resize(particles.size()+add,0);

    }
  
  clock_t end = clock();
  
  cout<<"time: "<<((end-start)/(double)CLOCKS_PER_SEC)<<endl;
  ofstream out("gauss.dat");
  for(auto it = particles.begin(); it != particles.end(); it++)
    {out<<(*it)<<endl;}
  
  return 0;
}
  
