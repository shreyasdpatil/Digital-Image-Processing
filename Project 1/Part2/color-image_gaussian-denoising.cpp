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
    unsigned char gaussian_denosimage[height][width][BytesPerPixel];
    unsigned char extendedimage2[height+4][width+4][BytesPerPixel];


    // Extended image for (5x5) Gaussian filter

    for (int x=0; x<height; x++){
        for (int y=0; y<width; y++){
            extendedimage2[x+2][y+2][0] = Imagedata[x][y][0];
            extendedimage2[x+2][y+2][1] = Imagedata[x][y][1];
            extendedimage2[x+2][y+2][2] = Imagedata[x][y][2];
        }
    }

    for (int x=0; x<width; x++) {
        for (int i = 0; i < 2; i++) {
            extendedimage2[i][x + 2][0] = Imagedata[2-i][x][0];
            extendedimage2[i][x + 2][1] = Imagedata[2-i][x][1];
            extendedimage2[i][x + 2][2] = Imagedata[2-i][x][2];
            extendedimage2[height + 2 +i][x + 2][0] = Imagedata[height - 2 - i][x][0];
            extendedimage2[height + 2 +i][x + 2][1] = Imagedata[height - 2 - i][x][1];
            extendedimage2[height + 2 +i][x + 2][2] = Imagedata[height - 2 - i][x][2];
        }
    }

    for (int x=0; x<height+4; x++) {
        for (int j = 0; j < 2; j++) {
            extendedimage2[x][j][0] = extendedimage2[x][4-j][0];
            extendedimage2[x][j][1] = extendedimage2[x][4-j][1];
            extendedimage2[x][j][2] = extendedimage2[x][4-j][2];
            extendedimage2[x][width + 2 +j][0] = extendedimage2[x][width-j][0];
            extendedimage2[x][width + 2 +j][1] = extendedimage2[x][width-j][1];
            extendedimage2[x][width + 2 +j][2] = extendedimage2[x][width-j][2];
        }
    }

    // Gaussian filter
    for(int i = 0; i<height; i++){
        for(int j=0; j<width; j++){
            gaussian_denosimage[i][j][0] = (extendedimage2[i][j][0] + extendedimage2[i][j+4][0] + extendedimage2[i+4][j][0] +
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

            gaussian_denosimage[i][j][1] = (extendedimage2[i][j][1] + extendedimage2[i][j+4][1] + extendedimage2[i+4][j][1] +
                                            extendedimage2[i+4][j+4][1] +
                                            4*(extendedimage2[i][j+1][1] + extendedimage2[i][j+3][1] +
                                               extendedimage2[i+1][j][1] + extendedimage2[i+3][j][1] + extendedimage2[i+4][j+1][1] +
                                               extendedimage2[i+4][j+3][1] + extendedimage2[i+1][j+4][1] + extendedimage2[i+3][j+4][1])+
                                            7 * (extendedimage2[i][j+2][1] + extendedimage2[i+4][j+2][1] + extendedimage2[i+2][j][1] +
                                                 extendedimage2[i+2][j+4][1]) +
                                            16*(extendedimage2[i+1][j+1][1] + extendedimage2[i+3][j+3][1] + extendedimage2[i+1][j+3][1] +
                                                extendedimage2[i+3][j+1][1]) +
                                            26* (extendedimage2[i+1][j+2][1] + extendedimage2[i+3][j+2][1] + extendedimage2[i+2][j+1][1] +
                                                 extendedimage2[i+2][j+3][1])+
                                            41* extendedimage2[i+2][j+2][1])/273;

            gaussian_denosimage[i][j][2] = (extendedimage2[i][j][2] + extendedimage2[i][j+4][2] + extendedimage2[i+4][j][2] +
                                            extendedimage2[i+4][j+4][2] +
                                            4*(extendedimage2[i][j+1][2] + extendedimage2[i][j+3][2] +
                                               extendedimage2[i+1][j][2] + extendedimage2[i+3][j][2] + extendedimage2[i+4][j+1][2] +
                                               extendedimage2[i+4][j+3][2] + extendedimage2[i+1][j+4][2] + extendedimage2[i+3][j+4][2])+
                                            7 * (extendedimage2[i][j+2][2] + extendedimage2[i+4][j+2][2] + extendedimage2[i+2][j][2] +
                                                 extendedimage2[i+2][j+4][2]) +
                                            16*(extendedimage2[i+1][j+1][2] + extendedimage2[i+3][j+3][2] + extendedimage2[i+1][j+3][2] +
                                                extendedimage2[i+3][j+1][2]) +
                                            26* (extendedimage2[i+1][j+2][2] + extendedimage2[i+3][j+2][2] + extendedimage2[i+2][j+1][2] +
                                                 extendedimage2[i+2][j+3][2])+
                                            41* extendedimage2[i+2][j+2][2])/273;
        }
    }


    if (!(file=fopen(argv[2],"wb"))) {
        cout << "Cannot open file: " << argv[2] << endl;
        exit(1);
    }
    fwrite(gaussian_denosimage, sizeof(unsigned char), width*height*BytesPerPixel, file);
    fclose(file);

    return 0;
}
