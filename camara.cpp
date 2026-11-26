#include "camara.h"

Camara::Camara(double anchoVista, double altoVista, bool modoVertical)
    : oscilacion(3.0, 1.5, 0.0, Vector2D(0, 0), modoVertical ? Vector2D(1, 0) : Vector2D(0, 1))
{
    posicion = Vector2D(0, 0);
    this->modoVertical = modoVertical;
    factorTurbulencia = 1.0;
    this->anchoVista = anchoVista;
    this->altoVista = altoVista;
    minX = 0;
    maxX = anchoVista;
    minY = 0;
    maxY = altoVista;
}

void Camara::setLimites(double minX, double maxX, double minY, double maxY) {
    this->minX = minX;
    this->maxX = maxX;
    this->minY = minY;
    this->maxY = maxY;
}

void Camara::setTurbulencia(double amplitud, double frecuencia) {
    Vector2D eje;
    if (modoVertical)
        eje = Vector2D(1, 0);
    else
        eje = Vector2D(0, 1);
    oscilacion = MovimientoOscilatorio(amplitud, frecuencia, 0.0, Vector2D(0, 0), eje);
}

void Camara::seguir(const ElementoJuego& objetivo, double dt) {
    double objX = posicion.x;
    double objY = posicion.y;

    if (modoVertical) {
        objY = objetivo.getPosicion().y - altoVista * 0.25;
    } else {
        objX = objetivo.getPosicion().x - anchoVista * 0.35;
    }

    double suave = 8.0 * dt;
    if (suave > 1.0)
        suave = 1.0;
    posicion.x += (objX - posicion.x) * suave;
    posicion.y += (objY - posicion.y) * suave;
    limitar();

    oscilacion.actualizar(dt, temblor, velTemblor);
}

void Camara::centrarEn(const ElementoJuego& objetivo) {
    if (modoVertical)
        posicion.y = objetivo.getPosicion().y - altoVista * 0.25;
    else
        posicion.x = objetivo.getPosicion().x - anchoVista * 0.35;
    limitar();
}

void Camara::limitar() {
    if (posicion.x < minX)
        posicion.x = minX;
    if (posicion.x > maxX - anchoVista)
        posicion.x = maxX - anchoVista;
    if (posicion.y < minY)
        posicion.y = minY;
    if (posicion.y > maxY - altoVista)
        posicion.y = maxY - altoVista;
}

Vector2D Camara::getPosicion() const {
    return posicion.sumar(temblor.escalar(factorTurbulencia));
}
