#include <algorithm>
#include <iostream>
#include <string>
#include <set>

int main() {
  const auto printItem = [](const std::size_t count, const std::string& item) {
    std::cout << count << '|' << item << '\n';
  };

  const auto alpha_compare =
      [](const std::string& lhs, const std::string& rhs) {
        return std::lexicographical_compare(
            std::begin(lhs), std::end(lhs), std::begin(rhs), std::end(rhs),
            [](char l, char r) { return std::tolower(l) < std::tolower(r); });
      };

  auto items =
      std::multiset<std::string, decltype(alpha_compare)>(alpha_compare);
  auto line = std::string{};
  while (getline(std::cin, line)) {
    if (line != "") {
      items.emplace(line);
    }
  }

  for (auto it = std::begin(items); it != std::end(items);
       it = items.upper_bound(*it)) {
    const auto& item = *it;
    auto count = items.count(item);

    if (item.find("sock") != std::string::npos) {  // we have a sock!
      if (count > 1) {
        printItem(count / 2, item);
      }
      if (count % 2 == 1) {  // one lonely sock left over
        printItem(0, item);
      }
    } else {
      printItem(count, item);
    }
  }
}
