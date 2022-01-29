#include "Declaraciones.h"

int main()
{
    FILE *pf;
    t_lista lista;
    char cod;
    int orden;

    pf = fopen("Lote.txt", "rt");
    if(!pf)
        return 1;

    crearLista(&lista);

    do
    {
        printf("\nIngrese A(para 'cantidad de materias y carrera') o "
               "B(para 'cantidad de materias y carrera'): ");
        scanf("%c", &cod);
        cod = toupper(cod);
    }while(cod != 'A' && cod != 'B');

    do
    {
        printf("\nIngrese 1(para orden ascendente) o 2(para orden descendente): ");
        scanf("%d", &orden);
    }while(orden != 1 && orden != 2);

    if(cod == 'A')
    {
        cargarLista(&lista, pf, cmpMatYCarr);
        if(orden == 1)
            recorridoAsc(&lista, cmpMat);
        else
            recorridoDesc(&lista, cmpMat);
    }
    else
    {
        cargarLista(&lista, pf, cmpCarrYMat);
        if(orden == 1)
            recorridoAsc(&lista, cmpCarr);
        else
            recorridoDesc(&lista, cmpCarr);
    }


    fclose(pf);
    return 0;
}
