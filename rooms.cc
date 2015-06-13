#include <algorithm>
#include <array>
#include <cassert>
#include <fstream>
#include <iostream>
#include <sstream>

class Room {
 public:
  static const std::size_t NUM_SLOTS = 32;
  auto book(unsigned start, unsigned nslots) -> bool {
    assert(start + nslots < NUM_SLOTS);
    if (std::any_of(std::begin(slots_) + start, std::begin(slots_) + nslots,
                    [](bool x) { return x; })) {
      return false;
    }

    std::fill_n(std::begin(slots_) + start, nslots, true);
    return true;
  }

  auto available(unsigned slot, unsigned nslots) const noexcept -> bool {
    assert(slot + nslots < NUM_SLOTS);
    return std::all_of(std::begin(slots_) + slot, std::begin(slots_) + nslots,
                       [](bool x) { return !x; });
  }

 private:
  std::array<bool, NUM_SLOTS> slots_;
};

auto query(const std::vector<Room>& rooms, unsigned slot, unsigned nslots)
    -> unsigned {
  return static_cast<unsigned>(std::count_if(
      std::begin(rooms), std::end(rooms), [slot, nslots](const Room& room) {
        return room.available(slot, nslots);
      }));
}

auto splitAtDash(const std::string& str) -> std::vector<unsigned> {
  std::vector<unsigned> result;
  std::stringstream ss{str};
  std::string tmp;
  while (getline(ss, tmp, '-')) {
    result.push_back(static_cast<unsigned>(std::stoul(tmp)));
  }
  return result;
}

int main() {
  auto line = std::string{};
  getline(std::cin, line);

  auto nrooms = 0ul;
  try {
    nrooms = std::stoul(line);
  } catch (const std::exception&) {
    return EXIT_FAILURE;
  }
  if (nrooms < 1) {
    return EXIT_FAILURE;
  }

  auto rooms = std::vector<Room>(nrooms);
  while (getline(std::cin, line)) {
    auto input = splitAtDash(line);
    if (input.size() == 2) {  // it's a query
      std::cout << query(rooms, input[0], input[1]) << '\n';
    } else if (input.size() == 3) {  // it's a booking
      if (input[0] >= nrooms) {
        std::cerr << "Invalid room ID!\n";
        return EXIT_FAILURE;
      }
      if (rooms[input[0]].book(input[1], input[2])) {
        std::cout << "Y\n";
      } else {
        std::cout << "N\n";
      }
    } else {  // it's BS
      std::cerr << "Invalid input!\n";
      return EXIT_FAILURE;
    }
  }
}
