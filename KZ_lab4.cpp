#include <fstream>
#include <iostream>
using namespace std;

struct Node
{
    int info;
    Node* left;
    Node* right;
};

Node* createNode(int data) {
    Node* newNode = new Node;
    newNode->info = data;
    newNode->left = nullptr;
    newNode->right = nullptr;
    return newNode;
}

class Arbol 
{ 
private:
    Node* root = nullptr;

    // Metodo recursivo privado para insertar un nodo en el arbol binario de busqueda
    Node* insertNode(Node* node, int data) {
        if (node == nullptr) {
            // Crear un nuevo nodo si se encuentra una posicion vacia
            return createNode(data);
        }

        if (data < node->info) {
            // Insertar en el subarbol izquierdo
            node->left = insertNode(node->left, data);
        } else if (data > node->info) {
            // Insertar en el subarbol derecho
            node->right = insertNode(node->right, data);
        } else {
            // El dato ya esta en el arbol
            cout << "El nodo ya se encuentra en el árbol: " << data << endl;
        }

        return node;
    }

    // Eliminar dato
    Node* eliminaNodo(Node* node, int data) const 
    {
        if (node == nullptr)
        {
            return node;
        }
        else if (data < node->info )
        {
            node->left = eliminaNodo(node->left, data);
        }
        else if (data > node->info )
        {
            node->right = eliminaNodo(node->right, data);
        }
        else
        {
            if (node->left == nullptr && node->right == nullptr)
            {
                free(node);
                node = nullptr;
            }
            else if (node->left == nullptr)
            {
                Node* temp = node;
                node = node->right;
                free(temp);
            }
            else if (node->right == nullptr)
            {
                Node* temp = node;
                node = node->left;
                free(temp);
            }
            else
            {
                Node* temp = node->right;
                while (temp->left != nullptr)
                {
                    temp = temp->left;
                }
                node->info = temp->info;
                node->right = eliminaNodo(node->right, temp->info);
            }
            
        }
        
        return node; 
    }


    //Modificar dato
    Node* modifyValue(Node* node, int old_data, int new_data)
    {
        if (node == nullptr)
        {
            Node* new_node = createNode(new_data);
            cout << "Arbol vacio, se ha creado arbol " << new_data << endl;
            return new_node;
        }

        
        node = eliminaNodo(node, old_data);
        node = insertNode(node, new_data);
    
        return node;            
    

    }       
        
    

     // Metodo recursivo privado para imprimir el arbol en preorden
    void printPreOrder(Node* node) const {
        if (node == nullptr) {
            return;
        }
        cout << node->info << " "; // Imprimir el dato del nodo actual
        printPreOrder(node->left);  // Recorrer el subarbol izquierdo
        printPreOrder(node->right); // Recorrer el subarbol derecho
    }

    void printInOrder(Node* node) const {
        if (node == nullptr) {
            return;
        }
        printInOrder(node->left);
        cout << node->info << " ";
        printInOrder(node->right);
    }      
        
    void printPostOrder(Node* node) const {
        if (node == nullptr) {
            return;
        }
        printPostOrder(node->left);
        printPostOrder(node->right);
        cout << node->info << " ";
    }


public:

    Arbol() : root(nullptr) {}
    

    // Metodo publico para insertar un nodo en el arbol
    void insert(int data) {
        root = insertNode(root, data);
        cout << "Insertando: " << data << endl;
    }

    void eliminar(int data) const {
        eliminaNodo(root, data);
        cout << "Eliminando: " << data << endl;
    }

    //Metodo publico para moficar un valor
    void modify(int old_data, int new_data)
    {
        modifyValue(root, old_data, new_data);
        cout << "Se ha modificado: " << old_data << " por: " << new_data << endl;
    }
    
    // Metodo publico para imprimir el arbol en preorden
    void printPreOrder() const {
        printPreOrder(root);
        cout << endl;
    }

    void printInOrder() const {
        printInOrder(root);
        cout << endl;
    }
    void printPostOrder() const {
        printPostOrder(root);
        cout << endl;
    }

    void recorrer(Node* node, ofstream& fp) {
        if (node != nullptr)
        {
            if (node->left != nullptr)
            {
                fp << node->info << "->" << node->left->info << ";" << endl;
            }
            else
            {
                string cadena = "\"" + to_string(node->info) + "i\"";
                fp << cadena << " [shape=point];" << endl;
                fp <<node->info << "->" << cadena << ";" << endl;
            }

            if (node->right != nullptr) {
                fp << node->info << "->" << node->right->info << ";" << endl;
            } else {
                string cadena = "\"" + to_string(node->info) + "d\"";
                fp << cadena << " [shape=point];" << endl;
                fp << node->info << "->" << cadena << ";" << endl;
            }
            recorrer(node->left, fp);
            recorrer(node->right, fp);
            
        }
        
    }

    void visualize() {
        ofstream fp("grafo.txt");

        if (!fp.is_open()) 
        {
            cerr << "Error al abrir el archivo grafo.txt" << endl;
            return;
        }
      
        fp << "digraph G {" << endl;
        fp << "node [style=filled fillcolor=yellow];" << endl;

        recorrer(root, fp);

        fp << "}" << endl;

        fp.close();

        system("dot -Tpng -o grafo.png grafo.txt");
        system("eog grafo.png");
    }

};

int main() {
   

    Arbol arbol;

    // Insertar numeros en el arbol usando el metodo insert
    arbol.insert(120);
    arbol.insert(87);
    arbol.insert(140);
    arbol.insert(43);
    arbol.insert(99);
    arbol.insert(130);
    arbol.insert(22);
    arbol.insert(65);
    arbol.insert(93);
    arbol.insert(135);
    arbol.insert(56);
    
    // Imprimir el arbol en preorden
    cout << "Recorrido en preorden: ";
    arbol.printPreOrder();
    cout << endl;

    cout << "Recorrido en inorden: ";
    arbol.printInOrder();
    cout << endl;

    cout << "Recorrido en postorden: ";
    arbol.printPostOrder();


    int numero = 65;
    cout << "Eliminando dato: " << endl;
    
    arbol.eliminar(numero);
    cout << endl;

    cout << "Imprimir en postorden: ";
    arbol.printPostOrder();
    cout << endl;

    int old_data = 140;
    int new_data = 90;

    arbol.modify(old_data, new_data);

    cout << "Imprimir en postorden: ";
    arbol.printPostOrder();
    cout << endl;
    arbol.visualize();


    return 0;
    
}