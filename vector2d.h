#ifndef VECTOR2D_H
#define VECTOR2D_H

// Vector 2D. Convención de pantalla (igual que Qt): x crece a la derecha,
// y crece hacia ABAJO.
struct Vector2D {
    double x = 0.0;
    double y = 0.0;

    Vector2D() = default;
    Vector2D(double x_, double y_) : x(x_), y(y_) {}

    Vector2D sumar(const Vector2D& otro) const { return {x + otro.x, y + otro.y}; }
    Vector2D escalar(double k) const { return {x * k, y * k}; }
};

#endif
