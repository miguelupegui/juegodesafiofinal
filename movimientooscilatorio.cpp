#include "movimientooscilatorio.h"
#include "excepciones.h"
#include <cmath>

#define PI 3.14159265358979

MovimientoOscilatorio::MovimientoOscilatorio(double amplitud, double frecuencia, double fase,
                                             Vector2D origen, Vector2D eje)
    : amplitud(amplitud), frecuencia(frecuencia), fase(fase), origen(origen), eje(eje)
{
    if (amplitud < 0 || frecuencia < 0)
        throw ExcepcionConfiguracion("amplitud y frecuencia no pueden ser negativas");
}

double MovimientoOscilatorio::desplazamiento(double t) const
{
    return amplitud * sin(2 * PI * frecuencia * t + fase);
}

void MovimientoOscilatorio::actualizar(double dt, Vector2D &pos, Vector2D &vel)
{
    tiempo += dt;
    double d = desplazamiento(tiempo);
    double w = 2 * PI * frecuencia;
    double v = amplitud * w * cos(w * tiempo + fase);

    pos.x = origen.x + eje.x * d;
    pos.y = origen.y + eje.y * d;
    vel.x = eje.x * v;
    vel.y = eje.y * v;
}
