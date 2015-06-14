#include <algorithm>
#include <iostream>
#include <vector>
#include <string>

int main() {
  auto colors =
      std::vector<std::string>{"White", "Black", "Blue", "Red", "Yellow"};

  auto line = std::string{};
  std::cin >> line;  // ignore number

  while (std::cin >> line) {
    auto pos = std::find(std::begin(colors), std::end(colors), line);
    if (pos != std::end(colors)) {
      colors.erase(pos);
      if (colors.size() == 1u) {
        std::cout << colors[0] << '\n';
        break;
      }
    }
  }
}
