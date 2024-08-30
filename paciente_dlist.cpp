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

    }
}

int main () {
    
}

//     //creacion de arreglo
//     Paciente pacientes[3];

//     pacientes[0].nombre = "Maria";
//     pacientes[0].edad = 45;
//     pacientes[0].peso = 54.5;
//     pacientes[0].altura = 1.65;

//     pacientes[1].nombre = "Juana";
//     pacientes[1].edad = 65;
//     pacientes[1].peso = 59.0;
//     pacientes[1].altura = 1.55;

//     pacientes[2].nombre = "Matias";
//     pacientes[2].edad = 29;
//     pacientes[2].peso = 88.0;
//     pacientes[2].altura = 1.80;

