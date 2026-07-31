#include <iostream>
#include <vector>
#include <algorithm>
#include <climits>

using namespace std;

int Oro(const vector<vector<char>>& mapa, int i, int j) {
    return mapa[i][j] == 'O' ? 1 : 0;
    /*
    vamos a devolver el número de bolsas de oro que haya
    en funcion de si en la casilla (i,j) esta marcada o no 
    con O (Oro)
    */ 
    
}

//Algoritmo de calculo del coste optimo

pair<vector<vector<int>>, int> Max_oro(const vector<vector<char>>& mapa, int n, int m) {
    vector<vector<int>> T(n, vector<int>(m, 0));
    T[0][0] = Oro(mapa, 0, 0); // Inicializamos la primera casilla

    for (int i = 0; i < n; ++i) {
        for (int j = 0; j < m; ++j) {
            //Recorremos nuestra matriz que representa el mapa del juego
            if (mapa[i][j] == 'M') { // Si en la posicion (i,j) hay un muro
                T[i][j] = INT_MIN; //corresponde con el -infinito
            } else {//Si no hay un muro puede ser que en la casilla haya o no oro
                int oro = Oro(mapa, i, j);
                // Evitamos reescribir la celda inicial (0,0)
                if (!(i == 0 && j == 0)) {
                    if (i > 0 && j > 0) {
                        if (T[i-1][j-1] != INT_MIN) {
                            T[i][j] = max(T[i][j], T[i-1][j-1] + oro);
                        }
                    }
                    if (i > 0) {
                        if (T[i-1][j] != INT_MIN) {
                            T[i][j] = max(T[i][j], T[i-1][j] + oro);
                        }
                    }
                    if (j > 0) {
                        if (T[i][j-1] != INT_MIN) {
                            T[i][j] = max(T[i][j], T[i][j-1] + oro);
                        }
                    }
                    // Si todas las anteriores fueron INT_MIN, esta debe serlo también
                    if (T[i][j] == INT_MIN) {
                        T[i][j] = INT_MIN; // esto es redundante pero claro
                    }
                }
            }
        }
    }

    int V = T[n-1][m-1];
    return make_pair(T, V); //Devolvemos la matriz y el numero max de oro que podemos conseguir
}


vector<pair<int, int>> Recuperar_solucion(const vector<vector<int>>& T, const vector<vector<char>>& mapa, int n, int m) {
    vector<pair<int, int>> ruta; // estructura donde vamos a almacenar la ruta solucion
    int i = n - 1, j = m - 1; // comenzamos en la casilla final

    while (i > 0 || j > 0) { //iteramos mientras podamos
        ruta.push_back(make_pair(i, j)); //añadimos la celda actual a la ruta
        int oro = Oro(mapa, i, j); // calculamos el oro de la celda actual
        if (i > 0 && j > 0 && T[i][j] == T[i-1][j-1] + oro) { //si coincide el == quiere decir que se llego a la solucion mediante esa celda
            i = i - 1;
            j = j - 1;
        } else if (i > 0 && T[i][j] == T[i-1][j] + oro) {
            i = i - 1;
        } else if (j > 0 && T[i][j] == T[i][j-1] + oro) {
            j = j - 1;
        }
    }

    ruta.push_back(make_pair(0, 0)); // añadimos la celda final para completar el proceso de rutas
    reverse(ruta.begin(), ruta.end()); // funcion que lo que hace es revertir el orden de la ruta, para que se vea desde 0,0 hasta el final
    return ruta;
}

int main() {
    vector<vector<char>> mapa = {
        {' ', 'O', ' ', 'M', 'O'},
        {' ', 'M', 'O', ' ', ' '},
        {' ', ' ', 'M', ' ', 'O'},
        {'O', ' ', ' ', 'O', ' '}
    };
    int n = 4;
    int m = 5;
    auto [T, V] = Max_oro(mapa, n, m); // autoasinacion, T recibe el first del pair y V el second del pair
    vector<pair<int, int>> ruta = Recuperar_solucion(T, mapa, n, m);

    cout << "Matriz T:" << endl;
    for (const auto& fila : T) { //recorremos la matriz de una manera distinta de la habitual
        for (int val : fila) {
            if (val == INT_MIN)
                cout << "-∞" << "\t";
            else
                cout << val << "\t";
        }
        cout << endl;
    }

    cout << "Máximo oro recogido: " << V << endl;
    cout << "Ruta: ";
    for (const auto& [x, y] : ruta) {
        cout << "(" << x << "," << y << ") ";
    }
    cout << endl;

    return 0;
}
