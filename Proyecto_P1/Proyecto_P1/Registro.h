#pragma once
#include <string>

template<typename T>
struct Registro {
    T cedula;
    T nombre;
    T fechaNacimiento;
    T edad;
    T horaEntrada;
    T horaAlmuerzo;
    T horaSalida;
    Registro* siguiente;
    Registro* anterior;

    Registro(const T& cedula, const T& nombre, const T& fechaNacimiento, const T& edad, const T& horaEntrada, const T& horaAlmuerzo, const T& horaSalida)
        : cedula(cedula), nombre(nombre), fechaNacimiento(fechaNacimiento), edad(edad), horaEntrada(horaEntrada), horaAlmuerzo(horaAlmuerzo), horaSalida(horaSalida),
        siguiente(nullptr), anterior(nullptr) {}
};