from numpy import *
import matplotlib.pyplot as plt
from sys import argv



filename = str(argv[1])
bins = linspace(1e-18,1,int(argv[2]))
v = loadtxt(filename)


h,edges = histogram(v,bins = bins)
#h[0]-=10000
width = (edges[1]-edges[0])
center = (edges[:-1] + edges[1:])/2
plt.bar(center, h, align = "center", width = width)

plt.show()
