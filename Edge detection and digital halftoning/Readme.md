## Edge detection and digital halftoning
Description:
In this project I have implemented classical edge detection methods like Canny, Sobel and Structured edge detector and evaluated their performance. Halftoning methods like Dithering, Random thresholding, Floyd-Steinberg, JJN, and Stucki are implemeted for grayscale images. Separable error diffusion and MBVQ error diffusion halftoning methods for color images have been implemented.

Software Requirements:
1. Any C++ coding platform(JetBrains Clion used for this project)
2. Matlab R2016b is preferable or higher.

Usage:
1. To run Canny edge detection put all images in CannyStill folder.
2. To run other edge detection methods, put all images in same folder as the source files.
   
   Example usage:
   g++ filename.cpp -o filename
   ./filename input_image.raw output_image.raw BytesPerPixel width height
   
3. To run structured edge detection and evaluation insert all input images in edges-master folder. Execute edgesDemo.m for edge detection and                                                                                                                                 new_edgeeval.m for evaluation.  

