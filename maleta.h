#ifndef MALETA_H
#define MALETA_H

#include "obstaculo.h"

class Maleta : public Obstaculo {
public:
    Maleta(double x, double pisoY, int tipo);

    bool colisionar(Jugador& j) override;
    void actualizar(double dt) override;

    int getTipo() { return tipo; }

private:
    int tipo;
};

#endif
