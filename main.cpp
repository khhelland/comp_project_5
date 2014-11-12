#include <vector>
#include <cmath>
using namespace std;


int main()
{
  int N = 1e4;
  double dt = 1e-3;
  vector<double> particles;
  double D = 1;
  double step = sqrt(2*D*dt);

  particles.assign(N,0);
  

  for(t=0;t<T;t+=dt)//time loop
    {
      int add = 0;
      for (vector<double>::iterator it = particles.begin(); 
           it != particles.end; ++it)//loop over particles
        {
          //draw random number r
          double eps = 1e-10
            r = rand0();//??
          if (r<0.5)
            {
              if (*it!<eps)
                {
                  *it-=step;
                  if (*it < eps) particle.erase(it);
                }
            }
          else 
            {
              if(*it<eps) add++;
                             
              *it += step;
            }
          if (*it>1) particle.erase(it);
        }
      for(int i = 0; i < add; i++) particles.push_back(0);
      
    }
  return 0;
}
  
