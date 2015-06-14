#include <iostream>

int main() {
  int score;
  std::cin >> score;

  for (auto co = 0; co <= score / 7; ++co) {
    const auto afterCo = score - 7 * co;
    for (auto tr = 0; tr <= afterCo / 3; ++tr) {
      const auto afterTr = afterCo - 3 * tr;
      if (afterTr % 2 == 0) {
        auto ki = afterTr / 2;
        std::cout << co << ' ' << tr << ' ' << ki << '\n';
      }
    }
  }
}
