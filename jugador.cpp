#include "jugador.h"
#include "movimientoparabolico.h"
#include "caidalibre.h"

Jugador::Jugador(double x, double y)
    : ElementoJuego(x, y, 48, 96, ":/sprites/jugador_0.png")
{
    velocidadBase = 300.0;
    factorVelocidad = 1.25;
    factorGiro = 14.0;
    estado = EstadoJugador::NORMAL;
    vivo = true;
    modeloMovimiento = nullptr;
    direccion = 0;
    mirandoDerecha = true;
    posicionAnterior = Vector2D(x, y);
    tiempoAturdido = 0;
    limiteIzq = 0;
    limiteDer = 100000;
    paracaidasAbierto = false;
    setMargenHitbox(12, 8);
}

void Jugador::moverIzquierda()
{
    direccion = -1;
    mirandoDerecha = false;
}

void Jugador::moverDerecha()
{
    direccion = 1;
    mirandoDerecha = true;
}

void Jugador::detener()
{
    direccion = 0;
}

bool Jugador::saltar()
{
    if (!vivo || estaAturdido())
        return false;

    MovimientoParabolico* salto = dynamic_cast<MovimientoParabolico*>(modeloMovimiento);
    if (salto == nullptr)
        return false;
    if (!salto->estaEnSuelo())
        return false;

    salto->iniciarSalto();
    return true;
}

void Jugador::cambiarModelo(ModeloFisico *m)
{
    modeloMovimiento = m;
    velocidad.y = 0;
}

void Jugador::aplicarEfecto(EstadoJugador e, double segundos)
{
    estado = e;
    temporizador.iniciar(segundos);
    actualizarRalentizacion();
}

bool Jugador::estaInvencible() const
{
    return estado == EstadoJugador::INVENCIBLE;
}

bool Jugador::recibirImpacto()
{
    if (estaInvencible() || !vivo)
        return false;
    vivo = false;
    return true;
}

void Jugador::volverPosicionAnterior()
{
    posicion.x = posicionAnterior.x;
    velocidad.x = 0;
}

void Jugador::empujar(double distancia, double tiempoAturdido)
{
    posicion.x = posicion.x + distancia;
    if (posicion.x < limiteIzq)
        posicion.x = limiteIzq;
    velocidad.x = 0;
    this->tiempoAturdido = tiempoAturdido;
}

void Jugador::abrirParacaidas()
{
    paracaidasAbierto = true;
    actualizarRalentizacion();
}

bool Jugador::estaEnSuelo() const
{
    MovimientoParabolico* salto = dynamic_cast<MovimientoParabolico*>(modeloMovimiento);
    if (salto == nullptr)
        return false;
    return salto->estaEnSuelo();
}

void Jugador::setLimitesX(double minX, double maxX)
{
    limiteIzq = minX;
    limiteDer = maxX;
}

void Jugador::actualizarRalentizacion()
{
    CaidaLibre* caida = dynamic_cast<CaidaLibre*>(modeloMovimiento);
    if (caida == nullptr)
        return;

    if (paracaidasAbierto)
        caida->setRalentizacion(0.3);
    else if (estado == EstadoJugador::RALENTIZADO)
        caida->setRalentizacion(0.5);
    else
        caida->setRalentizacion(1.0);
}

void Jugador::actualizar(double dt)
{
    posicionAnterior = posicion;

    double objetivo = 0;
    if (vivo && tiempoAturdido <= 0)
        objetivo = direccion * velocidadBase * factorVelocidad;
    if (tiempoAturdido > 0)
        tiempoAturdido -= dt;

    double cambio = factorGiro * dt;
    if (cambio > 1)
        cambio = 1;
    velocidad.x = velocidad.x + (objetivo - velocidad.x) * cambio;
    posicion.x = posicion.x + velocidad.x * dt;

    if (posicion.x < limiteIzq)
        posicion.x = limiteIzq;
    if (posicion.x > limiteDer - ancho)
        posicion.x = limiteDer - ancho;

    if (modeloMovimiento != nullptr)
        modeloMovimiento->actualizar(dt, posicion, velocidad);

    if (temporizador.estaActivo()) {
        temporizador.actualizar(dt);
        if (temporizador.haExpirado()) {
            estado = EstadoJugador::NORMAL;
            actualizarRalentizacion();
        }
    }
}

void Jugador::reiniciar(double x, double y)
{
    posicion = Vector2D(x, y);
    posicionAnterior = posicion;
    velocidad = Vector2D(0, 0);
    estado = EstadoJugador::NORMAL;
    temporizador.detener();
    vivo = true;
    activo = true;
    direccion = 0;
    mirandoDerecha = true;
    tiempoAturdido = 0;
    paracaidasAbierto = false;
}
