#include <iostream>
#include <string>
#include <algorithm> // Para sort en búsqueda binaria
using namespace std;

const int TAM = 100;

class SolicitudConstancia {
private:
    string nombreAlumno;
    string carrera;
    int materiasAprobadas;
    float promedio;

public:
    SolicitudConstancia() : nombreAlumno(""), carrera(""), materiasAprobadas(0), promedio(0.0) {}

    SolicitudConstancia(string nombre, string carr, int materias, float prom) :
        nombreAlumno(nombre), carrera(carr), materiasAprobadas(materias), promedio(prom) {}

    // Sobrecarga de operadores
    void operator=(const SolicitudConstancia& x) {
        nombreAlumno = x.nombreAlumno;
        carrera = x.carrera;
        materiasAprobadas = x.materiasAprobadas;
        promedio = x.promedio;
    }

    bool operator==(const SolicitudConstancia& other) const {
        return nombreAlumno == other.nombreAlumno;
    }

    bool operator<(const SolicitudConstancia& other) const {
        return nombreAlumno < other.nombreAlumno;
    }

    friend ostream& operator<<(ostream& os, const SolicitudConstancia& sc) {
        os << "CONSTANCIA DE ESTUDIO\n";
        os << "Nombre: " << sc.nombreAlumno << "\n";
        os << "Carrera: " << sc.carrera << "\n";
        os << "Materias: " << sc.materiasAprobadas << "\n";
        os << "Promedio: " << sc.promedio << "\n";
        return os;
    }

    friend istream& operator>>(istream& is, SolicitudConstancia& sc) {
        cout << "Nombre del alumno: ";
        getline(is, sc.nombreAlumno);
        cout << "Carrera: ";
        getline(is, sc.carrera);
        cout << "Materias aprobadas: ";
        is >> sc.materiasAprobadas;
        cout << "Promedio general: ";
        is >> sc.promedio;
        is.ignore();
        return is;
    }

    // Getters
    string getNombre() const { return nombreAlumno; }
    string getCarrera() const { return carrera; }
    int getMaterias() const { return materiasAprobadas; }
    float getPromedio() const { return promedio; }
};

class Cola {
private:
    SolicitudConstancia datos[TAM];
    int ult;
    int frente;

    bool elimina(int pos) {
        if (pos < 0 || pos > ult) return false;
        for (int i = pos; i < ult; i++) {
            datos[i] = datos[i + 1];
        }
        ult--;
        return true;
    }

    bool inserta(const SolicitudConstancia& elem, int pos) {
        if (llena() || pos < 0 || pos > ult + 1) return false;
        for (int i = ult + 1; i > pos; i--) {
            datos[i] = datos[i - 1];
        }
        datos[pos] = elem;
        ult++;
        return true;
    }

public:
    Cola() : ult(-1), frente(0) {}

    bool vacia() const {
        return ult == -1;
    }

    bool llena() const {
        return ult == TAM - 1;
    }

    int ultimo() const {
        return ult;
    }

    friend ostream& operator<<(ostream& o, Cola& L) {
        if (L.vacia()) {
            o << "Cola vacia";
            return o;
        }
        for (int i = L.frente; i <= L.ult; i++) {
            o << L.datos[i] << "\n";
        }
        return o;
    }

    void enqueue(const SolicitudConstancia& elem) {
        if (!llena()) {
            datos[++ult] = elem;
        }
    }

    SolicitudConstancia dequeue() {
        if (vacia()) {
            throw runtime_error("Cola vacia");
        }
        return datos[frente++];
    }

    int busquedaLineal(const SolicitudConstancia& elem) {
        for (int i = frente; i <= ult; i++) {
            if (datos[i] == elem) {
                return i - frente;
            }
        }
        return -1;
    }

    int busquedaBinaria(const string& nombre) {
        // Crear copia temporal ordenada para búsqueda binaria
        SolicitudConstancia temp[TAM];
        int size = ult - frente + 1;
        for (int i = 0; i < size; i++) {
            temp[i] = datos[frente + i];
        }

        sort(temp, temp + size);

        int izquierda = 0;
        int derecha = size - 1;

        while (izquierda <= derecha) {
            int medio = izquierda + (derecha - izquierda) / 2;

            if (temp[medio].getNombre() == nombre) {
                // Encontrar posición real en la cola original
                for (int i = frente; i <= ult; i++) {
                    if (datos[i].getNombre() == nombre) {
                        return i - frente;
                    }
                }
            }

            if (temp[medio].getNombre() < nombre) {
                izquierda = medio + 1;
            } else {
                derecha = medio - 1;
            }
        }
        return -1;
    }
};

int main() {
    Cola colaConstancias;
    int opcion;

    do {
        cout << "\nMenu:\n1. Dar de alta solicitud\n2. Elaborar constancia\n";
        cout << "3. Buscar solicitud (lineal)\n4. Buscar solicitud (binaria)\n5. Salir\nOpcion: ";
        cin >> opcion;
        cin.ignore();

        try {
            switch (opcion) {
                case 1: {
                    if (colaConstancias.llena()) {
                        cout << "La cola esta llena. No se pueden agregar mas solicitudes.\n";
                        break;
                    }
                    SolicitudConstancia nueva;
                    cin >> nueva;
                    colaConstancias.enqueue(nueva);
                    cout << "Solicitud agregada correctamente.\n";
                    break;
                }
                case 2: {
                    if (colaConstancias.vacia()) {
                        cout << "No hay solicitudes pendientes.\n";
                    } else {
                        SolicitudConstancia sc = colaConstancias.dequeue();
                        cout << "\nConstancia elaborada:\n" << sc << endl;
                    }
                    break;
                }
                case 3: {
                    string nombre;
                    cout << "Nombre del alumno a buscar: ";
                    getline(cin, nombre);
                    SolicitudConstancia temp(nombre, "", 0, 0.0f);

                    int pos = colaConstancias.busquedaLineal(temp);
                    if (pos != -1) {
                        cout << "Solicitud encontrada. Hay " << pos << " constancias antes de esta.\n";
                    } else {
                        cout << "No se encontro la solicitud. Debe dar de alta una nueva.\n";
                    }
                    break;
                }
                case 4: {
                    string nombre;
                    cout << "Nombre del alumno a buscar: ";
                    getline(cin, nombre);

                    int pos = colaConstancias.busquedaBinaria(nombre);
                    if (pos != -1) {
                        cout << "Solicitud encontrada (binaria). Hay " << pos << " constancias antes de esta.\n";
                    } else {
                        cout << "No se encontro la solicitud (binaria). Debe dar de alta una nueva.\n";
                    }
                    break;
                }
                case 5:
                    cout << "Saliendo del programa...\n";
                    break;
                default:
                    cout << "Opcion no valida.\n";
            }
        } catch (const exception& e) {
            cerr << "Error: " << e.what() << endl;
        }
    } while (opcion != 5);

    return 0;
}
