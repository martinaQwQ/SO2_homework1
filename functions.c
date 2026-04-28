#include "header.h"

// Elimina gli spazi davanti 
char *salta_spazi(char *riga){
    while (isspace(*riga))
        riga++;   //avanzo con il puntatore
    return riga;
} 
void lettura_riga(){
    FILE *fp;
    fp= fopen ("prova.c", "r");  // apro il file
    char riga[300];
    if (fp == NULL){
        perror("Errore apertura file");
        return ;
    }
    while ((fgets(riga, sizeof(riga), fp)) != NULL){ //legge la riga 
        salta_spazi(riga);
        

        if (riga[0]== '#'){
            continue;} else{ printf("%s", riga);}

    }
    fclose(fp);
}
