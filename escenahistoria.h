#ifndef ESCENAHISTORIA_H
#define ESCENAHISTORIA_H

#include <QWidget>
#include <QTimer>
#include <QPixmap>
#include <QString>
#include <QKeyEvent>
#include <QPaintEvent>
#include <vector>

struct Dialogo {
    QString personaje;
    QString frase;
};

class EscenaHistoria : public QWidget {
    Q_OBJECT
public:
    EscenaHistoria(QString titulo, QString rutaFondo,
                   std::vector<Dialogo> lineas, QWidget* parent = nullptr);

    void empezar();

    static std::vector<Dialogo> escenaAvion();
    static std::vector<Dialogo> escenaSalto();
    static std::vector<Dialogo> escenaFinal(const QString& resumen);

signals:
    void escenaTerminada();

protected:
    void paintEvent(QPaintEvent* event) override;
    void keyPressEvent(QKeyEvent* event) override;

private slots:
    void parpadear();

private:
    void avanzar();

    QString titulo;
    QPixmap fondo;
    QPixmap personaje;
    std::vector<Dialogo> lineas;
    int lineaActual;
    int parpadeo;
    QTimer timer;
};

#endif
