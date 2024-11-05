#include <iostream>
#include <cstring>
#include <ctype.h>

struct Nodo 
{
    int numero;
    Nodo* siguiente;
};

/* La funcion hash principal, donde registro es el numero ingresado al insertar*/
int funcion_hash(int registro, int largo){
    int posicion = (registro % largo);    
    return posicion;
}
class TablaHash
{
public:
    Nodo** tabla_hash;
    TablaHash(int largo)
    {
        tabla_hash = new Nodo*[largo];

    }

    void insertar_a_tabla(int largo)
    {
        int ingreso;
        int posicion;
        std::cout << "Ingrese numero distinto de 0" << std::endl;
        std::cin >> ingreso;
        if (ingreso == 0) 
        {
            std::cout << "Numero invalido. Por favor, ingrese un numero distinto de 0." << std::endl;
            return;
        }
        posicion = funcion_hash(ingreso, largo);
        busqueda_tabla(ingreso, largo);
        Nodo* nuevo_ingreso = new Nodo;
        nuevo_ingreso->numero = ingreso;
        nuevo_ingreso->siguiente = nullptr;
        if (tabla_hash[posicion] == nullptr)
        {
            tabla_hash[posicion] = nuevo_ingreso;
            std::cout << "Numero " << ingreso << " insertado en la posicion " << posicion << std::endl;
        }
        else
        {
            std::cout << "Colision encontrada" << std::endl;
            encadenamiento(nuevo_ingreso, posicion);
        }
        mostrar_tabla(largo);
        int opcion_otro_ingreso;
        std::cout << "Desea agregar otro numero" << std::endl;
        std::cout << "1. si" << std::endl;
        std::cout << "2. no" << std::endl;
        std::cin >> opcion_otro_ingreso;
        std::cout << std::endl;
        if (opcion_otro_ingreso == 1)
        {
            insertar_a_tabla(largo);
        }
        else if (opcion_otro_ingreso == 2)
        {
            std::cout << "Saliendo..." << std::endl;
            return;
        }
        else
        {
            
            std::cout << "Opcion no valida" << std::endl;
            std::cout << "Saliendo..." << std::endl;
            return;
        }
        
    }

    void mostrar_tabla(int largo){
        for (int i = 0; i < largo; i++)
        {
            std::cout << "Posicion " << i << ": ";
            Nodo* temp = tabla_hash[i];
            if (temp == nullptr)
            {
                std::cout << " Vacio " << std::endl;
            }
            else
            {
                while (temp != nullptr)
                {
                    std::cout << temp->numero << " , " ;
                    temp = temp->siguiente;
                }
                std::cout << std::endl;   
            }    
        }   
    }

    void encadenamiento(Nodo* nodo, int posicion){
        Nodo* temp = tabla_hash[posicion];
        while (temp->siguiente != nullptr)
        {
            temp = temp->siguiente; 
        }
        temp ->siguiente = nodo;
        std::cout << "Número " << nodo->numero << " insertado en la posición " << posicion << std::endl;
    }

    bool busqueda_tabla(int numero_a_buscar, int largo){
        int indice = funcion_hash(numero_a_buscar, largo);
        Nodo* temp = tabla_hash[indice];
        while (temp != nullptr)
        {
            if (temp->numero == numero_a_buscar)
            {
                std::cout << "Se ha encontrado " << numero_a_buscar << "en posicion " << indice << std::endl;
                return true;
            }
        }   
        std::cout << "No se ha encontrado " << numero_a_buscar << "en la tabla" << std::endl;
        return false;
    }
};
/*Funciones para verificar si es primo, utilizadas para la nueva funcion hash en la doble direccion hash*/
bool es_primo(int n) {
    if (n <= 1) return false;
    for (int j = 2; j * j <= n; ++j) 
    { 
        if (n % j == 0) return false;
    }
    return true;
}

int previo_primo(int largo) {
    int i = largo; 
    while (true) {
        if (es_primo(i)) {
            return i; 
        }
        i--;
    }
}
/* Segunda funcion hash para evaluar doble direccion hash. Toma el primo previo a la clave del numero a insertar para definir su desplazamiento*/
int segundo_hash(int clave, int largo){
    int primo = previo_primo(largo);
    int nuevo_hash = primo - (clave / primo);
    return nuevo_hash;
}

void mostrar(int* arr, int largo){
    
    for (int i = 0; i < largo; i++)
    {
        std::cout << arr[i] << " , "; 
    }
}

void prueba_lineal(int* arr, int registro, int posicion, int largo){
    int i = posicion;
    while (true)
    {
        /*se ubica en posicion 0 una vez que a recorrido todos los numeros superiores*/
        if (i >= largo)
        {
            i = 0;
        }
    /*llega a la siguiente posicion vacia*/
        if (arr[i] == 0)
        {
            arr[i] = registro;
            std::cout << "Se ha ubicado " << registro <<" en posicion " << i << std::endl;
            break;
        }

        i += 1;
        /*si no quedan posiciones vacias (vuelve a su numero original), informa al usuario y rompe el ciclo*/
        if (i == posicion)
        {
            std::cout << "No hay espacio disponible." << std::endl;
            break;
        }       
    }
}

bool busqueda_lineal(int* arr, int numero_a_buscar, int largo){
    int indice = funcion_hash(numero_a_buscar, largo);
    int i = indice;
    while (arr[i] != 0)
    {
        if (arr[i] == numero_a_buscar)
        {
            std::cout <<  "Se ha encontrado " << numero_a_buscar << " en posicion " << i << std::endl;
            return true;
        }

        i = (i + 1)%largo;    
    }  
    return false;
}

int indice_cuadratico(int posicion, int i, int largo){
    int indice = (posicion + (i^2)) % largo;
    return indice;    
}

void prueba_cuadratica(int* arr, int registro, int posicion, int largo){
    int i = 0;
    int nueva_posicion = posicion;
    while (true)
    {
        /*define la nueva posicion segun la formula*/
        nueva_posicion = indice_cuadratico(posicion, i, largo);
        /*se ubica cuando encuentra una posicion vacia*/
        if (arr[nueva_posicion] == 0)
        {
            arr[nueva_posicion] = registro;
            std::cout << "Se ha ubicado " << registro <<" en posicion " << nueva_posicion << std::endl;
            break;
        }

        i += 1;
        
        if (posicion == nueva_posicion)
        {
            std::cout << "No hay espacio disponible." << std::endl;
            break;
        }       
    }
}

bool busqueda_cuadratica(int* arr, int numero_a_buscar, int largo) {
    int indice = funcion_hash(numero_a_buscar, largo);
    if (arr[indice] == numero_a_buscar)
    {
        std::cout << "El numero " << numero_a_buscar << " se encuentra en la posicion " << indice << std::endl;
        return true;               
    }
    
    int siguiente_posicion = indice;
    int i = 1;
    while (arr[indice] != 0)
    {
        if (arr[indice] == numero_a_buscar)
        {
            std::cout << "El numero " << numero_a_buscar << " se encuentra en la posicion " << indice << std::endl;
            return true;
        }
        siguiente_posicion = indice_cuadratico(indice, i, largo);
        i += 1;
        if (siguiente_posicion == indice)
        {
            break;
        }
        
    }
    return false;    
}

void doble_direccion_hash(int* arr,int registro, int posicion, int largo){
    int nueva_clave = posicion;
    int i = 1;
    /*calcula desplazamiento con el segundo hash*/
    int desplazamiento = segundo_hash(posicion, largo);
    while (i < largo)
    {
        /*selecciona nueva posicion*/
        nueva_clave = (nueva_clave + desplazamiento) % largo;
        /*busca posicion y se agrega ahi si esta vacio*/
        if (arr[nueva_clave] == 0)
        {
            arr[nueva_clave] = registro;
            std::cout << "Número " << registro << " insertado en la posición " << nueva_clave << std::endl;
            break;
        }
        i += 1;
        if (i == largo)
        {
            std::cout << "No hay espacio disponible." << std::endl;
            break;
        }           
    }    
}

bool busqueda_doble_hash(int* arr, int numero_a_buscar, int largo){
    int posicion = funcion_hash(numero_a_buscar, largo);
    if (arr[posicion] == numero_a_buscar)
    {
        std::cout << "Numero " << numero_a_buscar << " encontrado en la posicion " << posicion << std::endl;
        return true;
    }
    int nueva_clave = posicion;
    int desplazamiento = segundo_hash(posicion, largo);
    int i = 1;
    while (true)
    {
        nueva_clave = (nueva_clave + desplazamiento) % largo;
        i += 1;
        if (nueva_clave == posicion)
        {
            break;
        }
        
    }  
    return false; 
}


void insertar(int* arr, int largo, char metodo){
    int ingreso;
    std::cout << "Ingrese numero distinto de 0" << std::endl;
    std::cin >> ingreso;
    if (ingreso == 0) {
        std::cout << "Número inválido. Por favor, ingrese un número distinto de 0." << std::endl;
        return;
    }
    if (metodo == 'L')
    {
        bool repetido = busqueda_lineal(arr, ingreso, largo);
        if (repetido == true)
        {
            return;
        }
        
    }
    else if (metodo == 'C')
    {
        bool repetido = busqueda_cuadratica(arr, ingreso, largo);
        if (repetido == true)
        {
            return;
        }
    }
    else if (metodo == 'D')
    {
        bool repetido = busqueda_doble_hash(arr, ingreso, largo);
        if (repetido == true)
        {
            return;
        }
    }

    int posicion = funcion_hash(ingreso, largo);
    if (arr[posicion] != 0)
    {
        std::cout << "Colision encontrada para: " << ingreso << " en posicion " << posicion << std::endl;
        if (metodo == 'L') {
            prueba_lineal(arr, ingreso, posicion, largo);
        } 
        else if (metodo == 'C') {
            prueba_cuadratica(arr, ingreso, posicion, largo);
        }
        else if (metodo == 'D') {
            doble_direccion_hash(arr, ingreso, posicion, largo);
        }
    }
    else
    {
        arr[posicion] = ingreso;
        std::cout << "Número " << ingreso << " insertado en la posición " << posicion << std::endl;
    }
    mostrar(arr, largo);
    int opcion_otro_ingreso;
    std::cout << std::endl;
    std::cout << "Desea agregar otro numero" << std::endl;
    std::cout << "1. si" << std::endl;
    std::cout << "2. no" << std::endl;
    std::cin >> opcion_otro_ingreso;
    std::cout << std::endl;
    if (opcion_otro_ingreso == 1)
    {
        insertar(arr, largo, metodo);
    }
    else if (opcion_otro_ingreso == 2)
    {
        std::cout << "Saliendo..." << std::endl;
        return;
    }
    else
    {
        
        std::cout << "Opcion no valida" << std::endl;
        std::cout << "Saliendo..." << std::endl;
        return;
    }
    
        
}

void buscar(char metodo, int largo, int *arr, TablaHash tabla){
    int numero_a_buscar;
    std::cout << "Ingrese numero" << std::endl;
    std::cin >> numero_a_buscar;
    if (metodo == 'L')
    {
        bool numero = busqueda_lineal(arr, numero_a_buscar, largo);
        if (numero == false)
        {
            std::cout << "El numero " << numero_a_buscar << " no se encuentra en la tabla" << std::endl;
        }      
    }
    else if (metodo == 'C')
    {
        bool numero = busqueda_cuadratica(arr, numero_a_buscar, largo);
        if (numero == false)
        {
            std::cout << "El numero " << numero_a_buscar << " no se encuentra en la tabla" << std::endl;
        }
    }
    else if (metodo == 'D')
    {
        bool numero = busqueda_doble_hash(arr, numero_a_buscar, largo);
        if (numero == false)
        {
            std::cout << "El numero " << numero_a_buscar << " no se encuentra en la tabla" << std::endl;
        }
    }    
    else
    {
        tabla.busqueda_tabla(numero_a_buscar, largo);
    }
    
}

    
void menu( int *arr, int largo, char metodo, TablaHash tabla){

    int n = 3;
    while (n !=0)
    {
        int opcion;
        std::cout << "Bienvenido, que desea hacer?" << std::endl;
        std::cout << "1. Insertar" << std::endl;
        std::cout << "2. Buscar" << std::endl;
        std::cout << "3. Mostrar arreglo" << std::endl;
        std::cout << "0. Salir" << std::endl;
        std::cin >> opcion;
        n = opcion;
        
        if (opcion == 1)
        {        
            if (metodo == 'E')
            {
                tabla.insertar_a_tabla(largo);
            }
            else
            {
                insertar(arr, largo, metodo);
            }
            
        }
        else if (opcion == 2)
        {
            buscar(metodo, largo, arr, tabla);
        }
        else if (opcion == 3)
        {
            if (metodo == 'E')
            {
                tabla.mostrar_tabla(largo);
            }
            else
            {
                mostrar(arr, largo);
            }
        }
        else if (opcion == 0)
        {
            break;
        }
        else
        {
            std::cout << "opcion no valida" << std::endl;
        }
    }
}

void hash(char *metodo){
    if (strcmp(metodo, "L") == 0) {
        // Implementar encadenamiento
    } else if (strcmp(metodo, "C") == 0) {
        // Implementar direccionamiento abierto
    } else if (strcmp(metodo, "D") == 0) {
        // Implementar doble hashing
    } else if (strcmp(metodo, "E") == 0) {
        // Implementar otro método
    } else {
        printf("Método no válido. Usa L, C, D o E.\n");
    }
}



int main(int argc, char *argv[]) {
    
    if (argc != 2) {
        std::cout << "Uso: ./hash {L|C|D|E}" << std::endl;
        return 1;
    }

    int largo;
    std::cout << "ingrese el largo del arreglo" << std::endl;
    std::cin >> largo;
    std::cout << std::endl;
    
    TablaHash* tabla = new TablaHash(largo);
    int* arr = new int[largo]();
    
    char metodo = argv[1][0];
    if (metodo != 'L' && metodo != 'C' && metodo != 'D' && metodo != 'E') {
        std::cout << "Opcion no valida." << std::endl;
        return 1;
    }
    menu(arr, largo, metodo, *tabla);
 
    return 0;
}
