#ifndef EXCEPCIONES_H
#define EXCEPCIONES_H

#include <exception>
#include <string>
#include <utility>

// Jerarquía de excepciones propia del juego.
class ExcepcionJuego : public std::exception {
public:
    explicit ExcepcionJuego(std::string mensaje) : mensaje_(std::move(mensaje)) {}
    const char* what() const noexcept override { return mensaje_.c_str(); }

private:
    std::string mensaje_;
};

// Valores de configuración inválidos (nivel inexistente, factores fuera de rango...).
class ExcepcionConfiguracion : public ExcepcionJuego {
public:
    explicit ExcepcionConfiguracion(const std::string& mensaje)
        : ExcepcionJuego("Configuracion invalida: " + mensaje) {}
};

// Recursos que no se pueden cargar
class ExcepcionRecurso : public ExcepcionJuego {
public:
    explicit ExcepcionRecurso(const std::string& mensaje)
        : ExcepcionJuego("Recurso no disponible: " + mensaje) {}
};

#endif
