# CTest

A simple C++ project with CMake build system and unit tests.

## Requirements

- CMake 3.14+
- GCC (g++) with C++17 support
- Make

```bash
sudo apt-get install -y cmake g++ make
```

## Build

```bash
mkdir build && cd build
cmake ..
make
```

## Run

```bash
./ctest            # run the demo program
ctest             # run the tests
```

## Project Structure

```
CTest/
├── include/          # headers
├── src/              # source files
└── tests/            # unit tests
```
