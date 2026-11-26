#ifndef JUGADOR_H
#define JUGADOR_H

#include "elementojuego.h"
#include "temporizadorefecto.h"
#include "modelofisico.h"

enum class EstadoJugador { NORMAL, INVENCIBLE, RALENTIZADO };

class Jugador : public ElementoJuego {
public:
    Jugador(double x, double y);

    void moverIzquierda();
    void moverDerecha();
    void detener();
    bool saltar();

    void cambiarModelo(ModeloFisico* m);
    ModeloFisico* getModelo() { return modeloMovimiento; }

    void aplicarEfecto(EstadoJugador e, double segundos);
    bool recibirImpacto();
    bool estaInvencible() const;

    void volverPosicionAnterior();
    void empujar(double distancia, double tiempoAturdido);

    void abrirParacaidas();
    bool tieneParacaidas() const { return paracaidasAbierto; }

    void actualizar(double dt);
    void reiniciar(double x, double y);

    void setLimitesX(double minX, double maxX);
    void setVelocidadBase(double v) { velocidadBase = v; }

    bool estaVivo() const { return vivo; }
    void morir() { vivo = false; }
    bool estaEnSuelo() const;
    bool estaAturdido() const { return tiempoAturdido > 0.0; }
    bool miraDerecha() const { return mirandoDerecha; }
    EstadoJugador getEstado() const { return estado; }
    TemporizadorEfecto getTemporizador() const { return temporizador; }

private:
    void actualizarRalentizacion();

    double velocidadBase;
    double factorVelocidad;
    double factorGiro;
    EstadoJugador estado;
    bool vivo;
    TemporizadorEfecto temporizador;
    ModeloFisico* modeloMovimiento;

    int direccion;
    bool mirandoDerecha;
    Vector2D posicionAnterior;
    double tiempoAturdido;
    double limiteIzq;
    double limiteDer;
    bool paracaidasAbierto;
};

#endif
