Part 1:
Run Getkernel1.py to get learned kernels.
Run inverse_saab_transform to get reconstructed images and PSNR. Change number of kernels in Getkernel1.py
for different settings as shown in report.

Part 2:
Run Getkernel3.py to get learned kernels.
Run Getfeatures3.py to get ouptut features of conv layers.
Run Getweights3.py to get weights and biases of fc layers.
Run mnist_test.py to get test accuracy for individual settings.
Run SVM.py to get final ensemnble train and test accuracy.
Repeat the above steps for different kernel sizes for 4 different settings.

Run Getkernel_laws.py to get kernels trained on 10000 Laws filtered images.
Run Getfeature3.py to get output decision vector of conv stage.
Run Getweights3.py to get weights and biases of fc layers. 
Run mnist_test.py to get test accuracy for individual settings.
Run SVM.py to get final ensemnble train and test accuracy.
Do the above steps for 6 different Laws filters.