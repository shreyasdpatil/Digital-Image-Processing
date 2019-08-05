Name: Shreyas Patil
USC Email: shreyasp@usc.edu
Date: 2/12/2019

#include <stdio.h>
#include <iostream>
#include <stdlib.h>
#include <math.h>
#include <cstdlib>

using namespace std;

int** dithering_matrix(int max, int** index_array){
    int **final_index_array;
    final_index_array = new int *[max];

    for(int a = 0 ; a < max ; a++ ){
        final_index_array[a] = new int[max];
    }

    // Initializng array values to 0
    if (max==2) {
        for (int m = 0; m < max; m++) {
            for (int n = 0; n < max; n++) {
                index_array[m][n] = 0;
            }
       }
    }

    for (int y=0; y<max/2; y++){
        for (int z=0; z<max/2; z++){
            final_index_array[y][z] = 4 * index_array[y][z] + 1;
            final_index_array[y][z+(max/2)] = 4 * index_array[y][z] + 2;
            final_index_array[y+(max/2)][z] = 4 * index_array[y][z] + 3;
            final_index_array[y+(max/2)][z+(max/2)] = 4 * index_array[y][z];
        }
    }

    // Deleting allocated memory
    for(int i = 0; i < max/2; i++) {
        delete [] index_array[i];
    }
    delete [] index_array;

    for (int y=0; y<max; y++){
        for (int z=0; z<max; z++){
            cout << final_index_array[y][z] <<endl;
        }
    }

    return final_index_array;

}

int main(int argc, char *argv[])

{
    // Define file pointer and variables
    FILE *file;
    int BytesPerPixel;
    int width = 600;
    int height = 400;

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
    unsigned char outImagedata[height][width][1];


    int** final_index_array;
    final_index_array = new int *[2];

    for(int a = 0 ; a < 2 ; a++ ){
        final_index_array[a] = new int[2];
    }

    for (int k=2; k<=32; k = k*2) {
        final_index_array = dithering_matrix(k, final_index_array);
    }


    float transformed_matrix[32][32];
    for (int m=0; m<32; m++){
        for (int n=0; n<32; n++){
            transformed_matrix[m][n] = ((final_index_array[m][n] + 0.5)/(32*32)) * 255;
        }
    }



    for (int i =0; i<height; i++){
        for (int j=0; j<width; j++) {
            if (Imagedata[i][j][0]<=transformed_matrix[i%32][j%32]){
                outImagedata[i][j][0] = 0;
            }
            else{
                outImagedata[i][j][0] = 255;
            }
        }

    }


    // Write image data (filename specified by second argument) from image data matrix

    if (!(file=fopen(argv[2],"wb"))) {
        cout << "Cannot open file: " << argv[2] << endl;
        exit(1);
    }
    fwrite(outImagedata, sizeof(unsigned char), height*width*BytesPerPixel, file);
    fclose(file);

    return 0;
}
