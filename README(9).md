# C and Assembly Architecture Projects

This repository includes low-level systems programming work developed by Joshua Moorehead. Projects span embedded game development on the Game Boy Advance (GBA) using C, and procedural logic programming in MIPS assembly.

---

## GBA Games (C)

### `tic_tac_toe/`
A functional GBA Tic Tac Toe game using direct memory-mapped graphics, input polling, and game state logic.

### `pong/`
A GBA-based Pong clone with paddle movement, ball bounce, and collision detection — built using low-level frame buffer control and custom logic.

Key Concepts:
- Memory-mapped I/O
- GBA button registers and graphics
- Real-time rendering in C

To compile:
```bash
./compile.sh
```

---

## MIPS Assembly

### `mips/`
A collection of small programs written in MIPS assembly for SPIM/MARS. Demonstrates core principles of assembly control flow, memory handling, and syscall interaction.

Includes:
- `mips1.asm` – Simple register-based logic
- `mips2.asm` – Extended control flow with branching
- `lectureLoops.asm` – Loop logic using register comparisons

---

## Tools Used

- `arm-none-eabi-gcc` for cross-compiling GBA C code
- MARS or QtSPIM for running `.asm` files

---

## License

All code is original and written by Joshua Moorehead. Provided for educational and portfolio purposes.