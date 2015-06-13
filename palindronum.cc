#include <algorithm>
#include <iostream>
#include <string>

auto isPalindrome(const std::string& str) noexcept -> bool {
  auto l = std::begin(str);
  auto r = std::end(str);
  --r;

  while (std::distance(l, r) > 0u) {
    if (*l != *r) {
      return false;
    }
    ++l;
    --r;
  }
  return true;
}

auto stepsToPalindrome(const std::string& str) -> std::size_t {
  for (auto r = std::end(str); r > std::begin(str); --r) {
    auto pal = std::string{};
    pal.reserve(str.size() * 2);
    std::copy(r, std::end(str), std::back_inserter(pal));
    std::reverse(std::begin(pal), std::end(pal));
    std::copy(std::begin(str), std::end(str), std::back_inserter(pal));
    if (isPalindrome(pal)) {
      return pal.size();
    }
  }
  return 0u;  // should never happen!
}

int main() {
  auto input = std::string{};
  std::cin >> input;
  std::cout << stepsToPalindrome(input) << '\n';
}
