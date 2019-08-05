#Name: Shreyas Patil
#USC Email: shreyasp@usc.edu
#Submission Date: 3/3/2019

import numpy as np
from matplotlib import pyplot as plt
from math import floor 

image = open('hat.raw','rb').read()
image = np.frombuffer(image, np.uint8)
img = image[0:512*512]
img = np.reshape(img, (512,512))
plt.matshow(img,cmap='gray')

def bilinear_interpolation(img, p_, q_):
    p = floor(p_)
    q = floor(q_)
    err_col = q_ - q   #error row=b
    err_row = p_ - p      #error column=a
#    if p>511 or q>511 or p<0 or q<0:
#        return 255
    value = (1-err_row)*(img[p][q]*(1-err_col) + img[p+1][q]*err_col) + err_row*(img[p][q+1]*(1-err_col) + img[p+1][q+1]*err_col)
    return value


#def output_array(x0, x1, x2, x3, x4, x5):
#    return  np.array([[1, 1, 1, 1, 1, 1],
#                     [x0[0], x1[0],    x2[0], x3[0], x4[0], x5[0]],
#                     [x0[1], x1[1],    x2[1], x3[1], x4[1], x5[1]],
#                     [x0[0]**2, x1[0]**2, x2[0]**2, x3[0]**2, x4[0]**2, x5[0]**2],
#                     [x0[0]*x0[1], x1[0]*x1[1], x2[0]*x2[1], x3[0]*x3[1], x4[0]*x4[1], x5[0]*x5[1]],
#                     [x0[1]**2, x1[1]**2, x2[1]**2, x3[1]**2, x4[1]**2, x5[1]**2]])

def output_array(x0, x1, x2, x3, x4, x5):
    return  np.array([[1, x0[0], x0[1], x0[0]**2, x0[0]*x0[1], x0[1]**2],
                      [1, x1[0], x1[1], x1[0]**2, x1[0]*x1[1], x1[1]**2],
                      [1, x2[0], x2[1], x2[0]**2, x2[0]*x2[1], x2[1]**2],
                      [1, x3[0], x3[1], x3[0]**2, x3[0]*x3[1], x3[1]**2],
                      [1, x4[0], x4[1], x4[0]**2, x4[0]*x4[1], x4[1]**2],
                      [1, x5[0], x5[1], x5[0]**2, x5[0]*x5[1], x5[1]**2]])

    
def input_array(u0, u1, u2, u3, u4, u5):
    return np.array([[u0[0], u1[0], u2[0], u3[0], u4[0], u5[0]],
                     [u0[1], u1[1], u2[1], u3[1], u4[1], u5[1]]])
    
def point_array(x,y):
    return np.array([1, x, y, x**2, x*y, y**2]).reshape(6,1)

#Control points in cartesian coordiantes
h1 = [0, 127]
h2 = [-127, 0]
h3 = [0, -128]
h4 = [128, 0]


p11 = [-255, 255]
p12 = [0, 255]
p13 = [256, 255]
p14 = [-127, 127]
p15 = [256/2, 127]
p16 = [0, 0]

p21 = [-255, -256]
p22 = [-255, 0]
p23 = [-255, 255]
p24 = [-127, -256/2]
p25 = [-127, 127]
p26 = [0, 0]

p31 = [256, -256]
p32 = [0, -256]
p33 = [-255, -255]
p34 = [256/2, -256/2]
p35 = [-127, -256/2]
p36 = [0, 0]

p41 = [256, 255]
p42 = [256, 0]
p43 = [256, -256]
p44 = [256/2, 127]
p45 = [256/2, -256/2]
p46 = [0, 0]


#outputmatrix1 = output_array(p11, p12, p13, p14, p15, p16)
#outputmatrix2 = output_array(p21, p22, p23, p24, p25, p26)
#outputmatrix3 = output_array(p31, p32, p33, p34, p35, p36)
#outputmatrix4 = output_array(p41, p42, p43, p44, p45, p46)

outputmatrix1 = output_array(p11, h1, p13, p14, p15, p16)
outputmatrix2 = output_array(p21, h2, p23, p24, p25, p26)
outputmatrix3 = output_array(p31, h3, p33, p34, p35, p36)
outputmatrix4 = output_array(p41, h4, p43, p44, p45, p46)




outputmatrix1_inv = np.linalg.inv(np.transpose(outputmatrix1))
outputmatrix2_inv = np.linalg.inv(np.transpose(outputmatrix2))
outputmatrix3_inv = np.linalg.inv(np.transpose(outputmatrix3))
outputmatrix4_inv = np.linalg.inv(np.transpose(outputmatrix4))

inputarray1 = input_array(p11, p12, p13, p14, p15, p16)
inputarray2 = input_array(p21, p22, p23, p24, p25, p26)
inputarray3 = input_array(p31, p32, p33, p34, p35, p36)
inputarray4 = input_array(p41, p42, p43, p44, p45, p46)

#coefficients1 = np.matmul(outputmatrix1_inv, inputarray1.T)
#coefficients2 = np.matmul(outputmatrix2_inv,inputarray2.T)
#coefficients3 = np.matmul(outputmatrix3_inv, inputarray3.T)
#coefficients4 = np.matmul(outputmatrix4_inv,inputarray4.T )

coefficients1 = np.matmul(inputarray1, outputmatrix1_inv)
coefficients2 = np.matmul(inputarray2, outputmatrix2_inv)
coefficients3 = np.matmul(inputarray3, outputmatrix3_inv)
coefficients4 = np.matmul(inputarray4, outputmatrix4_inv )

warp = np.zeros((512, 512))

for i in range(256):
    for j in range(i, 512-i):
        u,v = np.matmul(coefficients1, point_array(j-255, 255 - i))
        u_img = u + 255
        v_img = 255 - v 
        if 1<=u_img<511 and 1<=v_img<511:
#            print(u_img, v_img)
            warp[i][j] = bilinear_interpolation(img, v_img, u_img)
    
plt.matshow(warp,cmap='gray')

#Applying warping to region 2
for i in range(256):
    for j in range(i, 512-i):
        u,v = np.matmul(coefficients2, point_array(i-255, 255-j))
        u_img = u + 255
        v_img = 255 - v 
        if 1<=u_img<511 and 1<=v_img<511:
            warp[j][i] = bilinear_interpolation(img, v_img, u_img)
        
plt.matshow(warp,cmap='gray')

#Applying warping to region 3
for i in range(511, 255, -1):
    for j in range(511-i, i+1):
        u,v = np.matmul(coefficients3, point_array(j-255, 255-i))
        u_img = u + 255
        v_img = 255 - v 
        if 1<=u_img<511 and 1<=v_img<511:
           warp[i][j] = bilinear_interpolation(img, v_img, u_img) 
        
plt.matshow(warp,cmap='gray')

#Applying warping to region 4
for i in range(511, 255, -1):
    for j in range(511-i, i+1):
        u,v = np.matmul(coefficients4, point_array(i-255, 255-j))
        u_img = u + 255
        v_img = 255 - v 
        if 1<=u_img<511 and 1<=v_img<511:
            warp[j][i] = bilinear_interpolation(img, v_img, u_img)
        
plt.matshow(warp,cmap='gray')

warp.astype('int8').tofile('warping_out.raw')