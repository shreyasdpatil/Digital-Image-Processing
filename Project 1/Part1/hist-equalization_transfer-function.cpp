Name: Shreyas Patil
USC Email: shreyasp@usc.edu

#include <stdio.h>
#include <iostream>
#include <stdlib.h>
#include <algorithm>
#include<fstream>


using namespace std;

int *location(int value, int occurence, int array[]){
    static int  pposition[2];
    for(int i=0; i<160000; i++){
        if(value==array[i]){
            pposition[0] = i+occurence;
            pposition[1] = pposition[0]/625;
        }
    }
    return pposition;
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

    // Method A

    // Creating Histogram array
    float ahist[256];
    float ahistnorm[256];
    for(int k=0; k<256; k++){
        ahist[k] = 0;
        ahistnorm[k] = 0;
    }
    for(int i=0; i<400; i++){
        for (int j=0; j<400; j++){
            ahist[Imagedata[i][j][0]] = ahist[Imagedata[i][j][0]] + 1;
            ahistnorm[Imagedata[i][j][0]] = ahist[Imagedata[i][j][0]] + 1;
        }
    }


    // Normalizing Histogram
    for (int i=0; i<256; i++){
        ahistnorm[i] = ahistnorm[i]/160000;
    }

    // Calculating CDF
    float cdf[256];
    cdf[0] = ahist[0];
    for(int k=1; k<256; k++){
        cdf[k] = cdf[k-1] + ahistnorm[k];
    }

    unsigned char outputaimage[height][width][BytesPerPixel];
    for(int i=0; i<400; i++){
        for(int j=0; j<400; j++){
            outputaimage[i][j][0] = (int)(cdf[Imagedata[i][j][0]]*255);
        }
    }


    // Write image data (filename specified by second argument) from image data matrix

    if (!(file=fopen(argv[2],"wb"))) {
        cout << "Cannot open file: " << argv[2] << endl;
        exit(1);
    }
    fwrite(outputaimage, sizeof(unsigned char), width*height*1, file);
    fclose(file);

    ofstream histfile("hist_rose_bright_A.txt");
    if (histfile.is_open()){
        for (int i=0; i<256; i++){
            histfile<< ahist[i] << " ";
        }
    histfile.close();
    }

    return 0;
}
