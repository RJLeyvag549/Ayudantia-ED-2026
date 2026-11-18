#include <iostream>

using namespace std;

int main(){
    int arreglo[5] = {10, 20, 30, 40, 50};
    int arregloBasura[3];
    int arregloCeros[5] = {};

    cout << "--- Declaracion e inicializacion ---\n";
    cout << "arreglo[0] = " << arreglo[0] << endl;
    cout << "arreglo[4] = " << arreglo[4] << endl;
    cout << "arregloCeros[2] = " << arregloCeros[2] << endl; // 0
    cout << "arregloBasura[0] = " << arregloBasura[0] << endl; // valor basura

    //modificar elementos
    cout << "\n--- Modificar elementos ---\n";
    arreglo[0] = 999;
    cout << "arreglo[0] ahora es: " << arreglo[0] << endl;

    //tamaño del arreglo
    cout << "\n--- Tamano del arreglo ---\n";
    cout << "El arreglo ocupa: " << sizeof(arreglo) << " bytes" << endl;
    cout << "Cada elemento ocupa: " << sizeof(arreglo[0]) << " bytes" << endl;
    cout << "Cantidad de elementos: " << sizeof(arreglo)/sizeof(arreglo[0]) << endl;

    //recorrido con for tradicional
    cout << "\n--- Recorrido con for tradicional ---\n";
    cout << "Arreglo: ";
    int n = sizeof(arreglo)/sizeof(arreglo[0]);
    for(int i = 0; i<n; i++){
        cout << "[" << arreglo[i] << "]";
    }
    cout << endl;

    //recorrido con for each
    cout << "\n--- Recorrido con for-each ---\n";
    cout << "Arreglo: ";
    for(int valor : arreglo){
        cout << "[" << valor << "]";
    }
    cout << endl;
    
    //palabra como arreglo de char
    cout << "\n--- Arreglo de char (cadena estilo C) vs string ---\n";
    char palabra[6] = {'H','o','l','a','!','\0'}; // '\0' marca el final
    cout << "Arreglo de char: " << palabra << endl;

    //Arreglo multidimensional (matriz 2D)
    cout << "\n--- Arreglo multidimensional (matriz 2D) ---\n";
    int matriz[2][3] = {
        {1,2,3},
        {4,5,6}
    };

    for(int m=0; m<2; m++){
        for(int n=0; n<3; n++){
            cout << "[" << matriz[m][n] << "]";
        }
        cout << endl;
    }

    //Memoria contigua (los elementos estan uno pegado al otro)
    cout << "\n--- Memoria contigua ---\n";
    for(int i=0; i<n; i++){
        cout << "Numero: [" << arreglo[i] << "] -> Direccion: " << &arreglo[i] << endl;
    }

    //suma, promedio y maximo
    cout << "\n--- Suma, promedio y maximo ---\n";
    int suma = 0;
    int maximo = arreglo[0];
    for(int i=0; i<n; i++){
        suma = suma + arreglo[i];
        if(arreglo[i] > maximo){
            maximo = arreglo[i];
        }
    }
    double promedio = (double)suma/n;
    cout << "Suma: " << suma << endl;
    cout << "Promedio: " << promedio << endl;
    cout << "Maximo: " << maximo << endl;

    return 0;
}