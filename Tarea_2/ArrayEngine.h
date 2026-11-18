#ifndef ARRAY_ENGINE_H
#define ARRAY_ENGINE_H

#include <vector>
#include "Particle.h"

using namespace std;

// ============================================================================
// MOTOR DE FÍSICAS BASADO EN ARREGLO DINÁMICO (std::vector)
// Estudiante A
// ============================================================================

class ArrayEngine {
public:
    vector<Particle> particles;

    ArrayEngine() {
    }

    // Cargar lote inicial de partículas
    void loadParticles(const vector<Particle>& initialParticles) {
        particles = initialParticles;
    }

    // 1. Integración de Euler Explícita O(N)
    // Recorrido secuencial continuo en memoria RAM (aprovecha la Caché L1/L2)
    void eulerIntegration(float dt, float gravity) {
        int n = particles.size();
        for (int i = 0; i < n; i++) {
            particles[i].y = particles[i].y + particles[i].vy * dt;
            particles[i].x = particles[i].x + particles[i].vx * dt;
            particles[i].vy = particles[i].vy + gravity * dt;
        }
    }

    // 2. Fragmentación de Partículas: la madre es reemplazada por la primera hija,
    // las hijas restantes se insertan al lado (penalización O(N) del vector por cada inserción).
    void particleSplitting(int maxMothersToSplit, int childrenPerMother) {
        int splitCount = 0;
        int idx = 0;
        while (idx < (int)particles.size() && splitCount < maxMothersToSplit) {
            for (int h = 0; h < childrenPerMother; h++) {
                Particle child(particles[idx].x + (h + 1) * 2.0,
                               particles[idx].y + (h + 1) * 2.0,
                               -particles[idx].vx * 0.8,
                               -particles[idx].vy * 0.8,
                               1.0);

                if (h == 0) {
                    particles[idx] = child;        // Primera hija: reemplaza a la madre
                } else {
                    particles.insert(particles.begin() + idx + h, child); // Resto: inserta al lado
                }
            }
            idx += childrenPerMother; // Salta la madre convertida y las hijas insertadas
            splitCount++;
        }
    }

    // 3. Filtro y Destrucción por Explosión AOE (Area of Effect)
    // Elimina las partículas dentro del radio usando erase()
    void explosionAOE(float expX, float expY, float radius) {
        float r2 = radius * radius;
        for (int i = 0; i < (int)particles.size(); ) {
            float dx = particles[i].x - expX;
            float dy = particles[i].y - expY;
            float distSq = dx * dx + dy * dy;

            if (distSq <= r2) {
                particles.erase(particles.begin() + i);
            } else {
                i++;
            }
        }
    }

    // 4. Detección de Colisiones por Fuerza Bruta O(N^2)
    // Comparación por pares i y j (j = i + 1) en memoria contigua
    void bruteForceCollisions() {
        int n = (int)particles.size();

        for (int i = 0; i < n; i++) {
            for (int j = i + 1; j < n; j++) {
                float dx = particles[j].x - particles[i].x;
                float dy = particles[j].y - particles[i].y;
                float distSq = dx * dx + dy * dy;

                float rSum = particles[i].radius + particles[j].radius;
                float rSumSq = rSum * rSum;

                if (distSq <= rSumSq) {
                    particles[i].vx = -particles[i].vx;
                    particles[i].vy = -particles[i].vy;
                    particles[j].vx = -particles[j].vx;
                    particles[j].vy = -particles[j].vy;
                }
            }
        }
    }
};

#endif
