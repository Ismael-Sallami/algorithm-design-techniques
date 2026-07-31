/*
El problema consiste en encontrar la salida de un laberinto. Más concretamente,
supondremos que el laberinto se representa mediante una matriz cuadrada
bidimensional de tamaño n × n. Cada posición almacena un valor booleano “true”
si la casilla es transitable y “false” si la casilla no es transitable. Los
movimientos permitidos son hacia casillas adyacentes de la misma fila o la misma
columna. Podemos suponer que las casillas de entrada y salida del laberinto son
(0, 0) y (n − 1, n − 1) respectivamente. Por tanto, el problema consiste en,
dada una matriz que representa el laberinto, encontrar si existe un camino para
ir desde la entrada hasta la salida.
*/

#include "maze.cpp"
#include <cmath>
#include <iostream>

using namespace std;

struct Pos {
  double x;
  double y;

  // Constructor para ser más cómodo, se puede omitir y usar: {coordenda x,
  // coordenada y}
  Pos(double x_val, double y_val) : x(x_val), y(y_val) {}
};

// Esta función auxiliar podríamos omitirla, pero prefiero realizar esta
// operación como una llamada a función para hacer un código más legible
bool estaEnMarcados(vector<Pos> Marcados, Pos p) {
  for (int i = 0; i < Marcados.size(); i++) {
    if (p.x == Marcados[i].x && p.y == Marcados[i].y)
      return true;
  }
  return false;
}

// Nota: pasamos las coordeandas para no acceder a un punto fuera de la matriz
// y, de esta manera asegurarnos de que no intentemos acceder a una posición de
// memoria que no debemos
bool Valida(double x, double y, vector<Pos> Marcados, laberinto m, int n) {
  int cnt = 0;

  // Vemos si ya estamos fuera del laberinto
  if (x < 0 || y < 0 || x > n - 1 || y > n - 1)
    return false;

  // Vemos si ya hemos pasado por ahí, de manera que si ya hemos pasado
  // devolvemos false
  if (!estaEnMarcados(Marcados, Pos(x, y)))
    cnt++;

  // Nos aseguramos de que no haya muro
  if (m.GetValor(x, y) != false)
    cnt++;

  // Si cumple con las características devolvemos true
  if (cnt == 2)
    return true;
  return false;
}

bool SolucionBacktracking_Laberinto(laberinto L, Pos pos_actual,
                                    vector<Pos> &Marcados) {
  int n = L.GetSize();

  if (pos_actual.x > n - 1 || pos_actual.y > n - 1) {
    Marcados.push_back(pos_actual);
    return true; // estamos ya fuera, así que devolvemos true
  }

  if (pos_actual.x == n - 1 && pos_actual.y == n - 1 &&
      Valida(pos_actual.x, pos_actual.y, Marcados, L, n)) {
    Marcados.push_back(pos_actual);
    return true; // es el destino, así que devolvemos true
  }

  if (estaEnMarcados(Marcados, pos_actual)) {
    return false;
  }

  Marcados.push_back(pos_actual);

  if (Valida(pos_actual.x + 1, pos_actual.y, Marcados, L, n)) {
    Pos p(pos_actual.x + 1, pos_actual.y);
    if (SolucionBacktracking_Laberinto(L, p, Marcados))
      return true;
  }

  if (Valida(pos_actual.x - 1, pos_actual.y, Marcados, L, n)) {
    Pos p(pos_actual.x - 1, pos_actual.y);
    if (SolucionBacktracking_Laberinto(L, p, Marcados))
      return true;
  }

  if (Valida(pos_actual.x, pos_actual.y - 1, Marcados, L, n)) {
    Pos p(pos_actual.x, pos_actual.y - 1);
    if (SolucionBacktracking_Laberinto(L, p, Marcados))
      return true;
  }

  if (Valida(pos_actual.x, pos_actual.y + 1, Marcados, L, n)) {
    Pos p(pos_actual.x, pos_actual.y + 1);
    if (SolucionBacktracking_Laberinto(L, p, Marcados))
      return true;
  }

  Marcados.pop_back();
  return false;
}

// Función auxiliar para pintar el camino solución (se puede omitir)
void PintarMatrizCamino(vector<Pos> &v, int n) {
  vector<vector<char>> matriz(n, vector<char>(n, 'X'));
  for (int i = 0; i < n; i++) {
    for (int j = 0; j < matriz[i].size(); j++) {
      for (int k = 0; k < v.size(); k++) {
        if (v[k].x == i && v[k].y == j) {
          matriz[i][j] = 'O';
        }
      }
    }
  }

  for (int i = 0; i < n; i++) {
    for (int j = 0; j < matriz[i].size(); j++) {
      cout << matriz[i][j] << "  ";
    }
    cout << endl;
  }
}

int main() {
  // Crear un laberinto
  laberinto L(3);
  L.muro(2, 1);
  L.muro(1, 1);

  // Imprimir el laberinto
  cout << "Laberinto:" << endl;
  L.imprimirMatrizBooleana();

  // Definir posición inicial
  Pos inicio = {5, 5};
  vector<Pos> Marcados;

  // Llamar a la función de solución de laberinto
  if (SolucionBacktracking_Laberinto(L, inicio, Marcados)) {
    cout << "\nHay una solucion." << endl;
  } else {
    cout << "\nNo hay solucion." << endl;
  }

  // Imprimir el camino recorrido
  cout << "Camino recorrido:" << endl;
  if (Marcados.empty()) {
    cout << "No se ha recorrido ninguna casilla." << endl;
  } else {
    for (int i = 0; i < Marcados.size(); i++) {
      cout << "(" << Marcados[i].x << ", " << Marcados[i].y << ") ";
    }
    cout << endl;
  }

  if (inicio.x == 0 && inicio.y == 0) {
    cout << endl
         << "Debemos de pasar por el caminito de círculos para llegar a la "
            "salida del laberinto desde el punto de inicio {0,0}: "
         << endl;
  }
  PintarMatrizCamino(Marcados, L.GetSize());

  return 0;
}
