#include "maleta.h"
#include "excepciones.h"

const double ANCHOS_MALETA[3] = {41, 88, 46};
const double ALTOS_MALETA[3] = {78, 56, 46};
const std::string RUTAS_MALETA[3] = {":/sprites/maleta_rodante.png",
                                     ":/sprites/maleta_verde.png",
                                     ":/sprites/mochila.png"};

static int validarTipo(int tipo)
{
    if (tipo < 0 || tipo > 2)
        throw ExcepcionConfiguracion("tipo de maleta no existe");
    return tipo;
}

static double anchoDe(int tipo) { return ANCHOS_MALETA[validarTipo(tipo)]; }
static double altoDe(int tipo) { return ALTOS_MALETA[validarTipo(tipo)]; }
static std::string rutaDe(int tipo) { return RUTAS_MALETA[validarTipo(tipo)]; }

Maleta::Maleta(double x, double pisoY, int tipo)
    : Obstaculo(x, pisoY - altoDe(tipo), anchoDe(tipo), altoDe(tipo), rutaDe(tipo))
{
    this->tipo = tipo;
    setMargenHitbox(4, 4);
}

bool Maleta::colisionar(Jugador &j)
{
    j.volverPosicionAnterior();
    return false;
}

void Maleta::actualizar(double dt)
{
}
