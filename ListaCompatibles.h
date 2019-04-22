#include "ListaArchivos.h"
#include <dirent.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

struct ListaCompatibles{
    struct ListaArchivos *Compat;
    struct ListaCompatibles *siguiente;
    struct ListaCompatibles *anterior;
}typedef listaCompatibles;

void ingresarArchivos(listaArchivos **archivos,listaCompatibles **x){
    if(*x == NULL){
        *x=malloc(sizeof(listaCompatibles));
        (*x)->Compat=*archivos;
        (*x)->siguiente= NULL;
        (*x)->anterior= NULL;
    }
    else{
        listaCompatibles *aux = *x;
        while(aux->siguiente != NULL){
            aux= aux->siguiente;
        }
        aux->siguiente = (listaCompatibles *) malloc(sizeof(listaCompatibles));
        aux->siguiente->anterior= aux;
        aux->siguiente->siguiente= NULL;
        (aux)->siguiente->Compat=*archivos;
    }
}

void eliminarCompatible(listaCompatibles **x, int o){
    listaCompatibles *aux= *x;
    for (int i=0; ((i<o) && (aux != NULL)); i++){
        aux=aux->siguiente;
    }
    if(aux != NULL){
        if(aux == *x){
            *x= (*x)->siguiente;
            (*x)->anterior= NULL;
            eliminarListaArchivo(&(aux->Compat));
            free(aux);
        }
        else{
            aux->siguiente->anterior = aux->anterior;
            aux->anterior->siguiente = aux->siguiente;
            eliminarListaArchivo(&(aux->Compat));
            free(aux);
        }
    }
}

void eliminarCompatible2(listaCompatibles **x, listaCompatibles *o){
    listaCompatibles *aux= *x;
    while (aux != o){
        aux= aux->siguiente;
    }
    if(aux != NULL){
        if(aux == *x){
            *x= (*x)->siguiente;
            if ((*x)!=NULL)
                (*x)->anterior= NULL;
            eliminarListaArchivo(&(aux->Compat));
            free(aux);
        }
        else{
            if (aux->siguiente != NULL)
                aux->siguiente->anterior = aux->anterior;
            if(aux->anterior != NULL)
                aux->anterior->siguiente = aux->siguiente;
            if (aux->Compat != NULL)
                eliminarListaArchivo(&(aux->Compat));
            free(aux);
        }
    }
}

void imprimirContenido(listaCompatibles *x){
    while(x != NULL){
        listaArchivos *aux= x->Compat;
        while (aux != NULL){
            printf("-%s\n", aux->fd);
            aux=aux->siguiente;
        }
        printf("\n\n");
        x= x->siguiente;
    }
}

int ListaCLength(listaCompatibles *x){
    int i=0;
    while (x != NULL){
        x=x->siguiente;
        i++;
    }
    return i;
}

void eliminarListaCompatibles(listaCompatibles **x){
    listaCompatibles *aux;
    while (*x != NULL){
        aux=*x;
        *x= (*x)->siguiente;
        eliminarListaArchivo(&(aux->Compat));
        free(aux);
    }
}