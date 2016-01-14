
#include <stdio.h>
#include <string.h>
#include <stdlib.h>

//Looks into the config file for the requested parameter for various uses
char * getConfig(char * request) {
	FILE *fp;
	if ((fp = fopen("config.txt", "r")) == NULL) {
		return "Could not open config file/Impossible d'ouvrir le fichier de configuration";
	}
	char temp[92];
	char * res;
	char * line;
	while(fgets(temp,92,fp) != NULL) {
		if ((strstr(temp, request)) != NULL) {
			line = strdup(temp);
		}
	}

	if(fp) {
		fclose(fp);
	}

	res = strtok(line,"=");
	res = strtok(NULL,"=");
	return res;
}
//Tries to use the config file and creates a default one if it fails
int checkConfig() {
	FILE *fp;
	if ((fp = fopen("config.txt", "r+")) == NULL) {
		printf("Config file not found/Fichier de config introuvable\n");
		printf("A default config file will be created/Un fichier de config de base sera créé\n");
		if ((fp = fopen("config.txt", "a")) != NULL) {
			fputs("CHEMIN=.\nTAILLE_MOT_MAX=15\nSEUIL_OCCURENCES=2\nNB_BITS=3\nNB_ECHANTILLONS=22000\nNB_INTERVALLES=200\nMDP_ADMIN=super42", fp);
			fclose(fp);
			return 1;
		} else {
			return 2;
		}
	} 
	return 0;
}

//Opens the best result with the default program
void openFile(char * file) {
	char command[100] = "xdg-open ";
	strcat(command, file);
	system(command);
}

//Compares the input and the password in the config file
int verifyPassword(char * password) {
	if (strcmp(password, getConfig("MDP_ADMIN")) == 0) {
		return 1;
	} else {
		return 0;
	}
}

/* Manage folder and sort before indexing function */
// works with absolute path
// possibility of some error in the table - sometimes a case change his own value to something wrong
char** getFileToIndex(char** textFile, int textSize) {
	/* Get list of file possibly to index */
	char** fileList = NULL;

	char* folder = getConfig("CHEMIN");
	char* order = "./../script/stockFile.sh ";
	char* finalOrder = (char *) malloc(1 + strlen(order)+ strlen(folder) );
	strcpy(finalOrder, order);
	strcat(finalOrder, folder);
 
	system(finalOrder);

	FILE* file = fopen("../script/listFile.txt","r");
	int character;
	int size = 0;
	int cpt = 0;
	if (file != NULL) {
	        char line[256];
		fgets(line, sizeof(line), file);
		size = atoi(line);
		fileList = malloc(size);
		while (fgets(line, sizeof(line), file) && cpt < size) {
			fileList[cpt] = malloc(strlen(line)+1);
			strcpy(fileList[cpt],line);
			fileList[cpt][strlen(line)-1] = '\0';
			cpt++;
		}
	}
	fclose(file);

	/* remove indexing file of the list */
	// TO DO : remove sound file and picture file already indexing		
	for(int i=0 ; i<size ; ++i) {
		fprintf(stderr,"error : %s\n",fileList[i]);
	}

	for(int i=0 ; i<size ; ++i) {
		for(int j=0 ; j<textSize ; ++j) {
			if(fileList[i] != NULL && textFile[j] != NULL) {
				if (strstr(fileList[i], textFile[j]) != NULL) {
					fileList[i] = NULL;
				}
			}
			fprintf(stderr,"error : %s\n",fileList[i]);
		}
	}

	/* FREE PART */
	free(finalOrder);
	system("rm ../script/listFile.txt");

	return fileList;
}
