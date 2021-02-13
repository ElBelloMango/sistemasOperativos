#include <stdio.h>
#include <string.h>
#include <stdlib.h>

typedef struct estudiante
{
    int cedula;
    char nombre[30];
    int semestre;
};
struct estudiante *mkdb(char *nombre, int size);
void mkreg(struct estudiante *bd, int cedula, char *nombre, int semestre, int *nroRegistro);
void savedb(FILE *archivo2, struct estudiante *espaciobd, char *nombre, int tamanobd, int contadorRegistro);
struct estudiante *loaddb(FILE *archivo, struct estudiante *espaciobd, int *tamanobd, int *contadorRegistro, char *nombre);
void readall(struct estudiante *bd, int tamanobd);
void readsize(struct estudiante *bd, int tamanobd);
void readreg(struct estudiante *bd, int tamanobd,int cedula);

struct estudiante *mkdb(char *nombre, int size)
{
    return (struct estudiante *)malloc(sizeof(struct estudiante) * size);
}
void mkreg(struct estudiante *bd, int cedula, char *nombre, int semestre, int *nroRegistro)
{
    strcpy((bd + *nroRegistro)->nombre, nombre);
    (bd + *nroRegistro)->cedula = cedula;
    (bd + *nroRegistro)->semestre = semestre;
    (*nroRegistro)++;
}
void savedb(FILE *archivo2, struct estudiante *espaciobd, char *nombre, int tamanobd, int contadorRegistro)
{
    fprintf(archivo2, "Tamaño: %d\n", tamanobd);
    fprintf(archivo2, "|Nombre |Cedula |Semestre |\n");
    for (int i = 0; i < contadorRegistro; i++)
    {
        fprintf(archivo2, "%s %d %d\n", (espaciobd + i)->nombre, (espaciobd + i)->cedula, (espaciobd + i)->semestre);
    }
}
struct estudiante *loaddb(FILE *archivo, struct estudiante *espaciobda, int *tamanobd, int *contadorRegistro, char *nombre)
{
    char LTrash[50];
    char linea[50];
    char lineaAnt[50];
    char nombreEstudiante[30];
    int contRegistros = 0;
    int cedula;
    int semestre;
    fscanf(archivo, "%s", LTrash);       //Omitimos la primer palabra
    fscanf(archivo, "%d", tamanobd);     //guardamos el tamaño de la BD
    fgets(lineaAnt, "%s[^\n]", archivo); //Omitir primera linea.
    fgets(lineaAnt, "%s[^\n]", archivo); //Omitir Segunda linea.
    while (1)
    {
        fgets(linea, "%s[^\n]", archivo);
        if (strncmp(lineaAnt, linea, 50) == 0)
        {
            break;
        }
        printf("%s\n", linea);
        strcpy(lineaAnt, linea);
        contRegistros++;
    }
    *contadorRegistro = contRegistros;
    printf("%d\n", contRegistros);
    espaciobda = mkdb(nombre, *tamanobd);
    rewind(archivo);
    fgets(lineaAnt, "%s[^\n]", archivo); //Omitir primera linea.
    fgets(lineaAnt, "%s[^\n]", archivo); //Omitir Segunda linea.
    for (int i = 0; i < contRegistros; i++)
    {
        fscanf(archivo, "%s", nombreEstudiante);
        fscanf(archivo, "%d", &cedula);
        fscanf(archivo, "%d", &semestre);
        // mkreg(espaciobda, cedula, nombreEstudiante, semestre, &i); //Me jodía los otros ciclos por cambiar directamente el valor de i.
        strcpy((espaciobda + i)->nombre, nombreEstudiante);
        (espaciobda + i)->cedula = cedula;
        (espaciobda + i)->semestre = semestre;
    }
    return espaciobda;
}
void readall(struct estudiante *bd, int tamanobd)
{
    for (int i = 0; i < tamanobd; i++)
    {
        printf("%s\n", (bd + i)->nombre);
        printf("%d\n", (bd + i)->cedula);
        printf("%d\n", (bd + i)->semestre);
    }
}
void readsize(struct estudiante *bd, int tamanobd)
{
    for (int i = 0; i < tamanobd; i++)
    {
        if ((bd + i)->cedula==0)
        {
            printf("La base de datos tiene %d registros de %d disponibles\n",i,tamanobd);
            break;
        }
    }
}
void readreg(struct estudiante *bd, int tamanobd,int cedula)
{
    int found=0;
    for (int i = 0; i < tamanobd; i++)
    {
        if ((bd + i)->cedula==cedula)
        {
            printf("-------------Registro encontrado---------\n");
            printf("%s\n", (bd + i)->nombre);
            printf("%d\n", (bd + i)->cedula);
            printf("%d\n", (bd + i)->semestre);
            found = 1;
            break;
        }
    }
    if(found == 0)
    {
        printf("Registro no encontrado.\n");
    }
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
        fscanf(stdin, "%s", comando);
        getc(stdin);
        if (strncmp("mkdb", comando, 4) == 0)
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
            FILE *archivo2 = fopen(nombre, "w+");
            savedb(archivo2, espaciobd, nombre, tamanobd, contadorRegistro);
        }
        else if (strncmp("loaddb", comando, 6) == 0)
        {

            char nombre[20];
            fscanf(stdin, "%s", nombre);
            // fgets("nan", "%s[^\n]", stdin); //Eliminar argumentos extras. Descartada esta linea por bug con los fgets al declarar un archivo en modo lectura
            FILE *archivo = fopen(nombre, "r");
            if (archivo == NULL)
            {
                perror("Error: ");
                return EXIT_FAILURE;
            }
            espaciobd = loaddb(archivo, espaciobd, &tamanobd, &contadorRegistro, nombre);
            fclose(archivo);
        }
        else if (strncmp("readall", comando, 7) == 0)
        {
            readall(espaciobd,tamanobd);
        }
        else if (strncmp("readsize", comando, 8) == 0)
        {
            readsize(espaciobd,tamanobd);
        }
        else if (strncmp("readreg", comando, 7) == 0)
        {
            int cedula;
            fscanf(stdin, "%d", &cedula);
            readreg(espaciobd,tamanobd,cedula);
        }
        else if (strncmp("exit", comando, 4) == 0)
        {
            int opcion;
            printf("Desea guardar la base de datos?\n1 si desea guardarla.\n2 si no desea guardarla.\n");
            scanf("%d", &opcion);
            getc(stdin);
            if (opcion == 1)
            {
                char nombre[20];
                printf("Ingrese el nombre de la db\n");
                scanf("%s", nombre);
                getc(stdin);
                FILE *archivo2 = fopen(nombre, "w+");
                savedb(archivo2, espaciobd, nombre, tamanobd, contadorRegistro);
                fclose(archivo2);
            }
            break;
        }

    } while (1);
    free(espaciobd);
    return 0;
}
