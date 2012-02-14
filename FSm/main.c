#include "Token.h"

int main(int argc, char const *argv[]){
    
    if(argc == 2){
        
        TokenT token;       /* next token in the input stream */
        
        char term[128];     /* the term recognized */
        
        FILE *stream;       /* where to read the data from */
        
        int fd_output;      /* File Descriptor for Output File */
        
        if((stream = fopen(argv[1],"r")) == NULL){
            fprintf(stderr, "El archivo %s no existe o no se puede abrir\n", argv[1]);
        }
        
        if( (fd_output = open("OutputFile.html", O_WRONLY | O_TRUNC | O_CREAT, 0666)) < 0){
            fprintf(stderr, "El archivo de Output 'OutputFile.html' no existe, no se puede crear o no se puede abrir.\n");
        }
        
        char *output =
        "<head>"
        "\n</head>"
        "\n<body>"
        "\n<table border=1>"
        "\n\t<tr>"
        "\n\t\t<th>Simbolos</th>"
        "\n\t\t<th>Tipo</th>"
        "\n\t</tr>";
        write( fd_output, output, strlen(output));
        
        
        do {
            output = 
            "\n\t<tr>"
            "\n\t\t<td>";
            write( fd_output, output, strlen(output));
            
            char *tipo;
            
            switch ( token = LeerToken(stream,term) ) {  
                case TERM_TOKEN :
                    if (isReservedWord(term)) {
                        tipo = "Palabra Reservada";
                        printf("\n %s : PALABRA RESERVADA", term);
                    }
                    else{
                        tipo = "Variable/ID";
                        printf("\n %s : ID", term);
                    }
                    break;
                    
                case DIGIT_TOKEN:
                    tipo = "Numero";
                    printf("\n %s : NUMERO", term);
                    break;
                    
                case DIGIT_POINT_TOKEN:
                    tipo = "Numero Decimal";
                    printf("\n %s : NUMERO DECIMAL", term);
                    break;
                    
                case AGRUPATION_TOKEN : 
                case COMMA_TOKEN: (void)printf ( "\n %s : AGRUPACION", term ); 
                    tipo = "Agrupacion";
                    break;
                    
                case COLON_TOKEN:
                case QUESTION_TOKEN:
                    tipo = "Condicional";
                    printf("\n %s : CONDICIONAL", term);
                    break;
                    
                case TILDE_TOKEN:
                    tipo = "Destructor";
                    printf("\n %s : DESTRUCTOR", term);
                    break;
                    
                case SEMICOLON_TOKEN:
                    tipo = "EOS (End Of Statement)";
                    printf("\n %s : EOS", term);
                    break;
                    
                case COMENT_TOKEN:
                    tipo = "Comentario";
                    printf("\n %s : COMENTARIO", term);
                    break;
                    
                case ARITMETIC_TOKEN:
                case ADDITION_TOKEN:
                case DIVISION_TOKEN:
                    tipo = "Operacion";
                    printf("\n %s : OPERACION", term);
                    break;
                    
                case ASSIGMENT_TOKEN:
                case ASIGNATION_TOKEN:
                    tipo = "Asignacion";
                    printf("\n %s : ASIGNACION", term);
                    break;
                    
                case POINTER_TOKEN:
                    tipo = "Apuntador";
                    printf("\n %s : APUNTADOR", term);
                    break;
                    
                case EQ_TESTING_TOKEN:
                    tipo = "Equality Testing";
                    printf("\n %s : Equality Testing", term);
                    break;
                    
                case LOGIC_TOKEN:
                    tipo = "Operado Logico";
                    printf("\n %s :  LOGICO", term);
                    break;
                    
                case BITWISE_LOGIC_TOKEN:
                    tipo = "Operador Logico Bitwise";
                    printf("\n %s : LOGICO BITWISE", term);
                    break;
                    
                case STRING_TOKEN:
                    tipo = "String";
                    printf("\n %s : STRING TOKEN", term);
                    break;
                    
                case BITWISE_SHIFT_TOKEN:
                    tipo = "Operado Logico Bitwise de Shift";
                    printf("\n %s : LOGICO BITWISE SHIFT ", term);
                    break;
                    
                    
                default :
                    //(void)printf ("Error"); 
                    break;        
            }
            
            /* HTML Output */
            write( fd_output, term, strlen(term));
            output = 
            "</td>"
            "\n\t\t<td>";
            write(fd_output, output, strlen(output));
            write(fd_output, tipo, strlen(tipo));
            output=
            "</td>"
            "\n\t</tr>";
            write( fd_output, output, strlen(output));
            /**/
            
        }while ( END_TOKEN != token );
        
        char *salida =
        "\n</table>"
        "\n</body>";
        write( fd_output, salida, strlen(salida));
        
        close(fd_output);
        fclose ( stream );
        
    } else {
        fprintf(stderr, "No se han especificado los archivos de origen, ni el archivo destino.\n");
        return -1;
    }
    
    
}