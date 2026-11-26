#ifndef POWERUP_H
#define POWERUP_H

#include "elementojuego.h"
#include "jugador.h"

class PowerUp : public ElementoJuego {
public:
    PowerUp(double x, double y, double ancho, double alto, const std::string& rutaSprite,
            double duracionEfecto);

    virtual void aplicarEfecto(Jugador& j) = 0;
    void actualizar(double dt) override;

    bool fueRecogido() const { return recogido; }
    double getTiempo() const { return tiempo; }

protected:
    double duracionEfecto;
    bool recogido;
    double tiempo;
};

class PowerUpVelocidadBaja : public PowerUp {
public:
    PowerUpVelocidadBaja(double x, double y);
    void aplicarEfecto(Jugador& j) override;
};

class PowerUpInvencibilidad : public PowerUp {
public:
    PowerUpInvencibilidad(double x, double y);
    void aplicarEfecto(Jugador& j) override;
};

#endif
