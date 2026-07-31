
#include <iostream>
#include <vector>
#include <stack>
#include <algorithm>
using namespace std;

int tiempo_min(int origen, int destino, vector<vector<int>> tiempos, vector<vector<int>> & tiempos_min, 
    vector<vector<int>> & antecesores){

    tiempos_min = tiempos;
    for (int i=0; i<4; ++i) // Inicialmente, no se harán escalas y el antecesor será el aeropuerto del que vuelen directamente
        for (int j=0; j<4; ++j)
            antecesores[i][j]= i;

    int t_escala=0;
    for (int k=0; k<4; ++k)
        for (int i=0; i<4; ++i)
            for (int j=0; j<4; ++j)
                if (k != i && k != j){
                    t_escala = tiempos_min[i][k] + tiempos_min[k][j] + 1;
                    tiempos_min[i][j] = min(tiempos_min[i][j], t_escala);
                    if (tiempos_min[i][j] == t_escala) // Si hace escala, ponemos dónde ha hecho escala en la matriz de antecesores
                        antecesores[i][j] = k;
                }

    return tiempos_min[origen][destino];
}

void imprimir_tiempos(const vector<vector<int>> & t){
    for (int i=0; i<4; ++i){
        for (int j=0; j<4; ++j)
            cout << t[i][j] << " ";
        cout << endl;
    }
}

vector<int> recuperar_sol(int origen, int destino, const vector<vector<int>> & antecesores){
    int col=destino;
    stack<int> s;
    vector<int> sol;
    s.push(destino);

    int anterior;
    do{
        anterior=antecesores[origen][col];
        s.push(anterior);
        col=anterior;
    } while (anterior != origen);

    while (! s.empty()){
        sol.push_back(s.top());
        s.pop();
    }

    return sol;

}

int main(){

    vector<vector<int>> tiempos (4, vector<int>(4)), tiempos_min(4, vector<int>(4)), antecesores(4, vector<int>(4));
    tiempos[0][0]=0;
    tiempos[0][1]=2;
    tiempos[0][2]=1;
    tiempos[0][3]=3;
    tiempos[1][0]=7;
    tiempos[1][1]=0;
    tiempos[1][2]=9;
    tiempos[1][3]=2;
    tiempos[2][0]=2;
    tiempos[2][1]=2;
    tiempos[2][2]=0;
    tiempos[2][3]=1;
    tiempos[3][0]=3;
    tiempos[3][1]=4;
    tiempos[3][2]=8;
    tiempos[3][3]=0;

    cout << "Tiempos originales: " << endl;
    imprimir_tiempos(tiempos);

    int n = tiempo_min(1, 0, tiempos, tiempos_min, antecesores);

    cout << endl << "Tiempos mínimos: " << endl;
    imprimir_tiempos(tiempos_min);

    cout << endl << "Antecesores: " << endl;
    imprimir_tiempos(antecesores);

    vector<int> sol=recuperar_sol(1, 0, antecesores);

    cout << endl << "Tiempo en llegar de 1 a 0: " << n << endl;

    cout << endl << "Aeropuertos para llegar de 1 a 0: " << endl;

    for (int i=0; i<sol.size(); ++i)
        cout << sol[i] << " ";
    cout << endl;

    return 0;

}