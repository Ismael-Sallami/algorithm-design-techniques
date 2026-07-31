/*Determinar si un cierto numero natural N puede expresarse como producto de
tres numeros naturales consecutivos.*/

#include <algorithm>
#include <chrono>
#include <fstream>
#include <iostream>
#include<cmath>

using namespace std;

bool divideYVenceras(long long n,long long izq,long long der) { 
    if(izq>der){
        return false;
    }
    long long x =(izq+der)/2;
    long long producto = x * (x + 1) * (x + 2);
    if (producto == n) {
        return true;
    } else if (producto < n) {
        return divideYVenceras(n, x + 1, der);
    } else {
        return divideYVenceras(n, izq, x - 1);
    }
}

int main(int argc, char * argv[]) { 
    
    if (argc != 2){
        cerr << "Se debe ejecutar: ./productoTresElementos <n_a_comprobar>" << endl;
        return -1;
    }
    
    int n=atoi(argv[1]);
    bool verdad=divideYVenceras(n,1,n);
    if(verdad)
        cout<<"Verdad segun divide y venceras para n:" <<n<<endl;
    else
        cout << "No es verdad según divide y venceras para n:" <<n<<endl;

    return 0; 

}