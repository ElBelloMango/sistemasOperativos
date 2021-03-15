#include <stdio.h>
#include <string.h>
#include <stdlib.h>
struct claveValor
{
    char clave[20];
    int valor;
}; 
void swap(struct claveValor *xp, struct claveValor *yp) 
{ 
    struct claveValor temp = *xp; 
    *xp = *yp; 
    *yp = temp; 
} 
void bubbleSort(struct claveValor *Registros, int cantElementos) 
{ 
   int i, j; 
   for (i = 0; i < cantElementos-1; i++)       
       for (j = 0; j < cantElementos-i-1; j++)  
           if (Registros[j].valor < Registros[j+1].valor) 
              swap(&Registros[j], &Registros[j+1]); 
}
int main(int argc, char const *argv[])
{
    struct claveValor *espacio = malloc(sizeof(struct claveValor) * 100);
    int contRegistros = 0;
    char linea[50];
    char lineaAnt[50];
    char c;
    FILE *archivo = fopen(argv[1], "r");
    FILE *archivo2 = fopen(argv[2], "w+");
    if (archivo == NULL)
    {
        perror("Error: ");
        return EXIT_FAILURE;
    }
    // Contar Lineas
    for (c = getc(archivo); c != EOF; c = getc(archivo)) 
        if (c == '\n')
            contRegistros = contRegistros + 1; 
    contRegistros++;
    rewind(archivo);
    for (int i = 0; i < contRegistros; i++)
    {
        fscanf(archivo, "%s", (espacio+i)->clave);
        fscanf(archivo, "%d", &(espacio+i)->valor);
    }
    printf("Antes del sort\n");
    printf("|clave |valor |\n");
    for (int i = 0; i < contRegistros; i++)
    {
        printf("%s\t%d\t\n", (espacio + i)->clave,(espacio + i)->valor);
    }
    bubbleSort(espacio,contRegistros);
    printf("Luego del sort\n");
    printf("|clave |valor |\n");
    for (int i = 0; i < contRegistros; i++)
    {
        printf("%s\t%d\t\n", (espacio + i)->clave,(espacio + i)->valor);
    }
    for (int i = 0; i < contRegistros; i++)
    {
        fprintf(archivo2, "%s %d\n", (espacio + i)->clave, (espacio + i)->valor);
    }
    fclose(archivo);
    fclose(archivo2);
    free(espacio);
    return 0;
}
