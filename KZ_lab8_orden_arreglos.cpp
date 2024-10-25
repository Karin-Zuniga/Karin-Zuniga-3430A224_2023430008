#include <chrono> // para calcular duracion del metodo
#include <iostream>
#include <cstdlib> // Para rand() y srand()


/* cambia las posiciones de los arreglos (intercambia arr[i] por arr[i_max]) . Para usar en quicksort*/
void cambia_indices(int i_max, int* arr, int i){

    int aux = arr[i_max];
    arr[i_max] = arr[i];
    arr[i] = aux;
}

/*metodo seleccion*/
void seleccion(int* arr, int tamano){
    /*Selecciona el numero a comparar*/
    for (int j = 0; j < tamano; j++)
    {
        /* compara con el siguiente numero. El anterior ya se encuentra fijo*/
        for (int i = j + 1; i < tamano; i++)
        {
            if (arr[i] < arr[j])
            {
                cambia_indices(j, arr,  i);
            }  
        } 
    
    }
}


/*metodo quicksort*/
void quicksort(int* arr, int tamano, int inicio){
    if (inicio >= tamano - 1)
    {
        return;
    }
    

    int pivote = arr[tamano - 1]; // escoge ultimo numero como pivote

    int i_max_izq = inicio; 

    for (int i = inicio; i < tamano - 1; i++)
    {   
        if (arr[i] < pivote)
        {   
            cambia_indices(i_max_izq, arr, i); //intercambia numeros
            i_max_izq = i_max_izq + 1;
        }

    }
    cambia_indices(i_max_izq, arr, tamano - 1);
    
    quicksort(arr, i_max_izq, inicio);
    quicksort(arr, tamano, i_max_izq + 1);
    
        
}

void llenarArreglo(int* arr, int size) {
    // Llenar el arreglo con numeros aleatorios entre 1 y 100
    for (int i = 0; i < size; ++i) {
        arr[i] = rand() % 100 + 1; // Genera un numero entre 1 y 100
    }
}

void mostrarArreglo(int* arr, int size) {
    // Mostrar los valores del arreglo
    std::cout << std::endl;
    for (int i = 0; i < size; ++i) {
        std::cout << arr[i] << " ";
    }
    std::cout << std::endl;
}

int main() {
    const int SIZE_tmp = 1000; // Tamano maximo predefinido del arreglo
    int arr[SIZE_tmp];
    int arr_quicksort[SIZE_tmp];

    int SIZE;
    std::cout << "Tamano del arreglo (n<1000): ";
    std::cin >> SIZE;

    // Inicializa la semilla para numeros aleatorios
    srand(static_cast<unsigned int>(time(0)));

    // ------------------------------------------

    // Llamar a la funcion para llenar el arreglo
    llenarArreglo(arr, SIZE);

    std::cout << "Arreglo de numeros enteros:\n";
    // Llamar a la funcion para mostrar el arreglo
    mostrarArreglo(arr, SIZE);


    /*----------------Aqui empieza el metodo de seleccion-----------*/

    auto start_1 = std::chrono::high_resolution_clock::now();
    
    // llamar metodo seleccion
    seleccion(arr, SIZE);
    auto end_1 = std::chrono::high_resolution_clock::now();
    std::chrono::duration<double> duration_1 = (end_1 - start_1)*1000;

    std::cout << "\nPost Metodo seleccion:\n";
    
    // Llamar a la funcion para mostrar el arreglo
    mostrarArreglo(arr, SIZE);

    std::cout << "\nTiempo de ejecucion: " << duration_1.count() << "ms " << std::endl;

/*-----------------crear segundo arreglo y mostrarlo--------------*/

    // Llamar a la funcion para llenar el arreglo
    llenarArreglo(arr_quicksort, SIZE);

    std::cout << "\nArreglo de numeros enteros:\n";
    // Llamar a la funcion para mostrar el arreglo
    mostrarArreglo(arr_quicksort, SIZE);

/*-------------------AQUI EMPIEZA QUICKSORT------------------------------*/
    auto start_2 = std::chrono::high_resolution_clock::now();
    
    // llamar metodo quicksort
    quicksort(arr_quicksort, SIZE, 0);

    auto end_2 = std::chrono::high_resolution_clock::now();
    std::chrono::duration<double> duration_2 = (end_2 - start_2)*1000;

    std::cout << "\nPost Metodo quicksort:\n";
    
    // Llamar a la funcion para mostrar el arreglo
    mostrarArreglo(arr_quicksort, SIZE);
    
   std::cout << "\nTiempo de ejecucion: " << duration_2.count() << "ms " << std::endl;
    return 0;
}