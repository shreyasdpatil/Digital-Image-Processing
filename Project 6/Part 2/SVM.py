#Name: Shreyas Patil
#USC Email: shreyasp@usc.edu
#Date: 4/28/2019

import pickle
import numpy as np
from sklearn.decomposition import PCA
from sklearn.cluster import KMeans
from numpy import linalg as LA
import matplotlib.pyplot as plt
from sklearn.metrics.pairwise import euclidean_distances
from sklearn.svm import SVC
from keras.datasets import mnist
from sklearn.metrics import accuracy_score
#from sklearn.metrics import confusion_matrix
from mlxtend.evaluate import confusion_matrix 
from mlxtend.plotting import plot_confusion_matrix

#Loading train data
fr = open('feature1.pkl','rb')  
feature1 = pickle.load(fr, encoding='latin1')
fr.close()

fr = open('feature2.pkl','rb')  
feature2 = pickle.load(fr, encoding='latin1')
fr.close()

fr = open('feature3.pkl','rb')  
feature3 = pickle.load(fr, encoding='latin1')
fr.close()

fr = open('feature4.pkl','rb')  
feature4 = pickle.load(fr, encoding='latin1')
fr.close()

fr = open('feature5.pkl','rb')  
feature5 = pickle.load(fr, encoding='latin1')
fr.close()

fr = open('feature6.pkl','rb')  
feature6 = pickle.load(fr, encoding='latin1')
fr.close()

fr = open('feature7.pkl','rb')  
feature7 = pickle.load(fr, encoding='latin1')
fr.close()

fr = open('feature8.pkl','rb')  
feature8 = pickle.load(fr, encoding='latin1')
fr.close()

fr = open('feature9.pkl','rb')  
feature9 = pickle.load(fr, encoding='latin1')
fr.close()

fr = open('feature10.pkl','rb')  
feature10 = pickle.load(fr, encoding='latin1')
fr.close()


#Loading test data
fr = open('test_feature1.pkl','rb')  
test_feature1 = pickle.load(fr, encoding='latin1')
fr.close()

fr = open('test_feature2.pkl','rb')  
test_feature2 = pickle.load(fr, encoding='latin1')
fr.close()

fr = open('test_feature3.pkl','rb')  
test_feature3 = pickle.load(fr, encoding='latin1')
fr.close()

fr = open('test_feature4.pkl','rb')  
test_feature4 = pickle.load(fr, encoding='latin1')
fr.close()

fr = open('test_feature5.pkl','rb')  
test_feature5 = pickle.load(fr, encoding='latin1')
fr.close()

fr = open('test_feature6.pkl','rb')  
test_feature6 = pickle.load(fr, encoding='latin1')
fr.close()

fr = open('test_feature7.pkl','rb')  
test_feature7 = pickle.load(fr, encoding='latin1')
fr.close()

fr = open('test_feature8.pkl','rb')  
test_feature8 = pickle.load(fr, encoding='latin1')
fr.close()

fr = open('test_feature9.pkl','rb')  
test_feature9 = pickle.load(fr, encoding='latin1')
fr.close()

fr = open('test_feature10.pkl','rb')  
test_feature10 = pickle.load(fr, encoding='latin1')
fr.close()



#print(feature1.shape)

final_features_train = np.concatenate((feature1, feature2, feature3, feature4, feature5, feature6, feature7, feature8, feature9, feature10), axis=1)
final_features_test = np.concatenate((test_feature1, test_feature2, test_feature3, test_feature4, test_feature5, test_feature6, test_feature7, test_feature8, test_feature9, test_feature10), axis=1) 
print(final_features_test.shape)

#Dimension reduction 
pca = PCA(n_components=10)
reduced_features_train = pca.fit_transform(final_features_train)
print(reduced_features_train.shape)

pca2 = PCA(n_components=10)
reduced_features_test = pca.transform(final_features_test)

#Training svm
(train_images, train_labels), (test_images, test_labels) = mnist.load_data()
clf = SVC(gamma='auto')
clf.fit(reduced_features_train, train_labels)
train_pred = clf.predict(reduced_features_train)
train_accuracy = accuracy_score(train_labels, train_pred)

#Testing svm
test_pred = clf.predict(reduced_features_test)
test_accuracy = accuracy_score(test_labels, test_pred)

confusion_train = confusion_matrix(train_labels, train_pred)
confusion_test = confusion_matrix(test_labels, test_pred)

#Plotting confusion matrix for train
trn = confusion_matrix(y_target=train_labels, 
                      y_predicted=train_pred)
fig, ax = plot_confusion_matrix(conf_mat=trn)
plt.show()

#Plotting confusion matrix for test
tst = confusion_matrix(y_target=test_labels, 
                      y_predicted=test_pred)
fig, ax = plot_confusion_matrix(conf_mat=tst)
plt.show()








