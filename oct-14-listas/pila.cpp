#include<iostream>

using namespace std;

class Nodo{
    public:
        int dato;
        Nodo* next;

    Nodo(int dato){
        this->dato = dato;
        next = nullptr;
    }
};

class Pila{
    public:
        Nodo* top;

        Pila(){
            top = nullptr;
        }

        // push: insertar al inicio (tope) O(1)
        void push(int dato){
            Nodo* nuevo = new Nodo(dato);
            if(top == nullptr){
                top = nuevo;
                cout<<"Top creado: "<<nuevo->dato<<endl;
                return;
            }
            nuevo->next = top;
            top = nuevo;
            cout<<"Elemento apilado: "<<nuevo->dato<<endl;
        }

        // pop: eliminar del inicio (tope) O(1)
        void pop(){
            if(top == nullptr){
                cout<<"La pila esta vacia, nada por desapilar..."<<endl;
                return;
            }
            Nodo* temp = top;
            top = top->next;
            cout<<"Elemento desapilado: "<<temp->dato<<endl;
            delete temp;
        }

        void mostrar(){
            if(top == nullptr){
                cout<<"Pila vacia."<<endl;
                return;
            }
            Nodo* actual = top;
            cout<<"Tope -> ";
            while(actual != nullptr){
                cout<<"["<<actual->dato<<"]";
                actual = actual->next;
            }
            cout<<endl;
        }
};

int main(){
    Pila pila;
    pila.push(10);
    pila.push(20);
    pila.push(30);
    pila.push(40);
    pila.push(50);
    pila.mostrar();

    pila.pop();
    pila.mostrar();

    pila.pop();
    pila.mostrar();

    return 0;
}
