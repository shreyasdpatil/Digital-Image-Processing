#Name: Shreyas Patil
#USC Email: shreyasp@usc.edu
#Date: 3/19/2019

import numpy as np
from matplotlib import pyplot as plt
import cv2
from sklearn.cluster import KMeans
from sklearn.decomposition import PCA

height = 510
width = 510

texture_image = open('comb.raw', 'rb').read()
texture_image = np.frombuffer(texture_image, np.uint8)
image = texture_image[0:510*510]
image = (np.reshape(image, (510, 510)))
pixel_mean = np.sum(image)/(height*width)


new_image = np.zeros((510, 510))
for i in range(height):
    for j in range(width):
        new_image[i][j] = image[i][j] - pixel_mean 
        


filter= np.array([[1, 4, 6, 4, 1],          #L5
                    [-1, -2, 0, 2, 1],      #E5
                    [-1, 0, 2, 0, -1],      #S5
                    [-1, 2, 0, -2, 1],      #W5
                    [1, -4, 6, -4, 1]])     #R5

    
Laws = np.zeros((25,5,5), dtype=int)
k=0
for i in range(5):
    for j in range(5):
        Laws[k][:,:] = np.matmul(filter[i].reshape(5,1), filter[j].reshape(1,5))
        k += 1
            



extendedImagedata = np.pad(new_image, ((2, 2), (2, 2)), 'reflect')


outImagedata = np.zeros((25, height, width))
#feature = np.zeros((height*width, 25))
            
l = 0
for i in range(2, height+2):
    for j in range(2, width+2):
        for k in range(25):
            total = 0
            for m in [-2, -1, 0, 1, 2]:
                for n in [-2, -1, 0, 1, 2]:
                    total += extendedImagedata[i + m][j + n] * Laws[k][m+2][n+2]

            outImagedata[k][i-2][j-2] = total
        l += 1
        


final_outImagedata5 = np.zeros((25, height+4, width+4))
final_outImagedata15 = np.zeros((25, height+14, width+14))
final_outImagedata17 = np.zeros((25, height+16, width+16))
final_outImagedata19 = np.zeros((25, height+18, width+18))
final_outImagedata21 = np.zeros((25, height+20, width+20))
final_outImagedata31 = np.zeros((25, height+30, width+30))
for i in range(25):
    final_outImagedata5[i] = np.pad(outImagedata[i], ((2, 2), (2, 2)), 'reflect')
    final_outImagedata15[i] = np.pad(outImagedata[i], ((7, 7), (7, 7)), 'reflect')
    final_outImagedata17[i] = np.pad(outImagedata[i], ((8, 8), (8, 8)), 'reflect')
    final_outImagedata19[i] = np.pad(outImagedata[i], ((9, 9), (9, 9)), 'reflect')
    final_outImagedata21[i] = np.pad(outImagedata[i], ((10, 10), (10, 10)), 'reflect')
    final_outImagedata31[i] = np.pad(outImagedata[i], ((15, 15), (15, 15)), 'reflect')
#Extending image boundaries by 2 on each side

#final_outImagedata = np.zeros((25, height+4, width+4))

       
feature = np.zeros((height*width, 25))  
            
for k in range(25):
    l = 0
    for i in range(height):
        for j in range(width):
            feature[l][k] = np.sum(abs(final_outImagedata19[k][i:i+19,j:j+19]))
            l+=1



#features_15 = np.zeros((height*width,15))            

#features_15 = np.vstack((feature[:,0], feature[:,6], feature[:,12], feature[:,18], feature[:,24], (feature[:,1]+feature[:,5])/2,
#(feature[:,2]+feature[:,10])/2, (feature[:,3]+feature[:,15])/2, (feature[:,4]+feature[:,20])/2,
#(feature[:,19]+feature[:,23])/2, (feature[:,7]+feature[:,11])/2, (feature[:,8]+feature[:,16])/2,
#(feature[:,9]+feature[:,21])/2, (feature[:,13]+feature[:,17])/2, (feature[:,14]+feature[:,22])/2)) 
#
#features_15 = features_15.T

#Energy feature normalization
#feature_norm = np.zeros((height*width, 25), dtype=float)
#for k in range(15):
#    feature_norm[:, k] = (features_15[:, k] - np.mean(features_15[:, k]))/np.std(features_15[:, k])

            
#Energy feature normaliation
#feature_norm = np.zeros((height*width, 25), dtype=float)
#for k in range(25):
#    for i in range(height*width):
#        feature_norm[i][k] = feature[i][k]/feature[i][0] 
  
      
            
#Energy feature normalization
feature_norm = np.zeros((height*width, 25), dtype=float)
for k in range(25):
    feature_norm[:, k] = (feature[:, k] - np.mean(feature[:, k]))/np.std(feature[:, k])


#PCA 
pca = PCA(n_components=3)
pca.fit(feature_norm)
feat_pca = pca.transform(feature_norm)



#K-means clustering
kmn = KMeans(n_clusters=7).fit(feat_pca)
labels = kmn.labels_


labels_2D = labels.reshape(510, 510)

output = np.zeros((510,510))

for i in range(height):
    for j in range(width):
        if labels_2D[i][j]==0:
            output[i][j] = 0
        elif labels_2D[i][j]==1:
            output[i][j] = 42
        elif labels_2D[i][j]==2:
            output[i][j] = 84
        elif labels_2D[i][j]==3:
            output[i][j] = 126
        elif labels_2D[i][j]==4:
            output[i][j] = 168
        elif labels_2D[i][j]==5:
            output[i][j] = 210
        else:
            output[i][j] = 255
            

 
#cv2.imwrite('segmentation17_pca.jpg', output) 
#cv2.imwrite('segmentation19_pca.jpg', output) 
#cv2.imwrite('segmentation21_pca.jpg', output)  

#cv2.imwrite('segmentation15_pca_std.jpg', output) 
#cv2.imwrite('segmentation17_pca_std.jpg', output) 
#cv2.imwrite('segmentation19_pca_std.jpg', output) 
#cv2.imwrite('segmentation21_pca_std.jpg', output)  
    
cv2.imwrite('segmentation19_pca_std.jpg', output) 

kernel = np.ones((27,27), np.float32)
A = cv2.morphologyEx(output, cv2.MORPH_CLOSE, kernel)
cv2.imwrite('segmentation19_std_close.jpg', A) 




##K means clustering
##feature = np.float32(feature)
##criteria = (cv2.TERM_CRITERIA_EPS + cv2.TERM_CRITERIA_MAX_ITER, 10, 1.0)
##compactness,label,center = cv2.kmeans(feature, 7, None, criteria, 10, cv2.KMEANS_RANDOM_CENTERS)     
#kmn = KMeans(n_clusters=7).fit(feature)
#kmn.labels_
          
    
            
            
            







  
    
    






