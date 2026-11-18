#ifndef LIST_ENGINE_H
#define LIST_ENGINE_H

#include <list>
#include <vector>
#include "Particle.h"

using namespace std;

// ============================================================================
// MOTOR DE FÍSICAS BASADO EN LISTA DOBLEMENTE ENLAZADA (std::list)
// Estudiante B
// ============================================================================

class ListEngine {
public:
    list<Particle> particles;

    ListEngine() {
    }

    // Cargar lote inicial de partículas
    void loadParticles(const vector<Particle>& initialParticles) {
        particles.clear();
        for (const Particle& p : initialParticles) {
            particles.push_back(p);
        }
    }

    // 1. Integración de Euler Explícita O(N)
    // Recorrido por punteros (sufre penalización de 'cache misses' al estar disperso en RAM)
    void eulerIntegration(float dt, float gravity) {
        for (Particle& p : particles) {
            p.y = p.y + p.vy * dt;
            p.x = p.x + p.vx * dt;
            p.vy = p.vy + gravity * dt;
        }
    }

    // 2. Fragmentación de Partículas: la madre es reemplazada por la primera hija,
    // las hijas restantes se insertan al lado en O(1) reconectando punteros.
    //
    // 'actual' equivale a tu variable 'actual = head' de listas nativas.
    // 'actual++' equivale a 'actual = actual->next'.
    void particleSplitting(int maxMothersToSplit, int childrenPerMother) {
        int splitCount = 0;
        auto actual = particles.begin(); // actual apunta a la primera madre (= head)

        while (actual != particles.end() && splitCount < maxMothersToSplit) {
            // FOR: genera todas las hijas de ESTA madre
            for (int h = 0; h < childrenPerMother; h++) {
                Particle child(actual->x + (h + 1) * 2.0,
                               actual->y + (h + 1) * 2.0,
                               -actual->vx * 0.8,
                               -actual->vy * 0.8,
                               1.0);

                if (h == 0) {
                    *actual = child;                          // Primera hija: reemplaza a la madre
                } else {
                    particles.insert(next(actual), child);   // Resto: inserta al lado en O(1)
                }
            }
            actual++;    // Pasa a la siguiente madre (= actual = actual->next)
            splitCount++;
        }
    }

    // 3. Filtro y Destrucción por Explosión AOE (Area of Effect)
    // std::list desengancha nodos en O(1) con erase() sin reorganizar memoria contigua.
    void explosionAOE(float expX, float expY, float radius) {
        float r2 = radius * radius;
        auto actual = particles.begin();

        while (actual != particles.end()) {
            float dx = actual->x - expX;
            float dy = actual->y - expY;
            float distSq = dx * dx + dy * dy;

            if (distSq <= r2) {
                actual = particles.erase(actual); // Desenganche en O(1)
            } else {
                actual++;
            }
        }
    }

    // 4. Detección de Colisiones por Fuerza Bruta O(N^2)
    // Doble recorrido por pares con iteradores
    void bruteForceCollisions() {
        for (auto a = particles.begin(); a != particles.end(); a++) {
            for (auto b = next(a); b != particles.end(); b++) {
                float dx = b->x - a->x;
                float dy = b->y - a->y;
                float distSq = dx * dx + dy * dy;

                float rSum = a->radius + b->radius;
                float rSumSq = rSum * rSum;

                if (distSq <= rSumSq) {
                    a->vx = -a->vx;
                    a->vy = -a->vy;
                    b->vx = -b->vx;
                    b->vy = -b->vy;
                }
            }
        }
    }
};

#endif
