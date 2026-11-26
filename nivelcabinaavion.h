#ifndef NIVELCABINAAVION_H
#define NIVELCABINAAVION_H

#include "nivelbase.h"
#include "agentefuego.h"
#include "puerta.h"
#include "configuraciondificultad.h"
#include "memoriaaprendizaje.h"
#include "movimientoparabolico.h"

class NivelCabinaAvion : public NivelBase {
public:
    static constexpr double PISO_Y = 495.0;
    static constexpr double LARGO = 7600.0;

    NivelCabinaAvion(Jugador* jugador, const ConfiguracionDificultad& config,
                     MemoriaAprendizaje* memoria);
    ~NivelCabinaAvion();

    void cargarElementos() override;
    void generarPasillo();

    void actualizar(double dt) override;
    bool verificarVictoria() override;
    bool verificarDerrota() override;
    int getNumero() const override { return 1; }

    const AgenteFuego& getFuego() const { return fuego; }
    const Puerta& getPuerta() const { return puerta; }
    double distanciaAlFuego() const;
    double progreso() const;

private:
    ConfiguracionDificultad config;
    AgenteFuego fuego;
    Puerta puerta;
    MovimientoParabolico* salto;
    bool aprendio;
};

#endif
