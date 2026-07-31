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

void copiar_submatriz (int i1, int j1, int i2, int j2, int diferencia, int **partidos){

    for (int i=i1; i<i2; ++i)
        for (int j=j1; j<j2; ++j){
            partidos[i+diferencia][j+diferencia] = partidos[i][j];
            partidos[i][j+diferencia] = partidos[i][j]+diferencia;
            partidos[i+diferencia][j] = partidos[i][j]+diferencia;
        }
}

void rellenar_columna (int n, int **partidos){
    int valor=n/2+1;
    for (int i=0; i<n; ++i){
        partidos[i][(n-1)/2]=valor++;
        if (valor==n+1)
            valor=1;
    }
}

int dyv(int **partidos, int n){

    if (n == 2){
        partidos[0][0]=2;
        partidos[1][0]=1;
        return 0;
    }

    dyv(partidos, n/2);
    copiar_submatriz (0, 0, n/2, n/2 -1, n/2, partidos);
    rellenar_columna(n, partidos);

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

    dyv(partidos, n);

    for (int i=0; i<n; ++i){
        for (int j=0; j<n-1; ++j)
            cout << partidos[i][j] << " ";
        cout << endl;
    }

    return 0;

}