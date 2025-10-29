# LLVM Optimization Plugins

## Project Overview

This project implements a **framework for LLVM optimization plugins**, such as **Dead Code Elimination (DCE) plugin**, **InstCombine plugin**. The goal of the framework is to allow multiple custom LLVM passes to be developed, compiled, and run independently, enabling easy experimentation with compiler optimizations.

The current project includes:

1. **Dead Code Elimination (DCE)** – removes unused and side-effect-free instructions from LLVM IR.
2. **InstCombine** - optimizes and simplifies LLVM IR instructions by combining and transforming instruction sequences into more efficient forms without changing the program's semantics.

---


### Dead Code Elimination (DCE) Plugin

- Removes instructions that:
  1. Have no uses.
  2. Are not terminators (`ret`, `br`, etc.).
  3. Have no side effects.
- Prints debug messages for each instruction removed.
- Can be invoked using `opt` with `-passes=dce-simple`.

---

### Instruction Combining (InstCombine) Plugin

- Simplifies and optimizes LLVM IR instructions by:
  1. Reordering operands to canonical form (e.g., swapping add operands so constants are on the right).
  2. Folding constant expressions (e.g., (x + c1) + c2 → x + (c1 + c2)).
  3. Replacing certain arithmetic operations with cheaper alternatives (e.g., x * 2 → x << 1).

- Prints debug messages for each transformation applied.
- Can be invoked using `opt` with `-passes=instcombine-simple`.

---

## Build & Run

```bash
cd DCE/
./run_dce_tests.sh
```

- This will compile all plugins (like DeadCodeElimination.so) and run the tests from the tests/ folder.
- Test outputs will be saved in tests_out/.
- Same can be applied for InstCombine/run_instcomb_tests.sh


