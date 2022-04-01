#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct{
    int dia;
    int mes;
    int ano;
} Data;

typedef struct student{
    char matricula[10];
    char nome[40];
    Data dataDeNascimento;
    float media;
    struct student *next;
    struct student *ant;
} Student;

int search(Student *first, const char matricula[10]){
    Student *aux;
    int counter = 0;
    for(aux=first; aux!=NULL; aux = aux->next){
        if(strcmp(aux->matricula, matricula) == 0){
            counter++;
        }
    }
    return counter;
}

void listDefault(Student *first){
    Student *aux;
    for(aux=first; aux != NULL; aux=aux->next){
        printf("%s, ", aux->matricula);
        printf("%s, ", aux->nome);
        printf("%d/%d/%d, ", aux->dataDeNascimento.dia, aux->dataDeNascimento.mes, aux->dataDeNascimento.ano);
        printf("%.2f\n", aux->media);
    }
}

void listInv(Student *last){
    Student *aux;
    for(aux = last; aux != NULL; aux = aux->ant){
        printf("%s, ", aux->matricula);
        printf("%s, ", aux->nome);
        printf("%d/%d/%d, ",aux->dataDeNascimento.dia, aux->dataDeNascimento.mes, aux->dataDeNascimento.ano);
        printf("%.2f\n",aux->media);
    }
}

void end(Student *first){
    for(Student *aux = first;aux != NULL; aux= aux->next){
        printf("*");
    }
}

Student *Insert(Student *last, const char matricula_ant[10]){
    Student *aux = last;
    if(strcmp(matricula_ant, aux->matricula) == 0){
        return aux;
    }
    for(; aux->ant !=NULL; aux = aux->ant){
        if(strcmp(matricula_ant, aux->ant->matricula) == 0){
            return aux->ant;
        }
    }

    return NULL;
}

int main(){
    Student *actual = NULL;
    Student *first = NULL;
    Student *last = NULL;
    int option = 1;
    while(1){
        scanf("%d", &option);
        if(option == 1){
            char matricula[10];
            char nome[40];
            char matricula_ant[10];
            int dia, mes, ano;
            float media;
            actual = (Student *) malloc(sizeof(Student));
            scanf("%s", matricula_ant);
            scanf("%s", matricula);
            scanf("%s", nome);
            scanf("%d/%d/%d", &dia,&mes,&ano);
            scanf("%f", &media);
            actual->dataDeNascimento.dia = dia;
            actual->dataDeNascimento.mes = mes;
            actual->dataDeNascimento.ano = ano;
            strcpy(actual->matricula, matricula);
            strcpy(actual->nome, nome);
            actual->media = media;
            actual->next = NULL;
            actual->ant = NULL;
            if(first == NULL){
                first = actual;
                last = first;
            }else{
                Student *aux = Insert(last, matricula_ant);
                if(aux==NULL){
                    first->ant = actual;
                    actual->next = first;
                    actual->ant = NULL;
                    first = actual;
                }else if(aux == last){
                    aux->next = actual;
                    actual->ant =aux;
                    actual->next = NULL;
                    last = actual;
                }else{
                    Student *prox = aux->next;
                    aux->next = actual;
                    actual->ant = aux;
                    actual->next = prox;
                    prox->ant = actual;
                }
            }

        }else if(option == 2){
            if(first == NULL){
                printf("Lista Vazia!\n");
            }else{
                char matricula[10];
                Student *aux;
                scanf("%s", matricula);
                for(int i=search(first,matricula); i>0; i--){
                    for(aux = first; aux!=NULL; aux = aux->next){
                        if(strcmp(matricula, aux->matricula) == 0){
                            if(aux == first){
                                first = aux->next;
                                if(first != NULL){
                                    first->ant = NULL;
                                }
                        }else if(aux == last){
                            last = aux->ant;
                            last->next = NULL;
                        }else{
                            aux->ant->next = aux->next;
                            aux->next->ant = aux->ant;
                        }
                        free(aux);
                        break;
                        }
                    }
                }
            }
        }else if(option == 3){
            if(first == NULL){
                printf("Lista Vazia!\n");
            }else{
            listDefault(first);
            }
        }else if(option == 4){
            if(first == NULL){
                printf("Lista Vazia!\n");
            }else{
                listInv(last); 
            }
        }else if(option == 0){
            end(first);
            printf("\n");
            break;
        }
    }
    printf("\n");
    return 0;
}