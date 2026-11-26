#include "nivelcabinaavion.h"
#include "maleta.h"
#include "carritovendedor.h"
#include <cstdlib>
#include <iostream>

NivelCabinaAvion::NivelCabinaAvion(Jugador* jugador, const ConfiguracionDificultad& config,
                                   MemoriaAprendizaje* memoria)
    : NivelBase(jugador, false), config(config), fuego(config, memoria, -150.0),
      puerta(LARGO - 200.0, PISO_Y)
{
    salto = nullptr;
    aprendio = false;
    metaRecorrido = LARGO;
}

NivelCabinaAvion::~NivelCabinaAvion() {
    jugador->cambiarModelo(nullptr);
    delete salto;
}

void NivelCabinaAvion::cargarElementos() {
    jugador->reiniciar(260.0, PISO_Y - jugador->getAlto());
    jugador->setLimitesX(0.0, LARGO);
    jugador->setVelocidadBase(config.velocidadPasillo);

    salto = new MovimientoParabolico(1800.0, 760.0, PISO_Y - jugador->getAlto());
    jugador->cambiarModelo(salto);

    camara.setLimites(0, LARGO, 0, 540);
    camara.setTurbulencia(config.turbulencia, 1.4);
    camara.centrarEn(*jugador);

    generarPasillo();
}

void NivelCabinaAvion::generarPasillo() {
    double separacion = 700.0 - 450.0 * config.densidadObstaculos;
    double x = 900.0;
    double fase = 0.0;
    int contador = 0;

    while (x < LARGO - 650.0) {
        int azar = rand() % 10;
        contador++;
        if (azar < 6) {
            int tipo = rand() % 3;
            obstaculos.push_back(new Maleta(x, PISO_Y, tipo));
            x += separacion + rand() % 150;
        } else {
            double amp = config.amplitudCarrito * (0.8 + (rand() % 40) / 100.0);
            double frec = config.frecuenciaCarrito * (0.85 + (rand() % 30) / 100.0);
            x += amp;
            obstaculos.push_back(new CarritoVendedor(x, PISO_Y, amp, frec, fase));
            fase += 1.7;
            x += amp + separacion + rand() % 150;
        }
    }
}

void NivelCabinaAvion::actualizar(double dt) {
    if (estado == EstadoNivel::EN_CURSO) {
        fuego.actualizar(dt, jugador->getHitbox().x);

        double d = distanciaAlFuego();
        if (d < 500.0)
            camara.setFactorTurbulencia(1.0 + 2.5 * (500.0 - d) / 500.0);
        else
            camara.setFactorTurbulencia(1.0);
    }

    NivelBase::actualizar(dt);

    if (estado != EstadoNivel::EN_CURSO && !aprendio) {
        fuego.aprender(tiempoTranscurrido);
        aprendio = true;
        if (estado == EstadoNivel::VICTORIA) {
            puerta.abrir();
            agregarEvento(EventoJuego::PUERTA);
        }
    }
}

bool NivelCabinaAvion::verificarVictoria() {
    return puerta.jugadorLlego(*jugador);
}

bool NivelCabinaAvion::verificarDerrota() {
    if (!jugador->estaVivo())
        return true;
    if (fuego.alcanzo(jugador->getHitbox().x))
        return true;
    return false;
}

double NivelCabinaAvion::distanciaAlFuego() const {
    return jugador->getHitbox().x - fuego.getPosicion().x;
}

double NivelCabinaAvion::progreso() const {
    double inicio = 260.0;
    double fin = puerta.getPosicion().x;
    double p = (jugador->getPosicion().x - inicio) / (fin - inicio);
    if (p < 0)
        p = 0;
    if (p > 1)
        p = 1;
    return p;
}
