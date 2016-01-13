
#include <stdio.h>
#include <string.h>
#include "config.h"
#include "interface.h"

char language[3];
char password[9];
char temp[2];
char *s1;
char *s2;
char *s3;
char *s4;
char *s5;
char *s6;
char *s7;
char *s8;
char *s9;
char *s10;

char fr1[] = "Bienvenue dans le moteur de recherche Upssearchtech, si vous êtes administrateur tapez votre mot de passe, sinon tapez simplement (u).";
char en1[] = "Welcome in the Upssearchtech search engine, if you are admin, please enter your password, else simply enter (u).";
char fr2[] = "Vous êtes";
char en2[] = "You are";
char fr3[] = "Tapez (0) si vous voulez lancer une indexation manuelle";
char en3[] = "Press (0) if you want to index manually";
char fr4[] = "Choisissez votre type de recherche :\n(1) Recherche par occurences d'un mot-clé\n(2) Recherche des textes les plus proches d'un texte donné\n(3) Recherche d'un document de type Image\n(4) Recherche d'un document de type Audio\n(q)uitter";
char en4[] = "What are you looking for ?\n(1) Search by hits of a keyword\n(2) Closest text of a given one\n(3) Image research\n(4) Audio research\n(q)uit";
char fr5[] = "Le mot de passe que vous avez rentré est erronné, corrigez-le ou tapez (u)";
char en5[] = "The password you entered is invalid, correct it or enter (u)";
char fr6[] = "Pour choisir, utilisez les touches indiquées dans le menu";
char en6[] = "Please use the keys as shown in the menu to choose";
char fr7[] = "Entrez un mot-clé pour trouver les textes avec le plus d'occurences";
char en7[] = "Enter a keyword to find the texts with the most hits";
char fr8[] = "Entrez le chemin d'un texte pour trouver les textes les plus ressemblants";
char en8[] = "Enter the path of a text to find the closest texts";
char fr9[] = "Entrez le chemin d'une image pour trouver images les plus ressemblantes";
char en9[] = "Enter the path of an image to find the closest images";
char fr10[] = "Entrez le chemin d'un jingle audio pour trouver le fichier le contenant";
char en10[] = "Enter the path of an audio sample to find the containing file";

//Copies the string according to the chosen language to display them
void loadLanguage(char * language) {
	if (strcmp(language,"fr") == 0) {
		s1 = strdup(fr1);
		s2 = strdup(fr2);
		s3 = strdup(fr3);
		s4 = strdup(fr4);
		s5 = strdup(fr5);
		s6 = strdup(fr6);
		s7 = strdup(fr7);
		s8 = strdup(fr8);
		s9 = strdup(fr9);
		s10 = strdup(fr10);
	} else if (strcmp(language,"en") == 0) {
		s1 = strdup(en1);
		s2 = strdup(en2);
		s3 = strdup(en3);
		s4 = strdup(en4);
		s5 = strdup(en5);
		s6 = strdup(en6);
		s7 = strdup(en7);
		s8 = strdup(en8);
		s9 = strdup(en9);
		s10 = strdup(en10);
	}
}

void keywordSearch() {
	openFile("fictest.txt");
}

void closestText() {
}

void imageSearch() {
	char a[10] = "01.txt" ; char b[10][100];
	  printf("Taper le nom du fichier image\n"); 
	  scanf("%s",a);
	  researchPictures(64,a,b);
	  printf("Les fichiers les plus proches est du plus ressemblant au moins ressemblant:\n);
}

void audioSearch() {
}

void launch() {
	printf("What language do you want to use ?/Quel langage voulez-vous utiliser ?(en)glish/(fr)ench\n");
	scanf("%s", language);
	while (strcmp(language,"en") != 0 && strcmp(language,"fr") != 0) {
		printf("The available languages are/Les langues disponibles sont : (en)glish/(fr)ench\n");
		scanf("%s", language);
	}
	loadLanguage(language);

	printf("%s\n", s1);
	scanf("%s", password);
	while ((verifyPassword(password) == 0) && (strcmp(password,"u") != 0)) {
		printf("%s\n", s5);
		scanf("%s", password);
	}

	while(strcmp(temp,"q") != 0) {

		if (strcmp(password,"u") == 0) {
			printf("%s user\n", s2);
		} else {
			printf("%s admin\n", s2);
			printf("%s\n", s3);
		}
		printf("%s\n", s4);
		scanf("%s", temp);

		if (strcmp(temp,"1") == 0) {
			keywordSearch();
		} else if (strcmp(temp,"2") == 0) {
			closestText();
		} else if (strcmp(temp,"3") == 0) {
			imageSearch();
		} else if (strcmp(temp,"4") == 0) {
			audioSearch();
		} else if (strcmp(temp, "5") == 0) {
			manualIndex();
		}
	}
}
