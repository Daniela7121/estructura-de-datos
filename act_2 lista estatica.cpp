#include <iostream>
#include <string>

using namespace std;

class Empleado {
private:
    string nombre;
    string domicilio;
    int clave;
    float sueldo;
    string reportaA;
public:
    Empleado() : nombre(""), domicilio(""), clave(0), sueldo(0.0), reportaA("") {}
    Empleado(string n, string d, int c, float s, string r) :
        nombre(n), domicilio(d), clave(c), sueldo(s), reportaA(r) {}

    bool operator==(const Empleado& other) const {
        return clave == other.clave;
    }

    friend ostream& operator<<(ostream& os, const Empleado& e) {
        os << "Clave: " << e.clave << "\nNombre: " << e.nombre
           << "\nDomicilio: " << e.domicilio << "\nSueldo: " << e.sueldo
           << "\nReporta a: " << e.reportaA;
        return os;
    }

    int getClave() const { return clave; }
};

class ListaEstatica {
private:
    static const int MAX = 100;
    Empleado elementos[MAX];
    int cantidad;
public:
    ListaEstatica() : cantidad(0) {}

    bool agrega(const Empleado& e) {
        if (cantidad >= MAX) {
            cout << "Error: Lista llena." << endl;
            return false;
        }
        elementos[cantidad++] = e;
        return true;
    }

    void buscar(const Empleado& e) const {
        if (cantidad == 0) {
            cout << "La lista no tiene elementos guardados aún." << endl;
            return;
        }

        bool encontrado = false;
        for (int i = 0; i < cantidad; i++) {
            if (elementos[i] == e) {
                cout << "Empleado encontrado en la posición " << i + 1 << ":\n";
                cout << elementos[i] << endl;
                encontrado = true;
                break;
            }
        }

        if (!encontrado) {
            cout << "No hubo resultados en la búsqueda." << endl;
        }
    }

    bool elimina(const Empleado& e) {
        if (cantidad == 0) {
            cout << "La lista no tiene elementos guardados aún." << endl;
            return false;
        }

        for (int i = 0; i < cantidad; i++) {
            if (elementos[i] == e) {
                for (int j = i; j < cantidad - 1; j++) {
                    elementos[j] = elementos[j + 1];
                }
                cantidad--;
                cout << "Empleado eliminado correctamente." << endl;
                return true;
            }
        }

        cout << "El Empleado ingresado no existe." << endl;
        return false;
    }

    bool inserta(const Empleado& e, int posicion) {
        if (cantidad >= MAX) {
            cout << "Error: Lista llena." << endl;
            return false;
        }

        if (posicion < 1 || posicion > cantidad + 1) {
            cout << "Error: Posición inválida." << endl;
            return false;
        }

        for (int i = cantidad; i >= posicion; i--) {
            elementos[i] = elementos[i - 1];
        }

        elementos[posicion - 1] = e;
        cantidad++;
        cout << "Empleado insertado correctamente." << endl;
        return true;
    }

    void muestra() const {
        if (cantidad == 0) {
            cout << "La lista está vacía." << endl;
            return;
        }

        cout << "\n=== EMPLEADOS REGISTRADOS ===\n";
        for (int i = 0; i < cantidad; i++) {
            cout << elementos[i] << "\n-----------------\n";
        }
    }
};

int main() {
    ListaEstatica lista;
    int opcion;

    do {
        cout << "\nMenu:\n1. Agregar\n2. Buscar\n3. Eliminar\n4. Insertar\n5. Mostrar\n6. Salir\nOpcion: ";
        cin >> opcion;
        cin.ignore();

        if (opcion == 1) {
            string nombre, domicilio, reportaA;
            int clave;
            float sueldo;

            cout << "Nombre: ";
            getline(cin, nombre);
            cout << "Domicilio: ";
            getline(cin, domicilio);
            cout << "Clave: ";
            cin >> clave;
            cout << "Sueldo: ";
            cin >> sueldo;
            cin.ignore();
            cout << "Reporta a: ";
            getline(cin, reportaA);

            lista.agrega(Empleado(nombre, domicilio, clave, sueldo, reportaA));
        }
        else if (opcion == 2) {
            int clave;
            cout << "Clave del empleado a buscar: ";
            cin >> clave;
            cin.ignore();

            lista.buscar(Empleado("", "", clave, 0.0, ""));
        }
        else if (opcion == 3) {
            int clave;
            cout << "Clave del empleado a eliminar: ";
            cin >> clave;
            cin.ignore();

            lista.elimina(Empleado("", "", clave, 0.0, ""));
        }
        else if (opcion == 4) {
            string nombre, domicilio, reportaA;
            int clave, posicion;
            float sueldo;

            cout << "Nombre: ";
            getline(cin, nombre);
            cout << "Domicilio: ";
            getline(cin, domicilio);
            cout << "Clave: ";
            cin >> clave;
            cout << "Sueldo: ";
            cin >> sueldo;
            cin.ignore();
            cout << "Reporta a: ";
            getline(cin, reportaA);
            cout << "Posición para insertar: ";
            cin >> posicion;
            cin.ignore();

            lista.inserta(Empleado(nombre, domicilio, clave, sueldo, reportaA), posicion);
        }
        else if (opcion == 5) {
            lista.muestra();
        }
    } while (opcion != 6);

    return 0;
}
