#include "carritovendedor.h"

CarritoVendedor::CarritoVendedor(double xCentro, double pisoY, double amplitud,
                                 double frecuencia, double fase)
    : Obstaculo(xCentro, pisoY - 96, 64, 96, ":/sprites/carrito.png"),
      vaiven(amplitud, frecuencia, fase, Vector2D(xCentro, pisoY - 96), Vector2D(1, 0))
{
    setMargenHitbox(6, 8);
    vaiven.actualizar(0, posicion, velocidad);
}

bool CarritoVendedor::colisionar(Jugador &j)
{
    if (j.estaAturdido())
        return false;

    j.empujar(-120, 0.3);
    return true;
}

void CarritoVendedor::actualizar(double dt)
{
    vaiven.actualizar(dt, posicion, velocidad);
}
