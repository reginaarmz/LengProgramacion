/*
    Autor: Ramírez Ramírez Aura Regina
    Proyecto: De Gramática Regular a Expresión Regular
*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_LINE_LENGHT 100

// Estructura de Nodo

typedef struct NODO {
    char *regla;
    char *prod;
    struct NODO *sig;  // Puntero sig
    struct NODO *ant;  // Puntero al nodo anterior
} NODO;

NODO* crearNodo(const char *regla, const char *prod);
void agregNodo(NODO **cab, const char *regla, const char *prod);
void liberarLinkedLista(NODO *cab);
NODO* crearLinkedLista(FILE *file);
void imprimirLista(NODO *cab);

void dividirLinea(const char *linea, char *regla, char *prod);
NODO* encontrarNodo(NODO *cab, const char *regla);
void agregProduc(NODO *nod, const char *prod);
void agregActNodo(NODO **cab, const char *regla, const char *prod);

NODO* crearLinkedLista(FILE *file);
void segundoPaso(NODO *cab);
void tercerPaso(NODO *cab);
void reemplazar(NODO *cab);



