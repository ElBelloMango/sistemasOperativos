#include <stdio.h>
#include <string.h>
#include <stdlib.h>

//ARMA
struct gun;
struct gun* crearArma();
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

//END ARMA
//PLAYER
struct player;

typedef struct
{
    char Nombre[20];
    gun* Arma;
}player;

struct player* CrearJugador();

struct player* CrearJugador(){
    return malloc(sizeof(player));
}
void CleanPlayer(player *jugador)
{
    free(jugador);
}

void InicializarJugador(player *jugador, char Nombre[20])
{
    strcpy(jugador->Nombre,Nombre);
    jugador->Arma = NULL;
}

void AgregarArma(player *jugador,gun* Arma)
{
    jugador->Arma = Arma;
    printf("El jugador %s ha agarrado un arma\n",jugador->Nombre);
}
void DispararArma(player *jugador)
{
    if (jugador->Arma)
    {
        Disparar(jugador->Arma);
        printf("%s Dice: Quieto Socio\n",jugador->Nombre);
        if (jugador->Arma->balas == 0)
        {
           printf("El jugador %s se quedó sin balas\n",jugador->Nombre);
           TirarArma(jugador);
        }
        
    }
    else{
        printf("El jugador %s no tiene una arma\n",jugador->Nombre);
    }
}
void TirarArma(player *jugador)
{
    if (jugador->Arma)
    {
        jugador->Arma = NULL;
        printf("El jugador %s tiró su arma y lo mataron\n",jugador->Nombre);
        exit(1);
    }
    else
    {
        printf("El jugador %s quería tirar su arma pero no tenía ninguna\n",jugador->Nombre);
    }
}
void RecargarArma(player *jugador)
{
    if (jugador->Arma)
    {
        printf("El jugador %s está recargando su arma\n",jugador->Nombre);
        Recargar(jugador->Arma);
    }
    else
    {
        printf("El jugador %s quería recargar su arma pero no tenía ninguna\n",jugador->Nombre);
    }
    
}
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
    
    return 0;
}
