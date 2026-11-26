#ifndef CAIDALIBRE_H
#define CAIDALIBRE_H

#include "modelofisico.h"

class CaidaLibre : public ModeloFisico {
public:
    CaidaLibre(double gravedad, double velocidadTerminal);

    void setRalentizacion(double f);
    double getRalentizacion() const { return factorRalentizacion; }
    double velocidadTerminalActual() const;

    void actualizar(double dt, Vector2D& pos, Vector2D& vel) override;
    void reiniciar() override;

private:
    double gravedad;
    double coefArrastre;
    double velocidadTerminal;
    double factorRalentizacion;
};

#endif
