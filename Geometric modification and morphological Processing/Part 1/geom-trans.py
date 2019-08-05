#Name: Shreyas Patil
#USC Email: shreyasp@usc.edu
#Date: 3/3/2019

import numpy as np
from matplotlib import pyplot as plt
import math

raw_image = open('lighthouse.raw','rb').read()
raw_image = np.frombuffer(raw_image, np.uint8)
img = raw_image[0:512*512]
img = np.reshape(img, (512,512))

new_img = np.zeros((512, 512), np.uint8)
for i in range(512):
    for j in range(512):
        new_img[i][j] = img[i][j]
        



lighthouse1_image = open('lighthouse1_out.raw','rb').read()
lighthouse1_image = np.frombuffer(lighthouse1_image, np.uint8)
img1 = lighthouse1_image[0:160*160]
img1 = np.reshape(img1, (160,160))
plt.matshow(img1,cmap='gray')

lighthouse2_image = open('lighthouse2_out.raw','rb').read()
lighthouse2_image = np.frombuffer(lighthouse2_image, np.uint8)
img2 = lighthouse2_image[0:160*160]
img2 = np.reshape(img2, (160,160))
plt.matshow(img2,cmap='gray')

lighthouse3_image = open('lighthouse3_out.raw','rb').read()
lighthouse3_image = np.frombuffer(lighthouse3_image, np.uint8)
img3 = lighthouse3_image[0:160*160]
img3 = np.reshape(img3, (160,160))
plt.matshow(img3,cmap='gray')



#Finding the 4 corners of the blank regions

#def four_corners(img, x_size, y_size)

flag1 = 0
for i in range(512):
    if flag1==1:
        break
    for j in range(256):
        if img[j][i]==255:
            x11 = i
            y11 = j
            flag1 = 1
            break

flag1 = 0
for j in range(511, -1, -1):
    if flag1==1:
        break
    for i in range(256):
        if img[j][i]==255:
            x12 = x11
            y12 = j
            flag1 = 1
            break
        
flag1 = 0
for i in range(255, -1, -1):
    if flag1==1:
        break
    for j in range(511, -1, -1):
        if img[j][i]==255:
            x13 = i
            y13 = j
            flag1=1
            break
        
flag1 = 0
for i in range(255, -1, -1):
    if flag1==1:
        break
    for j in range(512):
        if img[j][i]==255:
            x14 = i
            y14 = y11
            flag1=1
            break
###########################################        

flag1 = 0
for i in range(256, 512 ,1):
    if flag1==1:
        break
    for j in range(256):
        if img[j][i]==255:
            x21 = i
            y21 = j
            flag1 = 1
            break


################################################

flag1 = 0
for i in range(320, 512, 1):
    if flag1==1:
        break
    for j in range(320, 512, 1):
        if img[i][j]==255:
            x31 = j
            y31 = i
            flag1 = 1
            
            break
#For lighthouse1    
for i in range(160):
    for j in range(160):
        new_img[y11+i][x11+j] = img1[i][j]
        
#For lighthouse2
for i in range(160):
    for j in range(160):
        new_img[y21+i][x21+j] = img2[i][j]
        

#For lighthouse3
for i in range(160):
    for j in range(160):
        new_img[y31+i][x31+j] = img3[i][j]
        
new_img.astype('int8').tofile('lighthouse_out.raw')

