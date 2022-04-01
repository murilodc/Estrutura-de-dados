#include <stdio.h>
#include <stdlib.h>
#include <string.h>

struct _elStack {
    char element[61]; //troque para char *
    struct _elStack *next;
};
typedef struct _elStack ElementStack;

typedef struct {
    ElementStack *top;
} Stack;

int isEmpty(Stack *stack){
    return (stack->top == NULL)? 1: 0;
}

void pop (Stack *stack){
    ElementStack *aux;
    
    aux = stack->top;
    stack->top = stack->top->next;
    printf("%s\n", aux->element);
    free(aux);
}


void printStack(ElementStack *element){
    if (element == NULL)
        return;
    printStack(element->next);
    printf("%s -> ", element->element);
}

void freeStack(Stack *stack){
    ElementStack *aux;

    if(isEmpty(stack)){
        printf("!");
    }else{
        while(stack->top != NULL){
            aux = stack->top;
            stack->top = stack->top->next;
            free(aux);
            printf("@");
        }
    }
}

void push(Stack *stack, char element[61]){
    ElementStack *newElement = malloc(sizeof(ElementStack));
    newElement->next = NULL;
    strcpy(newElement->element, element);

    newElement->next = stack->top;
    stack->top = newElement;
}


int main (){
    Stack url;
    url.top = NULL;

    char element[61];
    scanf("%s", element);
    while(strcmp(element, "E") != 0){
        if(strcmp(element,"B") == 0){
            if(isEmpty(&url)){
                printf("Vazio\n");
            }else{
                pop(&url);
            }
        }else{
            push(&url, element);
        }
        scanf("%s", element);
    }
    freeStack(&url);

    printf("\n");

    return 0;
}