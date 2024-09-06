
#include <iostream>
#include <string>
#include <fstream>
#include <sstream>
using namespace std;

//estructura
struct Paciente {
    string nombre;
    int edad;
    double altura;
    double peso;
    double azucar;
    double indice;
    Paciente* next; //se agrega puntero
};
// Estructura de la cola
struct Cola {
    Paciente* primero; 
    Paciente* final;  
    int tamanio;       

    // Constructor de la cola
    Cola() {
        primero = nullptr;
        final = nullptr;
        tamanio = 0;
    }
};

// Función para verificar si la cola está vacía o llena
bool estaVacia(Cola& cola) {
    return cola.primero == nullptr;
}

bool estaLlena(Cola& cola) {
    return cola.tamanio == 10;
}



int compararCaracteristicas(double azucar, double indice){
    int gravedad_azucar;
    double gravedad;
    if (azucar < 5.7) 
    {
        gravedad_azucar = 0;
    }
    else if (azucar >= 5.7 && azucar <= 6.5)
    {
        gravedad_azucar = 1;
    }
    else
    {
        gravedad_azucar = 2;

    }
    gravedad = gravedad_azucar * indice;
    return gravedad;
}
//elimina ultimo paciente
void eliminarPacienteFinal(Cola& cola){
     Paciente* actual = cola.primero;
    Paciente* anterior = nullptr;

    while (actual->next != nullptr) {
        anterior = actual;
        actual = actual->next;
    }

    delete actual;
    anterior->next = nullptr;
}
// funcion para encolar
void agregarPacienteCola(Cola& cola, const string& nombre, int edad, double altura, double peso, double azucar) {
    
    if (estaLlena(cola) == true) {
        return;
    }

    Paciente* nuevoPaciente = new Paciente();
    nuevoPaciente->nombre = nombre;
    nuevoPaciente->edad = edad;
    nuevoPaciente->altura = altura;
    nuevoPaciente->peso = peso;
    nuevoPaciente->azucar = azucar;
    nuevoPaciente->indice = peso / (altura * altura);
    nuevoPaciente->next = nullptr;

    double caracteristica = compararCaracteristicas(nuevoPaciente->azucar, nuevoPaciente->indice);
    
    if (estaVacia(cola) == true|| compararCaracteristicas(cola.primero->azucar, cola.primero->indice) > caracteristica ) {
        cola.primero = nuevoPaciente;
        cola.final = nuevoPaciente;
    } else {
        Paciente* actual = cola.primero;
        while (actual->next != nullptr && compararCaracteristicas(actual->next->azucar, actual->next->indice >= caracteristica)) 
        {
            actual = actual->next;
        }
        nuevoPaciente->next = actual->next;
        actual->next = nuevoPaciente;
        cola.tamanio++;
        if (estaLlena(cola) == true){
            eliminarPacienteFinal(cola);
        }
    }

    
}

//funcion para eliminar paciente
void eliminarPacienteCola(Cola& cola){
    if (estaVacia(cola)) {
        cout << "La cola está vacía.\n";
        return;
    }

    Paciente* temp = cola.primero;
    cola.primero = cola.primero->next;
    if (cola.primero == nullptr) {
        cola.final = nullptr;
    }

    cout << "Paciente removido: " << temp->nombre << "\n";
    delete temp;
    cola.tamanio--;
}


//funcion para mostrar todos los paciente
void imprimirPaciente(Cola& cola){
    if (estaVacia(cola)) {
        cout << "La cola está vacía.\n";
        return;
    }

    Paciente* actual = cola.primero;
    while (actual != nullptr) {
        cout << "Nombre paciente: " << actual->nombre << "\n";
        cout << "Edad: " << actual->edad << "\n";
        cout << "Peso: " << actual->peso << "\n";
        cout << "Altura: " << actual->altura << "\n";
        cout << "IMC: " << actual->indice << "\n";
        cout << "A1C: " << actual->azucar << "%\n";
        cout << "---------------- \n" << endl;
        actual = actual->next;        

    }
}

//funcion para buscar pacientes con IMC y A1C
void buscarPacienteNumero(Cola& cola, double cifra, int tipo) {
    Paciente* actual = cola.primero;
    Paciente* anterior = nullptr;
    bool encontrado = false;

    while (actual != nullptr){
        if (tipo == 1 && actual->indice == cifra || tipo == 2 && actual->azucar == cifra)
        {
            cout << "Nombre paciente: " << actual->nombre << "\n";
            cout << "Edad: " << actual->edad << "\n";
            cout << "Peso: " << actual->peso << "\n";
            cout << "Altura: " << actual->altura << "\n";
            cout << "IMC: " << actual->indice << "\n";
            cout << "A1C: " << actual->azucar << "%\n";
            cout << "---------------- \n";
            encontrado = true;
        }
        actual = actual->next;
    }
    if (!encontrado) {
        cout << "No se encontró paciente.\n";
    }
    
}
//buscar paciente por nombre
void buscarPaciente(Cola& cola, const string& nombre) {
    Paciente* actual = cola.primero;
    bool encontrado = false;

    while (actual != nullptr) {
        if (actual->nombre == nombre) {
            cout << "Nombre paciente: " << actual->nombre << "\n";
            cout << "Edad: " << actual->edad << "\n";
            cout << "Peso: " << actual->peso << "\n";
            cout << "Altura: " << actual->altura << "\n";
            cout << "IMC: " << actual->indice << "\n";
            cout << "A1C: " << actual->azucar << "%\n";
            cout << "---------------- \n";
            encontrado = true;
            break; 
        }
        actual = actual->next;
    }

    if (!encontrado) {
        cout << "No se encontró paciente.\n";
    }

}

// Agregar csv
void cargarCsv(Cola& cola, string nombre_archivo)
{
    ifstream archivo(nombre_archivo);
    if (!archivo.is_open()) {
        cout << "No se pudo abrir el archivo " << nombre_archivo << endl;
        return;
    }

    string linea;
    while (getline(archivo, linea)) 
    {
        stringstream ss(linea); 
        string nombre;
        int edad;
        double altura;
        double peso;
        double azucar;
        
        
        getline(ss, nombre, ',');
        ss >> edad;

        ss.ignore(); 
        ss >> altura;
        
        ss.ignore();
        ss >> peso;
        
        ss.ignore();
        ss >> azucar;
        
        agregarPacienteCola(cola, nombre, edad, altura, peso, azucar);

    }

    archivo.close(); 
}


int main () {
    int menu = 1;
    int opcion;


    Cola cola;
    cargarCsv(cola, "patient_list.csv");

    while ( menu != 0)
    {
        cout << "Bienvenido, que desea hacer? \n";
        cout << "0. Salir\n";
        cout << "1. Mostrar informacion \n";
        cout << "2. Eliminar Paciente \n";

        
        cin >> opcion;

        if (opcion == 0)
        {
            break;
        }
           
        //pide selecciona al paciente por el nombre
        else if (opcion == 1)
        {
            int mostrar;
            string seleccion;
            double seleccion_num;
            cout << "1. buscar por nombre\n";
            cout << "2. buscar por IMC\n";
            cout << "3. buscar por A1C\n";
            cout << "4. mostrar todo\n" << endl;
            cin >> mostrar;
            // busca por nombre
            if (mostrar == 1) {
                cout << "Indique el nombre\n" << endl;
                cin >> seleccion;
                buscarPaciente(cola, seleccion);

            }
            //buscar por IMC
            else if (mostrar == 2)
            {
            
                cout << "Indique el IMC\n" << endl;
                cin >> seleccion_num;
                buscarPacienteNumero(cola, seleccion_num, 1);
                
            }
            //buscar por A1C
            else if (mostrar == 3)
            {
            
                cout << "Indique el A1C\n" << endl;
                cin >> seleccion_num;
                buscarPacienteNumero(cola, seleccion_num, 2);
                
            }

            //imprime la totalidad de los pacientes
            else if (mostrar == 4)
            {
                imprimirPaciente(cola);
            }
        
            else
            {
                cout << "numero no valido\n" << endl;
            }
        }


        //elimina pidiendo el nombre del sujeto a eliminar
        else if (opcion == 2)
        {
            eliminarPacienteCola(cola);
        }
         
        
        
        else
        {
            cout << "opcion no valida\n";
        }
               

    }
    //liberar memoria
    while (cola.primero != nullptr) {
        Paciente* temp = cola.primero;
        cola.primero = cola.primero->next;
        delete temp;
    }
    return 0;
    
}
