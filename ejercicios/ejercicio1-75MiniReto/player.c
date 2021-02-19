#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "gun.h"

typedef struct
{
    char Nombre[20];
    struct gun *Arma;
} player;

struct player *CrearJugador()
{
    return malloc(sizeof(player));
}
void CleanPlayer(player *jugador)
{
    free(jugador);
}

void InicializarJugador(player *jugador, char Nombre[20])
{
    strcpy(jugador->Nombre, Nombre);
    jugador->Arma = NULL;
}

void AgregarArma(player *jugador, struct gun *Arma)
{
    jugador->Arma = Arma;
    printf("El jugador %s ha agarrado un arma\n", jugador->Nombre);
}
void DispararArma(player *jugador)
{
    if (jugador->Arma)
    {
        Disparar(jugador->Arma);
        printf("%s Dice: Quieto Socio\n", jugador->Nombre);
    }
    else
    {
        printf("El jugador %s no tiene una arma\n", jugador->Nombre);
    }
}
void TirarArma(player *jugador)
{
    if (jugador->Arma)
    {
        jugador->Arma = NULL;
        printf("El jugador %s tiró su arma y lo mataron\n", jugador->Nombre);
    }
    else
    {
        printf("El jugador %s quería tirar su arma pero no tenía ninguna\n", jugador->Nombre);
    }
}
void RecargarArma(player *jugador)
{
    if (jugador->Arma)
    {
        printf("El jugador %s está recargando su arma\n", jugador->Nombre);
        Recargar(jugador->Arma);
    }
    else
    {
        printf("El jugador %s quería recargar su arma pero no tenía ninguna\n", jugador->Nombre);
    }
}