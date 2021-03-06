// Mamaev Alexey

// Написать программу, генерирующую все подстановки, порожденные
// произвольной одной подстановкой


#include "bits/stdc++.h"
using namespace std;

bool equal(vector<int> first, vector<int> second) {
  if (first.size() != second.size())
    return false;

  for (int i = 0; i < first.size(); ++i) {
    if (first[i] != second[i])
      return false;
  }
  return true;
}

int main() {

  int n;
  cin >> n;

  vector<int> source(n), dest(n), next(n);

/*  for (int i = 0; i < n; ++i) {
    cin >> source[i];
  }*/

  for (int i = 0; i < n; ++i) {
    cin >> dest[i];
    next[i] = dest[i];
    source[i] = i + 1;
  }

  for (int i = 0; i < n; ++i) {
    cout << source[i] << " ";
  }
  cout << endl;

  while (!equal(source, next)) {
/*    for (int i = 0; i < n; ++i) {
      cout << source[i] << " ";
    }
    cout << endl;*/

    for (int i = 0; i < n; ++i) {
      cout << next[i] << " ";
      next[i] = dest[next[i] - 1];
    }

    cout << endl;

  }

  return 0;
}