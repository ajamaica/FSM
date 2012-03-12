#include <stdio.h>
#include <stdlib.h>
#include <assert.h>

typedef struct nodo{
    int value;
    struct nodo *next;
}Nodo;

struct stack{
    Nodo *top;
};

void reset(struct stack *s){
    struct nodo *p, *q;
    
    p = s->top;
    while(p != NULL){
        q = p->next;
        free(p);
        p = q;
    }
    
    s->top = NULL;
}

void init(struct stack *s){
    s->top = NULL;
}

void push(struct stack *s, int val){
    struct nodo *nuevo;
    
    nuevo = (struct nodo *) malloc( sizeof(struct nodo) );
    nuevo->value = val;
    nuevo->next = s->top;
    
    s->top = nuevo;
    
}

int top(struct stack *s){
    assert(s->top != NULL);
    
    return s->top->value;
}

int is_empty(struct stack *s){
    return (s->top != NULL);
}

void pop(struct stack *s){
    struct nodo *p;
    
    assert (s->top != NULL);
    
    p = s->top;
    s->top = p->next;
    
    free(p);
}

int main (int argc, char const *argv[]){
    int i;
    struct stack mi_stack;
    
    init(&mi_stack);
    for(i = 0; i < 10; i++){
        printf("Agregando %i\n", i);
        push(&mi_stack, i);
    }
    
    printf("\nis_empty? %i\n\n", is_empty(&mi_stack));
    for(; i > 0; i--){
        printf("El elemento tope es %i\n", top(&mi_stack));
        pop(&mi_stack);
    }

    return 0;
}