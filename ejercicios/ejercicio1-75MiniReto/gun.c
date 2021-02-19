#include <stdio.h>
#include <string.h>
#include <stdlib.h>
typedef struct
{
    int capacidad;
    int balas;
} gun;

struct gun *crearArma()
{
    return malloc(sizeof(gun));
}

void CleanGun(gun *Arma)
{
    free(Arma);
}

void InicializarArma(gun *Arma, int balas)
{
    if (balas > 0)
    {
        Arma->capacidad = balas;
        Arma->balas = balas;
    }
    else
    {
        printf("Cantidad no valida de balas\n");
    }
}

void Disparar(gun *Arma)
{
    while (Arma->balas > 0)
    {
        char opcion = 'L';
        printf("Presione S para disparar, L para detenerse o A para modo automático\n");
        scanf("%c", &opcion);
        getc(stdin);
        if (opcion == 'S' && Arma->balas >0 )
        {
            printf("PUM Quedan %d Balas\n", Arma->balas - 1);
            Arma->balas = Arma->balas - 1;
        }
        else if (opcion == 'A' && Arma->balas >0 )
        {
            while (Arma->balas >0)
            {
               printf("PUM Quedan %d Balas\n", Arma->balas - 1);
                Arma->balas = Arma->balas - 1;
            }
        }
        
        else
        {
            break;
        }
    }
}

void Recargar(gun *Arma)
{
    Arma -> balas = Arma ->capacidad;
    printf("Arma recargada \n");
}