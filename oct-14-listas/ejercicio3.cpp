#include <iostream>
#include <string>

using namespace std;

// ============================================================================
// EJERCICIO 3: PILA (STACK) BASADA EN NODOS
// Caso: Validador de Sintaxis de Delimitadores de Código { [ ( ) ] }
// ============================================================================

class NodoPila {
public:
    char simbolo;
    NodoPila* next;

    NodoPila(char s) {
        this->simbolo = s;
        this->next = nullptr;
    }
};

class Pila {
public:
    NodoPila* top;

    Pila() {
        top = nullptr;
    }

    // 1. Apilar en el tope O(1)
    void push(char s) {
        NodoPila* nuevo = new NodoPila(s);
        nuevo->next = top;
        top = nuevo;
    }

    // 2. Desapilar del tope O(1)
    void pop() {
        if (isEmpty()) {
            cout << "Pila vacía, nada por desapilar." << endl;
            return;
        }
        NodoPila* temp = top;
        top = top->next;
        delete temp;
    }

    // 3. Verificar si la pila está vacía
    bool isEmpty() {
        return top == nullptr;
    }
};

// Función externa que UTILIZA la estructura Pila para resolver el problema
bool verificarBalance(string codigo) {
    Pila pila;

    for (char c : codigo) {
        // Si es símbolo de apertura, apilar
        if (c == '(' || c == '[' || c == '{') {
            pila.push(c);
        }
        // Si es símbolo de cierre, verificar coincidencia con el tope directamente
        else if (c == ')' || c == ']' || c == '}') {
            if (pila.isEmpty()) {
                return false; // Cierre sin apertura previa
            }

            char apertura = pila.top->simbolo; // Acceso directo a top->simbolo

            if ((c == ')' && apertura != '(') ||
                (c == ']' && apertura != '[') ||
                (c == '}' && apertura != '{')) {
                return false; // No coinciden los delimitadores
            }

            pila.pop(); // Si coincidieron, desapilamos
        }
    }

    // Es válido únicamente si no quedaron aperturas pendientes
    return pila.isEmpty();
}

int main() {
    string codigoValido = "if (a[0] == 10) { procesar(); }";
    string codigoInvalido = "while (x > 0) { lista.push(y; }";

    cout << "--- EVALUACIÓN CON PILA ---" << endl;
    cout << "Analizando: " << codigoValido << endl;
    cout << "Resultado: " << (verificarBalance(codigoValido) ? "Sintaxis VÁLIDA" : "ERROR de sintaxis") << endl;

    cout << endl;
    cout << "Analizando: " << codigoInvalido << endl;
    cout << "Resultado: " << (verificarBalance(codigoInvalido) ? "Sintaxis VÁLIDA" : "ERROR de sintaxis") << endl;

    return 0;
}
