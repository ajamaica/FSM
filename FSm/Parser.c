//
//  Parser.c
//  FSm
//
//
#include "header.h"
#include <stdio.h>

void parser(){
    char ** matriz;
    int fd, nbytes, i=0, j=0;
    char buffer[BUFSIZ];
    
    if( (fd = open("TABLA_LL.txt", O_WRONLY | O_TRUNC | O_CREAT, 0666)) < 0){
        fprintf(stderr, "El archivo de Output 'TABLA_LL.txt' no existe, no se puede crear o no se puede abrir.\n");
    }
    
    while ( (nbytes = read(fd, buffer, BUFSIZ)) > 0 ) {
        char * pch;
        pch = strtok (buffer," ,.-");
        while (pch != NULL)
        {
            matriz[i][j] = pch;
            pch = strtok (NULL, " ,.-");
            j++;
        }
        i++;
	}
}
