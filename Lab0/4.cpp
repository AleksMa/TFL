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
bool gen_elements(const set<int> &base, set<int> &elements) {
  bool get_new = false;
  set<int> new_elements;
  for (auto base_elem : base) {
    for (auto mul : elements) {
      int left = Matrix[base_elem][mul];
      if (elements.find(left) == elements.end()) {
        new_elements.insert(left);
        get_new = true;
        continue;
      }
      int right = Matrix[mul][base_elem];
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
  else {
    return gen_elements(base, elements);
  }
}

// Запуск проверки на порождающее множество
bool is_generator(set<int> &base) {
  if (base.size() == N)
    return true;
  set<int> elements;
  elements.insert(base.begin(), base.end());
  return gen_elements(base, elements);
}

// Рекурсивная генерация m-местных сочетаний на N элементах с проверкой порождающих
void generators_rec(const set<int> &base, int m, set<int> comb) {
  if (m == 0) {
    bool fl = is_generator(comb);
    //if (fl) {
    for (auto t : comb) {
      //cout << get_elem(t) << " ";
      cout << t << " ";
    }
    cout << endl;
    found_generators = true;
    //}
  } else {
    set<int> base_new;
    base_new.insert(base.begin(), base.end());
    for (auto q : base) {
      if (base.size() < m)
        return;
      base_new.erase(q);
      set<int> comb_new;
      comb_new.insert(comb.begin(), comb.end());
      comb_new.insert(q);
      generators_rec(base_new, m - 1, comb_new);
    }
  }
}

void generators(const set<int> &base, int m) {
  set<int> c;
  generators_rec(base, m, c);
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

  set<int> base;
  for (int i = 0; i < N; ++i)
    base.insert(i);

  int m = 1;
  cout << "Порождающие:\n";
  //while (!found_generators)
  while (m < 4)
    generators(base, m++);

  cout << endl;

  for (int i = 0; i < N; ++i) {
    cout << get_elem(i) << ":" << endl;
    cout << (is_left_e(i) ? "" : "не ") << "левая единица" << endl;
    cout << (is_right_e(i) ? "" : "не ") << "правая единица" << endl;
  }

}
