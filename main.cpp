#include <QApplication>
#include <QMessageBox>
#include <cstdlib>
#include <ctime>

#include "vistajuego.h"
#include "excepciones.h"

// por ahora abre directo el juego en normal, despues se hace el menu
int main(int argc, char *argv[])
{
    QApplication app(argc, argv);
    srand((unsigned)time(nullptr));

    try {
        VistaJuego vista;
        vista.setWindowTitle("Escape del Avion");
        vista.show();
        // por ahora: al ganar el nivel 1 pasa directo al 2 y al final se cierra
        QObject::connect(&vista, &VistaJuego::nivelSuperado, &vista, &VistaJuego::empezarNivel2);
        QObject::connect(&vista, &VistaJuego::juegoGanado, &vista, &QWidget::close);
        QObject::connect(&vista, &VistaJuego::volverAlMenu, &vista, &QWidget::close);
        vista.nuevoJuego(Dificultad::NORMAL);
        return app.exec();
    } catch (ExcepcionJuego& e) {
        QMessageBox::critical(nullptr, "Error del juego", e.what());
    }
    return 1;
}
