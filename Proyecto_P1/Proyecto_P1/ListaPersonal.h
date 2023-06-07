#pragma once
#include "Registro.h"
#include <iostream>
#include <string>

template<typename T>
class ListaPersonal {
private:
    Registro<T>* primero;
    Registro<T>* ultimo;

public:
    ListaPersonal() : primero(nullptr), ultimo(nullptr) {}
    Registro<T>* obtenerPrimerRegistro() const;
    void agregarRegistro(const T& cedula, const T& nombre, const T& fechaNacimiento, const T& edad, const T& horaEntrada, const T& horaAlmuerzo, const T& horaSalida);
    bool existeUsuario(const T& cedula);
    void registrarHoraEntrada(const T& cedula, const T& horaEntrada);
    void registrarHoraAlmuerzo(const T& cedula, const T& horaAlmuerzo);
    void registrarHoraSalida(const T& cedula, const T& horaSalida);
    void mostrarRegistros();
};