/*
El alcalde de "Algovilla del Tuerto", un conocido pueblo, desea renovar el
embaldosado de las calles de su localidad. Sin embargo, las arcas del
ayuntamiento no están muy saneadas y no se puede permitir embaldosar todas las
calles del pueblo. El encanto de Algovilla reside en sus múltiples plazas (una
en cada intersección de calles), que son monumentos locales, y en la belleza de
pasear entre dichas plazas en época de verano, por lo que es un atractivo
turístico que trae riqueza y trabajo a la localidad en esta época del año. El no
realizar el embaldosado puede disminuir el atractivo del pueblo, la visita
turística y, por tanto, reducir el desahogo económico que se produce en verano
para sus habitantes, debido al turismo. Para solucionar el problema, el concejal
de urbanismo ha propuesto la siguiente solución: Gastar el menor dinero posible
en asfaltar un conjunto de calles, de forma que siempre que se pueda llegar
desde una plaza a cualquier otra a través de calles asfaltadas. Así, cualquier
turista podrá disfrutar de los paseos entre estos monumentos. Como asesor, se te
requiere que formules el problema y lo resuelvas, proporcionando una solución
que permita viajar desde cualquier plaza a cualquier otra plaza, con la
restricción de que el paseo se realice siempre por una calle asfaltada y que el
coste de asfaltar las calles necesarias para ello sea mínimo. Se te
proporcionará información sobre qué plazas están unidas entre sí directamente
por una única calle y el coste de asfaltarlas (suponer coste igual a +∞ cuando
no exista una calle que une dos plazas de forma directa).
*/

#include <algorithm>
#include <cstdlib>
#include <fstream>
#include <iostream>
#include <vector>

using namespace std;

class Grafo {
private:
  struct Arista {
    int origen;
    int destino;
    int peso;

    Arista(int o, int d, int p) : origen(o), destino(d), peso(p) {}
  };

  vector<vector<int>> matrizAdyacencia;
  vector<vector<int>> listaAdyacencia;
  vector<Arista> aristas;

public:
  Grafo(int n) {
    // Inicializar la matriz de adyacencia
    matrizAdyacencia.resize(n, vector<int>(n, 0));

    // Inicializar la lista de adyacencia
    listaAdyacencia.resize(n);
  }

  void agregarConexion(int a, int b, int peso) {
    matrizAdyacencia[a][b] = peso;
    matrizAdyacencia[b][a] = peso;
    listaAdyacencia[a].push_back(b);
    listaAdyacencia[b].push_back(a);
    aristas.push_back(Arista(a, b, peso));
  }

  void imprimirListaAdyacencia() {
    for (int i = 0; i < listaAdyacencia.size(); i++) {
      cout << "Nodo " << i << ": ";
      for (int j = 0; j < listaAdyacencia[i].size(); j++) {
        cout << listaAdyacencia[i][j] << " ";
      }
      cout << "\n";
    }
  }

  void imprimirMatrizAdyacencia() {
    for (int i = 0; i < matrizAdyacencia.size(); i++) {
      for (int j = 0; j < matrizAdyacencia[i].size(); j++) {
        cout << matrizAdyacencia[i][j] << " ";
      }
      cout << "\n";
    }
  }

  // Implementación del algoritmo de Kruskal
  vector<vector<int>> kruskal() {
    vector<vector<int>> solucion(matrizAdyacencia.size(),
                                 vector<int>(matrizAdyacencia.size(), 0));

    sort(aristas.begin(), aristas.end(),
         [](const Arista &a, const Arista &b) { return a.peso < b.peso; });

    vector<int> padre(matrizAdyacencia.size());
    for (int i = 0; i < padre.size(); ++i)
      padre[i] = i;

    for (const auto &arista : aristas) {
      int padreOrigen = encontrarPadre(padre, arista.origen);
      int padreDestino = encontrarPadre(padre, arista.destino);

      if (padreOrigen != padreDestino) {
        solucion[arista.origen][arista.destino] = arista.peso;
        cout << "Asfaltar calle entre Plaza " << arista.origen << " y Plaza "
             << arista.destino << " con coste " << arista.peso << endl;
        unir(padre, padreOrigen, padreDestino);
      }
    }
    return solucion;
  }

  // Método para generar un archivo DOT que describe el grafo
  void generarArchivoDOT(string nombreArchivo) {
    ofstream archivo(nombreArchivo);

    archivo << "graph G {" << endl;

    for (const auto &arista : aristas) {
      archivo << arista.origen << " -- " << arista.destino << " [label=\""
              << arista.peso << " €"
              << "\"];" << endl;
    }

    archivo << "}" << endl;
    archivo.close();

    cout << "Archivo DOT generado: " << nombreArchivo << endl;
  }

  // Método para generar un archivo PNG a partir de un archivo DOT
  void generarPNG(string nombreArchivoDOT) {
    string comando =
        "dot -Tpng " + nombreArchivoDOT + " -o " + nombreArchivoDOT + ".png";
    system(comando.c_str());
    cout << "Archivo PNG generado: " << nombreArchivoDOT + ".png" << endl;
  }

private:
  int encontrarPadre(vector<int> &padre, int nodo) {
    if (padre[nodo] != nodo)
      padre[nodo] = encontrarPadre(padre, padre[nodo]);
    return padre[nodo];
  }

  void unir(vector<int> &padre, int nodoA, int nodoB) { padre[nodoB] = nodoA; }
};

int main() {
  int n = 5; // Cantidad de nodos (plazas)
  Grafo grafo(n);

  // Para la prueba, utilizaremos las calles y plazas de Algovilla del Tuerto.
  // Plaza Azcarate: Nodo 0
  // Plaza de la Libertad: Nodo 1
  // Plaza Mayor: 2
  // Plaza de las Maravilas: Nodo 3
  // Plaza de la Constitucion: Nodo 4

  grafo.agregarConexion(0, 1, 1100000);
  grafo.agregarConexion(0, 2, 130000);
  grafo.agregarConexion(0, 3, 450004);
  grafo.agregarConexion(0, 4, 748556);
  grafo.agregarConexion(1, 2, 1300000);
  grafo.agregarConexion(1, 3, 555123);
  grafo.agregarConexion(1, 4, 1700000);
  grafo.agregarConexion(2, 4, 554521);
  grafo.agregarConexion(3, 4, 143552);

  // Generar archivo DOT para el grafo completo
  grafo.generarArchivoDOT("grafo_completo.dot");
  grafo.generarPNG("grafo_completo.dot");

  cout << "Aristas del Árbol de Expansión Mínima (Algoritmo de Kruskal):\n";
  vector<vector<int>> mst = grafo.kruskal();

  // Generar archivo DOT para el árbol de expansión mínima
  Grafo mst_grafo(n);
  for (int i = 0; i < n; ++i) {
    for (int j = i + 1; j < n; ++j) {
      if (mst[i][j] > 0) {
        mst_grafo.agregarConexion(i, j, mst[i][j]);
      }
    }
  }
  mst_grafo.generarArchivoDOT("mst.dot");
  mst_grafo.generarPNG("mst.dot");

  return 0;
}
