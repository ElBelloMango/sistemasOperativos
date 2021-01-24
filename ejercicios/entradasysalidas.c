#include <stdio.h>
#include <stdlib.h>
#include <string.h>
 

void omitirPalabra(FILE *); 

void omitirPalabra(FILE *archivo){
    char L[20]={""};
    fscanf(archivo, "%s", L);
}
char checkEOF(char,FILE *);
char checkEOF(char last, FILE * archivo){
        last = fgetc(archivo);
        last = fgetc(archivo);
        last = fgetc(archivo);
        last = fgetc(archivo);
        return last;
}

int main()
{
    
    FILE *archivo;
    FILE *archivo2;
    char linea[20];
    
    

    archivo = fopen("entrada.txt", "r");
    archivo2 =fopen("salida.txt","w+");
   
    char Last;
    int contMaterias=0;
    while (Last!=EOF)
    {
        omitirPalabra(archivo);
        fscanf(archivo, "%s", linea);
        printf("Materia :%s\n", linea);
        omitirPalabra(archivo);
        fscanf(archivo, "%s", linea);
        printf("Nota :%s\n", linea);
        omitirPalabra(archivo);
        fscanf(archivo, "%s", linea);
        printf("creditos :%s\n", linea);
        contMaterias++;
        Last = checkEOF(Last,archivo);
    }
    fprintf(archivo2,"%d\n",contMaterias);
    fprintf(archivo2,"Materias");
   
    fclose(archivo);

    return 0;
}
