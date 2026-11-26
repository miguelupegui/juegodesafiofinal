#ifndef TEMPORIZADOREFECTO_H
#define TEMPORIZADOREFECTO_H

class TemporizadorEfecto {
public:
    TemporizadorEfecto();

    void iniciar(double segundos);
    void actualizar(double dt);
    void detener();

    bool haExpirado() const;
    bool estaActivo() const { return activo; }
    double getTiempoRestante() const { return tiempoRestante; }
    double getDuracion() const { return duracion; }

private:
    double duracion;
    double tiempoRestante;
    bool activo;
};

#endif
