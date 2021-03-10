#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

int main(int argc, char const *argv[])
{
    int sumatoria = 0;
    printf("Se ingresaron %d numeros\n", argc - 1);
    for (int i = 1; i < argc; i++)
    {
        sumatoria = sumatoria + atoi(argv[i]);
    }
    double promedio = sumatoria/(argc-1);
    printf("Promedio = %f\n",promedio);
    exit(EXIT_SUCCESS);
}
