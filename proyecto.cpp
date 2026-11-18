#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include <box2d/box2d.h>
#include <iostream>
#include <fstream>
#include <vector>
#include <cmath>
#include <memory>

// Usamos espacios de nombres para std y sf
using namespace std;
using namespace sf;

// ==========================================
// 1. ESTRUCTURAS Y MATEMÁTICA
// ==========================================
struct Vector2D {
    float x;
    float y;

    float magnitud() const {
        return sqrt(x * x + y * y);
    }
};

struct GameState {
    int totalPelotas = 0;
    int colisionesDetectadas = 0;

    // Serialización simple a archivo de texto usando fstream
    void guardar(const string& filename) const {
        ofstream file(filename);
        if (file.is_open()) {
            file << totalPelotas << "\n";
            file << colisionesDetectadas << "\n";
            file.close();
            cout << "[Guardado] Estado guardado en " << filename << endl;
        }
    }

    // Deserialización
    void cargar(const string& filename) {
        ifstream file(filename);
        if (file.is_open()) {
            file >> totalPelotas;
            file >> colisionesDetectadas;
            file.close();
            cout << "[Cargado] Estado cargado desde " << filename << endl;
        }
    }
};

// Escala de conversión Box2D (metros) <-> SFML (píxeles)
const float SCALE = 30.0f;

int main() {
    // ------------------------------------------
    // 2. VENTANA Y GRÁFICOS CON SFML
    // ------------------------------------------
    RenderWindow window(VideoMode(800, 600), "SFML + Box2D + Audio + Serialización");
    window.setFramerateLimit(60);

    // Fuente y Texto para la interfaz
    Font font;
    Text text;
    if (font.loadFromFile("/usr/share/fonts/truetype/dejavu/DejaVuSans.ttf")) {
        text.setFont(font);
        text.setCharacterSize(18);
        text.setFillColor(Color::White);
        text.setPosition(10.f, 10.f);
    }

    // ------------------------------------------
    // 3. AUDIO CON SFML
    // ------------------------------------------
    unique_ptr<SoundBuffer> buffer;
    unique_ptr<Sound> bounceSound;
    bool audioDisponible = false;

    try {
        vector<Int16> samples;
        const unsigned sampleRate = 44100;
        const float duration = 0.1f; // 100 ms
        for (unsigned i = 0; i < sampleRate * duration; ++i) {
            float t = i / static_cast<float>(sampleRate);
            samples.push_back(static_cast<Int16>(10000 * sin(2 * 3.14159f * 440 * t)));
        }

        buffer = make_unique<SoundBuffer>();
        if (buffer->loadFromSamples(samples.data(), samples.size(), 1, sampleRate)) {
            bounceSound = make_unique<Sound>(*buffer);
            audioDisponible = true;
        }
    } catch (...) {
        audioDisponible = false;
        cout << "[Info] No se pudo inicializar OpenAL / Tarjeta de audio. Modo silencioso activo." << endl;
    }

    // ------------------------------------------
    // 4. FÍSICAS CON BOX2D
    // ------------------------------------------
    b2Vec2 gravity(0.0f, 9.8f);
    b2World world(gravity);

    // Crear Suelo Estático en Box2D
    b2BodyDef groundBodyDef;
    groundBodyDef.position.Set(400.0f / SCALE, 550.0f / SCALE);
    b2Body* groundBody = world.CreateBody(&groundBodyDef);

    b2PolygonShape groundBox;
    groundBox.SetAsBox(400.0f / SCALE, 10.0f / SCALE);
    groundBody->CreateFixture(&groundBox, 0.0f);

    // Forma visual del suelo en SFML
    RectangleShape groundShape(Vector2f(800.0f, 20.0f));
    groundShape.setFillColor(Color::Green);
    groundShape.setOrigin(400.0f, 10.0f);
    groundShape.setPosition(400.0f, 550.0f);

    // Estructura para almacenar cuerpos de físicas y sus figuras SFML
    struct Pelota {
        b2Body* body;
        CircleShape shape;
    };
    vector<Pelota> pelotas;

    // Estado del juego para serialización
    GameState estado;
    estado.cargar("estado_juego.txt"); // Intentar cargar previo si existe

    // Lambda/Función para spawnear pelota
    auto crearPelota = [&](float x, float y) {
        b2BodyDef bodyDef;
        bodyDef.type = b2_dynamicBody;
        bodyDef.position.Set(x / SCALE, y / SCALE);
        b2Body* body = world.CreateBody(&bodyDef);

        b2CircleShape dynamicCircle;
        dynamicCircle.m_radius = 15.0f / SCALE;

        b2FixtureDef fixtureDef;
        fixtureDef.shape = &dynamicCircle;
        fixtureDef.density = 1.0f;
        fixtureDef.friction = 0.3f;
        fixtureDef.restitution = 0.7f; // Rebote
        body->CreateFixture(&fixtureDef);

        CircleShape shape(15.0f);
        shape.setFillColor(Color::Cyan);
        shape.setOrigin(15.0f, 15.0f);

        pelotas.push_back({body, shape});
        estado.totalPelotas++;
    };

    // ------------------------------------------
    // 5. BUCLE PRINCIPAL
    // ------------------------------------------
    Clock clock;
    while (window.isOpen()) {
        Event event;
        while (window.pollEvent(event)) {
            if (event.type == Event::Closed)
                window.close();

            // Clic izquierdo -> Spawnear pelota
            if (event.type == Event::MouseButtonPressed && event.mouseButton.button == Mouse::Left) {
                crearPelota(static_cast<float>(event.mouseButton.x), static_cast<float>(event.mouseButton.y));
                if (audioDisponible && bounceSound && bounceSound->getStatus() != Sound::Playing) {
                    bounceSound->play();
                }
            }

            // Tecla G -> Guardar estado (Serialización)
            if (event.type == Event::KeyPressed && event.key.code == Keyboard::G) {
                estado.guardar("estado_juego.txt");
            }

            // Tecla C -> Cargar estado (Deserialización)
            if (event.type == Event::KeyPressed && event.key.code == Keyboard::C) {
                estado.cargar("estado_juego.txt");
            }
        }

        // Dar un paso en la simulación física de Box2D
        float timeStep = 1.0f / 60.0f;
        int32 velocityIterations = 6;
        int32 positionIterations = 2;
        world.Step(timeStep, velocityIterations, positionIterations);

        // Actualizar posiciones de SFML desde Box2D
        for (auto& p : pelotas) {
            b2Vec2 pos = p.body->GetPosition();
            float angle = p.body->GetAngle();
            p.shape.setPosition(pos.x * SCALE, pos.y * SCALE);
            p.shape.setRotation(angle * 180.0f / 3.14159f);

            // Cálculo matemático usando nuestra estructura Vector2D
            b2Vec2 vel = p.body->GetLinearVelocity();
            Vector2D vCustom{vel.x, vel.y};
            (void)vCustom.magnitud();
        }

        // Renderizado
        window.clear(Color(30, 30, 30));

        // Dibujar suelo
        window.draw(groundShape);

        // Dibujar pelotas
        for (const auto& p : pelotas) {
            window.draw(p.shape);
        }

        // Dibujar UI Texto
        if (font.getInfo().family != "") {
            text.setString("Haz Clic para crear pelotas\n'G': Guardar Estado | 'C': Cargar Estado\nPelotas Totales: " + to_string(estado.totalPelotas));
            window.draw(text);
        }

        window.display();
    }

    return 0;
}
