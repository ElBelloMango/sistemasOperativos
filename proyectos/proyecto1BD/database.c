#include <stdio.h>
#include <string.h>
#include <stdlib.h>
typedef struct estudiante
{
    int cedula;
    char nombre[30];
    int semestre;
};

struct estudiante* mkdb(char* nombre,int size);
struct estudiante* mkdb(char* nombre,int size)
{
    return (struct estudiante *)malloc(sizeof(struct estudiante)*size);
}

int main(int argc, char const *argv[])
{
    char comando[20];
    printf("Ingrese un comando\n");
    scanf("%s",comando);
    getc(stdin);
    printf("%s\n",comando);
    struct estudiante *espaciobd;
    if (strncmp("mkdb",comando,4)==0)
    {
        char nombre[20];
        int tamano;
        fscanf(stdin,"%s",nombre);
        fscanf(stdin,"%d",&tamano);
        fgets("nan","%s[^\n]",stdin); //Eliminar argumentos extras.
        espaciobd = mkdb(nombre,tamano);
         
        strcpy(espaciobd->nombre, "Camilo" );
        espaciobd->cedula=122021221;
        espaciobd->semestre=3;
        for (int i = 0; i < tamano; i++)
        {
            printf("%s\n",(espaciobd+i)->nombre);
            printf("%d\n",(espaciobd+i)->cedula);
            printf("%d\n",(espaciobd+i)->semestre);
        }
        
    }
    else if(strncmp("loaddb",comando,6)==0)
    {
        char nombre[20];
        fscanf(stdin,"%s",nombre);
        fgets("nan","%s[^\n]",stdin); //Eliminar argumentos extras.
    }
    
    
    return 0;
}
