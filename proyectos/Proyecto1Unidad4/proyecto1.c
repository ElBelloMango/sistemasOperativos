#include <stdio.h>
#include <unistd.h>
#include <sys/stat.h>
#include <stdlib.h>
#include <sys/types.h>
#include <dirent.h>
#include <errno.h>
#include <string.h>

void unix_error(char *msg) /* Unix-style error */
{
    fprintf(stderr, "%s: %s\n", msg, strerror(errno));
    exit(0);
}

int contsub = 0;

void printSubDir(char *path)
{
    contsub++;
    char newDir[512];
    DIR *directorio;
    struct dirent *estructura;
    // printf("Ruta a abrir:%s\n"),path;
    directorio = opendir(path);
    while ((estructura = readdir(directorio)) != NULL)
    {
        for (int i = 0; i < contsub; i++)
        {
            printf("\t");
        }

        if (estructura->d_type == 4)
            printf("Found Directory: %s%s\n", path, estructura->d_name);
        else
            printf("Found file: %s%s\n", path, estructura->d_name);
        if (estructura->d_type == 4 && strcmp(estructura->d_name, "..") != 0 && strcmp(estructura->d_name, ".") != 0)
        {
            // printf("Directorio a recorrer: %s\n",estructura->d_name);
            strcpy(newDir, path);
            strcat(newDir, estructura->d_name);
            strcat(newDir, "/");
            // printf("Ruta a seguir: %s\n", newDir);
            printSubDir(newDir);
            contsub = contsub-1;
        }
    }
}

int main(int argc, char **argv)
{
    DIR *streamp;
    struct dirent *dep;

    if (argc != 2)
    {
        printf("usage: %s <pathname>\n", argv[0]);
        exit(1);
    }
    printf("desde donde se ejecuta el programa: %s\n", argv[0]);
    printf("ruta: %s\n\n", argv[1]); //La ruta relativa desde donde se ejecuta el programa ej: dirEjemplo/ - dirEjemplo/sub2/ - ../
    streamp = opendir(argv[1]);
    char newDir[512] = "";
    errno = 0;
    while ((dep = readdir(streamp)))
    {
        for (int i = 0; i < contsub; i++)
        {
            printf("\t");
        }
        if (dep->d_type == 4)
            printf("Found Directory: %s%s\n", argv[1], dep->d_name);
        else
            printf("Found file: %s%s\n", argv[1], dep->d_name);
        if (dep->d_type == 4 && strcmp(dep->d_name, "..") != 0 && strcmp(dep->d_name, ".") != 0)
        {
            // printf("Directorio a recorrer: %s\n",dep->d_name);
            strcat(newDir, argv[1]);
            strcat(newDir, dep->d_name);
            strcat(newDir, "/");
            // printf("Ruta a seguir: %s\n", newDir);
            printSubDir(newDir);
            contsub = contsub-1;
        }
        strcpy(newDir, "");
    }
    if (errno != 0)
        unix_error("readdir error");

    closedir(streamp);
    exit(0);
}
