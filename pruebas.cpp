#include <iostream>
#include <cmath>
#include <string>

#include "excepciones.h"
#include "movimientoparabolico.h"
#include "crecimientoexponencial.h"
#include "movimientooscilatorio.h"
#include "caidalibre.h"
#include "memoriaaprendizaje.h"
#include "agentefuego.h"
#include "configuraciondificultad.h"
#include "quicktimeevent.h"
#include "jugador.h"
#include "maleta.h"
#include "powerup.h"
#include "juego.h"
#include "nivelcabinaavion.h"

using namespace std;

int buenas = 0;
int hechas = 0;

void revisar(bool seCumple, string queSeEspera) {
    hechas++;
    if (seCumple) {
        buenas++;
        cout << "[ BIEN ] " << queSeEspera << endl;
    } else {
        cout << "[ MAL  ] " << queSeEspera << "   <-----" << endl;
    }
}

void seccion(string nombre) {
    cout << endl << "== " << nombre << " ==" << endl;
}

void pruebasFisicas() {
    seccion("Fisicas");

    MovimientoParabolico salto(1800, 760, 400);
    Vector2D pos(0, 400), vel(0, 0);
    salto.iniciarSalto();
    double alturaMinima = 400;
    for (int i = 0; i < 120; i++) {
        salto.actualizar(1.0 / 60, pos, vel);
        if (pos.y < alturaMinima)
            alturaMinima = pos.y;
    }
    double subio = 400 - alturaMinima;
    revisar(std::fabs(subio - salto.alturaMaxima()) < 15, "el salto sube mas o menos v^2/2g");
    revisar(salto.estaEnSuelo() && pos.y == 400, "despues del salto vuelve al suelo");

    CrecimientoExponencial fuego(100, 0.1, 300);
    Vector2D pf, vf;
    fuego.actualizar(1.0, pf, vf);
    double v1 = vf.x;
    fuego.actualizar(1.0, pf, vf);
    revisar(vf.x > v1, "la velocidad del fuego crece con el tiempo");
    for (int i = 0; i < 100; i++)
        fuego.actualizar(1.0, pf, vf);
    revisar(vf.x <= 300.0001, "la velocidad del fuego no pasa del maximo");

    MovimientoOscilatorio osc(50, 0.5);
    Vector2D po, vo;
    bool dentro = true;
    for (int i = 0; i < 200; i++) {
        osc.actualizar(0.05, po, vo);
        if (std::fabs(po.x) > 50.0001)
            dentro = false;
    }
    revisar(dentro, "el oscilatorio nunca se sale de la amplitud");
    revisar(std::fabs(osc.desplazamiento(0) - osc.desplazamiento(2.0)) < 0.0001, "con f = 0.5 Hz se repite cada 2 s");

    CaidaLibre caida(900, 420);
    Vector2D pc, vc;
    for (int i = 0; i < 600; i++)
        caida.actualizar(1.0 / 60, pc, vc);
    revisar(std::fabs(vc.y - 420) < 5, "la caida llega a la velocidad terminal");
    caida.setRalentizacion(0.5);
    for (int i = 0; i < 600; i++)
        caida.actualizar(1.0 / 60, pc, vc);
    revisar(std::fabs(vc.y - 210) < 5, "con el reloj la velocidad terminal baja a la mitad");
}

void pruebasExcepciones() {
    seccion("Excepciones");

    bool lanzo = false;
    try {
        CaidaLibre mala(-10, 100);
    } catch (ExcepcionConfiguracion& e) {
        lanzo = true;
    }
    revisar(lanzo, "gravedad negativa lanza ExcepcionConfiguracion");

    lanzo = false;
    try {
        ConfiguracionDificultad c;
        c.cargarPreset(5);
    } catch (ExcepcionJuego& e) {
        lanzo = true;
    }
    revisar(lanzo, "un nivel que no existe lanza excepcion");

    lanzo = false;
    try {
        Maleta m(0, 100, 7);
    } catch (ExcepcionConfiguracion& e) {
        lanzo = true;
    }
    revisar(lanzo, "un tipo de maleta que no existe lanza excepcion");

    lanzo = false;
    try {
        Juego j(Dificultad::NORMAL);
        j.iniciarNivel(3);
    } catch (ExcepcionConfiguracion& e) {
        lanzo = true;
    }
    revisar(lanzo, "iniciar el nivel 3 lanza excepcion");
}

void pruebasAgente() {
    seccion("Agente inteligente (fuego)");

    ConfiguracionDificultad config;
    config.cargarPreset(1);
    MemoriaAprendizaje memoria(config.tiempoObjetivo, config.tasaAprendizaje,
                               config.factorMin, config.factorMax);
    AgenteFuego fuego(config, &memoria, 0);

    double d = fuego.percibir(500);
    revisar(d == 500, "percibe la distancia al jugador");

    fuego.razonar();
    revisar(fuego.decision() == DecisionFuego::MANTENER, "lejos del jugador decide MANTENER");
    fuego.percibir(100);
    fuego.razonar();
    revisar(fuego.decision() == DecisionFuego::ACELERAR, "cerca del jugador decide ACELERAR");

    double antes = fuego.getPosicion().x;
    fuego.actuar(0.5);
    revisar(fuego.getPosicion().x > antes, "al actuar el fuego avanza");

    fuego.aprender(40);
    revisar(memoria.getFactorActual() > 1.0, "si el jugador dura mucho, el fuego se vuelve mas rapido");
    fuego.aprender(3);
    fuego.aprender(3);
    revisar(memoria.getFactorActual() < 1.0, "si lo atrapa rapido, el fuego se calma");
    revisar(memoria.intentos() == 3, "la memoria guarda los 3 intentos");

    for (int i = 0; i < 50; i++)
        memoria.registrar(100);
    revisar(memoria.getFactorActual() <= config.factorMax, "el factor no pasa del maximo");

    ConfiguracionDificultad facil, dificil;
    facil.aplicarDificultad(Dificultad::FACIL);
    dificil.aplicarDificultad(Dificultad::DIFICIL);
    revisar(dificil.umbralCercania > facil.umbralCercania, "en dificil el fuego detecta al jugador desde mas lejos");
    revisar(dificil.tasaAprendizaje > facil.tasaAprendizaje, "en dificil el fuego aprende mas rapido");
}

void pruebasJugador() {
    seccion("Jugador, poderes y QTE");

    Jugador j(0, 0);
    CaidaLibre caida(900, 420);
    j.cambiarModelo(&caida);

    PowerUpInvencibilidad estrella(0, 0);
    estrella.aplicarEfecto(j);
    revisar(j.estaInvencible(), "la estrella lo vuelve invencible");
    revisar(!j.recibirImpacto() && j.estaVivo(), "invencible no se muere con un golpe");
    for (int i = 0; i < 8 * 60; i++)
        j.actualizar(1.0 / 60);
    revisar(!j.estaInvencible(), "a los 7 segundos se le acaba el poder");
    revisar(j.recibirImpacto() && !j.estaVivo(), "sin poder un golpe lo mata");

    Jugador j2(0, 0);
    j2.cambiarModelo(&caida);
    PowerUpVelocidadBaja reloj(0, 0);
    reloj.aplicarEfecto(j2);
    revisar(caida.getRalentizacion() == 0.5, "el reloj hace que caiga mas despacio");
    j2.cambiarModelo(nullptr);

    QuickTimeEvent qte(1.5);
    qte.iniciar();
    qte.registrarTecla(qte.getTecla());
    revisar(qte.exito(), "QTE: la tecla correcta abre el paracaidas");

    qte.iniciar();
    qte.registrarTecla('Z');
    revisar(qte.fallo(), "QTE: una tecla equivocada falla");

    qte.iniciar();
    qte.actualizar(2.0);
    revisar(qte.fallo(), "QTE: si se acaba el tiempo falla");
}

void pruebasNivel() {
    seccion("Nivel 1 completo");

    Juego juego(Dificultad::NORMAL);
    juego.iniciarNivel(1);
    revisar(juego.getNivel()->getObstaculos().size() > 0, "el pasillo tiene obstaculos");

    double t = 0;
    while (juego.getNivel()->getEstado() == EstadoNivel::EN_CURSO && t < 60) {
        juego.actualizar(1.0 / 60);
        t += 1.0 / 60;
    }
    revisar(juego.getNivel()->getEstado() == EstadoNivel::DERROTA, "quieto, el fuego lo alcanza");
    revisar(juego.getMuertes() == 1, "se cuenta la muerte");
    revisar(juego.getMemoria()->intentos() == 1, "el fuego guardo el intento en su memoria");

    juego.reiniciarNivel();
    revisar(juego.getNivel()->getEstado() == EstadoNivel::EN_CURSO, "al reiniciar el nivel vuelve a empezar");
    revisar(juego.getMemoria()->intentos() == 1, "la memoria no se borra al reiniciar");
}

int main() {
    srand(1);
    cout << "PRUEBAS DE LA CAPA LOGICA - Escape del Avion" << endl;

    pruebasFisicas();
    pruebasExcepciones();
    pruebasAgente();
    pruebasJugador();
    pruebasNivel();

    cout << endl << "Pasaron " << buenas << " de " << hechas << " pruebas" << endl;
    return 0;
}
