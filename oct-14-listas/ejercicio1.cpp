#include <iostream>
#include <string>

using namespace std;

// ============================================================================
// EJERCICIO 1: LISTA LINEAL DOBLEMENTE ENLAZADA
// Caso: Visor de Galería de Fotos (Navegación bidireccional simple)
// ============================================================================

class NodoFoto {
public:
    string archivo;
    NodoFoto* prev;
    NodoFoto* next;

    NodoFoto(string archivo) {
        this->archivo = archivo;
        this->prev = nullptr;
        this->next = nullptr;
    }
};

class GaleriaFotos {
public:
    NodoFoto* head;
    NodoFoto* tail;
    NodoFoto* actual; // Puntero a la foto actualmente visible en pantalla

    GaleriaFotos() {
        head = nullptr;
        tail = nullptr;
        actual = nullptr;
    }

    // 1. Agregar foto al final de la galería en O(1)
    void agregarFoto(string archivo) {
        NodoFoto* nuevo = new NodoFoto(archivo);

        if (head == nullptr) {
            head = tail = actual = nuevo;
            return;
        }

        tail->next = nuevo;
        nuevo->prev = tail;
        tail = nuevo;
    }

    // 2. Mover a la foto siguiente en O(1)
    void fotoSiguiente() {
        if (actual != nullptr && actual->next != nullptr) {
            actual = actual->next;
            cout << "Foto actual: " << actual->archivo << endl;
        } else {
            cout << "[Aviso] Ya estás en la última foto de la galería." << endl;
        }
    }

    // 3. Mover a la foto anterior en O(1) gracias al puntero prev
    void fotoAnterior() {
        if (actual != nullptr && actual->prev != nullptr) {
            actual = actual->prev;
            cout << "Foto actual: " << actual->archivo << endl;
        } else {
            cout << "[Aviso] Ya estás en la primera foto de la galería." << endl;
        }
    }

    // 4. Eliminar la última foto agregada en O(1) usando tail
    void eliminarUltimaFoto() {
        if (tail == nullptr) {
            cout << "La galería está vacía, nada por eliminar." << endl;
            return;
        }

        NodoFoto* aEliminar = tail;

        // Caso: Si solo queda 1 foto en la galería
        if (head == tail) {
            head = tail = actual = nullptr;
        } else {
            // Si el visor estaba parado en la foto que se va a borrar
            if (actual == tail) {
                actual = tail->prev;
            }
            tail = tail->prev;
            tail->next = nullptr;
        }

        cout << "Foto eliminada: " << aEliminar->archivo << endl;
        delete aEliminar;
    }

    void mostrarGaleria() {
        NodoFoto* aux = head;
        cout << "Galería: ";
        while (aux != nullptr) {
            if (aux == actual) cout << "[" << aux->archivo << "*] ";
            else cout << aux->archivo << " ";
            aux = aux->next;
        }
        cout << endl;
    }
};

int main() {
    GaleriaFotos galeria;

    galeria.agregarFoto("playa.jpg");
    galeria.agregarFoto("montaña.jpg");
    galeria.agregarFoto("familia.jpg");
    galeria.mostrarGaleria(); // [playa.jpg*] montaña.jpg familia.jpg

    cout << "\n--- Navegando hacia adelante ---" << endl;
    galeria.fotoSiguiente(); // montaña.jpg
    galeria.fotoSiguiente(); // familia.jpg
    galeria.fotoSiguiente(); // [Aviso] Ya estás en la última foto

    cout << "\n--- Navegando hacia atrás (gracias a prev en O(1)) ---" << endl;
    galeria.fotoAnterior(); // montaña.jpg
    galeria.fotoAnterior(); // playa.jpg
    galeria.fotoAnterior(); // [Aviso] Ya estás en la primera foto

    cout << "\n--- Eliminando última foto cargada (familia.jpg) ---" << endl;
    galeria.eliminarUltimaFoto();
    galeria.mostrarGaleria();

    return 0;
}
