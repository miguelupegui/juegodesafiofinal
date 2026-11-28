#include "ventanaprincipal.h"

#include <QMessageBox>

#include "excepciones.h"

VentanaPrincipal::VentanaPrincipal(QWidget* parent)
    : QMainWindow(parent)
{
    escena = nullptr;
    dificultad = Dificultad::NORMAL;

    setWindowTitle("Escape del Avion - Chapecoense 2016");
    setFixedSize(960, 540);

    pantallas = new QStackedWidget(this);
    menu = new MenuPrincipal();
    vista = new VistaJuego();
    pantallas->addWidget(menu);
    pantallas->addWidget(vista);
    setCentralWidget(pantallas);

    connect(menu, &MenuPrincipal::jugar, this, &VentanaPrincipal::empezarJuego);
    connect(menu, &MenuPrincipal::salir, this, &QMainWindow::close);
    connect(vista, &VistaJuego::volverAlMenu, this, &VentanaPrincipal::mostrarMenu);
    connect(vista, &VistaJuego::nivelSuperado, this, &VentanaPrincipal::contarSalto);
    connect(vista, &VistaJuego::juegoGanado, this, &VentanaPrincipal::contarFinal);

    mostrarMenu();
}

void VentanaPrincipal::mostrarEscena(EscenaHistoria* nueva) {
    quitarEscena();
    escena = nueva;
    pantallas->addWidget(escena);
    pantallas->setCurrentWidget(escena);
    escena->empezar();
}

void VentanaPrincipal::quitarEscena() {
    if (escena != nullptr) {
        pantallas->removeWidget(escena);
        escena->deleteLater();
        escena = nullptr;
    }
}

void VentanaPrincipal::empezarJuego(Dificultad dificultad) {
    this->dificultad = dificultad;
    try {
        EscenaHistoria* nueva = new EscenaHistoria("Vuelo a Medellin", ":/sprites/fondo_cabina.png",
                                                   EscenaHistoria::escenaAvion());
        connect(nueva, &EscenaHistoria::escenaTerminada, this, &VentanaPrincipal::jugarNivel1);
        mostrarEscena(nueva);
    } catch (ExcepcionJuego& error) {
        QMessageBox::critical(this, "Error", error.what());
        mostrarMenu();
    }
}

void VentanaPrincipal::jugarNivel1() {
    try {
        quitarEscena();
        vista->nuevoJuego(dificultad);
        pantallas->setCurrentWidget(vista);
        vista->setFocus();
    } catch (ExcepcionJuego& error) {
        vista->detenerJuego();
        QMessageBox::critical(this, "Error", error.what());
        mostrarMenu();
    }
}

void VentanaPrincipal::contarSalto() {
    try {
        EscenaHistoria* nueva = new EscenaHistoria("El salto", ":/sprites/fondo_cielo.png",
                                                   EscenaHistoria::escenaSalto());
        connect(nueva, &EscenaHistoria::escenaTerminada, this, &VentanaPrincipal::jugarNivel2);
        mostrarEscena(nueva);
    } catch (ExcepcionJuego& error) {
        QMessageBox::critical(this, "Error", error.what());
        mostrarMenu();
    }
}

void VentanaPrincipal::jugarNivel2() {
    try {
        quitarEscena();
        pantallas->setCurrentWidget(vista);
        vista->empezarNivel2();
    } catch (ExcepcionJuego& error) {
        vista->detenerJuego();
        QMessageBox::critical(this, "Error", error.what());
        mostrarMenu();
    }
}

void VentanaPrincipal::contarFinal() {
    try {
        EscenaHistoria* nueva = new EscenaHistoria("En tierra", ":/sprites/fondo_suelo.png",
                                                   EscenaHistoria::escenaFinal(vista->resumenPartida()));
        connect(nueva, &EscenaHistoria::escenaTerminada, this, &VentanaPrincipal::mostrarMenu);
        mostrarEscena(nueva);
    } catch (ExcepcionJuego& error) {
        QMessageBox::critical(this, "Error", error.what());
        mostrarMenu();
    }
}

void VentanaPrincipal::mostrarMenu() {
    quitarEscena();
    pantallas->setCurrentWidget(menu);
}
