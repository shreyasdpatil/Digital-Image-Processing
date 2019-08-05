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

    ///////////////////////// INSERT YOUR PROCESSING CODE HERE /////////////////////////

    unsigned char demosimage[height][width][3];
    unsigned char extendedimage[height+2][width+2][BytesPerPixel];
    for (int x=0; x<width; x++){
        extendedimage[0][x+1][BytesPerPixel-1] = Imagedata[1][x][BytesPerPixel-1];
        extendedimage[width][x+1][BytesPerPixel-1] = Imagedata[width-2][x][BytesPerPixel-1];
    }
    for (int x=0; x<height; x++){
        extendedimage[x+1][0][BytesPerPixel-1] = Imagedata[x][1][BytesPerPixel-1];
        extendedimage[x+1][height][BytesPerPixel-1] = Imagedata[x][height-2][BytesPerPixel-1];
    }
    for (int x=0; x<height; x++){
        for (int y=0; y<width; y++){
            extendedimage[x+1][y+1][BytesPerPixel-1] = Imagedata[x][y][BytesPerPixel-1];
        }
    }

    // Part 1 (a)
    for (int a=0; a<height; a++){
        for (int b=0; b<width; b++){
            if (a%2==0){
                if (b%2==0){
                    demosimage[a][b][0] = (extendedimage[a+1][b][BytesPerPixel-1] + extendedimage[a+1][b+2][BytesPerPixel-1])/2;
                    demosimage[a][b][1] = extendedimage[a+1][b+1][BytesPerPixel-1];
                    demosimage[a][b][2] = (extendedimage[a][b+1][BytesPerPixel-1] + extendedimage[a+2][b+1][BytesPerPixel-1])/2;
                }
                else{
                    demosimage[a][b][0] = extendedimage[a+1][b+1][BytesPerPixel-1];
                    demosimage[a][b][1] = (extendedimage[a+1][b][BytesPerPixel-1] + extendedimage[a][b+1][BytesPerPixel-1] + extendedimage[a+1][b+2][BytesPerPixel-1] +
                                           extendedimage[a+2][b+1][BytesPerPixel-1])/4;
                    demosimage[a][b][2] = (extendedimage[a][b][BytesPerPixel-1] + extendedimage[a][b+2][BytesPerPixel-1] + extendedimage[a+2][b][BytesPerPixel-1] +
                                           extendedimage[a+2][b+2][BytesPerPixel-1])/4;
                }
            }
            else{
                if (b%2==0){
                    demosimage[a][b][0] = (extendedimage[a][b][BytesPerPixel-1] + extendedimage[a][b+2][BytesPerPixel-1] + extendedimage[a+2][b][BytesPerPixel-1] +
                                           extendedimage[a+2][b+2][BytesPerPixel-1])/4;
                    demosimage[a][b][1] = (extendedimage[a+1][b][BytesPerPixel-1] + extendedimage[a][b+1][BytesPerPixel-1] + extendedimage[a+1][b+2][BytesPerPixel-1] +
                                           extendedimage[a+2][b+1][BytesPerPixel-1])/4;
                    demosimage[a][b][2] = extendedimage[a+1][b+1][BytesPerPixel-1];
                }
                else{
                    demosimage[a][b][0] = (extendedimage[a][b+1][BytesPerPixel-1] + extendedimage[a+2][b+1][BytesPerPixel-1])/2;
                    demosimage[a][b][1] = extendedimage[a+1][b+1][BytesPerPixel-1];
                    demosimage[a][b][2] = (extendedimage[a+1][b][BytesPerPixel-1] + extendedimage[a+1][b+2][BytesPerPixel-1])/2;
                }
            }

        }
    }

    // Write image data (filename specified by second argument) from image data matrix

    if (!(file=fopen(argv[2],"wb"))) {
        cout << "Cannot open file: " << argv[2] << endl;
        exit(1);
    }
    fwrite(demosimage, sizeof(unsigned char), width*height*3, file);
    fclose(file);

    return 0;
}
