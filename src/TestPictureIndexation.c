#include<stdio.h>
#include<stdlib.h>
#include<math.h>
#include<string.h>
#include "PictureIndexation.h"

int main(void) {
    blackandWhiteIndexation("./IMAGE_NOIR_ET_BLANC/");
    colorIndexation("./IMAGE_COULEUR/");
//     file1comparedTofile2(256,1,3);
//     printf("%d\n",researchPictures(256,1));
//   char chemin[100] = "./Descripteurs/";
//     descToFileName(4,fileName, 0);
//     printf("%s\n",fileName);
//   char baseDesc[50] = "BASE_DESCRIPTEUR_IMAGE.txt";
//   strcat(chemin,baseDesc);
//   printf("%s\n",chemin);
//     printf("%d\n",file1Tofile2comparison(256,chemin,3,2));
    return 0;
}