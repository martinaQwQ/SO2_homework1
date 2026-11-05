#include "header.h"
int main (int argc, char *argv[]){
    Parametri p;

    if (leggiParametri(argc, argv, &p) != 1){
        printf("Errore nei parametri\n");
        return 1;
    }

    if (p.input != NULL){
    printf("File input: %s\n", p.input);
    }
    else {
        return 1;
    }
  
    return 0;
    }
 