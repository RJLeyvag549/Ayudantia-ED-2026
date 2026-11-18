#include <iostream>
#include <vector>

using namespace std;

// 1. Nodo para la lista doblemente enlazada de vecinos
class NodoVecino {
public:
    int id;               // Identificador del vertice con el que conecta
    NodoVecino* next;
    NodoVecino* prev;

    NodoVecino(int id) {
        this->id = id;
        next = nullptr;
        prev = nullptr;
    }
};

// 2. Vertice del grafo: contiene su id y administra su propia lista doble de vecinos
class Vertice {
public:
    int id;               // Identificador propio de este vertice (ej: 10, 20, 50...)
    NodoVecino* head;     // Cabecera (head) de su lista doble de vecinos

    Vertice(int id) {
        this->id = id;
        this->head = nullptr;
    }

    // Inserta un vecino al inicio de su lista doblemente enlazada
    void insertarVecino(int idVecino) {
        NodoVecino* nuevo = new NodoVecino(idVecino);
        nuevo->next = head;
        if (head != nullptr) {
            head->prev = nuevo;
        }
        head = nuevo;
    }

    // Desengancha y elimina un vecino de su lista doblemente enlazada
    void eliminarVecino(int idVecino) {
        // 1. Buscar el nodo del vecino
        NodoVecino* actual = head;
        while (actual != nullptr && actual->id != idVecino) {
            actual = actual->next;
        }

        if (actual == nullptr) return; // No existe ese vecino en la lista

        // 2. Desenganchar por la izquierda
        if (actual == head) {
            head = actual->next; // Era el primer vecino
        } else {
            actual->prev->next = actual->next; // El anterior salta a actual
        }

        // 3. Desenganchar por la derecha (si no es el ultimo)
        if (actual->next != nullptr) {
            actual->next->prev = actual->prev;
        }

        // 4. Liberar memoria
        delete actual;
    }
};

// 3. Grafo: administra el arreglo de vertices y coordina las conexiones
class Grafo {
public:
    vector<Vertice> vertices; // Arreglo auxiliar de vertices

    // Busca la posicion (indice) de un vertice por su id; retorna -1 si no existe
    int buscarIndiceVertice(int id) {
        for (int i = 0; i < (int)vertices.size(); i++) {
            if (vertices[i].id == id) {
                return i;
            }
        }
        return -1;
    }

    // Inserta un nuevo vertice en el arreglo
    void insertarVertice(int id) {
        if (buscarIndiceVertice(id) != -1) {
            cout << "El vertice " << id << " ya existe en el grafo." << endl;
            return;
        }
        vertices.push_back(Vertice(id));
    }

    // Conecta dos vertices con una arista no dirigida
    void insertarArista(int origen, int destino) {
        int u = buscarIndiceVertice(origen);
        int v = buscarIndiceVertice(destino);

        if (u == -1 || v == -1) {
            cout << "Error: uno o ambos vertices no existen en el grafo." << endl;
            return;
        }

        vertices[u].insertarVecino(destino);
        if (origen != destino) {
            vertices[v].insertarVecino(origen);
        }
    }

    // Elimina la arista entre dos vertices
    void eliminarArista(int origen, int destino) {
        int u = buscarIndiceVertice(origen);
        int v = buscarIndiceVertice(destino);

        if (u == -1 || v == -1) return;

        vertices[u].eliminarVecino(destino);
        if (origen != destino) {
            vertices[v].eliminarVecino(origen);
        }
    }

    // Muestra toda la informacion del grafo
    void mostrar() {
        for (int i = 0; i < (int)vertices.size(); i++) {
            cout << "Vertice [" << vertices[i].id << "]: ";
            NodoVecino* actual = vertices[i].head;
            if (actual == nullptr) {
                cout << "(sin aristas)";
            }
            while (actual != nullptr) {
                cout << "-> [" << actual->id << "] ";
                actual = actual->next;
            }
            cout << endl;
        }
    }
};

int main() {
    Grafo grafo;

    // 1. Insertamos vertices con id propio
    grafo.insertarVertice(10);
    grafo.insertarVertice(20);
    grafo.insertarVertice(30);
    grafo.insertarVertice(40);
    grafo.insertarVertice(99); // Vertice aislado (sin aristas)

    // 2. Insertamos aristas no dirigidas entre vertices existentes
    grafo.insertarArista(10, 20);
    grafo.insertarArista(10, 30);
    grafo.insertarArista(20, 40);
    grafo.insertarArista(30, 40);

    cout << "--- Estado Inicial del Grafo ---" << endl;
    grafo.mostrar();

    // 3. Eliminar arista entre 10 y 30
    cout << "\n--- Eliminando arista entre 10 y 30 ---" << endl;
    grafo.eliminarArista(10, 30);
    grafo.mostrar();

    return 0;
}
