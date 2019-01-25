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

[x,y]=importar('09_14')
x=np.asarray(x)
y=np.asarray(y)
dx=10000*np.sum(x)/len(x)
dy=10000*np.sum(y)/len(x)



HOST = '192.168.43.1'    # The remote host
PORT = 8886              # The same port as used by the server
s = socket.socket(socket.AF_INET, socket.SOCK_STREAM)
s.connect((HOST, PORT))
#s.sendall('Hello, world')
#data = s.recv(1024)

xl=0
yl=0
vx=np.zeros(4000)
vy=np.zeros(4000)
ct=0



plt.ion()
plt.show()


arq = open('.\caos.txt', 'w')
arq.write("=============")

while 1:
	l=s.recv(100)
	l=l.decode('ascii')
	m=l.split()
	if len(m)>2:
		x=np.int(m[0])
		y=np.int(m[1])
		z=np.int(m[2])
	#print( x +y+z)#int(l.decode('ascii')) )   

	ct=ct+1
	xl=xl+x-dx
	yl=yl+z-dy
	vx[ct]=xl
	vy[ct]=yl
	
	plt.plot(vx[0:(ct+1)],vy[0:(ct+1)])
	plt.draw()
	plt.pause(0.001)

	#print('angle=')
	#print(np.arctan2(x-dx,z-dy))
	arq.write(repr(xl)+"\t"+repr(yl)+"\n")

#s.close()

#print 'Received', repr(data)


