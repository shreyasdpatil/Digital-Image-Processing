Name: Shreyas Patil
USC Email: shreyasp@usc.edu
Date: 2/12/2019

#include <stdio.h>
#include <iostream>
#include <stdlib.h>
#include <math.h>
#include <cstdlib>

using namespace std;
int vertex[3];

int find_MBVQ(int R, int G, int B){
    if (R+G>255){
        if (G+B>255) {
            if (R + G + B > 510) {
                return 1;
            }
            else {
                return 2;
            }
        }
        else{
            return 3;
        }
    }
    else{
        if(!((G+B) > 255)) {
            if (!((R + G + B) > 255)) {
                return 4;
            } else {
                return 5;
            }
        }
        else{
            return 6;
        }
    }
}

void getNearestVertex(int mbvq, int R, int G, int B) {
    // No.1 for CMYW
    if (mbvq == 1) {
        vertex[0] = 255;    //White
        vertex[1] = 255;
        vertex[2] = 255;
        if (B < 128){
            if (B <= R){
                if (B <= G){
                    vertex[0] = 255;             //'yellow';
                    vertex[1] = 255;
                    vertex[2] = 0;
                }
            }
        }
        if (G < 128){
            if (G <= B){
                if (G <= R){
                    vertex[0] = 255;         //'magenta';
                    vertex[1] = 0;
                    vertex[2] = 255;
                }
            }
        }
        if (R < 128){
            if (R <= B){
                if (R <= G){
                    vertex[0] = 0;                //'cyan';
                    vertex[1] = 255;
                    vertex[2] = 255;
                }
            }
        }
    }


    // No.2 for MYGC
    if (mbvq == 2){
        vertex[0] = 255;                 //'magenta';
        vertex[1] = 0;
        vertex[2] = 255;
        if (G >= B){
            if (R >= B){
                if (R >= 128) {
                    vertex[0] = 255;              //'yellow';
                    vertex[1] = 255;
                    vertex[2] = 0;
                }
                else{
                    vertex[0] = 0;                  //'green';
                    vertex[1] = 255;
                    vertex[2] = 0;
                }
            }
        }
        if (G >= R){
            if (B >= R){
                if (B >= 128) {
                    vertex[0] = 0;                          //'cyan';
                    vertex[1] = 255;
                    vertex[2] = 255;
                }
                else{
                    vertex[0] = 0;                              //'green';
                    vertex[1] = 255;
                    vertex[2] = 0;
                }
            }
        }
    }


    // No.3 for RGMY
    if (mbvq == 3){
        if (B > 128){
            if (R > 128){
                if (B >= G) {
                    vertex[0] = 255;                  //'magenta';
                    vertex[1] = 0;
                    vertex[2] = 255;
                }
                else {
                    vertex[0] = 255;                      //'yellow';
                    vertex[1] = 255;
                    vertex[2] = 0;
                }
            }
            else{
                if (G > B + R) {
                    vertex[0] = 0;                        //'green';
                    vertex[1] = 255;
                    vertex[2] = 0;
                }
                else {
                    vertex[0] = 255;                         //'magenta';
                    vertex[1] = 0;
                    vertex[2] = 255;
                }
            }
        }
        else{
            if (R >= 128){
                if (G >= 128) {
                    vertex[0] = 255;                             //'yellow';
                    vertex[1] = 255;
                    vertex[2] = 0;
                }
                else {
                    vertex[0] = 255;                                //'red';
                    vertex[1] = 0;
                    vertex[2] = 0;
                }
            }
            else{
                if (R >= G) {
                    vertex[0] = 255;                                  //'red';
                    vertex[1] = 0;
                    vertex[2] = 0;
                }
                else{
                    vertex[0] = 0;                                 //'green';
                    vertex[1] = 255;
                    vertex[2] = 0;
                }
            }
        }
    }


    // No.4 for KRGB
    if (mbvq == 4) {
        vertex[0] = 0;                                      //'black';
        vertex[1] = 0;
        vertex[2] = 0;
        if (B > 128) {
            if (B >= R) {
                if (B >= G) {
                    vertex[0] = 0;                              //'blue';
                    vertex[1] = 0;
                    vertex[2] = 255;
                }
            }
        }
        if (G > 128) {
            if (G >= B) {
                if (G >= R) {
                    vertex[0] = 0;                          //'green';
                    vertex[1] = 255;
                    vertex[2] = 0;
                }
            }
        }
        if (R > 128) {
            if (R >= B) {
                if (R >= G) {
                    vertex[0] = 255;                              //'red';
                    vertex[1] = 0;
                    vertex[2] = 0;
                }
            }
        }
    }



    // No.5 for RGBM
    if (mbvq == 5){
        vertex[0] = 0;                                       //'green';
        vertex[1] = 255;
        vertex[2] = 0;
        if (R > G){
            if (R >= B){
                if (B < 128){
                    vertex[0] = 255;                             //'red';
                    vertex[1] = 0;
                    vertex[2] = 0;
                }
                else{
                    vertex[0] = 255;                              //'magenta';
                    vertex[1] = 0;
                    vertex[2] = 255;
                }
            }
        }
        if (B > G){
            if (B >= R){
                if (R < 128){
                    vertex[0] = 0;                              //'blue';
                    vertex[1] = 0;
                    vertex[2] = 255;
                }
                else{
                    vertex[0] = 255;                                   //'magenta';
                    vertex[1] = 0;
                    vertex[2] = 255;
                }
            }
        }
    }


    // No.6 for CMGB
    if (mbvq == 6){
        if (B > 128){
            if ( R > 128){
                if (G >= R) {
                    vertex[0] = 0;                         //'cyan';
                    vertex[1] = 255;
                    vertex[2] = 255;
                }
                else {
                    vertex[0] = 255;                             //'magenta';
                    vertex[1] = 0;
                    vertex[2] = 255;
                }
            }
            else{
                if (G > 128) {
                    vertex[0] = 0;                                //'cyan';
                    vertex[1] = 255;
                    vertex[2] = 255;
                }
                else {
                    vertex[0] = 0;                                 //'blue';
                    vertex[1] = 0;
                    vertex[2] = 255;
                }
            }
        }
        else{
            if ( R > 128) {
                if (R - G + B >= 128) {
                    vertex[0] = 255;                                   //'magenta';
                    vertex[1] = 0;
                    vertex[2] = 255;
                } else {
                    vertex[0] = 0;                                     //'green';
                    vertex[1] = 255;
                    vertex[2] = 0;
                }
            }
            else{
                if (G >= B) {
                    vertex[0] = 0;                                     //'green';
                    vertex[1] = 255;
                    vertex[2] = 0;
                }
                else{
                    vertex[0] = 0;                                      //'blue';
                    vertex[1] = 0;
                    vertex[2] = 255;
                }
            }
        }
    }

}




int main(int argc, char *argv[]) {
    // Define file pointer and variables
    FILE *file;
    int BytesPerPixel;
    int width = 500;
    int height = 375;

    // Check for proper syntax
    if (argc < 3) {
        cout << "Syntax Error - Incorrect Parameter Usage:" << endl;
        cout << "program_name input_image.raw output_image.raw [BytesPerPixel = 1] [Size = 256]" << endl;
        return 0;
    }

    // Check if image is grayscale or color
    if (argc < 4) {
        BytesPerPixel = 1; // default is grey image
    } else {
        BytesPerPixel = atoi(argv[3]);
        // Check if size is specified
        if (argc >= 5) {
            width = atoi(argv[4]);
            height = atoi(argv[5]);
        }
    }

    // Allocate image data array
    unsigned char Imagedata[height][width][BytesPerPixel];

    // Read image (filename specified by first argument) into image data matrix
    if (!(file = fopen(argv[1], "rb"))) {
        cout << "Cannot open file: " << argv[1] << endl;
        exit(1);
    }
    fread(Imagedata, sizeof(unsigned char), width * height * BytesPerPixel, file);
    fclose(file);

    ///////////////////////// INSERT YOUR PROCESSING CODE HERE /////////////////////////
//    unsigned char newImagedata[height+2][width+2][BytesPerPixel];
    unsigned char outImagedata[height][width][BytesPerPixel];

    // Allocating dynamic memory
    float ***newImagedata = new float** [height+2];
    for (int i = 0; i < height+2; i++)
    {
        newImagedata[i] = new float*[width+2];

        for (int j = 0; j < width+2; j++)
            newImagedata[i][j] = new float[BytesPerPixel];
    }





    // Extending boundaries by 1 on each side

    for (int x=0; x<height; x++){
        for (int y=0; y<width; y++){
            newImagedata[x+1][y+1][0] = Imagedata[x][y][0];
            newImagedata[x+1][y+1][1] = Imagedata[x][y][1];
            newImagedata[x+1][y+1][2] = Imagedata[x][y][2];
        }
    }

    // Extending rows
    for (int x=0; x<width; x++) {
        for(int i=0; i<3; i++) {
            newImagedata[0][x][i] = Imagedata[1][x][i];
            newImagedata[height + 1][x][i] = Imagedata[height - 2][x][i];

        }
    }

    // Extending columns
    for (int x=0; x<height+2; x++) {
        for (int i=0; i<3; i++) {
            newImagedata[x][0][i] = newImagedata[x][1][i];
            newImagedata[x][width + 1][i] = newImagedata[x][width - 2][i];
        }
    }



    int region;
    for (int i = 1; i<height+1; i++){
        if (i%2!=0) {
            for (int j = 1; j < width+1; j++) {
                region = find_MBVQ(Imagedata[i-1][j-1][0], Imagedata[i-1][j-1][1], Imagedata[i-1][j-1][2]);
                getNearestVertex(region, newImagedata[i][j][0], newImagedata[i][j][1], newImagedata[i][j][2]);
                for (int k=0; k<3; k++) {
                    outImagedata[i-1][j-1][k] = vertex[k];
                    float error = (newImagedata[i][j][k] - vertex[k]);
                    newImagedata[i][j + 1][k] += ((7 / 16.0) * error);
                    newImagedata[i + 1][j - 1][k] += ((3 / 16.0) * error);
                    newImagedata[i + 1][j][k] += ((5 / 16.0) * error);
                    newImagedata[i + 1][j + 1][k] += ((1 / 16.0) * error);
                }
            }
        }
        else{
            for (int j = width; j >= 1; j--) {
                region = find_MBVQ(Imagedata[i-1][j-1][0], Imagedata[i-1][j-1][1], Imagedata[i-1][j-1][2]);
                getNearestVertex(region, newImagedata[i][j][0], newImagedata[i][j][1], newImagedata[i][j][2]);
                for (int k=0; k<3; k++) {
                    outImagedata[i-1][j-1][k] = vertex[k];
                    float error = (newImagedata[i][j][k] - vertex[k]);
                    newImagedata[i][j - 1][k] += ((7 / 16.0) * error);
                    newImagedata[i + 1][j - 1][k] += ((1 / 16.0) * error);
                    newImagedata[i + 1][j][k] += ((5 / 16.0) * error);
                    newImagedata[i + 1][j + 1][k] += ((3 / 16.0) * error);
                }

            }

        }
    }
    // Deallocating memory
    for(int i = 0; i < height+2; ++i) {
        for(int j = 0; j < width+2; ++j) {
            delete[] newImagedata[i][j];
        }
        delete[] newImagedata[i];
    }

    delete[] newImagedata;

    // Write image data (filename specified by second argument) from image data matrix

    if (!(file=fopen(argv[2],"wb"))) {
        cout << "Cannot open file: " << argv[2] << endl;
        exit(1);
    }
    fwrite(outImagedata, sizeof(unsigned char), width*height*BytesPerPixel, file);
    fclose(file);

    return 0;
}
