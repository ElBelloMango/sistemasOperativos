#include <stdio.h>
#include <stdlib.h>
#include <string.h>
char encrypt(char caracter);
char encrypt(char caracter){
    return(caracter+0x11);
}

int main(int argc, char const *argv[])
{
    FILE *archEntrada;
    FILE *archSalida;
    

    char (*encFunc)(char);
    if (strncmp("sum", argv[1],3) == 0)
    {
        encFunc=&encrypt;
    }
    

    archEntrada = fopen(argv[2], "r");
    archSalida =fopen(argv[3],"w+");

    int Last = fgetc(archEntrada); 
    while (Last!=EOF)
    {
        fputc((*encFunc)(Last),archSalida);
        Last = fgetc(archEntrada); 
    }
    fclose(archEntrada);
    fclose(archSalida);

    return 0;
}
