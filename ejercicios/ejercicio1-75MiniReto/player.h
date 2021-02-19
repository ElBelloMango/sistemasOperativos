#ifndef PLAYER_H_
#define PLAYER_H_

struct player;
struct gun;
struct player *CrearJugador();
void CleanPlayer(struct player* jugador);
void InicializarJugador(struct player *jugador, char Nombre[20]);
void AgregarArma(struct player *jugador, struct gun *Arma);
void DispararArma(struct player *jugador);
void TirarArma(struct player *jugador);
void RecargarArma(struct player *jugador);

#endif