Name: Shreyas Patil
USC Email: shreyasp@usc.edu

#include <stdio.h>
#include <iostream>
#include <stdlib.h>
#include <math.h>

using namespace std;

double weight(int row, int column, unsigned char I[][282][1], int a, int h){
    double norm;
    double normal = 0.0;
    double final_value = 0.0;
    double new_pixel_value;
    for (int k=row-10; k<row+11; k++){
        for(int l=column-10; l<column+11; l++) {
            norm = 0.0;
            for (int i =-3; i<=3; i++) {
                for (int j=-3; j<=3; j++) {
                    norm += (1/(sqrt(2 * M_PI)*a))*exp((-(i*i) - (j*j))/(2 * (a * a)))*pow((I[row+i][column+j][0]-I[k+i][l+j][0]), 2);
                }
            }
            final_value += I[k][l][0]*exp(-norm/(h*h));
            normal += exp(-norm/(h*h));
        }
    }
    new_pixel_value = final_value/normal;
    return new_pixel_value;
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
    unsigned char extendedimage[282][282][1];

    // Extending image boundaries by 13 on each side
    for (int x=0; x<height; x++){
        for (int y=0; y<width; y++){
            extendedimage[x+13][y+13][0] = Imagedata[x][y][0];
        }
    }

    for (int x=0; x<width; x++) {
        for (int i = 0; i < 13; i++) {
            extendedimage[i][x + 13][0] = Imagedata[13 - i][x][0];
            extendedimage[height + (i + 13)][x + 13][0] = Imagedata[height - 2-i][x][0];
        }
    }

    for (int x=0; x<height+26; x++){
        for (int i = 0; i < 13; i++) {
            extendedimage[x][i][0] = extendedimage[x][26-i][0];
            extendedimage[x][width+(i+13)][0] = extendedimage[x][width+11-i][0];
        }
    }


    for(int i = 13; i<height+13; i++){
        for(int j=13; j<width+13 ; j++){
            denosimage[i-13][j-13][0] = (int)weight(i, j, extendedimage, 5, 15);
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
