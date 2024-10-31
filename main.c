/*
    Autor: Ramírez Ramírez Aura Regina
    Proyecto: De Gramática Regular a Expresión Regular
*/

#include "main.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>


//Funcion para crear un nodo
NODO* creaNodo(const char *regla, const char *prod)
{
    NODO *nuevoN = (NODO *)malloc(sizeof(NODO));
    nuevoN->regla = strdup(regla);
    nuevoN->prod = strdup(prod);
    nuevoN->sig = NULL;
    nuevoN->ant = NULL;

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

// Función para agregar producción
void agregProduc(NODO *cab, const char *prod)
{

    if (!strstr(cab->prod, prod)) {
        size_t nuevTam = strlen(cab->prod) + strlen(prod) + 4;
        cab->prod = (char *)realloc(cab->prod, nuevTam);

        if (strlen(cab->prod) > 0) {
            strcat(cab->prod, " | ");
        }
        strcat(cab->prod, prod);
    }
}


//Función para agregar un nuevo nodo o actualizar uno existente
void agregActNodo(NODO **cab, const char *regla, const char *prod)
{
    NODO *exisNodo = encontrarNodo(*cab, regla);

    if (exisNodo)
        agregProduc(exisNodo, prod);
    else
    {
        NODO *nuevoN = creaNodo(regla, prod);
        if (!*cab)
            *cab = nuevoN;
        else
        {
            NODO *aux = *cab;

            while (aux->sig)
                aux = aux->sig;

            aux->sig = nuevoN;
            nuevoN->ant = aux;
        }
    }
}

//Funcion para librerar un linked list
void liberarLinkedLista(NODO *cab)
{
    NODO *actual= cab;
    NODO *sigNodo;

    while (actual)
    {
        sigNodo = actual->sig;
        free(actual->regla);
        free(actual->prod);
        free(actual);
        actual = sigNodo;
    }
}

// Función para dividir una línea en identificador de regla y producción
void dividirLinea(const char *linea, char *regla, char *prod)
{
    // Encontrar la posición de "->" en la línea
    const char *delimite = strstr(linea, "->");

    if (delimite != NULL)
    {
        strncpy(regla, linea, delimite - linea);
        regla[delimite - linea] = '\0';

        strcpy(prod, delimite + 2);
    }
}

// Función para crear una Double Linked List
NODO* crearLinkedLista(FILE *file)
{
    NODO *cab = NULL;
    char linea[1000];
    char regla[1000];
    char prod[1000];

    while (fgets(linea, sizeof(linea), file))
    {
        linea[strcspn(linea, "\n")] = '\0';
        dividirLinea(linea, regla, prod);
        agregActNodo(&cab, regla, prod);
    }
    return cab;
}

//Funcion para imprimir Linked List
void imprimirLista(NODO* cab)
{
    NODO *actual = cab;

    while(actual)
    {
        printf("%s -> %s\n", actual->regla, actual -> prod);
        actual = actual->sig;
    }
}

//Función de paso 2
void segundoPaso(NODO *cab)
{
    NODO *actual = cab;

    while (actual)
    {
        char *prod = actual->prod;
        char *symbol = strtok(strdup(prod), " | ");
        char nuevaProd[1000] = "";
        int inicio = 1;
        char aux[1000];

        while (symbol)
        {
            if (strlen(symbol) >= 2 && symbol[strlen(symbol)-1] == actual->regla[0])
            {
                if (!inicio) strcat(nuevaProd, " | ");

                snprintf(aux, sizeof(aux), "{%c}", symbol[0]);
                strcat(nuevaProd, aux);
                if (strlen(symbol) > 2)
                {
                    // Si hay más caracteres entre 'a' y 'A'
                    strcat(nuevaProd, "(");
                    strncat(nuevaProd, symbol + 1, strlen(symbol) - 2);
                    strcat(nuevaProd, ")");
                }
            } else {
                if (!inicio) strcat(nuevaProd, " | ");
                strcat(nuevaProd, symbol);
            }
            inicio = 0;
            symbol = strtok(NULL, " | ");
        }

        //Cambiar la produc.
        free(actual->prod);
        actual->prod = strdup(nuevaProd);

        NODO *siguiente = actual->sig;
        while (siguiente)
        {
            char *pos = strstr(siguiente->prod, actual->regla);

            if (pos)
            {
                char nuevaProd[1000] = "";
                size_t longu = pos - siguiente->prod;
                strncpy(nuevaProd, siguiente->prod, longu);
                strcat(nuevaProd, actual->prod);
                strcat(nuevaProd, pos + strlen(actual->regla));

                free(siguiente->prod);
                siguiente->prod = strdup(nuevaProd);
            }
            siguiente = siguiente->sig;
        }

        actual = actual->sig;
    }
}

//Funcion de paso 3
void tercerPaso(NODO *cab)
{
    // Ir al último nodo
    NODO *actual = cab;
    while (actual->sig)
        actual = actual->sig;

    while (actual)
    {
        // Buscar patrones de la forma A -> aA
        char *prod = actual->prod;
        char *symbol = strtok(strdup(prod), " | ");
        char nuevaProd[1000] = "";
        int inicio = 1;
        char aux[1000];

        while (symbol)
        {
            if (strlen(symbol) >= 2 && symbol[strlen(symbol)-1] == actual->regla[0])
            {

                if (!inicio) strcat(nuevaProd, " | ");

                snprintf(aux, sizeof(aux), "{%c}", symbol[0]);
                strcat(nuevaProd, aux);
                if (strlen(symbol) > 2)
                {
                    strcat(nuevaProd, "(");
                    strncat(nuevaProd, symbol + 1, strlen(symbol) - 2);
                    strcat(nuevaProd, ")");
                }
            }
            else
            {
                if (!inicio) strcat(nuevaProd, " | ");
                    strcat(nuevaProd, symbol);
            }

            inicio = 0;
            symbol = strtok(NULL, " | ");
        }

        //Cambiar la produc.
        free(actual->prod);
        actual->prod = strdup(nuevaProd);

        NODO *ante = actual->ant;

        while (ante)
        {
            char *pos = strstr(ante->prod, actual->regla);

            if (pos)
            {
                char nuevaProd[1000] = "";
                size_t longu = pos - ante->prod;
                strncpy(nuevaProd, ante->prod, longu);
                strcat(nuevaProd, actual->prod);
                strcat(nuevaProd, pos + strlen(actual->regla));

                free(ante->prod);
                ante->prod = strdup(nuevaProd);
            }
            ante = ante->ant;
        }

        actual = actual->ant;
    }
}

// Reemplazo de "{a}" por "a*"
void reemplazar(NODO *cab)
{
    NODO *actual = cab;

    while (actual)
    {
        char *prod = actual->prod;
        char nuevaProd[1000] = " ";
        char *pos = prod;

        while (*pos)
        {
            if (*pos == '{')
            {
                char *fin = strchr(pos, '}');

                if (fin && (fin - pos) == 2)
                {
                    strncat(nuevaProd, pos + 1, 1);
                    strcat(nuevaProd, "*");
                    pos = fin + 1;
                }

                else
                {
                    strncat(nuevaProd, pos, 1);
                    pos++;
                }
            }
            else
            {
                strncat(nuevaProd, pos, 1);
                pos++;
            }

        }

        free(actual->prod);
        actual->prod = strdup(nuevaProd);
        actual = actual->sig;
    }
}

void expresionReg(NODO *cab)
{
    if (cab)
        printf("Expresion Regular: %s\n", cab->prod);
}


int main()
{
    FILE *archivo = fopen("gramatica2.txt","r");
    if(archivo == NULL)
    {
        perror("Error al abrir el archivo");
        return 1;
    }

    NODO *cab = crearLinkedLista(archivo);
    fclose(archivo);

    //Paso 1
    printf("Paso 1: Lectura y agrupación de reglas\n \n");
    imprimirLista(cab);

    //Paso 2
    segundoPaso(cab);
    printf("Paso 2: Combinación de reglas similares\n");
    imprimirLista(cab);

    //Paso 3
    tercerPaso(cab);
    printf("Paso 3: Procesamiento de reglas \n");
    imprimirLista(cab);

    reemplazar(cab);
    imprimirLista(cab);

    expresionReg(cab);

    liberarLinkedLista(cab);

    return 0;
}
