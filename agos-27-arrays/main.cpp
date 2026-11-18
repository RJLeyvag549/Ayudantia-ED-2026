// Comparacion de tipos de datos y multiplicacion de matrices.
#include <chrono>
#include <iostream>
#include <vector>

using namespace std;


void llenarMatrices(vector<vector<int>>& matrizA,
					vector<vector<int>>& matrizB,
					int n) {
	for (int fila = 0; fila < n; fila++) {
		for (int columna = 0; columna < n; columna++) {
			matrizA[fila][columna] = (fila * n + columna) % 10 + 1;
			matrizB[fila][columna] = (fila * n + columna + 3) % 10 + 1;
		}
	}
}

void multiplicarMatrices(const vector<vector<int>>& matrizA,
						 const vector<vector<int>>& matrizB,
						 vector<vector<long long>>& resultado,
						 int n) {
	for (int fila = 0; fila < n; fila++) {
		for (int columna = 0; columna < n; columna++) {
			long long suma = 0;
			for (int k = 0; k < n; k++) {
				suma += matrizA[fila][k] * matrizB[k][columna];
			}
			resultado[fila][columna] = suma;
		}
	}
}

void multiplicarConNewDelete(const int* matrizA,
							 const int* matrizB,
							 long long* resultado,
							 int n) {
	for (int fila = 0; fila < n; fila++) {
		for (int columna = 0; columna < n; columna++) {
			long long suma = 0;
			for (int k = 0; k < n; k++) {
				suma += matrizA[fila * n + k] * matrizB[k * n + columna];
			}
			resultado[fila * n + columna] = suma;
		}
	}
}

int main() {
	int n;
	cout << "=== Comparacion de arreglos y matrices ===\n";
	cout << "Ingrese n: ";
	cin >> n;

	if (!cin || n == 0 || n > 1000) {
		cout << "Ingrese un valor entre 1 y 1000.\n";
		return 1;
	}

	cout << "\nTamanos de tipos de datos\n";
	cout << "short:      " << sizeof(short) << " bytes\n";
	cout << "int:        " << sizeof(int) << " bytes\n";
	cout << "long:       " << sizeof(long) << " bytes\n";
	cout << "long long:  " << sizeof(long long) << " bytes\n";
	cout << "float:      " << sizeof(float) << " bytes\n";
	cout << "double:     " << sizeof(double) << " bytes\n";
	cout << "\nUn arreglo de n elementos ocupa n * sizeof(tipo).\n";
	cout << "Una matriz de n x n elementos ocupa n * n * sizeof(tipo).\n";

	int cantidad = n * n;
	vector<vector<int>> matrizA(n, vector<int>(n));
	vector<vector<int>> matrizB(n, vector<int>(n));
	vector<vector<long long>> resultadoVector(n, vector<long long>(n));
	llenarMatrices(matrizA, matrizB, n);

	auto inicioVector = chrono::high_resolution_clock::now();
	multiplicarMatrices(matrizA, matrizB, resultadoVector, n);
	auto finVector = chrono::high_resolution_clock::now();
	double tiempoVector = chrono::duration<double, milli>(finVector - inicioVector).count();

	int* matrizANew = new int[cantidad];
	int* matrizBNew = new int[cantidad];
	long long* resultadoNew = new long long[cantidad];

	for (int i = 0; i < cantidad; i++) {
		matrizANew[i] = matrizA[i];
		matrizBNew[i] = matrizB[i];
	}

	auto inicioNew = chrono::high_resolution_clock::now();
	multiplicarConNewDelete(matrizANew, matrizBNew, resultadoNew, n);
	auto finNew = chrono::high_resolution_clock::now();
	double tiempoNew = chrono::duration<double, milli>(finNew - inicioNew).count();
	long long primerResultadoVector = resultadoVector[0][0];
	long long primerResultadoNew = resultadoNew[0];

	delete[] matrizANew;
	delete[] matrizBNew;
	delete[] resultadoNew;

	cout << "\n=== Multiplicacion de matrices ===\n";
	cout << "Vector:      " << tiempoVector << " ms\n";
	cout << "new/delete:  " << tiempoNew << " ms\n";
	cout << "Primer resultado con vector: " << primerResultadoVector << "\n";
	cout << "Primer resultado con new: " << primerResultadoNew << "\n";

	return 0;
}
