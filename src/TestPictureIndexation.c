#include<stdio.h>
#include<stdlib.h>
#include<math.h>
#include "PictureIndexation.h"

int main(void) {
//  int i, j, T[8]={0};
//  int L = 10, H = 10, P = 8;
//  int*** ImageQuantifie = (int***)malloc(L*sizeof((int**)malloc(H*sizeof((int*)malloc(P*sizeof(int))))));
//  int** Image = (int**)malloc(H*sizeof((int*)malloc(H*sizeof(int))));

//  for(i = 0; i<L; i++){
//    for(j = 0; j<H; i++){
//      *(*(Image+i*sizeof(int*))+j*sizeof(int)) = i+j;
//    }
//  }
    FILE * Image;
    ImageBuilder(10,15);
    Image = fopen("IMAGE.txt", "r");
    if(Image != NULL) {

//  nBitQuantificator(8,65);
        Quantification(Image,8,10,15);
        fclose(Image);
    } else printf("Desole probleme d'ouverture niveau 1...\n");
//  for(i = 0; i<10; i++){
//    for(j = 0; j<10; i++){
//      printf("La quantification des pixels (%d,%d) : %d, %d, %d, %d\n", i,j, ImageQuantifie[i][j][0],ImageQuantifie[i][j][1],ImageQuantifie[i][j][2],ImageQuantifie[i][j][3]);
//    }
//  }

    return 0;

}