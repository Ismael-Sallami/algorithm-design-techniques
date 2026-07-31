#include <algorithm>
#include <chrono>
#include <cstdlib> 
#include <cstring> 
#include <fstream>
#include <iostream>
#include <random> 
#include <vector>

using namespace std;

bool test(const vector<int> &v1, const vector<int> &v2) {
  if (v1.size() != v2.size()) {
    return false;
  }
  for (size_t i = 0; i < v1.size(); i++) {
    if (v1[i] != v2[i]) {
      return false;
    }
  }
  return true;
}

void algoritmoBasico(vector<int>& arr1, vector<int>& arr2) {
    // Encontrar el rango de los elementos
    int maxElement = *max_element(arr1.begin(), arr1.end());
    int minElement = *min_element(arr1.begin(), arr1.end());
    int range = maxElement - minElement + 1;

    // Inicializar el array de conteo con ceros
    vector<int> count(range, 0);

    // Contar la cantidad de ocurrencias de cada elemento
    for (int i = 0; i < arr1.size(); ++i) {
        count[arr1[i] - minElement]++;
    }

    // Actualizar el array de conteo para tener las posiciones correctas
    for (int i = 1; i < range; ++i) {
        count[i] += count[i - 1];
    }

    // Crear un array auxiliar para almacenar los elementos ordenados
    vector<int> output(arr1.size());

    // Colocar los elementos en el array ordenado
    for (int i = arr1.size() - 1; i >= 0; --i) {
        output[count[arr1[i] - minElement] - 1] = arr1[i];
        count[arr1[i] - minElement]--;
    }

    // Copiar los elementos ordenados de vuelta al array original
    for (int i = 0; i < arr1.size(); ++i) {
        arr1[i] = output[i];
    }

    // Ordenamos el array2

    // Encontrar el rango de los elementos
    maxElement = *max_element(arr2.begin(), arr2.end());
    minElement = *min_element(arr2.begin(), arr2.end());
    range = maxElement - minElement + 1;

    // Inicializar el array 2 de conteo con ceros
    vector<int> count2(range, 0);

    // Contar la cantidad de ocurrencias de cada elemento
    for (int i = 0; i < arr2.size(); ++i) {
        count2[arr2[i] - minElement]++;
    }

    // Actualizar el array2 de conteo para tener las posiciones correctas
    for (int i = 1; i < range; ++i) {
        count2[i] += count2[i - 1];
    }

    // Crear un array 2 auxiliar para almacenar los elementos ordenados
    vector<int> output2(arr2.size());

    // Colocar los elementos en el array2 ordenado
    for (int i = arr2.size() - 1; i >= 0; --i) {
        output2[count2[arr2[i] - minElement] - 1] = arr2[i];
        count2[arr2[i] - minElement]--;
    }

    // Copiar los elementos ordenados de vuelta al array 2 original
    for (int i = 0; i < arr2.size(); ++i) {
        arr2[i] = output2[i];
    }

    
}
int Dividir(vector<int> &v, vector<int> &v2, int inicio, int fin) {
    int pivote;
    if (v[inicio] == v2[inicio])
        pivote = v2[inicio];
    else {
        auto iterador = find(v2.begin(), v2.end(), v[inicio]);
        pivote = *iterador;
    }

    int izq = inicio + 1;
    int der = fin;

    while (izq <= der) {
        while (izq <= der && v[izq] <= pivote)
            izq++;

        while (izq <= der && v[der] > pivote)
            der--;

        if (izq < der)
            swap(v[izq], v[der]);
    }

    swap(v[inicio], v[der]);
    return der;
    }
    
    void Quicksort(vector<int>&v,vector<int>&v2,int inicio, int fin){
      if (inicio < fin) {
          int pivote = Dividir(v, v2, inicio, fin);
          Quicksort(v, v2, inicio, pivote - 1);
          Quicksort(v,v2, pivote + 1, fin);
      }
    }
    
    void divideYvenceras(vector<int> &v, vector<int> &v2, int inicio, int fin) {
        if (inicio < fin) {
            Quicksort(v, v2, inicio, fin);
            Quicksort(v2, v, inicio, fin); // Aquí se debe usar v2 en lugar de v para el segundo vector
        }
}


int main(int argc, char* argv[]) {
    // Crear y escribir en el archivo TXT
    ofstream archivo_txt("salida_tuercasYtornillos.txt");
    if (!archivo_txt.is_open()) {
        cout << "Error al abrir el archivo salida_tuercasYtornillos.txt" << endl;
        return 1;
    }

    archivo_txt << " n es el tamaño del caso, t1 es el tiempo del algoritmo divide y vencerás, t2 es el tiempo del algoritmo iterativo" << endl;
    archivo_txt << "n T1 T2" << endl;

    for (int n = 1; n <= 20; n += 2) {
        vector<int> tornillos, tuercas; // Generar valores para los vectores
        for (int i = 0; i < n; ++i) {
            tornillos.push_back(i + 1); // Tuercas
            tuercas.push_back(i + 1); // Tornillos
        }

        // Barajar los vectores para garantizar que estén en un orden aleatorio
        srand(time(nullptr)); // Inicializa la semilla de generador de números aleatorios
        random_shuffle(tornillos.begin(), tornillos.end());
        random_shuffle(tuercas.begin(), tuercas.end());

        // Iniciar el temporizador
        clock_t inicio = clock();

        // Ordenar los vectores utilizando el algoritmo "Quicksort"
        divideYvenceras(tornillos, tuercas, 0, tornillos.size() - 1);

        // Detener el temporizador
        clock_t fin = clock();

        // Calcular el tiempo transcurrido en microsegundos
        double tiempo = double(fin - inicio) * 1000000.0 / CLOCKS_PER_SEC;

        // Escribir en el archivo TXT
        archivo_txt << n << "," << tiempo;
    
        // Iniciar el temporizador
        clock_t inicio2 = clock();

        // Ordenar los vectores utilizando el algoritmo "Quicksort"
        algoritmoBasico(tornillos, tuercas);

        // Detener el temporizador
        clock_t fin2 = clock();

        // Calcular el tiempo transcurrido en microsegundos
        double tiempo2 = double(fin2 - inicio2) * 1000000.0 / CLOCKS_PER_SEC;

        archivo_txt << " " << tiempo2 << endl;


    }
}

