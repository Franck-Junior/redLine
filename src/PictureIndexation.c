#include<stdio.h>
#include<stdlib.h>
#include<math.h>
#include "PictureIndexation.h"
#include<string.h>

// Whenever they are used, H and L will mean "hauteur" and "largeur"

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
    } else printf("Desole probleme d'ouverture niveau 2...Il y a eu un problème dans la quantification, veuillez réessayer.\n");

}




int quantiToPixellevel(int niv, char quanti[]) {
    int i,level = 0;
    for(i = 0; i < niv; i++) {
        if(quanti[i]=='1') level = level+(int)pow(2,niv-1-i);
    }
    return level;
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




void Quantification(FILE* Image, int n) {
    int j,i,a,H,L;
    char quanti[2];
    FILE * ImageQuantifieR;
    FILE * ImageQuantifieV;
    FILE * ImageQuantifieB;
    ImageQuantifieR = fopen("QUANTIFIED_IMAGE_ROUGE.txt", "w+");
    ImageQuantifieV = fopen("QUANTIFIED_IMAGE_VERT.txt", "w+");
    ImageQuantifieB = fopen("QUANTIFIED_IMAGE_BLEU.txt", "w+");
    fscanf(Image,"%d ",&H);
    fscanf(Image,"%d ",&L);
    fscanf(Image,"%d ",&a);

    for(i = 0; i < H; i++) {
        for(j = 0; j < L; j++) {
            fscanf(Image,"%d ",&a);
            nBitQuantificator(ImageQuantifieR,n,a);
            fprintf(ImageQuantifieR," ");
        }
        fprintf(ImageQuantifieR,"\n");
    }
    fclose(ImageQuantifieR);

    for(i = 0; i < H; i++) {
        for(j = 0; j < L; j++) {
            fscanf(Image,"%d ",&a);
            nBitQuantificator(ImageQuantifieV,n,a);
            fprintf(ImageQuantifieV," ");
        }
        fprintf(ImageQuantifieV,"\n");
    }
    fclose(ImageQuantifieV);

    for(i = 0; i < H; i++) {
        for(j = 0; j < L; j++) {
            fscanf(Image,"%d ",&a);
            nBitQuantificator(ImageQuantifieB,n,a);
            fprintf(ImageQuantifieB," ");
        }
        fprintf(ImageQuantifieB,"\n");
    }
    fclose(ImageQuantifieB);

    ImageQuantifieR = fopen("QUANTIFIED_IMAGE_ROUGE.txt", "r+");
    ImageQuantifieV = fopen("QUANTIFIED_IMAGE_VERT.txt", "r+");
    ImageQuantifieB = fopen("QUANTIFIED_IMAGE_BLEU.txt", "r+");
    FILE* ImageQuantifie = fopen("QUANTIFIED_IMAGE.txt","w");

    for(i = 0; i < H; i++) {
        for(j = 0; j < L; j++) {
            fscanf(ImageQuantifieR,"%s",quanti);
            fprintf(ImageQuantifie,"%s",quanti);
            fscanf(ImageQuantifieV,"%s",quanti);
            fprintf(ImageQuantifie,"%s",quanti);
            fscanf(ImageQuantifieB,"%s",quanti);
            fprintf(ImageQuantifie,"%s ",quanti);
        }
        fprintf(ImageQuantifie,"\n");
    }
    fclose(ImageQuantifieR);
    fclose(ImageQuantifieV);
    fclose(ImageQuantifieB);
    system("rm QUANTIFIED_IMAGE_ROUGE.txt");
    system("rm QUANTIFIED_IMAGE_VERT.txt");
    system("rm QUANTIFIED_IMAGE_BLEU.txt");
    fclose(ImageQuantifie);

    ImageQuantifie = fopen("QUANTIFIED_IMAGE.txt","r+");
    ImageQuantifieR = fopen("IMAGE.txt","w");

    for(i = 0; i < H; i++) {
        for(j = 0; j < L; j++) {
            fscanf(ImageQuantifie,"%s",quanti); /*strcpy(quanti,"000011");*/
            fprintf(ImageQuantifieR,"%d ",quantiToPixellevel(3*n,quanti));
        }
        fprintf(ImageQuantifieR,"\n");
    }

    fclose(ImageQuantifieR);
    fclose(ImageQuantifie);

}




void histogramme(FILE* Image, int niv, char chemin[100], int H, int L, int id) {
    FILE* Histo;
    int i,j,a;
    char cheminlocal[100];
    strcpy(cheminlocal,chemin);
    if(niv == 256)
        strcat(cheminlocal,"BASE_DESCRIPTEUR_IMAGE_NOIR_ET_BLANC.txt");
    else strcat(cheminlocal,"BASE_DESCRIPTEUR_IMAGE_COULEUR.txt");
//     printf("%s\n",cheminlocal);
    Histo = fopen(cheminlocal, "a+");
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




int file1comparedTofile2(int niv, char chemin[100], int id1, int id2) {
    FILE * Histo1;
    FILE * Histo2;
    FILE * Descripteurs;
    int resultat;
        int i, id, L;
	
    Descripteurs = fopen(chemin, "r");
    if(Descripteurs != NULL) {
        Histo1 = fopen("HISTO_1","w+");
            fscanf(Descripteurs,"%d ",&id);
        while((!feof(Descripteurs))&&(id != id1)) {
	    for(i = 0; i < niv; i++) {
                    fscanf(Descripteurs,"%d ",&id);
                }
                fscanf(Descripteurs,"%d ",&id);
	}
            if(id == id1) {
                for(i = 0; i < niv; i++) {
                    fscanf(Descripteurs,"%d ",&L);
                    fprintf(Histo1,"%d ",L);

                }

            }
        fclose(Descripteurs);
        fclose(Histo1);
    } else printf("Desole probleme d'ouverture niveau 1...\n");

    Descripteurs = fopen(chemin, "r");
    if(Descripteurs != NULL) {
        Histo2 = fopen("HISTO_2","w+");
            fscanf(Descripteurs,"%d ",&id);
        while((!feof(Descripteurs))&&(id != id2)) {
	    for(i = 0; i < niv; i++) {
                    fscanf(Descripteurs,"%d ",&id);
                }
                fscanf(Descripteurs,"%d ",&id);
	}
            if(id == id2) {

                for(i = 0; i < niv; i++) {
                    fscanf(Descripteurs,"%d ",&L);
                    fprintf(Histo2,"%d ",L);
                }
            }
	      fclose(Descripteurs);
	      fclose(Histo2);
	} else printf("Desole probleme d'ouverture niveau 1...\n");

        Histo1 = fopen("HISTO_1","r");
        Histo2 = fopen("HISTO_2","r");
        /*printf("La resultat de la comparaison est : %d. \n",comparison(niv,Histo1,Histo2));*/resultat = comparison(niv,Histo1,Histo2);
        fclose(Histo1);
        fclose(Histo2);
        system("rm HISTO_1");
        system("rm HISTO_2");
    return resultat;
}




void textDescriptorLinker(char fileName[], char chemin[100], int id) {
    char cheminlocal[100];
    strcpy(cheminlocal,chemin);
    strcat(cheminlocal,"LISTE_BASE_IMAGE");
    FILE* LISTE_BASE = fopen(cheminlocal,"a+");
    fprintf(LISTE_BASE,"%s ", fileName);
    fprintf(LISTE_BASE,"%d\n",id);
    fclose(LISTE_BASE);

}




int blackandWhiteIndexation(char cheminlocal[100], int nbdesc) {
    FILE * Image;
    FILE * LISTE_FICHIER;
    char nomfichier[100];
    int H,L,buffer,nbfichiers,niv= 256;
    LISTE_FICHIER = fopen("listefichier","r");
    char chemin[100];
    char commande[100];
    strcpy(chemin,cheminlocal);
    strcpy(commande,"ls ");
    strcat(commande,chemin);
    strcat(commande," > listefichier");

    while(LISTE_FICHIER == NULL) { /*Cette boucle permet de faire une liste des fichiers présents dans le dossier oy se trouve les images noirs et blancs*/
        system(commande);
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
        if(nomfichier[((int)strlen(nomfichier))-1] == 't') {
	    nomfichier[((int)strlen(nomfichier))-1] = 't';
   nomfichier[((int)strlen(nomfichier))-2] = 'x';
   nomfichier[((int)strlen(nomfichier))-3] = 't';
	    
            strcat(chemin,nomfichier);
	    
            Image = fopen(chemin, "r");
            if(Image != NULL) {
                fscanf(Image,"%d ",&H);
                fscanf(Image,"%d ",&L);
                fscanf(Image,"%d ",&buffer);
                histogramme(Image,256,"./Descripteurs/",H,L,nbdesc);
                textDescriptorLinker(nomfichier,"./Descripteurs/",nbdesc);
                nbdesc++;
                fclose(Image);
            } else printf("Desole probleme d'ouverture niveau 1...\n");

        }
        i++;
        strcpy(chemin, "./IMAGE_NOIR_ET_BLANC/");
    }

    fclose(LISTE_FICHIER);
    system("rm listefichier");
    return 0;
}




int colorIndexation(char cheminlocal[100], int nbdesc) {

    FILE * Image;
    FILE * LISTE_FICHIER;
    char nomfichier[100];
    int H,L,buffer,nbfichiers,niv= 256;
    LISTE_FICHIER = fopen("listefichier","r");
    char chemin[100];
    char commande[100];
    strcpy(chemin,cheminlocal);
    strcpy(commande,"ls ");
    strcat(commande,chemin);
    strcat(commande," > listefichier");

    while(LISTE_FICHIER == NULL) { /*Cette boucle permet de faire une liste des fichiers présents dans le dossier*/
        system(commande);
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
    strcpy(commande,chemin);
    while(i < nbfichiers) {
        fscanf(LISTE_FICHIER,"%s",nomfichier);
        if(nomfichier[((int)strlen(nomfichier))-1] == 't') {
	    nomfichier[((int)strlen(nomfichier))-1] = 't';
   nomfichier[((int)strlen(nomfichier))-2] = 'x';
   nomfichier[((int)strlen(nomfichier))-3] = 't';
	    
            strcat(commande,nomfichier);
	    
            Image = fopen(commande, "r");
            Quantification(Image,2);
            fclose(Image);
            Image = fopen("IMAGE.txt","r+");
            if(Image != NULL) {
                fscanf(Image,"%d ",&H);
                fscanf(Image,"%d ",&L);
                fscanf(Image,"%d ",&buffer);
                histogramme(Image,64,"./Descripteurs/",H,L,nbdesc);
                textDescriptorLinker(nomfichier,"./Descripteurs/",nbdesc);
                nbdesc++;
                fclose(Image);
            } else printf("Desole probleme d'ouverture niveau 1...\n");

        }
        i++;
        strcpy(commande,chemin);
        //strcpy(chemin, "./IMAGE_NOIR_ET_BLANC/");
    }


    fclose(LISTE_FICHIER);
    system("rm listefichier");
    system("rm QUANTIFIED_IMAGE.txt");
    system("rm IMAGE.txt");

}




void researchPictures(int niv, char fileName[50], char fileNamefound[50]) {
    int i,desc,max = 0; //desc the id of the descriptor of the most resembling image
    int id = fileNameToDesc("./Descripteurs/",fileName);
    char cheminlocal[100];
    if(niv == 64) strcpy(cheminlocal,"./Descripteurs/BASE_DESCRIPTEUR_IMAGE_COULEUR.txt");
    else strcpy(cheminlocal,"./Descripteurs/BASE_DESCRIPTEUR_IMAGE_NOIR_ET_BLANC.txt");
    int ref;
    for(i = 1; i < 5; i++) {
        ref = file1comparedTofile2(niv,cheminlocal,id,i);
        if((max < ref)&&(i!=id)) {
            max = ref;
            desc = i;
        }
    }
    descToFileName(desc,"./Descripteurs/",fileNamefound);;
}

// void researchPictures(char fileRef[100], int niv,char chemin[100], char fileRes[100]){
//   int i,max = 0; //resdesc the id of the descriptor of the most resembling image
//   int ref;
//   for(i = 1; i < 4; i++){
//     ref = file1Tofile2comparison(niv,chemin,fileRef,fileRes);
//     if(max < ref){
//       max = ref;
//       desc = id+i;
//     }
//   }
//
// }

void descToFileName(int id, char chemin[100], char currentfile[100]) {
    FILE* F;
    int currentid;
    char cheminlocal[100];
    strcpy(cheminlocal,chemin);
        strcat(cheminlocal,"LISTE_BASE_IMAGE");
        printf("%s\n",cheminlocal);
        F = fopen(cheminlocal,"r+");
        fscanf(F,"%s",currentfile);
        fscanf(F,"%d",&currentid);
        while((currentid != id) && (!feof(F))) {
            fscanf(F,"%s",currentfile);
            fscanf(F,"%d",&currentid);
        }
}

int fileNameToDesc(char chemin[100], char fileName[100]) {
    FILE* F;
    int currentid;
    char currentfile[100];
    char cheminlocal[100];
    strcpy(cheminlocal,chemin);
        strcat(cheminlocal,"LISTE_BASE_IMAGE");
        F = fopen(cheminlocal,"r+");
        fscanf(F,"%s",currentfile);
        fscanf(F,"%d",&currentid);
        while(strcmp(currentfile,fileName) && (!feof(F))) {
            fscanf(F,"%s",currentfile);
            fscanf(F,"%d",&currentid);
        }
        return currentid;
}

int file1Tofile2comparison(int niv, char chemin[100], char fileName1[50], char fileName2[50]) {
    char cheminlocal[100];
    char baseDesc[50];
    strcpy(cheminlocal,chemin);
    if(niv == 256) {
        strcpy(baseDesc,"BASE_DESCRIPTEUR_IMAGE_NOIR_ET_BLANC.txt");
        strcat(cheminlocal,baseDesc);
        return file1comparedTofile2(niv,cheminlocal,fileNameToDesc(chemin,fileName1),fileNameToDesc(chemin,fileName2));
    } else {
        strcpy(baseDesc,"BASE_DESCRIPTEUR_IMAGE_COULEUR.txt");
        strcat(cheminlocal,baseDesc);
        return file1comparedTofile2(niv,cheminlocal,fileNameToDesc(chemin,fileName1),fileNameToDesc(chemin,fileName2));
    }
}



int indexation(char chemin[100],char nomDufichier[100], int nbdesc){
  FILE* Image;      
  char cheminlocal[100];
  char nomfichier[100];
  int H,L,C;
	strcpy(cheminlocal,chemin);
	strcpy(nomfichier,nomDufichier);
	nomfichier[((int)strlen(nomfichier))-1] = 't';
   nomfichier[((int)strlen(nomfichier))-2] = 'x';
   nomfichier[((int)strlen(nomfichier))-3] = 't';
        strcat(cheminlocal,nomfichier);
            Image = fopen(cheminlocal, "r");
            if(Image != NULL) {
                fscanf(Image,"%d ",&H);
                fscanf(Image,"%d ",&L);
                fscanf(Image,"%d ",&C);
		if(C == 1){
                histogramme(Image,256,"./Descripteurs/",H,L,nbdesc);
		} else histogramme(Image,64,"./Descripteurs/",H,L,nbdesc);
                textDescriptorLinker(nomfichier,"./Descripteurs/",nbdesc);
                nbdesc++;
                fclose(Image);
		return 1;
            } else printf("Sorry the file %s to be indexed has not been found\n",nomfichier);


    return 0;
}