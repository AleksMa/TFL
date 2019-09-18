// Mamaev Alexey
// Написать программу генерирующую таблицу умножения для Z(17)

#include "bits/stdc++.h"
using namespace std;

int main() {

  int q, ql, n;
  cin >> q >> n;
  ql = q;

  vector<int> dest(n);

  for (int i = 0; i < n; ++i) {
    cin >> dest[i];
  }

  do {
    cout << q << " ";
    q = dest[q - 1];
  } while (q != ql);

  return 0;
}