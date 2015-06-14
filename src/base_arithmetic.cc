#include <algorithm>
#include <fstream>
#include <iostream>
#include <string>
#include <vector>

auto isHexChar(char c) noexcept -> bool { return c >= 'A' && c <= 'F'; }

auto charToDigit(char c) noexcept -> int {
  if (isHexChar(c)) {
    return 10 + (c - 'A');
  }
  return c - '0';
}

auto findBase(const std::string& str) noexcept -> int {
  return charToDigit(
      *std::max_element(std::begin(str), std::end(str), [](char lhs, char rhs) {
        return charToDigit(lhs) < charToDigit(rhs);
      })) + 1;
}

auto bestConversion(const std::string& str) noexcept -> long long {
  return std::stoll(str, nullptr, findBase(str));
}

int main() {
  auto line = std::string{};
  getline(std::cin, line);
  auto x = bestConversion(line);
  getline(std::cin, line);
  auto y = bestConversion(line);
  std::cout << x + y << '\n';
}
