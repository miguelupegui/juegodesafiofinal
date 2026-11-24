#ifndef AGENTEFUEGO_H
#define AGENTEFUEGO_H

#include "agente/memoriaaprendizaje.h"
#include "fisica/crecimientoexponencial.h"
#include "niveles/configuraciondificultad.h"
#include "utilidades/vector2d.h"

// Decisión que toma el agente en cada actualización.
enum class DecisionFuego { MANTENER, ACELERAR };

// Agente inteligente del nivel 1: el fuego.
// Ciclo: percibir -> razonar -> actuar, y aprender al terminar cada intento.
//
// Es lógica pura. El sprite/partículas del fuego solo leen posicion().x.
// El frente del fuego es posicion().x; el jugador es alcanzado cuando el
// frente llega a su coordenada X.
class AgenteFuego {
public:
    // memoria: no puede ser nula y NO es propiedad del agente (la posee Juego).
    AgenteFuego(const ConfiguracionDificultad& config, MemoriaAprendizaje* memoria,
                double xInicial);

    // 1. Percepción: distancia en X entre el jugador y el frente del fuego.
    double percibir(double xJugador);

    // 2. Razonamiento: decide MANTENER o ACELERAR según la distancia percibida.
    void razonar();

    // 3. Acción: modifica la posición X del fuego.
    void actuar(double dt);

    // Un tick completo: percibir + razonar + actuar.
    void actualizar(double dt, double xJugador);

    // 4. Aprendizaje: registra cuánto sobrevivió el jugador en este intento.
    void aprender(double tiempoSupervivencia);

    bool alcanzo(double xJugador) const;

    // Deja al agente listo para un nuevo intento
    void reiniciar();

    const Vector2D& posicion() const { return posicion_; }
    double velocidadActual() const { return velocidad_.x; }
    double factorVelocidad() const { return factorVelocidad_; }
    double distanciaPercibida() const { return distanciaPercibida_; }
    DecisionFuego decision() const { return decisionActual_; }

private:
    ConfiguracionDificultad config_;
    MemoriaAprendizaje* memoria_;       // no propietario
    CrecimientoExponencial crecimiento_;
    double xInicial_;
    Vector2D posicion_;
    Vector2D velocidad_;
    double factorVelocidad_;
    double distanciaPercibida_ = 0.0;
    DecisionFuego decisionActual_ = DecisionFuego::MANTENER;
};

#endif
