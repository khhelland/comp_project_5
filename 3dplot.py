from numpy import *
from matplotlib.pyplot import *
from mpl_toolkits.mplot3d import Axes3D
from sys import argv

v = loadtxt(str(argv[1]))

x = linspace(0,1,len(v))
X,Y = meshgrid(x,x)
fig = figure()
ax = fig.add_subplot(111, projection="3d")
ax.plot_wireframe(X,Y,v)
ax.set_ylabel('y')
ax.set_xlabel('x')
ax.set_zlabel('z')

figure()
imshow(v)
colorbar()

show()
