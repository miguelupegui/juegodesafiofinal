#ifndef VENTANAPRINCIPAL_H
#define VENTANAPRINCIPAL_H

#include <QMainWindow>
#include <QStackedWidget>

#include "menuprincipal.h"
#include "vistajuego.h"
#include "escenahistoria.h"

class VentanaPrincipal : public QMainWindow {
    Q_OBJECT
public:
    VentanaPrincipal(QWidget* parent = nullptr);

private slots:
    void empezarJuego(Dificultad dificultad);
    void jugarNivel1();
    void contarSalto();
    void jugarNivel2();
    void contarFinal();
    void mostrarMenu();

private:
    void mostrarEscena(EscenaHistoria* nueva);
    void quitarEscena();

    QStackedWidget* pantallas;
    MenuPrincipal* menu;
    VistaJuego* vista;
    EscenaHistoria* escena;
    Dificultad dificultad;
};

#endif
