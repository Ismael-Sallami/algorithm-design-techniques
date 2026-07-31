
#include <chrono>
#include <cstring>
#include <fstream>
#include <iostream>
#include <string>
#include <vector>

using namespace std;
using namespace std::chrono;

int algoritmoBasico(int **partidos, int n) {
  for (int i = 0; i < n - 1; ++i) {
    partidos[0][i] = i + 2;
    partidos[i + 1][i] = 1;
  }
  int col_inicial_suma = 2;
  for (int i = 1; i <= n - 1; ++i) {
    int fila = i;
    int contador = i + 2;
    int j;
    for (j = col_inicial_suma; contador <= n; ++j) {
      if (j == n - 1)
        j = 0;
      if (partidos[fila][j] == 0)
        partidos[fila][j] = contador++;
    }
    for (int k = 0; k < n - 1; ++k) {
      int valor = partidos[fila][k];
      if (partidos[valor - 1][k] == 0)
        partidos[valor - 1][k] = fila + 1;
    }
    col_inicial_suma += 2;
    if (col_inicial_suma >= n)
      col_inicial_suma = col_inicial_suma % (n - 1);
  }
  return 0;
}

void copiar_submatriz(int i1, int j1, int i2, int j2, int diferencia,
                      int **partidos) {
  for (int i = i1; i < i2; ++i)
    for (int j = j1; j < j2; ++j) {
      partidos[i + diferencia][j + diferencia] = partidos[i][j];
      partidos[i][j + diferencia] = partidos[i][j] + diferencia;
      partidos[i + diferencia][j] = partidos[i][j] + diferencia;
    }
}

void sumar_cantidad_a_submatriz(int i1, int j1, int i2, int j2, int cantidad,
                                int **partidos) {
  for (int i = i1; i < i2; ++i)
    for (int j = j1; j < j2; ++j)
      partidos[i][j] += cantidad;
}

void rellenar_columna(int n, int **partidos) {
  int valor = n / 2 + 1;
  for (int i = 0; i < n; ++i) {
    partidos[i][(n - 1) / 2] = valor++;
    if (valor == n + 1)
      valor = 1;
  }
}

int dyv(int **partidos, int n) {
  if (n == 2) {
    partidos[0][0] = 2;
    partidos[1][0] = 1;
    return 0;
  }
  dyv(partidos, n / 2);
  copiar_submatriz(0, 0, n / 2, n / 2 - 1, n / 2, partidos);
  rellenar_columna(n, partidos);
  return 0;
}

int main(int argc, char *argv[]) {
  if (argc != 3) {
    cout << "Uso: " << argv[0] << " <tamaño_máximo> <nombre_archivo.ods>"
         << endl;
    return 1;
  }

  int n_max = atoi(argv[1]); // Obtener el tamaño máximo desde el argumento de
                             // línea de comandos
  if (n_max <= 0) {
    cout << "El tamaño máximo debe ser un entero positivo." << endl;
    return 1;
  }

  string nombre_archivo = argv[2]; // Obtener el nombre del archivo ODS

  // Crear y escribir en el archivo ODS
  ofstream archivo_ods(nombre_archivo);
  if (!archivo_ods.is_open()) {
    cout << "Error al abrir el archivo " << nombre_archivo << endl;
    return 1;
  }

  archivo_ods << "n,Tiempo iterativo (microsegundos),Tiempo dyv "
                 "(microsegundomicrosegundos)"
              << endl;

  for (int n = 2; n <= n_max; n *= 2) {
    int **partidos = new int *[n];
    for (int i = 0; i < n; ++i) {
      partidos[i] = new int[n - 1];
      for (int j = 0; j < n - 1; ++j) {
        partidos[i][j] = 0;
      }
    }

    string arg = to_string(n);

    string comando = "./campeonato_dyv " + arg;
    auto start = high_resolution_clock::now();

    int resultado = system(comando.c_str());
    auto end = high_resolution_clock::now();
    auto duration_dyv = duration_cast<microseconds>(end - start);

    if (resultado == 0) {
      cout << "El programa se ejecutó correctamente." << endl;
    } else {
      cout << "Error al ejecutar el programa." << endl;
    }

    comando = "./campeonato_iterativo " + arg;
    start = high_resolution_clock::now();

    resultado = system(comando.c_str());
    end = high_resolution_clock::now();
    auto duration_basico = duration_cast<microseconds>(end - start);

    if (resultado == 0) {
      cout << "El programa se ejecutó correctamente." << endl;
    } else {
      cout << "Error al ejecutar el programa." << endl;
    }

    archivo_ods << n << "," << duration_basico.count() << ","
                << duration_dyv.count() << endl;

    for (int i = 0; i < n - 1; ++i)
      delete[] partidos[i];
    delete[] partidos;
  }

  archivo_ods.close();

  cout << "El archivo " << nombre_archivo << " se ha creado con éxito." << endl;

  return 0;
}
