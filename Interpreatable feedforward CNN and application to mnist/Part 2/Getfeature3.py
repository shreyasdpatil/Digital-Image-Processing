#Name: Shreyas Patil
#USC Email: shreyasp@usc.edu
#Date: 4/28/2019
import pickle
import numpy as np
import data3
import saab3

def main():
    # load data
    fr=open('pca_params10.pkl','rb')  
    pca_params=pickle.load(fr)
    fr.close()

    # read data
    train_images, train_labels, test_images, test_labels, class_list = data3.import_data("0-9")
    print('Training image size:', train_images.shape)
    print('Testing_image size:', test_images.shape)
    
    # Training
    f = []
    for i in range(600):
        print('--------Training--------')
        trn_images=train_images[i*100:100*(i+1)]
        feature = saab3.initialize(trn_images, pca_params)
        feature = feature.reshape(feature.shape[0], -1)
        f.append(feature)

    f = np.vstack(f)
    print("S4 shape:", feature.shape)
    print('--------Finish Feature Extraction subnet--------')
    feat={}
    feat['feature']=f
	
    # save data
    fw=open('feat10.pkl','wb')    
    pickle.dump(feat, fw)    
    fw.close()

if __name__ == '__main__':
	main()
