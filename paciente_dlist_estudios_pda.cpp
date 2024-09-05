#include <iostream>
#include <string>
#include <fstream>
#include <sstream>
using namespace std;

//estructura
struct Paciente {
    string nombre;
    int edad;
    double peso;
    double altura;
    double indice;
    Paciente* next; //se agrega puntero
};
//Funcion para agregar
void agregarPaciente(Paciente*& head, const string& nombre, int edad, double peso, double altura){
    Paciente* nuevoPaciente = new Paciente();
    nuevoPaciente->nombre = nombre;
    nuevoPaciente->edad = edad;
    nuevoPaciente->peso = peso;
    nuevoPaciente->altura = altura;
    nuevoPaciente->indice = peso / (altura*altura);
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
//funcion para mostrar todos los paciente
void imprimirPaciente(const Paciente* head){
    const Paciente* actual = head;
    while (actual != nullptr) {
        cout << "Nombre paciente: " << actual->nombre << "\n";
        cout << "Edad: " << actual->edad << "\n";
        cout << "Peso: " << actual->peso << "\n";
        cout << "Altura: " << actual->altura << "\n";
        cout << "IMC: " << actual->indice << "\n";
        cout << "---------------- \n";
        actual = actual->next;        

    }
}

//funcion para buscar pacientes
void buscarPaciente(Paciente*& head, const string& nombre) {
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
        cout << "Nombre paciente: " << actual->nombre << "\n";
        cout << "Edad: " << actual->edad << "\n";
        cout << "Peso: " << actual->peso << "\n";
        cout << "Altura: " << actual->altura << "\n";
        cout << "IMC: " << actual->indice << "\n";
        cout << "---------------- \n";
        actual = actual->next;
        
        
    }
}
//calcula y entrega promedio de peso o edad
void promedio(Paciente*&head, string caracteristica){
    const Paciente* actual = head;
    int suma;
    int contador;
    contador = 0;
    suma = 0;
    double promedio;


    while (actual != nullptr){
        if (caracteristica == "peso")
        {
            suma = suma + actual->peso;
            contador += 1;
            actual = actual->next;
        }
        else if (caracteristica == "edad")
        {
            suma = suma + actual->edad;
            contador += 1;
            actual = actual->next;
        }
        else
        {
            cout << "Algo no funciono \n";
        }

    }
    promedio = suma / contador;

    if (caracteristica == "peso")
    {
        cout << "El promedio de peso es: " << promedio << " \n";
        
    }
    else if (caracteristica == "edad")
    {
        cout << "El promedio de edad es: " << promedio << " \n";
      
    }
    else
    {
        cout << "Algo no funciono \n";
    } 
    
}

// Agregar csv
void cargarCsv(Paciente*&head, string nombre_archivo)
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
        
        
        getline(ss, nombre, ',');
        ss >> edad;

        ss.ignore(); 
        ss >> altura;
        
        ss.ignore();
        ss >> peso;
        
        agregarPaciente(head, nombre, edad, peso, altura);
    }

    archivo.close(); 
}


int main () {
    int menu = 1;
    int opcion;
    
    Paciente* head = nullptr;
    agregarPaciente(head, "Alicia", 23, 59.5, 1.60);
    agregarPaciente(head, "Maria", 76, 67.5, 1.65);
    agregarPaciente(head, "Juan", 43, 67.3, 1.8);

    while ( menu != 0)
    {
        cout << "Bienvenido, que desea hacer? \n";
        cout << "0. Salir\n";
        cout << "1. Agregar Paciente \n";
        cout << "2. Mostrar informacion \n";
        cout << "3. Eliminar Paciente \n";
        cout << "4. Promedio de edad \n";
        cout << "5. Promedio de peso \n";
        cout << "6. Cargar csv \n" << endl;
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
        //pide selecciona al paciente por el nombre
        else if (opcion == 2)
        {
            int mostrar;
            string seleccion;
            cout << "1. buscar por nombre\n";
            cout << "2. mostrar todo\n" << endl;
            cin >> mostrar;
            // busca por nombre
            if (mostrar == 1) {
                cout << "Indique el nombre\n" << endl;
                cin >> seleccion;
                buscarPaciente(head, seleccion);

            }
            //imprime la totalidad de los pacientes
            else if (mostrar == 2)
            {
                imprimirPaciente(head);
            }
            else
            {
                cout << "numero no valido\n" << endl;
            }
        }


        //elimina pidiendo el nombre del sujeto a eliminar
        else if (opcion == 3)
        {
            string nombre;
            cout << "Indique el nombre\n";
            cin >> nombre;

            eliminarPaciente(head, nombre);
        }
        else if (opcion == 4)
        {
            promedio(head, "edad");
        }
        else if (opcion == 5)
        {
            promedio(head, "peso");
        }
        else if (opcion == 6)
        {
            string nombre_archivo;
            cout << "Ingrese el nombre del archivo: \n";
            cin >> nombre_archivo;
            cargarCsv(head, nombre_archivo);
        }
        else
        {
            cout << "opcion no valida\n";
        }
        
        
        
        
            
            
                      
        
        

    }
    //liberar memoria
    while (head != nullptr) {
        Paciente* temp = head;
        head = head->next;
        delete temp;
    }
    return 0;
    
}
