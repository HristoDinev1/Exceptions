## Стъпки

**Step 1: Clone repo**
```bash
git clone <repo-url>
cd BankingSystem
```

**Step 2: Create branch**
```bash
git checkout -b fix-exceptions
```

**Step 3: Преработвате кода**

**Step 4: Push**
```bash
git add .
git commit -m "exceptions"
git push origin fix-exceptions
```

**Step 5: Check GitHub Actions** - вижте резултатите на вашия branch

---

## Optional: Test локално преди push

**Linux / macOS:**
```bash
cmake -S . -B build
cmake --build build
ctest --test-dir build --output-on-failure
```

**Windows:**
```bash
mkdir build
cd build
cmake ..
cmake --build .
ctest --test-dir build --output-on-failure
```
