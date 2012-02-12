#include <stdio.h>
#include "header.h"

/*FN************************************************************************
 
 
 GetToken( stream )
 
 
 
 
 Run a finite state machine on an input stream, collecting
 
 the text of the token if it is a term. The transition table
 
 for this DFA is the following (negative states are final):
 
 
 State  |  White  Letter  (    )  &   |   ^  EOS  Digit  Other
 
 -------------------------------------------------------------
 
 0    |   0      1     -2  -3  -4  -5  -6  -7    -8     -8
 
 1    |  -1      1     -1  -1  -1  -1  -1  -1     1     -1
 
 
 See the token type above to see what is recognized in the
 
 various final states.
 
 **/


static TokenType

GetToken( stream, term )

FILE *stream;  /* in: where to grab input characters */

char *term;    /* out: the token text if the token is a term */

{
    
    int next_ch;  /* from the input stream */
    
    int state;    /* of the tokenizer DFA */
    
    int i;        /* for scanning through the term buffer */
    
    
    /* Part 1: Run a state machine on the input */
    
    state = 0;
    
    i = 0;
    
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
                    
                case LFT_PAREN_CH : state = -2; break;
                    
                case RGT_PAREN_CH : state = -3; break;
                    
                case AMPERSAND_CH : state = -4; break;
                                        
                case BAR_CH :       state = -5; break;
                    
                case CARET_CH :     state = -6; break;
                    
                case EOS_CH :       state = -7; break;
                    
                case DIGIT_CH :     state = 1; break;
                    
                case OTHER_CH :   term[i] = '\0';   state = -8; break;
                    
                case ADDITION_CH :  state = 9; break;
                    
                case HYPHENMINUS_CH :  state = 10; break;


                    
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
                if ( SUSTRACTION_CH != char_class[next_ch]) {
                    
                    
                    term[i] = '\0';
                    state = -10;
                    
                }else{
                                        
                    term[i] = '\0';
                    state = -11;
                }
                
                break;
                
            default :state = -8; break;
            
                
                
        }
        
    }
    
    
    /* Part 2: Coerce the final state to return the type token */
    
    return( (TokenType) (-state) );
    
    
} /* GetToken */



/*FN***********************************************************************
 
 
 main( argc, argv )
 
 
 Returns: int -- 0 on success, 1 on failure
 
 
 Purpose: Program main function
 
 
 Plan:    Part 1: Open a file named on the command line
 
 Part 2: List all the tokens found in the file
 
 Part 3: Close the file and return
 
 
 Notes:   This program simply lists the tokens found in a single file
 
 named on the command line.
 
 **/


int main(int argc, char **argv, char **envp){
    
    TokenType token;   /* next token in the input stream */
    
    char term[128];    /* the term recognized */
    
    FILE *stream;      /* where to read the data from */
    
    
    stream = fopen("File.c","r");
        
        do
            
            switch( token = GetToken(stream,term) )
            
        {
                
            case TERM_TOKEN :      (void)printf ( "term: %s\n", term ); break;
                
            case LFT_PAREN_TOKEN : (void)printf ( "left parenthesis\n" ); break;
                
            case RGT_PAREN_TOKEN : (void)printf ( "right parenthesis\n" ); break;
                
            case AND_TOKEN :       (void)printf ( "and operator\n" ); break;
                
            case OR_TOKEN :        (void)printf ( "or operator\n" ); break;
                
            case NOT_TOKEN :       (void)printf ( "not operator\n" ); break;
                
            case END_TOKEN :       (void)printf ( "end of string\n" ); break;
                
            case NO_TOKEN :        (void)printf ( "%s : no token\n", term ); break;
                
            case B_TOKEN :        (void)printf ( "%s s : YEEEY \n", term ); break;
                
            case SUSTRACTION_TOKEN :        (void)printf ( "%s s : Menos \n", term ); break;
                
            case ASIGNATION_TOKEN :        (void)printf ( "%s s : Asignacion \n", term ); break;



                
            default :              (void)printf ( "bad data\n" ); break;
                
        }
    
    while ( END_TOKEN != token );
    
    
    fclose ( stream );
    
    
}