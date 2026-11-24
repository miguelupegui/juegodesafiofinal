#ifndef RECTANGULO_H
#define RECTANGULO_H

// Rectángulo alineado a los ejes. (x, y) es la esquina superior izquierda.
// Se usa como hitbox: más pequeño que el sprite para que las colisiones
// se sientan justas.
struct Rectangulo {
    double x = 0.0;
    double y = 0.0;
    double ancho = 0.0;
    double alto = 0.0;

    Rectangulo() = default;
    Rectangulo(double x_, double y_, double ancho_, double alto_)
        : x(x_), y(y_), ancho(ancho_), alto(alto_) {}

    // Dos rectángulos que solo se tocan por el borde NO se consideran en colisión.
    bool intersecta(const Rectangulo& otro) const {
        return x < otro.x + otro.ancho && x + ancho > otro.x &&
               y < otro.y + otro.alto && y + alto > otro.y;
    }
};

#endif