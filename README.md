# Str + vec_str

Small C library: a length-based string type and a dynamic array of those strings.

## Files

| File | Purpose |
|------|---------|
| `str.h` | `Str` type and helpers (header-only) |
| `dynamic_array_str.h` / `.c` | `vec_str`, a growable array of `Str` |

## Str

```c
typedef struct { char *val; size_t len; } Str;
```

Strings are **not** null-terminated. The end is always decided by `len`.

Naming convention: functions returning a `Str` are uppercase (`STR`, `STR_SLICE`, `STR_DEEP_COPY`); everything else is lowercase.

| Function | Description |
|----------|-------------|
| `STR(s)` | Allocate a new `Str` from a C string |
| `STR_SLICE(s, l, r)` | Non-owning view of `[l, r)`; no allocation |
| `STR_DEEP_COPY(s)` | Allocate an independent copy |
| `str_eq(a, b)` | Length + `memcmp` equality |
| `str_at(s, i)` | Char at `i`, or `'\0'` if out of range |
| `str_print(s)` | Write `s` to stdout via `fwrite` |
| `str_free(s)` | Free `s.val` |

On allocation failure or invalid input, constructors return `(Str){0}`.

## vec_str

```c
typedef struct { Str *ptr; size_t size; size_t capacity; } vec_str;
```

| Function | Description |
|----------|-------------|
| `vec_str_init(v, cap)` | Init with capacity `cap > 0`. Returns 0 / -1 |
| `vec_str_append(v, s)` | Push; doubles capacity when full |
| `vec_str_get(v, i)` | Bounds-checked read |
| `vec_str_put(v, i, s)` | Bounds-checked replace; frees the old element |
| `vec_str_is_empty(v)` | True if null, unallocated, or size 0 |
| `vec_str_free(v)` | Frees every element and the buffer |

`get`, `put`, and `append` call `exit(EXIT_FAILURE)` on null pointers, out-of-bounds indices, uninitialised strings, or realloc failure.

## Ownership rules

- `vec_str` **owns** its elements and frees them in `vec_str_free` / `vec_str_put`.
- Only append strings you own (`STR`, `STR_DEEP_COPY`). **Never append a `STR_SLICE`**: it points into another buffer and will be freed incorrectly.
- Slices are invalid once the source string is freed.

## Usage

```c
vec_str v;
vec_str_init(&v, 4);

vec_str_append(&v, STR("hello"));
vec_str_append(&v, STR("world"));

str_print(vec_str_get(&v, 0));   // hello

vec_str_free(&v);
```

Build: compile `dynamic_array_str.c` with your sources and include the headers.

## Known limitations

- `str.h` defines non-`static` functions in a header; including it in more than one `.c` file causes duplicate-symbol link errors (mark them `static inline` or split into `str.c`).
- Empty strings are treated as failures (`malloc(0)` / `{0}`), and `vec_str_append`/`put` reject them.
- `perror` is used for non-errno errors, so messages may include unrelated text.
