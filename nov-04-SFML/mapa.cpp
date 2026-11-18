#include <SFML/Graphics.hpp>

const int COLUMNAS = 28;
const int FILAS = 31;
const int TAM = 18;

// # = muro, . = punto, o = energizador, = = puerta, espacio = vacio.
const char* MAPA[FILAS] = {
    "############################",
    "#............##............#",
    "#.####.#####.##.#####.####.#",
    "#o####.#####.##.#####.####o#",
    "#.####.#####.##.#####.####.#",
    "#..........................#",
    "#.####.##.########.##.####.#",
    "#.####.##.########.##.####.#",
    "#......##....##....##......#",
    "######.##### ## #####.######",
    "     #.##### ## #####.#     ",
    "     #.##          ##.#     ",
    "     #.## ###==### ##.#     ",
    "######.## #      # ##.######",
    "      .   #      #   .      ",
    "######.## #      # ##.######",
    "     #.## ######## ##.#     ",
    "     #.##          ##.#     ",
    "     #.## ######## ##.#     ",
    "######.## ######## ##.######",
    "#............##............#",
    "#.####.#####.##.#####.####.#",
    "#.####.#####.##.#####.####.#",
    "#o..##.......  .......##..o#",
    "###.##.##.########.##.##.###",
    "###.##.##.########.##.##.###",
    "#......##....##....##......#",
    "#.##########.##.##########.#",
    "#.##########.##.##########.#",
    "#..........................#",
    "############################"
};

int main() {
    sf::RenderWindow ventana(
        sf::VideoMode(COLUMNAS * TAM, FILAS * TAM),
        "Mapa de Pac-Man"
    );
    ventana.setFramerateLimit(60);

    sf::RectangleShape muro(sf::Vector2f(TAM - 2.0f, TAM - 2.0f));
    muro.setFillColor(sf::Color::Blue);

    sf::CircleShape punto(2.0f);
    punto.setFillColor(sf::Color(255, 184, 151));

    sf::CircleShape energizador(6.0f);
    energizador.setFillColor(sf::Color(255, 184, 151));

    sf::RectangleShape puerta(sf::Vector2f(TAM - 2.0f, 4.0f));
    puerta.setFillColor(sf::Color(255, 184, 255));

    while (ventana.isOpen()) {
        sf::Event evento;
        while (ventana.pollEvent(evento)) {
            if (evento.type == sf::Event::Closed) {
                ventana.close();
            }
        }

        ventana.clear(sf::Color::Black);

        for (int fila = 0; fila < FILAS; ++fila) {
            for (int columna = 0; columna < COLUMNAS; ++columna) {
                float x = static_cast<float>(columna * TAM);
                float y = static_cast<float>(fila * TAM);
                char celda = MAPA[fila][columna];

                if (celda == '#') {
                    muro.setPosition(x + 1.0f, y + 1.0f);
                    ventana.draw(muro);
                } else if (celda == '.') {
                    punto.setPosition(x + TAM / 2.0f - 2.0f,
                                      y + TAM / 2.0f - 2.0f);
                    ventana.draw(punto);
                } else if (celda == 'o') {
                    energizador.setPosition(x + TAM / 2.0f - 6.0f,
                                            y + TAM / 2.0f - 6.0f);
                    ventana.draw(energizador);
                } else if (celda == '=') {
                    puerta.setPosition(x + 1.0f, y + TAM / 2.0f);
                    ventana.draw(puerta);
                }
            }
        }

        ventana.display();
    }

    return 0;
}
