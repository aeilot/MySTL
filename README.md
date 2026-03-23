# My Data Structures

This repository is a study-oriented collection of STL-inspired data structures written in modern C++. The goal is to build familiar containers and classic supporting structures from scratch, then validate them with GoogleTest-based coverage.

## What Is Here

The codebase is currently split into two groups:

- `include/smart/`: container-style implementations such as `Stack`, `Queue`, `Deque`, `list`, `vector`, and `LinkedList`.
- `include/legacy/`: classic data structures such as `DSU`, `Trie`, `Map`, `PriorityQueue`, `BST`, and `SplayTree`.

## Current Coverage

### Implemented and tested

- `Stack`
- `Queue`
- `Deque`
- `list`
- `vector`
- `LinkedList`
- `DSU`
- `Trie`
- `Map`
- `PriorityQueue`
- `BST`
- `SplayTree`

### Planned or worth expanding

- AVL tree
- Red-black tree
- B-tree or B+ tree
- Fibonacci heap
- Leftist heap
- Skew heap
- More hash-based containers
- Benchmarks against STL equivalents

## Build

Requirements:

- CMake 4.0+
- A compiler with C++23 support
- Internet access on the first configure so CMake can fetch GoogleTest

Configure and build:

```sh
cmake -S . -B build
cmake --build build
```

## Run Tests

This project uses GoogleTest with CMake test discovery.

```sh
ctest --test-dir build --output-on-failure
```

You can also run the compiled test binary directly after building:

```sh
./build/my_stl
```

## Repository Layout

- `include/`: header implementations for all containers and supporting concepts
- `include/smart/`: STL-like container implementations
- `include/legacy/`: classic tree, graph, and associative structures
- `tests/`: GoogleTest suites for each implemented structure
- `CMakeLists.txt`: top-level build and test configuration

## Development Notes

- The project is currently header-driven, with tests compiled into a single `my_stl` executable.
- New structures should generally include matching coverage in `tests/`.
- If you add a new container, update this README so the implementation list stays accurate.

## License

MIT.
