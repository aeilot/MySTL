# My Data Structures

This repository is a hands-on implementation of common STL-like containers and algorithms in idiomatic C++20. Every module is built with clarity, modern language features, and an eye toward learning how the core data structures behave under the hood.

## Status

### Implemented
- `SequentialList` (vector wrapper with controlled resizing)
- `LinkedList` (double/singly linked nodes and iterators)
- `Stack` (LIFO container built on top of the list primitives)
- `Queue` (FIFO queue with customizable allocator support)
- `BinaryHeap` (array-based min/max heap with sift operations)
- `DisjointSetUnion` (union-find with path compression)
- `HashTable` (open addressing + linear probing)
- `BinarySearchTree` (BST with traversal helpers)

### Planned
- Huffman Tree
- Leftist Heap
- Skew Heap
- Double-Ended Heap (Min-Max Heap)
- Static Search Table
- AVL Tree
- Red-Black Tree
- AA Tree
- Splay Tree
- B-Tree / B+ Tree
- Advanced Disjoint Set variants
- Fibonacci Heap

## Build & Run

1. Configure the project with CMake (requires a working C++20 toolchain):

   ```sh
   cmake -S . -B build
   ```

2. Build everything:

   ```sh
   cmake --build build
   ```

3. Run the executable for experimentation or add new tests via `test.cpp` (the repository currently uses this file as a scratchpad for validating the containers).

## Repository Layout

- `include/`: public headers containing the current data structures and helpers.
- `test.cpp`: scratch space for manual verification and proof-of-concept demos.
- `CMakeLists.txt`: top-level build configuration that pulls in the headers and links the playground executable.

## Roadmap

- Flesh out the remaining advanced heaps and balanced trees with the same build/testing approach.
- Introduce benchmark suites that compare each container against the STL counterparts.
- Package individual headers into a consumable study bundle with documentation.

## Contributing

1. Open an issue describing the structure you want to add or improve.
2. Follow the existing style (header-only, expressive unit tests in `test.cpp`).
3. Update the status list above so the roadmap reflects your work.
4. Submit a pull request; mention any backwards-incompatible API changes in the description.

## License

Unless otherwise noted, code in this repo is covered by the MIT License (see `LICENSE` if present).
