// Mamaev Alexey

// Написать программу:
// a. проверяющую ассоциативность операции,
// b. найти порождающие,
// c. проверить наличие единицы справа и слева.

#include "bits/stdc++.h"

using namespace std;

const int N = 4;
bool found_generators = false;

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

// Проверка на ассоциативность полным перебором (с выводом контрпримера при отсутствии ассоциативности)
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

// Последовательное порождение некоторым множеством элементов всех возможных значений
// Породили все элементы - порождающее множество
bool is_generator_rec(set<int> elements) {
  while (true) {
    bool get_new = false;
    set<int> new_elements;
    for (auto elem : elements) {
      for (auto mul : elements) {
        int left = Matrix[elem][mul];
        if (elements.find(left) == elements.end()) {
          new_elements.insert(left);
          get_new = true;
          continue;
        }
        int right = Matrix[mul][elem];
        if (elements.find(right) == elements.end()) {
          new_elements.insert(right);
          get_new = true;
          continue;
        }
      }
    }
    elements.insert(new_elements.begin(), new_elements.end());
    if (!get_new)
      return false;
    else if (elements.size() == N)
      return true;
  }
}

// Запуск проверки на порождающее множество
bool is_generator(set<int> &elements) {
  if (elements.size() == N)
    return true;
  return is_generator_rec(elements);
}

void make_generators_set(int k) {
  int j = 0;
  set<int> generators;
  while (j < N) {
    if (1 << j & k) {
      generators.insert(j);
    }
    j++;
  }
  if (is_generator(generators)) {
    for (auto t : generators) {
      cout << get_elem(t) << " ";
    }
    cout << endl;
  }
}

void make_all_combs(vector<int> &base) {
  cout << "Порождающие:\n";
  int k = 1, max = 1 << N;
  while (k < max) {
    make_generators_set(k);
    k++;
  }
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

  vector<int> base(N);
  for (int i = 0; i < N; ++i)
    base[i] = i;

  make_all_combs(base);

  cout << endl;

  for (int i = 0; i < N; ++i) {
    cout << get_elem(i) << ":" << endl;
    cout << (is_left_e(i) ? "" : "не ") << "левая единица" << endl;
    cout << (is_right_e(i) ? "" : "не ") << "правая единица" << endl;
  }

}
