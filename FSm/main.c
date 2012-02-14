#include "header.h"

/*
  
 
 0    |   0      1     -2  -3  -4  -5  -6  -7    -8     -8
 
 1    |  -1      1     -1  -1  -1  -1  -1  -1     1     -1
 
 **/


static TokenType

GetToken( stream, term )

FILE *stream;  

char *term;

{
    
    int next_ch;  
    
    int state;    
    
    int i;        
    
    int p;
    
    state = 0;
    
    i = 0;
    
    p = 0;
    
    while ( 0  <= state )
        
    {
        
        if ( EOF == (next_ch = getc(stream)) ) next_ch = '\0';
        
        
        term[i++] = convert_case[next_ch];
        
        switch( state )
        
        {
                
            case 0 :
            
                
                switch( char_class[next_ch] )
                
            {
                    
                case WHITE_CH :     i = 0; break;
                    
                case LETTER_CH :    state =  1; break;
                                        
                case LFT_PAREN_CH :
                case RGT_PAREN_CH :
                case LFT_CURLYBRACKET_CH :
                case RGT_CURLYBRACKET_CH : 
                case LFT_SQRBRACKET_CH : 
                case RGT_SQRBRACKET_CH : term[i] = '\0'; state = -AGRUPATION_TOKEN; break;
                    
                case AMPERSAND_CH : state = 4; break;
                                        
                case PIPE_CH :       state = 5; break;
                    
                case CARET_CH :     state = 6; break;
                    
                case EOS_CH :       state = -7; break;
                    
                case DIGIT_CH :     state = 25; break;
                    
                case OTHER_CH :   term[i] = '\0';   state = -8; break;
                    
                case ADDITION_CH :  state = 9; break;
                    
                case HYPHENMINUS_CH :  state = 10; break;

                case STAR_CH :  state = 11; break;
                    
                case SLASH_CH :  state = 12; break;
                    
                case GT_CH :  state = 13; break;

                case LT_CH :  state = 14; break;

                case EQ_CH :  state = 15; break;

                case PERCENTAGE_CH :  state = 16; break;
                    
                case COMMA_CH : term[i] = '\0'; state = -17; break;

                case SEMICOLON_CH : term[i] = '\0'; state = -18; break;
                
                case COLON_CH : term[i] = '\0'; state = -20; break;
                    
                case TILDE_CH :  state = -19; break;

                case EXCLAMATION_CH :  state = 21; break;
                    
                case NUMBERSIGN_CH :  state = 22; break;
                    
                case POINT_CH :  state = 23; break;

                case QUOTATION_CH :  state = 24; break;
                    
                case QUESTION_CH : state = -27; break;
                    
                    


                default :           state =-8; break;
                    
            }
                
                break;
                
                
            case 1 :
                
                
                
                if ( (DIGIT_CH != char_class[next_ch])
                    
                    && (LETTER_CH != char_class[next_ch]) )
                    
                {
                    
                    ungetc( next_ch, stream );
                    
                    term[i-1] = '\0';
                    
                    state = -1;
                    
                    
                    
                }
                
                
                break;
            case 4:
                
                if (AMPERSAND_CH == char_class[next_ch] ) {
                    term[i] = '\0';
                    state = -LOGIC_TOKEN;
                }else{
                    ungetc( next_ch, stream );
                    term[i-1] = '\0';      
                    state = -LOGIC_TOKEN;
                }
            
            break;
            case 5:
                
                if (PIPE_CH == char_class[next_ch] ) {
                    term[i] = '\0';
                    state = -LOGIC_TOKEN;
                }else
                if (EQ_CH == char_class[next_ch] ) {
                    term[i] = '\0';
                    state = -ASSIGMENT_TOKEN;
                }
                
                else{
                    ungetc( next_ch, stream );
                    term[i-1] = '\0';      
                    state = -LOGIC_TOKEN;
                }
                
                break;
            case 6:
                
                if (EQ_CH == char_class[next_ch] ) {
                    term[i] = '\0';
                    state = -ASSIGMENT_TOKEN;
                }else{
                    ungetc( next_ch, stream );
                    term[i-1] = '\0';      
                    state = -LOGIC_TOKEN;
                }
                
            break;
                
            case 9:
                
                if (ADDITION_CH == char_class[next_ch] ) {
                    
                    term[i] = '\0';
                    state = -9;
                }else

                        
                if (EQ_CH == char_class[next_ch] ) {
                            
                            term[i] = '\0';
                            state = -13;
                }else
                {
                            ungetc( next_ch, stream );
                            term[i-1] = '\0';      
                            state = -9;
                }
            
            break;  
                
            case 10:

                if (HYPHENMINUS_CH == char_class[next_ch] ) {
                    
                    term[i] = '\0';
                    state = -9;
                }else
                    
                    
                if (EQ_CH == char_class[next_ch] ) {
                        
                        term[i] = '\0';
                        state = -ASIGNATION_TOKEN;
                }else
                if (GT_CH == char_class[next_ch]) {
                    term[i] = '\0';
                    state = -POINTER_TOKEN;
                    
                }else{
                        ungetc( next_ch, stream );
                        term[i-1] = '\0';      
                        state = -9;
                }
                
                break;
                
            case 11:
                    
                    term[i] = '\0';
                    state = 29;
                
                
            break;
                
            case 12:
                
               
                if (STAR_CH == char_class[next_ch] ) {
                    
                    term[i] = '\0';
                    state = -29;
                }else
                
                if (SLASH_CH == char_class[next_ch] ) {
                    
                    term[i] = '\0';
                    state = -29;
                }else
                
                if (EQ_CH == char_class[next_ch] ) {
                    
                    term[i] = '\0';
                    state = -13;
                }else
                {
                    ungetc( next_ch, stream );
                    term[i-1] = '\0';      
                    state = -12;
                }
                
                
                


                
            break;
           
            case 13:
                
                if (GT_CH == char_class[next_ch] ) {
                        
                        term[i] = '\0';
                        state = 100;
                }else
                        
                if (EQ_CH == char_class[next_ch] ) {
                            
                            term[i] = '\0';
                            state = -EQ_TESTING_TOKEN;
                }else
                {
                            ungetc( next_ch, stream );
                            term[i-1] = '\0';      
                            state = -LOGIC_TOKEN;
                }
                
            break;
            case 14:
                
                if (LT_CH == char_class[next_ch] ) {
                    
                    term[i] = '\0';
                    state = 100;
                }else
                    
                    if (EQ_CH == char_class[next_ch] ) {
                        
                        term[i] = '\0';
                        state = -EQ_TESTING_TOKEN;
                }else
                {
                        ungetc( next_ch, stream );
                        term[i-1] = '\0';      
                        state = -LOGIC_TOKEN;
                }
                
            break;
                
            case 15:
                
                if (EQ_CH == char_class[next_ch] ) {
                    
                    term[i] = '\0';
                    state = -LOGIC_TOKEN;
                }else
                {
                        ungetc( next_ch, stream );
                        term[i-1] = '\0';      
                        state = -ASSIGMENT_TOKEN;
                }
                
            break;
                
            // >>
            case 100:
                if (EQ_CH == char_class[next_ch] ) {
                    ungetc( next_ch, stream );
                    term[i] = '\0';      
                    state = -BITWISE_LOGIC_TOKEN;

                }else{
                    ungetc( next_ch, stream );
                    term[i-1] = '\0';      
                    state = -BITWISE_SHIFT_TOKEN;
                }
            
            break;
                
            case 16:
                
                if (EQ_CH == char_class[next_ch] ) {
                    
                    term[i] = '\0';
                    state = -ASSIGMENT_TOKEN;
                }else
                {
                    ungetc( next_ch, stream );
                    term[i-1] = '\0';
                    state = -ARITMETIC_TOKEN;
                }
            
            break;
                
                
                
                
            case 23:
                if ( (DIGIT_CH != char_class[next_ch]) ){
                    
                    ungetc( next_ch, stream );

                    term[i-1] = '\0';
                    state = 26;
                }
                
                if( (POINT_CH == char_class[next_ch])){

                    state = 25;
                }
            break;
                
                
            case 25:       
                
                
                if ( (DIGIT_CH != char_class[next_ch]) && ((POINT_CH != char_class[next_ch])))
                    
                {
                    ungetc( next_ch, stream );
                    
                    term[i-1] = '\0';
                    
                    state = -25;
                    
                    
                    
                }
                
                
                if ((POINT_CH == char_class[next_ch])) {
                    
                    state = 26;
                }
                
                
                
            break;
                
            case 26:
                
                
                
                if ( (DIGIT_CH != char_class[next_ch]) )
                    
                {
                    
                    
                    ungetc( next_ch, stream );
                    
                    term[i-1] = '\0';
                    
                    state = -26;
                    
                }
                
                
                
                
            break;
                
            case 29:
                
                
                if ( (DIGIT_CH != char_class[next_ch]) && (LETTER_CH != char_class[next_ch]) )
                    
                {
                    
                    
                    ungetc( next_ch, stream );
                    
                    term[i-1] = '\0';
                    
                    state = -29;
                    
                }
                
                
                
                
                break;

    
                
           
                
            default : state = -8; break;
            
                
                
        }
        
    }
    
    
    
    return( (TokenType) (-state) );
    
    
} 



int main(int argc, char **argv, char **envp){
    
    TokenType token;   /* next token in the input stream */
    
    char term[128];    /* the term recognized */
    
    FILE *stream;      /* where to read the data from */
    
    int fd_output;      /* File Descriptor for Output File */
    
    
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
    
    
    stream = fopen("File.c","r");
        
    do{
        output = 
        "\n\t<tr>"
        "\n\t\t<td>";
        write( fd_output, output, strlen(output));
        switch( token = GetToken(stream,term) )
        {  
                
                
            case TERM_TOKEN :
                if (isReservedWord(term)) {
                    printf("\n %s : PALABRA RESERVADA", term);
                }
                else{
                    printf("\n %s : ID", term);
                }
            break;
                
            case DIGIT_TOKEN:
                printf("\n %s : NUMERO", term);
            break;
                
            case DIGIT_POINT_TOKEN:
                printf("\n %s : NUMERO DECIMAL", term);
            break;
                
            case AGRUPATION_TOKEN : 
            case COMMA_TOKEN: (void)printf ( "\n %s : AGRUPACION", term ); 
            break;
                
            case COLON_TOKEN:
            case QUESTION_TOKEN:
                printf("\n %s : CONDICIONAL", term);
            break;
                
            case TILDE_TOKEN:
                printf("\n %s : DESTRUCTOR", term);
            break;
                
            case SEMICOLON_TOKEN:
                printf("\n %s : EOS", term);
            break;
                
            case COMENT_TOKEN:
                printf("\n %s : COMENTARIO", term);
                break;
            
            case ARITMETIC_TOKEN:
            case ADDITION_TOKEN:
            case DIVISION_TOKEN:
                printf("\n %s : OPERACION", term);
                break;
                
            case ASSIGMENT_TOKEN:
            case ASIGNATION_TOKEN:
                printf("\n %s : ASIGNACION", term);
            break;
                
            case POINTER_TOKEN:
                printf("\n %s : APUNTADOR", term);
            break;
                
            case EQ_TESTING_TOKEN:
                printf("\n %s : Equality Testing", term);
            break;
                
            case LOGIC_TOKEN:
                printf("\n %s :  LOGICO", term);
            break;
                
            case BITWISE_LOGIC_TOKEN:
                printf("\n %s : LOGICO BITWISE", term);
            break;
                
            case BITWISE_SHIFT_TOKEN:
                printf("\n %s : LOGICO BITWISE SHIFT ", term);
            break;
                

            default :
                //(void)printf ("Error"); 
            break;
                
        
                
        }
        
        
        write( fd_output, term, strlen(term));
        output = 
        "</td>"
        "\n\t\t<td> Palabra Rervada</td>"
        "\n\t</tr>";
        write( fd_output, output, strlen(output));
    }while ( END_TOKEN != token );
    char *salida =
    "\n</table>"
    "\n</body>";
    
    write( fd_output, salida, strlen(salida));
    
    close(fd_output);
    fclose ( stream );
    
    
}