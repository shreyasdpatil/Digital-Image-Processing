#Name: Shreyas Patil
#USC Email: shreyasp@usc.edu
#Date: 3/19/2019

import numpy as np
from matplotlib import pyplot as plt
from mpl_toolkits.mplot3d import Axes3D
import cv2
from sklearn.cluster import KMeans

height = 28
width = 28
image1 = []
image2 = []

for i in range(5):
    zeros_image = open('{}{}.raw'.format('zero_', i+1), 'rb').read()
    ones_image = open('{}{}.raw'.format('one_', i+1), 'rb').read()
    zeros_image = np.frombuffer(zeros_image, np.uint8)
    ones_image = np.frombuffer(ones_image, np.uint8)
    zeros = zeros_image[0:height*width]
    ones = ones_image[0:height*width]
    image1.append(np.reshape(zeros, (28, 28)))
    image2.append(np.reshape(ones, (28, 28)))


eight = open('eight.raw', 'rb').read()
eight = np.frombuffer(eight, np.uint8)
eight = eight[0:height*width]
eight = np.reshape(eight, (height, width))

sift = cv2.xfeatures2d.SIFT_create()
#Finding keypoints and descriptors

key_points1, descriptors1 = sift.detectAndCompute(image1[0], None)
key_points2, descriptors2 = sift.detectAndCompute(image1[1], None)
key_points3, descriptors3 = sift.detectAndCompute(image1[2], None)
key_points4, descriptors4 = sift.detectAndCompute(image1[3], None)
key_points5, descriptors5 = sift.detectAndCompute(image1[4], None)

key_points6, descriptors6 = sift.detectAndCompute(image2[0], None)
key_points7, descriptors7 = sift.detectAndCompute(image2[1], None)
key_points8, descriptors8 = sift.detectAndCompute(image2[2], None)
key_points9, descriptors9 = sift.detectAndCompute(image2[3], None)
key_points10, descriptors10 = sift.detectAndCompute(image2[4], None)


eight_key_points, eight_descriptors = sift.detectAndCompute(eight, None)


#all_descriptors = np.concatenate((descriptor1, descriptor2),  axis=0)

all_descriptors = np.concatenate((descriptors1, descriptors2, descriptors3, descriptors4, descriptors5,
                                  descriptors6, descriptors7, descriptors8, descriptors9),  axis=0)

#all_descriptors = np.squeeze(all_descriptors, axis=0)


kmn = KMeans(n_clusters=2).fit(all_descriptors)
train_labels = kmn.labels_
centroids = kmn.cluster_centers_

eight_labels = kmn.predict(eight_descriptors)

        
#eight_labels_ones = np.count_nonzero(eight_labels)
#eight_labels_zeros = len(eight_labels) - eight_labels_ones
#
#train_labels_ones = np.count_nonzero(train_labels)
#train_labels_zeros = len(train_labels) - train_labels_ones

#Plotting BOVW histogram for 0 and 1 images
plt.hist(train_labels)
plt.show()

#Plotting histogram for 8 image
#plt.hist(eight_labels)
#plt.show()

zero_label = kmn.predict(np.concatenate((descriptors1, descriptors2, descriptors3, descriptors4, descriptors5),  axis=0))
one_label = kmn.predict(np.concatenate((descriptors6, descriptors7, descriptors8, descriptors9),  axis=0))
plt.hist(zero_label)
plt.show()

plt.hist(one_label)
plt.show()

#Plotting histogram for 8 image
plt.hist(eight_labels)
plt.show()


#Finding histogram intersection

zero_labels_ones = np.count_nonzero(zero_label)
zero_labels_zeros = len(zero_label) - zero_labels_ones

one_labels_ones = np.count_nonzero(one_label)
one_labels_zeros = len(one_label) - one_labels_ones

eight_labels_ones = np.count_nonzero(eight_labels)
eight_labels_zeros = len(eight_labels) - eight_labels_ones

zero_close = min(eight_labels_zeros, zero_labels_zeros)/max(eight_labels_zeros, zero_labels_zeros) + min(eight_labels_ones, zero_labels_ones)/max(eight_labels_ones, zero_labels_ones)
one_close = min(eight_labels_zeros, one_labels_zeros)/max(eight_labels_zeros, one_labels_zeros) + min(one_labels_ones, eight_labels_ones)/max(one_labels_ones, eight_labels_ones)

print('Intersection with zeros histogram', zero_close)
print('Intersection with ones histogram', one_close)









