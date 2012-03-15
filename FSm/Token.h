#ifndef FSm_Token_h
#define FSm_Token_h

#include "header.h"

static TokenT LeerToken( FILE *stream, char *term ) {
    
    int next_ch;  
    int state;    
    int i;        
    int p;
    
    state = 0;
    i = 0;
    p = 0;
    
    while ( 0  <= state ){
        if ( EOF == (next_ch = getc(stream)) ) {
            next_ch = '\0';
        }
        
        term[i++] = convert_case[next_ch];
        
        switch ( state ){
            case 0 :
                switch ( char_class[next_ch] ) {
                    case WHITE_CH :     
                        i = 0; 
                        break;
                        
                    case LETTER_CH :    
                        state =  1; 
                        break;
                        
                    case LFT_PAREN_CH :
                    case RGT_PAREN_CH :
                        term[i] = '\0'; 
                        state = -AGRUPATION_TOKEN; 
                        break;
                        
                    case EOS_CH :       
                        state = -7; 
                        break;
                        
                    case DIGIT_CH :     
                        state = 25; 
                        break;
                        
                    case OTHER_CH :   
                        term[i] = '\0';  
                        state = -8; 
                        break;
                        
                    case STAR_CH :  
                        state = 11; 
                        break;
                        
                    default :           
                        state =-8; 
                        break;
                }
                break;
                
            case 1 :
                if ( (DIGIT_CH != char_class[next_ch])
                    && (LETTER_CH != char_class[next_ch]) ) {
                    ungetc( next_ch, stream );
                    term[i-1] = '\0';
                    state = -1;
                }
                break;
               
            case 11:
                term[i] = '\0';
                state = 29;
                break;
               
            case 25:       
                if ( (DIGIT_CH != char_class[next_ch])) {
                    ungetc( next_ch, stream );
                    term[i-1] = '\0';
                    state = -25;
                }
                
            case 26:
                if ( (DIGIT_CH != char_class[next_ch]) ) {
                    ungetc( next_ch, stream );
                    term[i-1] = '\0';
                    state = -26;
                }
                break;
                
            case 29:
                if ( (DIGIT_CH != char_class[next_ch]) && (LETTER_CH != char_class[next_ch]) ) {
                    
                    ungetc( next_ch, stream );
                    term[i-1] = '\0';
                    //state = -COMENT_TOKEN;
                }
                break;
                
            default : state = -8; break;
        }
    }
    
    return( (TokenT) (-state) );
} 


#endif
