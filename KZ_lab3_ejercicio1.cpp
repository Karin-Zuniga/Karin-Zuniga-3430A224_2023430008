#include <iostream>
#include <vector>
using namespace std;

struct Dato
{
    int numero;
   
    Dato* next;

};

class Pila
{
public:
    int max;
    int tope = 0;
    bool band = false;
    Dato* head;

    bool Pila_llena(int tope, int max){
        bool band;
        if (tope == max)
        {
            band = true;
        }
        else
        {
            band = false;
        }
        return band;
    }

    void push(int dato){
        
        if (Pila_llena(tope, max) == true)
        {
            cout << "Desbordamiento, Pila llena\n";
            return;
        }

        Dato* nuevoDato = new Dato();
        nuevoDato->numero = dato;
        nuevoDato->next = NULL;
        tope = tope + 1;

        if (!head) {
            head = nuevoDato;
            return;
        }
        
        Dato* temp = head;
        while (temp->next) {
            temp = temp->next;
        }
        temp->next = nuevoDato;
        
    }

    void pop(){
        if (!head) {
            cout << "Subdesbordamiento, Pila vacia." << endl;
            return;
        }
        if (!head->next) {
            delete head;   
            head = NULL;
            tope = tope - 1;   
            return;
        }
        Dato* temp = head;
        while (temp->next->next) {
            temp = temp->next;
        }
        delete temp->next;
        temp->next = NULL;
        
    }

    void mostrar() {
        if (!head) {
            cout << "Pila Vacia" << endl;
            return;
        }

        Dato* temp = head;
        while (temp) {
            cout << temp->numero << " , "; 
            temp = temp->next;
        }
        cout << "Fin de la pila" << endl; 
    }

        
};


int main () {

    int menu = 1;
    int maximo;
    cout << "Ingrese maximo de la pila\n";
    cin >> maximo;
    Pila nueva_pila;
    nueva_pila.max = maximo;

    
    while ( menu != 0)
    {
        int opcion;

        cout << "Bienvenido, que desea hacer? \n";
        cout << "Agregar[1] \n";
        cout << "Remover[2] \n";
        cout << "Ver pila[3]\n ";
        cout << "Salir[0] \n";
        cin >> opcion;

        if (opcion == 0)
        {
            break;
        }
        
        else if (opcion == 1)
        {
            int dato;
            cout << "Agregue dato \n";
            cin >> dato;
            nueva_pila.push(dato);
            
            
        } 
        
        else if (opcion == 2)
        {
            nueva_pila.pop();
        }
        
        else if (opcion == 3)
        {
            nueva_pila.mostrar();    
        }
        
        else
        {
            cout << "opcion no valida\n";
        }
    }
}