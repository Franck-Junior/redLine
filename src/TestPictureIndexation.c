#include<stdio.h>
#include<stdlib.h>
#include<math.h>
#include "PictureIndexation.h"

int main(void) {
    FILE * Image;
    ImageBuilder(10,15);
    
    Image = fopen("IMAGE.txt", "r");
    if(Image != NULL) {
        Quantification(Image,8,10,15);
        fclose(Image);
    } else printf("Desole probleme d'ouverture niveau 1...\n");
    
    Image = fopen("IMAGE.txt", "r");
    if(Image != NULL) {
	histogramme(Image,256,10,15);
        fclose(Image);
    } else printf("Desole probleme d'ouverture niveau 1...\n");
    
    return 0;
}