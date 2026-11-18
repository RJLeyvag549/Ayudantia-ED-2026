#include <SFML/Graphics.hpp>

int main() {
    sf::RenderWindow ventana(sf::VideoMode(800, 600), "Mi ventana SFML");
    ventana.setFramerateLimit(60);

    while (ventana.isOpen()) {
        sf::Event evento;
        while (ventana.pollEvent(evento)) {
            if (evento.type == sf::Event::Closed) ventana.close();
        }

        ventana.clear(sf::Color::Black);

        // TODO: dibujar aqui las figuras y el contenido de la escena.

        ventana.display();
    }
}
