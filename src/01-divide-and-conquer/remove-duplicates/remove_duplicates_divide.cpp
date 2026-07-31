/*Dado un vector de n elementos, se pide eliminar todos los elementos
duplicados, es decir, que estén más de una vez en el vector.*/

#include <algorithm>
#include <iostream>
#include <vector>

using namespace std;

vector<int> divideyvenceras(vector<int> &vec, bool ord) {
  if (ord == false) {
    sort(vec.begin(), vec.end());
    ord = true;
  }

  if (vec.size() > 1) {
    int mitad = vec.size() / 2;
    auto iter = find(vec.begin(), vec.end(), vec[mitad]);
    int veces = count(iter, vec.end(), vec[mitad]);
    if (veces == int(vec.size())) {

      while (vec.size() > 1) {
        vec.pop_back();
      }
    } else {
      if (vec.back() != vec[mitad]) {
        for (int i = 0; i < veces; i++) {
          iter++;
        }
      }

      vector<int> izq(vec.begin(), iter);
      vector<int> der(iter, vec.end());
      izq = divideyvenceras(izq, ord);
      der = divideyvenceras(der, ord);
      for (size_t i = 0; i < der.size(); i++) {
        izq.push_back(der[i]);
      }
      vec = izq;
    }
  }
  return vec;
}

void imprimir(const vector<int> &v) {
  for (size_t i = 0; i < v.size(); ++i)
    cout << v[i] << " ";
}

int main(int argc, char *argv[]) {

  if (argc != 2) {
    cerr << "\nError: El programa se debe ejecutar de la siguiente forma.\n\n";
    cerr << argv[0] << "   tamCaso";
    return 0;
  }

  int n = atoi(argv[1]);

  vector<int> v(n);
  // Generamos vector aleatorio de prueba, con componentes entre 0 y n-1
  for (int i = 0; i < n; i++)
    v[i] = rand() % n;

  cout << "Vector con repetidos: " << endl;

  imprimir(v);

  v = divideyvenceras(v, false);

  cout << "Vector sin repetidos: " << endl;

  imprimir(v);

  return 0;
}
