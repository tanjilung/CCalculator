# CLAUDE.md

This file provides guidance to Claude Code (claude.ai/code) when working with code in this repository.

## Project Overview

CCalculator is a desktop calculator application built with C++17, CMake, and Qt5 Widgets. It provides basic arithmetic operations (add, subtract, multiply, divide) via a grid-based button UI.

## Build System

Out-of-source build in the `build/` directory:

```bash
cd build && cmake .. && make
```

The project defines two targets:
- `ccalculator` — the main GUI application executable
- `ccalculator_tests` — the test binary linked against `math_utils.cpp` only (no Qt dependency)

CMake configuration: `CMAKE_AUTOMOC ON`, C++17, Qt5 Widgets.

## Running

```bash
cd build && ./ccalculator          # launch GUI (requires display)
cd build && ctest                  # run unit tests
cd build && ./ccalculator_tests    # run tests directly (shows per-test PASS output)
```

## Architecture

### Pure logic layer (`include/math_utils.h` / `src/math_utils.cpp`)
Free functions `add()`, `subtract()`, `multiply()`, `divide()` operating on `double`. `divide()` throws `std::invalid_argument` on division by zero. This is the only code with unit test coverage.

### UI layer (`include/calculator_window.h` / `src/calculator_window.cpp`)
`CalculatorWindow` — a `QMainWindow` subclass with a 4-column `QGridLayout` of buttons and a read-only `QLineEdit` display at the top. The calculator implements a two-operand state machine:

- `previousOperand_` / `currentOperand_` — accumulates operands across keystrokes
- `pendingOperation_` — stores the last operator pressed (+, -, *, /)
- `isNewNumber_` — flag to decide whether the next digit replaces or appends to the display
- `hasError_` — sticky flag set on invalid operations; cleared by pressing C

Operations chain: pressing an operator when one is already pending evaluates the pending operation first before storing the new operator. The `compute()` method dispatches to `math_utils` functions. `formatDisplay()` uses `'g'` format with 15 significant digits.

### Entry point (`src/main.cpp`)
Minimal — creates `QApplication`, constructs `CalculatorWindow`, shows it.

## Key Conventions

- Headers use traditional include guards (e.g. `CALCULATOR_WINDOW_H`).
- Member variables use trailing underscore suffix (`display_`, `hasError_`).
- `.vscode/` is gitignored — IDE settings are local only.
- Tests use raw `assert` with a custom `approx()` helper, not an external test framework.
