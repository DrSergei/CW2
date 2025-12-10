add_executable(seq seq.cpp)
target_link_libraries(seq parlay)

add_executable(par par.cpp)
target_link_libraries(par parlay)

add_executable(tests tests.cpp)
target_link_libraries(tests parlay)
