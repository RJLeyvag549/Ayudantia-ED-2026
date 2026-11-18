#include <iostream>

using namespace std;
//tipos de datos primitivos: bool, char, int, float, double

int main() {
    bool esVerdadero = false; // 0 es false, 1 es true
    cout << "bool: " << esVerdadero << " -> tamaño ->" << sizeof(esVerdadero) << " bytes" << endl;
    /*
    if(esVerdadero){
        cout << esVerdadero << " es verdadero" << endl;
    } else {
        cout << esVerdadero << " es falso" << endl;
    }
    */

    //caracteres
    char letra = 'A';
    cout << "char: " << letra << " -> tamaño ->" << sizeof(letra) << " bytes" << endl;
    cin >> letra;
    //numeros enteros
    unsigned char byte = 255;
    cout << "byte: " << (int)byte << " -> tamaño ->" << sizeof(byte) << " bytes" << endl;

    short numShort = 32000;
    cout << "short: " << numShort << " -> tamaño ->" << sizeof(numShort) << " bytes" << endl;

    int numInt = 2000000000;
    cout << "int: " << numInt << " -> tamaño ->" << sizeof(numInt) << " bytes" << endl;

    long numLong = 9000000000000000000;
    cout << "long: " << numLong << " -> tamaño ->" << sizeof(numLong) << " bytes" << endl;

    //numeros flotantes
    cout.precision(10);
    cout << fixed;
    float numFloat = 3.1415923423;
    cout << "float: " << numFloat << " -> tamaño ->" << sizeof(numFloat) << " bytes" << endl;
    double numDouble = 3.1415923423;
    cout << "double: " << numDouble << " -> tamaño ->" << sizeof(numDouble) << " bytes" << endl;

    //Direcciones de memoria
    cout << "\n--- direcciones en ram ---" << endl;
    cout << "esVerdadero -> " << (void*)&esVerdadero << endl;
    cout << "letra1      -> " << (void*)&letra << endl;
    cout << "numShort    -> " << (void*)&numShort << endl;
    cout << "numInt      -> " << (void*)&numInt << endl;
    cout << "numLong     -> " << (void*)&numLong << endl;
    cout << "numFloat    -> " << (void*)&numFloat << endl;
    cout << "numDouble   -> " << (void*)&numDouble << endl;
}