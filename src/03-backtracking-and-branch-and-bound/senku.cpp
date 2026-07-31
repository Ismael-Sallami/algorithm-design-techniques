/*
En el juego (solitario) del senku, también llamado solitario chino, se colocan 32 piezas iguales en un tablero
de 33 casillas, tal y como se indica en la siguiente figura (las “x" corresponden a posiciones no válidas):
Solo se permiten movimientos de las piezas en vertical y horizontal. Una pieza solo puede moverse saltando
sobre otra y situándose en la siguiente casilla, que debe estar vacía. La pieza sobre la que se salta se retira
del tablero. Se consigue terminar con éxito el juego cuando queda una sola pieza en la posición central del
tablero (la que estaba inicialmente vacía). Diseñar e implementar un algoritmo de backtracking que
encuentre una serie de movimientos para llegar con éxito al final del juego.
*/

#include <iostream>
#include <vector>
#include <queue>
using namespace std;

struct movimiento{
    int x_inicial;
    int y_inicial;
    int x_final;
    int y_final;
};

queue<movimiento> encontrar_posibles_movimientos(vector<vector<char>> tablero){

    queue<movimiento> movimientos;
    movimiento m;
    for (int i=0; i<7; ++i)
        for (int j=0; j<7; ++j){
            //Movimientos a la izquierda
            if (i >= 2 && tablero[i][j]=='o' && tablero [i-1][j]=='o' && tablero[i-2][j]==' '){
                m.x_inicial=i;
                m.y_inicial=j;
                m.x_final=i-2;
                m.y_final=j;
                movimientos.push(m);
            }
            //Movimientos a la derecha
            if (i <= 4 && tablero[i][j]=='o' && tablero [i+1][j]=='o' && tablero[i+2][j]==' '){
                m.x_inicial=i;
                m.y_inicial=j;
                m.x_final=i+2;
                m.y_final=j;
                movimientos.push(m);
            }
            //Movimientos arriba
             if (j >= 2 && tablero[i][j]=='o' && tablero [i][j-1]=='o' && tablero[i][j-2]==' '){
                m.x_inicial=i;
                m.y_inicial=j;
                m.x_final=i;
                m.y_final=j-2;
                movimientos.push(m);
            }
            //Movimientos abajo
             if (j <= 4 && tablero[i][j]=='o' && tablero [i][j+1]=='o' && tablero[i][j+2]==' '){
                m.x_inicial=i;
                m.y_inicial=j;
                m.x_final=i;
                m.y_final=j+2;
                movimientos.push(m);
            }
        }

    return movimientos;
}

void hacer_movimiento(vector<vector<char>> & tablero, movimiento m){

    tablero[m.x_inicial][m.y_inicial]=' ';
    tablero[m.x_final][m.y_final]='o';

    if (m.x_inicial == m.x_final){
        if (m.y_final > m.y_inicial)
            tablero[m.x_final][m.y_final-1]=' ';
        else 
            tablero[m.x_final][m.y_final+1]=' ';
    }
    else{
         if (m.x_final > m.x_inicial)
            tablero[m.x_final-1][m.y_final]=' ';
        else 
            tablero[m.x_final+1][m.y_final]=' ';
    }
}

void imprimir_tablero(vector<vector<char>> tablero){
    for (int i=0; i<7; ++i){
        for (int j=0; j<7; ++j)
            cout << tablero[i][j] << " ";
        cout << endl;
    }
}

bool backtracking(vector<vector<char>> tablero, int n_canicas, vector<movimiento> & movs){

    bool es_solucion=false;
    if (n_canicas == 1 && tablero[3][3]=='o')
        es_solucion=true;
    else{
        queue<movimiento> posibles_movimientos = encontrar_posibles_movimientos(tablero);
        while (!posibles_movimientos.empty() && !es_solucion){
            vector<vector<char>> tablero_inicial=tablero;
            hacer_movimiento(tablero, posibles_movimientos.front());
            movs.push_back(posibles_movimientos.front());
            posibles_movimientos.pop();
            es_solucion=backtracking(tablero, n_canicas-1, movs);
            if (!es_solucion){
                tablero=tablero_inicial;
                movs.pop_back();
            }
        }
    }
     
    return es_solucion;
}

void imprimir_movimiento(movimiento m){
    cout << m.x_inicial << " " << m.y_inicial << " a " << m.x_final << " " << m.y_final << endl;
}

int main(){

   vector<vector<char>> tablero {
    {'x', 'x', 'o', 'o', 'o', 'x', 'x'},
    {'x', 'x', 'o', 'o', 'o', 'x', 'x'},
    {'o', 'o', 'o', 'o', 'o', 'o', 'o'},
    {'o', 'o', 'o', ' ', 'o', 'o', 'o'},
    {'o', 'o', 'o', 'o', 'o', 'o', 'o'},
    {'x', 'x', 'o', 'o', 'o', 'x', 'x'},
    {'x', 'x', 'o', 'o', 'o', 'x', 'x'},
   };

    cout << endl;
    imprimir_tablero(tablero);
    vector<movimiento> movs;

    cout << endl << "¿Solución encontrada?" << endl;
    bool sol = backtracking(tablero, 32, movs);
    sol ? cout << "Sí" : cout << "No";
    cout << endl << endl;

    if (sol){
        cout << "Movimientos que nos llevan a una solución: " << endl;
        for (int i=0; i<movs.size(); ++i)
            imprimir_movimiento(movs[i]);
    }
    cout << endl;

    return 0;
}