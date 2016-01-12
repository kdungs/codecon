#include <iostream>

template <typename T = long long>
T findSolution(T max_money, const T my_price, const T other_price) {
  while (max_money > 0 && (max_money % my_price) != 0) {
    max_money -= other_price;
  }
  if (max_money <= 0) {
    return -1;
  }
  return max_money / my_price;
}

int main() {
  long long a0, o0, m0, x, y, mf;
  std::cin >> a0 >> o0 >> m0 >> x >> y >> mf;

  const auto dm = mf - m0;
  const auto mm = a0 * x + o0 * y - dm;

  const auto a = findSolution(mm, x, y);
  const auto o = findSolution(mm, y, x);

  if (a == -1 || o == -1) {
    std::cout << "Impossible\n";
  } else {
    std::cout << a << ' ' << o << '\n';
  }
}
