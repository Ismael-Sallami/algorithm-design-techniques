/*Dado un vector de enteros V de tamaño n que en cada posicion contiene el
código numérico del candidato votado por una persona (hay n votos), se desea
conocer si hay algún candidato "x" que tenga mayoría absoluta (puede haber uno
solo, o ninguno), es decir necesita más (estrictamente mayor) de n/2 votos. O lo
que es lo mismo: Card{i | v[i]=x} > n/2. No se conoce a priori quienes son los
candidatos. Por ejemplo si n = 10 tiene que tener 6 votos o mas. Si n = 11,
necesita tambien 6 votos o mas. No se puede suponer que exista una relacion de
orden entre los elementos del vector.*/

#include <chrono>
#include <fstream>
#include <iostream>
#include <unordered_map>
#include <vector>

#define ALG_BASICO
#define ALG_DIVIDE_Y_VENCERAS
#define UMBRAL
#define INTERVALO

using namespace std;

int algoritmoBasico(const vector<int> &arr, int n) { // O(n)

  unordered_map<int, int> aux;

  for (int i = 0; i < n; ++i) { // O(n)
    aux[arr[i]]++;              // 0(1)
    if (aux[arr[i]] > n / 2)
      return arr[i];
  }

  return -1;
}

int divideYVenceras(const vector<int> &arr, int inicio,
                    int fin) { // O(n*log(n))

  // Tomamos como candidatos iniciales los elementos que quedan en subvectores
  // de tamaño 1
  if (inicio == fin) {
    return arr[inicio];
  }

  int mitad = inicio + (fin - inicio) / 2;

  // Llamada recursiva en las dos mitades
  int mayoria_izquierda = divideYVenceras(arr, inicio, mitad);
  int mayoria_derecha = divideYVenceras(arr, mitad + 1, fin);

  // Si un número es mayoría en la izquierda y en la derecha del vector, lo es
  // en todo el vector
  if (mayoria_izquierda == mayoria_derecha) {
    return mayoria_derecha;
  }

  int contador_izquierda = 0, contador_derecha = 0;

  // Contar votos totales de cada candidato en el vector
  for (int i = inicio; i <= fin; ++i) {
    if (arr[i] == mayoria_izquierda)
      contador_izquierda++;
    else if (arr[i] == mayoria_derecha)
      contador_derecha++;
  }

  // Vemos si alguno es mayoría absoluta, si no devolvemos -1
  if (contador_izquierda > (fin - inicio + 1) / 2)
    return mayoria_izquierda;

  if (contador_derecha > (fin - inicio + 1) / 2)
    return mayoria_derecha;

  return -1;
}

int main(int argc, char *argv[]) {

  chrono::time_point<std::chrono::high_resolution_clock> t0,
      tf; // Para medir el tiempo de ejecución
  unsigned long int semilla;
  ofstream fsalida;

  if (argc != 5) {
    cerr << "\nError: El programa se debe ejecutar de la siguiente forma.\n\n";
    cerr << argv[0]
         << " NombreFicheroSalida Semilla CotaInferiorIntervalo "
            "CotaSuperiorIntervalo ";
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

  // Pasamos por cada tamaño de caso
  for (int n = 10000; n < 100000; n += 100) {

    vector<int> v;
    int s = atoi(argv[4]), i = atoi(argv[3]);
    // Generamos vector aleatorio de prueba, con componentes entre 0 y n-1
    for (i = 0; i < n; i++) {
#ifndef INTERVALO
      v.push_back(rand() % n);
#endif
#ifdef INTERVALO
      v.push_back(rand() % ((s - i + 1) + i));
#endif
    }

    cerr << "Ejecutando mayoria_absoluta para tam. caso: " << n << endl;

    t0 = std::chrono::high_resolution_clock::
        now(); // Cogemos el tiempo en que comienza la ejecuciÛn del algoritmo

    algoritmoBasico(v, n);

    tf = std::chrono::high_resolution_clock::
        now(); // Cogemos el tiempo en que finaliza la ejecuciÛn del algoritmo

    unsigned long tejecucion =
        std::chrono::duration_cast<std::chrono::microseconds>(tf - t0).count();

    cerr << "\tTiempo iterativo (us): " << tejecucion << " para tam. caso " << n
         << endl;

    t0 = std::chrono::high_resolution_clock::
        now(); // Cogemos el tiempo en que comienza la ejecuciÛn del algoritmo

    divideYVenceras(v, 0, n - 1);

    tf = std::chrono::high_resolution_clock::
        now(); // Cogemos el tiempo en que finaliza la ejecuciÛn del algoritmo

    unsigned long tejecucion2 =
        std::chrono::duration_cast<std::chrono::microseconds>(tf - t0).count();

    cerr << "\tTiempo divide y vencerás (us): " << tejecucion2
         << " para tam. caso " << n << endl;

    // Guardamos tam. de caso y t_ejecucion a fichero de salida
    fsalida << n << " " << tejecucion << " " << tejecucion2 << "\n";
  }
  // Cerramos fichero de salida
  fsalida.close();

  return 0;
}
