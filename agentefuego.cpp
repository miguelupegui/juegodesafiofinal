#include "agentefuego.h"
#include "excepciones.h"

AgenteFuego::AgenteFuego(const ConfiguracionDificultad& config, MemoriaAprendizaje* memoria,
                         double xInicial)
    : config(config), memoria(memoria),
      crecimiento(config.velocidadBaseFuego, config.tasaCrecimientoFuego, config.velocidadMaxFuego),
      xInicial(xInicial), posicion(xInicial, 0.0)
{
    if (memoria == NULL)
        throw ExcepcionConfiguracion("AgenteFuego necesita una MemoriaAprendizaje");
    factorVelocidad = memoria->getFactorActual();
}

double AgenteFuego::percibir(double xJugador)
{
    distanciaPercibida = xJugador - posicion.x;
    return distanciaPercibida;
}

void AgenteFuego::razonar()
{
    if (distanciaPercibida < config.umbralCercania)
        decisionActual = DecisionFuego::ACELERAR;
    else
        decisionActual = DecisionFuego::MANTENER;
}

void AgenteFuego::actuar(double dt)
{
    double boost = 1.0;
    if (decisionActual == DecisionFuego::ACELERAR)
        boost = config.factorAceleracion;

    crecimiento.setEscala(factorVelocidad * boost);
    crecimiento.actualizar(dt, posicion, velocidad);
}

void AgenteFuego::actualizar(double dt, double xJugador)
{
    percibir(xJugador);
    razonar();
    actuar(dt);
}

void AgenteFuego::aprender(double tiempoSupervivencia)
{
    memoria->registrar(tiempoSupervivencia);
    factorVelocidad = memoria->getFactorActual();
}

bool AgenteFuego::alcanzo(double xJugador) const
{
    if (posicion.x >= xJugador)
        return true;
    else
        return false;
}

void AgenteFuego::reiniciar()
{
    crecimiento.reiniciar();
    posicion = Vector2D(xInicial, 0.0);
    velocidad = Vector2D();
    factorVelocidad = memoria->getFactorActual();
    distanciaPercibida = 0.0;
    decisionActual = DecisionFuego::MANTENER;
}
