/*
Una red de sensores inalámbrica está compuesta por múltiples nodos sensores
desplegados en un entorno (invernadero, campo de cultivo, instalación
industrial, perímetro de vigilancia de seguridad, ...), cada uno equipado con un
transmisor de datos inalámbrico de un alcance reducido. Cada cierto tiempo, cada
sensor debe enviar los datos recolectados del entorno a un servidor de datos
central (sink). Sin embargo, la distancia entre el nodo sensor y el servidor
central puede ser elevada como para enviar todos los datos directamente, por lo
que será necesario, en ocasiones, enviar los datos por otros nodos sensores que
hagan de enlace intermedio (ver Figura 1). Nos interesa enviar los datos con la
máxima velocidad posible por lo que, para cada par de nodos sensores de la red n
i, nj (entre los que se incluye el servidor central), conocemos el tiempo de
envío entre ambos nodos como t(ni, nj) – el tiempo que se tarda en enviar los
datos desde el nodo ni al nodo nj) -. El valor t(ni, nj) podría tener valor
infinito si la red inalámbrica no permite enviar datos directamente desde el
nodo ni hasta el nodo nj. Se pide: desarrollar un algoritmo (greedy) que nos
permita conocer por cuáles nodos sensores intermedios debe enviar los datos cada
nodo sensor, hasta llegar el servidor central, de modo que se tarde el mínimo
tiempo en la transmisión desde cada nodo hasta el servidor central.
*/


/*
La implementación de grafo que vamos a seguir es la de tener una
matriz de adyacencia de manera que tanto en las filas como en las columnas 
vamos a tener los nodos y en la posición [i][j] (siendo i y j los nodos)
un 0 si los nodos no están conectados directamente por una arista, y
1 en caso contrario
*/


#include<iostream>
#include<vector>
#include<climits>
#include<queue>

#define INF INT_MAX

using namespace std;

//Inicializamos la matriz
void crearMatriz(vector<vector<int>>& matriz, int n) {
    for(int i = 0; i < n; i++) {
        vector<int> row(n, 0);
        matriz.push_back(row);
    }
}

//Definimos la función para agregar las relaciones entre los nodos.
void anadirConexion(vector<vector<int>>& matriz, int a, int b, int peso) {
    matriz[a][b] = peso;
    matriz[b][a] = peso;
}

//Implementamos una función que nos devuelva la lista de adyacencia.
void crearLista(vector<vector<int>>& adjList, int n) {
    adjList.resize(n);
}

//Función usada para agregar un vecino
void agregarVecino(vector<vector<int>>& adjList, int a, int b) {
    adjList[a].push_back(b);
    adjList[b].push_back(a);
}

//Función para imprimir la lista de adyacencia
void imprimirLista(vector<vector<int>>& adjList) {
    for(int i = 0; i < adjList.size(); i++) {
        cout << "Nodo " << i << ": ";
        for(int j = 0; j < adjList[i].size(); j++) {
            cout << adjList[i][j] << " ";
        }
        cout << "\n";
    }
}

//Función para imprimir la matriz de adyacencia
void imprimirMatriz(vector<vector<int>>& matriz) {
    for(int i = 0; i < matriz.size(); i++) {
        for(int j = 0; j < matriz[i].size(); j++) {
            cout << matriz[i][j] << " ";
        }
        cout << "\n";
    }
}

// Definimos un par de enteros para representar un nodo y su distancia
typedef pair<int, int> pii;

vector<int> dijkstra(vector<vector<int>>& matriz, int inicio, int n) {
    vector<int> distancia(n, INF);
    vector<vector<int>> predecesores(matriz.size()); 
    distancia[inicio] = 0;

    // Usamos una cola de prioridad para almacenar los nodos a visitar
    priority_queue<pii, vector<pii>, greater<pii>> pq;
    pq.push({0, inicio});

    while (!pq.empty()) {
        int u = pq.top().second;
        int dist_u = pq.top().first;
        pq.pop();

        // Si la distancia actual es mayor que la distancia almacenada, no procesamos
        if (dist_u > distancia[u]) continue;

        // Recorremos los vecinos de u
        for (int v = 0; v < n; ++v) {
            // Si hay un camino de u a v (que corresponde con que en la matriz de 
            //adyacencia haya un valor distinto de 0 en la pos i j, 
            //siendo i,j los nodos) 
            //y la distancia de inicio a u más la distancia de u a v es menor que la distancia almacenada para v
            if (matriz[u][v] && distancia[u] + matriz[u][v] < distancia[v]) {
                distancia[v] = distancia[u] + matriz[u][v];
                pq.push({distancia[v], v});
                //vamos a ir añadiendo a la lista de predecesores todos los que vamos recorriendo de 
                //esta manera lo que hacemos es
                // cada vez que vamos añadir uno añadimos los que ya estaban y acto seguido por el que vamos a pasar ahora
                predecesores[v].insert(predecesores[v].begin(), predecesores[u].begin(), predecesores[u].end());
                // Agregamos v al final de la lista de predecesores de v
                predecesores[v].push_back(v);
            }
        }
    }

    // Imprimir las distancias más cortas desde el origen
    for (int i = 0; i < matriz.size(); i++) {
        if (distancia[i] == INF) {
            cout << "El vértice " << i << " es inalcanzable desde el origen" << endl;
        } else {
            cout << "Distancia del origen al vértice " << i << ": " << distancia[i] << endl;
        }
    }

    cout << "La lista de predecesores es: " << endl;

    for(int i=0;i<matriz.size();i++){
        for(int j=0;j<predecesores[i].size();j++){
            cout << predecesores[i][j] << " ";
        }
        cout << endl;
    }
    cout << endl;

    return distancia;
}

// int main() {
//     int n;
//     cout << "Introduce el número de nodos del grafo de la red de sensores inalámbrica: ";
//     cin >> n;

//     vector<vector<int>> matriz;
//     crearMatriz(matriz, n);
//     vector<vector<int>> adjList;
//     crearLista(adjList, n);

//     int n_conex;
//     cout << "Dime el número de conexiones: ";
//     cin >> n_conex;

//     while (n_conex > 0) {
//         int a, b, p;
//         cout << "nodos que tienen conexión y su peso: ";
//         cin >> a >> b >> p;
//         anadirConexion(matriz, a, b,p);
//         agregarVecino(adjList, a, b);
//         n_conex--;
//     }

//     cout << "Matriz de adyacencia:\n";
//     imprimirMatriz(matriz);
//     cout << "Lista de adyacencia:\n";
//     imprimirLista(adjList);

//     //Uso del algoritmo de Dijkstra

//     int inicio, fin;
//     cout << "Introduce el nodo inicial y el nodo final: ";
//     cin >> inicio >> fin;

//     vector<int> distancias = dijkstra(matriz,0,n);

//     cout << "La distancia más corta desde " << inicio << " a " << fin << " es: " << distancias[fin] << endl;

//     return 0;

// }

int main(int argc, char *argv[]) {
    int n = 5; // Número de nodos del grafo por defecto
    vector<vector<int>> matriz = {
        {0, 10, 0, 20, 0},
        {10, 0, 15, 0, 25},
        {0, 15, 0, 30, 0},
        {20, 0, 30, 0, 35},
        {0, 25, 0, 35, 0}
    };

    vector<vector<int>> adjList;
    crearLista(adjList, n);

    // Creamos la lista de adyacencia a partir de la matriz
    for (int i = 0; i < n; ++i) {
        for (int j = 0; j < n; ++j) {
            if (matriz[i][j] != 0) {
                agregarVecino(adjList, i, j);
            }
        }
    }

    cout << "Matriz de adyacencia:\n";
    imprimirMatriz(matriz);
    cout << "Lista de adyacencia:\n";
    imprimirLista(adjList);

    // Nodos de inicio y final predefinidos
    int inicio = 0; // Nodo de inicio
    int fin = 4;    // Nodo final

    // Uso del algoritmo de Dijkstra
    vector<int> distancias = dijkstra(matriz, inicio, n);

    cout << "La distancia más corta desde " << inicio << " a " << fin << " es: " << distancias[fin] << endl;

    return 0;
}



