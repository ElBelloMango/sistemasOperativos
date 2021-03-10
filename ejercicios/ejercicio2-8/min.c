#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

int main(int argc, char const *argv[])
{
    int min = 999999999;
    printf("Se ingresaron %d numeros\n", argc - 1);
    for (int i = 1; i < argc; i++)
    {
        if (atoi(argv[i])<min)
        {
            min = atoi(argv[i]);
        }
    }
    printf("Minimo = %d\n",min);
    exit(EXIT_SUCCESS);
}