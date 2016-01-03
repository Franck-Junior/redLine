#include<stdio.h>
#include<stdlib.h>
#include<math.h>
#include "PictureIndexation.h"

int main(void) {
    FILE * Image;
    int H,L,buffer,niv= 256;
    
    Image = fopen("./IMAGE_NOIR_ET_BLANC/51.txt", "r");
    if(Image != NULL) {
	fscanf(Image,"%d ",&H);
	fscanf(Image,"%d ",&L);
	fscanf(Image,"%d ",&buffer);
	histogramme(Image,256,H,L,51);
        fclose(Image);
    } else printf("Desole probleme d'ouverture niveau 1...\n");
    
    Image = fopen("./IMAGE_NOIR_ET_BLANC/52.txt", "r");
    if(Image != NULL) {
	fscanf(Image,"%d ",&H);
	fscanf(Image,"%d ",&L);
	fscanf(Image,"%d ",&buffer);
	histogramme(Image,256,H,L,52);
        fclose(Image);
    } else printf("Desole probleme d'ouverture niveau 1...\n");
    
    Image = fopen("./IMAGE_NOIR_ET_BLANC/61.txt", "r");
    if(Image != NULL) {
	fscanf(Image,"%d ",&H);
	fscanf(Image,"%d ",&L);
	fscanf(Image,"%d ",&buffer);
	histogramme(Image,256,H,L,61);
        fclose(Image);
    } else printf("Desole probleme d'ouverture niveau 1...\n");
    
    Image = fopen("./IMAGE_NOIR_ET_BLANC/62.txt", "r");
    if(Image != NULL) {
	fscanf(Image,"%d ",&H);
	fscanf(Image,"%d ",&L);
	fscanf(Image,"%d ",&buffer);
	histogramme(Image,256,H,L,62);
        fclose(Image);
    } else printf("Desole probleme d'ouverture niveau 1...\n");
        
    file1comparedfile2(niv,52,62);
    
    return 0;
}