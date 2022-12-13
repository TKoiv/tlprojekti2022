import numpy as np
import matplotlib.pyplot as plt
from tensorflow import keras
import pandas as pd
from sklearn.model_selection import train_test_split
#from tensorflow.keras import layers

# Model / data parameters
num_classes = 6
input_shape = (3)

file = ("file.csv")
data = pd.read_csv(file,delimiter=";")

numberOfRows = len(data.index)

datax = data.values[0::,5]
datay = data.values[0::,6]
dataz = data.values[0::,7]
label = data.values[0::,9]
# print("vanha",label)
label[0::] = label -1

labelMatrix = np.zeros((numberOfRows,1))
labelMatrix[:,0] = label

labelMatrix = keras.utils.to_categorical(labelMatrix, num_classes)

dataMatrix = np.zeros((numberOfRows,3))
dataMatrix[:,0] = datax
dataMatrix[:,1] = datay
dataMatrix[:,2] = dataz

# Load the data and split it between train and test sets

x_train, x_test, y_train, y_test = train_test_split(dataMatrix, labelMatrix, test_size=0.2)

model = keras.Sequential(
    [
        keras.Input(shape=input_shape),
        #layers.Dense(6, activation="relu", name='hidden1'),
        keras.layers.Dense(num_classes, activation="softmax", name='output'),
    ]
)

model.summary()

batch_size = 38
epochs = 300

model.compile(loss="categorical_crossentropy", optimizer="adam", metrics=["accuracy"])
model.fit(x_train, y_train, batch_size=batch_size, epochs=epochs)

weights = model.layers[0].get_weights()[0]
biases = model.layers[0].get_weights()[1]
print("Mallin painokertoimet weights ovat:")
print(weights)
print("")
print("Ja mallin bias arvot ovat:")
print(biases)

with open('parametritNeuro.h', 'w') as f:
  line = "float w[3][6] = {"
  for i in range(2):
    line = line + "{"
    outputThis = np.array2string(weights[i,:],precision=3,separator=',')
    line = line + outputThis[1:len(outputThis)-1]
    line = line + "},"
  outputThis = np.array2string(weights[2,:],precision=3,separator=',')
  line = line + "{"
  line = line + outputThis[1:len(outputThis)-1]
  line = line + "}"
  line = line + "};"
  f.write(line)
  f.write('\n')

  line = "float b[6] = {"
  outputThis = np.array2string(biases,precision=3,separator=',')
  line = line + outputThis[1:len(outputThis)-1] + "};"
  f.write(line)

  f.close()