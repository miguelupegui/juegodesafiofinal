#ifndef NIVELBASE_H
#define NIVELBASE_H

#include <vector>

#include "jugador.h"
#include "obstaculo.h"
#include "powerup.h"
#include "camara.h"

enum class EstadoNivel { EN_CURSO, VICTORIA, DERROTA };

enum class EventoJuego { SALTO, GOLPE, PODER, PUERTA, PARACAIDAS, DERROTA };

class NivelBase {
public:
    NivelBase(Jugador* jugador, bool vertical);
    virtual ~NivelBase();

    virtual void cargarElementos() = 0;
    virtual void actualizar(double dt);
    virtual bool verificarVictoria() = 0;
    virtual bool verificarDerrota() = 0;
    virtual void procesarColisiones();
    virtual void teclaEspecial(char tecla);
    virtual int getNumero() const = 0;

    void limpiarMemoria();

    std::vector<EventoJuego> sacarEventos();
    void agregarEvento(EventoJuego e);

    const std::vector<Obstaculo*>& getObstaculos() const { return obstaculos; }
    const std::vector<PowerUp*>& getPowerUps() const { return powerUps; }
    Jugador* getJugador() const { return jugador; }
    const Camara& getCamara() const { return camara; }
    EstadoNivel getEstado() const { return estado; }
    double getTiempo() const { return tiempoTranscurrido; }
    double getMetaRecorrido() const { return metaRecorrido; }

protected:
    std::vector<Obstaculo*> obstaculos;
    std::vector<PowerUp*> powerUps;
    Jugador* jugador;
    Camara camara;
    double tiempoTranscurrido;
    double metaRecorrido;
    EstadoNivel estado;
    std::vector<EventoJuego> eventos;
};

#endif
