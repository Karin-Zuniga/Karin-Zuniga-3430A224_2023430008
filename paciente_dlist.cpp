#include <iostream>
#include <string>
using namespace std;

//estructura
struct Paciente {
    string nombre;
    int edad;
    double peso;
    double altura;
    Paciente* next; //se agrega puntero
};
//Funcion para agregar
void agregarPaciente(Paciente*& head, const string& nombre, int edad, double peso, double altura){
    Paciente* nuevoPaciente = new Paciente();
    nuevoPaciente->nombre = nombre;
    nuevoPaciente->edad = edad;
    nuevoPaciente->peso = peso;
    nuevoPaciente->altura = altura;
    nuevoPaciente->next = head;
    head = nuevoPaciente;
}
//funcion para eliminar paciente
void eliminarPaciente(Paciente*& head, const string& nombre){
    Paciente* actual = head;
    Paciente* anterior = nullptr;

    while (actual != nullptr && actual->nombre != nombre){
        anterior = actual;
        actual = actual->next;
    }
    
    if (actual != nullptr){
        if (anterior == nullptr)
       {
        head = actual->next;
        }
        else
        {
            anterior->next = actual->next;
        }
        delete actual;
        
        
    }
}
//funcion para mostrar paciente
void imprimirPaciente(const Paciente* head){
    const Paciente* actual = head;
    while (actual != nullptr) {
        cout << "Nombre paciente: " << actual->nombre << "\n";
        cout << "Edad: " << actual->edad << "\n";
        cout << "Peso: " << actual->peso << "\n";
        cout << "Altura: " << actual->altura << "\n";
        cout << "---------------- \n";
        actual = actual->next;        

    }
}

int main () {
    int menu = 1;
    int opcion;
    
    Paciente* head = nullptr;

    while ( menu != 0)
    {
        cout << "Bienvenido, que desea hacer? \n";
        cout << "0. Salir\n";
        cout << "1. Agregar Paciente \n";
        cout << "2. Mostrar informacion \n";
        cout << "3. Eliminar Paciente \n";
        cin >> opcion;

        if (opcion == 0)
        {
            break;
        }
        //opcion 1. agrega datos nuevo paciente
        else if (opcion == 1)
        {
            string nombre;
            int edad;
            double peso;
            double altura;
            cout << "Nombre \n";
            cin >> nombre;
            cout << "edad \n";
            cin >> edad;
            cout << "peso \n";
            cin >> peso;
            cout << "altura \n";
            cin >> altura;

            agregarPaciente(head, nombre, edad, peso, altura);

        } 
        //muestra todos los pacientes
        else if (opcion == 2)
        {
           imprimirPaciente(head);
        }
        //elimina pidiendo el nombre del sujeto a eliminar
        else if (opcion == 3)
        {
            string nombre;
            cout << "Indique el nombre\n";
            cin >> nombre;

            eliminarPaciente(head, nombre);
        }
        

    }
    //liberar memoria
    while (head != nullptr) {
        Paciente* temp = head;
        head = head->next;
        delete temp;
    }
    
}
