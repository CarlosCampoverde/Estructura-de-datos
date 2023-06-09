#include "Menu.h"
#include "Registro.h"
#include <iostream>
#include <fstream>
#include <string>
#include <ctime>
#include <regex>

using namespace std;

template<typename T>
Menu<T>::Menu() {
    const string nombreArchivo = "registros.txt";
    cargarRegistrosDesdeArchivo(nombreArchivo);
}

template<typename T>
void Menu<T>::ejecutar() {

    int opcion = 0;
    while (opcion != 4) {
        mostrarMenuPrincipal();
        cin >> opcion;

        switch (opcion) {
        case 1:
            registrarNuevoUsuario();
            system("pause");
            system("cls");
            break;
        case 2:
            ingresarConCedula();
            system("pause");
            system("cls");
            break;
        case 3:
            mostrarRegistros();
            system("pause");
            system("cls");
            break;
        case 4:
            cout << "Saliendo del programa..." << endl;
            system("pause");
            system("cls");
            break;
        default:
            cout << "Opcion invalida. Por favor, ingrese una opcion valida." << endl;
            system("pause");
            system("cls");
            break;
        }
    }

    const string nombreArchivo = "registros.txt";
    guardarRegistrosEnArchivo(nombreArchivo);
}

template<typename T>
bool esMayorDe18(const T& fechaNacimiento) {
    time_t now;
    struct tm timeinfo;
    time(&now);
    localtime_s(&timeinfo, &now);
    int currentYear = timeinfo.tm_year + 1900;
    int currentMonth = timeinfo.tm_mon + 1;
    int currentDay = timeinfo.tm_mday;

    int userYear = stoi(fechaNacimiento.substr(0, 4));
    int userMonth = stoi(fechaNacimiento.substr(5, 2));
    int userDay = stoi(fechaNacimiento.substr(8, 2));

    int age = currentYear - userYear;

    if (currentMonth < userMonth || (currentMonth == userMonth && currentDay < userDay)) {
        age--;
    }
    return age >= 18;
}

template<typename T>
int calcularEdad(const T& fechaNacimiento) {
    time_t now;
    struct tm timeinfo;
    time(&now);
    localtime_s(&timeinfo, &now);
    int currentYear = timeinfo.tm_year + 1900;
    int currentMonth = timeinfo.tm_mon + 1;
    int currentDay = timeinfo.tm_mday;

    int userYear = stoi(fechaNacimiento.substr(0, 4));
    int userMonth = stoi(fechaNacimiento.substr(5, 2));
    int userDay = stoi(fechaNacimiento.substr(8, 2));

    int age = currentYear - userYear;

    if (currentMonth < userMonth || (currentMonth == userMonth && currentDay < userDay)) {
        age--;
    }

    return age;
}

template<typename T>
bool Menu<T>::validarCedula(const T& cedula) {
    // La c�dula debe tener 10 d�gitos
    if (cedula.length() != 10) {
        return false;
    }

    // Los dos primeros d�gitos representan el c�digo de la provincia
    int codigoProvincia = stoi(cedula.substr(0, 2));
    if (codigoProvincia < 1 || codigoProvincia > 24) {
        return false;
    }

    // Verificar el tercer d�gito
    int tercerDigito = stoi(cedula.substr(2, 1));
    if (tercerDigito < 0 || tercerDigito > 5) {
        return false;
    }

    // Algoritmo de verificaci�n
    int sumaPares = 0;
    for (int i = 0; i < 9; i += 2) {
        int digito = stoi(cedula.substr(i, 1)) * 2;
        sumaPares += (digito > 9) ? digito - 9 : digito;
    }

    int sumaImpares = 0;
    for (int i = 1; i < 8; i += 2) {
        sumaImpares += stoi(cedula.substr(i, 1));
    }

    int sumaTotal = sumaPares + sumaImpares;
    int digitoVerificador = (10 - (sumaTotal % 10)) % 10;

    // Verificar el �ltimo d�gito (d�gito verificador)
    int ultimoDigito = stoi(cedula.substr(9, 1));
    if (ultimoDigito != digitoVerificador) {
        return false;
    }

    return true;
}

template<typename T>
string Menu<T>::obtenerHoraActual() {
    time_t now = time(0);
    tm timeinfo;
    localtime_s(&timeinfo, &now);
    char buffer[80];
    strftime(buffer, sizeof(buffer), "%Y-%m-%d %H:%M:%S", &timeinfo);
    return buffer;
}

template<typename T>
void Menu<T>::cargarRegistrosDesdeArchivo(const string& nombreArchivo) {
    ifstream archivo(nombreArchivo);
    if (!archivo) {
        cout << "No se pudo abrir el archivo " << nombreArchivo << endl;
        return;
    }

    string linea;
    while (getline(archivo, linea)) {
        size_t pos1 = linea.find("/");
        size_t pos2 = linea.find("/", pos1 + 1);
        size_t pos3 = linea.find("/", pos2 + 1);
        size_t pos4 = linea.find("/", pos3 + 1);
        size_t pos5 = linea.find("/", pos4 + 1);
        size_t pos6 = linea.find("/", pos5 + 1);

        string cedula = linea.substr(0, pos1);
        string nombre = linea.substr(pos1 + 1, pos2 - pos1 - 1);
        string fechaNacimiento = linea.substr(pos2 + 1, pos3 - pos2 - 1);
        string edad = linea.substr(pos3 + 1, pos4 - pos3 - 1);
        string horaEntrada = linea.substr(pos4 + 1, pos5 - pos4 - 1);
        string horaAlmuerzo = linea.substr(pos5 + 1, pos6 - pos5 - 1);
        string horaSalida = linea.substr(pos6 + 1);
        listaPersonal.agregarRegistro(cedula, nombre, fechaNacimiento, edad, horaEntrada, horaAlmuerzo, horaSalida);
    }
    archivo.close();
}

template<typename T>
void Menu<T>::guardarRegistrosEnArchivo(const std::string& nombreArchivo) {
    ofstream archivo(nombreArchivo);
    if (!archivo) {
        cout << "No se pudo abrir el archivo " << nombreArchivo << endl;
        return;
    }

    Registro<T>* actual = listaPersonal.obtenerPrimerRegistro();
    while (actual) {
        archivo << actual->cedula << " / "
            << actual->nombre << " / "
            << actual->fechaNacimiento<< " / "
            << actual->edad<<" / "
            << actual->horaEntrada << " / "
            << actual->horaAlmuerzo << " / "
            << actual->horaSalida << endl;
        actual = actual->siguiente;
    }

    archivo.close();
}

template<typename T>
void Menu<T>::mostrarMenuPrincipal() {
    cout << "MENU PRINCIPAL" << endl;
    cout << "1. Registrar nuevo usuario" << endl;
    cout << "2. Ingresar con cedula" << endl;
    cout << "3. Mostrar registros" << endl;
    cout << "4. Salir" << endl;
    cout << "Ingrese su opcion: ";
}

template<typename T>
void Menu<T>::mostrarMenuRegistroUsuario() {
    cout << "MENU REGISTRO USUARIO" << endl;
    cout << "1. Registrar hora de entrada" << endl;
    cout << "2. Registrar hora de almuerzo" << endl;
    cout << "3. Registrar hora de salida" << endl;
    cout << "4. Volver al menu principal" << endl;
    cout << "Ingrese su opcion: ";
}

template<typename T>
void Menu<T>::registrarNuevoUsuario() {
    T cedula;
    bool cedulaValida = false;

    while (!cedulaValida) {
        cout << "Ingrese la cedula: ";
        cin.ignore();
        getline(cin, cedula);

        if (!validarCedula(cedula)) {
            cout << "Cedula invalida. Ingrese una cedula valida." << endl;
        }
        else {
            cedulaValida = true;
        }
    }

    if (listaPersonal.existeUsuario(cedula)) {
        cout << "Ya existe un usuario registrado con la cedula " << cedula << "." << endl;
        return;
    }

    string fechaNacimiento;
    bool fechaValida = false;

    while (!fechaValida) {
        cout << "Ingrese la fecha de nacimiento (YYYY-MM-DD): ";
        getline(cin, fechaNacimiento);

        if (!esMayorDe18(fechaNacimiento)) {
            cout << "El usuario debe ser mayor de 18 a�os para ser registrado." << endl;
        }
        else {
            fechaValida = true;
        }
    }

    int edadStr = calcularEdad(fechaNacimiento);
    string edad = to_string(edadStr);
    cout << "Tu edad es: " << edad << " a�os." << endl;


    string nombre;
    regex nombreRegex("[A-Za-z ]+"); //expresi�n para validar cadenas
    cout << "Ingrese el nombre del usuario: ";
    getline(cin, nombre);

    while (!regex_match(nombre, nombreRegex)) {
        cout << "El nombre ingresado es invalido. \n\tIngrese un nombre valido: ";
        getline(cin, nombre);
    }

    listaPersonal.agregarRegistro(cedula, nombre, fechaNacimiento, edad, "", "", "");
    cout << "Se registro al usuario con cedula " << cedula << endl;
}

template<typename T>
void Menu<T>::ingresarConCedula() {
    T cedula;
    cout << "Ingrese la cedula: ";
    cin.ignore();
    getline(cin, cedula);

    if (!validarCedula(cedula)) {
        cout << "Cedula invalida. Ingrese una cedula valida." << endl;
        return;
    }

    if (!listaPersonal.existeUsuario(cedula)) {
        cout << "El usuario no existe. Registre al usuario antes de registrar la hora de entrada, salida o almuerzo." << endl;
        return;
    }

    int opcionRegistroUsuario = 0;
    while (opcionRegistroUsuario != 4) {
        mostrarMenuRegistroUsuario();
        cin >> opcionRegistroUsuario;

        switch (opcionRegistroUsuario) {
        case 1: {
            string horaEntrada = obtenerHoraActual();
            listaPersonal.registrarHoraEntrada(cedula, horaEntrada);
            cout << "Se registro la hora de entrada: " << horaEntrada << endl;
            system("pause");
            system("cls");
            break;
        }
        case 2: {
            string horaAlmuerzo = obtenerHoraActual();
            listaPersonal.registrarHoraAlmuerzo(cedula, horaAlmuerzo);
            cout << "Se registro la hora de almuerzo: " << horaAlmuerzo << endl;
            system("pause");
            system("cls");
            break;
        }
        case 3: {
            string horaSalida = obtenerHoraActual();
            listaPersonal.registrarHoraSalida(cedula, horaSalida);
            cout << "Se registro la hora de salida: " << horaSalida << endl;
            system("pause");
            system("cls");
            break;
        }
        case 4:
            cout << "Volviendo al menu principal..." << endl;
            break;
        default:
            cout << "Opcion invalida. Por favor, ingrese una opcion valida." << endl;
            system("pause");
            system("cls");
            break;
        }
    }
}

template<typename T>
void Menu<T>::mostrarRegistros() {
    listaPersonal.mostrarRegistros();
}
