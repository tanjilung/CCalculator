# CCalculator — Qt Calculator

A desktop calculator app built with C++17, CMake, and Qt Widgets.

## Requirements

- CMake 3.14+
- A C++17 compiler
- Qt5 Widgets

### Linux

```bash
sudo apt-get install -y cmake g++ make qtbase5-dev libqt5gui5 libqt5widgets5
```

### Windows

- **CMake 3.14+** — [cmake.org](https://cmake.org/download/) (or `winget install Kitware.CMake`)
- **Visual Studio 2019/2022** with the *"Desktop development with C++"* workload (provides the MSVC `cl` compiler + build tools)
- **Qt5** — [qt.io](https://www.qt.io/download-open-source) (pick the *MSVC 2019 64-bit* kit), or `winget install QT.qt5.5152.msvc2019_64`
- Make sure the Qt `bin` folder is on your `PATH` so CMake can find `Qt5`

## Build

### Linux / macOS

```bash
mkdir build && cd build
cmake ..
make
```

### Windows (Developer Command Prompt)

Open the **"Developer Command Prompt for VS"** (or VS Code with a C++ toolchain on `PATH`), then:

```bat
mkdir build
cd build
cmake ..
cmake --build . --config Release
```

> The `--config Release` flag matters on MSVC (multi-config generator); omit it for Linux/macOS.

## Run

### Linux / macOS

```bash
./ccalculator        # launch the calculator GUI
ctest                # run the unit tests
./ccalculator_tests  # run tests directly (per-test OK/FAIL output)
```

### Windows

```bat
Release\ccalculator.exe        # launch the GUI (from the build dir)
ctest --test-dir .             # run the unit tests
Release\ccalculator_tests.exe  # run tests directly
```

## Project Structure

```
CCalculator/
├── CMakeLists.txt            # build config: GUI app + test target, Qt5 setup
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
