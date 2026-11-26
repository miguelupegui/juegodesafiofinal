#ifndef PUERTA_H
#define PUERTA_H

#include "elementojuego.h"
#include "jugador.h"

class Puerta : public ElementoJuego {
public:
    Puerta(double x, double pisoY);

    bool jugadorLlego(const Jugador& j) const;
    void abrir();
    bool estaAbierta() const { return abierta; }

    void actualizar(double dt) override;

private:
    bool abierta;
};

#endif
