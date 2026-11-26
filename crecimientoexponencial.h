#ifndef CRECIMIENTOEXPONENCIAL_H
#define CRECIMIENTOEXPONENCIAL_H

#include "modelofisico.h"

class CrecimientoExponencial : public ModeloFisico {
public:
    CrecimientoExponencial(double v0, double tasaK, double velocidadMax);

    double velocidadActual() const;

    void actualizar(double dt, Vector2D& pos, Vector2D& vel) override;
    void reiniciar() override { tiempo = 0.0; }

    void setEscala(double escala) { this->escala = escala; }
    double getEscala() const { return escala; }
    double getTiempo() const { return tiempo; }

private:
    double v0;
    double tasaK;
    double velocidadMax;
    double escala = 1.0;
    double tiempo = 0.0;
};

#endif
