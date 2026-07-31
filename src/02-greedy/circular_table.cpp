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
vector<char> algoritmo(vector<pair<char,vector<int>>> matriz, int n) {
    vector<char> mesa;
    set<char> prohibido;
    prohibido.insert('a'); 
    mesa.push_back('a');
    for(int i = 1; i < n; i++) {
        pair<char, int> mejor = {' ', -1}; 
        char ultimo = mesa.back();
        int indice_ultimo = ultimo - 'a'; 
        for(int j = 0; j < n; j++) {
            char actual = 'a' + j;
            if(actual != ultimo && prohibido.find(actual) == prohibido.end() && matriz[indice_ultimo].second[j] > mejor.second) {
                mejor.first = actual;
                mejor.second = matriz[indice_ultimo].second[j];
            }
        }
        if(mejor.first != ' ') {
            mesa.push_back(mejor.first);
            prohibido.insert(mejor.first);
        } else {
            for(int j = 0; j < n; j++) {
                prohibido.insert('a' + j);
            }
        }
    }
    return mesa;
}

int main() { 
    int n,valor;
    cout << "Ingrese el número de invitados: ";
    cin >> n;
    vector<pair<char,vector<int>>> matriz(n);
    vector<char> mesa;
   for(int i = 0; i < n; i++){
        matriz[i].first = 'a' + i;
        for(int j = 0; j <= i; j++){ 
            int valor = rand() % 101;
            if(i == j) { 
                valor = -1; 
            }
            matriz[i].second.push_back(valor);
            if(i != j) { 
                matriz[j].second.push_back(valor);
            }
        }
    }
    
      for(int i = 0; i < n; i++) {
        cout << matriz[i].first << ": ";
        for(int j = 0; j < n; j++) {
            cout << matriz[i].second[j] << " ";
        }
        cout << endl;
    }
    mesa=algoritmo(matriz,n);
    for(int i=0;i<mesa.size();i++)
        cout<<mesa[i];
    cout<<endl;
    return 0; 
}
