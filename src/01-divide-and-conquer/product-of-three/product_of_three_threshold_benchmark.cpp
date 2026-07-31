/*Determinar si un cierto numero natural N puede expresarse como producto de
tres numeros naturales consecutivos.*/

#include <algorithm>
#include <chrono>
#include <cmath>
#include <ctime>
#include <fstream>
#include <iostream>

using namespace std;

bool algoritmoBasico(long long n) {
  for (auto j = 6; j <= n; j++) {
    if (((j - 1) * j * (j + 1)) == n)
      return true;
  }
  return false;
}

int divideYVenceras(long long n, long long izq, long long der) {
  if (izq > der || der < 6) {
    return 0;
  }
  long long x = (izq + der) / 2;
  long long producto = x * (x + 1) * (x + 2);
  if (producto == n) {
    return 1;
  } else if (producto < n) {
    return divideYVenceras(n, x + 1, der);
  } else {
    return divideYVenceras(n, izq, x - 1);
  }
}

int main(int argc, char *argv[]) {
  chrono::time_point<std::chrono::high_resolution_clock> t0, tf;
  ofstream fsalidaBasico, fsalidaDIvideYVenceras;
  if (argc != 2) {
    cerr << "Se debe ejecutar: ./productoTresElementos <n_a_comprobar>" << endl;
    return -1;
  }

  fsalidaDIvideYVenceras.open("DatosDivide.txt");
  for (int i = 1; i <= atoi(argv[1]); i += 10) {

    int n = i;
    t0 = std::chrono::high_resolution_clock::now();
    divideYVenceras(n, 1, n);
    tf = std::chrono::high_resolution_clock::now();
    std::chrono::duration<double, std::micro> tejecucion2 =
        std::chrono::duration_cast<std::chrono::duration<double, std::micro>>(
            tf - t0);
    fsalidaDIvideYVenceras << n << " " << tejecucion2.count() << endl;
  }

  fsalidaDIvideYVenceras.close();
  fsalidaBasico.open("DatosBasico.txt");
  for (int i = 1; i <= atoi(argv[1]); i += 10) {
    int n = i;
    t0 = std::chrono::high_resolution_clock::now();
    divideYVenceras(n, 1, n);
    tf = std::chrono::high_resolution_clock::now();
    std::chrono::duration<double, std::micro> tejecucion1 =
        std::chrono::duration_cast<std::chrono::duration<double, std::micro>>(
            tf - t0);
    fsalidaBasico << n << " " << tejecucion1.count() << endl;
  }
  fsalidaBasico.close();

  return 0;
}
