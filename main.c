#include "main.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

//Funcion para crear un nodo

NODO* creaNodo(const char *regla, const char *prod)
{
    NODO *nuevoN = (NODO *)malloc(sizeof(NODO));
    nuevoN->regla= strdup(regla);
    nuevoN->prod= strdup(prod);
    nuevoN->sig= NULL;

    return(nuevoN);
}

//Función para encontar un nodo por regla identidad

NODO* encontrarNodo(NODO *cab, const char *regla)
{
    NODO *actual=cab;

    while(actual)
    {
        if(strcmp(actual->regla, regla)==0)
            return(actual);
        
        actual= actual->sig;
    }
    return(NULL); //se retorna NULL si no lo encontró

}

//Funcion para agregar producción 

void agregProduc(NODO *nod, const char *prod)
{
    size_t nuevoTam= strlen(nod->prod) + strlen(prod) + 4;
    nod->prod= (char *)realloc(nod->prod, nuevoTam);

    strcat(nod->prod, " | ");
    strcat(nod->prod, prod);

}

//Función para agregar un nuevo nodo o actualizar uno existente

void agregActNodo(NODO **cab, const char *regla, const char *prod)
{
    NODO *exisNodo= encontrarNodo(*cab, regla);

    if(exisNodo)
    {
        agregProduc(exisNodo, prod); //Si lo encontró, agrega la producción
    }
    else{
        NOO *nuevoN= creaNodo(regla, prod);

        if(!*cab)
            *cab= nuevoN;
        else{
            NODO *aux=*cab;

            while (aux->sig)
            {
                aux=aux->sig;
            }

            aux->sig= nuevoN;
            
        }
    }
}

//Funcion para librerar un linked de la lista

void liberarLinkedLista(NODO *cab)
{
    NODO *actual= cab;
    NODO *sigNodo;

    while (actual)
    {
        sigNodo= actual->sig;
        free(actual->regla);
    }
    
}
