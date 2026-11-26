#include "temporizadorefecto.h"

TemporizadorEfecto::TemporizadorEfecto()
{
    duracion = 0;
    tiempoRestante = 0;
    activo = false;
}

void TemporizadorEfecto::iniciar(double segundos)
{
    duracion = segundos;
    tiempoRestante = segundos;
    activo = true;
}

void TemporizadorEfecto::actualizar(double dt)
{
    if (!activo) return;

    tiempoRestante = tiempoRestante - dt;
    if (tiempoRestante <= 0) {
        tiempoRestante = 0;
        activo = false;
    }
}

void TemporizadorEfecto::detener()
{
    tiempoRestante = 0;
    activo = false;
}

bool TemporizadorEfecto::haExpirado() const
{
    if (activo)
        return false;
    return true;
}
