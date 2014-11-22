#include <vector>
#include <random>
#include <iostream>
#include <fstream>
#include <cmath>
#include <algorithm>

using namespace std;

int main()
{
  int N = 1e3;
  double dt = 1e-3;
  double T = 3;
  vector<double> particles;
  double D = 0.1;
  double std = sqrt(2*D*dt);

  //RNG&PDF
  default_random_engine generator;
  normal_distribution<double> distribution(0,1);

  particles.assign(N,0);
  
  //time loop
  double nextPrintTime = 0;
  for(double t=0;t<T;t+=dt)
    {
      int add = 0;
      if(t > nextPrintTime) {
        double progress = t / T * 100;
        printf("t=%.2f ( %.2f%% ) %ld particles \r",t, progress, particles.size());
        fflush(stdout);
        nextPrintTime += 500*dt;
      }
            
      //loop over particles
      for (auto it = particles.begin();it != particles.end(); ++it) 
        {
          //draw random step
          //double eps = 1e-2;
          double step = std*distribution(generator);//??
          //if (*it<eps) 
            // {
            //   //reject backward move if particle is "at" 0
            //   if (step>=0)
            //     {
            //       *it+=step;
                  
            //       //add particles at 0 after timestep if particle moves from 0
            //       if(*it>eps) add++;
                  
            //     }
            // }
            //else 
            //{
          add += *it==0;
          *it += step;
              

          //erase particle if it moves to 0
          if (*it <= 0) {
            // particles.erase(it);it--; 
            swap(*it, particles.back());
            particles.pop_back();
            it--;
            continue;
          } 
              
              //erase particle if it moves beyond 1
          if (*it>=1) {
            // particles.erase(it);it--;
            swap(*it, particles.back());
            particles.pop_back();
            it--;
            continue;
          }
              //}
          
        }
      //add new particles to 0
      particles.resize(particles.size() + add, 0);
      // for(int i = 0; i < add; i++) particles.push_back(0);
    }
  
  ofstream out;
  out.open("1dgaussstepmc.dat");
  for(vector<double>::iterator it = particles.begin();it!=particles.end();it++)
    {
      out<<(*it)<<" ";
    }
  
  return 0;
}

