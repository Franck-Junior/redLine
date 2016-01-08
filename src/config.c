
#include <stdio.h>
#include <string.h>

//Looks into the config file for the requested parameter for various uses
char * getConfig(char * request) {
	FILE *fp;
	if ((fp = fopen("config.txt", "r+")) == NULL);
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
