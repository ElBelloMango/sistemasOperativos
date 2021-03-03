#include <stdio.h>
#include <stdlib.h>

int main(int argc, char *argv[])
{
    int min = 999999999;
    int max = 0;
    int sumatoria = 0;
    printf("Se ingresaron %d numeros\n", argc - 1);
    for (int i = 1; i < argc; i++)
    {
        printf("Numero %d : %d\n", i, atoi(argv[i]));
        if (atoi(argv[i])<min)
        {
            min = atoi(argv[i]);
        }
        if (atoi(argv[i])>max)
        {
            max = atoi(argv[i]);
        }
        sumatoria = sumatoria + atoi(argv[i]);
    }
    double promedio = sumatoria/(argc-1);
    printf("Minimo = %d\n",min);
    printf("Maximo = %d\n",max);
    printf("Sumatoria = %d\n",sumatoria);
    printf("Promedio = %f\n",promedio);
    exit(EXIT_SUCCESS); // exit(EXIT_FAILURE) en caso de error
}