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

    // Extending image boundaries by 1 on each side
    for (int x=0; x<height; x++){
        for (int y=0; y<width; y++){
            extendedimage[x+1][y+1][0] = Imagedata[x][y][0];
        }
    }

    for (int x=0; x<width; x++){
        extendedimage[0][x+1][0] = Imagedata[1][x][0];
        extendedimage[height+1][x+1][0] = Imagedata[height-2][x][0];
    }

    for (int x=0; x<height+1; x++){
        extendedimage[x][0][0] = extendedimage[x][2][0];
        extendedimage[x][width+1][0] = extendedimage[x][width-1][0];
    }


    for(int i = 1; i<height+1; i++){
        for(int j=1; j<width+1; j++){
            denosimage[i-1][j-1][0] = (extendedimage[i-1][j-1][0] + extendedimage[i-1][j][0] + extendedimage[i-1][j+1][0] +
                                   extendedimage[i][j-1][0] + extendedimage[i][j][0] + extendedimage[i][j+1][0] +
                                   extendedimage[i+1][j-1][0] + extendedimage[i+1][j][0] + extendedimage[i+1][j+1][0])/9;
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
