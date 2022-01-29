#include "Declaraciones.h"

void crearLista(t_lista *l)
{
    *l = NULL;
}

int cargarLista(t_lista *l, FILE *pf, int (*cmp)(const void *d1, const void* d2))
{
    char linea[TAM_LINEA];
    t_alum alum;

    while(fgets(linea, TAM_LINEA, pf))
    {
        trozarCamposLV(linea, &alum);
        ponerEnListaOrdenada(l, &alum, sizeof(t_alum), cmp);
    }
    return 1;
}

void trozarCamposLV(char *cad, t_alum *alum)
{
    int i=0;
    char *aux = strchr(cad, '\n');
    *aux = '\0';

    aux = strrchr(cad, '|');
    sscanf(aux+1, "%d", &alum->carrera);
    *aux = '\0';

    while((aux = strrchr(cad, '/')))
    {
        sscanf(aux+1, "%d", &alum->notas[i]);
        *aux = '\0';
        i++;
    }

    aux = strrchr(cad, '|');
    sscanf(aux+1, "%d", &alum->notas[i]);
    *aux = '\0';

    aux = strrchr(cad, '|');
    sscanf(aux+1, "%d", &alum->cantMat);
    *aux = '\0';

    aux = strrchr(cad, '|');
    strcpy(alum->apyn, aux+1);
    *aux = '\0';

    sscanf(cad, "%d", &alum->dni);
}

int ponerEnListaOrdenada(t_lista *l, const void *d, unsigned cantBy,
                         int (*cmp)(const void *d1, const void *d2))
{
    t_nodo *actual = *l,
           *auxAnt,
           *auxSig,
           *nue;

    int comp;

    if(*l)
    {
        while((comp = cmp(d, actual->info)) > 0 && actual->sig != NULL)
            actual = actual->sig;
        while((comp = cmp(d, actual->info)) < 0 && actual->ant != NULL)
            actual = actual->ant;


        if(comp > 0)
        {
            auxSig = actual->sig;
            auxAnt = actual;
        }
        else
        {
            auxSig = actual;
            auxAnt = actual->ant;
        }
    }
    else
    {
        auxAnt = NULL;
        auxSig = NULL;
    }

    nue = (t_nodo*)malloc(sizeof(t_nodo));
    if(!nue)
        return 0;
    nue->info = malloc(cantBy);
    if(!nue->info)
    {
        free(nue);
        return 0;
    }

    memcpy(nue->info, d, cantBy);
    nue->tamInfo = cantBy;

    nue->ant = auxAnt;
    nue->sig = auxSig;

    if(auxAnt)
        auxAnt->sig = nue;
    if(auxSig)
        auxSig->ant = nue;

    *l = nue;

    return 1;
}


int recorridoAsc(const t_lista *l, int (*cmp)(const void *d1, const void *d2))
{
    int cantAlum = 1;
    float sumaNotas = 0,
          promedio;

    if(!*l)
        return 0;

    while((*l)->ant)
        l = &(*l)->ant;

    while(*l)
    {
        while((*l)->sig && cmp((*l)->info, (*l)->sig->info) == 0)
        {
            cantAlum++;
            suma((*l)->info, &sumaNotas);
            l = &(*l)->sig;
        }

        suma((*l)->info, &sumaNotas);
        promedio = sumaNotas/cantAlum;

        mostrar((*l)->info, promedio, cantAlum);

        l = &(*l)->sig;
        sumaNotas = 0;
    }
    return 1;
}

int recorridoDesc(const t_lista *l, int (*cmp)(const void *d1, const void *d2))
{
    int cantAlum = 1;
    float sumaNotas = 0,
          promedio;

    if(!*l)
        return 0;

    while((*l)->sig)
        l = &(*l)->sig;

    while(*l)
    {
        while((*l)->ant && cmp((*l)->info, (*l)->ant->info) == 0)
        {
            cantAlum++;
            suma((*l)->info, &sumaNotas);
            l = &(*l)->ant;
        }

        suma((*l)->info, &sumaNotas);
        promedio = sumaNotas/cantAlum;

        mostrar((*l)->info, promedio, cantAlum);

        l = &(*l)->ant;
        sumaNotas = 0;
    }
    return 1;
}

void suma(const void *d1, float* sumaNotas)
{
    t_alum *info = (t_alum*)d1;
    int i;

    for(i=0 ; i < info->cantMat ; i++)
        *sumaNotas += info->notas[i];
}

void mostrar(const void *d1, float prom, int cantAlum)
{
    t_alum *info = (t_alum*)d1;
    printf("\n[Cantidad Materias : %d / Carrera : %d] --> Cantidad Alumnos = %d"
           " y Promedio General : %.2f\n", info->cantMat, info->carrera, cantAlum, prom);
}


int cmpMatYCarr(const void* d1, const void* d2)
{
    t_alum *alum1 = (t_alum*)d1,
            *alum2 = (t_alum*)d2;
    int comp;
    if((comp = alum1->cantMat - alum2->cantMat)==0)
        return alum1->carrera - alum2->carrera;
    return comp;
}

int cmpCarrYMat(const void* d1, const void* d2)
{
    t_alum *alum1 = (t_alum*)d1,
            *alum2 = (t_alum*)d2;
    int comp;
    if((comp = alum1->carrera - alum2->carrera)==0)
        return alum1->cantMat - alum2->cantMat;
    return comp;
}

int cmpMat(const void* d1, const void* d2)
{
    t_alum *alum1 = (t_alum*)d1,
            *alum2 = (t_alum*)d2;
    return alum1->cantMat - alum2->cantMat;
}

int cmpCarr(const void* d1, const void* d2)
{
    t_alum *alum1 = (t_alum*)d1,
            *alum2 = (t_alum*)d2;

    return alum1->carrera - alum2->carrera;
}
