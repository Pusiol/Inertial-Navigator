# Echo client program
import socket
import matplotlib.pyplot as plt
import numpy as np

HOST = '192.168.0.112'    # The remote host
PORT = 8886              # The same port as used by the server
s = socket.socket(socket.AF_INET, socket.SOCK_STREAM)
s.connect((HOST, PORT))
#s.sendall('Hello, world')
#data = s.recv(1024)

xl=0
yl=0
vx=np.zeros(100)
vy=np.zeros(100)
ct=0



plt.ion()
plt.show()



while 1:
	l=s.recv(100)
	l=l.decode('ascii')
	m=l.split()
	x=np.int(m[0])
	y=np.int(m[1])
	z=np.int(m[2])
	print( x +y+z)#int(l.decode('ascii')) )   

	ct=ct+1
	xl=xl+y
	yl=yl+z
	vx[ct]=xl
	vy[ct]=yl
	
	plt.plot(vx[0:(ct+1)],vy[0:(ct+1)])
	plt.draw()
	plt.pause(0.001)


#s.close()

#print 'Received', repr(data)


