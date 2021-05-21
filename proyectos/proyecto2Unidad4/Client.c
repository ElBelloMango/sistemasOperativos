#include <stdio.h>
#include <string.h>
#include <errno.h>
#include <unistd.h>
#include <stdlib.h>
#include <pthread.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <signal.h>
#include <arpa/inet.h>

#define PORT 6666
#define BUF_SIZE 128

struct client_t
{
    int socket;
    int rxState;
    int nroCliente;
    char nombreCliente[30];
};

void *readThread(void *arg)
{
    struct client_t *client = ((struct client_t *)arg);
    ssize_t numOfBytes;
    char buf[BUF_SIZE];

    while (1)
    {
        numOfBytes = read(client->socket, buf, BUF_SIZE);
        // printf("Usuario recibió: %s\n",buf);
        if (0 == numOfBytes)
        {
            printf("Server closed the socket end\n");
            break;
        }
        else if (-1 == numOfBytes)
        {
            perror("ReadThread read() fails: ");
            break;
        }
        if (0 == strncmp(buf, ":exit", strlen(":exit")))
        {
            printf("Disconnected from server\n");
            close(client->socket);
            exit(EXIT_SUCCESS);
            break;
        }
        else
        {
            write(STDOUT_FILENO,buf,strlen(buf));
            
        }
    }
    printf("Terminate Pthread for reading\n");
    client->rxState = 0;
    return NULL;
}

void *writeThread(void *arg)
{
    struct client_t *client = ((struct client_t *)arg);
    char buf[BUF_SIZE];
    int status;
    int primera = 0;
    if (primera==0)
            printf("Escriba el nombre de el cliente\n");  
    while (1)
    {
        if (0 == client->rxState)
        {
            printf("Server closed the socket\n");
            break;
        }

        if (fgets(buf, BUF_SIZE, stdin) == NULL)
        {
            printf("Fgets NULL\n");
        }
        if (0 == strncmp(buf, ":exit", strlen(":exit")))
        {
            printf("Clinet exit\n");
            break;
        }

        if (buf[strlen(buf) - 1] == '\n')
            buf[strlen(buf) - 1] = 0;

  
        status = write(client->socket, buf, strlen(buf) + 1);
        // printf("Pruebas de errores.\nBuf: %s\n",buf);
        if (primera==0)
        {
            printf("Conectado, ya puede chatear\n");
            primera = 1; 
        }

        if (-1 == status)
        {
            perror("Server write to client fails: ");
            break;
        } 
    }
    close(client->socket);
    exit(EXIT_SUCCESS);
}

int main(int argc, char *argv[])
{

    char buf[BUF_SIZE];
    int status;
    int server_sd;
    pthread_t rxThreadId;
    pthread_t writeThreadId;
    struct client_t client;

    // 1. Ignore SIGPIPE
    signal(SIGPIPE, SIG_IGN);

    // 2. Create socket
    server_sd = socket(AF_INET, SOCK_STREAM, 0);
    if (server_sd == -1)
    {
        perror("Socket creation fails\n");
        exit(EXIT_FAILURE);
    }
    printf("Socket created\n");

    //3. Connect to the server 127.0.0.1:PORT
    // Prepare the address
    struct sockaddr_in addr;
    memset(&addr, 0, sizeof(addr));
    addr.sin_family = AF_INET;
    addr.sin_addr.s_addr = inet_addr("127.0.0.1");
    addr.sin_port = htons(PORT);

    status = connect(server_sd, (struct sockaddr *)&addr, sizeof(addr));
    if (-1 == status)
    {
        perror("Connect fails\n");
        close(server_sd);
        exit(EXIT_FAILURE);
    }

    printf("Server connected\n");

    // 4. Create a thread for receiving messages from client
    client.socket = server_sd;
    client.rxState = 1;
    printf("Create Pthread for reading\n");
    status = pthread_create(&rxThreadId, NULL, &readThread, &client);
    if (-1 == status)
    {
        perror("Pthread read fails: ");
        close(server_sd);
        exit(EXIT_FAILURE);
    }

    int writeStatus;
    writeStatus = pthread_create(&writeThreadId, NULL, &writeThread, &client);
    while(1)
    {

    }
}