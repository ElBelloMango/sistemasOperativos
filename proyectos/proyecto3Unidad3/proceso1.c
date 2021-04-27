#include <stdio.h>
#include <stdint.h>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>
#include <errno.h>
#include <string.h>
#include <sys/mman.h>
#include <sys/wait.h>
#include <semaphore.h>
#include <pthread.h>

#define SH_SIZE 500

int shared_fd1 = -1;
int shared_fd2 = -1;

sem_t *sem1write, *sem1read;
sem_t *sem2write, *sem2read;

struct parametros
{
    char Mensaje[SH_SIZE];
};

void init_control_mechanism()
{
    // Primer Proceso
    sem1write = sem_open("sem1write", O_CREAT, 0666, 0);
    if(sem1write == SEM_FAILED){
        perror("user 1 sem_open sem1w fails: ");
        exit(EXIT_FAILURE);
    }

    sem1read = sem_open("sem1read", O_CREAT, 0666, 0);
    if(sem1read == SEM_FAILED){
        perror("user 1 sem_open sem1r fails: ");
        exit(EXIT_FAILURE);
    }

    sem2write = sem_open("sem2write",0);
    if(sem2write == SEM_FAILED){
        perror("user1 sem_open sem2write: ");
        exit(EXIT_FAILURE);
    }

    sem2read = sem_open("sem2read",0);
    if(sem2read == SEM_FAILED){
        perror("user1 sem_open sem2r: ");
        exit(EXIT_FAILURE);
    }
}

void init_shared_resource()
{
    shared_fd1 = shm_open("shm0", O_CREAT | O_RDWR, 0600);
    if (shared_fd1 < 0)
    {
        perror("Failed to create shared memory: ");
        exit(EXIT_FAILURE);
    }
    shared_fd2 = shm_open("shm1", O_RDONLY , 0600);
    if (shared_fd2 < 0)
    {
        perror("Failed to create shared memory: ");
        exit(EXIT_FAILURE);
    }
    fprintf(stdout, "Shared memory is created with fd: %d\n", shared_fd1);
}


void *sendMsg(void *parametros)
{
    struct parametros *p = (struct parametros *)parametros;
    char *map;
    char *ptr;
    while (fgets(p->Mensaje, sizeof p->Mensaje, stdin) != NULL)
    {
        if(sem_post(sem1write) == -1){
            perror("sem_post error sem1write: ");
            exit(EXIT_FAILURE);
        }

        map = mmap(NULL, SH_SIZE, PROT_WRITE, MAP_SHARED, shared_fd1, 0);

        if (map == MAP_FAILED) {
            perror("Mapping failed: ");
            exit(EXIT_FAILURE);
        }

        ptr = (char *)map;
        memcpy(ptr, p->Mensaje, sizeof(p->Mensaje));

        if (munmap(ptr, SH_SIZE) < 0) {
            perror("Unmapping failed: ");
            exit(EXIT_FAILURE);
        }

        if(sem_wait(sem2read) == -1){
            perror("sem_wait error sem2r: ");
            exit(EXIT_FAILURE);
        } 
    }
     if(sem_close(sem1write) == -1){
        perror("sem_close fails write: ");
        exit(EXIT_FAILURE);
    }

    if(sem_unlink("sem1write") == -1){
        perror("sem_unlink falls sem1write: ");
        exit(EXIT_FAILURE);
    }

    if(sem_close(sem1read) == -1){
        perror("sem_close fails sem1r: ");
        exit(EXIT_FAILURE);
    }

    if(sem_unlink("sem1read") == -1){
        perror("sem_unlink falls sem1r: ");
        exit(EXIT_FAILURE);
    }
    if (close(shared_fd1) < 0) {
        perror("Closing shm failed: ");
        exit(EXIT_FAILURE);
    }

    if (shm_unlink("shm0") < 0) {
        perror("Unlink failed: ");
        exit(EXIT_FAILURE);
    }

}

void *reciveMsg(void *parametros)
{
    struct parametros *p = (struct parametros *)parametros;
    char *ptr;
    for (;;)
    {
        if(sem_wait(sem2write) == -1){
            perror("sem_wait error sem2write: ");
            exit(EXIT_FAILURE);
        }
        void* map = mmap(NULL, SH_SIZE, PROT_READ, MAP_SHARED, shared_fd2, 0);
        if (map == MAP_FAILED) {
            perror("Mapping failed: ");
            exit(EXIT_FAILURE);
        }
        ptr = (char*)map;
        fprintf(stdout, "Usuario 2: %s\n", ptr);
        if (munmap(ptr, SH_SIZE) < 0) {
            perror("Unmapping failed: ");
            exit(EXIT_FAILURE);
        }

        //abrir candado semaforo lectura 1
        if(sem_post(sem1read) == -1){
            perror("sem_post error sem1r: ");
            exit(EXIT_FAILURE);
        }
    }
    printf("Com End\n");
}


int main(int argc, char **argv)
{
    pthread_t hilos_ids[2];
    init_shared_resource();
    init_control_mechanism();

    // Truncate fd1
    if (ftruncate(shared_fd1, SH_SIZE * sizeof(char)) < 0)
    {
        perror("Truncation failed: ");
        exit(EXIT_FAILURE);
    }
    fprintf(stdout, "The memory region is truncated.\n"); 

    char Mensaje[SH_SIZE];

    struct parametros hilo1_param;
    struct parametros hilo2_param;

    strcpy(hilo1_param.Mensaje,Mensaje);
    // hilo1_param.Mensaje = Mensaje;



    pthread_create(&hilos_ids[0], NULL, &sendMsg, &hilo1_param);
    pthread_create(&hilos_ids[1], NULL, &reciveMsg, &hilo2_param);
    
    pthread_join(hilos_ids[0], NULL);
    pthread_join(hilos_ids[1], NULL);

    exit(EXIT_SUCCESS);
}