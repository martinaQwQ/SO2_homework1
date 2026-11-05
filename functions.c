#include "header.h"
int leggiParametri (int argc, char *argv[], Parametri *p ){
    //inizializzazione struct
    p-> input = NULL;
    p-> output= NULL;
    p-> verbose= 0;
    char *parametro= NULL;


    for (int i= 1; i< argc; i++){

        //CASO_1 --in/--out/--verbose
        if (argv[i][0]== '-' && argv[i][1]== '-'){
        
            if (strcmp(argv[i], "--in")== 0){
                if (p->input != NULL ||
                    i+1>= argc ||
                    !(isalpha(argv[i+1][0]) || argv[i+1][0] == '_') ){
                        printf("Errore: file input non valido\n");
                        return -1;
                    }
                    p->input= argv[++i];
            }

            else if (strcmp(argv[i], "--out")== 0){
                if (p->output != NULL ||
                    i+1 >= argc ||
                    !(isalpha(argv[i+1][0]) || argv[i+1][0]=='_')){
                    printf("Errore: file output non valido\n");
                    return -1;
                }
                p-> output= argv[++i];
            }

            else if (strcmp(argv[i], "--verbose")== 0){
                p->verbose = 1; 
            }
            else {
                printf("%s: Opzione sconosciuta\n", argv[i]);
                return -1;
            }
        }

        //CASO_2 -i/-o/-v e composti 
        else if(argv[i][0]== '-' &&
                argv[i][1]!= '-' &&
                argv[i][1] != '\0'){

            parametro = argv[i];
            for (int j= 1; parametro[j]!= '\0'; j++){
                if (parametro[j]=='i'){
                    if (p->input != NULL ||
                        i+1 >= argc ||
                        !(isalpha(argv[i+1][0]) || argv[i+1][0]=='_')){
                            printf("Errore: file input non valido\n");
                            return -1 ;
                    } 
                    p->input = argv[++i];
                    
                } 
               

                else if (parametro[j] == 'o') {
                    if (p-> output != NULL ||
                        i+1 >= argc || 
                        !(isalpha(argv[i+1][0]) ||
                        (argv[i+1][0]=='_'))) {
                        printf("Errore: file output non valido\n");
                        return -1;
                    }
                    p->output = argv[++i];
                }

                else if (parametro[j]== 'v'){
                    p-> verbose= 1;
                }

                else {
                    printf("%c: parametro sconosciuto\n", parametro[j]);
                    return -1;
                }
            }
           
        }

        // Parametri diversi da i/o/v
        else {
            printf("Opzione sconosciuta %s\n", argv[i]);
            return -1; //altre opzioni
        }
        
    }

    // File input obbligatorio
    if (p->input == NULL){
        printf("Errore: file input mancante\n");
        return -1;
    }

    //  Verbose
    if (p->verbose){
        printf("Verbose attivo\n");
    }
    return 1;
}


int apriFile(Parametri *p){
    FILE * file = fopen(p->input, "r");
   
   //file vuoto
    if (file == NULL){
        printf("Errore apertura file\n");
        return -1;
    }
    else {
        
    }
}