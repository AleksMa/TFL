// Mamaev Alexey

// Дана подстановка s1 порядка 7 и какой-то ее элемента q, написать
// программу, вычисляющую орбиту элемента q.

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