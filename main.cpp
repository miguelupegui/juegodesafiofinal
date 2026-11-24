#include <QApplication>
#include <QGraphicsScene>
#include <QGraphicsView>
#include <QGraphicsRectItem>
#include <QBrush>
#include <QPen>

int main(int argc, char *argv[])
{
    QApplication app(argc, argv);

    // la escena
    QGraphicsScene escena(0, 0, 960, 540);
    escena.setBackgroundBrush(QColor(40, 40, 60));

    // donde va el jugador
    auto *prueba = escena.addRect(0, 0, 50, 80, QPen(Qt::NoPen), QBrush(Qt::red));
    prueba->setPos(100, 400);

    // cámara del mundo
    QGraphicsView vista(&escena);
    vista.setFixedSize(962, 542);
    vista.setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    vista.setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    vista.setWindowTitle("Nivel 1 - Cabina del avion");
    vista.show();

    return app.exec();
}