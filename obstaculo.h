#ifndef OBSTACULO_H
#define OBSTACULO_H

#include "elementojuego.h"
#include "jugador.h"

class Obstaculo : public ElementoJuego {
public:
    Obstaculo(double x, double y, double ancho, double alto, std::string rutaSprite)
        : ElementoJuego(x, y, ancho, alto, rutaSprite) {}

    virtual bool colisionar(Jugador& j) = 0;
};

#endif
