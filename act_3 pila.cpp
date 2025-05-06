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

    friend ostream& operator<<(ostream& os, const Empleado& e) {
        os << "Clave: " << e.clave << "\nNombre: " << e.nombre
           << "\nDomicilio: " << e.domicilio << "\nSueldo: " << e.sueldo
           << "\nReporta a: " << e.reportaA;
        return os;
    }
};

class PilaEstatica {
private:
    static const int MAX = 100;
    Empleado elementos[MAX];
    int tope;
public:
    PilaEstatica() : tope(-1) {}

    bool push(const Empleado& e) {
        if (tope >= MAX - 1) {
            cout << "Error: Pila llena." << endl;
            return false;
        }
        elementos[++tope] = e;
        return true;
    }

    bool pop() {
        if (tope < 0) {
            cout << "Error: Pila vacía." << endl;
            return false;
        }
        tope--;
        return true;
    }

    bool top(Empleado& e) const {
        if (tope < 0) {
            cout << "Error: Pila vacía." << endl;
            return false;
        }
        e = elementos[tope];
        return true;
    }

    bool vacia() const {
        return tope < 0;
    }

    bool llena() const {
        return tope >= MAX - 1;
    }
};

int main() {
    PilaEstatica pila;
    int opcion;

    do {
        cout << "\nMenu:\n1. Push\n2. Pop\n3. Top\n4. Salir\nOpcion: ";
        cin >> opcion;
        cin.ignore();

        if (opcion == 1) {
            if (pila.llena()) {
                cout << "No se puede hacer push, pila llena." << endl;
                continue;
            }

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

            pila.push(Empleado(nombre, domicilio, clave, sueldo, reportaA));
            cout << "Empleado agregado a la pila." << endl;
        }
        else if (opcion == 2) {
            if (pila.pop()) {
                cout << "Elemento eliminado de la pila." << endl;
            }
        }
        else if (opcion == 3) {
            Empleado e;
            if (pila.top(e)) {
                cout << "Elemento en el tope:\n" << e << endl;
            }
        }
    } while (opcion != 4);

    return 0;
}
