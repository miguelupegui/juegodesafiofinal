#include "movimientoparabolico.h"
#include "excepciones.h"
#include <cmath>

MovimientoParabolico::MovimientoParabolico(double gravedad, double velocidadSalto, double sueloY)
    : gravedad(gravedad), velocidadSalto(velocidadSalto), sueloY(sueloY)
{
    if (gravedad <= 0 || velocidadSalto <= 0) {
        throw ExcepcionConfiguracion("gravedad y velocidadSalto deben ser positivas");
    }
}

void MovimientoParabolico::iniciarSalto()
{
    if (enSuelo == true) {
        impulsoPendiente = true;
        enSuelo = false;
    }
}

void MovimientoParabolico::actualizar(double dt, Vector2D &pos, Vector2D &vel)
{
    if (impulsoPendiente) {
        vel.y = -velocidadSalto;
        impulsoPendiente = false;
    }
    if (enSuelo)
        return;

    pos.y = pos.y + vel.y * dt + 0.5 * gravedad * pow(dt, 2);
    vel.y = vel.y + gravedad * dt;

    if (pos.y >= sueloY) {
        pos.y = sueloY;
        vel.y = 0;
        enSuelo = true;
    }
}

void MovimientoParabolico::reiniciar()
{
    enSuelo = true;
    impulsoPendiente = false;
}

double MovimientoParabolico::alturaMaxima() const
{
    return pow(velocidadSalto, 2) / (2 * gravedad);
}
