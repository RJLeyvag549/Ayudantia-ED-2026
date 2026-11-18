#include<iostream>

using namespace std;

class Nodo{
    public:
        int dato;
        Nodo* next;
        Nodo* prev;
    Nodo(int dato){
        this->dato = dato;
        next = nullptr;
        prev = nullptr;
    }
};

class Lista{
    public: 
        Nodo* head;
        Nodo* tail;
    
        Lista(){
            head = nullptr;
            tail = nullptr;
        }

        void insertarNodoInicio(int dato){
            Nodo* nuevo = new Nodo(dato);
            nuevo->next = head;
            head = nuevo;
            cout<<"Nodo ingresado: "<<nuevo->dato<<endl;
        }

        void eliminarNodoFinal(){
            if(head==nullptr){
                cout<<"La lista esta vacia, nada por eliminar..." <<endl;
                return;
            }
            if(head->next == nullptr){
                delete head;
                head = nullptr;
                cout<<"Se eliminoi el head"<<endl;
                return;
            }
            Nodo* actual = head;
            while(actual->next->next != nullptr){
                cout << actual <<endl;    //imprime direccion
                actual = actual->next;
            }
            cout << actual <<endl;    //imprime direccion
            delete actual->next;
            actual->next = nullptr;
        }

        void mostrar(){
            Nodo* actual = head;
            while(actual != nullptr){
                cout<<"["<<actual->dato<<"]";
                actual = actual->next;
            }
            cout<<endl;
        }
};

int main(){
    Lista lista;
    lista.insertarNodoInicio(10);
    lista.insertarNodoInicio(30);
    lista.insertarNodoInicio(20);
    lista.insertarNodoInicio(40);
    lista.insertarNodoInicio(60);
    lista.mostrar();
    lista.eliminarNodoFinal();
    lista.mostrar();
    
}