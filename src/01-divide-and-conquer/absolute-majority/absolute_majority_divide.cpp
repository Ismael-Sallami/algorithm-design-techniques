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

int divideYVenceras(const vector<int> &arr, int inicio, int fin) { // O(n*log(n))

    // Tomamos como candidatos iniciales los elementos que quedan en subvectores de tamaño 1
    if (inicio == fin) {
        return arr[inicio];
    }

    int mitad = inicio + (fin - inicio) / 2;

    // Llamada recursiva en las dos mitades
    int mayoria_izquierda = divideYVenceras(arr, inicio, mitad);
    int mayoria_derecha = divideYVenceras(arr, mitad + 1, fin);

    // Si un número es mayoría en la izquierda y en la derecha del vector, lo es en todo el vector
    if (mayoria_izquierda == mayoria_derecha) {
        return mayoria_derecha;
    }

    int contador_izquierda = 0, contador_derecha = 0;

    // Contar votos totales de cada candidato en el vector
    for (int i = inicio; i <= fin; ++i) {
        if (arr[i] == mayoria_izquierda) 
            contador_izquierda++;
        else if (arr[i] == mayoria_derecha) 
            contador_derecha++;
    }

    // Vemos si alguno es mayoría absoluta, si no devolvemos -1
    if (contador_izquierda > (fin - inicio + 1) / 2) 
        return mayoria_izquierda;

    if (contador_derecha > (fin - inicio + 1) / 2)
        return mayoria_derecha;
    
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

    resultado = divideYVenceras(array, 0, n-1);

    if (resultado == -1)
        cout << "Ningún candidato tiene la mayoría absoluta. " << endl;
    else
        cout << "El candidato " << resultado << " tiene mayoría absoluta. " << endl;

    return 0; 

}