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


void printSubDir(char* path){
    char newDir[100];
    DIR *directorio;
    struct dirent *estructura;
    // printf("Ruta a abrir:%s\n"),path;
    directorio = opendir(path);
    while ((estructura = readdir(directorio)) != NULL)
    {
        if (estructura->d_type == 4)
            printf("Found Directory: %s/%s\n",path, estructura->d_name);
        else
            printf("Found file: %s/%s\n",path, estructura->d_name);
        if (estructura->d_type == 4 && strcmp(estructura->d_name, "..") != 0 && strcmp(estructura->d_name, ".") != 0)
        {
            // printf("Directorio a recorrer: %s\n",estructura->d_name);
            strcat(path,"/");
            strcat(newDir,path);
            // printf("newDir primer paso: %s\n",newDir);
            strcat(newDir,estructura->d_name);
            // printf("Ruta a seguir: %s\n",newDir);            
            printSubDir(newDir);
        }
    }
}

int main(int argc, char **argv)
{
    DIR *streamp;
    struct dirent *dep;

    // if (argc != 2)
    // {
    //     printf("usage: %s <pathname>\n", argv[0]);
    //     exit(1);
    // }
    streamp = opendir("dirEjemplo");
    char newDir[100] = "";
    errno = 0;
    while ((dep = readdir(streamp)))
    {
        if (dep->d_type == 4)
            printf("Found Directory: %s/%s\n","dirEjemplo", dep->d_name);
        else
            printf("Found file: %s/%s\n","dirEjemplo", dep->d_name);
        if (dep->d_type == 4 && strcmp(dep->d_name, "..") != 0 && strcmp(dep->d_name, ".") != 0)
        {
            // printf("Directorio a recorrer: %s\n",dep->d_name);
            strcat(newDir,"dirEjemplo/");
            strcat(newDir,dep->d_name);
            // printf("Ruta a seguir: %s\n",newDir);
            printSubDir(newDir);
        }
        strcpy(newDir,"");
    }
    if (errno != 0)
        unix_error("readdir error");

    closedir(streamp);
    exit(0);
}
