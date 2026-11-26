#include "puerta.h"

Puerta::Puerta(double x, double pisoY)
    : ElementoJuego(x, pisoY - 170, 123, 170, ":/sprites/puerta_cerrada.png"), abierta(false) {
    setMargenHitbox(20, 10);
}

bool Puerta::jugadorLlego(const Jugador& j) const {
    return colisionaCon(j);
}

void Puerta::abrir() {
    abierta = true;
    rutaSprite = ":/sprites/puerta_abierta.png";
}

void Puerta::actualizar(double dt) {
}
