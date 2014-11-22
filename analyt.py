from numpy import *
from math import pi
from mpl_toolkits.mplot3d import Axes3D
from matplotlib.pyplot import *


def su(n,x):
    a = (-2/(n*pi))*sin(n*pi*x)#*exp(-n*n*pi*pi*t)
    return a

v = zeros((30,30))
u = zeros((30,30))
x = linspace(0,1,30)
y = linspace(0,1,30)
X,Y = meshgrid(x,y);
t = 0
for a in range(1,3000):
    v += su(a,X)
         
#v -=u
fig = figure()
ax = fig.add_subplot(111, projection="3d")
ax.plot_wireframe(X,Y,v)
ax.set_ylabel('y')
ax.set_xlabel('x')
ax.set_zlabel('z')

show()
