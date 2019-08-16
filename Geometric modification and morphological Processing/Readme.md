# Geometric modification and morphological processing
### Description: 
In this project I have implemented various geometric transformations for different applications. Lens distortion introduced in images has been corrected using reverse address mapping technique. Morphological operations like thinning, shrinking and skeletonizing have been implemented and utilized for object anlysis in an image.

### Requirements:
1) Any IDE for python scripting(spyder used)
2) IDE for C++ coding(Clion used)
3) gcc/g++ compiler
4) Matlab 2016b+

### Usage:
1. For geometric modification, run following python files for each subimages as below

   ```
   python geom-trans-img1.py
   python geom-trans-img2.py
   python geom-trans-img3.py
   ```

   To get the final transformed image run,
   
   `python geom-trans.py`
  
2. To run the lens distortion correction script
   python lens-distortion-correction.py
  
3. For morphological processing use the below commands
   For shrinking:
   g++ shrinking.cpp
   ./a.out pattern1.raw pattern1_shrink_out.raw 1 375 375
   
   For thinning:
   g++ thinning.cpp
   ./a.out pattern1.raw pattern1_thin_out.raw 1 375 375
   
   For skeletonizing:
   g++ skeletonizing1.cpp
   ./a.out pattern1.raw pattern1_skele_out.raw 1 375 375
   
   Replace pattern1 with filename of input raw images.
   
4. For defect detection run
   g++ defect-detection.cpp
   ./a.out deer.raw deer_out.raw 1 500 690
   deer.raw is the input image name and deer_out.raw is the ouput image name.
   
5. For object analysis in image(in this case rice grains in the image) run object_analysis.m file in Matlab.
   

   
   
