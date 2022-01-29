#ifndef DECLARACIONES_H
#define DECLARACIONES_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

#define minimo(x, y) ( ( (x) < (y) ) ?  (x) : (y) )
#define TAM_LINEA 50

typedef struct s_nodo
{
    void *info;
    unsigned tamInfo;
    struct s_nodo *sig,
                  *ant;
}t_nodo;

typedef t_nodo* t_lista;


typedef struct
{
    int dni;
    char apyn[31];
    int cantMat;
    int notas[50];
    int carrera;
}t_alum;


void crearLista(t_lista *l);
int ponerEnListaOrdenada(t_lista *l, const void *d, unsigned cantBy,
                         int (*cmp)(const void *d1, const void *d2));

int cargarLista(t_lista *l, FILE *pf, int (*cmp)(const void *d1, const void* d2));
int recorridoAsc(const t_lista *l, int (*cmp)(const void *d1, const void *d2));
int recorridoDesc(const t_lista *l, int (*cmp)(const void *d1, const void *d2));

void trozarCamposLV(char *cad, t_alum *alum);
void suma(const void *d1, float* sumaNotas);
void mostrar(const void *d1, float prom, int cantAlum);

int cmpMatYCarr(const void* d1, const void* d2);
int cmpCarrYMat(const void* d1, const void* d2);
int cmpMat(const void* d1, const void* d2);
int cmpCarr(const void* d1, const void* d2);


#endif // DECLARACIONES_H
