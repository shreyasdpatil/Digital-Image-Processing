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
    unsigned char newImagedata[height+4][width+4][1];
    unsigned char outImagedata[height][width];


    for (int x=0; x<height; x++){
        for (int y=0; y<width; y++){
            newImagedata[x+2][y+2][0] = Imagedata[x][y][0];
        }
    }

    // Extending rows
    for (int x=0; x<width; x++) {
        newImagedata[0][x+2][0] = Imagedata[2][x][0];
        newImagedata[1][x+2][0] = Imagedata[1][x][0];
        newImagedata[height + 2][x + 2][0] = Imagedata[height - 2][x][0];
        newImagedata[height + 3][x + 2][0] = Imagedata[height - 3][x][0];
    }

    // Extending columns
    for (int x=0; x<height; x++) {
        newImagedata[x+2][0][0] = newImagedata[x][2][0];
        newImagedata[x+2][1][0] = newImagedata[x][1][0];
        newImagedata[x + 2][width + 2][0] = newImagedata[x][width - 2][0];
        newImagedata[x + 3][width + 3][0] = newImagedata[x][width - 3][0];
    }


    for (int i = 2; i<height+2; i++){
        if ((i-2)%2!=0) {
            for (int j = 2; j < width+2; j++) {
                outImagedata[i-2][j-2] = (newImagedata[i][j][0] < 128) ? 0:255;
                int error = (int)(newImagedata[i][j][0] - outImagedata[i-2][j-2]);
                newImagedata[i][j+1][0] += (int)((8/42.0) * error);
                newImagedata[i][j + 2][0] += (int)((4/42.0) * error);

                newImagedata[i+1][j-2][0] += (int)((2/42.0) * error);
                newImagedata[i+1][j-1][0] += (int)((4/42.0)*error);
                newImagedata[i+1][j][0] += (int)((8/42.0)*error);
                newImagedata[i+1][j+1][0] += (int)((4/42.0)*error);
                newImagedata[i+1][j+2][0] += (int)((2/42.0)*error);

                newImagedata[i+2][j-2][0] += (int)((1/42.0)*error);
                newImagedata[i+2][j-1][0] += (int)((2/42.0)*error);
                newImagedata[i+2][j][0] += (int)((4/42.0)*error);
                newImagedata[i+2][j+1][0] += (int)((2/42.0)*error);
                newImagedata[i+2][j+2][0] += (int)((1/42.0)*error);
            }
        }
        else{
            for (int j = width+2; j >= 2; j--) {
                outImagedata[i-2][j-2] = (newImagedata[i][j][0] < 128) ? 0:255;
                int error = (int)(newImagedata[i][j][0] - outImagedata[i-2][j-2]);
                newImagedata[i][j-1][0] += (int)((8/42.0) * error);
                newImagedata[i][j - 2][0] += (int)((4/42.0) * error);

                newImagedata[i+1][j-2][0] += (int)((2/42.0) * error);
                newImagedata[i+1][j-1][0] += (int)((4/42.0)*error);
                newImagedata[i+1][j][0] += (int)((8/42.0)*error);
                newImagedata[i+1][j+1][0] += (int)((4/42.0)*error);
                newImagedata[i+1][j+2][0] += (int)((2/42.0)*error);

                newImagedata[i+2][j-2][0] += (int)((1/42.0)*error);
                newImagedata[i+2][j-1][0] += (int)((2/42.0)*error);
                newImagedata[i+2][j][0] += (int)((4/42.0)*error);
                newImagedata[i+2][j+1][0] += (int)((2/42.0)*error);
                newImagedata[i+2][j+2][0] += (int)((1/42.0)*error);
            }

        }
    }

    // Write image data (filename specified by second argument) from image data matrix

    if (!(file=fopen(argv[2],"wb"))) {
        cout << "Cannot open file: " << argv[2] << endl;
        exit(1);
    }
    fwrite(outImagedata, sizeof(unsigned char), height*width, file);
    fclose(file);

    return 0;
}
