#import <stdio.h>

// Proyecto Teoría de la Computación

typedef enum {
    
    WHITE_CH,             /* whitespace  */
    
    DIGIT_CH,             /*  digits */
    
    LETTER_CH,            /* letters */
    
    LFT_PAREN_CH,         /* ( */
    
    RGT_PAREN_CH,         /* ) */
    
    AMPERSAND_CH,         /* & */
    
    ADDITION_CH,         /* + */
    
    BAR_CH,               /* | */
    
    CARET_CH,             /* ^ */
    
    EOS_CH,               /* \0 */
    
    OTHER_CH,             /* CATCH ALL THE STF */
    
    
} CharClassType;


static CharClassType char_class[128] = {
    
    /* ^@ */  EOS_CH,      /* ^A */  OTHER_CH,    /* ^B */  OTHER_CH,
    
    /* ^C */  OTHER_CH,    /* ^D */  OTHER_CH,    /* ^E */  OTHER_CH,
    
    /* ^F */  OTHER_CH,    /* ^G */  OTHER_CH,    /* ^H */  WHITE_CH,
    
    /* ^I */  WHITE_CH,    /* ^J */  WHITE_CH,    /* ^K */  WHITE_CH,
    
    /* ^L */  WHITE_CH,    /* ^M */  WHITE_CH,    /* ^N */  OTHER_CH,
    
    /* ^O */  OTHER_CH,    /* ^P */  OTHER_CH,    /* ^Q */  OTHER_CH,
    
    /* ^R */  OTHER_CH,    /* ^S */  OTHER_CH,    /* ^T */  OTHER_CH,
    
    /* ^U */  OTHER_CH,    /* ^V */  OTHER_CH,    /* ^W */  OTHER_CH,
    
    /* ^X */  OTHER_CH,    /* ^Y */  OTHER_CH,    /* ^Z */  OTHER_CH,
    
    /* ^[ */  OTHER_CH,    /* ^\ */  OTHER_CH,    /* ^] */  OTHER_CH,
    
    /* ^^ */  OTHER_CH,    /* ^_ */  OTHER_CH,    /*    */  WHITE_CH,
    
    /*  ! */  OTHER_CH,    /*  " */  OTHER_CH,    /*  # */  OTHER_CH,
    
    /*  $ */  OTHER_CH,    /*  % */  OTHER_CH,    /*  & */  AMPERSAND_CH,
    
    /*  ' */  OTHER_CH,    /*  ( */  LFT_PAREN_CH, /*  ) */  RGT_PAREN_CH,
    
    /*  * */  OTHER_CH,    /*  + */  ADDITION_CH,    /*  , */  OTHER_CH,
    
    /*  - */  OTHER_CH,    /*  . */  OTHER_CH,    /*  / */  OTHER_CH,
    
    /*  0 */  DIGIT_CH,    /*  1 */  DIGIT_CH,    /*  2 */  DIGIT_CH,
    
    /*  3 */  DIGIT_CH,    /*  4 */  DIGIT_CH,    /*  5 */  DIGIT_CH,
    
    /*  6 */  DIGIT_CH,    /*  7 */  DIGIT_CH,    /*  8 */  DIGIT_CH,
    
    /*  9 */  DIGIT_CH,    /*  : */  OTHER_CH,    /*  ; */  OTHER_CH,
    
    /*  < */  OTHER_CH,    /*  = */  OTHER_CH,    /*  > */  OTHER_CH,
    
    /*  ? */  OTHER_CH,    /*  @ */  OTHER_CH,    /*  A */  LETTER_CH,
    
    /*  B */  LETTER_CH,   /*  C */  LETTER_CH,   /*  D */  LETTER_CH,
    
    /*  E */  LETTER_CH,   /*  F */  LETTER_CH,   /*  G */  LETTER_CH,
    
    /*  H */  LETTER_CH,   /*  I */  LETTER_CH,   /*  J */  LETTER_CH,
    
    /*  K */  LETTER_CH,   /*  L */  LETTER_CH,   /*  M */  LETTER_CH,
    
    /*  N */  LETTER_CH,   /*  O */  LETTER_CH,   /*  P */  LETTER_CH,
    
    /*  Q */  LETTER_CH,   /*  R */  LETTER_CH,   /*  S */  LETTER_CH,
    
    /*  T */  LETTER_CH,   /*  U */  LETTER_CH,   /*  V */  LETTER_CH,
    
    /*  W */  LETTER_CH,   /*  X */  LETTER_CH,   /*  Y */  LETTER_CH,
    
    /*  Z */  LETTER_CH,   /*  [ */  OTHER_CH,    /*  \ */  OTHER_CH,
    
    /*  ] */  OTHER_CH,    /*  ^ */  CARET_CH,    /*  _ */  OTHER_CH,
    
    /*  ` */  OTHER_CH,    /*  a */  LETTER_CH,   /*  b */  LETTER_CH,
    
    /*  c */  LETTER_CH,   /*  d */  LETTER_CH,   /*  e */  LETTER_CH,
    
    /*  f */  LETTER_CH,   /*  g */  LETTER_CH,   /*  h */  LETTER_CH,
    
    /*  i */  LETTER_CH,   /*  j */  LETTER_CH,   /*  k */  LETTER_CH,
    
    /*  l */  LETTER_CH,   /*  m */  LETTER_CH,   /*  n */  LETTER_CH,
    
    /*  o */  LETTER_CH,   /*  p */  LETTER_CH,   /*  q */  LETTER_CH,
    
    /*  r */  LETTER_CH,   /*  s */  LETTER_CH,   /*  t */  LETTER_CH,
    
    /*  u */  LETTER_CH,   /*  v */  LETTER_CH,   /*  w */  LETTER_CH,
    
    /*  x */  LETTER_CH,   /*  y */  LETTER_CH,   /*  z */  LETTER_CH,
    
    /*  { */  OTHER_CH,    /*  | */  BAR_CH,      /*  } */  OTHER_CH,
    
    /*   */  OTHER_CH,    /* ^? */  OTHER_CH,                           };



static char convert_case[128] = {
    
    /* ^@ */    0,    /* ^A */    0,    /* ^B */    0,    /* ^C */     0,
    
    /* ^D */    0,    /* ^E */    0,    /* ^F */    0,    /* ^G */     0,
    
    /* ^H */    0,    /* ^I */    0,    /* ^J */    0,    /* ^K */     0,
    
    /* ^L */    0,    /* ^M */    0,    /* ^N */    0,    /* ^O */     0,
    
    /* ^P */    0,    /* ^Q */    0,    /* ^R */    0,    /* ^S */     0,
    
    /* ^T */    0,    /* ^U */    0,    /* ^V */    0,    /* ^W */     0,
    
    /* ^X */    0,    /* ^Y */    0,    /* ^Z */    0,    /* ^[ */     0,
    
    /* ^\ */    0,    /* ^] */    0,    /* ^^ */    0,    /* ^_ */     0,
    
    /*    */  ' ',    /*  ! */  '!',    /*  " */  '"',    /*  # */   '#',
    
    /*  $ */  '$',    /*  % */  '%',    /*  & */  '&',    /*  ' */  '\'',
    
    /*  ( */  '(',    /*  ) */  ')',    /*  * */  '*',    /*  + */   '+',
    
    /*  , */  ',',    /*  - */  '-',    /*  . */  '.',    /*  / */   '/',
    
    /*  0 */  '0',    /*  1 */  '1',    /*  2 */  '2',    /*  3 */   '3',
    
    /*  4 */  '4',    /*  5 */  '5',    /*  6 */  '6',    /*  7 */   '7',
    
    /*  8 */  '8',    /*  9 */  '9',    /*  : */  ':',    /*  ; */   ';',
    
    /*  < */  '<',    /*  = */  '=',    /*  > */  '>',    /*  ? */   '?',
    
    /*  @  */ '@',    /*  A */  'a',    /*  B */  'b',    /*  C */   'c',
    
    /*  D */  'd',    /*  E */  'e',    /*  F */  'f',    /*  G */   'g',
    
    /*  H */   'h',   /*  I */  'i',    /*  J */  'j',    /*  K */   'k',
    
    /*  L */   'l',   /*  M */  'm',    /*  N */  'n',    /*  O */   'o',
    
    /*  P */   'p',   /*  Q */  'q',    /*  R */  'r',    /*  S */   's',
    
    /*  T */   't',   /*  U */  'u',    /*  V */  'v',    /*  W */   'w',
    
    /*  X */   'x',   /*  Y */  'y',    /*  Z */  'z',    /*  [ */   '[',
    
    /*  \ */  '\\',   /*  ] */  ']',    /*  ^ */  '^',    /*  _ */   '_',
    
    /*  ` */   '`',   /*  a */  'a',    /*  b */  'b',    /*  c */   'c',
    
    /*  d */   'd',   /*  e */  'e',    /*  f */  'f',    /*  g */   'g',
    
    /*  h */   'h',   /*  i */  'i',    /*  j */  'j',    /*  k */   'k',
    
    /*  l */   'l',   /*  m */  'm',    /*  n */  'n',    /*  o */   'o',
    
    /*  p */   'p',   /*  q */  'q',    /*  r */  'r',    /*  s */   's',
    
    /*  t */   't',   /*  u */  'u',    /*  v */  'v',    /*  w */   'w',
    
    /*  x */   'x',   /*  y */  'y',    /*  z */  'z',    /*  { */   '{' ,
    
    /*  | */   '|',   /*  } */  '}',    /*  ~ */  '~',    /* ^? */     0,
    };




typedef enum {
    
    
    TERM_TOKEN      = 1,    /* a search term */
    
    LFT_PAREN_TOKEN = 2,    /* left parenthesis */
    
    RGT_PAREN_TOKEN = 3,    /* right parenthesis */
    
    AND_TOKEN       = 4,    /* set intersection connective */
    
    ADDITION_TOKEN  = 9,    /* set intersection connective */

    OR_TOKEN        = 5,    /* set union connective */
    
    NOT_TOKEN       = 6,    /* set difference connective */
    
    END_TOKEN       = 7,    /* end of the query */
    
    NO_TOKEN        = 8,    /* the token is not recognized */
    
    B_TOKEN        = 9,    /* the token is not recognized */

    
    
} TokenType;


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

                
            default :              (void)printf ( "bad data\n" ); break;
                
        }
    
    while ( END_TOKEN != token );
    
    
    fclose ( stream );
    
    
}