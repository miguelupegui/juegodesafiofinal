#include "crecimientoexponencial.h"
#include "excepciones.h"
#include <cmath>

CrecimientoExponencial::CrecimientoExponencial(double v0, double tasaK, double velocidadMax)
{
    if (v0 <= 0 || tasaK < 0 || velocidadMax < v0)
        throw ExcepcionConfiguracion("tiene que ser v0 > 0, tasaK >= 0 y velocidadMax >= v0");

    this->v0 = v0;
    this->tasaK = tasaK;
    this->velocidadMax = velocidadMax;
}

double CrecimientoExponencial::velocidadActual() const
{
    double v = v0 * exp(tasaK * tiempo);
    if (v > velocidadMax)
        v = velocidadMax;
    return v * escala;
}

void CrecimientoExponencial::actualizar(double dt, Vector2D &pos, Vector2D &vel)
{
    tiempo += dt;
    vel.x = velocidadActual();
    vel.y = 0;
    pos.x += vel.x * dt;
}
