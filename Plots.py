from numpy import genfromtxt, linspace, min, max
import matplotlib.pyplot as plt

datos2 = genfromtxt('salidat2', delimiter=',')
datos1 = genfromtxt("RadialVelocities.dat", delimiter=' ')

datos1 = datos1[1:,:]
datos2 = datos2[1:,:]

rmin = min(datos1[:,0])
rmax = max(datos1[:,0])
n = len(datos1)

r = linspace(rmin, rmax, n)

plt.plot(datos1[:,0], datos1[:,1], color="green")


Mb = datos2[-1,0]
Md = datos2[-1,1]
Mh = datos2[-1,2]

v = Mb**0.5*r/(r**2+0.2497**2)**0.75 + Md**0.5*r/( r**2+(5.16+0.3105)**2)**0.75 + Mh**0.5/(r**2+64.3**2)**0.25

plt.plot(r, v, color="blue")

plt.legend(['Datos', 'Modelo'], loc='best')
plt.xlabel('r'); plt.ylabel('v')
plt.savefig('datos-modelo.png')