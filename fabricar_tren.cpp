#include <iostream>
using namespace std;

// Nodo del tren (vagón)
class Nodo {
public:
    int data;
    Nodo* next;
    Nodo(int data) {
        this->data = data;
        this->next = nullptr;
    }
};

// Lista enlazada representando el tren
class Tren {
private:
    Nodo* head; // locomotora

public:
    Tren() {
        head = nullptr;
    }

    void agregarVagon(int data) {
        Nodo* nuevo = new Nodo(data);
        // Si no hay locomotora, crearla
        if (head == nullptr) {
            head = nuevo;
            cout << "Locomotora creada: " << data << endl;
        } else {
            // Agregar vagón al final
            Nodo* current = head;
            while (current->next != nullptr)
                current = current->next;
            current->next = nuevo;
            cout << "Vagon agregado: " << data << endl;
        }
    }

    void eliminarVagon(int data) {
        // Si no hay locomotora
        if (head == nullptr) {
            cout << "No hay tren para eliminar vagones.\n";
            return;
        }

        // Eliminar locomotora
        if (head->data == data) {
            Nodo* temp = head;
            head = head->next;
            delete temp;
            cout << "Locomotora eliminada.\n";
            return;
        }
        // Eliminar vagón
        Nodo* current = head;
        Nodo* prev = nullptr;
        while (current != nullptr && current->data != data) {
            prev = current;
            current = current->next;
        }

        if (current == nullptr) {
            cout << "No se encontró el vagon " << data << endl;
            return;
        }

        prev->next = current->next;
        delete current;
        cout << "Vagon " << data << " eliminado.\n";
    }

    void mostrarTren() {
        if (head == nullptr) {
            cout << "El tren no tiene locomotora ni vagones.\n";
            return;
        }

        // Línea de vapor
        cout << "  e@@@@@@@@@@@@@@\n";
        cout << "    @@@\"\"\"\"\"\"\"\"\"\"\n";

        // Contar cuántos nodos (vagones) hay
        int count = 0;
        Nodo* current = head;
        while (current != nullptr) {
            count++;
            current = current->next;
        }

        // Línea 1: techo locomotora + techos de vagones
        cout << "   @\" ___";
        for (int i = 1; i < count; i++)
            cout << "  ___________";
        cout << "\n";

        // Línea 2: parte frontal de locomotora + vagones
        cout << "  II__[w]";
        for (int i = 1; i < count; i++)
            cout << "  | [i] [z] |";
        cout << "\n";

        // Línea 3: parte media (ventanas / cuerpo)
        cout << " {======|";
        for (int i = 1; i < count; i++)
            cout << "__|~~~~~~~~~|";
        cout << "\n";

        // Línea 4: ruedas
        cout << "/oO--000'";
        for (int i = 1; i < count; i++)
            cout << "\"\"`-OO---OO-'";
        cout << "\n";

        // Mostrar debajo los datos de cada nodo (como identificación de vagones)
        cout << "\nVagones: ";
        current = head;
        while (current != nullptr) {
            cout << "[" << current->data << "] ";
            current = current->next;
        }
        cout << "\n";
    }


    // Eliminar todos los vagones y locomotora
    void destruirTren() {
        Nodo* current = head;
        while (current != nullptr) {
            Nodo* temp = current;
            current = current->next;
            delete temp;
        }
        head = nullptr;
        cout << "Todo el tren ha sido destruido.\n";
    }

    ~Tren() {
        destruirTren();
    }
};

int main() {
    Tren tren;
    int opcion, valor;

    do {
        cout << "\n--- Menu del Tren ---\n";
        cout << "1. Agregar vagon (o locomotora si no existe)\n";
        cout << "2. Eliminar vagon por valor\n";
        cout << "3. Mostrar tren\n";
        cout << "4. Destruir todo el tren\n";
        cout << "0. Salir\n";
        cout << "Ingrese opcion: ";
        cin >> opcion;

        switch(opcion) {
            case 1:
                cout << "Ingrese valor del vagon: ";
                cin >> valor;
                tren.agregarVagon(valor);
                break;
            case 2:
                cout << "Ingrese valor del vagon a eliminar: ";
                cin >> valor;
                tren.eliminarVagon(valor);
                break;
            case 3:
                tren.mostrarTren();
                break;
            case 4:
                tren.destruirTren();
                break;
            case 0:
                cout << "Saliendo...\n";
                break;
            default:
                cout << "Opcion invalida.\n";
        }

    } while(opcion != 0);

    return 0;
}
