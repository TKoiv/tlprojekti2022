import numpy as np
import matplotlib.pyplot as plt


def dataReading():
    file = "putty.log"
    data = np.loadtxt(file)
    print("Data on: ", data)

    return data

def dataProcessing(data):

    global randomMax 
    global randomMin
    randomMax = np.max(data)
    randomMin = np.min(data)

    numberOfRows = len(data) / 3
    numberOfRows = int(numberOfRows)
    

    datax = data[0::3]
    datay = data[1::3]
    dataz = data[2::3]

    dataMatrix = np.zeros((numberOfRows,3))
    dataMatrix[:,0] = datax
    dataMatrix[:,1] = datay
    dataMatrix[:,2] = dataz

    return dataMatrix,numberOfRows

def randomData():
    random = np.random.randint(randomMin,randomMax,size=(4,3))

    return random

def kMeans(dataMatrix,random,numberOfRows):
    values = np.zeros(4)
    counts = np.zeros(4)
    averageDistance = np.zeros((4,3))
    centerPointCumulativeSum = np.zeros((4,3))
    for i in range(numberOfRows):
        for j in range(4):
            value1 = np.abs(np.sqrt(np.power((random[j,0]-dataMatrix[i,0]),2) + np.power((random[j,1]-dataMatrix[i,1]),2) + np.power((random[j,2]-dataMatrix[i,2]),2)))
            values[j] = value1
        
        index = np.argmin(values)
        counts[index] += 1
        centerPointCumulativeSum[index,0:3] += dataMatrix[i,0:3]
        
    apu1 = np.min(counts)
    y = 0

    if apu1 == 0:
        random = randomData()
        kMeans(dataMatrix,random,numberOfRows)
    elif apu1 != 0:
        for y in range(4):
            averageDistance[y] = (centerPointCumulativeSum[y] / counts[y])

        plotter(averageDistance,dataMatrix,numberOfRows)
        for k in range(10):
            iteration(averageDistance,dataMatrix,numberOfRows)
            k += 1
            print("iteration", k)
        plotter(averageDistance,dataMatrix,numberOfRows)
def iteration(averageDistance,dataMatrix,numberOfRows):
    averageDistance = averageDistance
    dataMatrix = dataMatrix
    numberOfRows = numberOfRows
    values = np.zeros(4)
    counts = np.zeros(4)
    centerPointCumulativeSum = np.zeros((4,3))
    for i in range(numberOfRows):
        for j in range(4):
            value1 = np.abs(np.sqrt(np.power((averageDistance[j,0]-dataMatrix[i,0]),2) + np.power((averageDistance[j,1]-dataMatrix[i,1]),2) + np.power((averageDistance[j,2]-dataMatrix[i,2]),2)))
            values[j] = value1
        
        index = np.argmin(values)
        counts[index] += 1
        centerPointCumulativeSum[index,0:3] += dataMatrix[i,0:3]
    y = 0  
    for y in range(4):
        averageDistance[y] = (centerPointCumulativeSum[y] / counts[y])
    

def plotter(averageDistance,dataMatrix,numberOfRows):
    
    fig = plt.figure()
    ax = fig.add_subplot(projection='3d')
    x = 0
    i = 0
    for x in range(numberOfRows):
        ax.scatter(dataMatrix[x,0],dataMatrix[x,1], dataMatrix[x,2], color="blue")
    for i in range(4):
        ax.scatter(averageDistance[i,0],averageDistance[i,1], averageDistance[i,2], marker="*",s=200)

    ax.set_xlabel('X Label')
    ax.set_ylabel('Y Label')
    ax.set_zlabel('Z Label')
    
    plt.show()

if __name__ == "__main__":
    data = dataReading()
    dataMatrix, numberOfRows = dataProcessing(data)
    random = randomData()
    kMeans(dataMatrix,random,numberOfRows)



