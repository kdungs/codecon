#include <algorithm>
#include <cassert>
#include <cmath>
#include <iostream>
#include <iterator>
#include <numeric>
#include <sstream>
#include <string>
#include <vector>

using Row = std::vector<double>;
using Rows = std::vector<Row>;

double distance(const Row& lhs, const Row& rhs) {
  assert(lhs.size() == rhs.size());

  auto sqdists = Row{};
  sqdists.reserve(lhs.size());
  std::transform(
      std::begin(lhs), std::end(lhs), std::begin(rhs),
      std::back_inserter(sqdists),
      [](const double l, const double r) { return std::pow(l - r, 2); });
  return std::accumulate(std::begin(sqdists), std::end(sqdists), 0.0);
}

Row parseRow(const std::string& str) {
  auto row = Row{};
  std::stringstream ss{str};
  std::string tmp;
  while (getline(ss, tmp, ',')) {
    row.push_back(std::stod(tmp));
  }
  return row;
}

std::vector<std::size_t> matchingPositions(const Rows& original, const Rows& modified) {
  assert(original.size() == modified.size());
  auto positions = std::vector<std::size_t>{};
  positions.reserve(original.size());

  auto ps = std::vector<std::size_t>(original.size());
  std::iota(std::begin(ps), std::end(ps), 0u);

  for (const auto& orow : original) {
    std::sort(std::begin(ps), std::end(ps),
              [&orow, &modified](const std::size_t l, const std::size_t r) {
                return distance(orow, modified[l]) >
                       distance(orow, modified[r]);
              });
    positions.push_back(ps.back());
    ps.pop_back();
  }

  return positions;
}

int main() {
  auto k = 0u;
  std::cin >> k;
  if (k == 0) { return EXIT_FAILURE; }

  auto lines = std::vector<std::string>{};
  auto iit = std::istream_iterator<std::string>{std::cin};
  auto eit = std::istream_iterator<std::string>{};
  std::copy(iit, eit, std::back_inserter(lines));

  auto originalRows = std::vector<Row>(k);
  auto modifiedRows = std::vector<Row>(k);
  std::transform(std::begin(lines), std::begin(lines) + k,
                std::begin(originalRows), parseRow);
  std::transform(std::begin(lines) + k, std::end(lines),
                std::begin(modifiedRows), parseRow);

  const auto ps = matchingPositions(originalRows, modifiedRows);
  for (auto i = 0u; i < k; ++i) {
    std::cout << i << ',' << ps[i] << '\n';
  }
}
