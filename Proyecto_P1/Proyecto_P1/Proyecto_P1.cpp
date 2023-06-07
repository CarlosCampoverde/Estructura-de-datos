#include <iostream>
#include <fstream>
#include <string>
#include <ctime>

using namespace std;

// Definición de la estructura Registro
struct Registro {
    string cedula;
    string nombre;
    string horaEntrada;
    string horaAlmuerzo;
    string horaSalida;
    Registro* siguiente;
    Registro* anterior;

    Registro(const string& cedula, const string& nombre, const string& horaEntrada, const string& horaAlmuerzo, const string& horaSalida)
        : cedula(cedula), nombre(nombre), horaEntrada(horaEntrada), horaAlmuerzo(horaAlmuerzo), horaSalida(horaSalida),
        siguiente(nullptr), anterior(nullptr) {}
};

// Clase ListaPersonal para gestionar la lista de registros
class ListaPersonal {
private:
    Registro* primero;
    Registro* ultimo;

public:
    ListaPersonal() : primero(nullptr), ultimo(nullptr) {}

    Registro* obtenerPrimerRegistro() const {
        return primero;
    }

    void agregarRegistro(const string& cedula, const string& nombre, const string& horaEntrada, const string& horaAlmuerzo, const string& horaSalida) {
        Registro* nuevo = new Registro(cedula, nombre, horaEntrada, horaAlmuerzo, horaSalida);

        if (!primero) {
            primero = nuevo;
            ultimo = nuevo;
        }
        else {
            ultimo->siguiente = nuevo;
            nuevo->anterior = ultimo;
            ultimo = nuevo;
        }
    }

    bool existeUsuario(const string& cedula) {
        Registro* actual = primero;
        while (actual) {
            if (actual->cedula == cedula) {
                return true;
            }
            actual = actual->siguiente;
        }
        return false;
    }

    void registrarHoraEntrada(const string& cedula, const string& horaEntrada) {
        Registro* actual = primero;
        while (actual) {
            if (actual->cedula == cedula) {
                actual->horaEntrada = horaEntrada;
                break;
            }
            actual = actual->siguiente;
        }
    }

    void registrarHoraAlmuerzo(const string& cedula, const string& horaAlmuerzo) {
        Registro* actual = primero;
        while (actual) {
            if (actual->cedula == cedula) {
                actual->horaAlmuerzo = horaAlmuerzo;
                break;
            }
            actual = actual->siguiente;
        }
    }

    void registrarHoraSalida(const string& cedula, const string& horaSalida) {
        Registro* actual = primero;
        while (actual) {
            if (actual->cedula == cedula) {
                actual->horaSalida = horaSalida;
                break;
            }
            actual = actual->siguiente;
        }
    }

    void mostrarRegistros() {
        Registro* actual = primero;
        while (actual) {
            cout << "Cedula: " << actual->cedula << endl;
            cout << "Nombre: " << actual->nombre << endl;
            cout << "Hora de entrada: " << actual->horaEntrada << endl;
            cout << "Hora de almuerzo: " << actual->horaAlmuerzo << endl;
            cout << "Hora de salida: " << actual->horaSalida << endl;
            cout << endl;

            actual = actual->siguiente;
        }
    }
};

// Función para validar la cédula ecuatoriana
bool validarCedula(const string& cedula) {
    // La cédula debe tener 10 dígitos
    if (cedula.length() != 10) {
        return false;
    }

    // Los dos primeros dígitos representan el código de la provincia
    int codigoProvincia = stoi(cedula.substr(0, 2));
    if (codigoProvincia < 1 || codigoProvincia > 24) {
        return false;
    }

    // Verificar el tercer dígito
    int tercerDigito = stoi(cedula.substr(2, 1));
    if (tercerDigito < 0 || tercerDigito > 5) {
        return false;
    }

    // Algoritmo de verificación
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

    // Verificar el último dígito (dígito verificador)
    int ultimoDigito = stoi(cedula.substr(9, 1));
    if (ultimoDigito != digitoVerificador) {
        return false;
    }

    return true;
}

// Función para obtener la hora actual en formato string
string obtenerHoraActual() {
    time_t now = time(0);
    tm timeinfo;
    localtime_s(&timeinfo, &now);
    char buffer[80];
    strftime(buffer, sizeof(buffer), "%Y-%m-%d %H:%M:%S", &timeinfo);
    return buffer;
}

// Función para cargar los registros desde un archivo
void cargarRegistrosDesdeArchivo(const string& nombreArchivo, ListaPersonal& listaPersonal) {
    ifstream archivo(nombreArchivo);
    if (!archivo) {
        cout << "No se pudo abrir el archivo " << nombreArchivo << endl;
        return;
    }

    string linea;
    while (getline(archivo, linea)) {
        size_t pos1 = linea.find(",");
        size_t pos2 = linea.find(",", pos1 + 1);
        size_t pos3 = linea.find(",", pos2 + 1);
        size_t pos4 = linea.find(",", pos3 + 1);

        string cedula = linea.substr(0, pos1);
        string nombre = linea.substr(pos1 + 1, pos2 - pos1 - 1);
        string horaEntrada = linea.substr(pos2 + 1, pos3 - pos2 - 1);
        string horaAlmuerzo = linea.substr(pos3 + 1, pos4 - pos3 - 1);
        string horaSalida = linea.substr(pos4 + 1);

        listaPersonal.agregarRegistro(cedula, nombre, horaEntrada, horaAlmuerzo, horaSalida);
    }

    archivo.close();
}

// Función para guardar los registros en un archivo
void guardarRegistrosEnArchivo(const string& nombreArchivo, const ListaPersonal& listaPersonal) {
    ofstream archivo(nombreArchivo);
    if (!archivo) {
        cout << "No se pudo abrir el archivo " << nombreArchivo << endl;
        return;
    }

    Registro* actual = listaPersonal.obtenerPrimerRegistro();
    while (actual) {
        archivo << actual->cedula << ","
            << actual->nombre << ","
            << actual->horaEntrada << ","
            << actual->horaAlmuerzo << ","
            << actual->horaSalida << endl;
        actual = actual->siguiente;
    }

    archivo.close();
}

// Función para mostrar el menú principal
void mostrarMenuPrincipal() {
    cout << "MENU PRINCIPAL" << endl;
    cout << "1. Registrar entrada" << endl;
    cout << "2. Registrar nuevo usuario" << endl;
    cout << "3. Ingresar con cédula" << endl;
    cout << "4. Mostrar registros" << endl;
    cout << "5. Salir" << endl;
    cout << "Ingrese su opción: ";
}

// Función para mostrar el menú de registro para un usuario existente
void mostrarMenuRegistroUsuario() {
    cout << "MENU REGISTRO USUARIO" << endl;
    cout << "1. Registrar hora de entrada" << endl;
    cout << "2. Registrar hora de almuerzo" << endl;
    cout << "3. Registrar hora de salida" << endl;
    cout << "4. Volver al menú principal" << endl;
    cout << "Ingrese su opción: ";
}

int main() {
    const string nombreArchivo = "registros.txt";
    ListaPersonal listaPersonal;
    cargarRegistrosDesdeArchivo(nombreArchivo, listaPersonal);

    int opcion = 0;
    while (opcion != 5) {
        mostrarMenuPrincipal();
        cin >> opcion;

        switch (opcion) {
        case 1: {
            string cedula;
            cout << "Ingrese la cedula: ";
            cin.ignore();
            getline(cin, cedula);

            if (!validarCedula(cedula)) {
                cout << "Cedula invalida. Ingrese una cedula valida." << endl;
                break;
            }

            if (!listaPersonal.existeUsuario(cedula)) {
                cout << "El usuario no existe. Registre al usuario antes de registrar la entrada." << endl;
                break;
            }

            string horaEntrada = obtenerHoraActual();
            listaPersonal.registrarHoraEntrada(cedula, horaEntrada);
            cout << "Se registró la hora de entrada: " << horaEntrada << endl;
            break;
        }
        case 2: {
            string cedula;
            cout << "Ingrese la cedula: ";
            cin.ignore();
            getline(cin, cedula);

            if (!validarCedula(cedula)) {
                cout << "Cedula invalida. Ingrese una cedula valida." << endl;
                break;
            }

            string nombre;
            cout << "Ingrese el nombre: ";
            getline(cin, nombre);

            listaPersonal.agregarRegistro(cedula, nombre, "", "", "");
            cout << "Se registró al usuario con cedula " << cedula << endl;
            break;
        }
        case 3: {
            string cedula;
            cout << "Ingrese la cedula: ";
            cin.ignore();
            getline(cin, cedula);

            if (!validarCedula(cedula)) {
                cout << "Cedula invalida. Ingrese una cedula valida." << endl;
                break;
            }

            if (!listaPersonal.existeUsuario(cedula)) {
                cout << "El usuario no existe. Registre al usuario antes de registrar la hora de entrada, salida o almuerzo." << endl;
                break;
            }

            int opcionRegistroUsuario = 0;
            while (opcionRegistroUsuario != 4) {
                mostrarMenuRegistroUsuario();
                cin >> opcionRegistroUsuario;

                switch (opcionRegistroUsuario) {
                case 1: {
                    string horaEntrada = obtenerHoraActual();
                    listaPersonal.registrarHoraEntrada(cedula, horaEntrada);
                    cout << "Se registró la hora de entrada: " << horaEntrada << endl;
                    break;
                }
                case 2: {
                    string horaAlmuerzo = obtenerHoraActual();
                    listaPersonal.registrarHoraAlmuerzo(cedula, horaAlmuerzo);
                    cout << "Se registró la hora de almuerzo: " << horaAlmuerzo << endl;
                    break;
                }
                case 3: {
                    string horaSalida = obtenerHoraActual();
                    listaPersonal.registrarHoraSalida(cedula, horaSalida);
                    cout << "Se registró la hora de salida: " << horaSalida << endl;
                    break;
                }
                case 4:
                    cout << "Volviendo al menú principal..." << endl;
                    break;
                default:
                    cout << "Opción inválida. Por favor, ingrese una opción válida." << endl;
                    break;
                }
            }

            break;
        }
        case 4:
            listaPersonal.mostrarRegistros();
            break;
        case 5:
            cout << "Saliendo del programa..." << endl;
            break;
        default:
            cout << "Opción inválida. Por favor, ingrese una opción válida." << endl;
            break;
        }
    }

    guardarRegistrosEnArchivo(nombreArchivo, listaPersonal);

    return 0;
}



//#include <iostream>
//#include <fstream>
//#include <sstream>
//#include <iomanip>
//
//// Estructura para almacenar los datos del usuario
//struct Usuario {
//    std::string nombre=nombre;
//    std::string contrasenia=contrasenia;
//};
//
//// Función para escapar comas en una cadena
//std::string escapeCommas(const std::string& input) {
//    std::ostringstream ss;
//    for (char c : input) {
//        if (c == ',')
//            ss << "\",\"";
//        else
//            ss << c;
//    }
//    return ss.str();
//}
//
//// Función para des-escapar comas en una cadena
//std::string unescapeCommas(const std::string& input) {
//    std::ostringstream ss;
//    std::istringstream iss(input);
//    std::string token;
//    while (std::getline(iss, token, ',')) {
//        if (token == "\",\"")
//            ss << ',';
//        else
//            ss << token;
//    }
//    return ss.str();
//}
//
//// Función para registrar un usuario en el archivo de texto
//void registrarUsuario(const Usuario& usuario, const std::string& archivo) {
//    std::ofstream file(archivo, std::ios::app); // Abrir el archivo en modo adjuntar
//
//    if (file.is_open()) {
//        // Escapar comas en los datos del usuario
//        std::string nombreEscapado = escapeCommas(usuario.nombre);
//        std::string contraseniaEscapada = escapeCommas(usuario.contrasenia);
//
//        // Escribir los datos en el archivo
//        file << nombreEscapado << "," << contraseniaEscapada << "\n";
//
//        std::cout << "Usuario registrado exitosamente\n";
//
//        file.close(); // Cerrar el archivo
//    }
//    else {
//        std::cout << "No se puede abrir el archivo\n";
//    }
//}
//
//// Función para buscar un usuario en el archivo de texto
//bool buscarUsuario(const std::string& nombreUsuario, const std::string& archivo) {
//    std::ifstream file(archivo);
//
//    if (file.is_open()) {
//        std::string line;
//        while (std::getline(file, line)) {
//            std::istringstream iss(line);
//            std::string nombre, contrasenia;
//            std::getline(iss, nombre, ',');
//            std::getline(iss, contrasenia, ',');
//
//            // Des-escapar comas en los datos del usuario
//            nombre = unescapeCommas(nombre);
//            contrasenia = unescapeCommas(contrasenia);
//
//            // Comprobar si el nombre de usuario coincide
//            if (nombre == nombreUsuario) {
//                std::cout << "Usuario encontrado. Datos del usuario:\n";
//                std::cout << "Nombre: " << nombre << "\n";
//                std::cout << "Contraseña: " << contrasenia << "\n";
//                file.close(); // Cerrar el archivo
//                return true;
//            }
//        }
//
//        std::cout << "Usuario no encontrado\n";
//        file.close(); // Cerrar el archivo
//    }
//    else {
//        std::cout << "No se puede abrir el archivo\n";
//    }
//
//    return false;
//}
//
//int main() {
//    std::string archivo = "usuarios.txt";
//
//    // Registro de usuario
//    Usuario nuevoUsuario;
//    std::cout << "Ingrese su nombre de usuario: ";
//    std::cin >> nuevoUsuario.nombre;
//    std::cout << "Ingrese su contraseña: ";
//    std::cin >> nuevoUsuario.contrasenia;
//
//    // Registrar el usuario en el archivo de texto
//    registrarUsuario(nuevoUsuario, archivo);
//
//    // Buscar un usuario en el archivo de texto
//    std::string nombreBuscar;
//    std::cout << "Ingrese el nombre de usuario a buscar: ";
//    std::cin >> nombreBuscar;
//    buscarUsuario(nombreBuscar, archivo);
//
//    return 0;
//}
