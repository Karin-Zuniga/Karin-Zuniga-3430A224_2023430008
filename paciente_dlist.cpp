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

// int main () {

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

//     //imprime pacientes
//     for (int i = 0; i < 3; ++i) {
//         cout << "Nombre paciente: " << pacientes[i].nombre << "\n";
//         cout << "Edad: " << pacientes[i].edad << "\n";
//         cout << "Peso: " << pacientes[i].peso << "\n";
//         cout << "Altura: " << pacientes[i].altura << "\n";
//         cout << "---------------- \n";        
//     }
// }
