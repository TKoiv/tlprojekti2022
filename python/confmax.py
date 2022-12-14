import numpy as np 
from sklearn.metrics import confusion_matrix 
from numpy import genfromtxt  
import matplotlib.pyplot as plt



rawData = genfromtxt('putty_arduino.log', delimiter=',')  
y_true = rawData[:,0] 
y_pred = rawData[:,1] 
print(confusion_matrix(y_true, y_pred))

confusionMatrix = confusion_matrix(y_true,y_pred)

fig, ax = plt.subplots(figsize=(7.5, 7.5))
ax.matshow(confusionMatrix, cmap=plt.cm.Blues, alpha=0.3)
for i in range(confusionMatrix.shape[0]):
    for j in range(confusionMatrix.shape[1]):
        ax.text(x=j, y=i,s=confusionMatrix[i, j], va='center', ha='center', size='xx-large')
 
plt.xlabel('Predictions', fontsize=18)
plt.ylabel('Actuals', fontsize=18)
plt.title('Confusion Matrix', fontsize=18)
plt.show()