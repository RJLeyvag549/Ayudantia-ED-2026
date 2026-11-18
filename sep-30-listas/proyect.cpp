// g++ main.cpp -o main -lsfml-graphics -lsfml-window -lsfml-system
#include <SFML/Graphics.hpp>
#include <cstdlib>
#include <ctime>

using namespace sf;

const int TAM = 25;
const int COLUMNAS = 30; // 750 / 25
const int FILAS = 20;    // 500 / 25

// ========================================================
// 1. LISTA DOBLE: CUERPO DEL GUSANO
// ========================================================
class NodoDoble {
    public:
        int x;
        int y;
        NodoDoble* next;
        NodoDoble* prev;

        NodoDoble(int x, int y){
            this->x = x;
            this->y = y;
            next = nullptr;
            prev = nullptr;
        }
    
};

class ListaDoble {
    public:
        NodoDoble* head;

        ListaDoble(){
            head = nullptr;
        }
        
        void insertarCabeza(int x, int y){
            NodoDoble* nuevo = new NodoDoble(x,y);
            if(head == nullptr){
                head = nuevo;
                return;
            }
            nuevo->next = head;
            head->prev = nuevo;
            head = nuevo;
        }

        void eliminarCola(){
            if(head==nullptr){
                return;
            }
            if(head->next==nullptr){
                delete head;
                head = nullptr;
                return;
            }
            NodoDoble* actual = head;
            while(actual->next!=nullptr){
                actual = actual->next;
            }
            actual->prev->next = nullptr;
            delete actual;
        }

        bool hayColision(int x, int y) {
            NodoDoble* actual = head;
            while (actual != nullptr) {
                if (actual->x == x && actual->y == y) return true;
                actual = actual->next;
            }
            return false;
        }
};

// ========================================================
// 2. LISTA CIRCULAR: ROTACIÓN DE COLORES DE FRUTA
// ========================================================
class NodoCircular {
    public:
        Color color;
        NodoCircular* next;

        NodoCircular(Color c) {
            color = c;
            next = nullptr;
        }
};

class ListaCircular {
    public:
        NodoCircular* actual;

        ListaCircular() {
            actual = nullptr;
        }

        void agregar(Color c) {
            NodoCircular* nuevo = new NodoCircular(c);
            if (!actual) {
                actual = nuevo;
                actual->next = actual; // Apunta a sí mismo (círculo)
                return;
            }
            nuevo->next = actual->next;
            actual->next = nuevo;
        }

        void avanzar() {
            if (actual) actual = actual->next;
        }
};

// ========================================================
// MAIN
// ========================================================
int main() {
    srand(time(nullptr));
    RenderWindow window(VideoMode(COLUMNAS * TAM, FILAS * TAM), "Snake Simple");
    VideoMode desktop = VideoMode::getDesktopMode();
    Vector2u size = window.getSize();
    window.setPosition(Vector2i(
        (desktop.width - static_cast<int>(size.x)) / 2,
        (desktop.height - static_cast<int>(size.y)) / 2
    ));

    window.setVerticalSyncEnabled(false);

    // 1. Inicializar Gusano (Lista Doble)
    ListaDoble gusano;
    gusano.insertarCabeza(5, 5);
    gusano.insertarCabeza(6, 5);
    gusano.insertarCabeza(7, 5);

    // 2. Inicializar Frutas (Lista Circular)
    ListaCircular frutas;
    frutas.agregar(Color::Red);
    frutas.agregar(Color::Yellow);
    frutas.agregar(Color::Magenta);
    frutas.agregar(Color::Cyan);

    int dirX = 1, dirY = 0;
    int comidaX = 15, comidaY = 10;
    Clock reloj;

    RectangleShape celda(Vector2f(TAM - 2, TAM - 2));

    while (window.isOpen()) {
        Event event;
        while (window.pollEvent(event)) {
            if (event.type == Event::Closed)
                window.close();

            if (event.type == Event::KeyPressed) {
                if ((event.key.code == Keyboard::Up    || event.key.code == Keyboard::W) && dirY == 0) { dirX = 0; dirY = -1; }
                if ((event.key.code == Keyboard::Down  || event.key.code == Keyboard::S) && dirY == 0) { dirX = 0; dirY = 1;  }
                if ((event.key.code == Keyboard::Left  || event.key.code == Keyboard::A) && dirX == 0) { dirX = -1; dirY = 0; }
                if ((event.key.code == Keyboard::Right || event.key.code == Keyboard::D) && dirX == 0) { dirX = 1; dirY = 0;  }
            }
        }

        // Movimiento a paso constante (cada 0.12 segundos)
        if (reloj.getElapsedTime().asSeconds() >= 0.12f) {
            reloj.restart();

            int nuevoX = gusano.head->x + dirX;
            int nuevoY = gusano.head->y + dirY;

            // Colisiones (paredes o propio cuerpo)
            if (nuevoX < 0 || nuevoX >= COLUMNAS || nuevoY < 0 || nuevoY >= FILAS || gusano.hayColision(nuevoX, nuevoY)) {
                window.close(); // Fin del juego
            } else {
                gusano.insertarCabeza(nuevoX, nuevoY);

                if (nuevoX == comidaX && nuevoY == comidaY) {
                    frutas.avanzar(); // Cambia al siguiente color circularmente
                    do {
                        comidaX = rand() % COLUMNAS;
                        comidaY = rand() % FILAS;
                    } while (gusano.hayColision(comidaX, comidaY));
                } else {
                    gusano.eliminarCola(); // Avanzar sin crecer
                }
            }
        }

        // Dibujar
        window.clear(Color(25, 25, 30));

        // Dibujar Comida
        celda.setPosition(comidaX * TAM, comidaY * TAM);
        celda.setFillColor(frutas.actual->color);
        window.draw(celda);

        // Dibujar Gusano
        NodoDoble* act = gusano.head;
        while (act != nullptr) {
            celda.setPosition(act->x * TAM, act->y * TAM);
            celda.setFillColor(act == gusano.head ? Color(80, 240, 80) : Color(40, 160, 40));
            window.draw(celda);
            act = act->next;
        }

        window.display();
    }

    return 0;
}
