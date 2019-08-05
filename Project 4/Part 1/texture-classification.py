#Name: Shreyas Patil
#USC Email: shreyasp@usc.edu
#Date: 3/19/2019

import numpy as np
from matplotlib import pyplot as plt
from mpl_toolkits.mplot3d import Axes3D
import cv2
from sklearn.decomposition import PCA
from sklearn.cluster import KMeans


#0,6,12,18,24,1+5/2,2+10/2,3+15/2,4+20/2,19+23/2,7+11/2,8+16/2,9+21/2,13+17/2,14+22/2

height = 128
width = 128
image = []
pixel_mean = np.zeros(12)

for i in range(12):
    texture_image = open('{}{}.raw'.format('texture', i+1), 'rb').read()
    texture_image = np.frombuffer(texture_image, np.uint8)
    img = texture_image[0:128*128]
    image.append(np.reshape(img, (128,128)))
    pixel_mean[i] = np.sum(image[i])/(height*width)


new_image = np.zeros((12, 128, 128))
for k in range(12):
    for i in range(height):
        for j in range(width):
            new_image[k][i][j] = image[k][i][j] - pixel_mean[k] 
        


filter= np.array([[1, 4, 6, 4, 1],
                    [-1, -2, 0, 2, 1],
                    [-1, 0, 2, 0, -1],
                    [-1, 2, 0, -2, 1],
                    [1, -4, 6, -4, 1]])

    
Laws = np.zeros((25,5,5), dtype=int)
k=0
for i in range(5):
    for j in range(5):
        Laws[k][:][:] = np.matmul(filter[i].reshape(5,1), filter[j].reshape(1,5))
        k += 1

extendedImagedata = np.zeros((12, height+4, width+4))            
for k in range(12):
    extendedImagedata[k] = np.pad(new_image[k], ((2, 2), (2, 2)), 'reflect')
    

#extendedImagedata = np.zeros((12, height+4, width+4))
#for k in range(12):
#    for i in range(height):
#        for j in range(width):
#            extendedImagedata[k][i+2][j+2] = new_image[k][i][j];
#    
#
#for k in range(12):
#    for j in range(width):
#        extendedImagedata[k][0][j+2] = new_image[k][2][j]
#        extendedImagedata[k][1][j+2] = new_image[k][1][j]
#        extendedImagedata[k][height+2][j+2] = new_image[k][height-2][j]
#        extendedImagedata[k][height+3][j+2] = new_image[k][height-3][j]
#        
#for k in range(12):
#    for i in range(height):
#        extendedImagedata[k][i+2][0] = new_image[k][i][2]
#        extendedImagedata[k][i+2][1] = new_image[k][i][1]
#        extendedImagedata[k][i+2][width+2] = new_image[k][i][width-2]
#        extendedImagedata[k][i+3][width+3] = new_image[k][i][width-3]



outImagedata = np.zeros((12, 25, height, width))
feature = np.zeros((12,25))
            
for a in range(12):
    for i in range(2, height+2):
        for j in range(2, width+2):
            for k in range(25):
                total = 0
                for m in [-2, -1, 0, 1, 2]:
                    for n in [-2, -1, 0, 1, 2]:
                        total += extendedImagedata[a][i + m][j + n] * Laws[k][m+2][n+2]
                        
                outImagedata[a][k][i-2][j-2] = total
                feature[a][k] += abs(total)/(height*width)

#
index_max = np.argmax([np.var(feature[:, i]) for i in range(25)])
index_min = np.argmin([np.var(feature[:, i]) for i in range(25)])
                
max_feature = np.argmax(feature[0,:] - feature[1,:])
min_feature = np.argmax(feature[0,:] - feature[1,:])                

#15 D feature vector
#features_15 = np.zeros((12,15))
##0,6,12,18,24,1+5/2,2+10/2,3+15/2,4+20/2,19+23/2,7+11/2,8+16/2,9+21/2,13+17/2,14+22/2
#for i in range(12):
#    features_15[i][:] = [feature[i][0], feature[i][6], feature[i][12], feature[i][18], feature[i][24], (feature[i][1]+feature[i][5])/2,
#    (feature[i][2]+feature[i][10])/2, (feature[i][3]+feature[i][15])/2, (feature[i][4]+feature[i][20])/2,
#    (feature[i][19]+feature[i][23])/2, (feature[i][7]+feature[i][11])/2, (feature[i][8]+feature[i][16])/2,
#    (feature[i][9]+feature[i][21])/2, (feature[i][13]+feature[i][17])/2, (feature[i][14]+feature[i][22])/2] 



#Feature normalization for horizontal 25 features
#feat_norm = np.zeros((12,25))
#for k in range(12):
#    feat_norm[k, :] = (feature[k, :] - np.mean(feature[k, :]))/np.std(feature[k, :])  
    
#Feature normalization for 25 features
feat_norm = np.zeros((12,25))
for k in range(25):
    feat_norm[:, k] = (feature[:, k] - np.mean(feature[:, k]))/np.std(feature[:, k]) 
    
 
                    
#Feature normalization for 15 features
#feat_norm_15 = np.zeros((12,15))
#for k in range(15):
#    feat_norm_15[:, k] = (features_15[:, k] - np.mean(features_15[:, k], axis=0))/np.std(features_15[:, k], axis=0)    
    

#Nomralization along horizontal axis
#feat_norm_15 = np.zeros((12,15))
#for k in range(12):
#    feat_norm_15[k, :] = (features_15[k, :] - np.mean(features_15[k, :]))/np.std(features_15[k, :])    






#Calculating feature with highest and lowest discriminant power
#index_max = np.argmax([np.var(feat_norm[:, i]) for i in range(25)])
#index_min = np.argmin([np.var(feat_norm[:, i]) for i in range(25)])






    


#pca = PCA(n_components=3)
#pca.fit(feat_norm)
#feat_pca = pca.transform(feat_norm)



            
#K means clustering
#feat_pca = np.float32(feat_pca)
#criteria = (cv2.TERM_CRITERIA_EPS + cv2.TERM_CRITERIA_MAX_ITER, 10, 1.0)
#compactness,label,center = cv2.kmeans(feat_pca, 5, None, criteria, 10, cv2.KMEANS_PP_CENTERS)

kmn = KMeans(n_clusters=4, init='k-means++').fit(feat_norm)
labels = kmn.labels_

zero = np.where(labels == 0)
one = np.where(labels == 1)
two = np.where(labels == 2)
three = np.where(labels == 3)
#four = np.where(labels == 4)

print(len(zero[0]))
for i in range(len(zero[0])):
    plt.matshow(image[zero[0][i]], cmap='gray')
    plt.show()
print(len(one[0]))
for i in range(len(one[0])):
     plt.matshow(image[one[0][i]], cmap='gray')
     plt.show()
print(len(two[0]))
for i in range(len(two[0])):
     plt.matshow(image[two[0][i]], cmap='gray')
     plt.show()
print(len(three[0]))
for i in range(len(three[0])):
     plt.matshow(image[three[0][i]], cmap='gray')
     plt.show()

     


#3D plot
fig = plt.figure()
ax = plt.axes(projection='3d')
x = feat_pca[:, 0]
y = feat_pca[:,1]
z = feat_pca[:,2]
ax.scatter3D(x, y, z, cmap='greens', edgecolor='k')


            

  
            
            







  
    
    






