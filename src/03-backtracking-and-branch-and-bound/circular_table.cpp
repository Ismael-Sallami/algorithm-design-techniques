/*
Se va a celebrar una cena de gala a la que asistirán n invitados. Todos se van a
sentar alrededor de una única gran mesa circular, de forma que cada invitado
tendrá sentados junto a él a otros dos comensales (uno a su izquierda y otro a
su derecha). En función de las características de cada invitado (por ejemplo
categoría o puesto, lugar de procedencia,...) existen unas normas de protocolo
que indican el nivel de conveniencia de que dos invitados se sienten en lugares
contiguos (supondremos que dicho nivel es un número entero entre 0 y 100). El
nivel de conveniencia total de una asignación de invitados a su puesto en la
mesa es la suma de todos los niveles de conveniencia de cada invitado con cada
uno de los dos invitados sentados a su lado. Se desea sentar a los invitados de
forma que el nivel de conveniencia global sea lo mayor posible.
*/
#include <cstdlib>
#include <iostream>
#include <utility>
#include <vector>
#include <cmath>
#include <set>
using namespace std;

void algoritmo(vector<vector<int>>& matriz, int n, int inicial, pair<vector<char>,int>& sol, vector<char>& actual, vector<bool>& usado, int& conveniencia) {
    if(inicial == n) {
        int nueva_conveniencia = 0;
        for(int i=0; i<n; i++) {
            int izq = (i-1+n)%n;
            int der = (i+1)%n;
            nueva_conveniencia+= matriz[actual[i]-'a'][actual[izq]-'a'];
            nueva_conveniencia+= matriz[actual[i]-'a'][actual[der]-'a'];
        }
        nueva_conveniencia/=2;
        if(nueva_conveniencia>sol.second) {
            sol.first=actual;
            sol.second=nueva_conveniencia;
        }
    } else {
        for(int i = 0; i < n; i++) {
            if(!usado[i]){
                usado[i]=true;
                actual[inicial]='a'+i;
                algoritmo(matriz, n, inicial+1, sol, actual, usado, conveniencia);
                usado[i]=false;
            }
        }
    }
}

int main() { 
    int n;
    cout << "Ingrese el número de invitados: ";
    cin >> n;
    vector<vector<int>> matriz(n, vector<int>(n));
    for(int i=0; i<n; i++){
        for(int j=i; j<n; j++){ 
            if(i==j) { 
                matriz[i][j]=-1; 
            } else {
                int valor=rand() % 101;
                matriz[i][j]=valor;
                matriz[j][i]=valor;
            }
        }
    }
    
    for(int i=0; i<n; i++) {
        char letra='a'+i;
        cout << letra << ": ";
        for(int j=0; j<n; j++) {
            cout << matriz[i][j] << " ";
        }
        cout << endl;
    }
    pair<vector<char>,int> mesa;
    mesa.second=0;
    vector<char> actual(n);
    vector<bool> usados(n, false);
    int conveniencia = 0;
    algoritmo(matriz, n, 0, mesa, actual, usados, conveniencia);
    for(int i=0; i<mesa.first.size(); i++)
        cout<<mesa.first[i];
    cout<<endl;
    return 0; 
}
