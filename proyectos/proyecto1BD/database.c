#include <stdio.h>
#include <string.h>
#include <stdlib.h>

typedef struct estudiante
{
    int cedula;
    char nombre[30];
    int semestre;
};

void mkreg(struct estudiante *bd, int cedula, char *nombre, int semestre, int *nroRegistro);
void mkreg(struct estudiante *bd, int cedula, char *nombre, int semestre, int *nroRegistro)
{
    strcpy((bd + *nroRegistro)->nombre, nombre);
    (bd + *nroRegistro)->cedula = cedula;
    (bd + *nroRegistro)->semestre = semestre;
    (*nroRegistro)++;
}
struct estudiante* mkdb(char *nombre, int size);
struct estudiante* mkdb(char *nombre, int size)
{
    return (struct estudiante *)malloc(sizeof(struct estudiante) * size);
}

int main(int argc, char const *argv[])
{
    int contadorRegistro = 0;
    int tamanobd = 0;
    char comando[20];
    struct estudiante *espaciobd;
    do
    {
        printf("Ingrese un comando\n");
        fscanf(stdin,"%s", comando);
        getc(stdin);
        if (strncmp("mkdb", comando,4) == 0)
        {
            char nombre[20];
            fscanf(stdin, "%s", nombre);
            fscanf(stdin, "%d", &tamanobd); 
            // fgets("nan", "%s[^\n]", stdin); //Eliminar argumentos extras.
            espaciobd = mkdb(nombre, tamanobd);
        }
        else if (strncmp("mkreg", comando, 5) == 0)
        {
            char nombre[20];
            int cedula;
            int semestre;
            fscanf(stdin, "%s", nombre);
            fscanf(stdin, "%d", &cedula);
            fscanf(stdin, "%d", &semestre);
            // fgets("nan", "%s[^\n]", stdin); //Eliminar argumentos extras.
            mkreg(espaciobd, cedula, nombre, semestre, &contadorRegistro);
        }
        else if (strncmp("savedb", comando, 6) == 0)
        {
            char nombre[20];
            fscanf(stdin, "%s", nombre);
            // fgets("nan", "%s[^\n]", stdin); //Eliminar argumentos extras.
            FILE *archivo2=fopen(nombre,"w+");
            fprintf(archivo2,"Tamaño: %d\n",tamanobd);
            fprintf(archivo2,"|Nombre |Cedula |Semestre |\n");
            for (int i = 0; i < contadorRegistro; i++)
            {
                fprintf(archivo2, "%s %d %d\n", (espaciobd + i)->nombre, (espaciobd + i)->cedula, (espaciobd + i)->semestre);
            }
        }
        else if (strncmp("loaddb", comando, 6) == 0)
        {
            
            char nombre[20];
            fscanf(stdin, "%s", nombre);
            // fgets("nan", "%s[^\n]", stdin); //Eliminar argumentos extras.
            char LTrash[50];
            char linea[50];
            char lineaAnt[50];
            char nombreEstudiante[30];
            int contRegistros = 0;
            int cedula;
            int semestre;
            FILE *archivo=fopen(nombre,"r");
            fscanf(archivo,"%s",LTrash); //Omitimos la primer palabra
            fscanf(archivo,"%d",&tamanobd); //guardamos el tamaño de la BD
            fgets(lineaAnt, "%s[^\n]", archivo); //Omitir primera linea.
            fgets(lineaAnt, "%s[^\n]", archivo); //Omitir Segunda linea.
            while (1)
            {
                fgets(linea, "%s[^\n]", archivo);
                if (strncmp(lineaAnt, linea, 50)==0)
                {
                    break;
                }
                printf("%s\n",linea);
                strcpy(lineaAnt,linea);
                contRegistros++;
            }
            contadorRegistro = contRegistros;
            printf("%d\n",contRegistros);
            espaciobd = mkdb(nombre, tamanobd);
            rewind(archivo);
            fgets(lineaAnt, "%s[^\n]", archivo); //Omitir primera linea.
            fgets(lineaAnt, "%s[^\n]", archivo); //Omitir Segunda linea.
            for (int i = 0; i < contRegistros;i++)
            {
                fscanf(archivo,"%s",nombreEstudiante);
                fscanf(archivo,"%d",&cedula);
                fscanf(archivo,"%d",&semestre);
                // mkreg(espaciobd, cedula, nombreEstudiante, semestre, &i);
                strcpy((espaciobd + i)->nombre, nombreEstudiante);
                (espaciobd + i)->cedula = cedula;
                (espaciobd + i)->semestre = semestre;
            }
        }
        else if (strncmp("readall", comando, 7) == 0)
        {
            for (int i = 0; i < tamanobd; i++)
            {
                printf("%s\n", (espaciobd + i)->nombre);
                printf("%d\n", (espaciobd + i)->cedula);
                printf("%d\n", (espaciobd + i)->semestre);
            }
        }

        else if (strncmp("exit", comando, 4) == 0)
        {
            break;
        }

    } while (1);

    return 0;
}
