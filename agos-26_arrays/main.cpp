#include <iostream>
#include <cstdlib>
#include <ctime>
#include <vector>
#include <chrono>

using namespace std;

// Funcion para generar valores aleatorios en un vector
// Se pasa por referencia (&) para modificar el vector original
void generarArregloAleatorio(vector<int>& array) {
    for (int i = 0; i < array.size(); i++) {
        array[i] = rand() % 100;
    }
}

// Funcion para imprimir un vector
// Se usa constante y referencia (&) para evitar copias innecesarias en memoria
void imprimirArreglo(const vector<int>& array) {
    cout << "Arreglo: ";
    for (int i = 0; i < array.size(); i++) {
        cout << "[" << array[i] << "]";
    }
    cout << endl;
}

// Funcion para generar valores aleatorios en una matriz dinamica
void generarMatrizAleatoria(vector<vector<int>>& matriz, int n, int m) {
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < m; j++) {
            matriz[i][j] = rand() % 10;
        }
    }
}

// Funcion para imprimir una matriz dinamica
void imprimirMatriz(const vector<vector<int>>& matriz) {
    for (int i = 0; i < matriz.size(); i++) {
        for (int j = 0; j < matriz[i].size(); j++) {
            cout << "[" << matriz[i][j] << "]";
        }
        cout << endl;
    }
}

int main() {
    // Inicializacion de la semilla aleatoria
    srand(time(NULL));

    // =================================================================
    // PARTE 1: MATRIZ ESTATICA / ARREGLO BIDIMENSIONAL
    // =================================================================
    {
        int n, m;
        cout << "Ingrese numero de filas n: ";
        cin >> n;
        cout << "Ingrese numero de columnas m: ";
        cin >> m;

        int matriz[n][m];
        for (int i = 0; i < n; i++) {
            for (int j = 0; j < m; j++) {
                matriz[i][j] = rand() % 10;
            }
        }

        cout << "Contenido de la matriz estatica:" << endl;
        for (int i = 0; i < n; i++) {
            for (int j = 0; j < m; j++) {
                cout << "[" << matriz[i][j] << "]";
            }
            cout << endl;
        }
    }

    // =================================================================
    // PARTE 2: VECTORES DINAMICOS (Limite del hardware)
    // =================================================================
    {
        int n;
        cout << "Ingrese tamano del vector: ";
        cin >> n;

        vector<int> array(n);
        generarArregloAleatorio(array);
        imprimirArreglo(array);

        // Agregar elementos al final del vector
        cout << "\n-> Agregando elementos con push_back..." << endl;
        array.push_back(101);
        array.push_back(102);
        imprimirArreglo(array);

        // Eliminar el ultimo elemento del vector
        cout << "\n-> Eliminando ultimo elemento con pop_back..." << endl;
        array.pop_back();
        imprimirArreglo(array);

        // Primer y ultimo elemento
        if (!array.empty()) {
            cout << "Primer elemento (front): " << array.front() << endl;
            cout << "Ultimo elemento (back): " << array.back() << endl;
        }

        // Insertar elemento en una posicion especifica (ejemplo: inicio)
        cout << "\n-> Insertando 999 al inicio (insert)..." << endl;
        array.insert(array.begin(), 999);
        imprimirArreglo(array);

        // Eliminar elemento en una posicion especifica (ejemplo: segundo elemento)
        cout << "\n-> Eliminando segundo elemento (erase)..." << endl;
        array.erase(array.begin() + 1);
        imprimirArreglo(array);

        // Consultar cantidad de elementos
        cout << "Cantidad de datos (size): " << array.size() << endl;

        // Limpieza del vector
        cout << "\n-> Limpiando el vector con clear..." << endl;
        array.clear();
        imprimirArreglo(array);

        // Verificacion si esta vacio
        if (array.empty()) {
            cout << "El arreglo esta vacio" << endl;
        } else {
            cout << "El arreglo tiene contenido" << endl;
        }
    }

    // =================================================================
    // PARTE 3: ARREGLO ESTATICO UNIDIMENSIONAL (limite de 8MB)
    // =================================================================
    {
        int n;
        cout << "Ingrese tamano para arreglo estatico: ";
        cin >> n;

        int array[n];
        for (int i = 0; i < n; i++) {
            array[i] = rand() % 100;
        }

        cout << "Arreglo estatico: ";
        for (int i = 0; i < n; i++) {
            cout << "[" << array[i] << "]";
        }
        cout << endl;
        cout << "Espacio ocupado en memoria (bytes): " << sizeof(array) << endl;
    }

    // =================================================================
    // PARTE 4: MATRIZ DINAMICA CON VECTOR DE VECTORES (vector<vector<int>>)
    // =================================================================
    {
        int n, m;
        cout << "Ingrese numero de filas n: ";
        cin >> n;
        cout << "Ingrese numero de columnas m: ";
        cin >> m;

        // Declaracion de matriz dinamica de n x m inicializada en 0
        vector<vector<int>> matriz(n, vector<int>(m, 0));

        generarMatrizAleatoria(matriz, n, m);
        cout << "\nMatriz Dinamica Generada:" << endl;
        imprimirMatriz(matriz);

        // Operacion: Suma de todos los elementos de la matriz
        int sumaTotal = 0;
        for (int i = 0; i < n; i++) {
            for (int j = 0; j < m; j++) {
                sumaTotal += matriz[i][j];
            }
        }
        cout << "\nSuma de todos los elementos de la matriz: " << sumaTotal << endl;
    }

    // =================================================================
    // PARTE 5: MULTIPLICACION DE MATRICES Y MEDICION DE TIEMPO (chrono)
    // =================================================================
    {
        int n;
        cout << "\nIngrese dimension n para multiplicar matrices cuadradas (n x n): ";
        cin >> n;

        // Declaracion de matrices cuadradas A, B y C de n x n
        vector<vector<int>> A(n, vector<int>(n, 0));
        vector<vector<int>> B(n, vector<int>(n, 0));
        vector<vector<int>> C(n, vector<int>(n, 0));

        generarMatrizAleatoria(A, n, n);
        generarMatrizAleatoria(B, n, n);

        // Medicion del tiempo de ejecucion con chrono
        auto inicio = chrono::high_resolution_clock::now();

        // Algoritmo clasico de multiplicacion de matrices O(n^3)
        for (int i = 0; i < n; i++) {
            for (int j = 0; j < n; j++) {
                for (int k = 0; k < n; k++) {
                    C[i][j] += A[i][k] * B[k][j];
                }
            }
        }

        auto fin = chrono::high_resolution_clock::now();

        // Calculo de la duracion en milisegundos y microsegundos usando tipo double
        double tiempoMilisegundos = chrono::duration<double, milli>(fin - inicio).count();
        double tiempoMicrosegundos = chrono::duration<double, micro>(fin - inicio).count();

        cout << "Multiplicacion de matrices " << n << "x" << n << " completada." << endl;
        cout << "Tiempo transcurrido: " << tiempoMilisegundos << " ms (" << tiempoMicrosegundos << " us)" << endl;
    }

    return 0;
}