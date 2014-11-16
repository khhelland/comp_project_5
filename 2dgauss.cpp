/*
tror jeg kan bruke ca den samme koden som for 1d.
Hva med å bruke en vektor av 2-arrays?
randbetingelsene i y-retning?
hvordan skal partiklene ved x=0 fordeles langs y?
*/

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
  vector<vector<double> > particles;
  double D = 1;
  double std = sqrt(2*D*dt);
  double dy = std;

  //RNG&PDF
  default_random_engine generator;
  normal_distribution<double> distribution(0,1/sqrt(2));

  //particles.assign(N,{0,0});
  for(double y = 0; y <= 1; y+=dy) for(int i=0; i<N; i++) particles.push_back({0,y});
  
  //time loop
  for(double t=0;t<T;t+=dt)
    {
      int add = 0;
      
      //loop over particles
      for (vector<vector<double> >::iterator it = particles.begin(); 
           it != particles.end(); ++it) 
        {
          //draw random steps
          double eps = 1e-3;
          double xstep = distribution(generator);//??
          double ystep = distribution(generator);
          // x-step?
          ///////////////////////////////////////////////////////////////////
          if ((*it)[0]<eps) 
            {
              //reject backward move if particle is "at" 0
              if (xstep>=0)
                {
                  (*it)[0]+=xstep;
                  
                  //add particles at 0 after timestep if particle moves from 0
                  if((*it)[0]>eps) add++;
                  
                }
            }
          else 
            {
              (*it)[0] += xstep;
              
              //erase particle if it moves to 0
              if ((*it)[0] < eps) particles.erase(it); 
              
              //erase particle if it moves beyond 1
              if ((*it)[0]>=1) particles.erase(it);
            }
          ////////////////////////////////////////////////////////////
          //y-step?
          
          (*it)[1]+= ystep;
        }
      //add new particles to 0
      for(int i = 0; i < add; i++) particles.push_back({0,0});
    }
  
  ofstream out("1dgaussstepmc.dat");
  for(vector<double>::iterator it = particles.begin();it!=particles.end();it++)
    {
      out<<(*it)<<" ";
    }
  
  return 0;
}

