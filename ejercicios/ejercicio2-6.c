#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/wait.h>

int main(int argc, char const *argv[])
{
    pid_t pid_hijo;
    printf("El pid del programa padre es: %d\n", (int)getpid());
    int nroHijo = 0;
    for (int i = 1; i <= 3; i++)
    {
        nroHijo=i;
        pid_hijo = fork();
        if (pid_hijo == 0)
        {
            printf("Hijo %d\n", i);
            break;
        }
        else
            wait(NULL);
    }
    for (int i = 1; i <= 10; i++)
    {
        int fact = 1;
        for (int j = i; j > 0; j--)
        {
            fact = fact * j;
        }
        if (0 == (int)pid_hijo)
        {
            printf("Hijo(%d) de PID = %d: fact(%d) = %d \n",nroHijo,(int)getpid(), i, fact);
        }
    }
    printf("Soy el proceso %d terminando \n", (int)getpid());
    exit(EXIT_SUCCESS);
}
