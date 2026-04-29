*This project has been created as part of the 42 curriculum by rivandri, airandri.*

---

# push_swap

## Description

**push_swap** is a sorting algorithm project from the 42 school curriculum. The goal is to sort a stack of integers using a limited set of operations on two stacks — **stack A** and **stack B** — while minimizing the total number of operations performed.

The program reads a list of integers as arguments, outputs to standard output the sequence of operations needed to sort stack A in ascending order, and optionally prints benchmark statistics to standard error.

What makes this implementation distinctive is its **adaptive strategy engine**: rather than committing to a single algorithm, the program measures the *disorder* of the input at runtime and selects the most efficient sorting strategy accordingly.

### Available Operations

| Operation | Description |
|-----------|-------------|
| `sa` | Swap the top two elements of stack A |
| `sb` | Swap the top two elements of stack B |
| `ss` | `sa` and `sb` simultaneously |
| `pa` | Push the top element of B onto A |
| `pb` | Push the top element of A onto B |
| `ra` | Rotate A upward (top becomes bottom) |
| `rb` | Rotate B upward |
| `rr` | `ra` and `rb` simultaneously |
| `rra` | Reverse rotate A (bottom becomes top) |
| `rrb` | Reverse rotate B |
| `rrr` | `rra` and `rrb` simultaneously |

---

## Algorithm Design & Justification

This project uses **four distinct sorting strategies**, each suited to a different input profile. The right strategy is selected by the `decision` module, which evaluates both the **size** of the input and its **disorder score**.

### Disorder Metric

The disorder score is computed in `disorder_metric.c` as the ratio of *inversions* (pairs where a larger index precedes a smaller one) to the total number of pairs. It is a float between `0.0` (perfectly sorted) and `1.0` (reversed).

```
disorder = mistakes / size
```

This metric runs in **O(n²)** but is only called once at the start, making it a cheap oracle for strategy selection.

---

### Strategy 1 — `sort_three` (≤ 3 elements)

**Complexity: O(1)** — at most 2 operations.

For 3 elements, every possible permutation can be solved with a fixed decision tree: find the maximum, move it to the bottom via `ra` or `rra`, then fix the remaining two with `sa` if needed. No loops, no recursion.

**Why:** With such small inputs any general algorithm would be overkill. Hard-coding the 6 possible permutations (implicitly via max position) is provably optimal.

---

### Strategy 2 — `handle_min` (4–5 elements, or small adaptive)

**Complexity: O(n²)** in the worst case, but extremely low constant for n ≤ 5.

The first half of the elements (minus one) are moved to B by repeatedly pushing the current minimum to the top of A and calling `pb`. Stack A is then sorted with `sort_three`, stack B is optionally fixed with `sb`, and everything is pushed back with `pa`.

**Why:** For 4–5 elements the overhead of chunk or radix sorting (index computation, bit iteration) would generate more operations than this direct approach. The small size bounds the O(n²) cost to a negligible number of moves.

---

### Strategy 3 — `selection_sort` (large inputs, disorder < 20%)

**Complexity: O(n²)**

Repeatedly finds the minimum element in A, rotates it to the top (choosing the shorter path between `ra` or `rra`), pushes it to B, and finally pushes all of B back to A. This produces a sorted A because elements were pushed to B in ascending order.

**Why:** When the array is nearly sorted (< 20% disorder), the minimum is usually already close to the top of A, so the rotation cost is low. The total operation count stays competitive with more complex algorithms in this regime, while keeping the implementation simple and predictable.

---

### Strategy 4 — `chunk_sort` (medium disorder: 20%–50%)

**Complexity: O(n√n)** approximately.

Elements are divided into chunks of size 20 (for n ≤ 100) or 45 (for n > 100). During the push phase, any element whose index falls in the current chunk window is immediately pushed to B; if it belongs to the lower half of that chunk it is additionally rotated in B (`rb`) to keep larger-indexed elements near the top. After all chunks are processed, elements are pulled back from B to A by repeatedly finding the maximum and rotating it to the top of B before calling `pa`.

**Why:** For moderately disordered inputs, chunking amortizes the cost of large rotations: instead of seeking an exact minimum each time (O(n) rotation), elements are accepted in a range, reducing the average rotation distance per push. The chunk size was tuned empirically to stay under 700 operations for n = 100 and under 5500 for n = 500.

---

### Strategy 5 — `radix_sort` (highly disordered: disorder ≥ 50%)

**Complexity: O(n log n)**

A bitwise LSD (Least Significant Digit) radix sort operating on the normalized indices (0 to n−1). For each bit position, elements whose index has a `0` in that bit are pushed to B; elements with a `1` are rotated. After processing all n elements, everything in B is pushed back to A. This is repeated for every bit up to the most significant bit of the largest index.

**Why:** For highly shuffled large inputs (e.g., n = 500, disorder > 50%), the guaranteed O(n log n) bound beats both selection sort and chunk sort. The number of passes equals ⌈log₂(n)⌉ — about 9 for n = 500 — and each pass costs exactly 2n operations, giving roughly 9000 operations for 500 elements, which satisfies the 42 project constraints.

---

### Decision Logic Summary

```
if size ≤ 3            → sort_three          O(1)
if size ≤ 5            → handle_min          O(n²), low constant
if disorder < 0.20     → selection_sort      O(n²), cheap on nearly-sorted data
if disorder < 0.50     → chunk_sort          O(n√n)
else                   → radix_sort          O(n log n)
```

The user may also override the adaptive logic with explicit flags (see Usage below).

---

## Instructions

### Prerequisites

- A C compiler (`cc`) with support for `-Wall -Wextra -Werror`
- `make`
- The `ft_printf` library must be present in a subdirectory named `ft_printf/` at the project root (it is compiled automatically)

### Compilation

```bash
# Build the push_swap binary
make

# Remove object files
make clean

# Remove object files and binary
make fclean

# Full rebuild
make re
```

### Usage

```bash
# Basic usage — outputs the list of operations to stdout
./push_swap 3 1 4 1 5 9 2 6

# Pass numbers as a single quoted string
./push_swap "5 3 8 1 2"

# Force a specific algorithm
./push_swap --simple  3 1 4 ...    # selection sort
./push_swap --medium  3 1 4 ...    # chunk sort
./push_swap --complex 3 1 4 ...    # radix sort
./push_swap --adaptive 3 1 4 ...   # default adaptive mode

# Print benchmark statistics to stderr
./push_swap --bench 3 1 4 1 5 9 2 6
```

### Benchmark Output Example

```
[bench] disorder: 72.50%
[bench] strategy: complex / O(n log n)
[bench] total_ops: 4832
[bench] sa: 0 sb: 0 ss: 0 pa: 2240 pb: 2240
[bench] ra: 176 rb: 0 rra: 176 rrb: 0 rrr: 0
```

### Verifying Correctness

You can pipe the output into a checker (provided separately by 42 or written manually):

```bash
ARG="5 3 8 1 2"; ./push_swap $ARG | ./checker $ARG
# Expected output: OK
```

Or count the number of operations:

```bash
./push_swap $(shuf -i 1-500 -n 500 | tr '\n' ' ') | wc -l
```
---

## Contributors

### rivandri

- `benchmark.c` : Performance testing code to measure disorder and to understand the strategy and complexity of the algorithm.

- `benchmark_utils.c` : Utility functions supporting benchmarking.

- `chunck_sort.c`: Implements chunk-based sorting, dividing data into blocks and sorting them individually.

- `handle_min.c` : Handles movement of the smallest element in the stack, often used during optimization.

- `index.c` : Assigns positional indexes to values for easier comparison and sorting logic.

- `lst_utils.c` : Contains helper functions for managing linked lists.

- `main.c` : Entry point of the program; parses arguments and launches the sorting algorithm.

- `main_utils.c` : Auxiliary functions used in main.c, such as input validation and error handling.

- `parsing.c` : Processes command-line arguments, checks for duplicates, and validates input format.

- `parsing_utils.c` : Supports parsing with functions like string-to-integer conversion and whitespace handling.

- `push_swap.h` : Header file declaring functions, structures, and macros shared across source files.

- `split.c` : Manages splitting the stack into segments, often used in advanced sorting strategies.

- `ft_printf` : allows printing strings, variables, numbers, and other data types by applying a specific format defined by format specifiers.

### airandri

- `decision.c` : Determines the optimal next move by evaluating stack states and cost metrics.

- `disorder_metric.c` : Calculates a score representing how unsorted the current stack configuration is.

- `is_index_sorted.c` : Checks whether the indexed elements in the stack are in correct ascending order.

- `radix_sort.c` : Implements radix sort using bit manipulation or digit-based partitioning for efficient sorting.

- `selection_sort.c` : Applies selection sort logic, suitable for small datasets within larger algorithms.

- `sort_three.c` : Optimized function to sort exactly three elements with minimal instructions.

- `push.c` : Contains pa and pb operations to move elements between stacks A and B.

- `swap.c` : Implements sa, sb, and ss to swap the top elements of one or both stacks.

- `rotate.c` : Handles ra, rb, and rr operations that shift stack elements upward.

- `reverse_rotate.c` : Implements rra, rrb, and rrr to shift stack elements downward.

- `Makefile` : Build script automating compilation of the push_swap and checker programs.

## Resources

### Sorting Algorithms & Complexity
- [Sorting Algorithms Visualized — VisuAlgo](https://visualgo.net/en/sorting)
- [Radix Sort — GeeksforGeeks](https://www.geeksforgeeks.org/radix-sort/)
- [Selection Sort — GeeksforGeeks](https://www.geeksforgeeks.org/selection-sort/)
- [Medium — push_swap: the ultimate guide](https://medium.com/@jamierobertdawson/push-swap-the-least-amount-of-moves-with-two-stacks-d1e76a71789a)

### Tools
- [push_swap visualizer by o-reo](https://github.com/o-reo/push_swap_visualizer)

---

### Use of AI in This Project

AI (Claude by Anthropic) was used during this project.

Specifically:

- **Algorithm selection**: Discussing the trade-offs between radix sort, chunk sort, and selection sort for varying input sizes and disorder levels, which led to the adaptive dispatch design in `decision.c`.
- **README writing**: This README was drafted with AI assistance.
