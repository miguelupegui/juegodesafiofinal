#include "powerup.h"

PowerUp::PowerUp(double x, double y, double ancho, double alto, const std::string& rutaSprite,
                 double duracionEfecto)
    : ElementoJuego(x, y, ancho, alto, rutaSprite)
{
    this->duracionEfecto = duracionEfecto;
    recogido = false;
    tiempo = 0;
    setMargenHitbox(2, 2);
}

void PowerUp::actualizar(double dt) {
    tiempo += dt;
}

PowerUpVelocidadBaja::PowerUpVelocidadBaja(double x, double y)
    : PowerUp(x, y, 28, 44, ":/sprites/poder_reloj.png", 7.0) {
}

void PowerUpVelocidadBaja::aplicarEfecto(Jugador& j) {
    j.aplicarEfecto(EstadoJugador::RALENTIZADO, duracionEfecto);
    recogido = true;
    desactivar();
}

PowerUpInvencibilidad::PowerUpInvencibilidad(double x, double y)
    : PowerUp(x, y, 45, 44, ":/sprites/poder_estrella.png", 7.0) {
}

void PowerUpInvencibilidad::aplicarEfecto(Jugador& j) {
    j.aplicarEfecto(EstadoJugador::INVENCIBLE, duracionEfecto);
    recogido = true;
    desactivar();
}
