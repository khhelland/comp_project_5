/*
  name: const.cpp
  Program to simulate diffusion in synapse with a constant step random walk.
  The program requires c++11.
*/
#include <vector>
#include <random>
#include <algorithm>
#include <cmath>
#include <fstream>
#include <iostream>

using namespace std;


int main()
{
  int N = 1e4;
  double dt = 1e-3;
  double T = 0.5;
  vector<double> particles;
  double std = sqrt(2*dt);
  
  //RNG&PDF
  default_random_engine generator;
  uniform_real_distribution<double> distribution(0,1);
  
  //initial state:
  particles.resize(N,0);
  
  double eps = 1e-14;
  //time loop
  for(double t = 0; t<T; t+=dt)
    {
      int add = 0;
      //particle loop
      for(auto it = particles.begin(); it!=particles.end(); it++)
        {
          //draw random step
          double r = distribution(generator);
          double step = (r<0.5)? -std : std;
          
          //add particle at 0 if particle moves from 0
          add += (fabs(*it) < eps);
          
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
      //cout<<add<<endl;
    }
  //cout <<particles.size()<<endl;
  ofstream out("const.dat");
  for(auto it = particles.begin(); it != particles.end(); it++)
    {out<<(*it)<<endl;}
  
  return 0;
}
  
