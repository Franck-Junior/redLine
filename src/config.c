
#include <stdio.h>
#include <string.h>
#include <stdlib.h>

//Looks into the config file for the requested parameter for various uses
char * getConfig(char * request) {
	FILE *fp;
	if ((fp = fopen("config.txt", "r+")) == NULL) {
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

