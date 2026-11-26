#ifndef ELEMENTOJUEGO_H
#define ELEMENTOJUEGO_H

#include <string>
#include "vector2d.h"
#include "rectangulo.h"

class ElementoJuego {
public:
    ElementoJuego(double x, double y, double ancho, double alto, std::string rutaSprite);
    virtual ~ElementoJuego();

    virtual void actualizar(double dt) = 0;

    Rectangulo getHitbox() const;
    bool colisionaCon(const ElementoJuego& otro) const;

    Vector2D getPosicion() const { return posicion; }
    Vector2D getVelocidad() const { return velocidad; }
    void setPosicion(double x, double y);

    double getAncho() const { return ancho; }
    double getAlto() const { return alto; }
    std::string getRutaSprite() const { return rutaSprite; }

    bool estaActivo() const { return activo; }
    void desactivar() { activo = false; }

protected:
    void setMargenHitbox(double margenX, double margenY);

    Vector2D posicion;
    Vector2D velocidad;
    Rectangulo hitbox;
    std::string rutaSprite;
    bool activo;
    double ancho;
    double alto;
};

#endif
