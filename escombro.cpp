#include "escombro.h"
#include "excepciones.h"

const double ANCHOS_ESCOMBRO[5] = {56, 76, 62, 53, 46};
const double ALTOS_ESCOMBRO[5] = {72, 62, 50, 38, 50};
const std::string RUTAS_ESCOMBRO[5] = {":/sprites/escombro_silla.png",
                                       ":/sprites/escombro_motor.png",
                                       ":/sprites/escombro_maletin.png",
                                       ":/sprites/escombro_cojin.png",
                                       ":/sprites/escombro_mochila.png"};

static int validarTipo(int tipo)
{
    if (tipo < 0 || tipo > 4)
        throw ExcepcionConfiguracion("tipo de escombro no existe");
    return tipo;
}

static double anchoDe(int tipo) { return ANCHOS_ESCOMBRO[validarTipo(tipo)]; }
static double altoDe(int tipo) { return ALTOS_ESCOMBRO[validarTipo(tipo)]; }
static std::string rutaDe(int tipo) { return RUTAS_ESCOMBRO[validarTipo(tipo)]; }

Escombro::Escombro(double x, double y, int tipo, double velocidadTerminal, double velocidadX)
    : Obstaculo(x, y, anchoDe(tipo), altoDe(tipo), rutaDe(tipo)),
      caida(600.0, velocidadTerminal)
{
    angulo = 0;
    tamano = ANCHOS_ESCOMBRO[tipo] * ALTOS_ESCOMBRO[tipo];
    velocidad.x = velocidadX;

    velocidadGiro = 9000.0 / ANCHOS_ESCOMBRO[tipo];
    if (velocidadX < 0)
        velocidadGiro = -velocidadGiro;

    setMargenHitbox(10, 10);
}

bool Escombro::colisionar(Jugador &j)
{
    if (j.estaInvencible()) {
        desactivar();
        return true;
    }
    j.recibirImpacto();
    return true;
}

void Escombro::actualizar(double dt)
{
    caida.actualizar(dt, posicion, velocidad);
    posicion.x += velocidad.x * dt;

    if (posicion.x < 0) {
        posicion.x = 0;
        velocidad.x = -velocidad.x;
    }
    if (posicion.x + ancho > 960) {
        posicion.x = 960 - ancho;
        velocidad.x = -velocidad.x;
    }

    angulo = angulo + velocidadGiro * dt;
    if (angulo > 360) angulo -= 360;
    if (angulo < -360) angulo += 360;
}
