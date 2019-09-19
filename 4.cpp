// Mamaev Alexey

// Написать программу:
//a. проверяющую ассоциативность операции,
//b. найти порождающие,
//c. проверить наличие единицы справа и слева.

#include "bits/stdc++.h"

using namespace std;

const int N = 4;

enum Elem {
  e, f, g, a
//0  1  2  3
};

//e, f, g, a
const Elem Matrix[N][N] = {{e, e, g, e},  // e
                           {e, f, f, f},  // f
                           {e, g, a, a},  // g
                           {a, e, e, e}}; // a

char get_elem(int elem) {
  if (elem == e)
    return 'e';
  if (elem == f)
    return 'f';
  if (elem == g)
    return 'g';
  if (elem == a)
    return 'a';
  return ' ';
}

bool is_assoc() {
  bool assoc = true;
  for (int i = 0; i < N; ++i) {
    for (int j = 0; j < N; ++j) {
      for (int k = 0; k < N; ++k) {
        if (Matrix[Matrix[i][j]][k] != Matrix[i][Matrix[j][k]]) {
          cout << "Нет ассоциативности: " << endl;
          cout << "(" << get_elem(i) << " * " << get_elem(j) << ") * " << get_elem(k) << " = "
               << get_elem(Matrix[Matrix[i][j]][k]) << endl;
          cout << get_elem(i) << " * (" << get_elem(j) << " * " << get_elem(k) << ") = "
               << get_elem(Matrix[i][Matrix[j][k]]) << endl << endl;
          assoc = false;
          break;
        }
      }
      if (!assoc)
        break;
    }
    if (!assoc)
      break;
  }
  return assoc;
}

bool gen_elements(int elem, set<int> &elements) {
  bool get_new = false;
  set<int> new_elements;
  for (auto mul:elements) {
    int left = Matrix[elem][mul];
    if (elements.find(left) == elements.end()) {
      //cout << get_elem(elem) << ": " << get_elem(left) << endl;
      new_elements.insert(left);
      get_new = true;
    }
    int right = Matrix[mul][elem];
    if (elements.find(right) == elements.end()) {
      //cout << get_elem(elem) << ": " << get_elem(right) << endl;
      new_elements.insert(right);
      get_new = true;
    }
  }
  elements.insert(new_elements.begin(), new_elements.end());
  if (!get_new)
    return false;
  else if (elements.size() == N)
    return true;
  else {
    return gen_elements(elem, elements);
  }
}

bool is_generator(int elem) {
  set<int> elements;
  elements.insert(elem);
  return gen_elements(elem, elements);
}

bool is_left_e(int elem) {
  for (int i = 0; i < N; ++i) {
    if (elem != Matrix[elem][i])
      return false;
  }
  return true;
}

bool is_right_e(int elem) {
  for (int i = 0; i < N; ++i) {
    if (elem != Matrix[i][elem])
      return false;
  }
  return true;
}

int main() {
  is_assoc();

  for (int i = 0; i < N; ++i) {
    cout << get_elem(i) << ": " << (is_generator(i) ? "порождающий" : "не порождающий") << endl;
  }

  cout << endl;

  for (int i = 0; i < N; ++i) {
    cout << get_elem(i) << ":" << endl;
    cout << (is_left_e(i) ? "" : "не ") << "левая единица" << endl;
    cout << (is_right_e(i) ? "" : "не ") << "правая единица" << endl;
  }

}
