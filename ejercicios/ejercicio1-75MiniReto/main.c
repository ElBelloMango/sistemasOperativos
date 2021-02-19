#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "gun.h"
#include "player.h"

//END ARMA
//PLAYER

int main(int argc, char const *argv[])
{
    struct gun *Arma = crearArma();
    struct player *jugador = CrearJugador();
    char Name[20];
    printf("ingrese el nombre del jugador\n");
    scanf("%s",Name);
    getc(stdin);
    InicializarJugador(jugador,Name);
    int hasgun = 0;
    while (1)
    {
        int Opcion;
        if (hasgun == 1)
        {
            printf("1 para disparar \n2 para recargar\n3 para tirar el arma\n");
            scanf("%d",&Opcion);
            getc(stdin);
            if (Opcion == 1)
            {
                DispararArma(jugador);
            }
            else if (Opcion == 2)
            {
                RecargarArma(jugador);
            }
            else if (Opcion == 3)
            {
                TirarArma(jugador);
                break;
            }
        }
        else{
            printf("0 para recoger un arma\n1 para disparar \n2 para recargar\n3 para tirar el arma\n");
            scanf("%d",&Opcion);
            getc(stdin);
            if (Opcion == 0)
            {
                int CantBalas;
                printf("Ingrese la cantidad de balas de el arma\n");
                scanf("%d",&CantBalas);
                getc(stdin);
                InicializarArma(Arma,CantBalas);
                AgregarArma(jugador,Arma);
                hasgun = 1;
            }
            else if (Opcion == 1)
            {
                DispararArma(jugador);
            }
            else if (Opcion == 2)
            {
                RecargarArma(jugador);
            }
            else if (Opcion == 3)
            {
                TirarArma(jugador);
            }
        }
        
    }
    CleanGun(Arma);
    CleanPlayer(jugador);
    return 0;
}
