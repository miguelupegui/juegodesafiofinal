#include "menuprincipal.h"

#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QGroupBox>
#include <QPixmap>

MenuPrincipal::MenuPrincipal(QWidget *parent) : QWidget(parent)
{
    setFixedSize(960, 540);

    fondo = new QLabel(this);
    fondo->setPixmap(QPixmap(":/sprites/fondo_cabina.png").scaled(960, 540));
    fondo->setGeometry(0, 0, 960, 540);

    QWidget *panel = new QWidget(this);
    panel->setGeometry(250, 80, 460, 380);
    panel->setStyleSheet("QWidget { background-color: rgba(20, 20, 35, 215); border-radius: 12px; }"
                         "QLabel { background: transparent; color: white; }"
                         "QRadioButton { background: transparent; color: white; font-size: 15px; }"
                         "QRadioButton::indicator { width: 12px; height: 12px; border-radius: 7px;"
                         "                          border: 2px solid #ffcc66; background: #202030; }"
                         "QRadioButton::indicator:checked { background: #ffcc66; }"
                         "QGroupBox { color: #ffcc66; font-size: 14px; font-weight: bold;"
                         "            border: 1px solid #ffcc66; margin-top: 10px; padding: 8px; }"
                         "QPushButton { background-color: #2e7d32; color: white; font-size: 17px;"
                         "              font-weight: bold; padding: 8px; border-radius: 6px; }"
                         "QPushButton:hover { background-color: #43a047; }");

    QLabel *titulo = new QLabel("ESCAPE DEL AVION");
    titulo->setAlignment(Qt::AlignCenter);
    titulo->setStyleSheet("font-size: 36px; font-weight: bold; color: #ff7043;");

    QLabel *subtitulo = new QLabel("En memoria del Chapecoense - 2016");
    subtitulo->setAlignment(Qt::AlignCenter);
    subtitulo->setStyleSheet("font-size: 14px; color: #cfd8dc;");

    QGroupBox *grupo = new QGroupBox("Dificultad (Nivel 1 - Cabina)");
    botonFacil = new QRadioButton("Facil");
    botonNormal = new QRadioButton("Normal");
    botonDificil = new QRadioButton("Dificil");
    botonNormal->setChecked(true);
    QHBoxLayout *filaDif = new QHBoxLayout();
    filaDif->addWidget(botonFacil);
    filaDif->addWidget(botonNormal);
    filaDif->addWidget(botonDificil);
    grupo->setLayout(filaDif);

    botonJugar = new QPushButton("JUGAR");
    botonSalir = new QPushButton("Salir");
    botonSalir->setStyleSheet("background-color: #b71c1c;");

    QVBoxLayout *columna = new QVBoxLayout(panel);
    columna->setContentsMargins(30, 20, 30, 20);
    columna->setSpacing(12);
    columna->addWidget(titulo);
    columna->addWidget(subtitulo);
    columna->addSpacing(10);
    columna->addWidget(grupo);
    columna->addSpacing(10);
    columna->addWidget(botonJugar);
    columna->addWidget(botonSalir);

    connect(botonJugar, &QPushButton::clicked, this, &MenuPrincipal::clickJugar);
    connect(botonSalir, &QPushButton::clicked, this, &MenuPrincipal::salir);
}

void MenuPrincipal::clickJugar()
{
    Dificultad d;
    if (botonFacil->isChecked())
        d = Dificultad::FACIL;
    else if (botonDificil->isChecked())
        d = Dificultad::DIFICIL;
    else
        d = Dificultad::NORMAL;
    emit jugar(d);
}
