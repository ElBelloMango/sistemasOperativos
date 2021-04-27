/* Filename: msgq_recv.c */
#include <stdio.h>
#include <stdlib.h>
#include <errno.h>
#include <sys/types.h>
#include <sys/ipc.h>
#include <sys/msg.h>
#include <pthread.h>
#include <string.h>
#define PERMS 0644
struct my_msgbuf
{
    long mtype;
    char mtext[200];
};

struct parametros
{
   struct my_msgbuf buf;
   int len;
   int msqid;
};

void *sendMsg(void *parametros)
{
   struct parametros *p = (struct parametros *)parametros;
   while (fgets(p->buf.mtext, sizeof p->buf.mtext, stdin) != NULL)
   {
      p->len = strlen(p->buf.mtext);
      /* remove newline at end, if it exists */
      if (p->buf.mtext[p->len - 1] == '\n')
         p->buf.mtext[p->len - 1] = '\0';
      if (msgsnd(p->msqid, &p->buf, p->len + 1, 0) == -1) /* +1 for '\0' */
         perror("msgsnd");
   }
   strcpy(p->buf.mtext, "end");
   p->len = strlen(p->buf.mtext);
   if (msgsnd(p->msqid, &p->buf, p->len + 1, 0) == -1) /* +1 for '\0' */
      perror("msgsnd");

   if (msgctl(p->msqid, IPC_RMID, NULL) == -1)
   {
      perror("msgctl");
      exit(1);
   }
   printf("message queue: done sending messages.\n");
}

void *reciveMsg(void *parametros)
{
    struct parametros *p = (struct parametros *)parametros;
    for (;;)
    { /* normally receiving never ends but just to make conclusion 
             /* this program ends wuth string of end */
        if (msgrcv(p->msqid, &p->buf, sizeof(p->buf.mtext), 1, 0) == -1)
        {
            perror("msgrcv");
            exit(1);
        }
        printf("Proceso1: \"%s\"\n", p->buf.mtext);
        int toend = strcmp(p->buf.mtext, "end");
        if (toend == 0)
            break;
    }
    printf("message queue: done receiving messages.\n");
    exit(1);
}

int main(void)
{
    pthread_t hilos_ids[2];
    struct my_msgbuf buf;
    int msqid;
    int len;
    int toend;
    key_t key;

    if ((key = ftok("msgq.txt", 'B')) == -1)
    {
        perror("ftok");
        exit(1);
    }

    if ((msqid = msgget(key, PERMS | IPC_CREAT)) == -1)
    { /* connect to the queue */
        perror("msgget");
        exit(1);
    }
    printf("Listo para la comunicación.\n");
    buf.mtype = 2;
    
    struct parametros hilo1_param;
    struct parametros hilo2_param;
 
    hilo1_param.buf = buf;
    hilo1_param.len = len;
    hilo1_param.msqid = msqid;


    hilo2_param.buf = buf;
    hilo2_param.msqid = msqid;

    pthread_create(&hilos_ids[0], NULL, &sendMsg, &hilo1_param);
    pthread_create(&hilos_ids[1], NULL, &reciveMsg, &hilo2_param);
    
    pthread_join(hilos_ids[0], NULL);
    pthread_join(hilos_ids[1], NULL);  

    system("rm msgq.txt");
    return 0;
}