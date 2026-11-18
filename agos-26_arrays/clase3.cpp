#include<iostream>
#include<cstdlib>
#include<ctime>
#include<vector>
#include<algorithm>


using namespace std;

void imprimirArray(vector<int>& array){
    cout << "Array: ";
    for(int valor : array){
        cout << "[" << valor << "]";
    }
    cout << endl;
}

void imprimirMatriz(vector<vector<int>>& matriz){
    cout << "=== Matriz ===" << endl;
    for(int i = 0; i < matriz.size(); i++){
        for(int j = 0; j < matriz[i].size(); j++){
            cout << "[" << matriz[i][j] << "]";
        }
        cout << endl;
    }
}

void generarArrayAleatorio(vector<int>& array){
    for(int i = 0; i < array.size(); i++){
        array[i] = rand() % 100;
    }
}

void generarMatrizAleatoria(vector<vector<int>>& matriz, int n, int m){
    for(int i = 0; i<n; i++){
        for(int j=0; j<m; j++){
            matriz[i][j] = rand() % 10;
        }
    }
}

struct Computador{
    int idComputador;
    string marca;
    string modelo;
    int memoriaRam;
};

int main(){
    cout << "=== Clase de Arreglos estaticos y dinamicos ===" << endl;
    srand(time(NULL));
    int n;
    cout << "Ingrese tamaño vector: ";
    cin >> n;
    if(n <= 0){
        cout << "Tamaño invalido" << endl;
        return 1;
    } 
    
        int array[n] = {};
        for(int i = 0; i < n; i++){
            array[i] = rand() % 10000;
        }
        cout << "Array: ";
        for(int valor : array){
            cout << "[" << valor << "]";
        }
        cout << endl;
        cout << "Espacio en bytes: " << sizeof(array) << endl;


        
    vector<int> array(n);
    generarArrayAleatorio(array);
    imprimirArray(array); 
    cout << "Espacio en bytes: " << sizeof(int)*n << endl << endl;

    array.push_back(101);
    array.push_back(102);
    imprimirArray(array);

    array.pop_back(); 
    imprimirArray(array);

    cout << "Tamaño del vector: " << array.size() << endl;
    if(array.empty()){
        cout << "El vector esta vacio" << endl;
    } else {
        cout << "El vector no esta vacio" << endl;
    }
    sort(array.begin(), array.end()); //n log(n)
    imprimirArray(array);

    vector<Computador> Laboratorio(2);
    for(int i = 0; i<2; i++){
        Laboratorio[i].idComputador = Laboratorio.size() + 1;
        cout << "Ingrese marca: ";
        cin >> Laboratorio[i].marca;
        cout << "Ingrese modelo: ";
        cin >> Laboratorio[i].modelo;
        cout << "Ingrese memoria RAM: ";
        cin >> Laboratorio[i].memoriaRam;
    }

    for(int i = 0; i<2; i++){
        cout << "Computador " << i+1 << ": " << Laboratorio[i].marca << " " << Laboratorio[i].modelo << " con " << Laboratorio[i].memoriaRam << " GB de RAM" << endl;
    }

    int n, m;
    cout << "Ingrese filas: ";
    cin >> n;
    cout << "Ingrese columnas: ";
    cin >> m;
    if(n <= 0 || m <= 0){
        cout << "Tamaños invalidos" << endl;
        return 1;
    }
    
    vector<vector<int>> matriz(n, vector<int>(m));
    generarMatrizAleatoria(matriz, n, m);
    imprimirMatriz(matriz);
 
    return 0;
}