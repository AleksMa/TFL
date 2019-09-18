// Mamaev Alexey

// Написать программу генерирующую таблицу умножения для Z(17)


#include "bits/stdc++.h"
using namespace std;

const int char_count = 4;

int main() {

  int n;
  cin >> n;

  for (int i = -1; i < n; ++i) {
    for (int j = -1; j < n; ++j) {
      // Printing table
      if (i == -1 && j == -1)
        cout << setw(char_count) << "";
      else if (i == -1 && j != -1)
        cout << setw(char_count) << right << j;
      else if (j == -1 && i != -1)
        cout << setw(char_count - 1) << right << i << "|";
      else {
        cout << setw(char_count) << right << i * j % n;
      }

    }
    cout << endl;
  }

  return 0;
}