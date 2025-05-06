#include <iostream>
#include <string>
#include <limits>

using namespace std;

class SocioClub {
private:
    int numeroSocio;
    string nombreSocio;
    string domicilio;
    int anoIngreso;

public:
    // Constructor por defecto con inicialización uniforme
    SocioClub() : numeroSocio(0), nombreSocio(""), domicilio(""), anoIngreso(0) {}

    // Constructor con parámetros
    SocioClub(int num, const string& nom, const string& dom, int ano) :
        numeroSocio(num), nombreSocio(nom), domicilio(dom), anoIngreso(ano) {}

    // Operador de igualdad
    bool operator==(const SocioClub& other) const {
        return numeroSocio == other.numeroSocio;
    }

    // Operador menor que para ordenamiento
    bool operator<(const SocioClub& other) const {
        return numeroSocio < other.numeroSocio;
    }

    // Operador de salida para mostrar información
    friend ostream& operator<<(ostream& os, const SocioClub& s) {
        os << "Número de socio: " << s.numeroSocio << "\n"
           << "Nombre: " << s.nombreSocio << "\n"
           << "Domicilio: " << s.domicilio << "\n"
           << "Año de ingreso: " << s.anoIngreso << "\n";
        return os;
    }

    // Getters (const para garantizar inmutabilidad)
    int getNumero() const { return numeroSocio; }
    const string& getNombre() const { return nombreSocio; }
    const string& getDomicilio() const { return domicilio; }
};

class Nodo {
public:
    SocioClub socio;
    Nodo* siguiente;

    // Constructor explícito
    explicit Nodo(const SocioClub& s) : socio(s), siguiente(nullptr) {}
};

class ListaSocios {
private:
    Nodo* cabeza;
    int totalSocios;

    // Función auxiliar para inserción ordenada
    void insertarOrdenado(Nodo* nuevo) {
        if (!cabeza || nuevo->socio < cabeza->socio) {
            nuevo->siguiente = cabeza;
            cabeza = nuevo;
        } else {
            Nodo* actual = cabeza;
            while (actual->siguiente && actual->siguiente->socio < nuevo->socio) {
                actual = actual->siguiente;
            }
            nuevo->siguiente = actual->siguiente;
            actual->siguiente = nuevo;
        }
        totalSocios++;
    }

public:
    // Constructor
    ListaSocios() : cabeza(nullptr), totalSocios(0) {}

    // Destructor para liberar memoria
    ~ListaSocios() {
        while (cabeza) {
            Nodo* temp = cabeza;
            cabeza = cabeza->siguiente;
            delete temp;
        }
    }

    // Registrar nuevo socio
    void registrarSocio(const SocioClub& s) {
        // Verificar si ya existe el número de socio
        for (Nodo* actual = cabeza; actual; actual = actual->siguiente) {
            if (actual->socio == s) {
                cerr << "Error: Ya existe un socio con ese número." << endl;
                return;
            }
        }

        // Insertar ordenado por número de socio
        Nodo* nuevo = new Nodo(s);
        insertarOrdenado(nuevo);
        cout << "Socio registrado correctamente." << endl;
    }

    // Dar de baja a un socio
    void darDeBaja(int numero) {
        if (!cabeza) {
            cerr << "No hay socios registrados." << endl;
            return;
        }

        if (cabeza->socio.getNumero() == numero) {
            Nodo* temp = cabeza;
            cabeza = cabeza->siguiente;
            delete temp;
            totalSocios--;
            cout << "Socio dado de baja correctamente." << endl;
            return;
        }

        Nodo* actual = cabeza;
        while (actual->siguiente && actual->siguiente->socio.getNumero() != numero) {
            actual = actual->siguiente;
        }

        if (actual->siguiente) {
            Nodo* temp = actual->siguiente;
            actual->siguiente = temp->siguiente;
            delete temp;
            totalSocios--;
            cout << "Socio dado de baja correctamente." << endl;
        } else {
            cerr << "No se encontró el socio con ese número." << endl;
        }
    }

    // Generar reporte de todos los socios
    void generarReporte() const {
        if (!cabeza) {
            cerr << "No hay socios registrados." << endl;
            return;
        }

        cout << "\n=== REPORTE DE SOCIOS ===\n";
        for (Nodo* actual = cabeza; actual; actual = actual->siguiente) {
            cout << actual->socio << "-----------------\n";
        }
    }

    // Buscar socio por nombre y domicilio
    void buscarPorNombreYDomicilio(const string& nombre, const string& domicilio) const {
        bool encontrado = false;

        cout << "\nResultados de búsqueda:\n";
        for (Nodo* actual = cabeza; actual; actual = actual->siguiente) {
            if (actual->socio.getNombre() == nombre &&
                actual->socio.getDomicilio() == domicilio) {
                cout << actual->socio << endl;
                encontrado = true;
            }
        }

        if (!encontrado) {
            cerr << "No se encontraron socios con ese nombre y domicilio." << endl;
        }
    }

    // Mostrar total de socios registrados
    void imprimirTotalSocios() const {
        cout << "Total de socios registrados: " << totalSocios << endl;
    }

    // Eliminar copias no deseadas
    ListaSocios(const ListaSocios&) = delete;
    ListaSocios& operator=(const ListaSocios&) = delete;
};

int main() {
    ListaSocios lista;
    int opcion;

    do {
        cout << "\nMenu:\n1. Registrar socio\n2. Dar de baja socio\n3. Generar reporte\n"
             << "4. Buscar socio (nombre y domicilio)\n5. Total de socios\n6. Salir\nOpcion: ";

        if (!(cin >> opcion)) {
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            cerr << "Entrada inválida. Por favor ingrese un número." << endl;
            continue;
        }
        cin.ignore();

        try {
            switch (opcion) {
                case 1: {
                    int numero, ano;
                    string nombre, domicilio;

                    cout << "Número de socio: ";
                    if (!(cin >> numero)) throw runtime_error("Número de socio inválido");
                    cin.ignore();

                    cout << "Nombre: ";
                    getline(cin, nombre);
                    if (nombre.empty()) throw runtime_error("Nombre no puede estar vacío");

                    cout << "Domicilio: ";
                    getline(cin, domicilio);
                    if (domicilio.empty()) throw runtime_error("Domicilio no puede estar vacío");

                    cout << "Año de ingreso: ";
                    if (!(cin >> ano)) throw runtime_error("Año de ingreso inválido");
                    cin.ignore();

                    lista.registrarSocio(SocioClub(numero, nombre, domicilio, ano));
                    break;
                }
                case 2: {
                    int numero;
                    cout << "Número de socio a dar de baja: ";
                    if (!(cin >> numero)) throw runtime_error("Número de socio inválido");
                    cin.ignore();
                    lista.darDeBaja(numero);
                    break;
                }
                case 3:
                    lista.generarReporte();
                    break;
                case 4: {
                    string nombre, domicilio;
                    cout << "Nombre del socio: ";
                    getline(cin, nombre);
                    cout << "Domicilio: ";
                    getline(cin, domicilio);
                    lista.buscarPorNombreYDomicilio(nombre, domicilio);
                    break;
                }
                case 5:
                    lista.imprimirTotalSocios();
                    break;
                case 6:
                    cout << "Saliendo del programa..." << endl;
                    break;
                default:
                    cerr << "Opción no válida. Intente nuevamente." << endl;
            }
        } catch (const exception& e) {
            cerr << "Error: " << e.what() << endl;
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
        }
    } while (opcion != 6);

    return 0;
}
