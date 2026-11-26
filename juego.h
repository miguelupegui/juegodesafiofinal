#ifndef JUEGO_H
#define JUEGO_H

#include "jugador.h"
#include "nivelbase.h"
#include "memoriaaprendizaje.h"
#include "configuraciondificultad.h"

class Juego {
public:
    Juego(Dificultad dificultad);
    ~Juego();

    void iniciarNivel(int n);
    void siguienteNivel();
    void reiniciarNivel();
    void actualizar(double dt);
    void gameOver();

    NivelBase* getNivel() const { return nivelActual; }
    Jugador* getJugador() const { return jugador; }
    const MemoriaAprendizaje* getMemoria() const { return memoria; }
    const ConfiguracionDificultad& getConfig() const { return config; }
    Dificultad getDificultad() const { return dificultad; }
    int getIndiceNivel() const { return indiceNivel; }
    int getMuertes() const { return muertes; }
    bool esUltimoNivel() const { return indiceNivel == 2; }

private:
    Jugador* jugador;
    NivelBase* nivelActual;
    int indiceNivel;
    MemoriaAprendizaje* memoria;
    ConfiguracionDificultad config;
    Dificultad dificultad;
    int muertes;
    bool contoMuerte;
};

#endif
