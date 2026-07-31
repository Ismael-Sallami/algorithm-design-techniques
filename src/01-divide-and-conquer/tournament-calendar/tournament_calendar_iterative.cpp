/*Se organiza un torneo con n participantes. Cada participante tiene que
competir exactamente una vez con todos los posibles oponentes. Además, cada
participante tiene que jugar exactamente un partido cada día. Por concreción, y
sin perdida de generalidad, puede suponerse que las competiciones se celebran en
días sucesivos y que cada participante compite una vez por día. Podemos suponer
que el número de participantes es potencia de dos, lo que nos simplificará el
problema (no es necesario que haya jornadas de descanso). Por lo tanto n = 2^k
participantes, con k entero positivo. Se pide construir un calendario que
permita que el torneo concluya en n-1 días.*/

#include <iostream>
#include <vector>
#include <chrono>
#include <fstream>

using namespace std;

#define UMBRAL

int algoritmoBasico(int **partidos, int n) { 

    for (int i=0; i<n-1; ++i){
        partidos[0][i] = i+2;
        partidos[i+1][i] = 1;
    }

    int col_inicial_suma=2;

    for (int i=1; i<=n-1; ++i){

        int fila=i;
        
        int contador=i+2;

        int j;
        for (j=col_inicial_suma; contador<=n; ++j){
            if (j == n-1)
                j = 0;
            if (partidos[fila][j]==0)
                partidos[fila][j]=contador++;
 
        }
        
        for (int k=0; k<n-1; ++k){
            int valor = partidos[fila][k];
            if (partidos[valor-1][k]==0)
                partidos[valor-1][k]=fila+1;
        }

        col_inicial_suma+=2;
        if (col_inicial_suma >= n)
            col_inicial_suma = col_inicial_suma % (n-1);

    }

    return 0; 
}

int main(int argc, char * argv[]) { 
    
    if (argc != 2){
        cerr << "Se debe ejecutar: ./campeonato <n_equipos>" << endl;
        return -1;
    }
    
    int n = atoi(argv[1]);

    int **partidos = new int * [n];
    for (int i=0; i<n; ++i){
        partidos[i] = new int[n-1];
        for (int j = 0; j < n-1; ++j) {
            partidos[i][j] = 0; 
        }
    }

    algoritmoBasico(partidos, n);

    for (int i=0; i<n; ++i){
        for (int j=0; j<n-1; ++j)
            cout << partidos[i][j] << " ";
        cout << endl;
    }

    return 0;

}