#ifndef ZONASEGURA_H
#define ZONASEGURA_H

#include "elementojuego.h"
#include "jugador.h"

class ZonaSegura : public ElementoJuego {
public:
    ZonaSegura(double alturaSegura);

    bool jugadorEnZona(const Jugador& j) const;
    double getAlturaSegura() const { return alturaSegura; }

    void actualizar(double dt) override;

private:
    double alturaSegura;
};

#endif
