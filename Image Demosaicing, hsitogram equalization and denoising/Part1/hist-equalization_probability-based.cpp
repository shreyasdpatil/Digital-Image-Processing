Name: Shreyas Patil
USC Email: shreyasp@usc.edu

#include <stdio.h>
#include <iostream>
#include <stdlib.h>
#include <algorithm>

using namespace std;

int location(int value, int occurence, int array[]){
    static int  pposition[2];
    for(int i=0; i<160000; i++){
        if(value==array[i]){
            pposition[0] = i+occurence;
            pposition[1] = pposition[0]/625;
        }
    }
    return pposition[1];
}

int main(int argc, char *argv[])

{
    // Define file pointer and variables
    FILE *file;
    int BytesPerPixel;
    int width = 400;
    int height = 400;

    // Check for proper syntax
    if (argc < 3){
        cout << "Syntax Error - Incorrect Parameter Usage:" << endl;
        cout << "program_name input_image.raw output_image.raw [BytesPerPixel = 1] [Size = 256]" << endl;
        return 0;
    }

    // Check if image is grayscale or color
    if (argc < 4){
        BytesPerPixel = 1; // default is grey image
    }
    else {
        BytesPerPixel = atoi(argv[3]);
        // Check if size is specified
        if (argc >= 5){
            width = atoi(argv[4]);
            height = atoi(argv[5]);
        }
    }

    // Allocate image data array
    unsigned char Imagedata[height][width][BytesPerPixel];

    // Read image (filename specified by first argument) into image data matrix
    if (!(file=fopen(argv[1],"rb"))) {
        cout << "Cannot open file: " << argv[1] <<endl;
        exit(1);
    }
    fread(Imagedata, sizeof(unsigned char), width*height*BytesPerPixel, file);
    fclose(file);

    ///////////////////////// INSERT YOUR PROCESSING CODE HERE /////////////////////////

    // Method B

    // Creating Histogram array
    int bhist[256];
    for(int k=0; k<256; k++){
        bhist[k] = 0;
    }
    for(int i=0; i<400; i++){
        for (int j=0; j<400; j++){
            bhist[Imagedata[i][j][0]] = bhist[Imagedata[i][j][0]] + 1;
        }
    }

    // Making 3D array to 1D
    static int Imagearray[160000];
    static int sortarray[160000];
    int k = 0;
    for(int i=0; i<height; i++){
        for(int j=0; j<width; j++){
            Imagearray[k] = Imagedata[i][j][0];
            sortarray[k] = Imagedata[i][j][0];
            k = k+1;
        }
    }

    sort(sortarray, sortarray+160000);
    int block = (height*width)/256;

    int count[256];
    for(int k=0; k<256; k++){
        count[k] = 0;
    }
    int outimagearray[160000];
    for(int i=0; i<height*width; i++) {
        for(int j=0; j<256; j++){
            if(count[j]==Imagearray[i]){
                count[j] = count[j] +1;
            }
        }
        outimagearray[i] = location(Imagearray[i], count[Imagearray[i]], sortarray);
    }

    //Converting output 1D array to 3D
    k =0;
    unsigned char outputbimage[height][width][BytesPerPixel];
    for(int i=0; i<height; i++){
        for(int j=0; j<width; j++){
            outputbimage[i][j][0] = outimagearray[k];
            k = k+1;
        }
    }


    // Write image data (filename specified by second argument) from image data matrix

    if (!(file=fopen(argv[2],"wb"))) {
        cout << "Cannot open file: " << argv[2] << endl;
        exit(1);
    }
    fwrite(outputbimage, sizeof(unsigned char), width*height*1, file);
    fclose(file);

    return 0;
}
