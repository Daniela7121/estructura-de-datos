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

class Nodo {
public:
    Constancia dato;
    Nodo* siguiente;

    Nodo(const Constancia& c) : dato(c), siguiente(nullptr) {}
};

class ColaDinamica {
private:
    Nodo* frente;
    Nodo* final;

public:
    ColaDinamica() : frente(nullptr), final(nullptr) {}

    void encolar(const Constancia& c) {
        Nodo* nuevo = new Nodo(c);
        if (final == nullptr) {
            frente = final = nuevo;
        } else {
            final->siguiente = nuevo;
            final = nuevo;
        }
        cout << "Solicitud encolada correctamente." << endl;
    }

    void desencolar() {
        if (frente == nullptr) {
            cout << "No hay solicitudes pendientes." << endl;
            return;
        }

        Nodo* temp = frente;
        frente = frente->siguiente;

        if (frente == nullptr) {
            final = nullptr;
        }

        cout << "Constancia elaborada:\n" << temp->dato << endl;
        delete temp;
    }

    ~ColaDinamica() {
        while (frente != nullptr) {
            Nodo* temp = frente;
            frente = frente->siguiente;
            delete temp;
        }
    }
};

int main() {
    ColaDinamica cola;
    int opcion;

    do {
        cout << "\nMenu:\n1. Dar de alta solicitud\n2. Elaborar constancia\n3. Salir\nOpcion: ";
        cin >> opcion;
        cin.ignore();

        if (opcion == 1) {
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
        }
        else if (opcion == 2) {
            cola.desencolar();
        }
    } while (opcion != 3);

    return 0;
}
