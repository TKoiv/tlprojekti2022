import numpy as np
import matplotlib.pyplot as plt
from numpy import linalg as LA

file = "putty.log"

data = np.loadtxt(file)

datax = data[0::3]
datay = data[1::3]
dataz = data[2::3]

numberOfRows = len(data)
numberOfRows = int(numberOfRows)

print(numberOfRows)



row1 = np.array([datax[0:10],datay[0:10],dataz[0:10]])
row2 = np.array([datax[10:20],datay[10:20],dataz[10:20]])
row3 = np.array([datax[20:30],datay[20:30],dataz[20:30]])
row4 = np.array([datax[30:40],datay[30:40],dataz[30:40]])

max = np.max(data)
random = np.random.randint(max,size=(4,1))

print(random)

centerPointCumulativeSum = np.zeros((4,3))
#print(centerPointCumulativeSum)
counts = np.zeros(4)
#print(counts)
distances = np.zeros(4)

''' i=0
for i in len(numberOfRows):
    for x in data[i]:
       random[:0] - x ''' 


''' fig = plt.figure()
ax = fig.add_subplot(projection='3d')

xs = datax
ys = datay
zs = dataz
ax.scatter(xs, ys, zs)

ax.set_xlabel('X Label')
ax.set_ylabel('Y Label')
ax.set_zlabel('Z Label')

plt.show() '''


