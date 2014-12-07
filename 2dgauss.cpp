/*
  name: 2dgauss.cpp
  Program to simulate diffusion in synapse with a 2d gaussian step random walk.
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
 
  vector<vector<double> > particles;
  vector<double> add;
  double std = sqrt(2*dt);
  
  //RNG&PDF
  default_random_engine generator;
  normal_distribution<double> distribution(0,1/sqrt(2));
  
  //initial state:
  int Ny = 100;
  int ny = N/Ny;
  double dy = 1.0/(Ny-1);
  for(double y =0;y<=1;y+=dy)
    {particles.resize(particles.size() + ny, {0,y});}
    
  double eps = 1e-14;
  
  clock_t start = clock();
  //time loop
  for(double t = 0; t<T; t+=dt)
    {
      add.resize(0);
      //particle loop
          for(auto it = particles.begin(); it!=particles.end(); it++)
        {
          //draw random steps
          double xstep = std*distribution(generator);
          double ystep = std*distribution(generator);
          
          //add particle at 0 if particle moves from 0
          if(fabs((*it)[0]) < eps)
            {add.push_back((*it)[1]);}
          
          //xstep
          (*it)[0] += xstep;
          
          //remove particle if it moves to x <= 0 or x >= 1
          if (((*it)[0] < eps)||((*it)[0] >= 1)) 
            {
              swap(*it,particles.back());
              particles.pop_back();
              it--;              
              continue;
            }
          //ystep
          (*it)[1] += ystep;
          
          //move particle if it moves out of y
          if((*it)[1]<0) (*it)[1] +=1;
          else if ((*it)[1]>1) (*it)[1] -=1;
          
        }
      //add the new particles
      for(auto it = add.begin();it!=add.end();it++) particles.push_back({0,*it});
      
    }
  clock_t end = clock();
  cout<<"time: "<<((end-start)/(double)CLOCKS_PER_SEC)<<endl;

  ofstream out("2dgauss.dat");
  for(auto it = particles.begin(); it != particles.end(); it++)
    {out<<(*it)[0]<<" "<<(*it)[1]<<endl;}
  
  return 0;
}
  
