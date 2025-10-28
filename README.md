# LLVM Optimization Plugins

## Project Overview

This project implements a **framework for LLVM optimization plugins**, such as **Dead Code Elimination (DCE) plugin**. The goal of the framework is to allow multiple custom LLVM passes to be developed, compiled, and run independently, enabling easy experimentation with compiler optimizations.

The current project includes:

1. **Dead Code Elimination (DCE)** – removes unused and side-effect-free instructions from LLVM IR.
2. 

---


### Dead Code Elimination (DCE) Plugin

- Removes instructions that:
  1. Have no uses.
  2. Are not terminators (`ret`, `br`, etc.).
  3. Have no side effects.
- Prints debug messages for each instruction removed.
- Can be invoked using `opt` with `-passes=dce-simple`.

---

## Build & Run

### 1. Build all plugins and tests with CMake

```bash
mkdir -p build
cd build
cmake ..
cmake --build .
```

## 2. Run all tests

```bash
make run_tests
```
- This will compile all plugins (like DeadCodeElimination.so) and run the tests from the tests/ folder.
- Test outputs will be saved in build/tests_out/.


