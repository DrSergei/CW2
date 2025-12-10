#include <cstdlib>
#include <exception>
#include <iostream>

#include "bfs.h"
#include "run.h"

int main() {
  try {
    constexpr int ATTEMPTS = 5;
    double time = 0;
    auto graph = generate_cube2();
    for (int i = 0; i < ATTEMPTS; i++) {
      parlay::internal::timer t;
      bfs_seq(0, graph);
      time += t.next_time();
    }
    std::cout.precision(4);
    std::cout << std::fixed;
    std::cout << "Average time: " << time / ATTEMPTS << std::endl;
    return EXIT_SUCCESS;
  } catch (std::exception &ex) {
    std::cerr << ex.what() << std::endl;
    return EXIT_FAILURE;
  }
}
