#include <QApplication>
#include <QMessageBox>
#include <cstdlib>
#include <ctime>
#include <new>

#include "ventanaprincipal.h"
#include "excepciones.h"

int main(int argc, char *argv[])
{
    QApplication app(argc, argv);

    srand(time(NULL));

    try {
        VentanaPrincipal ventana;
        ventana.show();
        return app.exec();
    } catch (ExcepcionJuego& e) {
        QMessageBox::critical(nullptr, "Error del juego", e.what());
    } catch (std::bad_alloc&) {
        QMessageBox::critical(nullptr, "Error", "No hay memoria suficiente");
    }
    return 1;
}
