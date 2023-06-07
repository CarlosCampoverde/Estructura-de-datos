#pragma once
#include "ListaPersonal.h"

template<typename T>
class Menu {
public:
    Menu();
    void ejecutar();

private:
    bool validarCedula(const T& cedula);
    std::string obtenerHoraActual();
    void cargarRegistrosDesdeArchivo(const std::string& nombreArchivo);
    void guardarRegistrosEnArchivo(const std::string& nombreArchivo);
    void mostrarMenuPrincipal();
    void mostrarMenuRegistroUsuario();
    void registrarNuevoUsuario();
    void ingresarConCedula();
    void mostrarRegistros();

    ListaPersonal<T> listaPersonal;
};