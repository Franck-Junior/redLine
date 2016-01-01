#include<stdio.h>
#include<stdlib.h>
#include<math.h>
#include "PictureIndexation.h"

// Whenever they are used, H and L will mean "hauteur" and "largeur"

// void Quantification (File* F, File* Quant, int n){
//   F fopen("sijdeiz","r");
//   Quant fopen("sijdsdeiz","w");
//   int tab[8];
//   while(!eof(F)){
//     fscanf(F,"%d",pixelLevel);
//     nBitQuantificator(2,pixelLevel,tab);
//     fprintf(Quant,"%d",tab);
//   }
//   fclose(F);
// }

void nBitQuantificator(FILE * FichierQuantif, int n, int pixelLevel) {
    int j;
    if(FichierQuantif != NULL) {
        pixelLevel = pixelLevel-(int)pow(2,7);
        for(j = 7; j > 7-n; j--) {
            if(pixelLevel >= 0)
                fprintf(FichierQuantif,"1");
            else {
                fprintf(FichierQuantif, "0");
                pixelLevel = pixelLevel+(int)pow(2,j);
            }
            pixelLevel = pixelLevel-(int)pow(2,j-1);

        }
    } else printf("Desole probleme d'ouverture niveau 2...\n");

}

void ImageBuilder(int H, int L) {
    FILE * Image;
    int i,j;
    Image = fopen("IMAGE.txt", "w+");
    if(Image != NULL) {
        for(i = 0; i < H; i++) {
            for(j = 0; j < L; j++) {
                fprintf(Image,"%d\t",2*i*j);
            }
            fprintf(Image,"\n");
        }
        fclose(Image);
    }
}

void Quantification(FILE* Image, int n, int H, int L) {
    int j,i,a;
    FILE * ImageQuantifie;
    ImageQuantifie = fopen("QUANTIFIED_IMAGE.txt", "w+");
    for(i = 0; i < H; i++) {
        for(j = 0; j < L; j++) {
            fscanf(Image,"%d ",&a);
            nBitQuantificator(ImageQuantifie,n,a);
            fprintf(ImageQuantifie," ");
        }
        fprintf(ImageQuantifie,"\t");
    }
    fclose(ImageQuantifie);

}

void histogramme(FILE* Image, int niv, int H, int L){ // calcule et affiche l'histogramme d'une image
  FILE* Histo;
  int i,j,a;
  Histo = fopen("IMAGE_HISTOGRAM.txt", "w+");
  int histo[256] = {0};
  for(i = 0; i<H; i++){
		for(j = 0; j<L; j++){
		  fscanf(Image,"%d ",&a);
		  histo[a]++;
		
		}
		
  }
  
  for(i = 0; i < niv; i++) fprintf(Histo,"%d ",histo[i]);
  fprintf(Histo,"\n");
  fclose(Histo);
}
