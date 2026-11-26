#ifndef MEMORIAAPRENDIZAJE_H
#define MEMORIAAPRENDIZAJE_H

#include <vector>

class MemoriaAprendizaje {
public:
    MemoriaAprendizaje(double tiempoObjetivo, double tasaAprendizaje,
                       double factorMin, double factorMax);

    void registrar(double tiempo);

    double calcularNuevoFactor(double factorActual) const;

    double getFactorActual() const { return factorActual; }
    std::vector<double> historial() const { return historialTiempos; }
    int intentos() const { return historialTiempos.size(); }

private:
    std::vector<double> historialTiempos;
    double tiempoObjetivo;
    double tasaAprendizaje;
    double factorMin;
    double factorMax;
    double factorActual = 1.0;
};

#endif
