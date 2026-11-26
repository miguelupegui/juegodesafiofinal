#ifndef ESCOMBRO_H
#define ESCOMBRO_H

#include "obstaculo.h"
#include "caidalibre.h"

class Escombro : public Obstaculo {
public:
    Escombro(double x, double y, int tipo, double velocidadTerminal, double velocidadX);

    bool colisionar(Jugador& j) override;
    void actualizar(double dt) override;

    double getAngulo() const { return angulo; }
    double getTamano() const { return tamano; }

private:
    CaidaLibre caida;
    double tamano;
    double angulo;
    double velocidadGiro;
};

#endif
