#include <iostream>
#include <iomanip>
#include <chrono>
#include <vector>
#include <cstdlib>
#include "Particle.h"
#include "ArrayEngine.h"
#include "ListEngine.h"

using namespace std;

// Genera un vector con N partículas usando una semilla fija para equidad total
vector<Particle> generarParticulas(int n) {
    srand(42);
    vector<Particle> lista;
    lista.reserve(n);

    for (int i = 0; i < n; i++) {
        float x = rand() % 1000;
        float y = rand() % 1000;
        float vx = (rand() % 200 - 100) / 10.0; // [-10, 10]
        float vy = (rand() % 200 - 100) / 10.0;
        float r = 2.0;
        lista.push_back(Particle(x, y, vx, vy, r));
    }
    return lista;
}

void evaluarRendimiento(int N) {
    cout << "\nGenerando lote de " << N << " particulas con semilla identica..." << endl;
    vector<Particle> datosBase = generarParticulas(N);

    ArrayEngine arrayEngine;
    ListEngine listEngine;

    // ========================================================================
    // PARÁMETROS FÍSICOS DE PRUEBA (CONFIGURADOS EN EL CÓDIGO)
    // ========================================================================
    float dt = 0.016;                    // Paso temporal (60 FPS = ~16ms)
    float gravedad = 9.8;                // Constante de aceleración gravitatoria (m/s²)
    int madresParaDividir = N / 50;      // 2% del total de partículas
    int hijasPorMadre = 2;               // Nuevas partículas que nacen a su lado
    float expX = 500.0, expY = 500.0;    // Centro de detonación AOE
    float expRadius = 250.0;             // Radio de la onda de choque

    // ========================================================================
    // 1. Integración de Euler O(N)
    // ========================================================================
    arrayEngine.loadParticles(datosBase);
    listEngine.loadParticles(datosBase);

    // Medición Arreglo
    auto inicio = std::chrono::high_resolution_clock::now();
    arrayEngine.eulerIntegration(dt, gravedad);
    auto fin = std::chrono::high_resolution_clock::now();
    chrono::duration<double, milli> duracionDecimal = fin - inicio;
    double tEulerArray = duracionDecimal.count();

    // Medición Lista
    inicio = std::chrono::high_resolution_clock::now();
    listEngine.eulerIntegration(dt, gravedad);
    fin = std::chrono::high_resolution_clock::now();
    duracionDecimal = fin - inicio;
    double tEulerList = duracionDecimal.count();

    // ========================================================================
    // 2. Colisiones Fuerza Bruta O(N^2)
    // ========================================================================
    inicio = std::chrono::high_resolution_clock::now();
    arrayEngine.bruteForceCollisions();
    fin = std::chrono::high_resolution_clock::now();
    duracionDecimal = fin - inicio;
    double tColArray = duracionDecimal.count();

    inicio = std::chrono::high_resolution_clock::now();
    listEngine.bruteForceCollisions();
    fin = std::chrono::high_resolution_clock::now();
    duracionDecimal = fin - inicio;
    double tColList = duracionDecimal.count();

    // ========================================================================
    // 3. Fragmentación de Partículas (Splitting en el medio)
    // ========================================================================
    inicio = std::chrono::high_resolution_clock::now();
    arrayEngine.particleSplitting(madresParaDividir, hijasPorMadre);
    fin = std::chrono::high_resolution_clock::now();
    duracionDecimal = fin - inicio;
    double tSplitArray = duracionDecimal.count();

    inicio = std::chrono::high_resolution_clock::now();
    listEngine.particleSplitting(madresParaDividir, hijasPorMadre);
    fin = std::chrono::high_resolution_clock::now();
    duracionDecimal = fin - inicio;
    double tSplitList = duracionDecimal.count();

    // ========================================================================
    // 4. Explosión AOE (Filtrado y Destrucción en Área)
    // ========================================================================
    inicio = std::chrono::high_resolution_clock::now();
    arrayEngine.explosionAOE(expX, expY, expRadius);
    fin = std::chrono::high_resolution_clock::now();
    duracionDecimal = fin - inicio;
    double tAoeArray = duracionDecimal.count();

    inicio = std::chrono::high_resolution_clock::now();
    listEngine.explosionAOE(expX, expY, expRadius);
    fin = std::chrono::high_resolution_clock::now();
    duracionDecimal = fin - inicio;
    double tAoeList = duracionDecimal.count();

    // ========================================================================
    // Salida Formateada con <iomanip>
    // ========================================================================
    cout << "\n";
    cout << "=========================================================================" << endl;
    cout << "          BENCHMARK MOTOR DE FISICAS CLI (N = " << N << " Particulas)          " << endl;
    cout << "=========================================================================" << endl;
    cout << left << setw(34) << "Algoritmo / Escenario"
         << setw(20) << "Arreglo Dinamico"
         << setw(20) << "Lista Doble Enlazada" << endl;
    cout << "-------------------------------------------------------------------------" << endl;

    cout << fixed << setprecision(2);

    cout << left << setw(34) << "1. Integracion de Euler (O(N))"
         << setw(9) << tEulerArray << setw(11) << " ms"
         << setw(9) << tEulerList << " ms" << endl;

    cout << left << setw(34) << "2. Colisiones Fuerza Bruta"
         << setw(9) << tColArray << setw(11) << " ms"
         << setw(9) << tColList << " ms" << endl;

    cout << left << setw(34) << "3. Fragmentacion (Splitting)"
         << setw(9) << tSplitArray << setw(11) << " ms"
         << setw(9) << tSplitList << " ms" << endl;

    cout << left << setw(34) << "4. Explosion AOE"
         << setw(9) << tAoeArray << setw(11) << " ms"
         << setw(9) << tAoeList << " ms" << endl;

    cout << "=========================================================================" << endl;
}

int main() {
    cout << "==============================================" << endl;
    cout << "   BENCHMARK MOTOR DE FISICAS: VECTOR VS LISTA" << endl;
    cout << "==============================================" << endl;

    cout << "\n>>> [1/3] MUESTRA 1: PRUEBA RAPIDA" << endl;
    evaluarRendimiento(10000);

    cout << "\n>>> [2/3] MUESTRA 2: PRUEBA ESTANDAR" << endl;
    evaluarRendimiento(50000);

    cout << "\n>>> [3/3] MUESTRA 3: PRUEBA PESADA" << endl;
    evaluarRendimiento(100000);

    cout << "\nPruebas finalizadas con exito.\n" << endl;
    return 0;
}
