/*Determinar si un cierto numero natural N puede expresarse como producto de
tres numeros naturales consecutivos.*/

#include <iostream>

using namespace std;

bool algoritmoBasico(long long n) {
  for (int j = 1; j < n; j++) {
    if (((j - 1) * j * (j + 1)) == n)
      return true;
  }
  return false;
}

int main(int argc, char *argv[]) {

  if (argc != 2) {
    cerr << "Se debe ejecutar: ./productoTresElementos <n_a_comprobar>" << endl;
    return -1;
  }

  int n = atoi(argv[1]);
  bool verdad = algoritmoBasico(n);
  if (verdad)
    cout << "Verdad segun iterativo para n:" << n << endl;
  else
    cout << "No es verdad según iterativo para n:" << n << endl;

  return 0;
}
