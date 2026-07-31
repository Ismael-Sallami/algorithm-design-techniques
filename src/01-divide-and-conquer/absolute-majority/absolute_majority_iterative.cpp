/*Dado un vector de enteros V de tamaño n que en cada posicion contiene el
código numérico del candidato votado por una persona (hay n votos), se desea
conocer si hay algún candidato "x" que tenga mayoría absoluta (puede haber uno
solo, o ninguno), es decir necesita más (estrictamente mayor) de n/2 votos. O lo
que es lo mismo: Card{i | v[i]=x} > n/2. No se conoce a priori quienes son los
candidatos. Por ejemplo si n = 10 tiene que tener 6 votos o mas. Si n = 11,
necesita tambien 6 votos o mas. No se puede suponer que exista una relacion de
orden entre los elementos del vector.*/

#include <iostream>
#include <vector>
#include <unordered_map>
#include <chrono>
#include <fstream>

using namespace std;

int algoritmoBasico(const vector<int> &arr, int n) { // O(n)

    unordered_map<int,int> aux;

    for (int i=0; i<n; ++i){ // O(n)
            aux[arr[i]]++; // 0(1)
            if (aux[arr[i]] > n/2)
               return arr[i];
    }

    return -1; 
}

int main (int argc, char* argv[]){
    
    if (argc < 2){
        cerr << "Se debe ejecutar de la siguiente forma: " << endl;
        cerr << "./mayoriaAbsoluta <numero de votos> <nº del candidato del primer voto> ... <nº del candidato del último voto> " << endl;
        return 0;
    }

    int n = atoi(argv[1]);

    vector<int> array;

    for (int i=0; i<n; ++i)
        array.push_back(atoi(argv[i+2]));


    int resultado;

    resultado = algoritmoBasico(array, n);

    if (resultado == -1)
        cout << "Ningún candidato tiene la mayoría absoluta. " << endl;
    else
        cout << "El candidato " << resultado << " tiene mayoría absoluta. " << endl;

    return 0; 

}