#include "nivelcaidalibre.h"
#include "escombro.h"
#include <cstdlib>

NivelCaidaLibre::NivelCaidaLibre(Jugador* jugador, const ConfiguracionDificultad& config)
    : NivelBase(jugador, true), config(config), zona(ALTURA_SEGURA), qte(1.6)
{
    alturaInicial = 80.0;
    alturaActual = METROS_TOTALES;
    caida = NULL;
    paracaidasAbierto = false;
    metaRecorrido = ALTO_MUNDO;
}

NivelCaidaLibre::~NivelCaidaLibre() {
    jugador->cambiarModelo(nullptr);
    delete caida;
}

void NivelCaidaLibre::cargarElementos() {
    jugador->reiniciar(456.0, alturaInicial);
    jugador->setLimitesX(0.0, 960.0);
    jugador->setVelocidadBase(config.velocidadPasillo);

    caida = new CaidaLibre(900.0, 420.0);
    jugador->cambiarModelo(caida);

    camara.setLimites(0, 960, -200, ALTO_MUNDO + 60);
    camara.setTurbulencia(config.turbulencia, 0.8);
    camara.centrarEn(*jugador);

    generarEscombros();
    generarPowerUps();
}

void NivelCaidaLibre::generarEscombros() {
    int cantidad = config.densidadObstaculos * 70;
    double inicio = 700.0;
    double fin = ALTURA_SEGURA - 500.0;
    double paso = (fin - inicio) / cantidad;

    for (int i = 0; i < cantidad; i++) {
        double y = inicio + i * paso + rand() % 80;
        double x = rand() % 880;
        int tipo = rand() % 5;
        double vt = 80 + rand() % 100;
        double vx = (rand() % 120) - 60;
        obstaculos.push_back(new Escombro(x, y, tipo, vt, vx));
    }
}

void NivelCaidaLibre::generarPowerUps() {
    for (int i = 0; i < 6; i++) {
        double y = 1300.0 + i * 1200.0 + rand() % 300;
        double x = 60 + rand() % 820;
        if (i % 2 == 0)
            powerUps.push_back(new PowerUpVelocidadBaja(x, y));
        else
            powerUps.push_back(new PowerUpInvencibilidad(x, y));
    }
}

void NivelCaidaLibre::actualizar(double dt) {
    NivelBase::actualizar(dt);
    if (estado != EstadoNivel::EN_CURSO)
        return;

    double pies = jugador->getPosicion().y + jugador->getAlto();
    alturaActual = METROS_TOTALES * (ALTO_MUNDO - pies) / (ALTO_MUNDO - alturaInicial);
    if (alturaActual < 0)
        alturaActual = 0;

    if (!qte.yaEmpezo() && zona.jugadorEnZona(*jugador))
        qte.iniciar();

    qte.actualizar(dt);

    if (qte.exito() && !paracaidasAbierto) {
        paracaidasAbierto = true;
        jugador->abrirParacaidas();
        agregarEvento(EventoJuego::PARACAIDAS);
    }
}

void NivelCaidaLibre::teclaEspecial(char tecla) {
    qte.registrarTecla(tecla);
}

bool NivelCaidaLibre::verificarVictoria() {
    double pies = jugador->getPosicion().y + jugador->getAlto();
    if (paracaidasAbierto && pies >= ALTO_MUNDO) {
        jugador->setPosicion(jugador->getPosicion().x, ALTO_MUNDO - jugador->getAlto());
        return true;
    }
    return false;
}

bool NivelCaidaLibre::verificarDerrota() {
    if (!jugador->estaVivo())
        return true;
    if (qte.fallo())
        return true;
    double pies = jugador->getPosicion().y + jugador->getAlto();
    if (paracaidasAbierto == false && pies >= ALTO_MUNDO)
        return true;
    return false;
}
