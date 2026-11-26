#ifndef MOVIMIENTOPARABOLICO_H
#define MOVIMIENTOPARABOLICO_H

#include "modelofisico.h"

class MovimientoParabolico : public ModeloFisico {
public:
    MovimientoParabolico(double gravedad, double velocidadSalto, double sueloY);

    void iniciarSalto();

    void actualizar(double dt, Vector2D& pos, Vector2D& vel) override;
    void reiniciar() override;

    bool estaEnSuelo() const { return enSuelo; }
    void setSueloY(double sueloY) { this->sueloY = sueloY; }
    double getSueloY() const { return sueloY; }

    double alturaMaxima() const;

private:
    double gravedad;
    double velocidadSalto;
    double sueloY;
    bool enSuelo = true;
    bool impulsoPendiente = false;
};

#endif
