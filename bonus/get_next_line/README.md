*This project has been created as part of the 42 curriculum by airandri.*

---

# get_next_line

> Read a file descriptor, one line at a time.

---

## Description

`get_next_line` is a project from the 42 school curriculum that challenges students to implement a C function capable of reading a single line from a file descriptor each time it is called. Repeated calls to the function on the same file descriptor yield successive lines until the end of the file (or stream) is reached.

**Goal:** Implement the following function:

```c
char *get_next_line(int fd);
```

| Return value | Meaning |
|---|---|
| `char *` (non-NULL) | A line was successfully read (includes the trailing `\n` if present) |
| `NULL` | End of file was reached, or an error occurred |

The returned string includes the newline character `\n` when one is present in the source. The caller is responsible for freeing the returned pointer.

The function works correctly with any file descriptor — regular files, standard input (`stdin`), or pipes — and handles any strictly positive compile-time value of `BUFFER_SIZE`.

**Key learning objectives:**
- Understanding file descriptors and the `read()` system call
- Managing dynamic memory without leaks across multiple calls
- Using `static` variables to persist state between function calls
- Handling edge cases: empty files, files without a trailing newline, `BUFFER_SIZE` of 1 or very large values

---

## Algorithm

### Architecture: four focused functions

The implementation is split into four functions, each with a single, well-defined responsibility:

```
get_next_line(fd)
│
├── read_and_fill()   — feeds raw bytes from fd into the stash
├── set_line()        — extracts the next complete line from the stash
└── stash_update()    — trims the consumed line and keeps the remainder
```

---

### `read_and_fill` — accumulate raw data into the stash

```c
char *read_and_fill(int fd, char *stash, char *buffer)
```

This function owns the relationship with the OS. Its job is to ensure that `stash` contains at least one complete line (i.e. a `\n`), or everything remaining up to EOF if no newline is left.

- If `stash` is `NULL` (first call, or after a full drain), it is initialised to an empty string via `ft_strdup("")`. This avoids any special-case branching in the join logic.
- A `while` loop calls `read()` repeatedly, each time appending the freshly-read `buffer` to `stash` using `ft_strjoin`.
- The loop exits as soon as `ft_strchr(stash, '\n')` finds a newline **or** `read()` returns `0` (EOF).
- On a `read()` error (`size == -1`), `stash` is freed and `NULL` is returned immediately.

The old `stash` pointer is saved in a local `ptr` and freed after each `ft_strjoin` call, so no intermediate allocation is ever leaked.

---

### `set_line` — extract the current line

```c
char *set_line(char *stash)
```

Once `stash` is guaranteed to hold at least one line's worth of data, `set_line` copies everything up to and **including** the `\n` into a freshly allocated string.

- A first pass counts characters until `\n` or `\0` to determine the exact allocation size (`i + 2`: `i` characters + possible `\n` + `\0`).
- A second pass copies those characters into the new string.
- If a `\n` is present at position `i`, it is copied before the null terminator.

The returned string is exactly what `get_next_line` hands back to the caller.

---

### `stash_update` — trim the consumed part

```c
char *stash_update(char *stash)
```

After the line has been extracted, the leading portion of `stash` (up to and including the `\n`) is no longer needed. `stash_update` discards it:

- It advances an index past all characters up to and including the `\n`.
- `ft_substr` allocates a new string containing only what follows that newline.
- The old `stash` is freed before returning the new one.

The result is stored back into the `static char *stash` inside `get_next_line`, ready for the next call.

---

### `get_next_line` — orchestration

```c
char *get_next_line(int fd)
```

The main function ties everything together:

```
1. Guard: return NULL if fd < 0 or BUFFER_SIZE <= 0.
2. Allocate a heap buffer of BUFFER_SIZE + 1 bytes.
3. Call read_and_fill()   → stash now holds ≥1 line, or EOF remainder.
4. Free the buffer (no longer needed after this point).
5. If stash is NULL or empty → free, set to NULL, return NULL (EOF/error).
6. Call set_line(stash)        → line  (returned to the caller).
7. Call stash_update(stash)    → new stash (kept for next call).
8. If new stash is empty       → free and set to NULL.
9. Return line.
```

The `static char *stash` variable persists between calls, carrying any unprocessed bytes forward so that nothing read from the file descriptor is ever lost or re-read.

---

### Design justification

| Choice | Justification |
|---|---|
| **Four separate functions** | Each function has one job. This makes the code easier to read, debug, and test in isolation. |
| **Heap-allocated buffer, freed each call** | Avoids a lingering allocation; the buffer is only needed during the read phase and is freed immediately after. |
| **`stash` initialised to `""` via `ft_strdup`** | Allows `ft_strjoin(stash, buffer)` to work unconditionally on the first call without a special null check inside the loop. |
| **`\n` included in the returned line** | Lets the caller distinguish a normal line from a last line with no trailing newline, without needing a separate return code. |
| **`stash` set to `NULL` when empty** | Prevents dangling empty-string allocations and makes the EOF condition unambiguous on the next call. |
| **`ssize_t` for the return of `read()`** | `read()` returns `ssize_t`, not `int`. Using the correct type avoids silent truncation on large reads. |

**Alternative considered — reading char by char (`BUFFER_SIZE = 1`):**
Reading one byte at a time eliminates the need for a stash buffer entirely, since there is never any leftover data. However, this requires one `read()` syscall per character, is extremely inefficient, and does not generalise to arbitrary `BUFFER_SIZE` values — a hard project requirement. It was rejected.

**Alternative considered — re-reading from the start each call:**
Seeking back to the beginning of the file and re-scanning for the n-th newline on each call is theoretically possible via `lseek()`, but it does not work on pipes or `stdin`, has O(n²) complexity over the whole file, and was rejected for both correctness and performance reasons.

---

## Instructions

### Prerequisites

- A C compiler: `gcc` or `clang`
- A Unix-like operating system (Linux or macOS)

### Files

| File | Role |
|---|---|
| `get_next_line.h` | Header — function prototype, `BUFFER_SIZE` definition, includes |
| `get_next_line.c` | Core logic: `get_next_line`, `read_and_fill`, `set_line`, `stash_update` |
| `get_next_line_utils.c` | Helper string functions: `ft_strdup`, `ft_strchr`, `ft_strjoin`, `ft_strlen`, `ft_substr` |

### Compilation

`BUFFER_SIZE` must be defined at compile time via the `-D` flag. Any strictly positive integer is valid.

```bash
gcc -Wall -Wextra -Werror -D BUFFER_SIZE=42 get_next_line.c get_next_line_utils.c -o gnl
```

Try extreme values to verify robustness:

```bash
# Minimum — one byte at a time
gcc -Wall -Wextra -Werror -D BUFFER_SIZE=1 get_next_line.c get_next_line_utils.c -o gnl

# Large buffer
gcc -Wall -Wextra -Werror -D BUFFER_SIZE=100000 get_next_line.c get_next_line_utils.c -o gnl
```

### Integration example

```c
#include <fcntl.h>
#include <stdio.h>
#include <stdlib.h>
#include "get_next_line.h"

int main(void)
{
    int     fd;
    char    *line;

    fd = open("my_file.txt", O_RDONLY);
    if (fd < 0)
        return (1);
    while ((line = get_next_line(fd)) != NULL)
    {
        printf("%s", line);   // line already contains '\n' if present
        free(line);
    }
    close(fd);
    return (0);
}
```

```bash
gcc -Wall -Wextra -Werror -D BUFFER_SIZE=4096 main.c get_next_line.c get_next_line_utils.c
```

### Testing

```bash
echo -e "Hello\nWorld\n42" > test.txt
gcc -D BUFFER_SIZE=5 get_next_line.c get_next_line_utils.c main.c && ./a.out
```

Community testers for exhaustive edge-case coverage:
- [gnlTester by Tripouille](https://github.com/Tripouille/gnlTester)
- [42TESTERS-GNL by DontBreakAlex](https://github.com/DontBreakAlex/42TESTERS-GNL)

---

## Resources

### Official / Reference documentation

- [Linux `man` page — `read(2)`](https://man7.org/linux/man-pages/man2/read.2.html) — The system call at the heart of this project.
- [Linux `man` page — `open(2)`](https://man7.org/linux/man-pages/man2/open.2.html) — Opening file descriptors.
- [C Standard — `static` storage duration (cppreference)](https://en.cppreference.com/w/c/language/storage_duration) — How `static` local variables persist across function calls.
- [GNU C Library — File Descriptors](https://www.gnu.org/software/libc/manual/html_node/File-Descriptors.html) — High-level overview of file descriptors in Unix.

### Tutorials and articles

- [Get Next Line — Explained (Medium)](https://medium.com/@ayogun/get-next-line-c9341a7bdece) — A clear walkthrough of the core concepts.
- [Static variables in C (GeeksForGeeks)](https://www.geeksforgeeks.org/static-variables-in-c/) — Concise refresher on `static`.
- [Understanding file descriptors (Baeldung)](https://www.baeldung.com/linux/file-descriptors) — Conceptual intro to fd.
- [Memory management and valgrind for GNL (harm-smits 42docs)](https://harm-smits.github.io/42docs/projects/get_next_line) — Tips for leak-free development on this project.

### Use of AI

AI assistance (Claude by Anthropic) was used during this project in the following ways:

- **Debugging** — Describing edge-case crashes to the AI in order to trace root causes faster: for instance, the double-free that could occur when `stash` was left as a dangling empty string after EOF, and the memory leak introduced by `ft_strjoin` when the old pointer is not freed immediately after the join.
- **Understanding concepts** — Asking for explanations of `static` variable lifetime across calls, the difference between `ssize_t` and `int` for `read()` return values, and why the `""` initialisation of `stash` is safer than leaving it `NULL`.
- **README drafting** — Structuring and writing this documentation, including the per-function algorithm breakdown and the design justification table.

AI was **not** used to write the C source code. All logic was designed, written, and tested by the student.

---

*42 Antananarivo — milestone1 / get_next_line*