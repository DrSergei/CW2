# CW2

## Setup

Install packages and clone repo.

```sh
sudo apt install cmake ninja build-essential
git clone ...
git submodule update --init --recursive
```

## Run

Just execute `run.sh` from the root of repo.

```sh
./run.sh
```

## Example

Performance is not stable, so 2 examples of execution trace on my laptop: WSL2, AMD Ryzen 7 8845HS.

```sh
sergei@DrSergei:~/CW2$ ./run.sh
-- The C compiler identification is GNU 13.3.0
-- The CXX compiler identification is GNU 13.3.0
-- Detecting C compiler ABI info
-- Detecting C compiler ABI info - done
-- Check for working C compiler: /usr/bin/cc - skipped
-- Detecting C compile features
-- Detecting C compile features - done
-- Detecting CXX compiler ABI info
-- Detecting CXX compiler ABI info - done
-- Check for working CXX compiler: /usr/bin/c++ - skipped
-- Detecting CXX compile features
-- Detecting CXX compile features - done
-- PARLAY VERSION 2.3.3
-- ---------------------------- General configuration -----------------------------
-- CMake Generator:                Ninja
-- Compiler:                       GNU 13.3.0
-- Build type:                     Release
-- CMAKE_CXX_FLAGS:                
-- CMAKE_CXX_FLAGS_DEBUG:          -g
-- CMAKE_CXX_FLAGS_RELEASE:        -O3 -DNDEBUG
-- CMAKE_CXX_FLAGS_RELWITHDEBINFO: -O2 -g -DNDEBUG -fno-omit-frame-pointer
-- CMAKE_EXE_LINKER_FLAGS          
-- CMAKE_INSTALL_PREFIX:           /usr/local
-- Performing Test CMAKE_HAVE_LIBC_PTHREAD
-- Performing Test CMAKE_HAVE_LIBC_PTHREAD - Success
-- Found Threads: TRUE  
-- -------------------------------- Library options ------------------------------
-- Using Parlay scheduler. Switch with -DPARLAY_{CILKPLUS,OPENCILK,OPENMP,TBB}=On
-- Elastic parallelism enabled. Disable with -DPARLAY_ELASTIC_PARALLELISM=Off
-- ------------------------------- Static Analysis --------------------------------
-- cppcheck:                     Disabled (enable with -DENABLE_CPPCHECK=On)
-- clang-tidy:                   Disabled (enable with -DENABLE_CLANG_TIDY=On)
-- include-what-you-use:         Disabled (enable with -DENABLE_IWYU=On)
-- ---------------------------------- Unit Tests ----------------------------------
-- testing: Disabled (enable with -DPARLAY_TEST=On)
-- ---------------------------------- Benchmarks ----------------------------------
-- benchmarks: Disabled (enable with -DPARLAY_BENCHMARK=On)
-- ----------------------------------- Examples -----------------------------------
-- examples: Disabled (enable with -DPARLAY_EXAMPLES=On)
-- example data: Off (add -DPARLAY_EXAMPLE_DATA=On to download)
-- Configuring done (1.3s)
-- Generating done (0.0s)
-- Build files have been written to: /home/sergei/CW2/build
[6/6] Linking CXX executable src/tests
Run parallel bfs
Average time: 1.1724
Run sequential bfs
Average time: 2.5562
Run tests
Tests success
sergei@DrSergei:~/CW2$ 
```

```sh
-- The C compiler identification is GNU 13.3.0
-- The CXX compiler identification is GNU 13.3.0
-- Detecting C compiler ABI info
-- Detecting C compiler ABI info - done
-- Check for working C compiler: /usr/bin/cc - skipped
-- Detecting C compile features
-- Detecting C compile features - done
-- Detecting CXX compiler ABI info
-- Detecting CXX compiler ABI info - done
-- Check for working CXX compiler: /usr/bin/c++ - skipped
-- Detecting CXX compile features
-- Detecting CXX compile features - done
-- PARLAY VERSION 2.3.3
-- ---------------------------- General configuration -----------------------------
-- CMake Generator:                Ninja
-- Compiler:                       GNU 13.3.0
-- Build type:                     Release
-- CMAKE_CXX_FLAGS:                
-- CMAKE_CXX_FLAGS_DEBUG:          -g
-- CMAKE_CXX_FLAGS_RELEASE:        -O3 -DNDEBUG
-- CMAKE_CXX_FLAGS_RELWITHDEBINFO: -O2 -g -DNDEBUG -fno-omit-frame-pointer
-- CMAKE_EXE_LINKER_FLAGS          
-- CMAKE_INSTALL_PREFIX:           /usr/local
-- Performing Test CMAKE_HAVE_LIBC_PTHREAD
-- Performing Test CMAKE_HAVE_LIBC_PTHREAD - Success
-- Found Threads: TRUE  
-- -------------------------------- Library options ------------------------------
-- Using Parlay scheduler. Switch with -DPARLAY_{CILKPLUS,OPENCILK,OPENMP,TBB}=On
-- Elastic parallelism enabled. Disable with -DPARLAY_ELASTIC_PARALLELISM=Off
-- ------------------------------- Static Analysis --------------------------------
-- cppcheck:                     Disabled (enable with -DENABLE_CPPCHECK=On)
-- clang-tidy:                   Disabled (enable with -DENABLE_CLANG_TIDY=On)
-- include-what-you-use:         Disabled (enable with -DENABLE_IWYU=On)
-- ---------------------------------- Unit Tests ----------------------------------
-- testing: Disabled (enable with -DPARLAY_TEST=On)
-- ---------------------------------- Benchmarks ----------------------------------
-- benchmarks: Disabled (enable with -DPARLAY_BENCHMARK=On)
-- ----------------------------------- Examples -----------------------------------
-- examples: Disabled (enable with -DPARLAY_EXAMPLES=On)
-- example data: Off (add -DPARLAY_EXAMPLE_DATA=On to download)
-- Configuring done (1.4s)
-- Generating done (0.0s)
-- Build files have been written to: /home/sergei/CW2/build
[6/6] Linking CXX executable src/tests
Run parallel bfs
Average time: 0.6923
Run sequential bfs
Average time: 2.4135
Run tests
Tests success
sergei@DrSergei:~/CW2$ 
```
