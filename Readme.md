# Online Library Management System (C++ / OOP)

## Summary
Simple, modular OOP implementation of a library system with:
- `Book`, `User`, `Library` classes
- Add/remove/search books
- Add/remove users
- Borrow and return flows with checks (availability, borrow limit, duplicate borrows)
- Unit-style tests (`tests.cpp`) using `assert` for both positive and negative scenarios.

## Build instructions
Requires a C++17-capable compiler (g++, clang++).

From project root:

```bash
# compile demo (optional)
g++ -std=c++17 -O2 src/*.cpp -o library-demo

# compile tests
g++ -std=c++17 -O2 src/Book.cpp src/User.cpp src/Library.cpp src/tests.cpp -o library-tests

# run tests
./library-tests
