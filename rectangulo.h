#ifndef RECTANGULO_H
#define RECTANGULO_H

struct Rectangulo {
    double x = 0.0;
    double y = 0.0;
    double ancho = 0.0;
    double alto = 0.0;

    Rectangulo() {}
    Rectangulo(double x, double y, double ancho, double alto)
        : x(x), y(y), ancho(ancho), alto(alto) {}

    bool intersecta(const Rectangulo& otro) const {
        if (x >= otro.x + otro.ancho) return false;
        if (x + ancho <= otro.x) return false;
        if (y >= otro.y + otro.alto) return false;
        if (y + alto <= otro.y) return false;
        return true;
    }
};

#endif
