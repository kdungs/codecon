#include <algorithm>
#include <iostream>
#include <functional>
#include <numeric>
#include <set>
#include <string>
#include <vector>

constexpr auto factorial(std::size_t n) -> std::size_t {
  return (n > 1) ? n * factorial(n - 1) : 1;
}

auto uniquePalindromes(std::string word) -> std::size_t {
  auto chars = std::multiset<char>{std::begin(word), std::end(word)};
  auto counts = std::vector<std::size_t>{};
  auto foundOdd = false;
  for (auto it = std::begin(chars); it != std::end(chars);
       it = chars.upper_bound(*it)) {
    auto count = chars.count(*it);
    if (count % 2 == 1) {
      if (foundOdd) {
        return 0;
      }
      foundOdd = true;
      count -= 1;  // aabbc <=> aabb because there is only one position for c
    }
    counts.emplace_back(count);  // extract unqiue counts
  }
  std::transform(std::begin(counts), std::end(counts), std::begin(counts),
                 [](std::size_t count) { return count / 2; });  // symmetry
  auto sum = std::accumulate(std::begin(counts), std::end(counts), 0u,
                             std::plus<std::size_t>());
  auto prodFactorials =
      std::accumulate(std::begin(counts), std::end(counts), 1u,
                      [](std::size_t acc, std::size_t count) {
                        return acc * factorial(count);
                      });
  return factorial(sum) / prodFactorials;
}


int main() {
  auto word = std::string{};
  std::cin >> word;

  std::cout << uniquePalindromes(word) << '\n';
}
