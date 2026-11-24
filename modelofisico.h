#ifndef MODELOFISICO_H
#define MODELOFISICO_H

#include "utilidades/vector2d.h"

// Clase base abstracta de los modelos físicos (patrón estrategia).
// Cada entidad recibe un modelo y le delega cómo se mueve.
class ModeloFisico {
public:
    virtual ~ModeloFisico() = default;

    // Avanza dt segundos y modifica posición y velocidad.
    virtual void actualizar(double dt, Vector2D& pos, Vector2D& vel) = 0;

    // Vuelve al estado inicial
    virtual void reiniciar() = 0;
};

#endif
