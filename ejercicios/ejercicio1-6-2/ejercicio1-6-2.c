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

int main(void)
{
    FILE *archivo;
    FILE *archivo2;

    int contMaterias;

    char (*espacioNombres)[30];
    double *espacioNotas;
    int *espacioCreditos;

    archivo = fopen("entrada.txt", "r");
    archivo2 =fopen("salida.txt","w+");

    char Last = 'c';
    char linea[20];
    while (Last!=EOF)
    {
        omitirPalabra(archivo);
        fscanf(archivo, "%s", linea);
        omitirPalabra(archivo);
        fscanf(archivo, "%s", linea);
        omitirPalabra(archivo);
        fscanf(archivo, "%s", linea);
        contMaterias++;
        Last = checkEOF(Last,archivo);
    }
    espacioNombres = (char (*)[30])(malloc(sizeof(char[30])*contMaterias));
    espacioNotas = (double *)(malloc(sizeof(double)*contMaterias));
    espacioCreditos = (int *)(malloc(sizeof(int)*contMaterias));
    rewind(archivo);
    for (int i = 0; i < contMaterias; i++)
    {
        omitirPalabra(archivo);
        fscanf(archivo,"%s",(espacioNombres+i));
        omitirPalabra(archivo);
        fscanf(archivo,"%lf",(double *)(espacioNotas+i));
        omitirPalabra(archivo);
        fscanf(archivo,"%d",(int *)(espacioCreditos+i));
        printf("Materia: %s de: %d creditos y con nota: %4.1lf registrada con exito\n",espacioNombres+i, *(espacioCreditos+i),*(espacioNotas+i));
    }
     
    double totalNotas;
    int totalCreditos;
    double promedioPonderado;

    fprintf(archivo2,"|#|   Materia|Nota|Creditos|\n");
    for (int i = 0; i < contMaterias; i++)
    {
        fprintf(archivo2,"|%d|%10.10s|%4.1lf|       %1d|\n",i+1,(espacioNombres+i),*(espacioNotas+i),*(espacioCreditos+i));
    }
    for (int i = 0; i < contMaterias; i++)
    {
        totalNotas += *(espacioNotas+i);
        totalCreditos += *(espacioCreditos+i);
        promedioPonderado += *(espacioNotas+i)*(*(espacioCreditos+i));
    }
    
    fprintf(archivo2,"Promedio del semestre: %f\n",totalNotas/contMaterias);
    fprintf(archivo2,"Total creditos: %d\n",totalCreditos);
    fprintf(archivo2,"Promedio Ponderado: %f\n",promedioPonderado/totalCreditos);  
    
    fclose(archivo);
    fclose(archivo2);
    free(espacioCreditos);
    free(espacioNombres);
    free(espacioNotas);
    return 0;
}
