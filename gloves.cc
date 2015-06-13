#include <algorithm>
#include <fstream>
#include <iostream>
#include <string>
#include <unordered_set>

auto isPalindrome(const std::string& str) -> bool {
  auto l = std::begin(str);
  auto r = std::end(str);
  --r;  // since end(str) points to the first position after str

  while (std::distance(l, r) > 1u) {
    if (*l != *r) {
      return false;
    }
    ++l;
    --r;
  }
  return true;
}

auto reverse(const std::string& str) -> std::string {
  auto rev = std::string{str};
  std::reverse(std::begin(rev), std::end(rev));
  return rev;
}

class GloveMatcher {
 public:
  auto matched() const noexcept -> int {
    if (!cache_.empty()) {
      return -1;
    }
    return matched_;
  }
  auto process(const std::string& item) -> void {
    if (isPalindrome(item)) {  // we found a hat!
      return;
    }

    const auto hint = cache_.find(item);
    if (hint != cache_.end()) {
      cache_.erase(hint);
      ++matched_;
    } else {
      cache_.emplace(reverse(item));
    }
  }

 private:
  int matched_;
  std::unordered_multiset<std::string> cache_;
};

int main() {
  auto gm = GloveMatcher{};

  auto line = std::string{};
  getline(std::cin, line);  // ignore number
  while (getline(std::cin, line)) {
    gm.process(line);
  }

  std::cout << gm.matched() << '\n';
}
