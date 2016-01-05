#include<stdio.h>
#include<stdlib.h>
#include<math.h>
#include<string.h>
#include "PictureIndexation.h"

int main(void) {
    FILE * Image;
    FILE * LISTE_FICHIER;
    char nomfichier[100];
    int H,L,buffer,nbfichiers,niv= 256;
    LISTE_FICHIER = fopen("listefichier","r");
    char chemin[100] = "./IMAGE_NOIR_ET_BLANC/";

    while(LISTE_FICHIER == NULL) { /*Cette boucle permet de faire une liste des fichiers présents dans le dossier*/
        system("ls ./IMAGE_NOIR_ET_BLANC/ > listefichier");
        LISTE_FICHIER = fopen("listefichier","r");
    }

    nbfichiers = 0;
    while(!feof(LISTE_FICHIER)) { /*Celle-ci permet de compter le nombre de fichiers dans le dossier*/
        fscanf(LISTE_FICHIER,"%s",nomfichier);
        nbfichiers++;
    }
    fclose(LISTE_FICHIER);

    nbfichiers -= 1;
    LISTE_FICHIER = fopen("listefichier","r");
    int i = 0;
    while(i < nbfichiers) {
        fscanf(LISTE_FICHIER,"%s",nomfichier);
        strcat(chemin,nomfichier);
        Image = fopen(chemin, "r");

        if(Image != NULL) {
            fscanf(Image,"%d ",&H);
            fscanf(Image,"%d ",&L);
            fscanf(Image,"%d ",&buffer);
            histogramme(Image,256,H,L,i+1);
            fclose(Image);
        } else printf("Desole probleme d'ouverture niveau 1...\n");
	
	textDescriptorLinker(nomfichier, i+1);
        i++;
        strcpy(chemin, "./IMAGE_NOIR_ET_BLANC/");
    }
    
    fclose(LISTE_FICHIER);
    system("rm listefichier");
    return 0;
}