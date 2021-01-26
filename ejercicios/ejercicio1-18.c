#include <stdio.h>
void imprimirArreglo(char *,int);
void imprimirArreglo(char *arreglo,int posiciones)
{
    for (int i = 0; i < posiciones; i++)
    {
        printf("Posicion %d: %c\n",i+1,*(arreglo+i));
    }
}
int main(void)
{
    int posiciones;
    printf("ingrese las posiciones del arreglo\n");
    scanf("%d",&posiciones);
    getc(stdin);
    char arreglo[posiciones];
    for (int i = 0; i < posiciones; i++)
    {
        printf("Ingrese el %d elemento del arreglo\n",i+1);
        scanf("%s",&arreglo[i]);
        getc(stdin);
        printf("Elemento : %c Añadido\n",arreglo[i]);
    }
    imprimirArreglo(arreglo,posiciones);
    int posicion;
    do
    {
        printf("sobreescriba una posicion del arreglo\nIngrese la posicion que desea cambiar\n");
        scanf("%d",&posicion);
        getc(stdin);
        if (posicion>0&&posicion<=posiciones)
        {
            scanf("%1c",&arreglo[posicion-1]);
            getc(stdin);
        }
    } while (posicion<0||posicion>posiciones);
    imprimirArreglo(arreglo,posiciones);
    return 0;
}
