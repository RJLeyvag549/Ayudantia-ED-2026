#include "cocina.h"

#include <iostream>
#include <string>

using namespace std;

class NodoCliente {
public:
    string nombre;
    NodoCliente* next;

    NodoCliente(string nombre){
        this->nombre = nombre;
        next = nullptr;
    }
};

class ColaClientes {
public:
    NodoCliente* front;
    NodoCliente* rear;

    ColaClientes(){
        front = nullptr;
        rear = nullptr;
    }

    bool isEmpty(){
        return front == nullptr;
    }

    void enqueue(string nombre){
        NodoCliente* nuevo = new NodoCliente(nombre);
        if(isEmpty()){
            front = nuevo;
            rear = nuevo;
        }else{
            rear->next = nuevo;
            rear = nuevo ;
        }
    }

    void dequeue(){
        if(isEmpty()){
            cout << "Cola vacia..." << endl;
            return;
        }
        NodoCliente* temp = front;
        front = front->next;
        delete temp;
    }
};

class NodoPlato {
public:
    int indice;
    NodoPlato* next;

    NodoPlato(int indice){
        this->indice = indice;
        next = nullptr;
    }
};

class PilaPlatos {
public:
    NodoPlato* top;

    PilaPlatos(){
        top = nullptr;
    }

    bool isEmpty(){
        return top == nullptr;
    }

    void push(){
        int indice = 0;
        NodoPlato* nuevo = new NodoPlato(indice);
        if(!isEmpty()){
            indice = top->indice+1;
        }
        nuevo->next = top;
        top = nuevo;
        cout<<"Se añadio plato " << top->indice << endl;
    }

    void pop(){
        if(isEmpty()){
            cout<<"La pila esta vacia, no se elimina nada..."<<endl;
            return;
        }
        NodoPlato* temp = top;
        top = top->next;
        delete temp;
    }
};

void menu() {
    ColaClientes clientes;
    PilaPlatos platos;
    int opcion;

    do {
        cout << "====================================\n"
             << "           MENU DE COCINA\n"
             << "====================================\n"
             << "  1) Recibir cliente\n"
             << "  2) Llevar cliente a la mesa\n"
             << "     y quitar un plato\n"
             << "  3) Lavar plato\n"
             << "  0) Salir\n"
             << "------------------------------------\n"
             << "Seleccion: ";

        cin >> opcion;

        switch (opcion) {
        case 1: {
            string nombre;
            cout << "Nombre del cliente: ";
            cin.ignore();
            getline(cin, nombre);
            clientes.enqueue(nombre);
            break;
        }
        case 2:
            if (clientes.isEmpty()) {
                cout << "No hay clientes esperando." << endl;
            } else if (platos.isEmpty()) {
                cout << "No hay platos limpios." << endl;
            } else {
                clientes.dequeue();
                platos.pop();
            }
            break;
        case 3:
            platos.push();
            break;
        case 0:
            cout << "Saliendo del programa..." << endl;
            break;
        default:
            cout << "Opcion no valida." << endl;
        }
    } while (opcion != 0);
}