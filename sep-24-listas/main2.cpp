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

class ListaCircular{
    public: 
        Nodo* head;
    
        ListaCircular(){
            head = nullptr;
        }

        void insertarNodoInicio(int dato){
            Nodo* nuevo = new Nodo(dato);
            if(head == nullptr){
                head = nuevo;
                nuevo->next = head;
                cout<<"Head creado: "<<nuevo->dato<<endl;
                return;
            }

            
            Nodo* actual = head;
            while(actual->next != head){
                actual = actual->next;
            }
            nuevo->next = head;
            actual->next = nuevo;
            head = nuevo;
            


            cout<<"Nodo ingresado: "<<nuevo->dato<<endl;
        }

        void insertarNodoFinal(int dato){
            Nodo* nuevo = new Nodo(dato);
            if(head == nullptr){
                head = nuevo;
                nuevo->next = head; 
                cout<<"Head creado al final: "<<nuevo->dato<<endl;
                return;
            }

            Nodo* actual = head;
            while(actual->next != head){
                actual = actual->next;
            }
            actual->next = nuevo;
            nuevo->next = head;

            cout<<"Nodo ingresado al final: "<<nuevo->dato<<endl;
        }

        void eliminarNodoFinal(){
            if(head == nullptr){
                cout<<"La lista esta vacia, nada por eliminar..." <<endl;
                return;
            }

            if(head->next == nullptr || head->next == head){
                delete head;
                head = nullptr;
                cout<<"Se elimino el head"<<endl;
                return;
            }

            
            Nodo* actual = head;
            while(actual->next->next != head){
                actual = actual->next;
            }
            delete actual->next;
            actual->next = head;

        }

        void mostrar(){
            if(head == nullptr) return;
            Nodo* actual = head;
            do {
                cout<<"["<<actual->dato<<"]";
                actual = actual->next;
            } while(actual != head);
            cout<<endl;
        
        }
};

int main(){
    ListaCircular lista;
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
