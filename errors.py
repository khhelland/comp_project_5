from numpy import *
from math import pi



def su(n,x,t):
    a = (-2/(n*pi))*sin(n*pi*x)*exp(-n*n*pi*pi*t)
    return a

v = zeros((30,30))
x = linspace(0,1,30)
X,Y = meshgrid(x,x);
t = 0.02
for a in range(1,3000):
    v += su(a,X,t)
v = v[:,1:-1]
# print amin(abs(v))

exp = loadtxt("exp.dat")[:,1:-1]
imp = loadtxt("jac.dat")[:,1:-1]

experr = amax(abs((exp-v)/v))
imperr = amax(abs((imp-v)/v))
print experr, imperr
