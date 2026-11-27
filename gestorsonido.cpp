#include "gestorsonido.h"

#include <QUrl>

GestorSonido::GestorSonido(QObject* parent) : QObject(parent) {
    cargar("salto", 1.0);
    cargar("golpe", 1.0);
    cargar("poder", 1.0);
    cargar("exito", 0.9);
    cargar("paracaidas", 0.9);
    cargar("derrota", 1.0);

    musica = new QSoundEffect(this);
    musica->setSource(QUrl("qrc:/sonidos/musica_fondo.wav"));
    musica->setLoopCount(QSoundEffect::Infinite);
    musica->setVolume(0.2);
}

void GestorSonido::cargar(const QString& nombre, double volumen) {
    QSoundEffect* efecto = new QSoundEffect(this);
    efecto->setSource(QUrl("qrc:/sonidos/" + nombre + ".wav"));
    efecto->setVolume(volumen);
    efectos.insert(nombre, efecto);
}

void GestorSonido::reproducir(QString nombre) {
    efectos[nombre]->play();
}

void GestorSonido::iniciarMusica() {
    if (!musica->isPlaying())
        musica->play();
}

void GestorSonido::detenerMusica() {
    musica->stop();
}
