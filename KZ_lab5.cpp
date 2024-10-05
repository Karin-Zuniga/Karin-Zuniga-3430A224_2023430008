#include <iostream>
#include <fstream>
#include <string>
#include <cstdlib>

#define TRUE 1
#define FALSE 0

enum {IZQUIERDO, DERECHO};

struct Nodo {
    int dato;
    int FE;
    Nodo* derecho;
    Nodo* izquierdo;
    Nodo* padre;
};

typedef Nodo* pNodo;
typedef Nodo* Arbol;

Nodo* CrearNodo(int dato){
    Nodo* nodo1 = new Nodo();
    nodo1->dato = dato;
    nodo1->izquierdo = nullptr;
    nodo1->derecho = nullptr;
    nodo1->padre = nullptr;
    nodo1->FE = 0;
    return nodo1;
}

void RotaIzquierdaIzquierda(Arbol& nodo1, pNodo& nodo){
    nodo->izquierdo = nodo1->derecho;
    nodo->derecho = nodo;
    nodo->FE =0;
    nodo = nodo1;
}
    
//void RotaDerechaDerecha(Arbol* raiz, pNodo nodo);
void RotaDerechaDerecha(Arbol& nodo1, pNodo& nodo){
    nodo->derecho = nodo1->izquierdo;
    nodo1->izquierdo = nodo;
    nodo->FE = 0;
    nodo = nodo1;
}
void RotaDerechaIzquierda(Arbol& nodo1, pNodo& nodo)
{
    pNodo nodo2 = nodo1->izquierdo;
    nodo->derecho = nodo2->izquierdo;
    nodo2->izquierdo = nodo;
    nodo1->izquierdo = nodo2->derecho;
    nodo2->derecho = nodo1;
    if (nodo2->FE ==  1)
    {
        nodo->FE = -1;
    }
    else
    {
        nodo->FE = 0;
    }
    if (nodo1->FE == -1)
    {
        nodo1->FE = 1;
    }
    else
    {
        nodo1->FE = 0;
    }
    nodo = nodo2;
}

void RotaIzquierdaDerecha(Arbol& nodo1, pNodo& nodo){
    pNodo nodo2 = nodo1->derecho;
    nodo->izquierdo = nodo2->derecho;
    nodo2->derecho = nodo;
    nodo1->derecho = nodo2->izquierdo;
    nodo2->izquierdo = nodo1;
    if (nodo2->FE ==-1)
    {
        nodo->FE = 1;
    }
    else
    {
        nodo->FE = 0;
    }
    if (nodo2->FE == 1)
    {
        nodo1->FE =-1;
    }
    else
    {
        nodo1->FE =0;
    }
    nodo = nodo2;
    
}

/* Insertar en arbol ordenado: */
void Insertar(Arbol& a, int dat, bool& crece)
{
    Arbol nodo1 = a; 
    if (a != nullptr)
    {
        if (dat < a->dato)
        {
            Insertar(a->izquierdo,dat, crece);
            if (crece == true)
            {
                switch (a->FE)
                {
                case 1:
                    a->FE = 0;
                    crece = false;
                    break;
                case 0:
                    a->FE = -1;
                    break;
                case -1:
                    nodo1 = a->izquierdo;
                    break;
                }
                if (nodo1->FE <=0)
                {
                    RotaIzquierdaIzquierda(nodo1, a);
                }
                else
                {
                    RotaIzquierdaDerecha(nodo1, a);
                }
                
                a->FE = 0;
                crece = false;                
                
            
            }
        
        }
        else
        {
            if(dat > a->dato){
                Insertar(a->derecho, dat, crece);
                if (crece == true)
                {
                    switch (a->FE)
                    {
                    case -1:
                        a->FE = 0;
                        crece = false;
                        break;
                    
                    case 0:
                        nodo1->FE = 1;
                        break;
                    
                    case 1:
                        nodo1 = a->derecho;
                        break;
                    }
                    if (nodo1->FE >= 0)
                    {
                        RotaDerechaDerecha(nodo1, a);

                    }
                    else
                    {
                        RotaDerechaIzquierda(nodo1, a);
                    }
                    
                    
                }
                
            
            }
            
            else
            {
                std::cout << "La informacion ya se encuentra en el arbol" << std::endl; 
            }
        }
        
    }
    else
    {
        a = CrearNodo(dat);
        a->dato = dat;
        a->izquierdo = nullptr;
        a->derecho = nullptr;
        a->FE = 0;
        crece = true;      
    }
    
}

/* reestructura izquierda */
void reestruct_izq(Arbol& nodo, bool& crece)
{
    Arbol nodo1 = nodo;
    if (crece == true)
    {   
        switch (nodo->FE)
        {
        case -1:
            nodo->FE = 0;
            break;
        case 0:
            nodo->FE = 1;
            crece = false;
            break;
        case 1:
            nodo1 = nodo->derecho;
            break;
        }
        if (nodo->FE>= 0)
        {
            RotaDerechaDerecha(nodo1, nodo);
        }
        else
        {
            RotaDerechaIzquierda(nodo1, nodo);
        }   
    }
}

/* reestructura derecha */
void reestruct_der(Arbol& nodo, bool& crece)
{
    Arbol nodo1 = nodo;
    if (crece == true)
    {   
        switch (nodo->FE)
        {
        case 1:
            nodo->FE = 0;
            break;
        case 0:
            nodo->FE = 1;
            crece = false;
            break;
        case -1:
            nodo1 = nodo->derecho;
            break;
        }
        if (nodo->FE>= 0)
        {
            RotaDerechaDerecha(nodo1, nodo);
        }
        else
        {
            RotaDerechaIzquierda(nodo1, nodo);
        }   
    }
}
/* Borrar un elemento: */
void Borrar(Arbol& a, int dat, bool& crece){

    if (a != nullptr)
    {
        if (dat < a->dato)
        {
            Borrar(a->izquierdo, dat, crece);
            reestruct_izq(a, crece);
        }
        else
        {
            if (dat > a->dato)
            {
                Borrar(a->derecho, dat, crece);
                reestruct_der(a, crece);
            }
            else
            {
                Arbol otro = a;
                crece = true;
                if (otro->derecho == nullptr)
                {
                    a = otro->izquierdo;
                }
                else
                {
                    if (otro->izquierdo == nullptr)
                    {
                        a = otro->derecho;
                    }
                    else
                    {
                        Arbol aux = a->izquierdo;
                        bool boleano = false;
                        while (aux->derecho != nullptr)
                        {
                            Arbol aux1 = aux;
                            aux = aux1->derecho;
                            boleano = true;
                        }
                        a->dato = aux->dato;
                        otro = aux;
                        if (boleano == true)
                        {
                            aux->derecho = aux->izquierdo;
                        }
                        else
                        {
                            a->izquierdo = aux->izquierdo;
                        }    
                    reestruct_der(a->izquierdo, crece);
                    }
                }
            delete otro;
            }
        }
        
    }
    else
    {
        std::cout << "La informacion no se encuentra en el arbol" << std::endl;
    }
    
    
}
/* Funcion de busqueda: */
int Buscar(Arbol a, int dat);
/* Comprobar si es un nodo hoja: */
int EsHoja(pNodo r);
/* Contar numero de nodos: */
int NumeroNodos(Arbol a, int* c);
/* Calcular la altura de un arbol: */
int AlturaArbol(Arbol a, int* altura);
/* Calcular altura de un dato: */
int Altura(Arbol a, int dat);
/* Generar salida para Graphiz */
void PreOrden(Arbol, std::ofstream &fp);

// Funciones de equilibrado:
void Equilibrar(Arbol raiz, pNodo nodo, int, int);

/* Funciones auxiliares: */
void Podar(Arbol* a);
void auxContador(Arbol a, int*);
void auxAltura(Arbol a, int, int*);

void MenuPrincipal();
void GenerarGrafo(Arbol);

int main() {
    Arbol ArbolInt = nullptr;
    bool crece = false;
    int opcion = 0;
    int valor;

    while (opcion != 6) {
        MenuPrincipal();
        std::cout << "Ingrese su opcion: ";
        std::cin >> opcion;

        switch (opcion) {
            case 1:
                std::cout << "Ingrese su numero: ";
                std::cin >> valor;
                Insertar(ArbolInt, valor, crece);
                break;
            case 3:
                std::cout << "numero a eliminar" << std::endl;
            case 5:
                GenerarGrafo(ArbolInt);
                break;
        }
    }

    /* Liberar memoria asociada al arbol. */
    Podar(&ArbolInt);
    return 0;
}

void GenerarGrafo(Arbol ArbolInt) {
    std::ofstream fp("grafo.txt");

    fp << "digraph G {\n";
    fp << "node [style=filled fillcolor=yellow];\n";

    fp << "nullraiz [shape=point];\n";
    fp << "nullraiz->" << ArbolInt->dato << " [label=" << ArbolInt->FE << "];\n";
    PreOrden(ArbolInt, fp);

    fp << "}\n";
    fp.close();

    system("dot -Tpng -ografo.png grafo.txt");
    system("eog grafo.png &");
}

void MenuPrincipal() {
    std::cout << "\n";
    std::cout << "<1> Ingresar numero\n";
    std::cout << "<2> Busqueda numero\n";
    std::cout << "<3> Eliminar numero\n";
    std::cout << "<4> Modificar elemento ingresado\n";
    std::cout << "<5> Generar Grafo\n";
    std::cout << "<6> Salir\n";
    std::cout << "\n";
}

void Podar(Arbol* a) {
    if (*a) {
        Podar(&(*a)->izquierdo);
        Podar(&(*a)->derecho);
        free(*a);
        *a = NULL;
    }
}


void Equilibrar(Arbol* a, pNodo nodo, int rama, int nuevo) {
    int salir = FALSE;

    while (nodo && !salir) {
        if (nuevo){
            if (rama == IZQUIERDO){
                nodo->FE -= 1;
            } else {
                nodo->FE += 1;
            }
        }
        else{
            if (rama == IZQUIERDO){
                nodo->FE += 1;
            } 
            else {
                nodo->FE -= 1;
            }
        }

        if (nodo->FE == 0)
            salir = TRUE;
        else if (nodo->FE == -2) {
            if (nodo->izquierdo->FE == 1)
                RotaIzquierdaDerecha(*a, nodo);
            else
                RotaIzquierdaIzquierda(*a, nodo);
            salir = TRUE;
        } else if (nodo->FE == 2) {
            if (nodo->derecho->FE == -1)
                RotaDerechaIzquierda(*a, nodo);
            else
                RotaDerechaDerecha(*a, nodo);
            salir = TRUE;
        }

        if (nodo->padre) {
            if (nodo->padre->derecho == nodo) {
                rama = DERECHO;
            } else {
                rama = IZQUIERDO;
            }
        }
        nodo = nodo->padre;
    }
}

void PreOrden(Arbol a, std::ofstream &fp) {
    if (a) {
        fp << a->dato << ";\n";
        if (a->izquierdo) {
            fp << a->dato << "->" << a->izquierdo->dato << ";\n";
            PreOrden(a->izquierdo, fp);
        }
        if (a->derecho) {
            fp << a->dato << "->" << a->derecho->dato << ";\n";
            PreOrden(a->derecho, fp);
        }
    }
}