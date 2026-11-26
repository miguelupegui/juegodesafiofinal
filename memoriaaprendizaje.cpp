#include "memoriaaprendizaje.h"
#include "excepciones.h"

MemoriaAprendizaje::MemoriaAprendizaje(double tiempoObjetivo, double tasaAprendizaje,
                                       double factorMin, double factorMax)
{
    if (tiempoObjetivo <= 0 || tasaAprendizaje < 0 || factorMin <= 0 || factorMax < factorMin)
        throw ExcepcionConfiguracion("parametros de MemoriaAprendizaje fuera de rango");

    this->tiempoObjetivo = tiempoObjetivo;
    this->tasaAprendizaje = tasaAprendizaje;
    this->factorMin = factorMin;
    this->factorMax = factorMax;
}

double MemoriaAprendizaje::calcularNuevoFactor(double factorActual) const
{
    if (historialTiempos.size() == 0)
        return factorActual;

    double ultimo = historialTiempos[historialTiempos.size() - 1];
    double ratio = (ultimo - tiempoObjetivo) / tiempoObjetivo;
    if (ratio > 1)
        ratio = 1;
    if (ratio < -1)
        ratio = -1;

    double nuevo = factorActual * (1 + tasaAprendizaje * ratio);
    if (nuevo < factorMin)
        nuevo = factorMin;
    if (nuevo > factorMax)
        nuevo = factorMax;
    return nuevo;
}

void MemoriaAprendizaje::registrar(double tiempo)
{
    historialTiempos.push_back(tiempo);
    factorActual = calcularNuevoFactor(factorActual);
}
