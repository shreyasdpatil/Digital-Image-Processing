#Name: Shreyas Patil
#USC Email: shreyasp@usc.edu
#Submission Date: 3/3/2019

import numpy as np
from matplotlib import pyplot as plt
from math import floor 
from scipy.optimize import least_squares
from scipy.optimize import curve_fit

def distortion(x, y, K1, K2):
    x_d = x*(1 + K1*(x*x + y*y) + K2*(x*x + y*y)**2)
    y_d = y*(1 + K1*(x*x + y*y) + K2*(x*x + y*y)**2)
    return x_d, y_d


image = open('classroom.raw','rb').read()
image = np.frombuffer(image, np.uint8)
img = image[0:712*1072]
img = np.reshape(img, (712,1072))
plt.matshow(img,cmap='gray')

def bilinear_interpolation(img, p_, q_):
    p = floor(p_) #x
    q = floor(q_)   #y
    err_col = q_ - q   #error row=b
    err_row = p_ - p      #error column=a  
    value = (1-err_row)*(img[p][q]*(1-err_col) + (img[p+1][q])*err_col) + err_row*(img[p][q+1]*(1-err_col) + (img[p+1][q+1])*err_col)
    
    return int(value)



height = 712
width = 1072

K1 = -0.3536 
K2 = 0.1730 
K3 = 0
fx = fy = 600

img_center = [height//2, width//2]

#output = np.zeros((712, 1072))
#for i in range(height):
#    for j in range(width):
#        x_d, y_d =  distortion((j-img_center[0])/fx, (i-img_center[1])/fy, K1, K2)
#        x_new = fx*x_d + img_center[0]
#        y_new = fy*y_d + img_center[1]
#        
#        value = bilinear_interpolation(img, x_new, y_new)
#        if value != 255:
#            output[i][j] = value
            
#output = np.zeros((712, 1072))
#for i in range(height):
#    for j in range(width):
#        x_d, y_d =  distortion((i-img_center[0])/fx, (j-img_center[1])/fy, K1, K2)
#        x_new = fx*x_d + img_center[0]
#        y_new = fy*y_d + img_center[1]
#        
#        if y_new > 711 and x_new>1071 and x_new<0 and y_new<0: 
#            output[i][j] = 255
#        else:
#             output[i][j] = img[round(x_new)][round(y_new)]
#            
#plt.matshow(output,cmap='gray')

#output.astype('int8').tofile('lens_distortion_out.raw')

output = np.zeros((712, 1072))
for i in range(height):
    for j in range(width):
        x_d, y_d =  distortion((i-img_center[0])/fx, (j-img_center[1])/fy, K1, K2)
        x_new = fx*x_d + img_center[0]
        y_new = fy*y_d + img_center[1]
        
        if y_new > 711 and x_new>1071 and x_new<0 and y_new<0: 
            output[i][j] = 255
        else:
             output[i][j] =  bilinear_interpolation(img, x_new, y_new)
            
plt.matshow(output,cmap='gray')

output.astype('int8').tofile('lens_distortion_out.raw')
    

    
        
        
        
    



















