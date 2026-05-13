## Стъпки

**Step 1: Clone repo**
```bash
git clone https://github.com/HristoDinev1/Exceptions/
cd Exceptions
```

**Step 2: Create branch**
```bash
git checkout -b ИметоНаВашиятBranch
```

**Step 3: Преработвате кода**

**Step 4: Push**
```bash
git add .
git commit -m "СъобщениеНаКомита"
git push origin ИметоНаВашиятBranch
```

**Step 5: Check GitHub Actions** - вижте резултатите на вашия branch

---

## Optional: Test локално преди push

**Linux / macOS:** - (нямам мак не съм тествал)
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
