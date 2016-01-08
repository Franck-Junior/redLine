#include<stdio.h>
#include<stdlib.h>
#include<math.h>
#include<string.h>
#include "PictureIndexation.h"

int main(void) {
    blackandWhiteIndexation("./IMAGE_NOIR_ET_BLANC/",1);
    colorIndexation("./IMAGE_COULEUR/",5);
//     file1comparedTofile2(256,1,3);
//     printf("%d\n",researchPictures(256,1));
//     char chemin[100] = "./Descripteurs/";
//     descToFileName(4,fileName, 0);
//     printf("%s\n",fileName);
//     char baseDesc[50] = "BASE_DESCRIPTEUR_IMAGE.txt";
//     strcat(chemin,baseDesc);
//     printf("%s\n",chemin);
//     printf("%d\n",file1Tofile2comparison(256,chemin,3,2));
//     fscanf(F,"%s.%s",a,b);
//     char a[50];
//     char b[50];
//     descToFileName(11,"./Descripteurs/",a,0);
//     printf("11:%s %d:42.txt\n",a,fileNameToDesc("./Descripteurs/","42.txt",0));


    return 0;
}