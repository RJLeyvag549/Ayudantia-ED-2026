#include <iostream>
#include <vector>
#include <cstdlib>
#include <ctime>
#include <chrono>

using namespace std;

// Rellena las matrices con enteros aleatorios simples entre 1 y 9
void generarMatrizAleatoria(vector<int>& m1, vector<int>& m2, int n) {
    int totalElementos = n * n;
    for (int i = 0; i < totalElementos; ++i) {
        m1[i] = 1 + rand() % 9;
        m2[i] = 1 + rand() % 9;
    }
}

// Suma de submatrices: R = A + B
void sumarMatrices(const vector<int>& A, const vector<int>& B, vector<int>& R, int n) {
    int total = n * n;
    for (int i = 0; i < total; ++i) {
        R[i] = A[i] + B[i];
    }
}

// Resta de submatrices: R = A - B
void restarMatrices(const vector<int>& A, const vector<int>& B, vector<int>& R, int n) {
    int total = n * n;
    for (int i = 0; i < total; ++i) {
        R[i] = A[i] - B[i];
    }
}

// --- ALGORITMO 1: TRADICIONAL ---
void multiplicarTradicional(const vector<int>& A, const vector<int>& B, vector<int>& C, int n) {
    for (int i = 0; i < n; ++i) {
        for (int j = 0; j < n; ++j) {
            int suma = 0;
            for (int k = 0; k < n; ++k) {
                suma += A[i * n + k] * B[k * n + j];
            }
            C[i * n + j] = suma;
        }
    }
}

// --- ALGORITMO 2: DR1 (Divide y Vencerás Tradicional - Propiedad 1) ---
void multiplicarDR1(const vector<int>& A, const vector<int>& B, vector<int>& C, int n) {
    if (n <= 16) {
        multiplicarTradicional(A, B, C, n);
        return;
    }

    int mitad = n / 2;
    int tamSub = mitad * mitad;

    vector<int> A11(tamSub), A12(tamSub), A21(tamSub), A22(tamSub);
    vector<int> B11(tamSub), B12(tamSub), B21(tamSub), B22(tamSub);

    for (int i = 0; i < mitad; ++i) {
        for (int j = 0; j < mitad; ++j) {
            A11[i * mitad + j] = A[i * n + j];
            A12[i * mitad + j] = A[i * n + (j + mitad)];
            A21[i * mitad + j] = A[(i + mitad) * n + j];
            A22[i * mitad + j] = A[(i + mitad) * n + (j + mitad)];

            B11[i * mitad + j] = B[i * n + j];
            B12[i * mitad + j] = B[i * n + (j + mitad)];
            B21[i * mitad + j] = B[(i + mitad) * n + j];
            B22[i * mitad + j] = B[(i + mitad) * n + (j + mitad)];
        }
    }

    vector<int> P1(tamSub), P2(tamSub), P3(tamSub), P4(tamSub);
    vector<int> P5(tamSub), P6(tamSub), P7(tamSub), P8(tamSub);

    multiplicarDR1(A11, B11, P1, mitad);
    multiplicarDR1(A12, B21, P2, mitad);
    multiplicarDR1(A11, B12, P3, mitad);
    multiplicarDR1(A12, B22, P4, mitad);
    multiplicarDR1(A21, B11, P5, mitad);
    multiplicarDR1(A22, B21, P6, mitad);
    multiplicarDR1(A21, B12, P7, mitad);
    multiplicarDR1(A22, B22, P8, mitad);

    for (int i = 0; i < mitad; ++i) {
        for (int j = 0; j < mitad; ++j) {
            int idxSub = i * mitad + j;
            C[i * n + j]                 = P1[idxSub] + P2[idxSub];
            C[i * n + (j + mitad)]       = P3[idxSub] + P4[idxSub];
            C[(i + mitad) * n + j]       = P5[idxSub] + P6[idxSub];
            C[(i + mitad) * n + (j + mitad)] = P7[idxSub] + P8[idxSub];
        }
    }
}

// --- ALGORITMO 3: DR2 (Algoritmo de Strassen - Propiedad 2) ---
void multiplicarDR2(const vector<int>& A, const vector<int>& B, vector<int>& C, int n) {
    if (n <= 16) {
        multiplicarTradicional(A, B, C, n);
        return;
    }

    int mitad = n / 2;
    int tamSub = mitad * mitad;

    vector<int> A11(tamSub), A12(tamSub), A21(tamSub), A22(tamSub);
    vector<int> B11(tamSub), B12(tamSub), B21(tamSub), B22(tamSub);

    for (int i = 0; i < mitad; ++i) {
        for (int j = 0; j < mitad; ++j) {
            A11[i * mitad + j] = A[i * n + j];
            A12[i * mitad + j] = A[i * n + (j + mitad)];
            A21[i * mitad + j] = A[(i + mitad) * n + j];
            A22[i * mitad + j] = A[(i + mitad) * n + (j + mitad)];

            B11[i * mitad + j] = B[i * n + j];
            B12[i * mitad + j] = B[i * n + (j + mitad)];
            B21[i * mitad + j] = B[(i + mitad) * n + j];
            B22[i * mitad + j] = B[(i + mitad) * n + (j + mitad)];
        }
    }

    vector<int> M(tamSub), N(tamSub), O(tamSub), P(tamSub), Q(tamSub), R(tamSub), S(tamSub);
    vector<int> temp1(tamSub), temp2(tamSub);

    sumarMatrices(A11, A22, temp1, mitad);
    sumarMatrices(B11, B22, temp2, mitad);
    multiplicarDR2(temp1, temp2, M, mitad);

    sumarMatrices(A21, A22, temp1, mitad);
    multiplicarDR2(temp1, B11, N, mitad);

    restarMatrices(B12, B22, temp1, mitad);
    multiplicarDR2(A11, temp1, O, mitad);

    restarMatrices(B21, B11, temp1, mitad);
    multiplicarDR2(A22, temp1, P, mitad);

    sumarMatrices(A11, A12, temp1, mitad);
    multiplicarDR2(temp1, B22, Q, mitad);

    restarMatrices(A21, A11, temp1, mitad);
    sumarMatrices(B11, B12, temp2, mitad);
    multiplicarDR2(temp1, temp2, R, mitad);

    restarMatrices(A12, A22, temp1, mitad);
    sumarMatrices(B21, B22, temp2, mitad);
    multiplicarDR2(temp1, temp2, S, mitad);

    for (int i = 0; i < mitad; ++i) {
        for (int j = 0; j < mitad; ++j) {
            int idxSub = i * mitad + j;
            C[i * n + j]                     = M[idxSub] + P[idxSub] - Q[idxSub] + S[idxSub];
            C[i * n + (j + mitad)]           = O[idxSub] + Q[idxSub];
            C[(i + mitad) * n + j]           = N[idxSub] + P[idxSub];
            C[(i + mitad) * n + (j + mitad)] = M[idxSub] + O[idxSub] - N[idxSub] + R[idxSub];
        }
    }
}

bool verificarIgualdad(const vector<int>& C1, const vector<int>& C2, int n) {
    int total = n * n;
    for (int i = 0; i < total; ++i) {
        if (C1[i] != C2[i]) return false;
    }
    return true;
}

// 3. MAIN Y PRUEBA DE RENDIMIENTO
int main() {
    srand((unsigned int)time(NULL));

    vector<int> tamanos = {64, 128, 256, 512, 1024, 2048};

    cout << "=========================================================================\n";
    cout << "  BENCHMARK EN C++: ALGORITMOS DE MULTIPLICACIÓN DE MATRICES (UBB 2024)\n";
    cout << "=========================================================================\n\n";

    cout << "n\t\t| Tradicional (s)\t| DR1 (s)\t\t| DR2 (s)\n";
    cout << "-------------------------------------------------------------------------\n";

    for (int n : tamanos) {
        int totalElem = n * n;

        vector<int> A(totalElem), B(totalElem);
        vector<int> C_trad(totalElem), C_dr1(totalElem), C_dr2(totalElem);

        generarMatrizAleatoria(A, B, n);

        // 1. Tradicional
        auto inicio = chrono::high_resolution_clock::now();
        multiplicarTradicional(A, B, C_trad, n);
        auto fin = chrono::high_resolution_clock::now();
        double t_trad = chrono::duration<double>(fin - inicio).count();

        // 2. DR1
        inicio = chrono::high_resolution_clock::now();
        multiplicarDR1(A, B, C_dr1, n);
        fin = chrono::high_resolution_clock::now();
        double t_dr1 = chrono::duration<double>(fin - inicio).count();

        // 3. DR2
        inicio = chrono::high_resolution_clock::now();
        multiplicarDR2(A, B, C_dr2, n);
        fin = chrono::high_resolution_clock::now();
        double t_dr2 = chrono::duration<double>(fin - inicio).count();

        if (!verificarIgualdad(C_trad, C_dr1, n) || !verificarIgualdad(C_trad, C_dr2, n)) {
            cerr << "ERROR: Los resultados de las matrices no coinciden para n = " << n << "!\n";
        }

        cout << n << "\t\t| " << t_trad << " s\t\t| " << t_dr1 << " s\t\t| " << t_dr2 << " s\n";
    }

    cout << "-------------------------------------------------------------------------" << endl;
    return 0;
}

