#include "header.h"


//manca ancora tanta roba 
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


int inCommento= 0;
void rimuoviCommento (char *riga){
    
    for (int i= 0; riga[i] != '\0'; i++){

        if(inCommento== 1){
            
            // caso: */
            if (riga[i]== '*' && riga[i+1] == '/'){
                riga[i] = ' ';
                riga[i+1] = ' ';
                inCommento=0;

            } else if(riga[i] != '\n'){
                riga[i]= ' ';
                
            }
        }

        // caso: //
        else if (riga[i] == '/' && riga[i+1] == '/'){
            while (riga[i] != '\n' && riga[i] != '\0'){ 
                riga[i] = ' ';
                i++;
                }
           break; 
            }
        
        // caso : /*
        else if(riga[i]== '/' && riga[i+1] == '*'){
            riga[i] = ' ';
            riga[i+1]= ' ';
            inCommento= 1;
            i++;
        }
    }
}



int apriFile(Parametri *p){
    FILE *file = fopen(p->input, "r");
   
   //file vuoto
    if (file == NULL){
        printf("Errore apertura file\n");
        return -1;
    } 
    char riga[1024];
    int numeroRiga= 0;
    inCommento=0;

    while (fgets(riga, sizeof(riga), file) != NULL){
        numeroRiga++;
        rimuoviCommento(riga);
        printf("Riga %d: %s", numeroRiga, riga);
    }

    //controllo errori di lettura
    if (ferror(file)){
        printf("Errore durante la lettura\n");
        fclose(file);
        return -1;
    }

    //errore di chiusura 
    if (fclose(file)== EOF){
        printf("Errore durante la chiusura\n");
        return -1;
    }
    
    return 0;
}

