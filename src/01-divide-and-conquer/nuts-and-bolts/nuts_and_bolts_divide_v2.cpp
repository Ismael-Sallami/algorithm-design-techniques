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

void Quicksort(vector<int> &v, vector<int> &v2, int inicio, int fin) {
  if (inicio < fin) {
    int pivote = Dividir(v, v2, inicio, fin);
    Quicksort(v, v2, inicio, pivote - 1);
    Quicksort(v, v2, pivote + 1, fin);
  }
}

void divideYvenceras(vector<int> &v, vector<int> &v2, int inicio, int fin) {
  if (inicio < fin) {
    Quicksort(v, v2, inicio, fin);
    Quicksort(v2, v, inicio,
              fin); // Aquí se debe usar v2 en lugar de v para el segundo vector
  }
}

int main() {
  vector<int> tornillos = {4, 2, 5, 1, 3};
  vector<int> tuercas = {3, 2, 1, 5, 4};

  cout << "Usando el algoritmo divide y vencerás:\n";
  divideYvenceras(tornillos, tuercas, 0, tornillos.size() - 1);
  for (size_t i = 0; i < tornillos.size(); ++i) {
    cout << "Tornillo " << tornillos[i] << " emparejado con tuerca "
         << tuercas[i] << endl;
  }
  if (test(tornillos, tuercas))
    cout << "Los vectores coinciden\n";
  else
    cout << "Los vectores no coinciden\n";

  return 0;
}
