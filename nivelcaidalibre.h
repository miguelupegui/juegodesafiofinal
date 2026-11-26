#ifndef NIVELCAIDALIBRE_H
#define NIVELCAIDALIBRE_H

#include "nivelbase.h"
#include "zonasegura.h"
#include "quicktimeevent.h"
#include "caidalibre.h"
#include "configuraciondificultad.h"

class NivelCaidaLibre : public NivelBase {
public:
    static constexpr double ALTO_MUNDO = 10000.0;
    static constexpr double ALTURA_SEGURA = 8900.0;
    static constexpr double METROS_TOTALES = 4000.0;

    NivelCaidaLibre(Jugador* jugador, const ConfiguracionDificultad& config);
    ~NivelCaidaLibre();

    void cargarElementos() override;
    void generarEscombros();
    void generarPowerUps();

    void actualizar(double dt) override;
    bool verificarVictoria() override;
    bool verificarDerrota() override;
    void teclaEspecial(char tecla) override;
    int getNumero() const override { return 2; }

    double getAlturaActual() const { return alturaActual; }
    const ZonaSegura& getZona() const { return zona; }
    const QuickTimeEvent& getQte() const { return qte; }
    bool getParacaidasAbierto() const { return paracaidasAbierto; }

private:
    ConfiguracionDificultad config;
    double alturaInicial;
    double alturaActual;
    ZonaSegura zona;
    QuickTimeEvent qte;
    CaidaLibre* caida;
    bool paracaidasAbierto;
};

#endif
