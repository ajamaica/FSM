//
//  Parser.c
//  FSm
//
//
//          o,y,no,*,id,(,),$
//        E
//        D
//        T
//        S
//        U
//        F
//        X
//        P
/*
#include "header.h"

void parser(){
    char * matriz[8][8];
    int fd, nbytes, i=0, j=0;
    char buffer[BUFSIZ];
    
    if( (fd = open("TABLA_LL.txt", O_RDONLY , 0666)) < 0){
        fprintf(stderr, "El archivo de Output 'TABLA_LL.txt' no existe, no se puede crear o no se puede abrir.\n");
    }
    
    
    char * pch;
    while ( (nbytes = read(fd, buffer, BUFSIZ)) > 0 ) {
        pch = strtok (buffer,"\n,");
        while (pch != NULL){
            matriz[i][j] = pch;
            pch = strtok (NULL, "\n,");
            j++;
            if(j == 8){
                j=0;
                i++;
            }
            if(i == 8){
                break;
            }
        }
	}
}
*/
