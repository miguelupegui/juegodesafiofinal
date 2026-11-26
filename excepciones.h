#ifndef EXCEPCIONES_H
#define EXCEPCIONES_H

#include <exception>
#include <string>

class ExcepcionJuego : public std::exception {
public:
    ExcepcionJuego(std::string mensaje) {
        this->mensaje = mensaje;
    }
    const char* what() const noexcept override {
        return mensaje.c_str();
    }

private:
    std::string mensaje;
};

class ExcepcionConfiguracion : public ExcepcionJuego {
public:
    ExcepcionConfiguracion(std::string mensaje)
        : ExcepcionJuego("Configuracion invalida: " + mensaje) {}
};

class ExcepcionRecurso : public ExcepcionJuego {
public:
    ExcepcionRecurso(std::string mensaje)
        : ExcepcionJuego("Recurso no disponible: " + mensaje) {}
};

#endif
