# CLAUDE.md

This file provides guidance to Claude Code (claude.ai/code) when working with code in this repository.

## Project Overview

CCalculator is a desktop calculator application built with C++17, CMake, and Qt5 Widgets. It provides basic arithmetic operations (add, subtract, multiply, divide) via a grid-based button UI.

## Build System

Out-of-source build in the `build/` directory. Two targets:
- `ccalculator` — the main GUI application executable
- `ccalculator_tests` — the test binary linked against `math_utils.cpp` only (no Qt dependency)

CMake configuration: `CMAKE_AUTOMOC ON`, C++17, Qt5 Widgets, warning flags (`-Wall -Wextra` on GCC/Clang, `/W4 /permissive-` on MSVC), `CMAKE_EXPORT_COMPILE_COMMANDS ON`.

### Linux / macOS

```bash
mkdir build && cd build
cmake ..
make
```

### Windows (Developer Command Prompt for VS)

```bat
mkdir build
cd build
cmake ..
cmake --build . --config Release
```

> `--config Release` is required on MSVC (multi-config generator); omit it on Linux/macOS.

## Running

### Linux / macOS

```bash
cd build && ./ccalculator          # launch GUI (requires display)
cd build && ctest                  # run unit tests
cd build && ./ccalculator_tests    # run tests directly (per-test OK/FAIL output)
```

### Windows (from the `build/` dir)

```bat
Release\ccalculator.exe            # launch GUI
ctest --test-dir .                 # run unit tests
```

## Architecture

### Pure logic layer (`include/math_utils.h` / `src/math_utils.cpp`)
Free functions `calc::add()`, `calc::subtract()`, `calc::multiply()`, `calc::divide()` operating on `double`, namespaced under `calc`. `divide()` throws `std::invalid_argument` on division by zero. This is the only code with unit test coverage.

### UI layer (`include/calculator_window.h` / `src/calculator_window.cpp`)
`CalculatorWindow` — a `QMainWindow` subclass with a 4-column `QGridLayout` of buttons and a read-only `QLineEdit` display at the top. The calculator implements a two-operand state machine:

- `previousOperand_` — accumulates the left operand across chained keystrokes
- `pendingOperation_` — stores the last operator pressed (+, -, *, /)
- `isNewNumber_` — flag to decide whether the next digit replaces or appends to the display
- `hasError_` — sticky flag set on invalid operations; cleared by pressing C

Operations chain: pressing an operator when one is already pending evaluates the pending operation first before storing the new operator. Both the chained-evaluation path in `handleOperation()` and the `handleEquals()` path wrap `compute()` in `try/catch` so a chained divide-by-zero (e.g. `5 / 0 *`) shows "Error" instead of terminating the app. The `compute()` method dispatches to `calc::` functions. `formatDisplay()` uses `'g'` format with 15 significant digits.

### Entry point (`src/main.cpp`)
Minimal — creates `QApplication`, constructs `CalculatorWindow`, shows it.

## Key Conventions

- Headers use traditional include guards (e.g. `CALCULATOR_WINDOW_H`).
- Math functions are namespaced under `calc`.
- Member variables use trailing underscore suffix (`display_`, `hasError_`).
- `.vscode/` is gitignored — IDE settings are local only.
- Tests are a plain `main()` using a `CHECK_APPROX`/`CHECK_TRUE` macro that prints per-test OK/FAIL and returns non-zero on failure (works in Release, no external framework).
