/*Dado un vector de n elementos, se pide eliminar todos los elementos
duplicados, es decir, que estén más de una vez en el vector.*/

#include <algorithm>
#include <chrono>
#include <fstream>
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
int main(int argc, char *argv[]) {

  int n, i, argumento;
  bool ordenar = false;
  chrono::time_point<std::chrono::high_resolution_clock> t0,
      tf; // Para medir el tiempo de ejecucion
  unsigned long int semilla;
  ofstream fsalida;

  if (argc <= 3) {
    cerr << "\nError: El programa se debe ejecutar de la siguiente forma.\n\n";
    cerr << argv[0]
         << " NombreFicheroSalida Semilla tamCaso1 tamCaso2 ... tamCasoN\n\n";
    return 0;
  }

  // Abrimos fichero de salida
  fsalida.open(argv[1]);
  if (!fsalida.is_open()) {
    cerr << "Error: No se pudo abrir fichero para escritura " << argv[1]
         << "\n\n";
    return 0;
  }

  // Inicializamos generador de no. aleatorios
  semilla = atoi(argv[2]);
  srand(semilla);

  // Pasamos por cada tamaÃ’o de caso
  for (argumento = 3; argumento < argc; argumento++) {

    // Cogemos el tamanio del caso
    n = atoi(argv[argumento]);

    vector<int> v(n);

    // Generamos vector aleatorio de prueba, con componentes entre 0 y n-1
    for (i = 0; i < n; i++)
      v[i] = rand() % n;

    vector<int> v2 = v;

    cerr << "Ejecutando Divide y venceras para tam. caso: " << n << endl;

    t0 = std::chrono::high_resolution_clock::
        now(); // Cogemos el tiempo en que comienza la ejecuciÃ›n del algoritmo
    divideyvenceras(
        v, ordenar); // Ejecutamos el algoritmo para tamaÃ’o de caso tam
    tf = std::chrono::high_resolution_clock::
        now(); // Cogemos el tiempo en que finaliza la ejecuciÃ›n del algoritmo

    unsigned long tejecucion =
        std::chrono::duration_cast<std::chrono::microseconds>(tf - t0).count();

    cerr << "\tTiempo dyv (us): " << tejecucion << " para tam. caso " << n
         << endl;

    t0 = std::chrono::high_resolution_clock::
        now(); // Cogemos el tiempo en que comienza la ejecuciÃ›n del algoritmo
    eliminar(v); // Ejecutamos el algoritmo para tamaÃ’o de caso tam
    tf = std::chrono::high_resolution_clock::
        now(); // Cogemos el tiempo en que finaliza la ejecuciÃ›n del algoritmo

    unsigned long tejecucion2 =
        std::chrono::duration_cast<std::chrono::microseconds>(tf - t0).count();

    cerr << "\tTiempo iterativo (us): " << tejecucion2 << " para tam. caso "
         << n << endl;

    // Guardamos tam. de caso y ts_ejecucion a fichero de salida
    fsalida << n << ";" << tejecucion << tejecucion2 << "\n";

    // Liberamos memoria del vector
  }

  // Cerramos fichero de salida
  fsalida.close();

  return 0;
}
