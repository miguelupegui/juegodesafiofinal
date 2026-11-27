#ifndef VISTAJUEGO_H
#define VISTAJUEGO_H

#include <QGraphicsView>
#include <QGraphicsScene>
#include <QGraphicsPixmapItem>
#include <QGraphicsRectItem>
#include <QGraphicsSimpleTextItem>
#include <QTimer>
#include <QElapsedTimer>
#include <QKeyEvent>
#include <QVector>
#include <QMap>

#include "juego.h"
#include "gestorsonido.h"

class VistaJuego : public QGraphicsView {
    Q_OBJECT
public:
    VistaJuego(QWidget* parent = nullptr);
    ~VistaJuego();

    void nuevoJuego(Dificultad dificultad);
    void detenerJuego();
    QString resumenPartida() const;

public slots:
    void empezarNivel2();

signals:
    void volverAlMenu();
    void nivelSuperado();
    void juegoGanado();

protected:
    void keyPressEvent(QKeyEvent* event) override;
    void keyReleaseEvent(QKeyEvent* event) override;

private slots:
    void actualizarJuego();

private:
    void construirEscena();
    void construirCabina();
    void construirCielo();
    void construirHud();

    void dibujar();
    void dibujarCabina();
    void dibujarCielo();
    void actualizarHud();

    void procesarEventos();
    void alTerminarIntento();
    void mostrarMensaje(const QString& titulo, const QString& sub, const QColor& color);
    void ocultarMensaje();

    QPixmap imagen(const QString& ruta);
    QGraphicsPixmapItem* crearItem(const QString& ruta, double z);
    QGraphicsSimpleTextItem* crearTexto(int tam, const QColor& color, bool negrita);
    void ponerEnPantalla(QGraphicsItem* item, double x, double y);
    void centrarTexto(QGraphicsSimpleTextItem* texto, double y);
    void voltear(QGraphicsPixmapItem* item, bool izquierda, double ancho);

    QGraphicsScene* escena;
    QTimer* timer;
    QElapsedTimer reloj;
    Juego* juego;
    GestorSonido* sonido;
    QMap<QString, QPixmap> cacheImagenes;

    QGraphicsPixmapItem* itemJugador;
    QGraphicsPixmapItem* itemPuerta;
    QGraphicsPixmapItem* itemParacaidas;
    QGraphicsRectItem* itemHumo;
    QGraphicsRectItem* itemZona;
    QGraphicsSimpleTextItem* textoZona;
    QVector<QGraphicsPixmapItem*> itemsObstaculos;
    QVector<QGraphicsPixmapItem*> itemsPoderes;
    QVector<QGraphicsPixmapItem*> itemsFuego;
    QVector<QGraphicsPixmapItem*> itemsChispas;

    QGraphicsSimpleTextItem* textoAviso;
    QGraphicsRectItem* barraFondo;
    QGraphicsRectItem* barraProgreso;
    QGraphicsSimpleTextItem* textoBarra;
    QGraphicsRectItem* cajaQte;
    QGraphicsSimpleTextItem* textoQte;
    QGraphicsSimpleTextItem* letraQte;
    QGraphicsRectItem* barraQte;
    QGraphicsRectItem* fondoMensaje;
    QGraphicsSimpleTextItem* tituloMensaje;
    QGraphicsSimpleTextItem* subMensaje;

    bool teclaIzq;
    bool teclaDer;
    bool pausado;
    bool mensajeVisible;
    double tiempoAnim;
    double esperaSiguiente;
    double tiempoIntro;
    double tiempoCabina;
};

#endif
