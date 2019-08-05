#Name: Shreyas Patil
#USC Email: shreyasp@usc.edu
#Date: 4/28/2019

import numpy as np
from numpy import linalg as LA
from skimage.util.shape import view_as_windows
import pickle

from sklearn.decomposition import PCA
from skimage.measure import block_reduce
import matplotlib.pyplot as plt
import saab1
import data1

    
def inverse(data):
    output = np.empty([1, 8, 8, 6])
    k = 0
    for i in range(0, 96, 16):
        for j in range(0, 16):
            for m in range(0, 8, 2):
                for n in range(0, 8, 2):
                    output[0, m:m+2, n:n+2, k] = data[0, :, :, i+j]
        k += 1
                    
    return output
        


def inverse_saab_transform(feat, pca_params):

    num_layers=pca_params['num_layers']
    kernel_sizes=pca_params['kernel_size']

    for i in range(num_layers-1, -1, -1):
        print('--------stage %d --------'%i)
        feature_expectation=pca_params['Layer_%d/feature_expectation'%i]
        kernels=pca_params['Layer_%d/kernel'%i]
#        bias=pca_params['Layer_%d/bias'%i]
#        print("a", feat.shape)
        
#        num_samples=feat.shape[0]
#        print("transformed", feat.shape)
#        transformed = feat.reshape(feat.shape[1]*feat.shape[2]*feat.shape[0], -1)
#        print("transformed", transformed.shape)
        if i==1:
            # Add bias
            bias=pca_params[f'Layer_{i}/bias']
            kernels=pca_params[f'Layer_{i-1}/kernel']
            e=np.zeros((1, kernels.shape[0]))

            e[0,0]=1
            print("a", feat.shape)
            feat += bias*e
            
            sample_patches_centered_w_bias = np.matmul(feat, np.linalg.pinv(np.transpose(kernels)))
#            print("sample_patches_centered", sample_patches_centered_w_bias.shape)
        
            sample_patches_centered = sample_patches_centered_w_bias - np.sqrt(16)*bias
            sample_patches_centered = sample_patches_centered.reshape(-1, sample_patches_centered.shape[-1])
            sample_patches_centered_w_bias = sample_patches_centered + feature_expectation
            sample_patches_centered_w_bias = sample_patches_centered_w_bias.reshape(4, 2, 2, 1, 1, 4, 4, 6)
            sample_patches_centered_w_bias = sample_patches_centered_w_bias.transpose(0,1,3,5,2,4,6,7).reshape(4,8,8,6)
            
        else:
#            transformed=np.matmul(sample_patches_centered, np.transpose(kernels)) 
            sample_patches_centered_w_bias = np.matmul(sample_patches_centered_w_bias, np.linalg.pinv(np.transpose(kernels)))
            sample_patches_centered_w_bias = sample_patches_centered_w_bias.reshape(-1, sample_patches_centered_w_bias.shape[-1])
            sample_patches = sample_patches_centered + feature_expectation
            sample_patches = sample_patches.reshape(4,8,8,1,1,4,4,1)
            sample_patches = sample_patches.transpose(0,1,3,5,2,4,6,7).reshape(4,32,32,1)
            sample_images = sample_patches

        
#        sample_patches_centered, feature_expectation=remove_mean(sample_patches, axis=0)
#        print("sample_patches", sample_patches.shape[0])
#        sample_patches=sample_patches.reshape(1, sample_patches[0]*sample_patches[0], sample_patches[0]**2)
#        print("sample_patches", sample_patches.shape)
#        ac_kernels = sample_patches
        
        
        
        # Unflatten
#        sample_patches=sample_patches.reshape([-1, sample_patches.shape[-1]])

        
        # Create image from patches
#        for i in range()
#        sample_patches=window_process(sample_images,kernel_sizes[i],kernel_sizes[i])
#        sample_image = sample_patches
    
    return sample_images



        
def main():
    # load data
    fr=open('pca_params.pkl','rb')  
    pca_params=pickle.load(fr)
    
    # read data
    train_images, train_labels = data1.import_data("0-9")
    print('Training image size:', train_images.shape)
    
    #Image reconstruction
    feature=saab1.initialize(train_images, pca_params)
    feature_inv = feature
#    print("out", feature_inv.shape)
    final_images = inverse_saab_transform(feature_inv, pca_params)
    sample = train_images[0].squeeze(-1)
    
    ohm = feature[0].squeeze(-1)
    k = 0
    for i in range(sample.shape[0]):
        for j in range( sample.shape[1]):
            k += ( sample[i][j] - ohm[i][j])**2
    k = k / ( sample.shape[0] *  sample.shape[1])
    
    maxi = np.max(train_images)
    mse_sqrt = np.sqrt(k)
    PSNR = 20 * np.log10(maxi / mse_sqrt)
#    plt.imshow(final_image)
    
   
if __name__ == '__main__':
	main()
        
        
        
        
    
        
    

    	