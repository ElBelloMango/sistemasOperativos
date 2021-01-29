#include <stdio.h>
#include <stdlib.h>
#include <string.h>
char encrypt(char caracter);
char encrypt(char caracter){
    return(caracter+0x11);
}
int main(void)
{
    FILE *archEntrada;
    FILE *archSalida;
    
    char funcion[20];
    char entrada[20];
    char salida[20];
    printf("ingrese la funcion para encriptar (sum)\n");
    scanf("%s",funcion);
    getc(stdin);
    printf("ingrese el archivo a encriptar (original.txt)\n");
    scanf("%s",entrada);
    getc(stdin);
    printf("ingrese el archivo de salida (encriptado.txt)\n");
    scanf("%s",salida);
    getc(stdin);

    char (*encFunc)(char);
    if (strncmp("sum", funcion,3) == 0)
    {
        encFunc=&encrypt;
    }
    

    archEntrada = fopen(entrada, "r");
    archSalida =fopen(salida,"w+");

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
