#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>

int main(int argc, char const *argv[])
{
    pid_t pid_hijo;
    char direcciones[3][20] = {{"./min"},{"./max"},{"./promedio"}};
    printf("El pid del programa padre es: %d\n", (int)getpid());
    int nroHijo = 0;
    for (int i = 0; i <= 2; i++)
    {
        nroHijo=i+1;
        pid_hijo = fork();
        if (pid_hijo == 0)
        {
            printf("Hijo %d\n", nroHijo);
            execv(direcciones[i], argv);
            break;
        }
        else
            wait(NULL);
    }
    return 0;
}