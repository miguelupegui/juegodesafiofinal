#ifndef MODELOFISICO_H
#define MODELOFISICO_H

#include "vector2d.h"

class ModeloFisico {
public:
    virtual ~ModeloFisico() {}

    virtual void actualizar(double dt, Vector2D& pos, Vector2D& vel) = 0;

    virtual void reiniciar() = 0;
};

#endif
