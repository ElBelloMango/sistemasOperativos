#include <stdio.h>
#include <stdlib.h>
#include <string.h>
char deencrypt(char caracter);
char deencrypt(char caracter){
    return(caracter-0x11);
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
    printf("ingrese el archivo a desencriptar (encriptado.txt)\n");
    scanf("%s",entrada);
    getc(stdin);
    printf("ingrese el archivo a desencriptar (pdesencriptado.txt)\n");
    scanf("%s",salida);
    getc(stdin);

    char (*encFunc)(char);
    if (strncmp("sum", funcion,3) == 0)
    {
        encFunc=&deencrypt;
    }
    

    archEntrada = fopen(entrada, "r");
    archSalida =fopen(salida,"w+");

    int Last = fgetc(archEntrada); 
    while (Last!=EOF)
    {
        fprintf(archSalida,"%c",(*encFunc)(Last));
        Last = fgetc(archEntrada); 
    }
    fclose(archEntrada);
    fclose(archSalida);

    return 0;
}