#include <algorithm>
#include <array>
#include <cassert>
#include <fstream>
#include <iostream>
#include <iterator>
#include <sstream>

class Room {
 public:
  static const std::size_t NUM_SLOTS = 32;
  auto book(unsigned start, unsigned nslots) -> bool {
    assert(start + nslots <= NUM_SLOTS);
    if (std::any_of(std::begin(slots_) + start,
                    std::begin(slots_) + start + nslots,
                    [](bool x) { return x; })) {
      return false;
    }

    std::fill_n(std::begin(slots_) + start, nslots, true);
    return true;
  }

  auto available(unsigned slot, unsigned nslots) const noexcept -> bool {
    assert(slot + nslots < NUM_SLOTS);
    return std::all_of(std::begin(slots_) + slot,
                       std::begin(slots_) + slot + nslots,
                       [](bool x) { return !x; });
  }

 private:
  std::array<bool, NUM_SLOTS> slots_;
};

auto query(const std::vector<Room>& rooms, unsigned slot, unsigned nslots)
    -> std::vector<std::size_t> {
  auto roomsAvailable = std::vector<std::size_t>{};
  for (auto i = 0ul; i < rooms.size(); ++i) {
    if (rooms[i].available(slot, nslots)) {
      roomsAvailable.emplace_back(i);
    }
  }
  return roomsAvailable;
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

template <typename T>
auto printWithSpace(const std::vector<T>& xs) -> void {
  assert(!xs.empty());
  auto it = std::begin(xs);
  std::cout << *it;
  ++it;
  for (; it != std::end(xs); ++it) {
    std::cout << " " << *it;
  }
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
      auto slot = input[0] - 1;  // correct indexing
      auto nslots = input[1];
      auto arooms = query(rooms, slot, nslots);

      if (arooms.empty()) {
        std::cout << "None\n";
      } else {
        std::transform(std::begin(arooms), std::end(arooms), std::begin(arooms),
                       [](unsigned x) { return x + 1; });  // correct indexing
        printWithSpace(arooms);
        std::cout << '\n';
      }
    } else if (input.size() == 3) {  // it's a booking
      if (input[0] == 0 || input[0] > nrooms) {
        std::cerr << "Invalid room ID!\n";
        return EXIT_FAILURE;
      }
      auto room = input[0] - 1;
      auto slot = input[1] - 1;
      auto nslots = input[2];
      if (rooms[room].book(slot, nslots)) {
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
