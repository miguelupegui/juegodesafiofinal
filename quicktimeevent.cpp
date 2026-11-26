#include "quicktimeevent.h"
#include "excepciones.h"
#include <cstdlib>
#include <string>

QuickTimeEvent::QuickTimeEvent(double ventanaTiempo)
{
    if (ventanaTiempo <= 0)
        throw ExcepcionConfiguracion("la ventana del QTE debe ser positiva");

    teclaRequerida = 'A';
    this->ventanaTiempo = ventanaTiempo;
    tiempoRestante = ventanaTiempo;
    activo = false;
    completado = false;
    fallado = false;
}

void QuickTimeEvent::iniciar()
{
    std::string letras = "FGHJKLUION";
    teclaRequerida = letras[rand() % 10];
    tiempoRestante = ventanaTiempo;
    activo = true;
    completado = false;
    fallado = false;
}

void QuickTimeEvent::registrarTecla(char t)
{
    if (!activo)
        return;

    if (t >= 'a' && t <= 'z')
        t = t - 32;

    activo = false;
    if (t == teclaRequerida)
        completado = true;
    else
        fallado = true;
}

void QuickTimeEvent::actualizar(double dt)
{
    if (!activo)
        return;

    tiempoRestante -= dt;
    if (tiempoRestante <= 0) {
        tiempoRestante = 0;
        activo = false;
        fallado = true;
    }
}
