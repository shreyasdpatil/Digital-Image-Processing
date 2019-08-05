Name: Shreyas Patil
USC Email: shreyasp@usc.edu
Date: 2/12/2019

#include <stdio.h>
#include <iostream>
#include <stdlib.h>
#include <math.h>
#include <cstdlib>

using namespace std;

int main(int argc, char *argv[])

{
    // Define file pointer and variables
    FILE *file;
    int BytesPerPixel;
    int width = 600;
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
    float newImagedata[height+2][width+2][1];
    unsigned char outImagedata[height][width][1];


    for (int x=0; x<height; x++){
        for (int y=0; y<width; y++){
            newImagedata[x+1][y+1][0] = Imagedata[x][y][0];
        }
    }

    // Extending rows
    for (int x=0; x<width; x++){
        newImagedata[0][x][0] = Imagedata[1][x][0];
        newImagedata[height+1][x][0] = Imagedata[height-2][x][0];
    }

    // Extending columns
    for (int x=0; x<height+2; x++){
        newImagedata[x][0][0] = newImagedata[x][2][0];
        newImagedata[x][width+1][0] = newImagedata[x][width-1][0];
    }


    for (int i = 1; i<height+1; i++){
        if (i%2!=0) {
            for (int j = 1; j < width+1; j++) {
                if (newImagedata[i][j][0] < 128) {
                    newImagedata[i][j+1][0] += (7/16.0) * newImagedata[i][j][0];
                    newImagedata[i+1][j - 1][0] += (3/16.0) * newImagedata[i][j][0];
                    newImagedata[i+1][j][0] += (5/16.0) * newImagedata[i][j][0];
                    newImagedata[i+1][j+1][0] += (1/16.0)*newImagedata[i][j][0];
                    newImagedata[i][j][0] = 0;
                } else {
                    newImagedata[i][j + 1][0] += (7 / 16.0) * (newImagedata[i][j][0] - 255);
                    newImagedata[i + 1][j - 1][0] += (3 / 16.0) * (newImagedata[i][j][0] - 255);
                    newImagedata[i + 1][j][0] += (5 / 16.0) * (newImagedata[i][j][0] - 255);
                    newImagedata[i + 1][j + 1][0] += (1 / 16.0) * (newImagedata[i][j][0] - 255);
                    newImagedata[i][j][0] = 255;
                }
            }
        }
        else{
            for (int j = width; j >= 1; j--) {
                if (newImagedata[i][j][0] < 128) {
                    newImagedata[i][j - 1][0] += (7/16.0) * newImagedata[i][j][0];
                    newImagedata[i + 1][j - 1][0] += (1/16.0)*newImagedata[i][j][0];
                    newImagedata[i + 1][j][0] += (5/16.0) * newImagedata[i][j][0];
                    newImagedata[i + 1][j + 1][0] += (3/16.0)* newImagedata[i][j][0];
                    newImagedata[i][j][0] = 0;
                } else {
                    newImagedata[i][j - 1][0] += (7/16.0) * (newImagedata[i][j][0] - 255);
                    newImagedata[i + 1][j - 1][0] += (1/16.0)*(newImagedata[i][j][0] - 255);
                    newImagedata[i + 1][j][0] += (5/16.0) * (newImagedata[i][j][0] - 255);
                    newImagedata[i + 1][j + 1][0] += (3/16.0)*(newImagedata[i][j][0] - 255);
                    newImagedata[i][j][0] = 255;
                }
            }

        }

    }

    for(int m=1; m<height+1; m++){
        for(int n=1; n<width+1; n++){
            outImagedata[m-1][n-1][0] = newImagedata[m][n][0];

        }
    }

    // Write image data (filename specified by second argument) from image data matrix

    if (!(file=fopen(argv[2],"wb"))) {
        cout << "Cannot open file: " << argv[2] << endl;
        exit(1);
    }
    fwrite(outImagedata, sizeof(unsigned char), height*width*BytesPerPixel, file);
    fclose(file);

    return 0;
}
