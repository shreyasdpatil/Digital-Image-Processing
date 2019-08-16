I = imread('rice.raw');

gray = rgb2gray(I)


figure(1)
imshow(I)


J = imdilate(I,SE)


