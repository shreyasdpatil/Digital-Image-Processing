#Name: Shreyas Patil
#USC Email: shreyasp@usc.edu
#Date: 4/28/2019

import keras
from keras.datasets import mnist
import numpy as np
import saab1
import cv2

def get_data_for_class(images, labels, cls):
	if type(cls)==list:
		idx=np.zeros(labels.shape, dtype=bool)
		for c in cls:
			idx=np.logical_or(idx, labels==c)
	else:
		idx=(labels==cls)
	return images[idx], labels[idx]

def import_data(use_classes):
#   img1 = cv2.imread('1.png') 
#   img2 = cv2.imread('2.png') 
#   img3 = cv2.imread('3.png') 
#   img4 = cv2.imread('4.png') 
#   input_imgs =  np.vstack(([img1[:,:,0]], [img2[:,:,0]], [img3[:,:,0]], [img4[:,:,0]]))
#   input_labels = np.array([9, 0, 5, 3])
#   input_imgs=input_imgs.reshape(-1,32,32,1)
#   input_imgs=input_imgs/255.
   
   img1 = cv2.imread('1.png') 
   img2 = cv2.imread('2.png') 
   img3 = cv2.imread('3.png') 
   img4 = cv2.imread('4.png') 
#   input_imgs =  np.vstack(([img1[:,:,0]]))
   input_imgs =  np.vstack(([img1[:,:,0]], [img2[:,:,0]], [img3[:,:,0]], [img4[:,:,0]]))
   
#   input_labels = np.array([9])
#   input_labels = np.array([0])
#   input_labels = np.array([5])
#   input_labels = np.array([3])
   input_labels = np.array([9, 0, 5, 3])
   
   input_imgs=input_imgs.reshape(-1,32,32,1)
   input_imgs=input_imgs/255.
 

		
   return input_imgs, input_labels

