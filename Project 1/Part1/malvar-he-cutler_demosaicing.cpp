Name: Shreyas Patil
USC Email: shreyasp@usc.edu

#include <stdio.h>
#include <iostream>
#include <stdlib.h>

using namespace std;

int main(int argc, char *argv[])

{
    // Define file pointer and variables
    FILE *file;
    int BytesPerPixel;
    int width = 390;
    int height = 300;

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

    unsigned char extendedimage[height+4][width+4][BytesPerPixel];

    for (int x=0; x<height; x++){
        for (int y=0; y<width; y++){
            extendedimage[x+2][y+2][0] = Imagedata[x][y][0];
        }
    }

    for (int x=0; x<width; x++){
        extendedimage[0][x+2][0] = Imagedata[2][x][0];
        extendedimage[1][x+2][0] = Imagedata[1][x][0];
        extendedimage[height+2][x+2][0] = Imagedata[height-2][x][0];
        extendedimage[height+3][x+2][0] = Imagedata[height-3][x][0];
    }

    for (int x=0; x<height; x++){
        extendedimage[x+2][0][0] = extendedimage[x][2][0];
        extendedimage[x+2][1][0] = extendedimage[x][1][0];
        extendedimage[x+2][width+2][0] = extendedimage[x][width-2][0];
        extendedimage[x+2][width+3][0] = extendedimage[x][width-3][0];
    }


    unsigned char mhcimage[height][width][3];

    for (int a=0; a<height; a++){
        for (int b=0; b<width; b++){
            if (a%2==0){
                if (b%2==0){
                    mhcimage[a][b][0] = (5*extendedimage[a+2][b+2][0] + 4*(extendedimage[a+2][b+1][0] + extendedimage[a+2][b+3][0]) -
                                         extendedimage[a+2][b][0] - extendedimage[a+2][b+4][0] - extendedimage[a+1][b+1][0] -
                                         extendedimage[a+1][b+3][0] - extendedimage[a+3][b+1][0] - extendedimage[a+3][b+3][0]
                                         + 0.5*(extendedimage[a][b+2][0] + extendedimage[a+4][b+2][0]))/8;

                    mhcimage[a][b][1] = extendedimage[a+2][b+2][0];

                    mhcimage[a][b][2] = (5*extendedimage[a+2][b+2][0] + 4*(extendedimage[a+1][b+2][0] + extendedimage[a+3][b+2][0]) +
                                         0.5*(extendedimage[a+2][b][0] + extendedimage[a+2][b+4][0]) - extendedimage[a][b+2][0] -
                                         extendedimage[a+4][b+2][0] - extendedimage[a+1][b+1][0] - extendedimage[a+3][b+1][0]
                                         - extendedimage[a+1][b+3][0] - extendedimage[a+3][b+3][0])/8;
                }
                else{
                    mhcimage[a][b][0] = extendedimage[a+2][b+2][0];

                    mhcimage[a][b][1] = (4*extendedimage[a+2][b+2][0] + 2*(extendedimage[a+1][b+2][0] + extendedimage[a+3][b+2][0] + extendedimage[a+2][b+1][0] + extendedimage[a+2][b+3][0]) -
                                         (extendedimage[a][b+2][0] + extendedimage[a+4][b+2][0] + extendedimage[a+2][b][0] + extendedimage[a+2][b+4][0]))/8;

                    mhcimage[a][b][2] = (6*extendedimage[a+2][b+2][0] + 2*(extendedimage[a+1][b+1][0] + extendedimage[a+3][b+1][0] + extendedimage[a+1][b+3][0] + extendedimage[a+3][b+3][0])
                                         -(1.5)*(extendedimage[a+2][b][0] + extendedimage[a][b+2][0] + extendedimage[a+4][b+2][0] + extendedimage[a+2][b+4][0]))/8;
                }
            }
            else {
                if (b%2==0){
                    mhcimage[a][b][0] = (6*extendedimage[a+2][b+2][0] + 2*(extendedimage[a+1][b+1][0] + extendedimage[a+3][b+1][0] + extendedimage[a+1][b+3][0] + extendedimage[a+3][b+3][0])
                                         -(1.5)*(extendedimage[a+2][b][0] + extendedimage[a][b+2][0] + extendedimage[a+4][b+2][0] + extendedimage[a+2][b+4][0]))/8;

                    mhcimage[a][b][1] = (4*extendedimage[a+2][b+2][0] + 2*(extendedimage[a+1][b+2][0] + extendedimage[a+3][b+2][0] + extendedimage[a+2][b+1][0] + extendedimage[a+2][b+3][0]) -
                                         (extendedimage[a][b+2][0] + extendedimage[a+4][b+2][0] + extendedimage[a+2][b][0] + extendedimage[a+2][b+4][0]))/8;

                    mhcimage[a][b][2] = extendedimage[a+2][b+2][0];
                }
                else{
                    mhcimage[a][b][0] = (5*extendedimage[a+2][b+2][0] + 4*(extendedimage[a+1][b+2][0] + extendedimage[a+3][b+2][0]) +
                                         0.5*(extendedimage[a+2][b][0] + extendedimage[a+2][b+4][0]) - extendedimage[a][b+2][0] -
                                         extendedimage[a+4][b+2][0] - extendedimage[a+1][b+1][0] - extendedimage[a+3][b+1][0]
                                         - extendedimage[a+1][b+3][0] - extendedimage[a+3][b+3][0])/8;

                    mhcimage[a][b][1] = extendedimage[a+2][b+2][0];

                    mhcimage[a][b][2] = (5*extendedimage[a+2][b+2][0] + 4*(extendedimage[a+2][b+1][0] + extendedimage[a+2][b+3][0]) -
                                         extendedimage[a+2][b][0] - extendedimage[a+2][b+4][0] - extendedimage[a+1][b+1][0] -
                                         extendedimage[a+1][b+3][0] - extendedimage[a+3][b+1][0] - extendedimage[a+3][b+3][0]
                                         + 0.5*(extendedimage[a][b+2][0] + extendedimage[a+4][b+2][0]))/8;
                }

            }
        }
    }

    // Write image data (filename specified by second argument) from image data matrix

    if (!(file=fopen(argv[2],"wb"))) {
        cout << "Cannot open file: " << argv[2] << endl;
        exit(1);
    }
    fwrite(mhcimage, sizeof(unsigned char), width*height*3, file);
    fclose(file);

    return 0;
}

