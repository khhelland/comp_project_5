#include <vector>
#include <random>
#include <iostream>
#include <fstream>
#include <cmath>

using namespace std;

int main()
{
  int N = 1e4;
  double dt = 1e-3;
  double T = 0.5;
  vector<double> particles;
  double D = 1;
  double std = sqrt(2*D*dt);

  //RNG&PDF
  default_random_engine generator;
  normal_distribution<double> distribution(0,1/sqrt(2));

  particles.assign(N,0);
  
  //time loop
  for(double t=0;t<T;t+=dt)
    {
      int add = 0;
      
      //loop over particles
      for (vector<double>::iterator it = particles.begin(); 
           it != particles.end(); ++it) 
        {
          //draw random step
          double eps = 1e-3;
          double step = distribution(generator);//??
          if (*it<eps) 
            {
              //reject backward move if particle is "at" 0
              if (step>=0)
                {
                  *it+=step;
                  
                  //add particles at 0 after timestep if particle moves from 0
                  if(*it>eps) add++;
                  
                }
            }
          else 
            {
              *it += step;
              
              //erase particle if it moves to 0
              if (*it < eps) particles.erase(it); 
              
              //erase particle if it moves beyond 1
              if (*it>=1) particles.erase(it);
            }
          
        }
      //add new particles to 0
      for(int i = 0; i < add; i++) particles.push_back(0);
    }
  
  ofstream out("1dgaussstepmc.dat");
  for(vector<double>::iterator it = particles.begin();it!=particles.end();it++)
    {
      out<<(*it)<<" ";
    }
  
  return 0;
}

