#Name: Shreyas Patil
#USC Email: shreyasp@usc.edu
#Date: 3/19/2019

import numpy as np
from matplotlib import pyplot as plt
import cv2

height = 1024
width = 768

image1 = open('river1.raw', 'rb').read()
image1 = np.frombuffer(image1, np.uint8)
image1 = image1[0:height*width*3]
image1 = np.reshape(image1, (height, width, 3))

image2 = open('river2.raw', 'rb').read()
image2 = np.frombuffer(image2, np.uint8)
image2 = image2[0:height*width*3]
image2 = np.reshape(image2, (height, width, 3))

sift = cv2.xfeatures2d.SIFT_create()
key_points1, descriptors1 = sift.detectAndCompute(image1, None)
key_points2, descriptors2 = sift.detectAndCompute(image2, None)

norm1 = [np.linalg.norm(descriptors1[i, :]) for i in range(descriptors1.shape[0])]
norm2 = [np.linalg.norm(descriptors2[i, :]) for i in range(descriptors2.shape[0])]

largest_scale_kp1 = np.argmax(norm1)



#Plotting key points
#map1 = cv2.drawKeypoints(image1, key_points1, image1, color=(0,255,0), flags=cv2.DRAW_MATCHES_FLAGS_DRAW_RICH_KEYPOINTS)
#map2 = cv2.drawKeypoints(image2, key_points2, image2, color=(0,255,0), flags=cv2.DRAW_MATCHES_FLAGS_DRAW_RICH_KEYPOINTS)
#
#
#
#plt.imshow(map1)
#plt.imshow(map2)
#
#map1 = cv2.cvtColor(map1, cv2.COLOR_RGB2BGR)
#cv2.imwrite("river1_out.jpg", map1)
#map2 = cv2.cvtColor(map2, cv2.COLOR_RGB2BGR)
#cv2.imwrite("river2_out.jpg", map2)






#Matching keypoints
brute_force = cv2.BFMatcher()
nn = brute_force.knnMatch(np.array([descriptors1[largest_scale_kp1]]), descriptors2, k=1)

#good = []
#for m,n,o in nn:
#    if m.distance < 0.8*n.distance:
#        good.append([m])

result = cv2.drawMatchesKnn(image1, np.array([key_points1[largest_scale_kp1]]), image2, key_points2, nn, None, matchColor=(255, 255, 255), flags=2)
cv2.imwrite("brute_force.jpg", cv2.cvtColor(result, cv2.COLOR_RGB2BGR))

print('Orientation of key point in river image1', key_points1[largest_scale_kp1].angle)
print('orientation of matching key point in river image2', key_points2[nn[0][0].trainIdx].angle)



#img=cv2.drawKeypoints(image1, [key_points1[largest_scale_kp1]], image1, color=(0,255,0), flags=cv2.DRAW_MATCHES_FLAGS_DRAW_RICH_KEYPOINTS)
#cv2.imwrite('key-point with the largest scale.jpg', cv2.cvtColor(img, cv2.COLOR_RGB2BGR))

#matches_all = brute_force.knnMatch(descriptors1, descriptors2, k=2)
#result_all = cv2.drawMatchesKnn(image1, key_points1, image2, key_points2, good, None)
#plt.imshow(result_all),plt.show()




#FLANN_INDEX_KDTREE = 1
#index_params = dict(algorithm = FLANN_INDEX_KDTREE, trees = 5)
#search_params = dict(checks=100)
#
#flann = cv2.FlannBasedMatcher(index_params,search_params)
#
#matches = flann.knnMatch(np.array([descriptors1[largest_scale_kp1]]), descriptors2, k=1)
#
##list_kp1 = [key_points1[mat.queryIdx].pt for mat in matches[0]] 
#
##Need to draw only good matches, so create a mask
##matchesMask = [[0,0] for i in range(len(matches))]
### ratio test as per Lowe's paper
##for i,(m,n) in enumerate(matches):
##    if m.distance < 0.7*n.distance:
##        matchesMask[i]=[1,0]
##draw_params = dict(matchColor = (0,255,0),
##                   singlePointColor = (255,0,0),
##                   matchesMask = matchesMask,
##                   flags = 0)
#
#result = cv2.drawMatchesKnn(image1, np.array([key_points1[largest_scale_kp1]]), image2, key_points2, matches, None, matchColor=(0, 0, 0))
#plt.imshow(result),plt.show()
#
#
#matches_all = flann.knnMatch(descriptors1, descriptors2, k=2)
#result_all = cv2.drawMatchesKnn(image1, key_points1, image2, key_points2, matches_all, None, matchColor=(0, 0, 255))
#plt.imshow(result_all),plt.show()


#result = cv2.cvtColor(result, cv2.COLOR_RGB2BGR)
#cv2.imwrite('Matching.jpg', result)



