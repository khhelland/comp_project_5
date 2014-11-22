/* 
   Name: 2dpde.cpp
   Program implements an explicit and an implicit method of solving the two dimensional
   diffusion equation for the matrix u(x_i,y_j), with Dirichlet boundary conditions in x
   and periodic boundary conditions in y.
*/



#include <armadillo>
#include <iostream>

using namespace std;
using namespace arma;

void explicit_step(mat &u, double alpha)
{
  //function for moving u one time step according to the diffusion equation
  
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

void jacobi_step(mat &u, double alpha)
{
  //function for finding next time step implicitly
  //with the jacobi iterative method
  mat u_prev = u;
  int n = u.n_cols;
  mat v(n,n);
  double diff=1;
  int max_iter = 1e6;
      
  
  for(int it = 0; ((it<max_iter)&&(diff>1e-7)); it++)
    {
      v = u;
      diff = 0;
      for (int i = 1; i<n-1; i++)
        {
          u(i,0) = (1/(1+4*alpha))*(alpha*(v(i+1,0) + v(i-1,0)
                                           + v(i,1) + v(i,n-1)) + u_prev(i,0));
          for(int j = 1; j < n-1; j++)
            {
              u(i,j) = (1/(1+4*alpha))*(alpha*(v(i+1,j) + v(i-1,j)
                                               + v(i,j+1) + v(i,j-1)) + u_prev(i,j));
              diff += fabs(u(i,j)-v(i,j));
            }
          u(i,n-1) = (1/(1+4*alpha))*(alpha*(v(i+1,n-1) + v(i-1,n-1)
                                             + v(i,0) + v(i,n-2)) + u_prev(i,n-1));
        }
      diff/=((n-1)*(n-1));
    }
}



void solve(double dx, double dt, double T, mat v,
           void (*method)(mat&, double),
           const char* outfile )
{
  double alpha  = dt/(dx*dx);
  for(double t=0; t<T; t+=dt)  
    {method(v,alpha);}
  
  ofstream out(outfile);
  out << v.t(); 
}




int main()
{
  //steps
  int n = 30;
  double dx = 1.0/(n-1);
  double dt = 0.5*dx*dx;
  
  //total time
  double T  = 0.02;

  //initial state
  mat v=zeros<mat>(n,n);
  
  for(int j = 0; j<n; j++)
    for(int i = 1; i < n-1 ; i++) 
      v(i,j) = -1 + i*dx;
  
  solve(dx,dt,T,v,*explicit_step,"exp.dat");
  solve(dx,dt,T,v,*jacobi_step,"jac.dat");
  
  return 0;
}
