#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>
int main(int argc, char const *argv[])
{
    char direcciones[2][20] = {{"./pc1"},{"./pc2"}};
    pid_t pid_hijo;
    for (int i = 0; i <= 1; i++)
    {
        pid_hijo = fork();
        if (pid_hijo == 0)
        {
            int RetVal;
            RetVal = execv(direcciones[i], argv);
            if (RetVal==-1)
            {
                perror("ERROR: ");
                exit(EXIT_FAILURE);
            }
        }  
    }
    wait(NULL);
    wait(NULL);
    FILE *archivo2 = fopen(argv[2], "r");
    char c;
    int contRegistros = 0;
    for (c = getc(archivo2); c != EOF; c = getc(archivo2)) 
        if (c == '\n')
            contRegistros = contRegistros + 1; 
    contRegistros++;
    rewind(archivo2);
    printf("Luego del sort\n");
    printf("|clave |valor |\n");
    for (int i = 0; i < contRegistros-1; i++)
    {
        char clave[20];
        int valor;
        fscanf(archivo2, "%s", clave);
        fscanf(archivo2, "%d", &valor);
        printf("%s\t%d\t\n",clave,valor);
    }
    fclose(archivo2);
    archivo2 = fopen(argv[3], "r");
    archivo2 = fopen(argv[3], "r");
    printf("Orden inverso\n");
    printf("|clave |valor |\n");
    for (int i = contRegistros-1; i > 0; i--)
    {
        char clave[20];
        int valor;
        fscanf(archivo2, "%s", clave);
        fscanf(archivo2, "%d", &valor);
        printf("%s\t%d\t\n", clave,valor);
    }
    fclose(archivo2);
    return 0;
}
