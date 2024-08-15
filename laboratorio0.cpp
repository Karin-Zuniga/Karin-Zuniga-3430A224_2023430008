#include <iostream>
#include <string>
using namespace std;

bool par_o_impar(int x){
    return (x % 2 == 0);

}

void is_par(int x){

    if (par_o_impar(x)) {
        std::cout << "el numero " <<  x << " es par \n";
    }
    else{
        std::cout << "el numero " <<  x << " es impar \n";
    }

}

void longitud_string(string palabra){
    int x = palabra.length();
    std::cout << "Hay " <<  x << " letras en " << palabra <<" \n";
}




int main()
{
int x;
std::cout << "Ingrese un numero \n";
std::cin >> x;
std::cout << "El numero es " << x << "\n";
is_par(x);
for(int i = 1; i <= 10; i = i + 1){
    is_par(i);
}
std::cout << "Ingrese una palabra \n";
string palabra;
std::cin >> palabra;

longitud_string(palabra);

string cadena = "hola" ;
longitud_string(cadena);

return 0;

}
