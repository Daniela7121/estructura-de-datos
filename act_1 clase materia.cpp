#include <iostream>
#include <string>

using namespace std;

class Materia {
private:
    string clave;
    string nombre;
    string maestro;
    int creditos;
public:
    Materia() : clave(""), nombre(""), maestro(""), creditos(0) {}
    Materia(string c, string n, string m, int cr) :
        clave(c), nombre(n), maestro(m), creditos(cr) {}

    // Sobrecarga de operadores
    bool operator==(const Materia& other) const {
        return clave == other.clave;
    }

    bool operator!=(const Materia& other) const {
        return !(*this == other);
    }

    bool operator<(const Materia& other) const {
        return creditos < other.creditos;
    }

    bool operator>(const Materia& other) const {
        return creditos > other.creditos;
    }

    Materia operator+(const Materia& other) const {
        return Materia(clave + "-" + other.clave,
                      nombre + " y " + other.nombre,
                      maestro + " & " + other.maestro,
                      creditos + other.creditos);
    }

    friend ostream& operator<<(ostream& os, const Materia& m) {
        os << "Clave: " << m.clave << "\nNombre: " << m.nombre
           << "\nMaestro: " << m.maestro << "\nCreditos: " << m.creditos;
        return os;
    }

    friend istream& operator>>(istream& is, Materia& m) {
        cout << "Ingrese clave: ";
        getline(is, m.clave);
        cout << "Ingrese nombre: ";
        getline(is, m.nombre);
        cout << "Ingrese maestro: ";
        getline(is, m.maestro);
        cout << "Ingrese creditos: ";
        is >> m.creditos;
        is.ignore();
        return is;
    }

    // Métodos de acceso
    string getClave() const { return clave; }
    string getMaestro() const { return maestro; }

    // Métodos de actualización
    void setClave(const string& c) { clave = c; }
    void setMaestro(const string& m) { maestro = m; }
};

void mostrarMenu() {
    cout << "\nMENU PRINCIPAL\n";
    cout << "1. Cambiar clave de Programacion\n";
    cout << "2. Cambiar maestro de Bases de Datos\n";
    cout << "3. Imprimir datos de Bases de Datos\n";
    cout << "4. Salir\n";
    cout << "Seleccione una opcion: ";
}

int main() {
    Materia programacion("PROG1", "Programacion I", "Dr. Garcia", 8);
    Materia basesDatos("BD1", "Bases de Datos", "Ing. Martinez", 6);

    int opcion;
    do {
        mostrarMenu();
        cin >> opcion;
        cin.ignore();

        switch(opcion) {
            case 1: {
                string nuevaClave;
                cout << "\nIngrese la nueva clave para Programacion: ";
                getline(cin, nuevaClave);
                programacion.setClave(nuevaClave);
                cout << "Clave actualizada correctamente.\n";
                break;
            }
            case 2: {
                string nuevoMaestro;
                cout << "\nIngrese el nuevo maestro para Bases de Datos: ";
                getline(cin, nuevoMaestro);
                basesDatos.setMaestro(nuevoMaestro);
                cout << "Maestro actualizado correctamente.\n";
                break;
            }
            case 3: {
                cout << "\nDatos de la materia Bases de Datos:\n";
                cout << basesDatos << endl;
                break;
            }
            case 4:
                cout << "Saliendo del programa...\n";
                break;
            default:
                cout << "Opcion no valida. Intente de nuevo.\n";
        }
    } while (opcion != 4);

    return 0;
}
