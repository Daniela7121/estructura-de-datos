#include <iostream>
#include <string>

using namespace std;

class Constancia {
private:
    string nombreAlumno;
    string carrera;
    int materiasAprobadas;
    float promedio;
public:
    Constancia() : nombreAlumno(""), carrera(""), materiasAprobadas(0), promedio(0.0) {}
    Constancia(string n, string c, int m, float p) :
        nombreAlumno(n), carrera(c), materiasAprobadas(m), promedio(p) {}

    friend ostream& operator<<(ostream& os, const Constancia& c) {
        os << "CONSTANCIA DE ESTUDIO\n";
        os << "Nombre del alumno: " << c.nombreAlumno << "\n";
        os << "Carrera: " << c.carrera << "\n";
        os << "Materias aprobadas: " << c.materiasAprobadas << "\n";
        os << "Promedio general: " << c.promedio << "\n";
        return os;
    }
};

class ColaEstatica {
private:
    static const int MAX = 100;
    Constancia elementos[MAX];
    int frente;
    int final;
    int cantidad;

public:
    ColaEstatica() : frente(0), final(-1), cantidad(0) {}

    bool encolar(const Constancia& c) {
        if (cantidad >= MAX) {
            cout << "Error: Cola llena." << endl;
            return false;
        }

        final = (final + 1) % MAX;
        elementos[final] = c;
        cantidad++;
        return true;
    }

    bool desencolar() {
        if (cantidad <= 0) {
            cout << "Error: Cola vacía." << endl;
            return false;
        }

        cout << "Constancia elaborada:\n" << elementos[frente] << endl;
        frente = (frente + 1) % MAX;
        cantidad--;
        return true;
    }

    bool vacia() const {
        return cantidad == 0;
    }

    bool llena() const {
        return cantidad == MAX;
    }
};

int main() {
    ColaEstatica cola;
    int opcion;

    do {
        cout << "\nMenu:\n1. Dar de alta solicitud\n2. Elaborar constancia\n3. Salir\nOpcion: ";
        cin >> opcion;
        cin.ignore();

        if (opcion == 1) {
            if (cola.llena()) {
                cout << "No se puede encolar, cola llena." << endl;
                continue;
            }

            string nombre, carrera;
            int materias;
            float promedio;

            cout << "Nombre del alumno: ";
            getline(cin, nombre);
            cout << "Carrera: ";
            getline(cin, carrera);
            cout << "Materias aprobadas: ";
            cin >> materias;
            cout << "Promedio general: ";
            cin >> promedio;
            cin.ignore();

            cola.encolar(Constancia(nombre, carrera, materias, promedio));
            cout << "Solicitud encolada correctamente." << endl;
        }
        else if (opcion == 2) {
            cola.desencolar();
        }
    } while (opcion != 3);

    return 0;
}
