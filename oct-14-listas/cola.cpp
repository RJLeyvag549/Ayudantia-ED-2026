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

class Cola{
    public:
        Nodo* front;
        Nodo* rear;

        Cola(){
            front = nullptr;
            rear = nullptr;
        }

        // enqueue: insertar al final (rear) O(1)
        void enqueue(int dato){
            Nodo* nuevo = new Nodo(dato);
            if(front == nullptr){
                front = nuevo;
                rear = nuevo;
                cout<<"Front creado: "<<nuevo->dato<<endl;
                return;
            }
            rear->next = nuevo;
            rear = nuevo;
            cout<<"Elemento encolado: "<<nuevo->dato<<endl;
        }

        // dequeue: eliminar del inicio (front) O(1)
        void dequeue(){
            if(front == nullptr){
                cout<<"La cola esta vacia, nada por desencolar..."<<endl;
                return;
            }
            Nodo* temp = front;
            front = front->next;
            if(front == nullptr){
                rear = nullptr;
            }
            cout<<"Elemento desencolado: "<<temp->dato<<endl;
            delete temp;
        }

        void mostrar(){
            if(front == nullptr){
                cout<<"Cola vacia."<<endl;
                return;
            }
            Nodo* actual = front;
            cout<<"Front -> ";
            while(actual != nullptr){
                cout<<"["<<actual->dato<<"]";
                actual = actual->next;
            }
            cout<<" <- Rear"<<endl;
        }
};

int main(){
    Cola cola;
    cola.enqueue(10);
    cola.enqueue(20);
    cola.enqueue(30);
    cola.enqueue(40);
    cola.enqueue(50);
    cola.mostrar();

    cola.dequeue();
    cola.mostrar();

    cola.dequeue();
    cola.mostrar();

    return 0;
}
