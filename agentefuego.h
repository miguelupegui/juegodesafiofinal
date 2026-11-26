#ifndef AGENTEFUEGO_H
#define AGENTEFUEGO_H

#include "memoriaaprendizaje.h"
#include "crecimientoexponencial.h"
#include "configuraciondificultad.h"
#include "vector2d.h"

enum class DecisionFuego { MANTENER, ACELERAR };

class AgenteFuego {
public:
    AgenteFuego(const ConfiguracionDificultad& config, MemoriaAprendizaje* memoria,
                double xInicial);

    double percibir(double xJugador);

    void razonar();

    void actuar(double dt);

    void actualizar(double dt, double xJugador);

    void aprender(double tiempoSupervivencia);

    bool alcanzo(double xJugador) const;
    void reiniciar();

    Vector2D getPosicion() const { return posicion; }
    double velocidadActual() const { return velocidad.x; }
    double getFactorVelocidad() const { return factorVelocidad; }
    double getDistancia() const { return distanciaPercibida; }
    DecisionFuego decision() const { return decisionActual; }

private:
    ConfiguracionDificultad config;
    MemoriaAprendizaje* memoria;
    CrecimientoExponencial crecimiento;
    double xInicial;
    Vector2D posicion;
    Vector2D velocidad;
    double factorVelocidad;
    double distanciaPercibida = 0.0;
    DecisionFuego decisionActual = DecisionFuego::MANTENER;
};

#endif
