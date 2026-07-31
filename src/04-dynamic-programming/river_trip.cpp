#include<iostream>
#include<vector>
#include<algorithm>

#define matriz vector<vector<int>>
#define camino vector<int>

using namespace std;

int calcviajeopt(matriz rio, matriz& opt, int salida, int destino){
    if (destino<salida){
        throw invalid_argument("No puedes subir a contracorriente");
    }

    int sobrantes=opt[salida].size()-1-destino;

    for(int i=destino-1; i>=salida; i--){
        for(int j=destino; j > i; j--){
            if (rio[i][j]==INT32_MAX){
                opt[i][j]=INT32_MAX;
            }else{
                opt[i][j]=rio[i][j] + *min_element(opt[j].begin()+j+1,opt[j].end()-sobrantes);
            }
        }  
            
    }
    return *min_element(opt[salida].begin()+salida+1,opt[salida].end()-sobrantes);
}

camino recuperarsol(matriz rio, matriz opt, int salida, int destino){
    if (destino<salida){
        throw invalid_argument("No puedes subir a contracorriente");
    }

    camino sol;
    if (salida==destino){
        sol={destino};
    } else {
        int sobrantes=opt[salida].size()-1-destino;

        int minimo=*min_element(opt[salida].begin()+salida+1,opt[salida].end()-sobrantes);
        int actual= (find(opt[salida].begin()+salida+1,opt[salida].end()-sobrantes,minimo)-opt[salida].begin());
        sol.push_back(salida);
        sol.push_back(actual);
        
        while(actual!=destino){
            minimo=*min_element(opt[actual].begin()+actual+1,opt[actual].end()-sobrantes);
            actual= (find(opt[actual].begin()+actual+1,opt[actual].end()-sobrantes,minimo)-opt[actual].begin());
            sol.push_back(actual);
        }
    }
    return sol;
}

int main(){
    matriz rio = 
    {
        {0,3,3,INT32_MAX,INT32_MAX},
        {INT32_MAX,0,4,7,INT32_MAX},
        {INT32_MAX,INT32_MAX,0,2,3},
        {INT32_MAX,INT32_MAX,INT32_MAX,0,2},
        {INT32_MAX,INT32_MAX,INT32_MAX,INT32_MAX,0}
    };

    matriz opt=
    {
        {0,0,0,0,0},
        {INT32_MAX,0,0,0,0},
        {INT32_MAX,INT32_MAX,0,0,0},
        {INT32_MAX,INT32_MAX,INT32_MAX,0,0},
        {INT32_MAX,INT32_MAX,INT32_MAX,INT32_MAX,0}
    };
    cout << "Mi rio tiene los siguientes costes: " << endl;
    for (int i=0; i < rio.size();i++){
        for (int j=0; j<rio.size(); j++){
            if (j<i && rio[i][j] == INT32_MAX){
                cout << "- ";
            } else if (rio[i][j] == INT32_MAX){
                cout << "∞ ";
            } else {
                cout << rio[i][j] << " ";
            }
        }
        cout << endl << endl;
    }

    cout << "El minimo de este rio es: " << calcviajeopt(rio,opt,0,4) << endl;

    camino sol=recuperarsol(rio,opt,0,4);
    cout << "El camino que minimiza este coste es el siguiente: " << endl;

    for (int i=0; i<sol.size();i++){
        cout << sol[i] << " ";
    }
    cout << endl;
}
