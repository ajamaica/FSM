#include <stdio.h>
#include "header.h"

/*
 
 State  |  White  Letter  (    )  &   |   ^  EOS  Digit  Other
 
 -------------------------------------------------------------
 
 0    |   0      1     -2  -3  -4  -5  -6  -7    -8     -8
 
 1    |  -1      1     -1  -1  -1  -1  -1  -1     1     -1
 
 **/


static TokenType

GetToken( stream, term )

FILE *stream;  /* in: where to grab input characters */

char *term;    /* out: the token text if the token is a term */

{
    
    int next_ch;  /* from the input stream */
    
    int state;    /* of the tokenizer DFA */
    
    int i;        /* for scanning through the term buffer */
    
    int p;
    /* Part 1: Run a state machine on the input */
    
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
                                        
                case LFT_PAREN_CH : term[i] = '\0'; state = -2; break;
                    
                case RGT_PAREN_CH : term[i] = '\0'; state = -3; break;
                    
                case LFT_CURLYBRACKET_CH : term[i] = '\0'; state = -30; break;
                    
                case RGT_CURLYBRACKET_CH : term[i] = '\0'; state = -31; break;
                    
                case LFT_SQRBRACKET_CH : term[i] = '\0'; state = -32; break;
                    
                case RGT_SQRBRACKET_CH : term[i] = '\0'; state = -33; break;
                    
                case AMPERSAND_CH : state = -4; break;
                                        
                case PIPE_CH :       state = -5; break;
                    
                case CARET_CH :     state = -6; break;
                    
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
                    
                case COMMA_CH :  state = -17; break;

                case SEMICOLON_CH : term[i] = '\0'; state = -18; break;
                
                case COLON_CH : state = -20; break;
                    
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

                
            case 9:
                if ( ADDITION_CH != char_class[next_ch]) 
                    
                {
                    
                    ungetc( next_ch, stream );
                    
                    term[i-1] = '\0';
                    state = -9;
                    
                }
            
            break;  
                
            case 10:

                if ( HYPHENMINUS_CH != char_class[next_ch]) {

                    
                    term[i] = '\0';
                    state = -10;
                    
                }else{
                                        
                    term[i] = '\0';
                    state = -11;
                }
                
                break;
                
            case 11:
                if (SLASH_CH == char_class[next_ch] ) {
                    
                    term[i] = '\0';
                    state = 29;
                }
                
                
                
            break;
                
            case 12:
                
                if (SLASH_CH != char_class[next_ch] ) {
                    ungetc( next_ch, stream );
                    term[i-1] = '\0';      
                    state = -12;
                }
                
                if (STAR_CH == char_class[next_ch] ) {
                    term[i] = '\0';
                    state = -29;
                }
                
                if (SLASH_CH == char_class[next_ch] ) {
                    
                    term[i] = '\0';
                    state = -29;
                }
                
                if (EQ_CH == char_class[next_ch] ) {
                    
                    term[i] = '\0';
                    state = -11;
                }
                
                


                
            break;
                
            case 13:
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
    
                
           
                
            default : state = -8; break;
            
                
                
        }
        
    }
    
    
    /* Part 2: Coerce the final state to return the type token */
    
    return( (TokenType) (-state) );
    
    
} /* GetToken */




int main(int argc, char **argv, char **envp){
    
    TokenType token;   /* next token in the input stream */
    
    char term[128];    /* the term recognized */
    
    FILE *stream;      /* where to read the data from */
    
    
    stream = fopen("File.c","r");
        
        do
            
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
                printf("\n %s : NUMERO", term);
                
            break;
                
            case RGT_PAREN_TOKEN :
            case LFT_PAREN_TOKEN :
            case RGT_CURLYBRACKET_TOKEN :
            case LFT_CURLYBRACKET_TOKEN :
            case RGT_SQRBRACKET_TOKEN :
            case LFT_SQRBRACKET_TOKEN : 
            case COMMA_TOKEN: (void)printf ( "\n %s : Agrupación", term ); break;
                
            case COLON_TOKEN:
            case QUESTION_TOKEN:
                printf("\n %s : CONDICIONAL", term);
            break;
                
            case TILDE_TOKEN:
                printf("\n %s : DESTRUCTOR", term);
            break;
                
            case SEMICOLON_TOKEN:
                printf("\n %s : EOS(End of Statement)", term);
                break;
                
            case COMENT_TOKEN:
                printf("\n %s : comentario ", term);
                break;
            
            case ASIGNATION_TOKEN:
                printf("\n %s : asignacion ", term);
                break;
                
            case DIVISION_TOKEN:
                printf("\n %s : Operación ", term);
                break;
                
            default :              (void)printf (""); break;
                
                
        }
    
    while ( END_TOKEN != token );
    
    
    fclose ( stream );
    
    
}