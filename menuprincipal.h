#ifndef MENUPRINCIPAL_H
#define MENUPRINCIPAL_H

#include <QWidget>
#include <QRadioButton>
#include <QPushButton>
#include <QLabel>

#include "configuraciondificultad.h"

class MenuPrincipal : public QWidget
{
    Q_OBJECT
public:
    MenuPrincipal(QWidget *parent = nullptr);

signals:
    void jugar(Dificultad dificultad);
    void salir();

private slots:
    void clickJugar();

private:
    QLabel *fondo;
    QRadioButton *botonFacil;
    QRadioButton *botonNormal;
    QRadioButton *botonDificil;
    QPushButton *botonJugar;
    QPushButton *botonSalir;
};

#endif
