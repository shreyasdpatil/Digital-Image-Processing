#Name: Shreyas Patil
#USC Email: shreyasp@usc.edu
#Date: 4/28/2019

import data3
import saab3
import pickle
import numpy as np
import sklearn
import cv2
import keras
from sklearn.decomposition import PCA
from sklearn.cluster import KMeans
from numpy import linalg as LA
import matplotlib.pyplot as plt
from sklearn.metrics.pairwise import euclidean_distances

def main():
    # load data
    fr=open('pca_params10.pkl','rb')  
    pca_params=pickle.load(fr, encoding='latin1')
    fr.close()

    # read data
    train_images, train_labels, test_images, test_labels, class_list = data3.import_data("0-9")
    print('Training image size:', train_images.shape)
    print('Testing_image size:', test_images.shape)
    
    # testing on conv layers
    print('--------Testing--------')
    feature=saab3.initialize(test_images, pca_params)
    feature=feature.reshape(feature.shape[0],-1)
    print("S4 shape:", feature.shape)
    print('--------Finish Feature Extraction subnet--------')
    
    num_clusters=[120, 80, 10]
    fr=open('llsr_weights10.pkl','rb')  
    weights=pickle.load(fr)
    fr.close()
    fr=open('llsr_bias10.pkl','rb')  
    biases=pickle.load(fr)
    fr.close()

    for k in range(len(num_clusters)):
	# least square regression
        weight=weights['%d LLSR weight'%k]
        bias=biases['%d LLSR bias'%k]
        feature=np.matmul(feature,weight)
        feature=feature+bias
        print(k,' layer LSR weight shape:', weight.shape)
        print(k,' layer LSR bias shape:', bias.shape)
        print(k,' layer LSR output shape:', feature.shape)
		
#        if k!=len(num_clusters)-1:
#            pred_labels=np.argmax(feature, axis=1)
#            num_clas=np.zeros((num_clusters[k],use_classes))
#            for i in range(num_clusters[k]):
#                for t in range(use_classes):
#                    for j in range(feature.shape[0]):
#                        if pred_labels[j]==i and train_labels[j]==t:
#                            num_clas[i,t]+=1
#            acc_test=np.sum(np.amax(num_clas, axis=1))/feature.shape[0]
#            print(k,' layer LSR testing acc is {}'.format(acc_test))

			# Relu
        for i in range(feature.shape[0]):
            for j in range(feature.shape[1]):
                if feature[i,j]<0:
                    feature[i,j]=0  
                    
#        else:
        if k==len(num_clusters)-1:
            pred_labels=np.argmax(feature, axis=1)
            acc_test=sklearn.metrics.accuracy_score(test_labels,pred_labels)
            print('testing acc is {}'.format(acc_test))
            
        fw=open('test_feature10.pkl','wb')    
        pickle.dump(feature, fw)    
        fw.close()


if __name__ == '__main__':
	main()

