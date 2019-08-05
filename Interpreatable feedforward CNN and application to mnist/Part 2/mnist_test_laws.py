import data3
import saab3
import pickle
import numpy as np
import sklearn
from sklearn.decomposition import PCA
from sklearn.cluster import KMeans
from numpy import linalg as LA
import matplotlib.pyplot as plt
from sklearn.metrics.pairwise import euclidean_distances

def filtering(img, Laws):
    for i in range(2, 30):
        for j in range(2, 30):
                total = 0
                for m in [-2, -1, 0, 1, 2]:
                    for n in [-2, -1, 0, 1, 2]:
                        total += img[i + m][j + n] * Laws[1][m+2][n+2]
    
                img[i-2][j-2] = total
    
    return img

filter= np.array([[-1, -2, 0, 2, 1],      #E5
                      [-1, 0, 2, 0, -1],      #S5
                      [-1, 2, 0, -2, 1]])      #W5

def main():
    # load data
    fr=open('pca_params6.pkl','rb')  
    pca_params=pickle.load(fr, encoding='latin1')
    fr.close()

    # read data
    train_images, train_labels, test_images, test_labels, class_list = data3.import_data("0-9")
    print('Training image size:', train_images.shape)
    print('Testing_image size:', test_images.shape)
    
    
    new_test_images = np.zeros((10000, 32, 32, 1))    
    for i in range(len(test_images)):
        new_test_images[i] = test_images[i]-np.mean(test_images[i], axis=None, keepdims=True)
        
    Laws = np.zeros((9,5,5), dtype=int)
    k=0
    for i in range(3):
        for j in range(3):
            Laws[k][:,:] = np.matmul(filter[i].reshape(5,1), filter[j].reshape(1,5))
            k += 1
    Laws = np.uint8(Laws)
    
    
    new_test_images2 = np.zeros((10000, 32, 32, 1))
    new_test_images2 = np.uint8(new_test_images2)
    
    for i in range(len(new_test_images)):
        new_test_images2[i] = filtering(new_test_images[i], Laws)
    
    

    # testing on conv layers
    print('--------Testing--------')
    feature=saab3.initialize(new_test_images2, pca_params)
    feature=feature.reshape(feature.shape[0],-1)
    print("S4 shape:", feature.shape)
    print('--------Finish Feature Extraction subnet--------')
    
    num_clusters=[120, 80, 10]
    use_classes=10
    fr=open('llsr_weights6.pkl','rb')  
    weights=pickle.load(fr)
    fr.close()
    fr=open('llsr_bias6.pkl','rb')  
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
            
    fw=open('test_pred_labels6.pkl','wb')    
    pickle.dump(feature, fw)    
    fw.close()


if __name__ == '__main__':
	main()

