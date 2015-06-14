#include <algorithm>
#include <iostream>
#include <set>
#include <string>

auto check(const std::string& str) noexcept -> bool {
  auto chars = std::multiset<char>{std::begin(str), std::end(str)};
  auto foundOdd = false;
  for (auto it = std::begin(chars); it != std::end(chars); it = chars.upper_bound(*it)) {
    if (chars.count(*it) % 2 == 1) {
      if (foundOdd) {
        return false;
      }
      foundOdd = true;
    }
  }
  return true;
}

int main() {
  auto word = std::string{};
  std::cin >> word;

  if (check(word)) {
    std::cout << "yes\n";
  } else {
    std::cout << "no\n";
  }
}
