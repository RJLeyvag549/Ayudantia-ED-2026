#include <SFML/Graphics.hpp>
#include <iostream>

int main() {
    sf::RenderWindow ventana(sf::VideoMode(1000, 600),"Formas graficas de SFML");
    ventana.setFramerateLimit(60);

    sf::Font fuente;
    if (!fuente.loadFromFile("DejaVuSans-Bold.ttf")) {
        std::cerr << "No se pudo cargar el .ttf "
                  << "Ejecuta el programa desde la carpeta nov-04-SFML.\n";
        return 1;
    }

    sf::CircleShape circulo(45.0f);
    circulo.setFillColor(sf::Color::Yellow);
    circulo.setPosition(60.0f, 80.0f);

    sf::CircleShape ovalo(45.0f);
    ovalo.setScale(1.7f, 0.8f);
    ovalo.setFillColor(sf::Color::Cyan);
    ovalo.setPosition(290.0f, 90.0f);

    sf::RectangleShape cuadrado(sf::Vector2f(90.0f, 90.0f));
    cuadrado.setFillColor(sf::Color::Green);
    cuadrado.setPosition(570.0f, 80.0f);

    sf::RectangleShape rectangulo(sf::Vector2f(150.0f, 75.0f));
    rectangulo.setFillColor(sf::Color(255, 130, 40));
    rectangulo.setPosition(790.0f, 90.0f);

    sf::ConvexShape triangulo;
    triangulo.setPointCount(3);
    triangulo.setPoint(0, sf::Vector2f(55.0f, 0.0f));
    triangulo.setPoint(1, sf::Vector2f(110.0f, 95.0f));
    triangulo.setPoint(2, sf::Vector2f(0.0f, 95.0f));
    triangulo.setFillColor(sf::Color::Magenta);
    triangulo.setPosition(60.0f, 340.0f);

    sf::Texture textura;
    if (!textura.loadFromFile("sans.png")) {
        std::cerr << "No se pudo cargar sans.png. "
                  << "Ejecuta el programa desde la carpeta nov-04-SFML.\n";
        return 1;
    }

    sf::Sprite sprite(textura);
    sprite.setScale(0.12f, 0.12f);
    sprite.setPosition(360.0f, 320.0f);

    sf::Text ejemploTexto("Hola, SFML!", fuente, 25);
    ejemploTexto.setFillColor(sf::Color::Yellow);
    ejemploTexto.setPosition(600.0f, 360.0f);

    while (ventana.isOpen()) {
        sf::Event evento;
        while (ventana.pollEvent(evento)) {
            if (evento.type == sf::Event::Closed ||
                (evento.type == sf::Event::KeyPressed &&
                 evento.key.code == sf::Keyboard::Escape)) {
                ventana.close();
            }
        }

        ventana.clear(sf::Color(25, 28, 40));

        ventana.draw(circulo);
        ventana.draw(ovalo);
        ventana.draw(cuadrado);
        ventana.draw(rectangulo);
        ventana.draw(triangulo);
        ventana.draw(sprite);
        ventana.draw(ejemploTexto);
        
        ventana.display();
    }

    return 0;
}
