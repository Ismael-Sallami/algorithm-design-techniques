#include <algorithm>
#include <climits>
#include <iostream>
#include <vector>

using namespace std;

// Función para calcular el coste mínimo y llenar la tabla de programación
// dinámica
pair<vector<vector<int>>, int>
calcularCosteMinimo(const vector<vector<int>> &montana) {
  int f = montana.size();
  int c = montana[0].size();
  vector<vector<int>> T(f, vector<int>(c, INT_MAX));

  // Inicializar la primera fila
  for (int j = 0; j < c; ++j) {
    T[0][j] = montana[0][j];
  }

  // Llenar la tabla T utilizando la ecuación recurrente
  for (int i = 1; i < f; ++i) {
    for (int j = 0; j < c; ++j) {
      T[i][j] = montana[i][j] + T[i - 1][j];
      if (j > 0) {
        T[i][j] = min(T[i][j], montana[i][j] + T[i - 1][j - 1]);
      }
      if (j < c - 1) {
        T[i][j] = min(T[i][j], montana[i][j] + T[i - 1][j + 1]);
      }
    }
  }

  // Encontrar el valor objetivo
  int V = INT_MAX;
  for (int j = 0; j < c; ++j) {
    V = min(V, T[f - 1][j]);
  }

  return {T, V};
}

// Función para recuperar la solución (el camino de menor coste)
vector<pair<int, int>> recuperarSolucion(const vector<vector<int>> &T,
                                         const vector<vector<int>> &montana) {
  int f = montana.size();
  int c = montana[0].size();
  vector<pair<int, int>> solucion;

  // Encontrar la columna con el valor mínimo en la última fila
  int j = min_element(T[f - 1].begin(), T[f - 1].end()) - T[f - 1].begin();

  // Rastrear el camino desde la cumbre hasta la base
  for (int i = f - 1; i >= 0; --i) {
    solucion.push_back({i, j});
    if (i > 0) {
      if (j > 0 && T[i - 1][j - 1] == T[i][j] - montana[i][j]) {
        j = j - 1;
      } else if (j < c - 1 && T[i - 1][j + 1] == T[i][j] - montana[i][j]) {
        j = j + 1;
      }
    }
  }

  reverse(solucion.begin(), solucion.end());
  return solucion;
}

int main() {
  // Ejemplo de matriz de costes (Pixel Mountain)
  /* vector<vector<int>> montana = {{4, 7, 8, 6, 4}, */
  /*                                {6, 7, 3, 9, 2}, */
  /*                                {3, 8, 1, 2, 4}, */
  /*                                {7, 1, 7, 3, 7}, */
  /*                                {2, 9, 8, 9, 3}}; */
  // Ejemplo de matriz montaña del guion
  vector<vector<int>> montana = {
      {3, 2, 5, 4, 8}, {5, 7, 5, 6, 1}, {4, 4, 6, 2, 3}, {2, 8, 9, 5, 8}};
  // Calcular el coste mínimo y obtener la tabla T
  auto [T, V] = calcularCosteMinimo(montana);

  // Imprimir la tabla de costes mínimos
  cout << "Tabla de costes mínimos (T):" << endl;
  for (const auto &fila : T) {
    for (int valor : fila) {
      cout << valor << "\t";
    }
    cout << endl;
  }
  cout << "Coste mínimo para alcanzar la cumbre: " << V << endl;

  // Recuperar y imprimir el camino de menor coste
  vector<pair<int, int>> solucion = recuperarSolucion(T, montana);
  cout << "Camino de menor coste:" << endl;
  for (const auto &[i, j] : solucion) {
    cout << "(" << i << ", " << j << ")"
         << " ";
  }
  cout << endl;

  return 0;
}
