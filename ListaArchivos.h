#include <stdio.h>
#include <stdlib.h>
#include <dirent.h>
#include <string.h>

struct ListaArchivos{
    char fd[1024];
    struct ListaArchivos *siguiente;
    struct ListaArchivos *anterior;
}typedef listaArchivos;

void imprimirContenido2(listaArchivos *aux){
        while (aux != NULL){
            printf("-%s\n", aux->fd);
            aux=aux->siguiente;
        }
        printf("\n\n");
}

void ingresarArchivo(listaArchivos **x, char *A){
    if(*x == NULL){
        *x=malloc(sizeof(listaArchivos));
        strcpy((*x)->fd, A);
        (*x)->siguiente= NULL;
        (*x)->anterior= NULL;
    }
    else{
        listaArchivos *aux = *x;
        while(aux->siguiente != NULL){
            aux= aux->siguiente;
        }
        aux->siguiente = malloc(sizeof(listaArchivos));
        aux->siguiente->anterior= aux;
        aux->siguiente->siguiente= NULL;
        strcpy(aux->siguiente->fd,A);
    }
}

void eliminarArchivo(listaArchivos **x, int o){
    listaArchivos *aux= *x;
    for (int i=0; i < o; i++){
        aux=aux->siguiente;
    }
    if(aux != NULL){
        if(aux == *x){
            *x= (*x)->siguiente;
            if (*x != NULL)
                (*x)->anterior= NULL;
            free(aux);
        }
        else{
            if (aux->siguiente != NULL)
                aux->siguiente->anterior = aux->anterior;
            if (aux ->anterior != NULL)
                aux->anterior->siguiente = aux->siguiente;
            free(aux);
        }
    }
}
void eliminarArchivo2(listaArchivos **x, char *o){
    listaArchivos *aux= *x;
    while ((aux != NULL) && (strcmp(aux->fd, o) != 0)){
        aux=aux->siguiente;
    }
    if(aux != NULL){
        if(aux == *x){
            *x= (*x)->siguiente;
            if (x != NULL)
                (*x)->anterior= NULL;
            free(aux);
        }
        else{
            if (aux->siguiente != NULL)
                aux->siguiente->anterior = aux->anterior;
            if (aux ->anterior != NULL)
                aux->anterior->siguiente = aux->siguiente;
            free(aux);
        }
    }
}

int ListaALength(listaArchivos *x){
    int i=0;
    while (x != NULL){
        x=x->siguiente;
        i++;
    }
    return i;
}

int busquedaFile(listaArchivos *l, char *fd){
    int x= -1;
    while(l != NULL){
        if (strcmp(l->fd, fd) == 0)
            return x;
        l=l->siguiente;
        x++;
    }
    return -1;
}

void eliminarListaArchivo(listaArchivos **x){
    listaArchivos *aux;
    while (*x != NULL){
        aux=*x;
        *x= (*x)->siguiente;
        free(aux);
    }
}

char *getPath(listaArchivos *x, int o){
    for (int i=0; i < o; i++){
        x=x->siguiente;
    }
    if (x!= NULL)
        return x->fd;
    return "";
}
