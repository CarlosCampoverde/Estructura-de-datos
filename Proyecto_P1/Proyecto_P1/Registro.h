#pragma once
#include <string>

template<typename T>
struct Registro {
    T cedula;
    T nombre;
    T diaNacimiento;
    T mesNacimiento;
    T anioNacimiento;
    T edad;
    T horaEntrada;
    T horaAlmuerzo;
    T horaSalida;
    std::string fechaNacimiento;
    Registro* siguiente;
    Registro* anterior;

    Registro(const T& cedula, const T& nombre, const T& horaEntrada, const T& horaAlmuerzo, const T& horaSalida, const std::string& fechaNacimiento)
        : cedula(cedula), nombre(nombre), horaEntrada(horaEntrada), horaAlmuerzo(horaAlmuerzo), horaSalida(horaSalida),
        fechaNacimiento(fechaNacimiento), siguiente(nullptr), anterior(nullptr) {}
};
