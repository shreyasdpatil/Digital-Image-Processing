#Name: Shreyas Patil
#USC Email: shreyasp@usc.edu
#Date: 3/3/2019

import numpy as np
from matplotlib import pyplot as plt
import math

image = open('lighthouse1.raw','rb').read()
image = np.frombuffer(image, np.uint8)
img = image[0:256*256]
img = np.reshape(img, (256,256))
plt.matshow(img,cmap='gray')


def interpolation(extract_img, out_rows, out_cols):
    
    in_cols = extract_img.shape[1]           #width
    in_rows = extract_img.shape[0]          #height
    col_ratio = (in_cols-1) / out_cols        
    row_ratio = (in_rows-1) / out_rows
    print(col_ratio)
    width = in_cols
    value = np.ravel(extract_img)
    
    output = np.zeros((out_rows, out_cols), np.uint8)
    for i in range(out_cols):
        for j in range(out_rows):
            c1 = j*col_ratio
            r1 = i*row_ratio
            err_col = c1-int(c1)
            err_row = r1-int(r1)
            index = int(r1)*width + int(c1)
            output[i][j] = int(value[index]*(1-err_row)*(1-err_col) + value[index+1]*err_row*(1-err_col) +
                            value[index+width]*(1-err_row)*err_col + value[index+width+1]*(err_row)*(err_col))
            
    return output     
            
            
flag1 = 0
for i in range(256):
    if flag1==1:
        break
    for j in range(256):
        if img[i][j]!=255:
            x1 = j-128
            y1 = 255-i-128
            flag1 = 1
            break

flag1 = 0
for i in range(255, -1, -1):
    if flag1==1:
        break
    for j in range(256):
        if img[i][j]!=255:
            x2 = j-128
            y2 = 255-i-128
            flag1 = 1
            break
        
flag1 = 0
for j in range(256):
    if flag1==1:
        break
    for i in range(256):
        if img[i][j]!=255:
            x3 = j-128
            y3 = 255-i-128
            flag1=1
            break
        
flag1 = 0
for j in range(255, -1, -1):
    if flag1==1:
        break
    for i in range(256):
        if img[i][j]!=255:
            x4 = j-128
            y4 = 255-i-128
            flag1=1
            break

#Finding center of given image

center = [(x1+x2)/2, (y1+y2)/2]

#Find angle of rotation

theta = 2*math.pi - math.atan2(y1-y3, x1-x3) - math.pi/2
sin_theta = math.sin(theta)
cos_theta = math.cos(theta)

#Reverse address mapping
T1 = np.array([[1, 0, -center[0]],
          [0, 1, -center[1]],
          [0, 0, 1]])

T2 = np.array([[1, 0, center[0]],
          [0, 1, center[1]],
          [0, 0, 1]])
    
R1 = np.array([[cos_theta, -sin_theta, 0],
          [sin_theta, cos_theta, 0],
          [0, 0, 1]])

    
outimg = np.zeros((256,256), np.uint8)
#A = np.zeros((256,256), np.uint8)
#B = np.zeros((256,256), np.uint8)
for i in range(len(img[:][1])):
    for j in range(len(img[1][:])):
        x = j-128
        y = 255-i-128
        A = np.matmul(np.linalg.inv(T2), [x, y, 1])
        B = np.matmul(np.linalg.inv(R1), A)
        out = np.matmul(np.linalg.inv(T1), B)
        u = 128+out[0]
        v = 255 - out[1]-128 
        if u>255 or v>255 or u<0 or v<0:
            outimg[i][j] = 255
            continue
        outimg[i][j] = img[int(v)][int(u)]
        
#Image after inverse translation
#plt.matshow(A,cmap='gray') 

#Image after inverse rotation
#plt.matshow(B,cmap='gray') 

#Image after inverse translation

plt.matshow(outimg,cmap='gray') 

#Image after inverse translation and rotation


       
#Now identifying the four corners of rotated image for scaling

flag2 = 0
x_1 = y_1 = 0
for i in range(256):    
    for j in range(256):
        if outimg[i][j]!=255:
            if x_1 == 0 and y_1==0:
                x_1 = j
                y_1 = i
            if i == y_1:
                y_2 = i
                x_2 = j
                if j > x_2:
                    x_2 = j
                continue

x_4 = y_4= 0
for i in range(255,-1,-1):    
    for j in range(255,-1,-1):
        if outimg[i][j]!=255:
            if x_4 ==0 and y_4 == 0:
                x_4 = j
                y_4 = i
            if i == y_4 and j == x_1:
                y_3 = i
                x_3 = j
                continue
   
#flag2 = 0
#for i in range(255, -1, -1):
#    if flag2==1:
#        break
#    for j in range(256):
#        if img[i][j]!=255:
#            x_2 = i
#            y_2 = j
#            flag2 = 1
#            break
        
        
#height = x_2 - x_1 
#
#flag2 = 0
#for j in range(255, - 1, -1):
#    if flag2==1:
#        break
#    for i in range(255, - 1, -1):
#        if img[j][i]!=255:
#            x_3 = j
#            y_3 = i
#            flag2=1
#            break
#
#flag2 = 0
#for i in range(256):
#    if flag2==1:
#        break
#    for j in range(255, -1, -1):
#        if img[i][j]!=255:
#            x_4 = i
#            y_4 = j
#            flag2=1
#            break
#
#width = x_4 - x_1
#
extract_img = outimg[y_1:y_3, x_1:x_2]
plt.matshow(extract_img,cmap='gray')

output = interpolation(extract_img, 160, 160)

plt.matshow(output,cmap='gray')


#output.astype('int8').tofile('lighthouse1_out.raw')




