#ifndef GUN_H_
#define GUN_H_

struct gun;
struct gun *crearArma();
void CleanGun(struct gun *Arma);
void InicializarArma(struct gun *Arma, int balas);
void Disparar(struct gun *Arma);
void Recargar(struct gun *Arma);

#endif