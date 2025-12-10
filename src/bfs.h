#pragma once

#include <atomic>
#include <cstddef>
#include <queue>

#include <parlay/parallel.h>
#include <parlay/primitives.h>
#include <parlay/sequence.h>

struct SimpleGraph {
  auto get_neighbors(std::size_t i) const { return data[i]; }
  std::size_t size() const { return data.size(); }
  parlay::sequence<parlay::sequence<std::size_t>> data;
};

struct FlattenGraph {
  auto get_neighbors(std::size_t i) const {
    return data.cut(offsets[i], offsets[i + 1]);
  }
  std::size_t size() const { return offsets.size() - 1; }
  parlay::sequence<std::size_t> offsets;
  parlay::sequence<std::size_t> data;
};

template <typename Graph>
inline auto bfs_seq(std::size_t start, const Graph &g) {
  auto n = g.size();
  auto dist = parlay::sequence<std::size_t>(n, n);
  dist[start] = 0;
  std::queue<std::size_t> q;
  q.push(start);
  while (!q.empty()) {
    std::size_t v = q.front();
    q.pop();
    for (auto u : g.get_neighbors(v)) {
      if (dist[u] > dist[v] + 1) {
        dist[u] = dist[v] + 1;
        q.push(u);
      }
    }
  }

  return dist;
}

template <typename Graph>
inline auto bfs_par(std::size_t start, const Graph &g) {
  auto n = g.size();
  parlay::sequence<std::size_t> dist(n, n);
  dist[start] = 0;
  auto visited = parlay::tabulate<std::atomic<bool>>(
      n, [&](auto i) { return i == start; });
  parlay::sequence<std::size_t> frontier(1, start);
  size_t level = 0;
  while (frontier.size() > 0) {
    level++;
    auto neighbors = parlay::flatten(parlay::map(
        frontier, [&](std::size_t u) { return g.get_neighbors(u); }));
    frontier = parlay::filter(neighbors, [&](std::size_t v) {
      if (visited[v].load(std::memory_order_relaxed)) {
        return false;
      }
      bool expected = false;
      if (!visited[v].compare_exchange_strong(expected, true)) {
        return false;
      }
      dist[v] = level;
      return true;
    });
  }

  return dist;
}

// template <typename Graph>
// inline auto bfs_par(std::size_t start, const Graph &g) {
//   auto n = g.size();
//   parlay::sequence<std::size_t> dist(n, n);
//   dist[start] = 0;
//   auto visited = parlay::tabulate<std::atomic<bool>>(
//       n, [&](long i) { return i == start; });
//   parlay::sequence<std::size_t> frontier(1, start);
//   size_t level = 0;
//   static constexpr auto INVALID = std::numeric_limits<std::size_t>::max();
//   while (frontier.size() > 0) {
//     const auto [offsets, total] = parlay::scan(parlay::map(
//         frontier, [&](std::size_t v) { return g.get_neighbors(v).size(); }));
//     auto tmp = parlay::sequence<std::size_t>(total, INVALID);
//     level++;
//     parlay::parallel_for(0, frontier.size(), [&](std::size_t i) {
//       auto v = frontier[i];
//       const auto neighbors = g.get_neighbors(v);
//       for (std::size_t j = 0; j < neighbors.size(); j++) {
//         auto u = neighbors[j];
//         bool expected = false;
//         if (!visited[u]) {
//           if (visited[u].compare_exchange_strong(expected, true)) {
//             tmp[offsets[i] + j] = u;
//             dist[u] = level;
//           }
//         }
//       }
//     });
//     frontier = parlay::filter(tmp, [](std::size_t u) { return u != INVALID;
//     });
//   }

//   return dist;
// }
