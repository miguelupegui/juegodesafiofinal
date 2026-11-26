#include "nivelbase.h"

NivelBase::NivelBase(Jugador* jugador, bool vertical)
    : camara(960, 540, vertical)
{
    this->jugador = jugador;
    tiempoTranscurrido = 0;
    metaRecorrido = 0;
    estado = EstadoNivel::EN_CURSO;
}

NivelBase::~NivelBase() {
    limpiarMemoria();
}

void NivelBase::actualizar(double dt) {
    if (estado != EstadoNivel::EN_CURSO)
        return;

    tiempoTranscurrido += dt;
    jugador->actualizar(dt);

    for (int i = 0; i < obstaculos.size(); i++) {
        if (obstaculos[i]->estaActivo())
            obstaculos[i]->actualizar(dt);
    }
    for (int i = 0; i < powerUps.size(); i++) {
        if (powerUps[i]->estaActivo())
            powerUps[i]->actualizar(dt);
    }

    procesarColisiones();
    camara.seguir(*jugador, dt);

    if (verificarDerrota()) {
        estado = EstadoNivel::DERROTA;
        jugador->morir();
        agregarEvento(EventoJuego::DERROTA);
    } else if (verificarVictoria()) {
        estado = EstadoNivel::VICTORIA;
    }
}

void NivelBase::procesarColisiones() {
    for (int i = 0; i < obstaculos.size(); i++) {
        if (obstaculos[i]->estaActivo() && jugador->colisionaCon(*obstaculos[i])) {
            bool fuerte = obstaculos[i]->colisionar(*jugador);
            if (fuerte == true)
                agregarEvento(EventoJuego::GOLPE);
        }
    }
    for (int i = 0; i < powerUps.size(); i++) {
        if (powerUps[i]->estaActivo() && jugador->colisionaCon(*powerUps[i])) {
            powerUps[i]->aplicarEfecto(*jugador);
            agregarEvento(EventoJuego::PODER);
        }
    }
}

void NivelBase::teclaEspecial(char tecla) {
}

void NivelBase::limpiarMemoria() {
    for (int i = 0; i < obstaculos.size(); i++)
        delete obstaculos[i];
    obstaculos.clear();

    for (int i = 0; i < powerUps.size(); i++)
        delete powerUps[i];
    powerUps.clear();
}

std::vector<EventoJuego> NivelBase::sacarEventos() {
    std::vector<EventoJuego> copia = eventos;
    eventos.clear();
    return copia;
}

void NivelBase::agregarEvento(EventoJuego e) {
    eventos.push_back(e);
}
