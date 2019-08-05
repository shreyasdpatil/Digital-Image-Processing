#Name: Shreyas Patil
#USC Email: shreyasp@usc.edu
#Date: 4/28/2019

from tensorflow.python.platform import flags
import pickle
import data3
import saab3
import numpy as np

def del_all_flags(FLAGS):
    flags_dict = FLAGS._flags()    
    keys_list = [keys for keys in flags_dict]    
    for keys in keys_list:
        FLAGS.__delattr__(keys)

del_all_flags(flags.FLAGS)

flags.DEFINE_string("output_path", None, "The output dir to save params")
flags.DEFINE_string("use_classes", "0-9", "Supported format: 0,1,5-9")
flags.DEFINE_string("kernel_sizes", "5,5", "Kernels size for each stage. Format: '3,3'")
flags.DEFINE_string("num_kernels", "5,15", "Num of kernels for each stage. Format: '4,10'")
flags.DEFINE_float("energy_percent", None, "Energy to be preserved in each stage")
flags.DEFINE_integer("use_num_images", -1, "Num of images used for training")
FLAGS = flags.FLAGS

def filtering(img, Laws):
    for i in range(2, 30):
        for j in range(2, 30):
                total = 0
                for m in [-2, -1, 0, 1, 2]:
                    for n in [-2, -1, 0, 1, 2]:
                        total += img[i + m][j + n] * Laws[5][m+2][n+2]
    
                img[i-2][j-2] = total
    
    return img

filter= np.array([[-1, -2, 0, 2, 1],      #E5
                      [-1, 0, 2, 0, -1],      #S5
                      [-1, 2, 0, -2, 1]])      #W5

def main():
	# read data
    train_images, train_labels, test_images, test_labels, class_list = data3.import_data(FLAGS.use_classes)
    print('Training image size:', train_images.shape)
    print('Testing_image size:', test_images.shape)
      
    new_train_images = train_images[:10000]
    new_train_labels = train_labels[:10000]
        
    for i in range(len(new_train_images)):
        new_train_images[i] = new_train_images[i]-np.mean(new_train_images[i], axis=None, keepdims=True)
        
    Laws = np.zeros((9,5,5), dtype=int)
    k=0
    for i in range(3):
        for j in range(3):
            Laws[k][:,:] = np.matmul(filter[i].reshape(5,1), filter[j].reshape(1,5))
            k += 1
    Laws = np.uint8(Laws)
    
    
    new_train_images2 = np.zeros((10000, 32, 32, 1))
    new_train_images2 = np.uint8(new_train_images2)
    
    for i in range(len(new_train_images)):
        new_train_images2[i] = filtering(new_train_images[i], Laws)
    
    
    
    kernel_sizes=saab3.parse_list_string(FLAGS.kernel_sizes)
    if FLAGS.num_kernels:
    	num_kernels=saab3.parse_list_string(FLAGS.num_kernels)
    else:
    	num_kernels=None
    energy_percent=FLAGS.energy_percent
    use_num_images=FLAGS.use_num_images
    print('Parameters:')
    print('use_classes:', class_list)
    print('Kernel_sizes:', kernel_sizes)
    print('Number_kernels:', num_kernels)
    print('Energy_percent:', energy_percent)
    print('Number_use_images:', use_num_images)

    pca_params=saab3.multi_Saab_transform(new_train_images2, new_train_labels,
    	                 kernel_sizes=kernel_sizes,
    	                 num_kernels=num_kernels,
    	                 energy_percent=energy_percent,
    	                 use_num_images=use_num_images,
    	                 use_classes=class_list)
    
    print("pca_params", pca_params)
    # save data
    fw=open('pca_params10.pkl','wb')    
    pickle.dump(pca_params, fw)    
    fw.close()

if __name__ == '__main__':
	main()

















