#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <pthread.h>

struct persona
{
    char nombre[20];
    char ocupacion[20];
    int edad;
};
struct parametros1
{
    struct persona *espacios;
    int cont;
    char nombreArchivo[20];
};
void swap(struct persona *xp, struct persona *yp)
{
    struct persona temp = *xp;
    *xp = *yp;
    *yp = temp;
}
void bubbleSort(struct persona *Registros, int cantElementos)
{
    int i, j;
    for (i = 0; i < cantElementos - 1; i++)
        for (j = 0; j < cantElementos - i - 1; j++)
            if (Registros[j].ocupacion[0] < Registros[j + 1].ocupacion[0])
                swap(&Registros[j], &Registros[j + 1]);
}
void *printInv(void *parametros)
{
    struct parametros1 *p = (struct parametros1 *)parametros;
    FILE *archivo3 = fopen(p->nombreArchivo, "w+");
    for (int i = (p->cont) - 1; i >= 0; i--)
    {
        fprintf(archivo3, "%s %s %d\n", (p->espacios + i)->nombre, (p->espacios + i)->ocupacion, (p->espacios + i)->edad);
    }
    fclose(archivo3);
    return 0;
}
void *printOrder(void *parametros)
{
    struct parametros1 *p2 = (struct parametros1 *)parametros;
    FILE *archivo2 = fopen(p2->nombreArchivo, "w+");
    bubbleSort(p2->espacios,p2->cont);
    for (int i = (p2->cont) - 1; i >= 0; i--)
    {
        fprintf(archivo2, "%s %s %d\n", (p2->espacios + i)->nombre, (p2->espacios + i)->ocupacion, (p2->espacios + i)->edad);
    }
    fclose(archivo2);
    return 0;
}
int main(int argc, char const *argv[])
{
    struct persona *espacio1 = calloc(100,sizeof(struct persona));
    struct persona *espacio2 = calloc(100,sizeof(struct persona));
    FILE *archivo = fopen(argv[1], "r");
    char c;
    int contRegistros = 0;
    // Contar Lineas
    for (c = getc(archivo); c != EOF; c = getc(archivo))
        if (c == '\n')
            contRegistros = contRegistros + 1;
    contRegistros++;
    rewind(archivo);
    for (int i = 0; i < contRegistros; i++)
    {
        fscanf(archivo, "%s", (espacio1 + i)->nombre);
        fscanf(archivo, "%s", (espacio1 + i)->ocupacion);
        fscanf(archivo, "%d", &(espacio1 + i)->edad);
    }
    rewind(archivo);
    for (int i = 0; i < contRegistros; i++)
    {
        fscanf(archivo, "%s", (espacio2 + i)->nombre);
        fscanf(archivo, "%s", (espacio2 + i)->ocupacion);
        fscanf(archivo, "%d", &(espacio2 + i)->edad);
    }
    printf("|%-20s|%-20s|Edad|\n", "Nombre", "Ocupacion");
    for (int i = 0; i < contRegistros; i++)
    {
        printf(" %-20s %-20s %d\n", (espacio1 + i)->nombre, (espacio1 + i)->ocupacion, (espacio1 + i)->edad);
    }
    pthread_t hilos_ids[2]; 
    struct parametros1 hilo1_param;
    struct parametros1 hilo2_param;

    hilo1_param.cont = contRegistros;
    hilo1_param.espacios = espacio1;
    strcpy(hilo1_param.nombreArchivo, argv[2]);

    hilo2_param.cont = contRegistros;
    hilo2_param.espacios = espacio2;
    strcpy(hilo2_param.nombreArchivo, argv[3]);

    pthread_create(&hilos_ids[0], NULL, &printInv, &hilo1_param); //No iniciar en 1 
    pthread_create(&hilos_ids[1], NULL, &printOrder, &hilo2_param);

    pthread_join(hilos_ids[0], NULL);                             //No iniciar en 1 
    pthread_join(hilos_ids[1], NULL);


    FILE *archivo2 = fopen(argv[2], "r");
    FILE *archivo3 = fopen(argv[3], "r");
    printf("Orden inverso\n");
    printf("|%-20s|%-20s|Edad|\n", "Nombre", "Ocupacion\n");
    for (int i = 0; i < contRegistros; i++)
    {
        char nombre[20];
        char ocupacion[20];
        int edad;
        fscanf(archivo2, "%s", nombre);
        fscanf(archivo2, "%s", ocupacion);
        fscanf(archivo2, "%d", &edad);
        printf(" %-20s %-20s %d\n",nombre,ocupacion,edad);
    }
    printf("Orden Alfabetico\n");
    printf("|%-20s|%-20s|Edad|\n", "Nombre", "Ocupacion\n");
    for (int i = contRegistros - 1; i >= 0; i--)
    {
        char nombre[20];
        char ocupacion[20];
        int edad;
        fscanf(archivo3, "%s", nombre);
        fscanf(archivo3, "%s", ocupacion);
        fscanf(archivo3, "%d", &edad);
        printf(" %-20s %-20s %d\n",nombre,ocupacion,edad);
    }
    return 0;
}
