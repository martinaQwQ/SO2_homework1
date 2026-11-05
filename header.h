#ifndef HEADER_H
#define HEADER_H
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <ctype.h>

typedef struct{
    char *input;  //argomento di input
    char *output; //argomento di output
    int verbose; // 1 se presente -v/ --verbose
}Parametri;

int leggiParametri (int argc, char *argv[], Parametri *p );

#endif 