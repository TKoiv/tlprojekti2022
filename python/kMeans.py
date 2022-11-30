import numpy as np
import matplotlib.pyplot as plt
import pandas as pd


def dataReading():
    # file = "putty.log"
    # data = np.loadtxt(file)
    # print("Data on: ", data)
    file = "file.csv"
    data = pd.read_csv(file,delimiter=";")
    # print("Data on: ", data)
    # print(data.values[668,5])
    

    return data

def dataProcessing(data):

    global randomMax 
    global randomMin
    

    numberOfRows = len(data)
    numberOfRows = int(numberOfRows)
    
    datax = data.values[0::,5]
    datay = data.values[0::,6]
    dataz = data.values[0::,7]

    # datax = data[0::3]
    # datay = data[1::3]
    # dataz = data[2::3]

    dataMatrix = np.zeros((numberOfRows,3))
    dataMatrix[:,0] = datax
    dataMatrix[:,1] = datay
    dataMatrix[:,2] = dataz

    randomMax = np.max(data.values[0::,5:7])
    randomMin = np.min(data.values[0::,5:7])

    # randomMax = int(500)
    # randomMin = int(260)

    return dataMatrix,numberOfRows

def randomData():
    random = np.random.randint(randomMin,randomMax,size=(6,3))

    return random

def kMeans(dataMatrix,random,numberOfRows):
    values = np.zeros(6)
    counts = np.zeros(6)
    averageDistance = np.zeros((6,3))
    centerPointCumulativeSum = np.zeros((6,3))
    for i in range(numberOfRows):
        for j in range(6):
            value1 = np.abs(np.sqrt(np.power((random[j,0]-dataMatrix[i,0]),2) + np.power((random[j,1]-dataMatrix[i,1]),2) + np.power((random[j,2]-dataMatrix[i,2]),2)))
            values[j] = value1
        
        index = np.argmin(values)
        counts[index] += 1
        centerPointCumulativeSum[index,0:3] += dataMatrix[i,0:3]
        print(counts)
        
    apu1 = np.min(counts)
    y = 0

    if apu1 == 0:
        random = randomData()
        kMeans(dataMatrix,random,numberOfRows)
    elif apu1 != 0:
        for y in range(6):
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
    values = np.zeros(6)
    counts = np.zeros(6)
    centerPointCumulativeSum = np.zeros((6,3))
    for i in range(numberOfRows):
        for j in range(6):
            value1 = np.abs(np.sqrt(np.power((averageDistance[j,0]-dataMatrix[i,0]),2) + np.power((averageDistance[j,1]-dataMatrix[i,1]),2) + np.power((averageDistance[j,2]-dataMatrix[i,2]),2)))
            values[j] = value1
        
        index = np.argmin(values)
        counts[index] += 1
        centerPointCumulativeSum[index,0:3] += dataMatrix[i,0:3]
    y = 0  
    for y in range(6):
        averageDistance[y] = (centerPointCumulativeSum[y] / counts[y])
    

def plotter(averageDistance,dataMatrix,numberOfRows):
    
    fig = plt.figure()
    ax = fig.add_subplot(projection='3d')
    x = 0
    i = 0
    for x in range(numberOfRows):
        ax.scatter(dataMatrix[x,0],dataMatrix[x,1], dataMatrix[x,2], color="blue")
    for i in range(6):
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



