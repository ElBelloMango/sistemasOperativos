#include <pthread.h>
#include <stdio.h>

struct parametros_hilo {
    char caracter;
    int contador;
};

void* imprimir_caracter(void* parametros)
{
    struct parametros_hilo* p = (struct parametros_hilo*) parametros;
    int i;
    for (i = 0; i < p->contador; ++i)
    {
        fputc(p->caracter,stderr);
    }
    return NULL;
}

int main()
{
    pthread_t hilo1;
    pthread_t hilo2;
    struct parametros_hilo hilo1_param;
    struct parametros_hilo hilo2_param;


    hilo1_param.caracter = 'x';
    hilo1_param.contador = 30000;
    pthread_create(&hilo1,NULL,&imprimir_caracter,&hilo1_param);

    hilo2_param.caracter = 'o';
    hilo2_param.contador = 20000;
    pthread_create(&hilo2,NULL,&imprimir_caracter,&hilo2_param);
    
    return 0;
}