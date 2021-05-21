#include <stdio.h>
#include <string.h>
#include <errno.h>
#include <unistd.h>
#include <stdlib.h>
#include <pthread.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <signal.h>

#define PORT 6666
#define BUF_SIZE 128
int clientnum = 0;
int posAva[10];

struct client_t
{
    int socket;
    int rxState;
    int nroCliente;
    char nombreCliente[30];
};
struct client_t client[10];

void *readThread(void *arg)
{
    int primera = 0;
    struct client_t *clientEnd = ((struct client_t *)arg);
    ssize_t numOfBytes;
    char buf[BUF_SIZE];
    int status;
    while (1)
    {
        strcpy(buf,"");
        numOfBytes = read(clientEnd->socket, buf, BUF_SIZE);
        if (0 == numOfBytes)
        {
            printf("client closed the socket end\n");
            break;
        }
        else if (-1 == numOfBytes)
        {
            perror("ReadThread read() fails: ");
            break;
        }
        else
        {
            if (primera == 0)
            {
                strcpy(clientEnd->nombreCliente, buf);
                printf("cliente %s conectado\n", clientEnd->nombreCliente);
                primera = 1;
            }
            else
            {
                printf("from client %s, #: %d: %s\n", clientEnd->nombreCliente, clientEnd->nroCliente, buf);
                char msg[BUF_SIZE];
                strcat(msg, clientEnd->nombreCliente);
                strcat(msg, ": ");
                strcat(msg, buf);
                strcat(msg, "\n");
                strcpy(buf, msg);
                strcpy(msg,"");
                for (int i = 0; i < clientnum; i++)
                {
                    if (i != clientEnd->nroCliente)
                    {
                        status = write(client[i].socket, buf, strlen(buf) + 1);
                        // printf("Pruebas de errores. Usuario: %s\nBuf: %s\nMsg: %s",clientEnd->nombreCliente,buf,msg);
                    }
                }
            }
        }
    }
    printf("Terminate Pthread for reading\n");
    clientEnd->rxState = 0;
    if (0 == client[clientEnd->nroCliente].rxState)
    {
        posAva[clientEnd->nroCliente] = 0;
        printf("Client #: %d closed the socket\n",clientEnd->nroCliente);
        close(client[clientEnd->nroCliente].socket);
        clientnum--;
    }
    return NULL;
}

int main(int argc, char *argv[])
{

    char buf[BUF_SIZE];
    int status;
    int enable = 1;
    int server_sd;
    int client_sd[10];
    pthread_t rxThreadId[10];

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

    // 3. turn off bind address checking
    status = setsockopt(server_sd, SOL_SOCKET, SO_REUSEADDR, (int *)&enable, sizeof(enable));
    if (-1 == status)
    {
        perror("setsockopt error: ");
    }

    //4. BIND the socket to an address
    // Prepare the address
    struct sockaddr_in addr;
    memset(&addr, 0, sizeof(addr));
    addr.sin_family = AF_INET;
    addr.sin_addr.s_addr = INADDR_ANY;
    addr.sin_port = htons(PORT);

    status = bind(server_sd, (struct sockaddr *)&addr, sizeof(addr));
    if (-1 == status)
    {
        perror("Bind fails: ");
        close(server_sd);
        exit(EXIT_FAILURE);
    }
    printf("Socket binded\n");

    // 5. Set backlog

    status = listen(server_sd, 1);

    if (-1 == status)
    {
        perror("Listen fails: ");
        close(server_sd);
        exit(EXIT_FAILURE);
    }

    printf("Server listening\n");


    for (int i = 0; i < 10; i++)
    {
        posAva[i]=0;
    }
    
    while (1)
    {
        for (int i = 0; i < 10; i++)
        {
            if (posAva[i] == 0)
            {   
                posAva[i] = 1;
                printf("Waiting for a client\n");
                client_sd[i] = accept(server_sd, NULL, NULL);
                printf("Client connected\n");
                if (-1 == client_sd[i])
                {
                    perror("Accept fails: ");
                    close(server_sd);
                    exit(EXIT_FAILURE);
                }
                // 7. Create a thread for receiving messages from client
                client[i].socket = client_sd[i];
                client[i].rxState = 1;
                client[i].nroCliente = i;

                printf("Create Pthread for reading\n");
                status = pthread_create(&rxThreadId[i], NULL, &readThread, &client[i]);
                if (-1 == status)
                {
                    perror("Pthread read fails: ");
                    close(server_sd);
                    exit(EXIT_FAILURE);
                }
                clientnum++;
            }
        }   
    }
    exit(EXIT_SUCCESS);
}