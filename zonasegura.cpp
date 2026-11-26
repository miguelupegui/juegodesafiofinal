#include "zonasegura.h"

ZonaSegura::ZonaSegura(double alturaSegura)
    : ElementoJuego(0, alturaSegura, 960, 80, ""), alturaSegura(alturaSegura) {
}

bool ZonaSegura::jugadorEnZona(const Jugador& j) const {
    double pies = j.getPosicion().y + j.getAlto();
    if (pies >= alturaSegura)
        return true;
    return false;
}

void ZonaSegura::actualizar(double dt) {
}
