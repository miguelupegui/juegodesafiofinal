#ifndef VECTOR2D_H
#define VECTOR2D_H

struct Vector2D {
    double x = 0.0;
    double y = 0.0;

    Vector2D() {}
    Vector2D(double x, double y) : x(x), y(y) {}

    Vector2D sumar(const Vector2D& otro) const {
        return Vector2D(x + otro.x, y + otro.y);
    }
    Vector2D escalar(double k) const {
        return Vector2D(x * k, y * k);
    }
};

#endif
