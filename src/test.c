#include "DealingWithSound.h"

int SEUIL = 3;
int TAILLE_MAX_MOT = 25;
int TAILLE_MIN_MOT = 3;
int TAILLE_MAX_CHEMIN = 150;
int TAILLE_MAX_NOM = 25;
int NB_MAX_RESULTATS = 50;
int NOMBRE_ECHANTILLONS = 1000;
int NOMBRE_INTERVALLES = 100; //<10000000, %2==0

int DEBUG=1;

typedef struct Scientific{
    int mantisse;
    int exposant;
}Scientific;

Scientific *normalization(char* in, Scientific *sc){

    char mantisseString[8];//8
    mantisseString[0]=in[3];
    for(int i=5;i<12;i++)
        mantisseString[i-4]=in[i];

    sc->mantisse=atoi(mantisseString);
    if(in[2]!=" ")
        sc->mantisse=sc->mantisse*-1;
    /*
    if(DEBUG){
        printf("mantisse : %s\n",mantisseString);
        printf("mantisse int : %d\n",sc->mantisse);
    }
    */

    sc->exposant=atoi(&(in[15]));

    /*
    if(DEBUG)
        printf("exposant int : %d\n",sc->exposant);
    */
    return sc;
}

    
int getIntervalle(Scientific sc){
    
    //on enleve 3 chiffres
    int result=sc.mantisse;
    for(int i=1;i<=sc.exposant;i++){
        result=result/10;
        //printf("result==%d, i==%d, exposant==%d\n",result,i,sc.exposant);
    }

    //printf("1: %d\n",result);
    
    //max result possible==99999999, min 999,
    int pas=1000000/NOMBRE_INTERVALLES;

    //printf(": %d/%d=%d\n",result,pas,result/pas);

    result=result/pas;

    if(result < 0)
        result=NOMBRE_INTERVALLES+result-1;

    //printf("3: %d\n",result);

    return result;
}

// index fileName trying to deal with wave files
int IndexFileAudio(char fileName[]){

    // open files fileName, base_descripteur_son, liste_base_son
    errno = 0;
    FILE* pFileName = fopen(fileName, "rb");
    if(pFileName  == NULL){
        if(DEBUG)
            printf("Error %d \n", errno);
        return(-1);   //Err opening fileName
    }
    FILE* pBaseDescriptorSon = fopen("./sto/base_descripteur_son", "a+");
    if (pBaseDescriptorSon == NULL){
        if(DEBUG)
            printf("Error %d \n", errno);
        return(-2);  //Err opening pBaseDescriptorSon
    }
    FILE* pListeBaseSon = fopen("./sto/liste_base_son", "a+");
    if (pListeBaseSon == NULL){
        if(DEBUG)
            printf("Error %d \n", errno);
        return(-3);  //Err opening pListeBaseSon
    }

    

    //update liste_base_son
    int currId = 0;
    int lastId=0;
    fseek(pListeBaseSon, -2,SEEK_END);
    fscanf(pListeBaseSon,"   %d", &lastId);
    printf("lastID=%d\n",lastId);
    currId = lastId+1;
    fprintf(pListeBaseSon,"%s;", fileName);
    fprintf(pListeBaseSon, "%d;", NOMBRE_INTERVALLES);
    fprintf(pListeBaseSon, "%d;", NOMBRE_ECHANTILLONS);
    fprintf(pListeBaseSon, "%d", currId);
    fprintf(pListeBaseSon, "\n");
    fclose(pListeBaseSon);

    //write descripteur into base_descripteur

    //go to the end of pBaseDescriptorSon to write the new descriptor
    fseek(pBaseDescriptorSon,0,SEEK_END);//go to the end 

    //go to the start of pFileName
    fseek(pFileName,0,SEEK_SET);

    fprintf(pBaseDescriptorSon,"%d\n", currId);

    int count[NOMBRE_INTERVALLES];
    for(int k=0;k<NOMBRE_INTERVALLES;k++)
        count[k]=0;

    char *currLine = NULL;
    size_t lenght = 0;
    ssize_t read;
    Scientific currSc;
    int done=0;

    while ((read = getline(&currLine, &lenght, pFileName)) != -1) {
        //printf("Retrieved line of length %zu :\n", read);
        //printf("lu %s", currLine);
        normalization(currLine,&currSc);
        done++;
        count[getIntervalle(currSc)]++;
        if(done==NOMBRE_ECHANTILLONS){
            //write in descriptor
            for(int k=0;k<NOMBRE_INTERVALLES;k++){
                fprintf(pBaseDescriptorSon,"%d;", count[k]);
                count[k]=0;
            }
            fprintf(pBaseDescriptorSon,"\n");
            done=0;
        }
        //printf("calculer %d/(10^%d) \n",currSc.mantisse, currSc.exposant );

    }
    if (currLine)
           free(currLine);

    fclose(pFileName);
    fclose(pBaseDescriptorSon);
   
    
    return 1;//Success
}

int main(){
    char fileName[TAILLE_MAX_CHEMIN];
    printf("Entrez un fichier ou un dossier : ");
    scanf("%s", fileName);
    switch(IndexFileAudio(fileName)){
        case -1:printf("impossible d'ouvrir le fichier à indexer\n");
            break;
        case -2:printf("impossible d'ouvrir le descriteur son\n");
            break;
        case -3:printf("impossible d'ouvrir la liste base son\n");
            break;
        case -4:printf("Err not RIFF\n");
            break;
        case -5:printf("Err not WAVE\n");
            break;
        default:
            printf("succès\n");
    }

}