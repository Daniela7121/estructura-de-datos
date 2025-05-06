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

    // Sobrecarga de operadores
    bool operator==(const Empleado& other) const {
        return clave == other.clave;
    }

    bool operator!=(const Empleado& other) const {
        return !(*this == other);
    }

    bool operator<(const Empleado& other) const {
        return sueldo < other.sueldo;
    }

    bool operator>(const Empleado& other) const {
        return sueldo > other.sueldo;
    }

    Empleado operator+(const Empleado& other) const {
        return Empleado(nombre + " & " + other.nombre,
                       domicilio + " / " + other.domicilio,
                       clave + other.clave,
                       sueldo + other.sueldo,
                       reportaA + " + " + other.reportaA);
    }

    friend ostream& operator<<(ostream& os, const Empleado& e) {
        os << "Clave: " << e.clave << "\nNombre: " << e.nombre
           << "\nDomicilio: " << e.domicilio << "\nSueldo: " << e.sueldo
           << "\nReporta a: " << e.reportaA;
        return os;
    }

    friend istream& operator>>(istream& is, Empleado& e) {
        cout << "Nombre: ";
        getline(is, e.nombre);
        cout << "Domicilio: ";
        getline(is, e.domicilio);
        cout << "Clave: ";
        is >> e.clave;
        cout << "Sueldo: ";
        is >> e.sueldo;
        is.ignore();
        cout << "Reporta a: ";
        getline(is, e.reportaA);
        return is;
    }

    // Métodos de acceso
    int getClave() const { return clave; }
    string getDomicilio() const { return domicilio; }
    float getSueldo() const { return sueldo; }
    string getReportaA() const { return reportaA; }

    // Métodos de actualización
    void setDomicilio(const string& d) { domicilio = d; }
    void setSueldo(float s) { sueldo = s; }
    void setReportaA(const string& r) { reportaA = r; }
};

void mostrarMenu() {
    cout << "\nMENU PRINCIPAL\n";
    cout << "1. Cambiar domicilio de un empleado\n";
    cout << "2. Actualizar sueldo de un empleado\n";
    cout << "3. Imprimir datos de un empleado\n";
    cout << "4. Cambiar persona a reportar\n";
    cout << "5. Salir\n";
    cout << "Seleccione una opcion: ";
}

int main() {
    Empleado jefePlanta("Juan Perez", "Calle 123", 1001, 25000, "Gerente General");
    Empleado jefePersonal("Maria Lopez", "Avenida 456", 1002, 22000, "Directora RH");

    int opcion;
    do {
        mostrarMenu();
        cin >> opcion;
        cin.ignore();

        switch(opcion) {
            case 1: {
                int clave;
                string nuevoDomicilio;

                cout << "\nIngrese la clave del empleado (1001 o 1002): ";
                cin >> clave;
                cin.ignore();
                cout << "Ingrese el nuevo domicilio: ";
                getline(cin, nuevoDomicilio);

                if (clave == jefePlanta.getClave()) {
                    jefePlanta.setDomicilio(nuevoDomicilio);
                    cout << "Domicilio actualizado correctamente.\n";
                } else if (clave == jefePersonal.getClave()) {
                    jefePersonal.setDomicilio(nuevoDomicilio);
                    cout << "Domicilio actualizado correctamente.\n";
                } else {
                    cout << "Error: Clave de empleado no valida.\n";
                }
                break;
            }
            case 2: {
                int clave;
                float porcentaje;

                cout << "\nIngrese la clave del empleado (1001 o 1002): ";
                cin >> clave;
                cout << "Ingrese el porcentaje de incremento: ";
                cin >> porcentaje;
                cin.ignore();

                if (clave == jefePlanta.getClave()) {
                    float nuevoSueldo = jefePlanta.getSueldo() * (1 + porcentaje/100);
                    jefePlanta.setSueldo(nuevoSueldo);
                    cout << "Sueldo actualizado a: " << nuevoSueldo << endl;
                } else if (clave == jefePersonal.getClave()) {
                    float nuevoSueldo = jefePersonal.getSueldo() * (1 + porcentaje/100);
                    jefePersonal.setSueldo(nuevoSueldo);
                    cout << "Sueldo actualizado a: " << nuevoSueldo << endl;
                } else {
                    cout << "Error: Clave de empleado no valida.\n";
                }
                break;
            }
            case 3: {
                int clave;
                cout << "\nIngrese la clave del empleado (1001 o 1002): ";
                cin >> clave;
                cin.ignore();

                if (clave == jefePlanta.getClave()) {
                    cout << "\nDatos del empleado:\n" << jefePlanta << endl;
                } else if (clave == jefePersonal.getClave()) {
                    cout << "\nDatos del empleado:\n" << jefePersonal << endl;
                } else {
                    cout << "Error: Clave de empleado no valida.\n";
                }
                break;
            }
            case 4: {
                int clave;
                string nuevaPersona;

                cout << "\nIngrese la clave del empleado (1001 o 1002): ";
                cin >> clave;
                cin.ignore();
                cout << "Ingrese el nuevo nombre de la persona a reportar: ";
                getline(cin, nuevaPersona);

                if (clave == jefePlanta.getClave()) {
                    jefePlanta.setReportaA(nuevaPersona);
                    cout << "Persona a reportar actualizada correctamente.\n";
                } else if (clave == jefePersonal.getClave()) {
                    jefePersonal.setReportaA(nuevaPersona);
                    cout << "Persona a reportar actualizada correctamente.\n";
                } else {
                    cout << "Error: Clave de empleado no valida.\n";
                }
                break;
            }
            case 5:
                cout << "Saliendo del programa...\n";
                break;
            default:
                cout << "Opcion no valida. Intente de nuevo.\n";
        }
    } while (opcion != 5);

    return 0;
}
