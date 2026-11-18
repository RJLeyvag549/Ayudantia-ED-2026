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
    
        Lista(){
            head = nullptr;
        }

        void insertarNodoInicio(int dato){
            Nodo* nuevo = new Nodo(dato);
            if(head==nullptr){
                head = nuevo;
                
                cout<<"Head creado: "<<nuevo->dato<<endl;
                return;
            }
            nuevo->next = head;
            head->prev = nuevo;
            head = nuevo;
            cout<<"Nodo ingresado: "<<nuevo->dato<<endl;
        }

        void insertarNodoFinal(int dato){
            Nodo* nuevo = new Nodo(dato);
            if(head == nullptr){
                head = nuevo;
                cout<<"Head creado al final: "<<nuevo->dato<<endl;
                return;
            }
            Nodo* actual = head;
            while(actual->next != nullptr){
                actual = actual->next;
            }
            actual->next = nuevo;
            nuevo->prev = actual;
            cout<<"Nodo ingresado al final: "<<nuevo->dato<<endl;
        }

        void eliminarNodoFinal(){
            if(head==nullptr){
                cout<<"La lista esta vacia, nada por eliminar..." <<endl;
                return;
            }
            if(head->next == nullptr){
                delete head;
                head = nullptr;
                cout<<"Se elimino el head"<<endl;
                return;
            }
            Nodo* actual = head;
            while(actual->next != nullptr){
                actual = actual->next;
            }
            actual->prev->next = nullptr;
            delete actual;
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
    lista.insertarNodoInicio(20);
    lista.insertarNodoInicio(30);
    lista.insertarNodoInicio(40);
    lista.insertarNodoInicio(50);
    lista.mostrar();

    lista.insertarNodoFinal(5);
    lista.mostrar();

    lista.eliminarNodoFinal();
    lista.mostrar();
    
    return 0;
}
