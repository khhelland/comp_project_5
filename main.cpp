#include <vector>
#include <random>
#include <iostream>
#include <fstream>

using namespace std;

int main()
{
  int N = 1e4;
  double dt = 1e-3;
  double T = 1;
  vector<double> particles;
  double D = 1;
  double step = sqrt(2*D*dt);

  //RNG&PDF
  default_random_engine generator;
  uniform_real_distribution<double> distribution(0,1);

  particles.assign(N,0);
  
  //time loop
  for(double t=0;t<T;t+=dt)
    {
      int add = 0;
      //loop over particles
      for (vector<double>::iterator it = particles.begin(); 
           it != particles.end(); ++it) 
        {
          //draw random number r
          double eps = 1e-10;
          double r = distribution(generator);//??
          if (r<0.5) //positive move
            {
              //reject backward move if particle is "at" 0
              if ((*it)>=eps)
                {
                  *it-=step;
                  //erase particle if it moves to 0
                  if (*it < eps) particles.erase(it);  }
            }
          //negative move
          else 
            {
              //add particles at 0 after timestep if particle moves from 0
              if(*it<eps) add++;
              
              *it += step;
              //erase particle if it moves beyond 1
              if (*it>=1) particles.erase(it);
            }
        }
      //add new particles to 0
      for(int i = 0; i < add; i++) particles.push_back(0);
    }
  
  ofstream out("1dconststepmc.dat");
  for(vector<double>::iterator it = particles.begin();it!=particles.end();it++)
    {
      out<<(*it)<<" ";
    }
  
  return 0;
}
  
