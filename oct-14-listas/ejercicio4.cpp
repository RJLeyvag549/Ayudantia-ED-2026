#include <iostream>
#include <string>

using namespace std;

// ============================================================================
// EJERCICIO 4: COLA (QUEUE) BASADA EN NODOS
// Nomenclatura estándar: front, rear, enqueue, dequeue, isEmpty
// ============================================================================

class NodoSolicitud {
public:
    string idSolicitud;
    string usuario;
    NodoSolicitud* next;

    NodoSolicitud(string id, string user) {
        this->idSolicitud = id;
        this->usuario = user;
        this->next = nullptr;
    }
};

class ColaServidor {
public:
    NodoSolicitud* front;
    NodoSolicitud* rear;

    ColaServidor() {
        front = nullptr;
        rear = nullptr;
    }

    // 1. Encolar al final (rear) en O(1)
    void enqueue(string id, string usuario) {
        NodoSolicitud* nuevo = new NodoSolicitud(id, usuario);

        if (isEmpty()) {
            front = rear = nuevo;
        } else {
            rear->next = nuevo;
            rear = nuevo;
        }
        cout << "[+ Encolado] Solicitud " << id << " de " << usuario << " en fila." << endl;
    }

    // 2. Desencolar desde el frente (front) en O(1): simplemente elimina el primer nodo
    void dequeue() {
        if (isEmpty()) {
            cout << "[Aviso] No hay solicitudes pendientes, cola vacía." << endl;
            return;
        }

        NodoSolicitud* temp = front;
        cout << "[Atendiendo]: Solicitud " << temp->idSolicitud << " de " << temp->usuario << endl;

        front = front->next;

        // Si la cola quedó vacía, actualizamos rear a nullptr
        if (front == nullptr) {
            rear = nullptr;
        }

        delete temp;
    }

    // 3. Verificar si la cola está vacía
    bool isEmpty() {
        return front == nullptr;
    }

    void mostrarFila() {
        if (isEmpty()) {
            cout << "Fila de espera vacía." << endl;
            return;
        }
        NodoSolicitud* actual = front;
        cout << "Fila actual (front -> rear): ";
        while (actual != nullptr) {
            cout << "[" << actual->idSolicitud << " (" << actual->usuario << ")] ";
            actual = actual->next;
        }
        cout << endl;
    }
};

int main() {
    ColaServidor servidor;

    // Llegan solicitudes a la venta de entradas
    servidor.enqueue("REQ-101", "Ana");
    servidor.enqueue("REQ-102", "Bernardo");
    servidor.enqueue("REQ-103", "Clara");

    cout << endl;
    servidor.mostrarFila();

    cout << "\n--- Procesando solicitudes por orden de llegada (FIFO) ---" << endl;
    servidor.dequeue(); // Atiende a Ana (primer nodo)
    servidor.dequeue(); // Atiende a Bernardo (segundo nodo)

    cout << endl;
    servidor.mostrarFila(); // Queda solo Clara

    // Llega una nueva persona
    cout << "\n--- Llega una nueva solicitud ---" << endl;
    servidor.enqueue("REQ-104", "Daniel");
    servidor.mostrarFila();

    return 0;
}
