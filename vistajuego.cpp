#include "vistajuego.h"

#include <QFont>
#include <QBrush>
#include <QPen>
#include <QTransform>
#include <QDebug>
#include <cmath>

#include "nivelcabinaavion.h"
#include "nivelcaidalibre.h"
#include "escombro.h"
#include "excepciones.h"

VistaJuego::VistaJuego(QWidget* parent)
    : QGraphicsView(parent), juego(nullptr),
      itemJugador(nullptr), itemPuerta(nullptr), itemParacaidas(nullptr),
      itemHumo(nullptr), itemZona(nullptr), textoZona(nullptr),
      textoAviso(nullptr),
      barraFondo(nullptr), barraProgreso(nullptr), textoBarra(nullptr),
      cajaQte(nullptr), textoQte(nullptr), letraQte(nullptr), barraQte(nullptr),
      fondoMensaje(nullptr), tituloMensaje(nullptr), subMensaje(nullptr),
      teclaIzq(false), teclaDer(false), pausado(false), mensajeVisible(false),
      tiempoAnim(0.0), esperaSiguiente(0.0), tiempoIntro(0.0), tiempoCabina(0.0) {
    escena = new QGraphicsScene(this);
    setScene(escena);
    setFixedSize(960, 540);
    setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    setFrameStyle(QFrame::NoFrame);
    setBackgroundBrush(QColor(20, 20, 30));
    setViewportUpdateMode(QGraphicsView::FullViewportUpdate);
    setFocusPolicy(Qt::StrongFocus);

    sonido = new GestorSonido(this);

    timer = new QTimer(this);
    connect(timer, &QTimer::timeout, this, &VistaJuego::actualizarJuego);
}

VistaJuego::~VistaJuego() {
    delete juego;
}

void VistaJuego::nuevoJuego(Dificultad dificultad) {
    delete juego;
    juego = new Juego(dificultad);
    juego->iniciarNivel(1);
    construirEscena();

    teclaIzq = false;
    teclaDer = false;
    pausado = false;
    sonido->iniciarMusica();
    reloj.start();
    timer->start(16);
    setFocus();
}

void VistaJuego::detenerJuego() {
    timer->stop();
    sonido->detenerMusica();
}

void VistaJuego::empezarNivel2() {
    if (juego == nullptr)
        return;
    juego->siguienteNivel();
    construirEscena();
    teclaIzq = false;
    teclaDer = false;
    sonido->iniciarMusica();
    reloj.restart();
    timer->start(16);
    setFocus();
}

QString VistaJuego::resumenPartida() const {
    if (juego == nullptr)
        return "";
    QString dif = "Normal";
    if (juego->getDificultad() == Dificultad::FACIL)
        dif = "Facil";
    else if (juego->getDificultad() == Dificultad::DIFICIL)
        dif = "Dificil";
    return QString("Dificultad: %1\nIntentos en la cabina: %2   -   tiempo hasta la puerta: %3 s\n"
                   "Veces que perdiste en total: %4")
        .arg(dif)
        .arg(juego->getMemoria()->intentos())
        .arg(tiempoCabina, 0, 'f', 1)
        .arg(juego->getMuertes());
}

QPixmap VistaJuego::imagen(const QString& ruta) {
    if (cacheImagenes.contains(ruta))
        return cacheImagenes[ruta];

    QPixmap p(ruta);
    if (p.isNull())
        throw ExcepcionRecurso("no se pudo cargar " + ruta.toStdString());
    cacheImagenes.insert(ruta, p);
    return p;
}

QGraphicsPixmapItem* VistaJuego::crearItem(const QString& ruta, double z) {
    QGraphicsPixmapItem* item = escena->addPixmap(imagen(ruta));
    item->setZValue(z);
    return item;
}

QGraphicsSimpleTextItem* VistaJuego::crearTexto(int tam, const QColor& color, bool negrita) {
    QGraphicsSimpleTextItem* t = escena->addSimpleText("");
    QFont f("Arial", tam);
    f.setBold(negrita);
    t->setFont(f);
    t->setBrush(color);
    t->setZValue(101);
    return t;
}

void VistaJuego::ponerEnPantalla(QGraphicsItem* item, double x, double y) {
    Vector2D cam = juego->getNivel()->getCamara().getPosicion();
    item->setPos(cam.x + x, cam.y + y);
}

void VistaJuego::centrarTexto(QGraphicsSimpleTextItem* texto, double y) {
    double ancho = texto->boundingRect().width();
    ponerEnPantalla(texto, (960 - ancho) / 2, y);
}

void VistaJuego::voltear(QGraphicsPixmapItem* item, bool izquierda, double ancho) {
    if (izquierda) {
        QTransform t;
        t.translate(ancho, 0);
        t.scale(-1, 1);
        item->setTransform(t);
    } else {
        item->resetTransform();
    }
}

void VistaJuego::construirEscena() {
    escena->clear();
    itemsObstaculos.clear();
    itemsPoderes.clear();
    itemsFuego.clear();
    itemsChispas.clear();
    itemJugador = nullptr;
    itemPuerta = nullptr;
    itemParacaidas = nullptr;
    itemHumo = nullptr;
    itemZona = nullptr;
    textoZona = nullptr;
    mensajeVisible = false;
    esperaSiguiente = 0.0;
    tiempoIntro = 2.5;

    NivelBase* nivel = juego->getNivel();

    if (nivel->getNumero() == 1)
        construirCabina();
    else
        construirCielo();

    const std::vector<Obstaculo*>& obs = nivel->getObstaculos();
    for (size_t i = 0; i < obs.size(); i++) {
        QGraphicsPixmapItem* it = crearItem(QString::fromStdString(obs[i]->getRutaSprite()), 2);
        it->setTransformOriginPoint(obs[i]->getAncho() / 2, obs[i]->getAlto() / 2);
        itemsObstaculos.push_back(it);
    }
    const std::vector<PowerUp*>& pod = nivel->getPowerUps();
    for (size_t i = 0; i < pod.size(); i++)
        itemsPoderes.push_back(crearItem(QString::fromStdString(pod[i]->getRutaSprite()), 3));

    itemJugador = crearItem(":/sprites/jugador_0.png", 5);

    construirHud();
    dibujar();
    actualizarHud();
}

void VistaJuego::construirCabina() {
    QPixmap fondo = imagen(":/sprites/fondo_cabina.png");
    int veces = (int)(NivelCabinaAvion::LARGO / fondo.width()) + 2;
    for (int i = 0; i < veces; i++) {
        QGraphicsPixmapItem* f = escena->addPixmap(fondo);
        f->setPos(i * fondo.width(), 0);
        f->setZValue(-10);
    }
    QGraphicsRectItem* pared = escena->addRect(NivelCabinaAvion::LARGO - 60, 0, 300, 540,
                                                QPen(Qt::NoPen), QBrush(QColor(120, 110, 95)));
    pared->setZValue(-9);

    itemPuerta = crearItem(":/sprites/puerta_cerrada.png", -5);

    itemHumo = escena->addRect(0, 0, 10, 540, QPen(Qt::NoPen), QBrush(QColor(40, 10, 0, 170)));
    itemHumo->setZValue(6);

    for (int i = 0; i < 24; i++) {
        QGraphicsPixmapItem* llama = crearItem(":/sprites/fuego_0.png", i < 12 ? 8 : 7);
        if (i >= 12)
            llama->setOpacity(0.85);
        itemsFuego.push_back(llama);
    }
    for (int i = 0; i < 6; i++)
        itemsChispas.push_back(crearItem(":/sprites/chispa.png", 9));
}

void VistaJuego::construirCielo() {
    QPixmap cielo = imagen(":/sprites/fondo_cielo.png");
    QPixmap suelo = imagen(":/sprites/fondo_suelo.png");
    double inicioSuelo = NivelCaidaLibre::ALTO_MUNDO - 1250;

    double y = -600;
    while (y < inicioSuelo) {
        QGraphicsPixmapItem* c = escena->addPixmap(cielo);
        c->setPos(0, y);
        c->setZValue(-10);
        y += cielo.height();
    }
    QGraphicsPixmapItem* s = escena->addPixmap(suelo);
    s->setPos(0, inicioSuelo);
    s->setZValue(-9);

    itemZona = escena->addRect(0, NivelCaidaLibre::ALTURA_SEGURA, 960, 60,
                                 QPen(QColor(120, 255, 120), 2), QBrush(QColor(80, 220, 80, 70)));
    itemZona->setZValue(-4);
    textoZona = escena->addSimpleText("ZONA SEGURA - ABRE EL PARACAIDAS");
    QFont f("Arial", 16);
    f.setBold(true);
    textoZona->setFont(f);
    textoZona->setBrush(Qt::white);
    textoZona->setPos(480 - textoZona->boundingRect().width() / 2, NivelCaidaLibre::ALTURA_SEGURA + 16);
    textoZona->setZValue(-3);

    itemParacaidas = crearItem(":/sprites/paracaidas.png", 4);
    itemParacaidas->setVisible(false);
}

void VistaJuego::construirHud() {
    textoAviso = crearTexto(15, Qt::white, true);
    textoAviso->setPen(QPen(Qt::black, 1));

    barraFondo = escena->addRect(0, 0, 260, 16, QPen(Qt::white), QBrush(QColor(0, 0, 0, 150)));
    barraFondo->setZValue(100);
    barraProgreso = escena->addRect(0, 0, 0, 16, QPen(Qt::NoPen), QBrush(QColor(76, 175, 80)));
    barraProgreso->setZValue(101);
    textoBarra = crearTexto(10, Qt::white, true);

    cajaQte = escena->addRect(0, 0, 280, 170, QPen(QColor(255, 235, 59), 3),
                                QBrush(QColor(0, 0, 0, 200)));
    cajaQte->setZValue(100);
    textoQte = crearTexto(15, Qt::white, true);
    textoQte->setText("PRESIONA LA TECLA");
    letraQte = crearTexto(60, QColor(255, 235, 59), true);
    barraQte = escena->addRect(0, 0, 240, 12, QPen(Qt::NoPen), QBrush(QColor(255, 87, 34)));
    barraQte->setZValue(101);
    cajaQte->setVisible(false);
    textoQte->setVisible(false);
    letraQte->setVisible(false);
    barraQte->setVisible(false);

    fondoMensaje = escena->addRect(0, 0, 960, 540, QPen(Qt::NoPen), QBrush(QColor(0, 0, 0, 160)));
    fondoMensaje->setZValue(110);
    tituloMensaje = crearTexto(34, Qt::white, true);
    tituloMensaje->setZValue(111);
    subMensaje = crearTexto(15, Qt::white, false);
    subMensaje->setZValue(111);
    ocultarMensaje();
}

void VistaJuego::actualizarJuego() {
    if (juego == nullptr)
        return;

    double dt = reloj.restart() / 1000.0;
    if (dt > 0.05)
        dt = 0.05;

    try {
        if (!pausado) {
            NivelBase* nivel = juego->getNivel();
            Jugador* j = juego->getJugador();

            if (teclaIzq && !teclaDer)
                j->moverIzquierda();
            else if (teclaDer && !teclaIzq)
                j->moverDerecha();
            else
                j->detener();

            EstadoNivel antes = nivel->getEstado();
            juego->actualizar(dt);
            tiempoAnim += dt;
            if (tiempoIntro > 0)
                tiempoIntro -= dt;

            procesarEventos();
            if (antes == EstadoNivel::EN_CURSO && nivel->getEstado() != EstadoNivel::EN_CURSO)
                alTerminarIntento();

            if (esperaSiguiente > 0) {
                esperaSiguiente -= dt;
                if (esperaSiguiente <= 0) {
                    timer->stop();
                    sonido->detenerMusica();
                    emit nivelSuperado();
                    return;
                }
            }
        }
        dibujar();
        actualizarHud();
    } catch (ExcepcionJuego& e) {
        timer->stop();
        mostrarMensaje("ERROR", QString::fromStdString(e.what()) + "\nESC: volver al menu",
                       QColor(255, 82, 82));
    }
}

void VistaJuego::procesarEventos() {
    std::vector<EventoJuego> eventos = juego->getNivel()->sacarEventos();
    for (size_t i = 0; i < eventos.size(); i++) {
        if (eventos[i] == EventoJuego::SALTO)
            sonido->reproducir("salto");
        else if (eventos[i] == EventoJuego::GOLPE)
            sonido->reproducir("golpe");
        else if (eventos[i] == EventoJuego::PODER)
            sonido->reproducir("poder");
        else if (eventos[i] == EventoJuego::PUERTA)
            sonido->reproducir("exito");
        else if (eventos[i] == EventoJuego::PARACAIDAS)
            sonido->reproducir("paracaidas");
        else if (eventos[i] == EventoJuego::DERROTA)
            sonido->reproducir("derrota");
    }
}

void VistaJuego::alTerminarIntento() {
    NivelBase* nivel = juego->getNivel();

    if (nivel->getNumero() == 1) {
        NivelCabinaAvion* cabina = static_cast<NivelCabinaAvion*>(nivel);
        const MemoriaAprendizaje* mem = juego->getMemoria();
        QString aprendio = "El fuego aprendio de este intento: la proxima vez ira mas rapido";
        if (mem->historial().back() < juego->getConfig().tiempoObjetivo)
            aprendio = "El fuego aprendio de este intento: la proxima vez ira un poco mas lento";
        if (nivel->getEstado() == EstadoNivel::VICTORIA) {
            tiempoCabina = cabina->getTiempo();
            mostrarMensaje("LLEGASTE A LA PUERTA!",
                           QString("Tiempo: %1 s\n%2\n\nSaltando del avion...")
                               .arg(cabina->getTiempo(), 0, 'f', 1).arg(aprendio),
                           QColor(129, 199, 132));
            esperaSiguiente = 3.0;
        } else {
            mostrarMensaje("EL FUEGO TE ALCANZO",
                           QString("Sobreviviste %1 s\n%2\n\nR: reintentar     ESC: menu")
                               .arg(cabina->getTiempo(), 0, 'f', 1).arg(aprendio),
                           QColor(255, 112, 67));
        }
    } else {
        NivelCaidaLibre* caida = static_cast<NivelCaidaLibre*>(nivel);
        if (nivel->getEstado() == EstadoNivel::VICTORIA) {
            sonido->reproducir("exito");
            mostrarMensaje("ATERRIZASTE A SALVO!",
                           "Lograste escapar del avion.\n\nENTER: continuar",
                           QColor(129, 199, 132));
        } else if (caida->getQte().fallo()) {
            mostrarMensaje("NO SE ABRIO EL PARACAIDAS",
                           QString("Tenias que presionar la %1\n\nR: reintentar     ESC: menu")
                               .arg(QChar::fromLatin1(caida->getQte().getTecla())),
                           QColor(255, 112, 67));
        } else {
            mostrarMensaje("TE GOLPEO UN ESCOMBRO",
                           QString("Te faltaban %1 m\n\nR: reintentar     ESC: menu")
                               .arg((int)caida->getAlturaActual()),
                           QColor(255, 112, 67));
        }
    }
}

void VistaJuego::dibujar() {
    NivelBase* nivel = juego->getNivel();
    Vector2D cam = nivel->getCamara().getPosicion();
    setSceneRect(cam.x, cam.y, 960, 540);

    const std::vector<Obstaculo*>& obs = nivel->getObstaculos();
    for (int i = 0; i < itemsObstaculos.size(); i++) {
        Obstaculo* o = obs[i];
        bool visible = o->estaActivo();
        if (nivel->getNumero() == 2 && o->getPosicion().y > NivelCaidaLibre::ALTO_MUNDO - 60)
            visible = false;
        itemsObstaculos[i]->setVisible(visible);
        itemsObstaculos[i]->setPos(o->getPosicion().x, o->getPosicion().y);
        Escombro* e = dynamic_cast<Escombro*>(o);
        if (e != nullptr)
            itemsObstaculos[i]->setRotation(e->getAngulo());
    }

    const std::vector<PowerUp*>& pod = nivel->getPowerUps();
    for (int i = 0; i < itemsPoderes.size(); i++) {
        PowerUp* p = pod[i];
        itemsPoderes[i]->setVisible(p->estaActivo());
        double flotar = 6 * std::sin(p->getTiempo() * 3 + i);
        itemsPoderes[i]->setPos(p->getPosicion().x, p->getPosicion().y + flotar);
    }

    if (nivel->getNumero() == 1)
        dibujarCabina();
    else
        dibujarCielo();
}

void VistaJuego::dibujarCabina() {
    NivelCabinaAvion* cabina = static_cast<NivelCabinaAvion*>(juego->getNivel());
    Jugador* j = juego->getJugador();
    Vector2D cam = cabina->getCamara().getPosicion();

    int cuadro = 0;
    if (!j->estaVivo())
        cuadro = 7;
    else if (!j->estaEnSuelo())
        cuadro = (j->getVelocidad().y < 0) ? 5 : 6;
    else if (std::fabs(j->getVelocidad().x) > 30)
        cuadro = 1 + ((int)(tiempoAnim * 12)) % 4;
    itemJugador->setPixmap(imagen(QString(":/sprites/jugador_%1.png").arg(cuadro)));
    itemJugador->setPos(j->getPosicion().x, j->getPosicion().y);
    voltear(itemJugador, !j->miraDerecha(), j->getAncho());
    if (j->estaAturdido())
        itemJugador->setOpacity(((int)(tiempoAnim * 20)) % 2 == 0 ? 0.4 : 1.0);
    else
        itemJugador->setOpacity(1.0);

    if (cabina->getEstado() == EstadoNivel::VICTORIA) {
        double t = 3.0 - esperaSiguiente;
        itemJugador->setPos(j->getPosicion().x + t * 120, j->getPosicion().y);
        double op = 1.0 - t / 1.5;
        itemJugador->setOpacity(op < 0 ? 0 : op);
    }

    const Puerta& puerta = cabina->getPuerta();
    itemPuerta->setPixmap(imagen(QString::fromStdString(puerta.getRutaSprite())));
    itemPuerta->setPos(puerta.getPosicion().x, puerta.getPosicion().y);

    double frente = cabina->getFuego().getPosicion().x;
    double izquierda = cam.x - 60;
    if (frente > izquierda)
        itemHumo->setRect(izquierda, 0, frente - izquierda - 20, 540);
    else
        itemHumo->setRect(0, 0, 0, 0);

    for (int i = 0; i < itemsFuego.size(); i++) {
        int fila = i / 12;
        int col = i % 12;
        int frame = ((int)(tiempoAnim * 10) + i) % 3;
        itemsFuego[i]->setPixmap(imagen(QString(":/sprites/fuego_%1.png").arg(frame)));
        double x = frente - 80 - col * 85 - fila * 40;
        double y = NivelCabinaAvion::PISO_Y - 180 - fila * 150;
        itemsFuego[i]->setPos(x, y);
    }
    for (int i = 0; i < itemsChispas.size(); i++) {
        double t = tiempoAnim * 1.3 + i * 0.37;
        double fase = t - std::floor(t);
        double x = frente + 10 + fase * 60 + i * 7;
        double y = NivelCabinaAvion::PISO_Y - 40 - std::sin(fase * 3.1416) * (60 + i * 15);
        itemsChispas[i]->setPos(x, y);
        itemsChispas[i]->setOpacity(1.0 - fase);
    }
}

void VistaJuego::dibujarCielo() {
    NivelCaidaLibre* caida = static_cast<NivelCaidaLibre*>(juego->getNivel());
    Jugador* j = juego->getJugador();

    QString ruta;
    if (caida->getParacaidasAbierto())
        ruta = ":/sprites/caida_paracaidas.png";
    else
        ruta = QString(":/sprites/caida_%1.png").arg(((int)(tiempoAnim * 4)) % 4);
    itemJugador->setPixmap(imagen(ruta));

    double px = j->getPosicion().x;
    double py = j->getPosicion().y;
    double ancho = itemJugador->pixmap().width();
    itemJugador->setPos(px + (j->getAncho() - ancho) / 2, py);
    itemJugador->resetTransform();

    if (j->estaInvencible())
        itemJugador->setOpacity(0.55 + 0.45 * std::sin(tiempoAnim * 25));
    else
        itemJugador->setOpacity(1.0);

    itemParacaidas->setVisible(caida->getParacaidasAbierto());
    itemParacaidas->setPos(px + j->getAncho() / 2 - 80, py - 105);
}

void VistaJuego::actualizarHud() {
    NivelBase* nivel = juego->getNivel();
    Jugador* j = juego->getJugador();

    ponerEnPantalla(textoAviso, 20, 18);

    if (nivel->getNumero() == 1) {
        NivelCabinaAvion* cabina = static_cast<NivelCabinaAvion*>(nivel);

        bool cerca = cabina->getFuego().decision() == DecisionFuego::ACELERAR;
        if (cerca && cabina->getEstado() == EstadoNivel::EN_CURSO && ((int)(tiempoAnim * 4)) % 2 == 0)
            textoAviso->setText("EL FUEGO ESTA CERCA!");
        else
            textoAviso->setText("");
        textoAviso->setBrush(QColor(255, 112, 67));

        ponerEnPantalla(barraFondo, 680, 22);
        ponerEnPantalla(barraProgreso, 680, 22);
        barraProgreso->setRect(0, 0, 260 * cabina->progreso(), 16);
        textoBarra->setText("PUERTA DE EMERGENCIA");
        ponerEnPantalla(textoBarra, 680, 42);
    } else {
        NivelCaidaLibre* caida = static_cast<NivelCaidaLibre*>(nivel);

        QString poder = "";
        if (j->getEstado() == EstadoJugador::INVENCIBLE)
            poder = "ESTRELLA: los escombros no te hacen nada";
        else if (j->getEstado() == EstadoJugador::RALENTIZADO)
            poder = "RELOJ: estas cayendo mas despacio";
        textoAviso->setText(poder);
        textoAviso->setBrush(QColor(255, 235, 59));

        double prog = 1.0 - caida->getAlturaActual() / NivelCaidaLibre::METROS_TOTALES;
        ponerEnPantalla(barraFondo, 680, 22);
        ponerEnPantalla(barraProgreso, 680, 22);
        barraProgreso->setRect(0, 0, 260 * prog, 16);
        textoBarra->setText("SUELO");
        ponerEnPantalla(textoBarra, 680, 42);

        const QuickTimeEvent& qte = caida->getQte();
        bool verQte = qte.estaActivo();
        cajaQte->setVisible(verQte);
        textoQte->setVisible(verQte);
        letraQte->setVisible(verQte);
        barraQte->setVisible(verQte);
        if (verQte) {
            ponerEnPantalla(cajaQte, 340, 170);
            centrarTexto(textoQte, 182);
            letraQte->setText(QString(QChar::fromLatin1(qte.getTecla())));
            centrarTexto(letraQte, 205);
            ponerEnPantalla(barraQte, 360, 310);
            barraQte->setRect(0, 0, 240 * qte.getTiempoRestante() / qte.getVentana(), 12);
        }
    }

    if (tiempoIntro > 0 && !mensajeVisible && !pausado) {
        tituloMensaje->setVisible(true);
        tituloMensaje->setBrush(QColor(255, 235, 59));
        if (nivel->getNumero() == 1)
            tituloMensaje->setText("CORRE HACIA LA PUERTA!");
        else
            tituloMensaje->setText("ESQUIVA LOS ESCOMBROS!");
        tituloMensaje->setOpacity(tiempoIntro > 1 ? 1.0 : tiempoIntro);
        centrarTexto(tituloMensaje, 220);
    } else if (!mensajeVisible) {
        tituloMensaje->setVisible(false);
        tituloMensaje->setOpacity(1.0);
    }

    if (mensajeVisible) {
        ponerEnPantalla(fondoMensaje, 0, 0);
        centrarTexto(tituloMensaje, 150);
        centrarTexto(subMensaje, 220);
    }
}

void VistaJuego::mostrarMensaje(const QString& titulo, const QString& sub, const QColor& color) {
    mensajeVisible = true;
    tituloMensaje->setText(titulo);
    tituloMensaje->setBrush(color);
    tituloMensaje->setOpacity(1.0);
    subMensaje->setText(sub);
    fondoMensaje->setVisible(true);
    tituloMensaje->setVisible(true);
    subMensaje->setVisible(true);
    actualizarHud();
}

void VistaJuego::ocultarMensaje() {
    mensajeVisible = false;
    fondoMensaje->setVisible(false);
    tituloMensaje->setVisible(false);
    subMensaje->setVisible(false);
}

void VistaJuego::keyPressEvent(QKeyEvent* event) {
    if (juego == nullptr || event->isAutoRepeat())
        return;

    NivelBase* nivel = juego->getNivel();
    int tecla = event->key();

    if (tecla == Qt::Key_Escape) {
        detenerJuego();
        emit volverAlMenu();
        return;
    }
    if (tecla == Qt::Key_P && nivel->getEstado() == EstadoNivel::EN_CURSO) {
        pausado = !pausado;
        if (pausado)
            mostrarMensaje("PAUSA", "P: continuar     ESC: menu", Qt::white);
        else
            ocultarMensaje();
        reloj.restart();
        return;
    }
    if (pausado)
        return;

    if (tecla == Qt::Key_R && nivel->getEstado() == EstadoNivel::DERROTA) {
        juego->reiniciarNivel();
        construirEscena();
        return;
    }
    if ((tecla == Qt::Key_Return || tecla == Qt::Key_Enter) &&
        nivel->getEstado() == EstadoNivel::VICTORIA && juego->esUltimoNivel()) {
        detenerJuego();
        emit juegoGanado();
        return;
    }

    if (nivel->getNumero() == 2 && tecla >= Qt::Key_A && tecla <= Qt::Key_Z) {
        NivelCaidaLibre* caida = static_cast<NivelCaidaLibre*>(nivel);
        if (caida->getQte().estaActivo()) {
            nivel->teclaEspecial((char)('A' + (tecla - Qt::Key_A)));
            return;
        }
    }

    if (tecla == Qt::Key_Left || tecla == Qt::Key_A)
        teclaIzq = true;
    else if (tecla == Qt::Key_Right || tecla == Qt::Key_D)
        teclaDer = true;
    else if (tecla == Qt::Key_Space || tecla == Qt::Key_Up || tecla == Qt::Key_W) {
        if (nivel->getEstado() == EstadoNivel::EN_CURSO && juego->getJugador()->saltar())
            nivel->agregarEvento(EventoJuego::SALTO);
    }
}

void VistaJuego::keyReleaseEvent(QKeyEvent* event) {
    if (event->isAutoRepeat())
        return;
    int tecla = event->key();
    if (tecla == Qt::Key_Left || tecla == Qt::Key_A)
        teclaIzq = false;
    else if (tecla == Qt::Key_Right || tecla == Qt::Key_D)
        teclaDer = false;
}
