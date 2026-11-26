#ifndef CAMARA_H
#define CAMARA_H

#include "vector2d.h"
#include "elementojuego.h"
#include "movimientooscilatorio.h"

class Camara {
public:
    Camara(double anchoVista, double altoVista, bool modoVertical);

    void setLimites(double minX, double maxX, double minY, double maxY);
    void setTurbulencia(double amplitud, double frecuencia);
    void setFactorTurbulencia(double f) { factorTurbulencia = f; }

    void seguir(const ElementoJuego& objetivo, double dt);
    void centrarEn(const ElementoJuego& objetivo);

    Vector2D getPosicion() const;
    bool esVertical() const { return modoVertical; }

private:
    void limitar();

    Vector2D posicion;
    bool modoVertical;
    MovimientoOscilatorio oscilacion;
    Vector2D temblor;
    Vector2D velTemblor;
    double factorTurbulencia;
    double anchoVista;
    double altoVista;
    double minX, maxX, minY, maxY;
};

#endif
