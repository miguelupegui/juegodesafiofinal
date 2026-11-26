#include "elementojuego.h"

ElementoJuego::ElementoJuego(double x, double y, double ancho, double alto, std::string rutaSprite)
{
    posicion = Vector2D(x, y);
    velocidad = Vector2D(0, 0);
    hitbox = Rectangulo(0, 0, ancho, alto);
    this->rutaSprite = rutaSprite;
    activo = true;
    this->ancho = ancho;
    this->alto = alto;
}

ElementoJuego::~ElementoJuego()
{
}

Rectangulo ElementoJuego::getHitbox() const
{
    Rectangulo r;
    r.x = posicion.x + hitbox.x;
    r.y = posicion.y + hitbox.y;
    r.ancho = hitbox.ancho;
    r.alto = hitbox.alto;
    return r;
}

bool ElementoJuego::colisionaCon(const ElementoJuego &otro) const
{
    if (activo == false || otro.activo == false)
        return false;
    return getHitbox().intersecta(otro.getHitbox());
}

void ElementoJuego::setPosicion(double x, double y)
{
    posicion.x = x;
    posicion.y = y;
}

void ElementoJuego::setMargenHitbox(double margenX, double margenY)
{
    hitbox.x = margenX;
    hitbox.y = margenY;
    hitbox.ancho = ancho - 2 * margenX;
    hitbox.alto = alto - 2 * margenY;
}
