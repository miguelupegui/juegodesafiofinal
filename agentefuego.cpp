#include "agente/agentefuego.h"

#include "nucleo/excepciones.h"

AgenteFuego::AgenteFuego(const ConfiguracionDificultad& config, MemoriaAprendizaje* memoria,
                         double xInicial)
    : config_(config), memoria_(memoria),
      crecimiento_(config.velocidadBaseFuego, config.tasaCrecimientoFuego, config.velocidadMaxFuego),
      xInicial_(xInicial), posicion_(xInicial, 0.0),
      factorVelocidad_(memoria ? memoria->factorActual() : 1.0) {
    if (!memoria_)
        throw ExcepcionConfiguracion("AgenteFuego necesita una MemoriaAprendizaje");
}

double AgenteFuego::percibir(double xJugador) {
    distanciaPercibida_ = xJugador - posicion_.x;
    return distanciaPercibida_;
}

void AgenteFuego::razonar() {
    decisionActual_ = (distanciaPercibida_ < config_.umbralCercania)
                          ? DecisionFuego::ACELERAR
                          : DecisionFuego::MANTENER;
}

void AgenteFuego::actuar(double dt) {
    const double boost = (decisionActual_ == DecisionFuego::ACELERAR) ? config_.factorAceleracion : 1.0;
    crecimiento_.setEscala(factorVelocidad_ * boost);
    crecimiento_.actualizar(dt, posicion_, velocidad_);
}

void AgenteFuego::actualizar(double dt, double xJugador) {
    percibir(xJugador);
    razonar();
    actuar(dt);
}

void AgenteFuego::aprender(double tiempoSupervivencia) {
    memoria_->registrar(tiempoSupervivencia);
    factorVelocidad_ = memoria_->factorActual();
}

bool AgenteFuego::alcanzo(double xJugador) const {
    return posicion_.x >= xJugador;
}

void AgenteFuego::reiniciar() {
    crecimiento_.reiniciar();
    posicion_ = Vector2D(xInicial_, 0.0);
    velocidad_ = Vector2D();
    factorVelocidad_ = memoria_->factorActual();
    distanciaPercibida_ = 0.0;
    decisionActual_ = DecisionFuego::MANTENER;
}
