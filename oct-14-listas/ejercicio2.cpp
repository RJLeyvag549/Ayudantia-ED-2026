#include <iostream>
#include <string>

using namespace std;

// ============================================================================
// EJERCICIO 2: LISTA ENLAZADA CIRCULAR SIMPLE (SOLO CON HEAD)
// Caso: Mesa de Juego de Cartas por Rondas (Eliminación por nombre)
// ============================================================================

class NodoJugador {
public:
    string nombre;
    NodoJugador* next;

    NodoJugador(string nombre) {
        this->nombre = nombre;
        this->next = nullptr;
    }
};

class MesaJuego {
public:
    NodoJugador* head;

    MesaJuego() {
        head = nullptr;
    }

    // 1. Agregar jugador al final del círculo
    void agregarJugador(string nombre) {
        NodoJugador* nuevo = new NodoJugador(nombre);

        if (head == nullptr) {
            head = nuevo;
            nuevo->next = head; // Cierra el ciclo consigo mismo
            return;
        }

        NodoJugador* actual = head;
        while (actual->next != head) {
            actual = actual->next;
        }

        actual->next = nuevo;
        nuevo->next = head; // Cierra el ciclo hacia head
    }

    // 2. Jugar una ronda completa recorriendo hasta volver a head
    void jugarRonda() {
        if (head == nullptr) {
            cout << "Mesa vacía, nada por jugar." << endl;
            return;
        }

        cout << "--- JUGANDO RONDA DE CARTAS ---" << endl;
        NodoJugador* actual = head;
        do {
            cout << "Turno de: [" << actual->nombre << "]" << endl;
            actual = actual->next;
        } while (actual != head);
        cout << "--- FIN DE LA RONDA ---\n" << endl;
    }

    // 3. Eliminar por nombre (versión sencilla y limpia para certamen)
    void eliminarJugador(string nombre) {
        if (head == nullptr) return;

        // Caso A: Si es el único jugador en la mesa
        if (head->next == head && head->nombre == nombre) {
            delete head;
            head = nullptr;
            cout << "Se eliminó el único jugador (" << nombre << "). Mesa vacía." << endl;
            return;
        }

        // Caso B: Si el jugador a eliminar es la cabeza (head)
        if (head->nombre == nombre) {
            // Buscamos el último para que apunte al nuevo head
            NodoJugador* ultimo = head;
            while (ultimo->next != head) {
                ultimo = ultimo->next;
            }
            NodoJugador* aEliminar = head;
            head = head->next;
            ultimo->next = head;
            delete aEliminar;
            cout << "Se eliminó al jugador '" << nombre << "' (era head)." << endl;
            return;
        }

        // Caso C: El jugador está en cualquier otra posición (intermedio o final)
        NodoJugador* actual = head;
        while (actual->next != head && actual->next->nombre != nombre) {
            actual = actual->next;
        }

        // Si lo encontramos como el siguiente de 'actual'
        if (actual->next->nombre == nombre) {
            NodoJugador* aEliminar = actual->next;
            actual->next = aEliminar->next; // Se salta el nodo a eliminar
            delete aEliminar;
            cout << "Se eliminó al jugador '" << nombre << "' de la mesa." << endl;
        } else {
            cout << "Jugador '" << nombre << "' no encontrado en la mesa." << endl;
        }
    }

    void mostrarMesa() {
        if (head == nullptr) {
            cout << "Mesa vacía." << endl;
            return;
        }
        NodoJugador* actual = head;
        do {
            cout << "[" << actual->nombre << "] -> ";
            actual = actual->next;
        } while (actual != head);
        cout << "(vuelve a " << head->nombre << ")" << endl;
    }
};

int main() {
    MesaJuego mesa;

    mesa.agregarJugador("Alice");
    mesa.agregarJugador("Bob");
    mesa.agregarJugador("Carlos");
    mesa.agregarJugador("Diana");

    mesa.mostrarMesa();
    cout << endl;

    // Ronda 1 con 4 jugadores
    mesa.jugarRonda();

    // Eliminar a Carlos (caso intermedio)
    mesa.eliminarJugador("Carlos");
    mesa.mostrarMesa();
    cout << endl;

    // Eliminar a Alice (caso que es head)
    mesa.eliminarJugador("Alice");
    mesa.mostrarMesa();
    cout << endl;

    // Ronda 2 con los restantes (Bob y Diana)
    mesa.jugarRonda();

    return 0;
}
