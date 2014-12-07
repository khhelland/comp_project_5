from numpy import *
from matplotlib.pyplot import *
from mpl_toolkits.mplot3d import Axes3D

n = 30
a = loadtxt("2dgauss.dat")
h,x,y = histogram2d(a[:,0],a[:,1],bins = n)


x = linspace(0,1,n)
X,Y = meshgrid(x,x)
fig = figure()
ax = fig.add_subplot(111, projection="3d")
ax.plot_wireframe(X,Y,h.T)
ax.set_ylabel('y')
ax.set_xlabel('x')
ax.set_zlabel('z')

figure()
hist(a[:,0],bins = n)

figure()
hist(a[:,1],bins = n)

show()
