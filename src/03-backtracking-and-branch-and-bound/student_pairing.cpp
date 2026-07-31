/*
Supongamos que tenemos n estudiantes en una clase y queremos crear con ellos
equipos formados por parejas (podemos suponer que n es un número par). Se
// dispone de una matriz p de tamaño n×n en la que p(i, j) indica el nivel de
// preferencia que el estudiante i tiene para trabajar con el estudiante j. El
// valor del emparejamiento del estudiante i con el j es p(i, j) * p(j, i). Se
// trata de encontrar un emparejamiento para todos los estudiantes de forma que
se
// maximice la suma de los valores de los emparejamientos.
// */

// dilema como hacer que explore otro nivel(para formar nuevas combinaciones)
#include <iostream>
#include <utility>
#include <vector>

using namespace std;

void Borrar(vector<pair<pair<int, int>, int>> &vectorcopia,
            pair<int, int> alumnos) {
  for (vector<pair<pair<int, int>, int>>::iterator it = vectorcopia.begin();
       it != vectorcopia.end();) {
    if (it->first.first == alumnos.first ||
        it->first.second == alumnos.second ||
        it->first.first == alumnos.second ||
        it->first.second == alumnos.first) {
      it = vectorcopia.erase(it);
    } else {
      ++it;
    }
  }
}

void backtrackingparejas(vector<pair<pair<int, int>, int>> vectorparejas,
                         pair<vector<pair<int, int>>, int> &solparcial,
                         int inicial) {
  auto vectorcopia = vectorparejas;
  pair<vector<pair<int, int>>, int> solcopia;

  solcopia.second = 0;
  solcopia.first.push_back(vectorcopia[inicial].first);
  solcopia.second += vectorcopia[inicial].second;
  Borrar(vectorcopia, make_pair(vectorcopia[inicial].first.first,
                                vectorcopia[inicial].first.second));

  while (vectorcopia.empty() == false) {
    solcopia.first.push_back(vectorcopia[0].first);
    solcopia.second += vectorcopia[0].second;
    Borrar(vectorcopia,
           make_pair(vectorcopia[0].first.first, vectorcopia[0].first.second));
  }

  if (solcopia.second > solparcial.second) {
    solparcial = solcopia;
  }

  if (inicial < vectorparejas.size() - 1) {
    backtrackingparejas(vectorparejas, solparcial, inicial + 1);
  }
  return;
}

vector<pair<pair<int, int>, int>> Crearparejas(vector<vector<int>> matriz) {
  vector<pair<pair<int, int>, int>> parej;
  int aux1, aux2;
  for (int i = 0; i < matriz.size(); i++) {
    for (int j = i + 1; j < matriz.size(); j++) {
      aux1 = i;
      aux2 = j;

      parej.push_back(make_pair(make_pair(aux1, aux2),
                                matriz[aux1][aux2] * matriz[aux2][aux1]));
    }
  }
  return parej;
}

int main() {
  int n;                               // Número de estudiantes
  vector<vector<int>> preferencias(6); // Matriz de preferencias

  preferencias[0] = {-1, 3, 5, 7, 4, 7};
  preferencias[1] = {4, -1, 3, 9, 4, 1};
  preferencias[2] = {9, 9, -1, 8, 6, 9};
  preferencias[3] = {7, 5, 8, -1, 2, 5};
  preferencias[4] = {1, 3, 9, 9, -1, 8};
  preferencias[5] = {6, 8, 7, 5, 8, -1};
  for (int i = 0; i < preferencias.size(); ++i) {
    for (int j = 0; j < preferencias.size(); ++j) {
      cout << " " << preferencias[i][j];
    }
    cout << endl;
  }

  vector<pair<pair<int, int>, int>> vectorparejas = Crearparejas(preferencias);
  cout << "Todas las posibles parejas son: " << endl;
  for (int i = 0; i < vectorparejas.size(); i++) {
    cout << "(" << vectorparejas[i].first.first << ","
         << vectorparejas[i].first.second << "," << vectorparejas[i].second
         << ") ";
  }
  cout << endl;
  pair<vector<pair<int, int>>, int> solparcial;
  pair<vector<pair<int, int>>, int> solfinal;

  backtrackingparejas(vectorparejas, solparcial, 0);
  solfinal = solparcial;
  cout << "Parejas finales:" << endl;
  for (int i = 0; i < solfinal.first.size(); i++) {
    cout << "(" << solfinal.first[i].first << "," << solfinal.first[i].second
         << ")" << endl;
  }
  cout << "Con una afinidad de " << solfinal.second << endl;

  return 0;
}
