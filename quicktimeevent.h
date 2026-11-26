#ifndef QUICKTIMEEVENT_H
#define QUICKTIMEEVENT_H

class QuickTimeEvent {
public:
    QuickTimeEvent(double ventanaTiempo);

    void iniciar();
    void registrarTecla(char t);
    void actualizar(double dt);

    bool fallo() const { return fallado; }
    bool exito() const { return completado; }
    bool estaActivo() const { return activo; }
    bool yaEmpezo() const { return activo || completado || fallado; }

    char getTecla() const { return teclaRequerida; }
    double getTiempoRestante() const { return tiempoRestante; }
    double getVentana() const { return ventanaTiempo; }

private:
    char teclaRequerida;
    double ventanaTiempo;
    double tiempoRestante;
    bool activo;
    bool completado;
    bool fallado;
};

#endif
