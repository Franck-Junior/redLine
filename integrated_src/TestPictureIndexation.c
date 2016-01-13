#include<stdio.h>
#include<stdlib.h>
#include<math.h>
#include<string.h>
#include "PictureIndexation.h"

int nbdesc = 0;

int main(void) {
//     blackandWhiteIndexation("./IMAGE_NOIR_ET_BLANC/",1);
//     colorIndexation("./IMAGE_COULEUR/",5);
    autoIndexation("./IMAGE_COULEUR/",5);
  char a[10] = "31.txt";char b[10];
  researchPictures(64,a,b);
  printf("%s\n",b);
//     
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
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
//     researchPictures(256,a,b);
//     printf("%s\n",b);
//     char a[50] = "61.jpg";
//     char b[50] = "txt";
//     int i;
//     
//     FILE* F = fopen("Test écriture en un point d'un fichiers","r+");
//     for(i = 0; i<3 ; i++){
//     fprintf(F,"%s est un %s : ",a,b);
//       fscanf(F," %s ",a);
//     }
//       fprintf(F,"fichier");
//     printf("%c\n",a[((int)strlen(a))-1]);
//    a[((int)strlen(a))-1] = 't';
//    a[((int)strlen(a))-2] = 'x';
//    a[((int)strlen(a))-3] = 't';
//    printf("%s\n",a);
//    fclose(F);
/*
 * Tu utiliseras pendant l'indexation lorsque tu prends les noms des fichiers jpg et textes une par une et consécutivement. 
 * Cela te permettra de comparer le nom de l'image au texte  suivant s'il correspondent pas et de passerr directement à la 
 * suite en signalant que l'un des fichiers n'a pas pu être indéxé
 */
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