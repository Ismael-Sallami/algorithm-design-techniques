/*
Supongamos que tenemos n estudiantes en una clase y queremos crear con ellos
equipos formados por parejas (podemos suponer que n es un número par). Se
dispone de una matriz p de tamaño n×n en la que p(i, j) indica el nivel de
preferencia que el estudiante i tiene para trabajar con el estudiante j. El
valor del emparejamiento del estudiante i con el j es p(i, j) * p(j, i). Se
trata de encontrar un emparejamiento para todos los estudiantes de forma que se
maximice la suma de los valores de los emparejamientos.
*/
#include <cstdlib>
#include <iostream>
#include <utility>
#include <vector>

using namespace std;

vector<pair<pair<int, int>, int>> GreedyParejas(vector<vector<int>> matriz) {
  vector<pair<pair<int, int>, int>> S, preferencia;
  for (int i = 0; i < matriz.size(); i++) {
    for (int j = i; j < matriz.size(); j++) {
      if (matriz[i][j] > 0) {
        preferencia.push_back(pair(pair(i, j), matriz[i][j] * matriz[j][i]));
      }
    }
  }

  while (!preferencia.empty()) {
    int max = 0;
    for (int i = 0; i < preferencia.size(); i++) {
      if (preferencia[max].second < preferencia[i].second) {
        max = i;
      }
    }
    S.push_back(preferencia[max]);
    for (auto i = preferencia.begin(); i != preferencia.end(); ++i) {
      if (i->first.first == S.back().first.first ||
          i->first.second == S.back().first.second ||
          i->first.second == S.back().first.first ||
          i->first.first == S.back().first.second) {
        i = preferencia.erase(i);
        --i;
      }
    }
  }
  return S;
}
int main() {
  int ent = 0;
  srand(time(NULL));
  vector<vector<int>> matr(4, vector<int>(4));
  for (int i = 0; i < matr.size(); i++) {
    matr[i][i] = -1;
  }
  for (int i = 0; i < matr.size(); i++) {
    for (int j = 0; j < matr.size(); j++) {
      if (matr[i][j] >= 0) {
        ent = rand() % 11;
        if (ent == 0) {
          ent++;
        }
        matr[i][j] = ent;
      }
    }
  }
  cout << "Estudiante ";
  for (int h = 0; h < matr.size(); h++) {
    cout << h << " ";
  }
  cout << endl;

  for (int i = 0; i < matr.size(); i++) {

    cout << "     " << i << "     ";
    for (int j = 0; j < matr.size(); j++) {
      cout << matr[i][j] << " ";
    }
    cout << endl;
  }
  cout << endl;
  vector<pair<pair<int, int>, int>> listafin = GreedyParejas(matr);
  for (int i = 0; i < listafin.size(); i++) {
    cout << listafin[i].first.first << "," << listafin[i].first.second << "("
         << listafin[i].second << ")" << endl;
  }
  return 0;
}
