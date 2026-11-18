#include <SFML/Graphics.hpp>

using namespace sf;

//https://www.youtube.com/watch?v=dbJxbAuKwPE

int main() {
    RenderWindow ventana(VideoMode(800, 600), "Movimiento con flechas");
    ventana.setFramerateLimit(60);

    CircleShape jugador(20.0f);
    jugador.setFillColor(Color::Yellow);
    jugador.setPosition(390.0f, 290.0f);

    Clock reloj;
    const float velocidad = 320.0f;

    while (ventana.isOpen()) {
        Event evento;
        while (ventana.pollEvent(evento)) {
            if (evento.type == Event::Closed) {
                ventana.close();
            }
        }

        float deltaTiempo = reloj.restart().asSeconds();
        Vector2f desplazamiento(0.0f, 0.0f);
        if (Keyboard::isKeyPressed(Keyboard::Left)) {
            desplazamiento.x -= velocidad * deltaTiempo;
        }
        if (Keyboard::isKeyPressed(Keyboard::Right)) {
            desplazamiento.x += velocidad * deltaTiempo;
        }
        if (Keyboard::isKeyPressed(Keyboard::Up)) {
            desplazamiento.y -= velocidad * deltaTiempo;
        }
        if (Keyboard::isKeyPressed(Keyboard::Down)) {
            desplazamiento.y += velocidad * deltaTiempo;
        }
        jugador.move(desplazamiento);

        Vector2f posicion = jugador.getPosition();
        if (posicion.x < 0.0f) {
            jugador.setPosition(0.0f, posicion.y);
        }
        if (posicion.y < 0.0f) {
            jugador.setPosition(jugador.getPosition().x, 0.0f);
        }
        if (posicion.x + jugador.getRadius() * 2.0f > ventana.getSize().x) {
            jugador.setPosition(ventana.getSize().x - jugador.getRadius() * 2.0f,
            jugador.getPosition().y);
        }
        if (posicion.y + jugador.getRadius() * 2.0f > ventana.getSize().y) {
            jugador.setPosition(jugador.getPosition().x,
            ventana.getSize().y - jugador.getRadius() * 2.0f);
        }

        ventana.clear(Color::Black);
        ventana.draw(jugador);
        ventana.display();
    }

    return 0;
}
