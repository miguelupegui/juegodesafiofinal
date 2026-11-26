#include "juego.h"
#include "nivelcabinaavion.h"
#include "nivelcaidalibre.h"
#include "excepciones.h"
#include <string>

Juego::Juego(Dificultad dificultad)
{
    nivelActual = nullptr;
    indiceNivel = 0;
    this->dificultad = dificultad;
    muertes = 0;
    contoMuerte = false;

    config.aplicarDificultad(dificultad);
    jugador = new Jugador(0, 0);
    memoria = new MemoriaAprendizaje(config.tiempoObjetivo, config.tasaAprendizaje,
                                      config.factorMin, config.factorMax);
}

Juego::~Juego() {
    delete nivelActual;
    delete jugador;
    delete memoria;
}

void Juego::iniciarNivel(int n) {
    if (n != 1 && n != 2)
        throw ExcepcionConfiguracion("no existe el nivel " + std::to_string(n));

    delete nivelActual;
    nivelActual = nullptr;

    if (n == 1) {
        nivelActual = new NivelCabinaAvion(jugador, config, memoria);
    } else {
        ConfiguracionDificultad config2;
        config2.cargarPreset(2);
        nivelActual = new NivelCaidaLibre(jugador, config2);
    }
    nivelActual->cargarElementos();
    indiceNivel = n;
    contoMuerte = false;
}

void Juego::siguienteNivel() {
    iniciarNivel(indiceNivel + 1);
}

void Juego::reiniciarNivel() {
    iniciarNivel(indiceNivel);
}

void Juego::actualizar(double dt) {
    if (nivelActual == nullptr)
        return;
    nivelActual->actualizar(dt);

    if (nivelActual->getEstado() == EstadoNivel::DERROTA && !contoMuerte)
        gameOver();
}

void Juego::gameOver() {
    muertes++;
    contoMuerte = true;
}
