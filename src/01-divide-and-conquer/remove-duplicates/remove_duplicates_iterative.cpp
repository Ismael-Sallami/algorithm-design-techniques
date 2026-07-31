/*Dado un vector de n elementos, se pide eliminar todos los elementos
duplicados, es decir, que estén más de una vez en el vector.*/

#include <iostream>
#include <vector>

using namespace std;

void eliminar(vector<int> &vec) {

  for (vector<int>::iterator i = vec.begin(); i != vec.end(); ++i) {
    for (vector<int>::iterator j = i + 1; j != vec.end(); j++) {
      if (*i == *j) {
        j = vec.erase(j) - 1;
      }
    }
  }
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

  eliminar(v);

  cout << "Vector sin repetidos: " << endl;

  imprimir(v);

  return 0;
}
