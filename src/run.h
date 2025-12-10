#pragma once

#include <cstddef>
#include <unordered_map>
#include <vector>

#include <parlay/parallel.h>
#include <parlay/primitives.h>
#include <parlay/sequence.h>

#include "bfs.h"

namespace detail {
inline auto get_index(std::size_t x, std::size_t y, std::size_t z, size_t N) {
  std::size_t i = x + N * y + N * N * z;
  return i;
}
} // namespace detail

inline auto generate_cube1(std::size_t N = 300) {
  auto data = parlay::sequence<parlay::sequence<std::size_t>>(N * N * N);
  for (std::size_t x = 0; x < N; x++) {
    for (std::size_t y = 0; y < N; y++) {
      for (std::size_t z = 0; z < N; z++) {
        std::size_t i = detail::get_index(x, y, z, N);
        if (x > 0) {
          data[i].push_back(detail::get_index(x - 1, y, z, N));
        }
        if (x + 1 < N) {
          data[i].push_back(detail::get_index(x + 1, y, z, N));
        }
        if (y > 0) {
          data[i].push_back(detail::get_index(x, y - 1, z, N));
        }
        if (y + 1 < N) {
          data[i].push_back(detail::get_index(x, y + 1, z, N));
        }
        if (z > 0) {
          data[i].push_back(detail::get_index(x, y, z - 1, N));
        }
        if (z + 1 < N) {
          data[i].push_back(detail::get_index(x, y, z + 1, N));
        }
      }
    }
  }
  return SimpleGraph{std::move(data)};
}

inline auto generate_cube2(std::size_t N = 300) {
  auto data = parlay::sequence<parlay::sequence<std::size_t>>(N * N * N);
  for (std::size_t x = 0; x < N; x++) {
    for (std::size_t y = 0; y < N; y++) {
      for (std::size_t z = 0; z < N; z++) {
        std::size_t i = detail::get_index(x, y, z, N);
        if (x > 0) {
          data[i].push_back(detail::get_index(x - 1, y, z, N));
        }
        if (x + 1 < N) {
          data[i].push_back(detail::get_index(x + 1, y, z, N));
        }
        if (y > 0) {
          data[i].push_back(detail::get_index(x, y - 1, z, N));
        }
        if (y + 1 < N) {
          data[i].push_back(detail::get_index(x, y + 1, z, N));
        }
        if (z > 0) {
          data[i].push_back(detail::get_index(x, y, z - 1, N));
        }
        if (z + 1 < N) {
          data[i].push_back(detail::get_index(x, y, z + 1, N));
        }
      }
    }
  }
  auto [offsets, total] =
      parlay::scan(parlay::map(data, [&](const auto &v) { return v.size(); }));
  offsets.push_back(total);
  return FlattenGraph{std::move(offsets), parlay::flatten(data)};
}

inline auto generate_cube3(std::size_t N = 300) {
  auto tmp = std::vector<std::vector<std::size_t>>(3 * (N - 1) + 1);
  for (std::size_t x = 0; x < N; x++) {
    for (std::size_t y = 0; y < N; y++) {
      for (std::size_t z = 0; z < N; z++) {
        std::size_t i = detail::get_index(x, y, z, N);
        tmp[x + y + z].push_back(i);
      }
    }
  }
  std::size_t idx = 0;
  auto mapper = std::unordered_map<std::size_t, std::size_t>();
  for (const auto &level : tmp) {
    for (auto i : level) {
      mapper[i] = idx++;
    }
  }
  auto data = parlay::sequence<parlay::sequence<std::size_t>>(N * N * N);
  for (std::size_t x = 0; x < N; x++) {
    for (std::size_t y = 0; y < N; y++) {
      for (std::size_t z = 0; z < N; z++) {
        std::size_t i = mapper[detail::get_index(x, y, z, N)];
        if (x > 0) {
          data[i].push_back(mapper[detail::get_index(x - 1, y, z, N)]);
        }
        if (x + 1 < N) {
          data[i].push_back(mapper[detail::get_index(x + 1, y, z, N)]);
        }
        if (y > 0) {
          data[i].push_back(mapper[detail::get_index(x, y - 1, z, N)]);
        }
        if (y + 1 < N) {
          data[i].push_back(mapper[detail::get_index(x, y + 1, z, N)]);
        }
        if (z > 0) {
          data[i].push_back(mapper[detail::get_index(x, y, z - 1, N)]);
        }
        if (z + 1 < N) {
          data[i].push_back(mapper[detail::get_index(x, y, z + 1, N)]);
        }
      }
    }
  }
  auto [offsets, total] =
      parlay::scan(parlay::map(data, [&](const auto &v) { return v.size(); }));
  offsets.push_back(total);
  return FlattenGraph{std::move(offsets), parlay::flatten(data)};
}

inline auto generate_line(std::size_t N = 300) {
  auto data = parlay::sequence<parlay::sequence<std::size_t>>(N);
  for (std::size_t i = 1; i < N; i++) {
    data[i].push_back(i - 1);
    data[i - 1].push_back(i);
  }
  return SimpleGraph{std::move(data)};
}

inline auto generate_cycle(std::size_t N = 300) {
  auto data = parlay::sequence<parlay::sequence<std::size_t>>(N);
  for (std::size_t i = 1; i < N; i++) {
    data[i].push_back(i - 1);
    data[i - 1].push_back(i);
  }
  data[0].push_back(N - 1);
  data[N - 1].push_back(0);
  return SimpleGraph{std::move(data)};
}

inline auto generate_simple1() {
  return SimpleGraph{{{1, 2}, {0, 2, 3}, {0, 1, 4}, {1, 4}, {2, 3}}};
}

inline auto generate_simple2() {
  return SimpleGraph{{{1, 2}, {0, 3, 4}, {0, 5, 6}, {1}, {1}, {2}, {2}}};
}

inline auto generate_simple3() {
  return SimpleGraph{
      {{3, 4, 5}, {3, 4, 5}, {3, 4, 5}, {0, 1, 2}, {0, 1, 2}, {0, 1, 2}}};
}

inline auto generate_simple4() {
  return SimpleGraph{{{1, 2}, {0, 2}, {0, 1, 3, 4}, {2}, {2}}};
}

inline auto generate_simple5() { return SimpleGraph{{{1}, {0}, {}}}; }
