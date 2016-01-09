#include<stdio.h>
#include<stdlib.h>
#include<math.h>
#include<string.h>
#include "PictureIndexation.h"

int main(void) {
//     blackandWhiteIndexation("./IMAGE_NOIR_ET_BLANC/",1);
//     colorIndexation("./IMAGE_COULEUR/",5);
//
//
//     char chemin[100] = "./Descripteurs/";
//     char a[10] = "01.txt";char b[10] = "01.txt";
//     printf("%d\n",file1Tofile2comparison(64,chemin,a,b));
//
//
//     printf("%d:61.txt %d:52.txt\n",fileNameToDesc("./Descripteurs/","61.txt",0),fileNameToDesc("./Descripteurs/","52.txt",0));
//     printf("%d\n",file1comparedTofile2(256,chemin,3,2));
//
//
    char a[50] = "61.txt";
    char b[50];
    researchPictures(256,a,b);
    printf("%s\n",b);
//     printf("d0%db\n",researchPictures(64,"01.txt"));
//     descToFileName(researchPictures(64,"31.txt"),"./Descripteurs/",a,0);
//
//
//
//     char baseDesc[50] = "BASE_DESCRIPTEUR_IMAGE.txt";
//     strcat(chemin,baseDesc);
//     printf("%s\n",chemin);
//     fscanf(F,"%s.%s",a,b);


    return 0;
}