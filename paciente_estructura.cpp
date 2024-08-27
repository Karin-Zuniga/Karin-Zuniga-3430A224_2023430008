#include <iostream>
#include <string>
using namespace std;

struct Paciente {
    string nombre;
    int edad;
    double peso;
    double altura;
};

int main () {
    Paciente paciente_1;
    paciente_1.nombre = "Maria";
    paciente_1.edad = 45;
    paciente_1.peso = 54.5;
    paciente_1.altura = 1.65;

    Paciente paciente_2;
    paciente_2.nombre = "Juana";
    paciente_2.edad = 65;
    paciente_2.peso = 59.0;
    paciente_2.altura = 1.55;

    Paciente paciente_3;
    paciente_3.nombre = "Matias";
    paciente_3.edad = 29;
    paciente_3.peso = 88.0;
    paciente_3.altura = 1.80;

    cout << "Nombre paciente: " << paciente_1.nombre << "\n";
    cout << "Edad: " << paciente_1.edad << "\n";
    cout << "Peso: " << paciente_1.peso << "\n";
    cout << "Altura: " << paciente_1.altura << "\n";
    cout << "---------------- \n";

    cout << "Nombre paciente: " << paciente_2.nombre << "\n";
    cout << "Edad: " << paciente_2.edad << "\n";
    cout << "Peso: " << paciente_2.peso << "\n";
    cout << "Altura: " << paciente_2.altura << "\n";
    cout << "---------------- \n";

    cout << "Nombre paciente: " << paciente_3.nombre << "\n";
    cout << "Edad: " << paciente_3.edad << "\n";
    cout << "Peso: " << paciente_3.peso << "\n";
    cout << "Altura: " << paciente_3.altura << "\n";
    cout << "---------------- \n";

}