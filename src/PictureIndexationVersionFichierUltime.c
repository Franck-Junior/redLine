#include<stdio.h>
#include<stdlib.h>
#include<math.h>
// #include<indexationImage.h>


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
    //avec QPICTURE, le tableau de pixels quantifiés
    for(i = 0; i < H; i++) {
        for(j = 0; j < L; j++) {
            fscanf(Image,"%d ",&a);
            nBitQuantificator(ImageQuantifie,n,a);
            fprintf(ImageQuantifie," ");
        }
        fprintf(ImageQuantifie,"\t");
//       nBitQuantificator(n, PICTURE[i][j], QPICTURE[i][j]);
    }
    fclose(ImageQuantifie);

}


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