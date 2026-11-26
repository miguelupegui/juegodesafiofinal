#ifndef CARRITOVENDEDOR_H
#define CARRITOVENDEDOR_H

#include "obstaculo.h"
#include "movimientooscilatorio.h"

class CarritoVendedor : public Obstaculo {
public:
    CarritoVendedor(double xCentro, double pisoY, double amplitud, double frecuencia, double fase);

    bool colisionar(Jugador& j) override;
    void actualizar(double dt) override;

private:
    MovimientoOscilatorio vaiven;
};

#endif
