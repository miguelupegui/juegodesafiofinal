#include "escenahistoria.h"

#include <QPainter>
#include <QFont>

#include "excepciones.h"

EscenaHistoria::EscenaHistoria(QString titulo, QString rutaFondo,
                               std::vector<Dialogo> lineas, QWidget* parent)
    : QWidget(parent), titulo(titulo), fondo(rutaFondo),
      personaje(":/sprites/jugador_0.png"), lineas(lineas),
      lineaActual(0), parpadeo(0) {
    if (fondo.isNull())
        throw ExcepcionRecurso("no se encontro el fondo " + rutaFondo.toStdString());
    if (lineas.empty())
        throw ExcepcionConfiguracion("la escena no tiene dialogos");

    setFixedSize(960, 540);
    setFocusPolicy(Qt::StrongFocus);
    connect(&timer, &QTimer::timeout, this, &EscenaHistoria::parpadear);
}

void EscenaHistoria::empezar() {
    lineaActual = 0;
    timer.start(30);
    setFocus();
}

void EscenaHistoria::parpadear() {
    parpadeo++;
    update();
}

void EscenaHistoria::avanzar() {
    if (lineaActual + 1 < (int)lineas.size()){
	lineaActual++;
	return;
    }
    timer.stop();
    emit escenaTerminada();
}

void EscenaHistoria::keyPressEvent(QKeyEvent* event) {
    if (event->isAutoRepeat())
        return;
    if (event->key() == Qt::Key_Return || event->key() == Qt::Key_Enter || event->key() == Qt::Key_Space) {
        avanzar();
    } else if (event->key() == Qt::Key_Escape) {
        timer.stop();
        emit escenaTerminada();
    }
}

void EscenaHistoria::paintEvent(QPaintEvent* event) {
    QPainter p(this);

    int altoFuente = fondo.width() * 540 / 960;
    int y = (fondo.height() - altoFuente) * 3 / 4;
    p.drawPixmap(QRect(0, 0, 960, 540), fondo, QRect(0, y, fondo.width(), altoFuente));
    p.fillRect(0, 0, 960, 540, QColor(0, 0, 0, 110));

    p.setPen(QColor(255, 204, 102));
    p.setFont(QFont("Courier New", 20, QFont::Bold));
    p.drawText(QRect(0, 20, 960, 40), Qt::AlignCenter, titulo);

    const Dialogo& linea = lineas[lineaActual];

    if (linea.personaje == "TU")
        p.setOpacity(1.0);
    else
        p.setOpacity(0.5);
    p.drawPixmap(70, 140, personaje.width() * 2.6, personaje.height() * 2.6, personaje);
    p.setOpacity(1.0);

    QRect caja(40, 380, 880, 140);
    p.setPen(QPen(QColor(255, 255, 255, 180), 2));
    p.setBrush(QColor(15, 15, 25, 225));
    p.drawRoundedRect(caja, 10, 10);

    QColor colorNombre = QColor(255, 210, 70);
    if (linea.personaje == "PILOTO")
        colorNombre = QColor(110, 190, 255);
    else if (linea.personaje == "NARRADOR")
        colorNombre = QColor(200, 200, 200);
    else if (linea.personaje == "RESUMEN")
        colorNombre = QColor(129, 199, 132);
    p.setPen(colorNombre);
    p.setFont(QFont("Courier New", 14, QFont::Bold));
    p.drawText(caja.x() + 20, caja.y() + 28, linea.personaje);

    p.setPen(Qt::white);
    p.setFont(QFont("Courier New", 13));
    p.drawText(QRect(caja.x() + 20, caja.y() + 40, caja.width() - 40, caja.height() - 50),
               Qt::AlignLeft | Qt::AlignTop | Qt::TextWordWrap, linea.frase);

    p.setFont(QFont("Courier New", 10));
    p.setPen(QColor(190, 190, 190));
    p.drawText(caja.x() + 20, caja.bottom() - 8, "[Esc] omitir historia");
    if ((parpadeo/15)%2 == 0)
        p.drawText(caja.right() - 150, caja.bottom() - 8, "[Enter] seguir >>");
}

std::vector<Dialogo> EscenaHistoria::escenaAvion() {
    std::vector<Dialogo> h;
    h.push_back({"NARRADOR", "Noviembre de 2016. El Chapecoense, un equipo pequeño de Brasil, viaja a "
                             "Medellin para jugar la final de la Copa Sudamericana contra Atletico Nacional."});
    h.push_back({"NARRADOR", "Es el partido mas importante de su historia. En el avion van los jugadores, "
                             "el cuerpo tecnico, periodistas y la tripulacion."});
    h.push_back({"TU", "No puedo dormir... mañana jugamos la final. Un momento... ¿que es ese olor a humo?"});
    h.push_back({"PILOTO", "¡Atencion! Hay fuego en la parte de atras del avion. Todos a la puerta de "
                           "emergencia de adelante. ¡Junto a la salida hay paracaidas!"});
    h.push_back({"TU", "¡El fuego viene para aca y cada vez va mas rapido! Tengo que llegar a esa puerta."});
    h.push_back({"NARRADOR", "CONTROLES: flechas o A/D para correr, Espacio o W para saltar las maletas. "
                             "Cuidado con los carritos de comida, te tiran para atras. P pausa."});
    h.push_back({"NARRADOR", "Ojo: el fuego aprende. Si sobrevives mucho tiempo, en el siguiente intento "
                             "sera mas rapido. Si te alcanza rapido, se calma un poco."});
    return h;
}

std::vector<Dialogo> EscenaHistoria::escenaSalto() {
    std::vector<Dialogo> h;
    h.push_back({"TU", "¡Llegue! Abri la puerta y... ¡salte! Ya tengo el paracaidas puesto."});
    h.push_back({"TU", "Pero si lo abro muy arriba me pueden golpear los pedazos del avion que vienen cayendo."});
    h.push_back({"NARRADOR", "Muevete con las flechas o A/D para esquivar los escombros. Un solo golpe y se "
                             "acaba el intento."});
    h.push_back({"NARRADOR", "El reloj de arena te hace caer mas despacio y la estrella te hace invencible, "
                             "los dos por 7 segundos."});
    h.push_back({"NARRADOR", "Cuando pases la ZONA SEGURA va a aparecer una letra: presionala rapido para "
                             "abrir el paracaidas."});
    return h;
}

std::vector<Dialogo> EscenaHistoria::escenaFinal(const QString& resumen) {
    std::vector<Dialogo> h;
    h.push_back({"TU", "Estoy en tierra... ¡estoy vivo! Tengo que avisarle a todos que estoy bien."});
    h.push_back({"NARRADOR", "Esta fue una fantasia animada. En la realidad, la noche del 28 de noviembre de "
                             "2016 el avion cayo cerca de La Union, Antioquia. Murieron 71 personas y solo "
                             "6 sobrevivieron."});
    h.push_back({"NARRADOR", "Atletico Nacional pidio que el titulo se le entregara al Chapecoense y la "
                             "Conmebol se lo dio. Medellin lleno el estadio Atanasio Girardot de blanco "
                             "para despedirlos."});
    h.push_back({"NARRADOR", "Este juego es un pequeño homenaje a ellos. Forca Chape."});
    h.push_back({"RESUMEN", resumen});
    return h;
}
