#include <armadillo>
#include <iostream>

using namespace std;
using namespace arma;

void explicit_step(mat &u, double dx, double dt)
{
  //matrix u(x,y): periodic border conditions so that u(x,0) <-> u(x,1)
  // and conditions u(0,y) = u(1,y) = 0 
 

  double alpha = dt/(dx*dx);
  int n = u.n_cols;
  mat v = u;
      
  for(int i=1; i<n-1; i++)
    {
      u(i,0) = v(i,0) + alpha*(v(i,1)+v(i,n-1) + v(i+1,0) + v(i-1,0) - 4*v(i,0));
      for(int j=1; j<n-1; j++)
        {
          u(i,j) = v(i,j) + alpha*(v(i+1,j)+v(i-1,j)+v(i,j+1)+v(i,j-1) - 4*v(i,j));
        }
      u(i,n-1) = v(i,n-1) + alpha*(v(i,0)+v(i,n-2) + v(i+1,n-1) + v(i-1,n-1) - 4*v(i,n-1));
    }
}



void solve(double dt, double dx, double T, mat v,
           void (*method)(mat&, double, double),
           const char* outfile )
{
  ofstream out(outfile);
     
  bool print1 = false;
    
  for(double t=0; t<T; t+=dt)
    {
      //update v
      method(v,dx,dt);
      
      //print to file
      if (t>=0.02 && !print1) 
        {
          out << v.t(); 
          print1 = true;
        }
    }
}


int main()
{
  //steps
  int n = 30;
  double dx = 1.0/n;
  double dt = 0.1*dx*dx;
  
  //total time
  double T  = 2;

  //initial state
  
  mat v=zeros<mat>(n,n);
  
  for(int j = 0; j<n; j++)
    for(int i = 1; i < n-1 ; i++) 
      v(i,j) = -1 + (i+1)*dx;
  //v(span(1,n-2),span()).fill(1);

  
  solve(dt,dx,T,v,*explicit_step,"exp.dat");
  
  return 0;
}
