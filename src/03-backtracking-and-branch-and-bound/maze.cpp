#include<iostream>
#include<vector>

using namespace std;

class laberinto {
private: 
    vector<vector<int>> matrizBooleana;

public:
    //Constructor
    laberinto(int n) : matrizBooleana(n, vector<int>(n, true)) {}

    //tam de la matriz
    int GetSize() {
        return matrizBooleana.size();
    }

    //añadir muro
    void muro(int i,int j){
        matrizBooleana[i][j]=false;
    }

    // Función para imprimir la matriz booleana
    void imprimirMatrizBooleana() {
        for(int i = 0; i < matrizBooleana.size(); i++) {
            for(int j = 0; j < matrizBooleana[i].size(); j++) {
                if(matrizBooleana[i][j]) cout << "True" << "  ";
                else cout << "False" << " ";
            }
            cout << "\n";
        }
    }

    bool GetValor(int i,int j){
        return matrizBooleana[i][j];
    }
};

