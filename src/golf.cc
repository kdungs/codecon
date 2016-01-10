#include <algorithm>
#include <iostream>
#include <numeric>
#include <vector>

auto solve(const std::vector<std::vector<unsigned>>& map, unsigned target,
           unsigned position, unsigned steps) -> unsigned {
  if (steps > 0u) {
    return std::accumulate(
        std::begin(map[position]), std::end(map[position]), 0u,
        [&map, target, steps](unsigned acc, unsigned newPos) {
          return acc + solve(map, target, newPos, steps - 1);
        });
  }
  if (position == target) {
    return 1u;
  }
  return 0u;
}

int main() {
  const auto map = std::vector<std::vector<unsigned>>{{4, 6},
                                                      {6, 8},
                                                      {7, 9},
                                                      {4, 8},
                                                      {0, 3, 9},
                                                      {},
                                                      {0, 1, 7},
                                                      {2, 6},
                                                      {1, 3},
                                                      {2, 4}};

  auto steps = 0u;
  std::cin >> steps;

  std::cout << solve(map, 9u, 1u, steps) << '\n';
}
