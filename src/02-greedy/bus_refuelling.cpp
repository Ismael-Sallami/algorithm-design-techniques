/*
Un autobús realiza una ruta determinada entre su origen y su destino (n
kilómetros en total). Con el tanque de gasolina lleno, el autobús puede recorrer
k kilómetros sin parar. El conductor dispone de un listado con las gasolineras
existentes en su camino, y el punto kilométrico donde se encuentran. Se pide:
Diseñar un algoritmo greedy que determine en qué gasolineras tiene que repostar
el conductor para realizar el mínimo número de paradas posible.
*/

#include <iostream>
#include <vector>
using namespace std;

const int TAM = 5;

/**
 * @brief Método para calcular el mínimo número de paradas que hay que hacer para respotar
 * para realizar una ruta de una distancia determinada.
 * 
 * @param distancias matriz con la distancia entre las gasolineras y el punto de partida
 * @param tam tamaño de la matriz
 * @param n distancia total a recorrer
 * @param k kilómetros que se pueden recorrer con un tanque de gasolina
 * @return vector<int> números de las gasolineras en las que se para a repostar
 */
vector<int> ParadasDeLaRuta(int distancias[][TAM], int tam, int n, int k){

    vector<int> s;
    int punto_actual = 0;

    while (n > k){

        int max_dist = 0;
        int prox_destino = 0;

        for (int i=1; i<tam; ++i)
            if (distancias[punto_actual][i] > max_dist){
                max_dist = distancias[punto_actual][i];
                prox_destino = i;
            }

        if (max_dist <= k){ // Si puedo llegar con un tanque lo añado a mi solución parcial
            s.push_back(prox_destino);
            punto_actual = prox_destino;
            n -= max_dist;
        }
        else // Nunca podré recorrer esa distancia sin parar
            distancias[punto_actual][prox_destino] = distancias[prox_destino][punto_actual] = -1;
    }

    return s;
}

int main() { 

    int distancias[TAM][TAM];

    for (int i=0; i<4; ++i){
        distancias[i][0] = -1;
        distancias[i][i] = 0; 
    }    

    int n = 2000, k = 500;

    distancias[0][1]=200;
    distancias[0][2]=300;
    distancias[0][3]=150;
    distancias[0][4]=600;

    distancias[1][2]=300;
    distancias[2][1]=300;
    distancias[1][3]=150;
    distancias[3][1]=150;
    distancias[1][4]=400;    
    distancias[4][1]=400;    

    distancias[2][3]=80;
    distancias[3][2]=80;
    distancias[2][4]=79;
    distancias[4][2]=79;

    distancias[3][4]=500;
    distancias[4][3]=500;

    vector<int> s = ParadasDeLaRuta(distancias, TAM, n, k);

    cout << "Se parará en las siguientes gasolineras: ";
    for (int i=0; i<s.size(); ++i)
        cout << s[i] << " ";
    cout << endl;
    
    return 0; 
}
