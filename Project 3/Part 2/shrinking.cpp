#include <stdio.h>
#include <iostream>
#include <stdlib.h>
#include <fstream>

using namespace std;

//int bond_num(int arr[8]) {
//    int four=0;
//    int eight=0;
//    int bond_number;
//    for (int i=0; i<8; i=i+2){
//        if (i%2==0 && arr[i]==1){
//            four+=1;
//        }
//        else{
//            eight+=1;
//        }
//    }
//    bond_number = four + eight;
//    return bond_number;
//}

//int match(int S[][9], int arr[8]){
//    int count;
//    for (int i=0; i<4; i++){
//        for (int j=0; j<8; j++){
//            if (S[i][j]==arr[j]){
//                count+=1;
//            }
//        }
//
//    }
//    return count;
//}



int S[][9] = {{255,0,255,0,0,0,0,0,0},
              {255,0,0,0,255,0,0,0,0},
              {255,0,0,0,0,0,255,0,0},
              {255,0,0,0,0,0,0,0,255},
              {255,255,0,0,0,0,0,0,0},
              {255,0,0,255,0,0,0,0,0},
              {255,0,0,0,0,255,0,0,0},
              {255,0,0,0,0,0,0,255,0},
              {255,255,255,0,0,0,0,0,0},
              {255,0,255,255,0,0,0,0,0},
              {255,0,0,255,255,0,0,0,0},
              {255,0,0,0,255,255,0,0,0},
              {255,0,0,0,0,255,255,0,0},
              {255,0,0,0,0,0,255,255,0},
              {255,0,0,0,0,0,0,255,255},
              {255,255,0,0,0,0,0,0,255},
              {255,255,255,0,0,0,0,0,255},
              {255,0,255,255,255,0,0,0,0},
              {255,0,0,0,255,255,255,0,0},
              {255,0,0,0,0,0,255,255,255},
              {255,255,0,255,255,0,0,0,0},
              {255,255,0,255,0,0,0,0,255},
              {255,0,255,255,0,255,0,0,0},
              {255,255,255,0,0,0,0,255,0},
              {255,255,255,255,0,0,0,0,0},
              {255,0,0,255,255,255,0,0,0},
              {255,0,0,0,0,255,255,255,0},
              {255,255,0,0,0,0,0,255,255},
              {255,255,0,255,255,0,0,0,255},
              {255,0,255,255,0,255,255,0,0},
              {255,255,255,255,255,0,0,0,0},
              {255,255,255,255,0,0,0,0,255},
              {255,0,255,255,255,255,0,0,0},
              {255,0,0,255,255,255,255,0,0},
              {255,0,0,0,255,255,255,255,0},
              {255,0,0,0,0,255,255,255,255},
              {255,255,0,0,0,0,255,255,255},
              {255,255,255,0,0,0,0,255,255},
              {255,255,255,255,255,0,0,0,255},
              {255,0,255,255,255,255,255,0,0},
              {255,0,0,0,255,255,255,255,255},
              {255,255,255,0,0,0,255,255,255},
              {255,255,255,255,0,0,0,255,255},
              {255,255,255,255,255,255,0,0,0},
              {255,0,0,255,255,255,255,255,0},
              {255,255,0,0,0,255,255,255,255},
              {255,255,255,255,255,0,0,255,255},
              {255,255,255,255,0,0,255,255,255},
              {255,255,255,255,255,255,255,0,0},
              {255,255,255,255,255,255,0,0,255},
              {255,0,255,255,255,255,255,255,0},
              {255,0,0,255,255,255,255,255,255},
              {255,255,0,0,255,255,255,255,255},
              {255,255,255,0,0,255,255,255,255},
              {255,255,255,255,255,0,255,255,255},
              {255,255,255,255,255,255,255,0,255},
              {255,0,255,255,255,255,255,255,255},
              {255,255,255,0,255,255,255,255,255}};



int U[][9] = {{0, 0, 1, 0, 1, 0, 0, 0, 0},
              {1, 0, 0, 0, 1, 0, 0, 0, 0},
              {0, 0, 0, 0, 1, 0, 0, 1, 0},
              {0, 0, 0, 0, 1, 1, 0, 0, 0},
              {0, 0, 1, 0, 1, 1, 0, 0, 0},
              {0, 1, 1, 0, 1, 0, 0, 0, 0},
              {1, 1, 0, 0, 1, 0, 0, 0, 0},
              {1, 0, 0, 1, 1, 0, 0, 0, 0},
              {0, 0, 0, 1, 1, 0, 0, 0, 0},
              {0, 0, 0, 0, 1, 0, 1, 1, 0},
              {0, 0, 0, 0, 1, 0, 0, 1, 1},
              {0, 0, 0, 0, 1, 1, 0, 0, 1},
              {0, 1, 1, 1, 1, 0, 0, 0, 0},
              {1, 1, 0, 0, 1, 1, 0, 0, 0},
              {0, 1, 0, 0, 1, 1, 0, 0, 1},
              {0, 0, 1, 0, 1, 1, 0, 1, 0},
              {0, 0, 1, 0, 1, 1, 1, 0, 0},
              {1, 1, 0, 0, 1, 0, 0, 0, 1},
              {0, 0, 1, 0, 1, 0, 1, 1, 0},
              {1, 0, 0, 0, 1, 1, 0, 0, 1},
              {0, 1, 1, 0, 1, 0, 1, 0, 0},
              {1, 0, 0, 1, 1, 0, 0, 0, 1},
              {0, 0, 1, 1, 1, 0, 1, 0, 0},
              {1, 0, 0, 0, 1, 0, 0, 1, 1},
              {0, 1, 1, 0, 1, 1, 1, 0, 0},
              {1, 1, 0, 1, 1, 0, 0, 0, 1},
              {0, 0, 1, 1, 1, 0, 1, 1, 0},
              {1, 0, 0, 0, 1, 1, 0, 1, 1},
              {0, 1, 0, 1, 1, 1, 0, 0, 0},
              {0, 1, 0, 1, 1, 1, 0, 0, 0},
              {0, 0, 0, 1, 1, 1, 0, 1, 0},
              {0, 0, 0, 1, 1, 1, 0, 1, 0},
              {0, 1, 0, 1, 1, 0, 0, 1, 0},
              {0, 1, 0, 1, 1, 0, 0, 1, 0},
              {0, 1, 0, 0, 1, 1, 0, 1, 0},
              {0, 1, 0, 0, 1, 1, 0, 1, 0},
              {0, 1, 0, 0, 1, 1, 1, 0, 0},
              {0, 1, 0, 1, 1, 0, 0, 0, 1},
              {0, 0, 1, 1, 1, 0, 0, 1, 0},
              {1, 0, 0, 0, 1, 1, 0, 1, 0},
              {1, 1, 0, 1, 1, 0, 0, 0, 0},
              {1, 1, 0, 1, 1, 0, 0, 0, 1},
              {1, 1, 0, 1, 1, 0, 0, 1, 0},
              {1, 1, 0, 1, 1, 0, 0, 1, 1},
              {1, 1, 0, 1, 1, 0, 1, 0, 0},
              {1, 1, 0, 1, 1, 0, 1, 0, 1},
              {1, 1, 0, 1, 1, 0, 1, 1, 0},
              {1, 1, 0, 1, 1, 0, 1, 1, 1},
              {0, 1, 0, 1, 1, 1, 1, 0, 0},
              {0, 1, 0, 1, 1, 1, 0, 0, 1},
              {0, 0, 0, 1, 1, 1, 0, 1, 1},
              {0, 0, 0, 1, 1, 1, 1, 1, 0},
              {0, 1, 1, 1, 1, 0, 0, 1, 0},
              {0, 1, 0, 1, 1, 0, 0, 1, 1},
              {0, 1, 0, 0, 1, 1, 0, 1, 1},
              {0, 1, 1, 0, 1, 1, 0, 1, 0},
              {0, 1, 0, 0, 1, 1, 1, 0, 1},
              {0, 1, 0, 1, 1, 0, 1, 0, 1},
              {0, 0, 1, 1, 1, 0, 0, 1, 1},
              {1, 0, 0, 0, 1, 1, 1, 1, 0},
              {1, 1, 0, 1, 1, 1, 0, 0, 0},
              {1, 1, 0, 1, 1, 1, 0, 0, 1},
              {1, 1, 0, 1, 1, 1, 0, 1, 0},
              {1, 1, 0, 1, 1, 1, 0, 1, 1},
              {1, 1, 0, 1, 1, 1, 1, 0, 0},
              {1, 1, 0, 1, 1, 1, 1, 0, 1},
              {1, 1, 0, 1, 1, 1, 1, 1, 0},
              {1, 1, 0, 1, 1, 1, 1, 1, 1},
              {1, 1, 0, 1, 1, 1, 0, 0, 0},
              {0, 1, 1, 1, 1, 1, 0, 0, 0},
              {0, 0, 1, 1, 1, 1, 0, 1, 0},
              {1, 0, 0, 1, 1, 1, 0, 1, 0},
              {1, 1, 0, 1, 1, 0, 0, 1, 0},
              {0, 1, 0, 1, 1, 0, 1, 1, 0},
              {0, 1, 0, 0, 1, 1, 1, 1, 0},
              {1, 1, 0, 0, 1, 1, 0, 1, 0},
              {1, 1, 0, 0, 1, 1, 1, 0, 0},
              {0, 1, 1, 1, 1, 0, 0, 0, 1},
              {1, 0, 1, 1, 1, 0, 0, 1, 0},
              {1, 0, 1, 0, 1, 1, 0, 1, 0},
              {1, 1, 1, 1, 1, 0, 0, 0, 0},
              {1, 1, 1, 1, 1, 0, 0, 0, 1},
              {1, 1, 1, 1, 1, 0, 0, 1, 0},
              {1, 1, 1, 1, 1, 0, 0, 1, 1},
              {1, 1, 1, 1, 1, 0, 1, 0, 0},
              {1, 1, 1, 1, 1, 0, 1, 0, 1},
              {1, 1, 1, 1, 1, 0, 1, 1, 0},
              {1, 1, 1, 1, 1, 0, 1, 1, 1},
              {1, 1, 0, 1, 1, 1, 1, 0, 0},
              {0, 1, 1, 1, 1, 1, 0, 0, 1},
              {0, 0, 1, 1, 1, 1, 0, 1, 1},
              {1, 0, 0, 1, 1, 1, 1, 1, 0},
              {1, 1, 1, 1, 1, 0, 0, 1, 0},
              {0, 1, 0, 1, 1, 0, 1, 1, 1},
              {0, 1, 0, 0, 1, 1, 1, 1, 1},
              {1, 1, 1, 0, 1, 1, 0, 1, 0},
              {1, 1, 0, 0, 1, 1, 1, 0, 1},
              {0, 1, 1, 1, 1, 0, 1, 0, 1},
              {1, 0, 1, 1, 1, 0, 0, 1, 1},
              {1, 0, 1, 0, 1, 1, 1, 1, 0},
              {1, 1, 1, 1, 1, 1, 0, 0, 0},
              {1, 1, 1, 1, 1, 1, 0, 0, 1},
              {1, 1, 1, 1, 1, 1, 0, 1, 0},
              {1, 1, 1, 1, 1, 1, 0, 1, 1},
              {1, 1, 1, 1, 1, 1, 1, 0, 0},
              {1, 1, 1, 1, 1, 1, 1, 0, 1},
              {1, 1, 1, 1, 1, 1, 1, 1, 0},
              {1, 1, 1, 1, 1, 1, 1, 1, 1},
              {1, 0, 1, 0, 1, 0, 0, 0, 1},
              {1, 0, 1, 0, 1, 0, 1, 0, 0},
              {1, 0, 0, 0, 1, 0, 1, 0, 1},
              {0, 0, 1, 0, 1, 0, 1, 0, 1},
              {1, 0, 1, 0, 1, 1, 0, 0, 1},
              {1, 0, 1, 0, 1, 0, 1, 1, 0},
              {1, 0, 0, 0, 1, 0, 1, 1, 1},
              {0, 0, 1, 0, 1, 0, 1, 1, 1},
              {1, 0, 1, 1, 1, 0, 0, 0, 1},
              {1, 0, 1, 1, 1, 0, 1, 0, 0},
              {1, 0, 0, 0, 1, 1, 1, 0, 1},
              {0, 0, 1, 0, 1, 1, 1, 0, 1},
              {1, 0, 1, 1, 1, 1, 0, 0, 1},
              {1, 0, 1, 1, 1, 0, 1, 1, 0},
              {1, 0, 0, 0, 1, 1, 1, 1, 1},
              {0, 0, 1, 0, 1, 1, 1, 1, 1},
              {1, 1, 1, 0, 1, 0, 0, 0, 1},
              {1, 1, 1, 0, 1, 0, 1, 0, 0},
              {1, 0, 0, 1, 1, 0, 1, 0, 1},
              {0, 1, 1, 0, 1, 0, 1, 0, 1},
              {1, 1, 1, 0, 1, 1, 0, 0, 1},
              {1, 1, 1, 0, 1, 0, 1, 1, 0},
              {1, 0, 0, 1, 1, 0, 1, 1, 1},
              {0, 1, 1, 0, 1, 0, 1, 1, 1},
              {1, 1, 1, 1, 1, 0, 0, 0, 1},
              {1, 1, 1, 1, 1, 0, 1, 0, 0},
              {1, 0, 0, 1, 1, 1, 1, 0, 1},
              {0, 1, 1, 0, 1, 1, 1, 0, 1},
              {1, 1, 1, 1, 1, 1, 0, 0, 1},
              {1, 1, 1, 1, 1, 0, 1, 1, 0},
              {1, 0, 0, 1, 1, 1, 1, 1, 1},
              {0, 1, 1, 0, 1, 1, 1, 1, 1},
              {1, 0, 1, 0, 1, 0, 0, 1, 0},
              {1, 0, 0, 0, 1, 1, 1, 0, 0},
              {0, 1, 0, 0, 1, 0, 1, 0, 1},
              {0, 0, 1, 1, 1, 0, 0, 0, 1},
              {1, 0, 1, 0, 1, 1, 0, 1, 0},
              {1, 0, 0, 0, 1, 1, 1, 1, 0},
              {0, 1, 0, 0, 1, 0, 1, 1, 1},
              {0, 0, 1, 1, 1, 0, 0, 1, 1},
              {1, 0, 1, 1, 1, 0, 0, 1, 0},
              {1, 0, 0, 1, 1, 1, 1, 0, 0},
              {0, 1, 0, 0, 1, 1, 1, 0, 1},
              {0, 0, 1, 1, 1, 1, 0, 0, 1},
              {1, 0, 1, 1, 1, 1, 0, 1, 0},
              {1, 0, 0, 1, 1, 1, 1, 1, 0},
              {0, 1, 0, 0, 1, 1, 1, 1, 1},
              {0, 0, 1, 1, 1, 1, 0, 1, 1},
              {1, 1, 1, 0, 1, 0, 0, 1, 0},
              {1, 1, 0, 0, 1, 1, 1, 0, 0},
              {0, 1, 0, 1, 1, 0, 1, 0, 1},
              {0, 1, 1, 1, 1, 0, 0, 0, 1},
              {1, 1, 1, 0, 1, 1, 0, 1, 0},
              {1, 1, 0, 0, 1, 1, 1, 1, 0},
              {0, 1, 0, 1, 1, 0, 1, 1, 1},
              {0, 1, 1, 1, 1, 0, 0, 1, 1},
              {1, 1, 1, 1, 1, 0, 0, 1, 0},
              {1, 1, 0, 1, 1, 1, 1, 0, 0},
              {0, 1, 0, 1, 1, 1, 1, 0, 1},
              {0, 1, 1, 1, 1, 1, 0, 0, 1},
              {1, 1, 1, 1, 1, 1, 0, 1, 0},
              {1, 1, 0, 1, 1, 1, 1, 1, 0},
              {0, 1, 0, 1, 1, 1, 1, 1, 1},
              {0, 1, 1, 1, 1, 1, 0, 1, 1},
              {1, 0, 1, 0, 1, 0, 0, 1, 1},
              {1, 0, 1, 0, 1, 1, 1, 0, 0},
              {1, 1, 0, 0, 1, 0, 1, 0, 1},
              {0, 0, 1, 1, 1, 0, 1, 0, 1},
              {1, 0, 1, 0, 1, 1, 0, 1, 1},
              {1, 0, 1, 0, 1, 1, 1, 1, 0},
              {1, 1, 0, 0, 1, 0, 1, 1, 1},
              {0, 0, 1, 1, 1, 0, 1, 1, 1},
              {1, 0, 1, 1, 1, 0, 0, 1, 1},
              {1, 0, 1, 1, 1, 1, 1, 0, 0},
              {1, 1, 0, 0, 1, 1, 1, 0, 1},
              {0, 0, 1, 1, 1, 1, 1, 0, 1},
              {1, 0, 1, 1, 1, 1, 0, 1, 1},
              {1, 0, 1, 1, 1, 1, 1, 1, 0},
              {1, 1, 0, 0, 1, 1, 1, 1, 1},
              {0, 0, 1, 1, 1, 1, 1, 1, 1},
              {1, 1, 1, 0, 1, 0, 0, 1, 1},
              {1, 1, 1, 0, 1, 1, 1, 0, 0},
              {1, 1, 0, 1, 1, 0, 1, 0, 1},
              {0, 1, 1, 1, 1, 0, 1, 0, 1},
              {1, 1, 1, 0, 1, 1, 0, 1, 1},
              {1, 1, 1, 0, 1, 1, 1, 1, 0},
              {1, 1, 0, 1, 1, 0, 1, 1, 1},
              {0, 1, 1, 1, 1, 0, 1, 1, 1},
              {1, 1, 1, 1, 1, 0, 0, 1, 1},
              {1, 1, 1, 1, 1, 1, 1, 0, 0},
              {1, 1, 0, 1, 1, 1, 1, 0, 1},
              {0, 1, 1, 1, 1, 1, 1, 0, 1},
              {1, 1, 1, 1, 1, 1, 0, 1, 1},
              {1, 1, 1, 1, 1, 1, 1, 1, 0},
              {1, 1, 0, 1, 1, 1, 1, 1, 1},
              {0, 1, 1, 1, 1, 1, 1, 1, 1},
              {1, 0, 1, 0, 1, 0, 1, 0, 0},
              {1, 0, 0, 0, 1, 0, 1, 0, 1},
              {0, 0, 1, 0, 1, 0, 1, 0, 1},
              {1, 0, 1, 0, 1, 0, 0, 0, 1},
              {1, 0, 1, 0, 1, 1, 1, 0, 0},
              {1, 0, 0, 0, 1, 0, 1, 1, 1},
              {0, 0, 1, 0, 1, 0, 1, 1, 1},
              {1, 0, 1, 0, 1, 0, 0, 1, 1},
              {1, 0, 1, 1, 1, 0, 1, 0, 0},
              {1, 0, 0, 1, 1, 0, 1, 0, 1},
              {0, 0, 1, 0, 1, 1, 1, 0, 1},
              {1, 0, 1, 0, 1, 1, 0, 0, 1},
              {1, 0, 1, 1, 1, 1, 1, 0, 0},
              {1, 0, 0, 1, 1, 0, 1, 1, 1},
              {0, 0, 1, 0, 1, 1, 1, 1, 1},
              {1, 0, 1, 0, 1, 1, 0, 1, 1},
              {1, 1, 1, 0, 1, 0, 1, 0, 0},
              {1, 1, 0, 0, 1, 0, 1, 0, 1},
              {0, 0, 1, 1, 1, 0, 1, 0, 1},
              {1, 1, 1, 0, 1, 0, 0, 0, 1},
              {1, 1, 1, 0, 1, 1, 1, 0, 0},
              {1, 1, 0, 0, 1, 0, 1, 1, 1},
              {0, 0, 1, 1, 1, 0, 1, 1, 1},
              {1, 1, 1, 0, 1, 0, 0, 1, 1},
              {1, 1, 1, 1, 1, 0, 1, 0, 0},
              {1, 1, 0, 1, 1, 0, 1, 0, 1},
              {0, 0, 1, 1, 1, 1, 1, 0, 1},
              {1, 1, 1, 0, 1, 1, 0, 0, 1},
              {1, 1, 1, 1, 1, 1, 1, 0, 0},
              {1, 1, 0, 1, 1, 0, 1, 1, 1},
              {0, 0, 1, 1, 1, 1, 1, 1, 1},
              {1, 1, 1, 0, 1, 1, 0, 1, 1},
              {1, 0, 1, 0, 1, 0, 1, 0, 1},
              {1, 0, 1, 0, 1, 0, 1, 0, 1},
              {1, 0, 1, 0, 1, 0, 1, 0, 1},
              {1, 0, 1, 0, 1, 0, 1, 0, 1},
              {1, 0, 1, 0, 1, 1, 1, 0, 1},
              {1, 0, 1, 0, 1, 0, 1, 1, 1},
              {1, 0, 1, 0, 1, 0, 1, 1, 1},
              {1, 0, 1, 0, 1, 0, 1, 1, 1},
              {1, 0, 1, 1, 1, 0, 1, 0, 1},
              {1, 0, 1, 1, 1, 0, 1, 0, 1},
              {1, 0, 1, 0, 1, 1, 1, 0, 1},
              {1, 0, 1, 0, 1, 1, 1, 0, 1},
              {1, 0, 1, 1, 1, 1, 1, 0, 1},
              {1, 0, 1, 1, 1, 0, 1, 1, 1},
              {1, 0, 1, 0, 1, 1, 1, 1, 1},
              {1, 0, 1, 0, 1, 1, 1, 1, 1},
              {1, 1, 1, 0, 1, 0, 1, 0, 1},
              {1, 1, 1, 0, 1, 0, 1, 0, 1},
              {1, 0, 1, 1, 1, 0, 1, 0, 1},
              {1, 1, 1, 0, 1, 0, 1, 0, 1},
              {1, 1, 1, 0, 1, 1, 1, 0, 1},
              {1, 1, 1, 0, 1, 0, 1, 1, 1},
              {1, 0, 1, 1, 1, 0, 1, 1, 1},
              {1, 1, 1, 0, 1, 0, 1, 1, 1},
              {1, 1, 1, 1, 1, 0, 1, 0, 1},
              {1, 1, 1, 1, 1, 0, 1, 0, 1},
              {1, 0, 1, 1, 1, 1, 1, 0, 1},
              {1, 1, 1, 0, 1, 1, 1, 0, 1},
              {1, 1, 1, 1, 1, 1, 1, 0, 1},
              {1, 1, 1, 1, 1, 0, 1, 1, 1},
              {1, 0, 1, 1, 1, 1, 1, 1, 1},
              {1, 1, 1, 0, 1, 1, 1, 1, 1},
              {1, 0, 1, 0, 1, 0, 1, 1, 0},
              {1, 0, 0, 0, 1, 1, 1, 0, 1},
              {0, 1, 1, 0, 1, 0, 1, 0, 1},
              {1, 0, 1, 1, 1, 0, 0, 0, 1},
              {1, 0, 1, 0, 1, 1, 1, 1, 0},
              {1, 0, 0, 0, 1, 1, 1, 1, 1},
              {0, 1, 1, 0, 1, 0, 1, 1, 1},
              {1, 0, 1, 1, 1, 0, 0, 1, 1},
              {1, 0, 1, 1, 1, 0, 1, 1, 0},
              {1, 0, 0, 1, 1, 1, 1, 0, 1},
              {0, 1, 1, 0, 1, 1, 1, 0, 1},
              {1, 0, 1, 1, 1, 1, 0, 0, 1},
              {1, 0, 1, 1, 1, 1, 1, 1, 0},
              {1, 0, 0, 1, 1, 1, 1, 1, 1},
              {0, 1, 1, 0, 1, 1, 1, 1, 1},
              {1, 0, 1, 1, 1, 1, 0, 1, 1},
              {1, 1, 1, 0, 1, 0, 1, 1, 0},
              {1, 1, 0, 0, 1, 1, 1, 0, 1},
              {0, 1, 1, 1, 1, 0, 1, 0, 1},
              {1, 1, 1, 1, 1, 0, 0, 0, 1},
              {1, 1, 1, 0, 1, 1, 1, 1, 0},
              {1, 1, 0, 0, 1, 1, 1, 1, 1},
              {0, 1, 1, 1, 1, 0, 1, 1, 1},
              {1, 1, 1, 1, 1, 0, 0, 1, 1},
              {1, 1, 1, 1, 1, 0, 1, 1, 0},
              {1, 1, 0, 1, 1, 1, 1, 0, 1},
              {0, 1, 1, 1, 1, 1, 1, 0, 1},
              {1, 1, 1, 1, 1, 1, 0, 0, 1},
              {1, 1, 1, 1, 1, 1, 1, 1, 0},
              {1, 1, 0, 1, 1, 1, 1, 1, 1},
              {0, 1, 1, 1, 1, 1, 1, 1, 1},
              {1, 1, 1, 1, 1, 1, 0, 1, 1},
              {1, 0, 1, 0, 1, 0, 1, 1, 1},
              {1, 0, 1, 0, 1, 1, 1, 0, 1},
              {1, 1, 1, 0, 1, 0, 1, 0, 1},
              {1, 0, 1, 1, 1, 0, 1, 0, 1},
              {1, 0, 1, 0, 1, 1, 1, 1, 1},
              {1, 0, 1, 0, 1, 1, 1, 1, 1},
              {1, 1, 1, 0, 1, 0, 1, 1, 1},
              {1, 0, 1, 1, 1, 0, 1, 1, 1},
              {1, 0, 1, 1, 1, 0, 1, 1, 1},
              {1, 0, 1, 1, 1, 1, 1, 0, 1},
              {1, 1, 1, 0, 1, 1, 1, 0, 1},
              {1, 0, 1, 1, 1, 1, 1, 0, 1},
              {1, 0, 1, 1, 1, 1, 1, 1, 1},
              {1, 0, 1, 1, 1, 1, 1, 1, 1},
              {1, 1, 1, 0, 1, 1, 1, 1, 1},
              {1, 0, 1, 1, 1, 1, 1, 1, 1},
              {1, 1, 1, 0, 1, 0, 1, 1, 1},
              {1, 1, 1, 0, 1, 1, 1, 0, 1},
              {1, 1, 1, 1, 1, 0, 1, 0, 1},
              {1, 1, 1, 1, 1, 0, 1, 0, 1},
              {1, 1, 1, 0, 1, 1, 1, 1, 1},
              {1, 1, 1, 0, 1, 1, 1, 1, 1},
              {1, 1, 1, 1, 1, 0, 1, 1, 1},
              {1, 1, 1, 1, 1, 0, 1, 1, 1},
              {1, 1, 1, 1, 1, 0, 1, 1, 1},
              {1, 1, 1, 1, 1, 1, 1, 0, 1},
              {1, 1, 1, 1, 1, 1, 1, 0, 1},
              {1, 1, 1, 1, 1, 1, 1, 0, 1},
              {1, 1, 1, 1, 1, 1, 1, 1, 1},
              {1, 1, 1, 1, 1, 1, 1, 1, 1},
              {1, 1, 1, 1, 1, 1, 1, 1, 1},
              {1, 1, 1, 1, 1, 1, 1, 1, 1}};





int main(int argc, char *argv[]) {
    // Define file pointer and variables
    FILE *file;
    int BytesPerPixel;
    int width = 375;
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
    unsigned char outImagedata[height][width][BytesPerPixel];

    // Read image (filename specified by first argument) into image data matrix
    if (!(file = fopen(argv[1], "rb"))) {
        cout << "Cannot open file: " << argv[1] << endl;
        exit(1);
    }
    fread(outImagedata, sizeof(unsigned char), width * height * BytesPerPixel, file);
    fclose(file);

    ///////////////////////// INSERT YOUR PROCESSING CODE HERE /////////////////////////
//    unsigned char outImagedata[height][width][BytesPerPixel];
    unsigned char extendedimage[height+2][width+2][BytesPerPixel];
    unsigned char new_Imagedata[height][width][BytesPerPixel];
    unsigned char M[height][width][BytesPerPixel];
    unsigned char M_extend[height][width][BytesPerPixel];
    unsigned char P[height][width][BytesPerPixel];

    for (int i =0; i<height; i++) {
        for (int j = 0; j < width; j++) {
            if (outImagedata[i][j][0] > 128) {
                outImagedata[i][j][0] = 255;
            } else {
                outImagedata[i][j][0] = 0;
            }
        }
    }

//    for (int i = 0; i < height; i++) {
//        for (int j = 0; j < width; j++) {
//            outImagedata[i][j][0] = Imagedata[i][j][0];
//
//        }
//    }

    int flag = 0;
    while(flag==0) {

//        cout<<"hi"<<endl;

        for (int i = 0; i < height; i++) {
            for (int j = 0; j < width; j++) {
                Imagedata[i][j][0] = outImagedata[i][j][0];

            }
        }


        // Extending image boundaries by 1 on each side
        for (int x = 0; x < height; x++) {
            for (int y = 0; y < width; y++) {
                extendedimage[x + 1][y + 1][0] = Imagedata[x][y][0];
            }
        }

        // Extending rows
        for (int x = 0; x < width; x++) {
            extendedimage[0][x][0] = Imagedata[1][x][0];
            extendedimage[height + 1][x][0] = Imagedata[height - 2][x][0];
        }
        // Extending columns
        for (int x = 0; x < height + 2; x++) {
            extendedimage[x][0][0] = extendedimage[x][2][0];
            extendedimage[x][width + 1][0] = extendedimage[x][width - 2][0];
        }

        int count;
        for (int i = 1; i < height + 1; i++) {
            for (int j = 1; j < width + 1; j++) {
                int arr[9] = {extendedimage[i][j][0], extendedimage[i][j + 1][0], extendedimage[i - 1][j + 1][0],
                              extendedimage[i - 1][j][0],
                              extendedimage[i - 1][j - 1][0],
                              extendedimage[i][j - 1][0], extendedimage[i + 1][j - 1][0],
                              extendedimage[i + 1][j][0],
                              extendedimage[i + 1][j + 1][0]};
//                    cout<<"enter"<<endl;
                for (int a=0; a<58; a++){
                    count = 0;
                    for (int b=0; b<9; b++){
                        if (S[a][b]!=arr[b]){
                            M[i - 1][j - 1][0] = 0;
                            count = 1;
//                                cout<<"enter"<<endl;
                            break;
                        }
                    }
                    if (count == 0) {
                        M[i - 1][j - 1][0] = 1;
//                        cout<<"enter"<<endl;
                        break;
//                        cout<<count<<endl;
                    }

                }
            }
        }


        //Extending M array
        for (int x = 0; x < height; x++) {
            for (int y = 0; y < width; y++) {
                M_extend[x + 1][y + 1][0] = M[x][y][0];
            }
        }

        // Extending rows
        for (int x = 0; x < width+2; x++) {
            M_extend[0][x][0] = 0;
            M_extend[height + 1][x][0] = 0;
        }
        // Extending columns
        for (int x = 0; x < height + 2; x++) {
            M_extend[x][0][0] = 0;
            M_extend[x][width + 1][0] = 0;
        }


        for (int i = 1; i < height + 1; i++) {
            for (int j = 1; j < width + 1; j++) {
                int arr[9] = {M_extend[i-1][j-1][0], M_extend[i-1][j][0], M_extend[i - 1][j + 1][0], M_extend[i][j-1][0],
                              M_extend[i][j][0],
                              M_extend[i][j + 1][0], M_extend[i + 1][j - 1][0], M_extend[i + 1][j][0],
                              M_extend[i + 1][j + 1][0]};
//                    cout<<"enter"<<endl;

                for (int a=0; a<332; a++){
                    count = 0;
                    for (int b=0; b<9; b++){
                        if (U[a][b]!=arr[b]){
                            P[i - 1][j - 1][0] = 0;
                            count = 1;
//                                cout<<"enter"<<endl;
                            break;
                        }
                    }
                    if (count==0){
                        P[i - 1][j - 1][0] = 1;
//                            cout<<"enter"<<endl;
                        break;
                    }
                }
            }
        }

        for (int i = 0; i < height; i++) {
            for (int j = 0; j < width; j++) {
                if (Imagedata[i][j][0] > 128) {
                    new_Imagedata[i][j][0] = 1;
                } else {
                    new_Imagedata[i][j][0] = 0;
                }
            }
        }

        for (int i = 0; i < height; i++) {
            for (int j = 0; j < width; j++) {
                outImagedata[i][j][0] = new_Imagedata[i][j][0] and ((not M[i][j][0]) or P[i][j][0]);
//                cout<<(int)outImagedata[i][j][0]<<endl;
            }
        }

        for (int i = 0; i < height; i++) {
            for (int j = 0; j < width; j++) {
                if (outImagedata[i][j][0]==0){
                    outImagedata[i][j][0] = 0;
                }
                else{
                    outImagedata[i][j][0] = 255;
                }
            }
        }

        int k=0;
        for (int i = 0; i < height; i++) {
            for (int j = 0; j < width; j++) {
                if (outImagedata[i][j][0] != Imagedata[i][j][0]) {
//                    cout<<"enter"<<endl;
                    k=1;
                    break;
                }
            }
            if (k==1){
                break;
            }
        }
        if (k==1){
            flag=0;
        }
        else{
            flag=1;
        }

    }

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
