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

void histogramme(FILE* Image, int niv, int H, int L, int id) { // calcule et affiche l'histogramme d'une image
    FILE* Histo;
    int i,j,a;
    Histo = fopen("BASE_DESCRIPTEUR_IMAGE.txt", "a+");
    int histo[256] = {0};
    fprintf(Histo,"%d\n",id);
    for(i = 0; i<H; i++) {
        for(j = 0; j<L; j++) {
            fscanf(Image,"%d ",&a);
            histo[a]++;

        }

    }

    for(i = 0; i < niv; i++) fprintf(Histo,"%d ",histo[i]);
    fprintf(Histo,"\n");
    fclose(Histo);
}

int comparison(int niv, FILE* Histo1, FILE* Histo2) {
    int i,a,b,distance = 0;

    for(i = 0; i < niv; i++) {
        fscanf(Histo1,"%d ",&a);
        fscanf(Histo2,"%d ",&b);
        if(a<b) distance = distance + a;
        else distance = distance + b;
    }
    return distance;
}

int file1comparedfile2(int niv, int id1, int id2) {
    FILE * Histo1;
    FILE * Histo2;
    FILE * Image;
    Image = fopen("BASE_DESCRIPTEUR_IMAGE.txt", "r");
    if(Image != NULL) {

        int i,fichier, L;
        Histo1 = fopen("HISTO_1","w+");
        Histo2 = fopen("HISTO_2","w+");

        while(!feof(Image)) {
            fscanf(Image,"%d ",&fichier);

            if(fichier == id1) {

                for(i = 0; i < niv; i++) {
                    fscanf(Image,"%d ",&L);
                    fprintf(Histo1,"%d ",L);

                }

            }

            if(fichier == id2) {

                for(i = 0; i < niv; i++) {
                    fscanf(Image,"%d ",&L);
                    fprintf(Histo2,"%d ",L);
                }

            }

        }

        fclose(Histo1);
        fclose(Histo2);
        Histo1 = fopen("HISTO_1","r+");
        Histo2 = fopen("HISTO_2","r+");
        printf("La resultat de la comparaison est : %d. \n",comparison(niv,Histo1,Histo2));
        fclose(Image);
        fclose(Histo1);
        fclose(Histo2);
        system("rm HISTO_1");
        system("rm HISTO_2");
    } else printf("Desole probleme d'ouverture niveau 1...\n");
}
