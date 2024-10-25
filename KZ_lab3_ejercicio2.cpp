#include <iostream>
#include <string>

using namespace std;

struct Contenedor
{
    string codigo;
    Contenedor* next;
};

struct Pila
{
    Contenedor* contenedores;
    int num_cont_utilizados;
    int capacidad;
    
    Pila(int num_cont): capacidad(num_cont), num_cont_utilizados(0){
        contenedores = new Contenedor[capacidad];
    } 

    bool pila_llena(){
        return num_cont_utilizados == capacidad;
    }

    bool pila_vacia(){
        return num_cont_utilizados == 0;
    }
    

    void push(const Contenedor& contenedor){
        
        if (pila_llena() == true)
        {
            cout << "Desbordamiento, Pila llena\n";
            return;
        }

        num_cont_utilizados = num_cont_utilizados + 1;
        contenedores[num_cont_utilizados] = contenedor;
        
    }

    Contenedor pop(const Contenedor*& contenedor) {
        if (pila_vacia) {
            cout << "Subdesbordamiento, Pila vacia." << endl;
            return;
        }

        if (!contenedor->next)
        {
            delete contenedor;
            contenedor = NULL;
            num_cont_utilizados = num_cont_utilizados - 1;
            return;

            
        } 
        
    }
};


class Area
{
public:
    int num_cont, max_pilas;

    void ingresar_contenedor(){
        string codigo;
        cout << "Ingrese el codigo \n";
        cin >> codigo;
        Contenedor cont;
        cont.codigo = codigo;
        
        
    }
    void retirar_contenedor(){
        return;
    }
    void mostrar_contenedores(){
        return;
    }

};



/*--------------main-------------------*/
int main()
{
    int n, m;
    int menu = 1;
    cout << "Ingrese el maximo de contenedores (n): ";
    cin >> n;
    cout << "Ingrese el maximo de pilas (m): ";
    cin >> m;
    Area nueva_area;
    nueva_area.num_cont = n;
    nueva_area.max_pilas = m;
    


    while (menu != 0)
    {
        int opcion;

        cout << "\nMenu:\n";
        cout << "1. Ingresar contenedor\n";
        cout << "2. Retirar contenedor\n";
        cout << "3. Mostrar contenedores\n";
        cout << "4. Salir\n";
        cout << "Ingrese una opcion: ";
        cin >> opcion;

        switch (opcion)
        {
        case 1:
            nueva_area.ingresar_contenedor();
            
        case 2:
            nueva_area.retirar_contenedor();
            
        case 3:
            nueva_area.mostrar_contenedores();

        case 4:
            break;
        
        default:
            cout << "opcion no valida" << endl;
        }

    }
    




    return 0;
}
