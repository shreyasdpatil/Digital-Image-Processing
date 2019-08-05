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
    unsigned char denosimage[height][width][BytesPerPixel];

    // Read image (filename specified by first argument) into image data matrix
    if (!(file=fopen(argv[1],"rb"))) {
        cout << "Cannot open file: " << argv[1] <<endl;
        exit(1);
    }
    fread(Imagedata, sizeof(unsigned char), width*height*BytesPerPixel, file);
    fclose(file);


    unsigned char trans_image[height][width][BytesPerPixel];

    // Applying the Anscombe root transformation on each pixel
    for(int i = 0; i<height; i++){
        for(int j=0; j<width; j++){
            trans_image[i][j][0] = (int)(2 * sqrt(Imagedata[i][j][0] + (float)3/(float)8));
//            cout << (int)trans_image[i][j][0] <<endl;
        }
    }


    // Extended image for 5x5 Gaussian filter
    unsigned char extendedimage2[height+4][width+4][BytesPerPixel];

    for (int x=0; x<height; x++){
        for (int y=0; y<width; y++){
            extendedimage2[x+2][y+2][0] = trans_image[x][y][0];
        }
    }

    for (int x=0; x<width; x++) {
            extendedimage2[0][x+2][0] = trans_image[2][x][0];
            extendedimage2[1][x+2][0] = trans_image[1][x][0];
            extendedimage2[height + 2][x + 2][0] = trans_image[height - 2][x][0];
        extendedimage2[height + 3][x + 2][0] = trans_image[height - 3][x][0];
    }

    for (int x=0; x<height; x++) {
        extendedimage2[x+2][0][0] = trans_image[x][2][0];
        extendedimage2[x+2][1][0] = trans_image[x][1][0];
        extendedimage2[x + 2][width + 2][0] = trans_image[x][width - 2][0];
        extendedimage2[x + 3][width + 3][0] = trans_image[x][width - 3][0];
    }

    // Applying Gaussian filter to the transformed image
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

    //Reconstructing the image by taking inverse Anscombe root transformation
    unsigned char inv_trans_image[height][width][BytesPerPixel];
    for(int i = 0; i<height; i++){
        for(int j=0; j<width; j++){
            inv_trans_image[i][j][0] = (int)(pow(0.5*denosimage[i][j][0], 2) - (float)3/(float)8);
        }
    }

    // Write image data (filename specified by second argument) from image data matrix

    if (!(file=fopen(argv[2],"wb"))) {
        cout << "Cannot open file: " << argv[2] << endl;
        exit(1);
    }
    fwrite(inv_trans_image, sizeof(unsigned char), width*height*BytesPerPixel, file);
    fclose(file);

    return 0;
}
