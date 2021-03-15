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
            execv(direcciones[i], argv);
            break;
        }
        else
            wait(NULL);
    }
    return 0;
}
