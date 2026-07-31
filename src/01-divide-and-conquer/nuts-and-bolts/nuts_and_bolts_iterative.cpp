#include <algorithm>
#include <cstdlib>
#include <cstring>
#include <iostream>
#include <vector>

using namespace std;

bool test(const vector<int> &v1, const vector<int> &v2) {
  if (v1.size() != v2.size()) {
    return false;
  }
  for (size_t i = 0; i < v1.size(); i++) {
    if (v1[i] != v2[i]) {
      return false;
    }
  }
  return true;
}

void algoritmoBasico(vector<int> &arr1, vector<int> &arr2) {
  int maxElement = *max_element(arr1.begin(), arr1.end());
  int minElement = *min_element(arr1.begin(), arr1.end());
  int range = maxElement - minElement + 1;

  vector<int> count(range, 0);

  for (size_t i = 0; i < arr1.size(); ++i) {
    count[arr1[i] - minElement]++;
  }

  for (int i = 1; i < range; ++i) {
    count[i] += count[i - 1];
  }

  vector<int> output(arr1.size());

  for (size_t i = arr1.size() - 1; i >= 0; --i) {
    output[count[arr1[i] - minElement] - 1] = arr1[i];
    count[arr1[i] - minElement]--;
  }

  for (size_t i = 0; i < arr1.size(); ++i) {
    arr1[i] = output[i];
  }

  maxElement = *max_element(arr2.begin(), arr2.end());
  minElement = *min_element(arr2.begin(), arr2.end());
  range = maxElement - minElement + 1;

  vector<int> count2(range, 0);

  for (size_t i = 0; i < arr2.size(); ++i) {
    count2[arr2[i] - minElement]++;
  }

  for (int i = 1; i < range; ++i) {
    count2[i] += count2[i - 1];
  }

  vector<int> output2(arr2.size());

  for (int i = arr2.size() - 1; i >= 0; --i) {
    output2[count2[arr2[i] - minElement] - 1] = arr2[i];
    count2[arr2[i] - minElement]--;
  }

  for (size_t i = 0; i < arr2.size(); ++i) {
    arr2[i] = output2[i];
  }
}
int main() {
  vector<int> tornillos = {4, 2, 5, 1, 3};
  vector<int> tuercas = {3, 2, 1, 5, 4};

  cout << "Usando el algoritmo básico:\n";
  algoritmoBasico(tornillos, tuercas);
  for (size_t i = 0; i < tornillos.size(); ++i) {
    cout << "Tornillo " << tornillos[i] << " emparejado con tuerca "
         << tuercas[i] << endl;
  }
  if (test(tornillos, tuercas))
    cout << "Los vectores coinciden\n";
  else
    cout << "Los vectores no coinciden\n";

  return 0;
}
