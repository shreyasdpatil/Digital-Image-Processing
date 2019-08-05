#Name: Shreyas Patil
#USC Email: shreyasp@usc.edu
#Date: 4/28/2019

import pickle
import numpy as np
import data1
import saab1
import keras
import sklearn
import cv2

def main():
    # load data
    fr=open('pca_params.pkl','rb')  
    pca_params=pickle.load(fr)
    fr.close()
    
    # read data
    train_images, train_labels = data1.import_data("0-9")
    print('Training image size:', train_images.shape)

    # Training
    print('--------Training--------')
    feature=saab1.initialize(train_images, pca_params) 
    print("features", feature)
    
    feature=feature.reshape(feature.shape[0],-1)
    print("S4 shape:", feature.shape)
    print('--------Finish Feature Extraction subnet--------')
    feat={}
    feat['feature']=feature
    	
    # save data
    fw=open('feat.pkl','wb')    
    pickle.dump(feat, fw)    
    fw.close()

if __name__ == '__main__':
	main()
