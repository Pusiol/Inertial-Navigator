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

import matplotlib.pyplot as plt
import csv
import numpy as np

[x,y]=importar('07_50_nimo')
plt.plot(x,y,'g')

print(x)

x=np.asarray(x)
y=np.asarray(y)




dx=x-np.sum(x)/len(x)
dy=y-np.sum(y)/len(x)

plt.plot(dx,dy,'b')

plt.axis([-40, 40, -40, 40])

plt.show()