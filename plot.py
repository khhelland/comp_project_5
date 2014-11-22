from numpy import *
from matplotlib.pyplot import *
from scipy.stats import kde
from sys import argv



filename = str(argv[1])
bins = int(argv[2])
v = loadtxt(filename)
#dense = kde.gaussian_kde(v)
x = linspace(0,1,100)
hist(v,bins = bins)
#plot(x,dense(x),'r')

show()
