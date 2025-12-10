#include <cstdlib>
#include <iostream>
#include <stdexcept>

#include "bfs.h"
#include "run.h"

template <typename T> void eq(T &l, T &r) {
  if (l == r) {
    return;
  }
  throw std::runtime_error("not equal");
}

int main() {
  try {
    auto graph1 = generate_cube1();
    auto graph2 = generate_cube2();
    auto graph3 = generate_cube3();
    // first form
    auto dist1_seq = bfs_seq(0, graph1);
    auto dist1_par = bfs_par(0, graph1);
    eq(dist1_seq, dist1_par);
    // second form
    auto dist2_seq = bfs_seq(0, graph2);
    auto dist2_par = bfs_par(0, graph2);
    eq(dist2_seq, dist2_par);
    // third form
    auto dist3_seq = bfs_seq(0, graph3);
    auto dist3_par = bfs_par(0, graph3);
    eq(dist3_seq, dist3_par);
    // mixed form
    eq(dist1_seq, dist2_seq);
    parlay::sort_inplace(dist2_seq);
    parlay::sort_inplace(dist3_seq);
    eq(dist2_seq, dist3_seq);
    auto graph_small = generate_cube3(2);
    auto dist_small_seq = bfs_par(0, graph_small);
    auto dist_small_par = bfs_par(0, graph_small);
    auto expected_small = parlay::sequence<std::size_t>{0, 1, 1, 1, 2, 2, 2, 3};
    eq(dist_small_seq, dist_small_par);
    eq(dist_small_seq, expected_small);
    auto graph_line = generate_line(300);
    auto dist_line_seq = bfs_seq(0, graph_line);
    auto dist_line_par = bfs_par(0, graph_line);
    auto expected_line =
        parlay::tabulate<std::size_t>(300, [](std::size_t i) { return i; });
    eq(dist_line_seq, dist_line_par);
    eq(dist_line_seq, expected_line);
    auto graph_cycle = generate_cycle(300);
    auto dist_cycle_seq = bfs_seq(0, graph_cycle);
    auto dist_cycle_par = bfs_par(0, graph_cycle);
    auto expected_cycle = parlay::tabulate<std::size_t>(
        300, [](std::size_t i) { return std::min(i, 300 - i); });
    eq(dist_cycle_seq, dist_cycle_par);
    eq(dist_cycle_seq, expected_cycle);
    auto graph_simple1 = generate_simple1();
    auto dist_simple1_seq = bfs_seq(0, graph_simple1);
    auto dist_simple1_par = bfs_par(0, graph_simple1);
    auto expected_simple1 = parlay::sequence<std::size_t>{0, 1, 1, 2, 2};
    eq(dist_simple1_seq, dist_simple1_par);
    eq(dist_simple1_seq, expected_simple1);
    auto graph_simple2 = generate_simple2();
    auto dist_simple2_seq = bfs_seq(0, graph_simple2);
    auto dist_simple2_par = bfs_par(0, graph_simple2);
    auto expected_simple2 = parlay::sequence<std::size_t>{0, 1, 1, 2, 2, 2, 2};
    eq(dist_simple2_seq, dist_simple2_par);
    eq(dist_simple2_seq, expected_simple2);
    auto graph_simple3 = generate_simple3();
    auto dist_simple3_seq = bfs_seq(0, graph_simple3);
    auto dist_simple3_par = bfs_par(0, graph_simple3);
    auto expected_simple3 = parlay::sequence<std::size_t>{0, 2, 2, 1, 1, 1};
    eq(dist_simple3_seq, dist_simple3_par);
    eq(dist_simple3_seq, expected_simple3);
    auto graph_simple4 = generate_simple4();
    auto dist_simple4_seq = bfs_seq(0, graph_simple4);
    auto dist_simple4_par = bfs_par(0, graph_simple4);
    auto expected_simple4 = parlay::sequence<std::size_t>{0, 1, 1, 2, 2};
    eq(dist_simple4_seq, dist_simple4_par);
    eq(dist_simple4_seq, expected_simple4);
    auto graph_simple5 = generate_simple5();
    auto dist_simple5_seq = bfs_seq(0, graph_simple5);
    auto dist_simple5_par = bfs_par(0, graph_simple5);
    auto expected_simple5 = parlay::sequence<std::size_t>{0, 1, 3};
    eq(dist_simple5_seq, dist_simple5_par);
    eq(dist_simple5_seq, expected_simple5);
    std::cout << "Tests success" << std::endl;
    return EXIT_SUCCESS;
  } catch (...) {
    std::cerr << "Tests failed" << std::endl;
    return EXIT_FAILURE;
  }
}
