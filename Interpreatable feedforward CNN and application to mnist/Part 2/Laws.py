#Name: Shreyas Patil
#USC Email: shreyasp@usc.edu
#Date: 4/28/2019

import numpy as np
from matplotlib import pyplot as plt
import cv2
from sklearn.cluster import KMeans
from sklearn.decomposition import PCA
from keras.datasets import mnist

def filtering(img):
    for i in range(2, 30):
        for j in range(2, 30):
                total = 0
                for m in [-2, -1, 0, 1, 2]:
                    for n in [-2, -1, 0, 1, 2]:
                        total += img[i + m][j + n] * Laws[0][m+2][n+2]
    
                img[i-2][j-2] = total
    
    return img
    

filter= np.array([[-1, -2, 0, 2, 1],      #E5
                  [-1, 0, 2, 0, -1],      #S5
                  [-1, 2, 0, -2, 1]])      #W5

(train_images, train_labels), (test_images, test_labels) = mnist.load_data()
#print(len(train_images[:10000]))
#print(train_labels[:10000].shape)

#train_images[:10000]
new_train_images = train_images[:10000]

#for i in range(len(train_images)):
#    train_images[i] = train_images[i]-np.mean(train_images[i], axis=None, keepdims=True)
    
for i in range(len(new_train_images)):
    new_train_images[i] = new_train_images[i]-np.mean(new_train_images[i], axis=None, keepdims=True)
    
#train_images=np.pad(train_images, ((0,0),(2,2),(2,2)), mode='constant')
new_train_images=np.pad(new_train_images, ((0,0),(2,2),(2,2)), mode='constant')

Laws = np.zeros((9,5,5), dtype=int)
k=0
for i in range(3):
    for j in range(3):
        Laws[k][:,:] = np.matmul(filter[i].reshape(5,1), filter[j].reshape(1,5))
        k += 1
Laws = np.uint8(Laws)


#outImagedata = np.zeros((60000, 32, 32))
#outImagedata = np.uint8(outImagedata)

outImagedata = np.zeros((10000, 32, 32))
outImagedata = np.uint8(outImagedata)

for i in range(len(new_train_images)):
    outImagedata[i] = filtering(new_train_images[i])
            
