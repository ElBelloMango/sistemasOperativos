#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

int main(int argc, char const *argv[])
{
    int max = 0;
    printf("Se ingresaron %d numeros\n", argc - 1);
    for (int i = 1; i < argc; i++)
    {
        if (atoi(argv[i])>max)
        {
            max = atoi(argv[i]);
        }
    }
    printf("Maximo = %d\n",max);
    exit(EXIT_SUCCESS);
}