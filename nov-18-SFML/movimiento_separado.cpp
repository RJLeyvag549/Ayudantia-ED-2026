#include <SFML/Graphics.hpp>
#include <algorithm>
#include <cmath>

void procesarEntrada(sf::RenderWindow& ventana, sf::Vector2f& direccion) {
    sf::Event evento;
    while (ventana.pollEvent(evento)) {
        if (evento.type == sf::Event::Closed) {
            ventana.close();
        }
    }

    direccion = sf::Vector2f(0.0f, 0.0f);
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left))  direccion.x -= 1.0f;
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right)) direccion.x += 1.0f;
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Up))    direccion.y -= 1.0f;
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Down))  direccion.y += 1.0f;

    // sqrt calcula la longitud del vector para que la diagonal no sea más rápida.
    float longitud = std::sqrt(direccion.x * direccion.x +
                               direccion.y * direccion.y);
    if (longitud > 0.0f) {
        direccion.x /= longitud;
        direccion.y /= longitud;
    }
}

void actualizar(sf::CircleShape& jugador, sf::Vector2f direccion,
                float deltaTiempo, sf::Vector2u tamVentana) {
    const float velocidad = 320.0f;
    jugador.move(direccion.x * velocidad * deltaTiempo,
                 direccion.y * velocidad * deltaTiempo);

    sf::Vector2f posicion = jugador.getPosition();
    float diametro = jugador.getRadius() * 2.0f;
    float maxX = static_cast<float>(tamVentana.x) - diametro;
    float maxY = static_cast<float>(tamVentana.y) - diametro;

    // min y max mantienen al jugador dentro de los límites de la ventana.
    posicion.x = std::max(0.0f, std::min(posicion.x, maxX));
    posicion.y = std::max(0.0f, std::min(posicion.y, maxY));
    jugador.setPosition(posicion);
}

void dibujar(sf::RenderWindow& ventana, const sf::CircleShape& jugador) {
    ventana.clear(sf::Color::Black);
    ventana.draw(jugador);
    ventana.display();
}

int main() {
    sf::RenderWindow ventana(sf::VideoMode(800, 600), "Movimiento por etapas");
    ventana.setFramerateLimit(60);

    sf::CircleShape jugador(20.0f);
    jugador.setFillColor(sf::Color::Yellow);
    jugador.setPosition(390.0f, 290.0f);

    sf::Clock reloj;
    while (ventana.isOpen()) {
        float deltaTiempo = reloj.restart().asSeconds();
        sf::Vector2f direccion;

        procesarEntrada(ventana, direccion);
        if (!ventana.isOpen()) break;

        actualizar(jugador, direccion, deltaTiempo, ventana.getSize());
        dibujar(ventana, jugador);
    }

    return 0;
}
