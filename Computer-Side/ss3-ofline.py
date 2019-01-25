# Echo client program
import socket
import matplotlib.pyplot as plt
import numpy as np

def importar(arquivo):
  s=[]
  t=[]
  flag=0
  l=[]
  with open(arquivo) as csvfile:
    spamreader = csv.reader(csvfile, delimiter='\t', quotechar=',')
    for row in spamreader:
        if(len(row)>2):
            s.append(float(row[0]))
            t.append(float(row[2]))
  return s,t


import csv

[x,y]=importar('21_35_mb')
x=np.asarray(x)
y=np.asarray(y)
dx=10000*np.sum(x)/len(x)
dy=10000*np.sum(y)/len(x)




xl=0
yl=0


vx=np.zeros(40000)
vy=np.zeros(40000)
ct=0



with open('dat2') as csvfile:
  spamreader = csv.reader(csvfile, delimiter=' ', quotechar=',')
  for row in spamreader:
    if(len(row)>2):
      x=float(row[0])
      z=float(row[2])

      ct=ct+1
      xl=xl+x-dx
      yl=yl+z-dy
      vx[ct]=xl
      vy[ct]=-yl


	
plt.plot(vy[0:(ct+1)],vx[0:(ct+1)])
#plt.axis([-7e7, 7e7, -7e7, 7e7])

plt.show()