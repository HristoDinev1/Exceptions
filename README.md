# Simple Banking / ATM Account Management System

A small C++ banking application written in a clean, student-friendly style.

The project currently works for "good" inputs (correct files, valid indexes, sensible
amounts). It is **not** robust: there are no `try/catch` blocks, no validation, no
bounds checks. That is the exercise.

## Repository layout

```
.
├── inc/                    # header files
├── src/                    # implementation files  <-- you mostly work here
├── tests/                  # Catch2 tests (public + hidden)
├── .github/workflows/      # CI
├── CMakeLists.txt
├── run_tests.bat
└── README.md
```

## Build

### Linux / macOS
```bash
cmake -S . -B build
cmake --build build
./build/banking
```

### Windows
```bat
mkdir build
cd build
cmake ..
cmake --build .
.\Debug\banking.exe
```

## Run the tests
```bash
ctest --test-dir build --output-on-failure
```
Or on Windows simply run `run_tests.bat`.

## Your task

1. Run the tests. Public tests should pass, hidden tests should mostly fail
   (or crash).
2. Go into `src/` and `inc/` and make the code robust:
   - Validate input (negative amounts, empty names, bad IDs, ...).
   - Throw appropriate standard exceptions:
     `std::invalid_argument`, `std::out_of_range`, `std::runtime_error`,
     `std::overflow_error`, `std::underflow_error`, `std::logic_error`,
     `std::length_error`.
   - Add a `try/catch` block in `Application::run()` — this is the central
     boundary where exceptions should be caught and reported to the user.
3. After your changes the hidden tests should pass as well.

You should **not** modify `tests/`, `.github/workflows/` or the build scripts.
