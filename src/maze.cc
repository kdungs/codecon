#include <algorithm>
#include <cassert>
#include <functional>
#include <iterator>
#include <iostream>
#include <vector>

struct Point {
  std::size_t row, col;

  auto operator==(const Point& rhs) const noexcept -> bool {
    return (row == rhs.row) && (col == rhs.col);
  }

  auto operator!=(const Point& rhs) const noexcept -> bool {
    return !(*this == rhs);
  }
};

auto operator<<(std::ostream& os, const Point& p) -> std::ostream & {
  os << p.row << ',' << p.col;
  return os;
}

struct Maze {
  std::size_t rows, cols;
  std::vector<bool> map; 
};

auto solveBfs(const Maze& maze, const Point& from, const Point& to)
    -> std::vector<Point> {
  auto visited = std::vector<bool>(maze.rows * maze.cols, false);
  auto prev = std::vector<Point>(maze.rows * maze.cols, {maze.rows, maze.cols});

  auto getAddress =
      [&maze](const Point& p) { return p.row * maze.cols + p.col; };

  auto getNeighbours = [&maze, &visited, &getAddress](const Point& p) {
    auto ns = std::vector<Point>{{p.row - 1, p.col},
                                 {p.row + 1, p.col},
                                 {p.row, p.col - 1},
                                 {p.row, p.col + 1}};
    ns.erase(std::remove_if(std::begin(ns), std::end(ns),
                            [&maze, &visited, &getAddress](const Point& np) {
                              const auto addr = getAddress(np);
                              return (np.row >= maze.rows) ||
                                     (np.col >= maze.cols) || !maze.map[addr] ||
                                     visited[addr];
                            }),
             std::end(ns));
    return ns;
  };

  auto queue = std::vector<Point>{};
  queue.emplace_back(from);

  while (!queue.empty()) {
    auto cur = queue.front();
    queue.erase(std::begin(queue));
    visited[getAddress(cur)] = true;

    if (cur == to) {
      break;
    }

    auto ns = getNeighbours(cur);
    for (const auto& n : ns) {
      prev[getAddress(n)] = cur;
      queue.emplace_back(n);
    }
  }

  auto path = std::vector<Point>{};
  for (auto cur = to; cur != from; cur = prev[getAddress(cur)]) {
    path.emplace_back(cur);
  }
  path.emplace_back(from);
  std::reverse(std::begin(path), std::end(path));
  return path;
}


int main() {
  auto rows = 0ul, cols = 0ul;
  std::cin >> rows >> cols;

  if (rows < 2 || cols < 2) {
    return EXIT_FAILURE;
  }

  auto map = std::vector<bool>{};
  map.reserve(rows * cols);
  char in;
  while (std::cin >> in) {
    map.emplace_back((in == '_'));
  }

  auto maze = Maze{rows, cols, map};
  auto path = solveBfs(maze, {1, 0}, {rows - 2, cols - 1});

  std::copy(std::begin(path), std::end(path),
            std::ostream_iterator<Point>(std::cout, "\n"));
}
