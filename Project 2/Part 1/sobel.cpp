Name: Shreyas Patil
USC Email: shreyasp@usc.edu
Date: 2/12/2019

#include <stdio.h>
#include <iostream>
#include <stdlib.h>
#include <math.h>
#include <algorithm>
#include <fstream>

using namespace std;
float gradient_x[321][481];
float gradient_y[321][481];
unsigned char gradient_normalize[321][481];

void normalization(float gradient[][481], int height, int width) {
    int max = gradient[0][0], min = gradient[0][0];
    for (int i = 0; i < height; i++) {
        for (int j = 0; j < width; j++) {
            if (gradient[i][j] > max) {
                max = gradient[i][j];
//                cout<< max << endl;
            }

            if (gradient[i][j] < min) {
                min = gradient[i][j];
//                cout<< min << endl;

            }
        }
    }
    for (int i = 0; i < height; i++) {
        for (int j = 0; j < width; j++) {
            gradient_normalize[i][j] = (gradient[i][j] - min)*255.0 / (max - min);
        }
    }
}

int main(int argc, char *argv[]) {
    // Define file pointer and variables
    FILE *file;
    int BytesPerPixel;
    int width = 481;
    int height = 321;

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
    unsigned char grayImagedata[height][width][1];
    unsigned char edgeImagedata[height + 2][width + 2][1];
    unsigned char outImagedata[height][width][1];


    // Converting color image to grayscale
    for (int i = 0; i < height; i++) {
        for (int j = 0; j < width; j++) {
            grayImagedata[i][j][0] = (int) (0.299 * Imagedata[i][j][0] + 0.587 * Imagedata[i][j][1] +
                                            0.114 * Imagedata[i][j][2]);
        }
    }

    // Extend image boundaries by 3 on each side
    // Extended image for 3x3 filter
    for (int x = 0; x < height; x++) {
        for (int y = 0; y < width; y++) {
            edgeImagedata[x + 1][y + 1][0] = grayImagedata[x][y][0];
        }
    }

    // Extending rows
    for (int x = 0; x < width; x++) {
        edgeImagedata[0][x][0] = grayImagedata[1][x][0];
        edgeImagedata[height + 1][x][0] = grayImagedata[height - 2][x][0];
    }
    // Extending columns
    for (int x = 0; x < height + 2; x++) {
        edgeImagedata[x][0][0] = edgeImagedata[x][2][0];
        edgeImagedata[x][width + 1][0] = edgeImagedata[x][width - 2][0];
    }


    for (int i = 1; i < height + 1; i++) {
        for (int j = 1; j < width + 1; j++) {
            gradient_x[i - 1][j - 1] = (-edgeImagedata[i - 1][j - 1][0] + edgeImagedata[i - 1][j + 1][0] +
                                        -2 * edgeImagedata[i][j - 1][0] + 2 * edgeImagedata[i][j + 1][0]
                                        - edgeImagedata[i + 1][j - 1][0] + edgeImagedata[i + 1][j + 1][0]);
            gradient_y[i - 1][j - 1] = (edgeImagedata[i - 1][j - 1][0] + 2 * edgeImagedata[i - 1][j][0] +
                                        edgeImagedata[i - 1][j + 1][0]
                                        - edgeImagedata[i + 1][j - 1][0] - 2 * edgeImagedata[i + 1][j][0] -
                                        edgeImagedata[i + 1][j + 1][0]);

            outImagedata[i - 1][j - 1][0] = (sqrt(pow(gradient_x[i - 1][j - 1], 2) + pow(gradient_y[i - 1][j - 1], 2)) /
                                             255.0 > 0.7) ? 0 : 255;
        }

    }


    // Gradient normalization
    normalization(gradient_x, height, width);
    FILE *file1;
    file1 = fopen("gradient_x.raw", "wb");
    fwrite(gradient_normalize, sizeof(unsigned char), height * width * 1, file1);
    fclose(file1);

    normalization(gradient_y, height, width);
    FILE *file2;
    file2 = fopen("gradient_y.raw", "wb");
    fwrite(gradient_normalize, sizeof(unsigned char), height * width * 1, file2);
    fclose(file2);



    // Write image data (filename specified by second argument) from image data matrix

    if (!(file = fopen(argv[2], "wb"))) {
        cout << "Cannot open file: " << argv[2] << endl;
        exit(1);
    }
    fwrite(outImagedata, sizeof(unsigned char), height * width * 1, file);
    fclose(file);

    // Writing gradient values to file
    return 0;
}
