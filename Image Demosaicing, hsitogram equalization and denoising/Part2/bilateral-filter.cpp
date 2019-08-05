Name: Shreyas Patil
USC Email: shreyasp@usc.edu

#include <stdio.h>
#include <iostream>
#include <stdlib.h>
#include <math.h>

using namespace std;
double filter[3][3];
void weight(int row, int column, unsigned char I[][258][1], int c, int s){
    double sum = 0.0;
    for (int i=-1; i<2; i++){
        for (int j=-1; j<2; j++){
            filter[i+1][j+1] = exp((-(i*i)-(j*j))/(2*(c*c))) * exp(-pow((I[row+i][column+j][0]-I[row][column][0]), 2)/(2*(s*s)));
            sum += filter[i+1][j+1];
        }
    }

    for (int i = 0; i < 3; ++i) {
        for (int j = 0; j < 3; ++j){
            filter[i][j] /= sum;
    }
    }
}

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
    unsigned char extendedimage[258][258][1];

    // Extended image for 3x3 filter
    for (int x=0; x<height; x++){
        for (int y=0; y<width; y++){
            extendedimage[x+1][y+1][0] = Imagedata[x][y][0];
        }
    }

    for (int x=0; x<width; x++){
        extendedimage[0][x+1][0] = Imagedata[1][x][0];
        extendedimage[height+1][x+1][0] = Imagedata[height-2][x][0];
    }

    for (int x=0; x<height; x++){
        extendedimage[x+1][0][0] = extendedimage[x][1][0];
        extendedimage[x+1][width+1][0] = extendedimage[x][width-2][0];
    }


    //3x3 Bilateral filters
    for(int i = 1; i<height+1; i++){
        for(int j=1; j<width+1; j++){
            weight(i, j, extendedimage, 1, 1);
            denosimage[i-1][j-1][0] = (filter[0][0]*extendedimage[i][j][0] + filter[0][1]*extendedimage[i][j+1][0] + filter[0][2]*extendedimage[i][j+2][0] +
                    filter[1][0]*extendedimage[i+1][j][0] + filter[1][1]*extendedimage[i+1][j+1][0] + filter[1][2]*extendedimage[i+1][j+2][0] +
                    filter[2][0]*extendedimage[i+2][j][0] + filter[2][1]*extendedimage[i+2][j+1][0] + filter[2][2]*extendedimage[i+2][j+2][0]);
        }
    }

    // Write image data (filename specified by second argument) from image data matrix

    if (!(file=fopen(argv[2],"wb"))) {
        cout << "Cannot open file: " << argv[2] << endl;
        exit(1);
    }
    fwrite(denosimage, sizeof(unsigned char), width*height*1, file);
    fclose(file);

    return 0;
}
