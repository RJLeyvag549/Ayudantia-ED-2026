#include <iostream>
#include <vector>
#include <string>
#include <sstream>

using namespace std;

struct CalculadoraArreglo {
    int numDimensiones;
    vector<int> capacidades; 
    vector<int> indices;      
    int tamanioElementoBytes; 
    string nombreTipoDato;
    int direccionBase;        
};

int obtenerTamanioTipo(int opcion, string& nombreTipo) {
    switch (opcion) {
        case 1: nombreTipo = "char"; return sizeof(char);
        case 2: nombreTipo = "short"; return sizeof(short);
        case 3: nombreTipo = "int"; return sizeof(int);
        case 4: nombreTipo = "long long"; return sizeof(long long);
        case 5: nombreTipo = "float"; return sizeof(float);
        case 6: nombreTipo = "double"; return sizeof(double);
        case 7: {
            int bytes = 0;
            cout << "Ingrese el tamaño personalizado del elemento en bytes: ";
            cin >> bytes;
            nombreTipo = "Personalizado (" + to_string(bytes) + " bytes)";
            return bytes;
        }
        default: nombreTipo = "int"; return sizeof(int);
    }
}

int calcularTotalElementos(const vector<int>& capacidades) {
    int total = 1;
    for (int cap : capacidades) {
        total *= cap;
    }
    return total;
}

int calcularDesplazamientoElementos(const vector<int>& capacidades, const vector<int>& indices) {
    int n = capacidades.size();
    int offsetTotal = 0;

    for (int k = 0; k < n; ++k) {
        int pesoDimension = 1;
        for (int j = k + 1; j < n; ++j) {
            pesoDimension *= capacidades[j];
        }
        offsetTotal += indices[k] * pesoDimension;
    }
    return offsetTotal;
}

void desplegarMenuPrincipal() {
    CalculadoraArreglo calc;
    calc.numDimensiones = 0;
    calc.tamanioElementoBytes = sizeof(int);
    calc.nombreTipoDato = "int";
    calc.direccionBase = 1000;

    int opcion = 0;

    do {
        cout << "\n==================================================" << endl;
        cout << "=== CALCULADORA DE TAMAÑO Y ACCESO A ARREGLOS  ===" << endl;
        cout << "==================================================" << endl;
        cout << "1. Definir tipo de dato (Actual: " << calc.nombreTipoDato << " [" << calc.tamanioElementoBytes << " bytes])" << endl;
        cout << "2. Definir N dimensiones y sus capacidades D1, D2, ..., DN (Actual: ";
        if (calc.numDimensiones == 0) {
            cout << "No definido";
        } else {
            cout << calc.numDimensiones << "D -> ";
            for (int i = 0; i < calc.numDimensiones; ++i) {
                cout << "[" << calc.capacidades[i] << "]";
            }
        }
        cout << ")" << endl;
        cout << "3. Definir Direccion Base (Actual: " << calc.direccionBase << " [0x" << hex << uppercase << calc.direccionBase << dec << "])" << endl;
        cout << "4. Ingresar indices de acceso [i1][i2]...[iN] y calcular" << endl;
        cout << "5. Calcular tamaño del arreglo actual" << endl;
        cout << "6. Salir" << endl;
        cout << "--------------------------------------------------" << endl;
        cout << "Seleccione una opcion: ";
        cin >> opcion;

        switch (opcion) {
            case 1: {
                cout << "\n--- SELECCION DE TIPO DE DATO ---" << endl;
                cout << "1. char (" << sizeof(char) << " byte)" << endl;
                cout << "2. short (" << sizeof(short) << " bytes)" << endl;
                cout << "3. int (" << sizeof(int) << " bytes)" << endl;
                cout << "4. long long (" << sizeof(long long) << " bytes)" << endl;
                cout << "5. float (" << sizeof(float) << " bytes)" << endl;
                cout << "6. double (" << sizeof(double) << " bytes)" << endl;
                cout << "7. Tamaño personalizado en bytes" << endl;
                cout << "Opcion: ";
                int subopcion;
                cin >> subopcion;
                calc.tamanioElementoBytes = obtenerTamanioTipo(subopcion, calc.nombreTipoDato);
                cout << "-> Tipo configurado a: " << calc.nombreTipoDato << endl;
                break;
            }

            case 2: {
                cout << "\n--- DEFINICION DE DIMENSIONES Y CAPACIDADES ---" << endl;
                if (calc.numDimensiones > 0) {
                    cout << "Configuracion actual: " << calc.numDimensiones << " dimensiones (";
                    for (int i = 0; i < calc.numDimensiones; ++i) {
                        cout << "[" << calc.capacidades[i] << "]";
                    }
                    cout << ")" << endl;
                }
                cout << "Ingrese el numero de dimensiones (X dimensiones): ";
                cin >> calc.numDimensiones;

                if (calc.numDimensiones <= 0) {
                    cout << "Error: El numero de dimensiones debe ser un entero positivo." << endl;
                    calc.numDimensiones = 0;
                    calc.capacidades.clear();
                    calc.indices.clear();
                    break;
                }

                calc.capacidades.resize(calc.numDimensiones);
                calc.indices.assign(calc.numDimensiones, 0);

                for (int i = 0; i < calc.numDimensiones; ++i) {
                    do {
                        cout << "Capacidad para la Dimension " << (i + 1) << " (D" << (i + 1) << "): ";
                        cin >> calc.capacidades[i];
                        if (calc.capacidades[i] <= 0) {
                            cout << "Error: La capacidad debe ser un numero entero positivo (> 0)." << endl;
                        }
                    } while (calc.capacidades[i] <= 0);
                }

                int totalElementos = calcularTotalElementos(calc.capacidades);
                int tamanioBytes = totalElementos * calc.tamanioElementoBytes;

                cout << "\n[OK] Arreglo configurado exitosamente:" << endl;
                cout << "Estructura: ";
                for (int i = 0; i < calc.numDimensiones; ++i) {
                    cout << "[" << calc.capacidades[i] << "]";
                }
                cout << endl;
                break;
            }

            case 3: {
                cout << "\n--- DIRECCION BASE ---" << endl;
                cout << "1. Ingresar en Decimal (ej. 1000)" << endl;
                cout << "2. Ingresar en Hexadecimal (ej. 0x1000 o 1000)" << endl;
                cout << "Opcion: ";
                int subopcion;
                cin >> subopcion;
                if (subopcion == 2) {
                    string hexStr;
                    cout << "Ingrese direccion base hexadecimal: ";
                    cin >> hexStr;
                    stringstream ss;
                    ss << hex << hexStr;
                    ss >> calc.direccionBase;
                } else {
                    cout << "Ingrese direccion base decimal: ";
                    cin >> calc.direccionBase;
                }
                cout << "-> Direccion Base guardada: " << calc.direccionBase 
                     << " (Hexadecimal: 0x" << hex << uppercase << calc.direccionBase << dec << ")" << endl;
                break;
            }

            case 4: {
                if (calc.numDimensiones == 0) {
                    cout << "\nError: Primero debe definir las dimensiones del arreglo (Opcion 2)." << endl;
                    break;
                }

                cout << "\n--- INGRESO DE INDICES DE ACCESO ---" << endl;
                cout << "Ingrese las posiciones a acceder para cada dimension (0 a Capacidad-1):" << endl;

                for (int i = 0; i < calc.numDimensiones; ++i) {
                    do {
                        cout << "Indice para Dimension " << (i + 1) << " [0.." << (calc.capacidades[i] - 1) << "]: ";
                        cin >> calc.indices[i];
                        if (calc.indices[i] < 0 || calc.indices[i] >= calc.capacidades[i]) {
                            cout << " Error: El indice " << calc.indices[i] << " esta fuera de rango [0.." 
                                 << (calc.capacidades[i] - 1) << "]." << endl;
                        }
                    } while (calc.indices[i] < 0 || calc.indices[i] >= calc.capacidades[i]);
                }

                int offsetElementos = calcularDesplazamientoElementos(calc.capacidades, calc.indices);
                int offsetBytes = offsetElementos * calc.tamanioElementoBytes;
                int direccionFinal = calc.direccionBase + offsetBytes;

                cout << "\n==================================================" << endl;
                cout << "=== CALCULOS DE ACCESO A MEMORIA ===" << endl;
                cout << "==================================================" << endl;
                cout << "Acceso solicitado: ";
                for (int i = 0; i < calc.numDimensiones; ++i) {
                    cout << "[" << calc.indices[i] << "]";
                }
                cout << endl;

                cout << "\n1. Desglose de Productos/Sumatoria (Offset por Dimension):" << endl;
                for (int k = 0; k < calc.numDimensiones; ++k) {
                    int pesoDimension = 1;
                    string expMult = "";
                    for (int j = k + 1; j < calc.numDimensiones; ++j) {
                        pesoDimension *= calc.capacidades[j];
                        expMult += " * D" + to_string(j + 1) + "(" + to_string(calc.capacidades[j]) + ")";
                    }
                    cout << "   - Dim " << (k + 1) << ": i" << (k + 1) << "(" << calc.indices[k] << ")" 
                         << (expMult.empty() ? "" : expMult) 
                         << " = " << calc.indices[k] * pesoDimension << " elementos" << endl;
                }

                cout << "\n2. Sumatoria total de elementos desplazados = " << offsetElementos << " elementos" << endl;
                cout << "3. Desplazamiento en Bytes = " << offsetElementos << " elementos * " 
                     << calc.tamanioElementoBytes << " bytes = " << offsetBytes << " bytes" << endl;

                cout << "\n4. DIRECCION DE MEMORIA CALCULADA:" << endl;
                cout << "   Direccion Final = DirBase + (Sumatoria(i_k * multiplicatoria(Capacidades)) * tamañoBytes)" << endl;
                cout << "   Direccion Final = " << calc.direccionBase << " + " << offsetBytes << " = " << direccionFinal << endl;
                cout << "   (En Hexadecimal secundario: 0x" << hex << uppercase << calc.direccionBase 
                     << " + 0x" << offsetBytes << " = 0x" << direccionFinal << dec << ")" << endl;
                cout << "==================================================" << endl;
                break;
            }

            case 5: {
                if (calc.numDimensiones == 0) {
                    cout << "\nError: Primero debe definir las dimensiones del arreglo (Opcion 2)." << endl;
                    break;
                }
                int totalElem = calcularTotalElementos(calc.capacidades);
                int totalBytes = totalElem * calc.tamanioElementoBytes;

                cout << "\n==================================================" << endl;
                cout << "=== CALCULO DE TAMAÑO DEL ARREGLO ACTUAL ===" << endl;
                cout << "==================================================" << endl;
                cout << "- Tipo de Dato: " << calc.nombreTipoDato << " (" << calc.tamanioElementoBytes << " bytes)" << endl;
                cout << "- Arreglo: ";
                for (int i = 0; i < calc.numDimensiones; ++i) {
                    cout << "[" << calc.capacidades[i] << "]";
                }
                cout << endl;
                cout << "- Total Elementos = ";
                for (int i = 0; i < calc.numDimensiones; ++i) {
                    cout << calc.capacidades[i] << (i + 1 < calc.numDimensiones ? " * " : "");
                }
                cout << " = " << totalElem << " elementos" << endl;
                cout << "- Tamaño Total en Bytes = " << totalElem << " elementos * " 
                     << calc.tamanioElementoBytes << " bytes = " << totalBytes << " bytes" << endl;
                cout << "==================================================" << endl;
                break;
            }

            case 6:
                cout << "¡Hasta luego!" << endl;
                break;

            default:
                cout << "Opcion invalida. Intente de nuevo." << endl;
                break;
        }

    } while (opcion != 6);
}

int main() {
    desplegarMenuPrincipal();
    return 0;
}
