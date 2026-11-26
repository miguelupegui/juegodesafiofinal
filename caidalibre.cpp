#include "caidalibre.h"
#include "excepciones.h"
#include <cmath>

CaidaLibre::CaidaLibre(double gravedad, double velocidadTerminal)
{
    if (gravedad <= 0 || velocidadTerminal <= 0)
        throw ExcepcionConfiguracion("la gravedad y la velocidad terminal deben ser positivas");

    this->gravedad = gravedad;
    this->velocidadTerminal = velocidadTerminal;
    factorRalentizacion = 1.0;
    coefArrastre = gravedad / pow(velocidadTerminal, 2);
}

void CaidaLibre::setRalentizacion(double f)
{
    if (f <= 0 || f > 1)
        throw ExcepcionConfiguracion("el factor de ralentizacion debe estar entre 0 y 1");
    factorRalentizacion = f;
}

double CaidaLibre::velocidadTerminalActual() const
{
    return velocidadTerminal * factorRalentizacion;
}

void CaidaLibre::actualizar(double dt, Vector2D &pos, Vector2D &vel)
{
    double vt = velocidadTerminalActual();
    coefArrastre = gravedad / pow(vt, 2);

    double a = gravedad - coefArrastre * vel.y * fabs(vel.y);
    double nuevaVel = vel.y + a * dt;

    if (vel.y > vt && nuevaVel < vt)
        nuevaVel = vt;

    vel.y = nuevaVel;
    pos.y += vel.y * dt;
}

void CaidaLibre::reiniciar()
{
    factorRalentizacion = 1.0;
    coefArrastre = gravedad / pow(velocidadTerminal, 2);
}
