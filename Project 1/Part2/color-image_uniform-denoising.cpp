Name: Shreyas Patil
USC Email: shreyasp@usc.edu

#include <stdio.h>
#include <iostream>
#include <stdlib.h>
#include <math.h>
#include <algorithm>

using namespace std;

int main(int argc, char *argv[])

{
    // Define file pointer and variables
    FILE *file;
    int BytesPerPixel;
    int width = 256;
    int height = 256;

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

    unsigned char denosimage[height][width][BytesPerPixel];
    unsigned char uniform_denosimage[height][width][BytesPerPixel];
    static unsigned char extendedimage[258][258][3];

    // Extended image for 3x3 filter
    for (int x=0; x<height; x++){
        for (int y=0; y<width; y++){
            extendedimage[x+1][y+1][0] = Imagedata[x][y][0];
            extendedimage[x+1][y+1][1] = Imagedata[x][y][1];
            extendedimage[x+1][y+1][2] = Imagedata[x][y][2];
        }
    }

    for (int x=0; x<width; x++){
        extendedimage[0][x][0] = Imagedata[1][x][0];
        extendedimage[0][x][1] = Imagedata[1][x][1];
        extendedimage[0][x][2] = Imagedata[1][x][2];
        extendedimage[height+1][x][0] = Imagedata[height-1][x][0];
        extendedimage[height+1][x][1] = Imagedata[height-1][x][1];
        extendedimage[height+1][x][2] = Imagedata[height-1][x][2];
    }

    for (int x=0; x<height+2; x++){
        extendedimage[x][0][0] = extendedimage[x][2][0];
        extendedimage[x][0][1] = extendedimage[x][2][1];
        extendedimage[x][0][2] = extendedimage[x][2][2];
        extendedimage[x][width+1][0] = extendedimage[x][width-1][0];
        extendedimage[x][width+1][1] = extendedimage[x][width-1][1];
        extendedimage[x][width+1][2] = extendedimage[x][width-1][2];
    }


    // Uniform Filter
    for(int i = 0; i<height; i++){
        for(int j=0; j<width; j++){
            uniform_denosimage[i][j][0] = (extendedimage[i][j][0] + extendedimage[i][j+1][0] + extendedimage[i][j+2][0] +
                                    extendedimage[i+1][j][0] + extendedimage[i+1][j+1][0] + extendedimage[i+1][j+2][0] +
                                    extendedimage[i+2][j][0] + extendedimage[i+2][j+1][0] + extendedimage[i+2][j+2][0])/9;


            uniform_denosimage[i][j][1] = (extendedimage[i][j][1] + extendedimage[i][j+1][1] + extendedimage[i][j+2][1] +
                                   extendedimage[i+1][j][1] + extendedimage[i+1][j+1][1] + extendedimage[i+1][j+2][1] +
                                   extendedimage[i+2][j][1] + extendedimage[i+2][j+1][1] + extendedimage[i+2][j+2][1])/9;

            uniform_denosimage[i][j][2] = (extendedimage[i][j][2] + extendedimage[i][j+1][2] + extendedimage[i][j+2][2] +
                                   extendedimage[i+1][j][2] + extendedimage[i+1][j+1][2] + extendedimage[i+1][j+2][2] +
                                   extendedimage[i+2][j][2] + extendedimage[i+2][j+1][2] + extendedimage[i+2][j+2][2])/9;
        }
    }





    // Write image data (filename specified by second argument) from image data matrix

    if (!(file=fopen(argv[2],"wb"))) {
        cout << "Cannot open file: " << argv[2] << endl;
        exit(1);
    }

    fwrite(uniform_denosimage, sizeof(unsigned char), width*height*BytesPerPixel, file);
    fclose(file);

    return 0;
}
