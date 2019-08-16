# Image Demosaicing, histogram equalization and denoising
## Description: 
This repository contains C++ code for bilinear demosaicing and MHC demosaicing and compares them visually. Contrast adjustment of images using transfer function based histogram equalization and cumulative probability based histogram equalization has been implemented. Various image denoising methods have been implemented to remove uniform noise, mixed noise(impulse and uniform) and shot noise. 

## Requirements:
1. Windows 10 used(Linux or Mac is also fine).
2. g++ compiler for compiling C++ code(JetBrains Clion IDE used for this project).

## Usage:
Use below command to run each file.

`g++ filename.cpp
./filename inputImageName outputImageName BytesPerPixel Width Height`


