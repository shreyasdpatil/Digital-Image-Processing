Name: Shreyas Patil
USC Email: shreyasp@usc.edu

#include <stdio.h>
#include <iostream>
#include <stdlib.h>
#include <math.h>

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

    // Problem 2 (a)
    unsigned char denosimage[height][width][BytesPerPixel];
    unsigned char extendedimage[height+2][width+2][BytesPerPixel];
    unsigned char extendedimage2[height+4][width+4][BytesPerPixel];

    // Extended image for 3x3 filter
    for (int x=0; x<height; x++){
        for (int y=0; y<width; y++){
            extendedimage[x+1][y+1][0] = Imagedata[x][y][0];
        }
    }

    for (int x=0; x<width; x++){
        extendedimage[0][x][0] = Imagedata[1][x][0];
        extendedimage[height+1][x][0] = Imagedata[height-2][x][0];
    }

    for (int x=0; x<height; x++){
        extendedimage[x][0][0] = Imagedata[x][1][0];
        extendedimage[x][width+1][0] = Imagedata[x][width-2][0];
    }

    // Extended image for Gaussian filter

    for (int x=0; x<height; x++){
        for (int y=0; y<width; y++){
            extendedimage2[x+2][y+2][0] = Imagedata[x][y][0];
        }
    }

    for (int x=0; x<width; x++){
        extendedimage2[0][x+2][0] = Imagedata[2][x][0];
        extendedimage2[1][x+2][0] = Imagedata[1][x][0];
        extendedimage2[height + 2][x + 2][0] = Imagedata[height - 2][x][0];
        extendedimage2[height + 3][x + 2][0] = Imagedata[height - 3][x][0];
    }

    for (int x=0; x<height; x++){
        extendedimage2[x+2][0][0] = extendedimage2[x][2][0];
        extendedimage2[x+2][1][0] = extendedimage2[x][1][0];
        extendedimage2[x+2][width+2][0] = extendedimage2[x][width-2][0];
        extendedimage2[x+2][width+3][0] = extendedimage2[x][width-3][0];
    }


/*  // Uniform filter
    for(int i = 0; i<height; i++){
        for(int j=0; j<width; j++){
            denosimage[i][j][BytesPerPixel] = (extendedimage[i][j][BytesPerPixel] + extendedimage[i][j+1][BytesPerPixel] + extendedimage[i][j+2][BytesPerPixel] +
                                               extendedimage[i+1][j][BytesPerPixel] + extendedimage[i+1][j+1][BytesPerPixel] + extendedimage[i+1][j+2][BytesPerPixel] +
                                               extendedimage[i+2][j][BytesPerPixel] + extendedimage[i+2][j+1][BytesPerPixel] + extendedimage[i+2][j+2][BytesPerPixel])/9;
        }
    }
*/

    // Gaussian filter
    for(int i = 0; i<height; i++){
        for(int j=0; j<width; j++){
            denosimage[i][j][0] = (extendedimage2[i][j][0] + extendedimage2[i][j+4][0] + extendedimage2[i+4][j][0] +
                                   extendedimage2[i+4][j+4][0] +
                                   4*(extendedimage2[i][j+1][0] + extendedimage2[i][j+3][0] +
                                      extendedimage2[i+1][j][0] + extendedimage2[i+3][j][0] + extendedimage2[i+4][j+1][0] +
                                      extendedimage2[i+4][j+3][0] + extendedimage2[i+1][j+4][0] + extendedimage2[i+3][j+4][0])+
                                   7 * (extendedimage2[i][j+2][0] + extendedimage2[i+4][j+2][0] + extendedimage2[i+2][j][0] +
                                        extendedimage2[i+2][j+4][0]) +
                                   16*(extendedimage2[i+1][j+1][0] + extendedimage2[i+3][j+3][0] + extendedimage2[i+1][j+3][0] +
                                       extendedimage2[i+3][j+1][0]) +
                                   26* (extendedimage2[i+1][j+2][0] + extendedimage2[i+3][j+2][0] + extendedimage2[i+2][j+1][0] +
                                        extendedimage2[i+2][j+3][0])+
                                   41* extendedimage2[i+2][j+2][0])/273;
        }
    }

    if (!(file=fopen(argv[2],"wb"))) {
        cout << "Cannot open file: " << argv[2] << endl;
        exit(1);
    }
    fwrite(denosimage, sizeof(unsigned char), width*height*BytesPerPixel, file);
    fclose(file);

    return 0;
}
