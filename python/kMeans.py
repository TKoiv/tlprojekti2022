import numpy as np
import matplotlib.pyplot as plt
from numpy import linalg as LA


def dataReading():
    file = "putty.log"
    data = np.loadtxt(file)
    return data

def dataProcessing(data):

    numberOfRows = len(data) / 3
    numberOfRows = int(numberOfRows)
    

    datax = data[0::3]
    datay = data[1::3]
    dataz = data[2::3]

    dataMatrix = np.zeros((numberOfRows,3))
    dataMatrix[:,0] = datax
    dataMatrix[:,1] = datay
    dataMatrix[:,2] = dataz
    #print(dataMatrix)
    #print(dataMatrix[0,1])

    

    #print(numberOfRows)


    row1 = np.array([datax[0:10],datay[0:10],dataz[0:10]])
    row2 = np.array([datax[10:20],datay[10:20],dataz[10:20]])
    row3 = np.array([datax[20:30],datay[20:30],dataz[20:30]])
    row4 = np.array([datax[30:40],datay[30:40],dataz[30:40]])

    ''' dataMatrix = np.arange(data)


    for idata in range(len(data)):
        print(data[idata+0]) '''

    return dataMatrix,numberOfRows, datax,datay,dataz

def randomData(data):
    max = np.max(data)
    min = np.min(data)
    random = np.random.randint(min,max,size=(4,3))
    #print("Random arvo on",random)
    #print("Eka arvo on: ",random[0])
    #print("Ekan eka arvo on: ",random[0,0])
    # print("Ekan toka arvo on: ",random[0,1])
    # print("Ekan kolmas arvo on: ",random[0,2])
    # xRandom = np.abs(np.sqrt(np.power(random[0,0],2)+np.power(random[1,0],2)+np.power(random[2,0],2)))
    # yRandom = np.abs(np.sqrt(np.power(random[1,0],2)+np.power(random[1,1],2)+np.power(random[1,2],2)))
    # zRandom = np.abs(np.sqrt(np.power(random[2,0],2)+np.power(random[2,1],2)+np.power(random[2,2],2)))
    # print("xRandom on",xRandom)
    # print("yRandom on",yRandom)
    # print("zRandom on",zRandom)

    return random

    


def kMeans(dataMatrix,random, numberOfRows,data):
    dataMatrix = dataMatrix
    numberOfRows = numberOfRows
    data = data
    distances = np.zeros(4)
    values = np.zeros(4)
    counts = np.zeros(4)
    averageDistance = np.zeros((4,3))
    centerPointCumulativeSum = np.zeros((4,3))
    for i in range(numberOfRows):
        for j in range(4):
            value1 = np.abs(np.sqrt(np.power((random[j,0]-dataMatrix[i,0]),2) + np.power((random[j,1]-dataMatrix[i,1]),2) + np.power((random[j,2]-dataMatrix[i,2]),2)))
            #print("Value 1 on: ", value1)
            values[j] = value1
        

        

        #print(values)
        index = np.argmin(values)
        print(index)
        distances[index] = values[index]
        distances = distances + distances 
        counts[index] += 1
        centerPointCumulativeSum[index,0:3] += dataMatrix[i,0:3]
        print("Yhteenlasketut",centerPointCumulativeSum)
        #print(distances)
        print(counts)
        apu1 = np.min(counts)

    if apu1 == 0:
        random = randomData(data)
        kMeans(dataMatrix,random, numberOfRows,data)
    else:
        for i in range(4):
            averageDistance[i] = (centerPointCumulativeSum[i] / counts[i])
            print("Average",averageDistance)

            #print(averageDistance[1,0])        
    return averageDistance










    ''' yRandom = np.abs(np.sqrt(np.power(random[1,0],2)+np.power(random[1,1],2)+np.power(random[1,2],2)))
        zRandom = np.abs(np.sqrt(np.power(random[2,0],2)+np.power(random[2,1],2)+np.power(random[2,2],2))) '''
    
    ''' centerPointCumulativeSum = np.zeros((numberOfRows,3))
        print(centerPointCumulativeSum)
        counts = np.zeros(4)
        print(counts)
        distances = np.zeros(4) '''
    
    #plotter()
    

def plotter(datax,datay,dataz,averageDistance):
    fig = plt.figure()
    ax = fig.add_subplot(projection='3d')

    ax.scatter(datax,datay,dataz, averageDistance)

    

    ax.set_xlabel('X Label')
    ax.set_ylabel('Y Label')
    ax.set_zlabel('Z Label')
    


    plt.show()

def plotter2(averageDistance,dataMatrix,numberOfRows):
    fig = plt.figure()
    ax = fig.add_subplot(projection='3d')
    for x in range(numberOfRows):
        ax.scatter(dataMatrix[x,0],dataMatrix[x,1], dataMatrix[x,2], color="blue")
    for i in range(4):
        ax.scatter(averageDistance[i,0],averageDistance[i,1], averageDistance[i,2], marker="*",s=200)

    

    ax.set_xlabel('X Label')
    ax.set_ylabel('Y Label')
    ax.set_zlabel('Z Label')
    


    plt.show()



if __name__ == "__main__":
    #Main program here!
    data = dataReading()
    #print(data)
    dataMatrix, numberOfRows, datax,datay,dataz = dataProcessing(data)
    random = randomData(data)
    averageDistance = kMeans(dataMatrix,random, numberOfRows,data)
    #plotter(datax,datay,dataz,averageDistance)
    plotter2(averageDistance,dataMatrix,numberOfRows)

    #print("Random", random)
    


