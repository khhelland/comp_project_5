from numpy import *
import matplotlib.pyplot as plt
from sys import argv



filename = str(argv[1])
#bins = linspace(1e-18,1,int(argv[2]))
bins = int(argv[2])
v = loadtxt(filename)


h,edges = histogram(v,bins = bins, normed = 0)
#h[0]-=10000
width = (edges[1]-edges[0])

h= h* (1-1.5*width)/h[1]

center = (edges[:-1] + edges[1:])/2
plt.bar(center, h, align = "center", width = width, label = "MC-simulation")

x = linspace(0,1,100)
plt.hold(1)
plt.plot(x,1-x,'r-',label="Analytical solution")
plt.legend()
plt.xlabel("x")
plt.ylabel("Normalised density u(x)")
plt.show()
