#include <iostream>
#include <string>
#include <vector>
#include <algorithm>

using namespace std;

class Solicitud {
private:
    string nombreAlumno;
    string carrera;
    string preparatoria;
    float promedio;
public:
    Solicitud() : nombreAlumno(""), carrera(""), preparatoria(""), promedio(0.0) {}
    Solicitud(string n, string c, string p, float prom) :
        nombreAlumno(n), carrera(c), preparatoria(p), promedio(prom) {}

   
    bool operator==(const Solicitud& other) const {
        return nombreAlumno == other.nombreAlumno;
    }

    bool operator<(const Solicitud& other) const {
        return promedio > other.promedio; // Orden descendente (mayor promedio primero)
    }

    bool operator>(const Solicitud& other) const {
        return promedio < other.promedio;
    }

    friend ostream& operator<<(ostream& os, const Solicitud& s) {
        os << "Nombre: " << s.nombreAlumno << "\nCarrera: " << s.carrera
           << "\nPreparatoria: " << s.preparatoria << "\nPromedio: " << s.promedio;
        return os;
    }


    string getNombre() const { return nombreAlumno; }
    float getPromedio() const { return promedio; }
};

class ListaSolicitudes {
private:
    vector<Solicitud> solicitudes;
public:
    void altaSolicitud(const Solicitud& s) {
        solicitudes.push_back(s);
        
        sort(solicitudes.begin(), solicitudes.end());
    }

    void buscarSolicitud(const string& nombre) {
    
        bool encontrado = false;
        int posicion = -1;

        for(size_t i = 0; i < solicitudes.size(); i++) {
            if(solicitudes[i].getNombre() == nombre) {
                encontrado = true;
                posicion = i + 1; // Posición en la lista (1-based)
                cout << "Datos de la solicitud:\n" << solicitudes[i] << endl;
                cout << "Lugar en la lista: " << posicion << " de " << solicitudes.size() << endl;
                break;
            }
        }

        if(!encontrado) {
            cout << "No se encontró la solicitud. Debe dar de alta una nueva." << endl;
        }
    }


    void busquedaBinaria(const string& nombre) {
        int izquierda = 0;
        int derecha = solicitudes.size() - 1;
        bool encontrado = false;

        while(izquierda <= derecha) {
            int medio = izquierda + (derecha - izquierda) / 2;

            if(solicitudes[medio].getNombre() == nombre) {
                encontrado = true;
                cout << "Datos de la solicitud (búsqueda binaria):\n" << solicitudes[medio] << endl;
                cout << "Lugar en la lista: " << medio + 1 << " de " << solicitudes.size() << endl;
                break;
            }

            if(solicitudes[medio].getNombre() < nombre) {
                izquierda = medio + 1;
            } else {
                derecha = medio - 1;
            }
        }

        if(!encontrado) {
            cout << "No se encontró la solicitud con búsqueda binaria." << endl;
        }
    }
};

int main() {
    ListaSolicitudes lista;
    int opcion;

    do {
        cout << "\nMenu:\n1. Dar de alta solicitud\n2. Buscar solicitud\n3. Salir\nOpcion: ";
        cin >> opcion;
        cin.ignore(); 

        if(opcion == 1) {
            string nombre, carrera, prepa;
            float promedio;

            cout << "Nombre del alumno: ";
            getline(cin, nombre);
            cout << "Carrera: ";
            getline(cin, carrera);
            cout << "Preparatoria: ";
            getline(cin, prepa);
            cout << "Promedio: ";
            cin >> promedio;
            cin.ignore();

            lista.altaSolicitud(Solicitud(nombre, carrera, prepa, promedio));
            cout << "Solicitud agregada correctamente." << endl;
        }
        else if(opcion == 2) {
            string nombre;
            cout << "Nombre del alumno a buscar: ";
            getline(cin, nombre);

            lista.buscarSolicitud(nombre);
           
        }
    } while(opcion != 3);

    return 0;
}
