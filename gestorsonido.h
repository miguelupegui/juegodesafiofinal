#ifndef GESTORSONIDO_H
#define GESTORSONIDO_H

#include <QObject>
#include <QMap>
#include <QString>
#include <QSoundEffect>

class GestorSonido : public QObject {
    Q_OBJECT
public:
    GestorSonido(QObject* parent = nullptr);

    void reproducir(QString nombre);
    void iniciarMusica();
    void detenerMusica();

private:
    void cargar(const QString& nombre, double volumen);

    QMap<QString, QSoundEffect*> efectos;
    QSoundEffect* musica;
};

#endif
