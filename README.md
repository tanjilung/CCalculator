# CCalculator — Qt Calculator

A desktop calculator app built with C++17, CMake, and Qt Widgets.

## Requirements

- CMake 3.14+
- GCC (g++) with C++17 support
- Make
- Qt5 Widgets

```bash
sudo apt-get install -y cmake g++ make qtbase5-dev libqt5gui5 libqt5widgets5
```

## Build

```bash
mkdir build && cd build
cmake ..
make
```

## Run

```bash
./ccalculator        # launch the calculator GUI
ctest               # run the unit tests
```

## Project Structure

```
CCalculator/
├── include/
│   ├── math_utils.h          # add, subtract, multiply, divide
│   └── calculator_window.h   # Qt QMainWindow subclass (GUI)
├── src/
│   ├── main.cpp              # QApplication entry point
│   ├── math_utils.cpp        # arithmetic implementations
│   └── calculator_window.cpp # UI construction & signal/slot wiring
└── tests/
    └── test_main.cpp         # unit tests for math_utils
```
