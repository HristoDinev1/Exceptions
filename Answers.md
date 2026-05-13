# Exception Changes

---

## `inc/MyVector.h`

### `pop_back`

```cpp
void pop_back() {
    // if (size_ == 0)
    //     throw std::underflow_error("pop_back: vector is empty");
    --size_;
}
```

---

### `at`

```cpp
T& at(std::size_t index) {
    // if (index >= size_)
    //     throw std::out_of_range("at: index out of range");
    return data[index];
}
const T& at(std::size_t index) const {
    // if (index >= size_)
    //     throw std::out_of_range("at: index out of range");
    return data[index];
}
```

---

### `reserve`

```cpp
void reserve(std::size_t newCapacity) {
    // if (newCapacity > std::numeric_limits<std::size_t>::max() / sizeof(T))
    //     throw std::length_error("reserve: requested capacity is too large");
    if (newCapacity <= capacity_) return;
    T* newData = new T[newCapacity];
    // ...
}
```

---

## `src/MyString.cpp`

### `operator[]`

```cpp
char& MyString::operator[](std::size_t index) {
    // if (index >= length)
    //     throw std::out_of_range("MyString::operator[]: index out of range");
    return data[index];
}

const char& MyString::operator[](std::size_t index) const {
    // if (index >= length)
    //     throw std::out_of_range("MyString::operator[]: index out of range");
    return data[index];
}
```

---

## `src/Account.cpp`

### `deposit`

```cpp
void Account::deposit(double amount) {
    // if (amount < 0)
    //     throw std::invalid_argument("deposit: amount must be non-negative");
    // if (std::isinf(balance + amount))
    //     throw std::overflow_error("deposit: amount would overflow balance");
    balance += amount;
    history.push_back(Transaction(TransactionType::Deposit, amount));
}
```

---

### `withdraw`

```cpp
void Account::withdraw(double amount) {
    // if (amount < 0)
    //     throw std::invalid_argument("withdraw: amount must be non-negative");
    // if (amount > balance)
    //     throw std::underflow_error("withdraw: insufficient funds");
    balance -= amount;
    history.push_back(Transaction(TransactionType::Withdraw, amount));
}
```

---

## `src/BankSystem.cpp`

### `createAccount`

```cpp
void BankSystem::createAccount(int id, const MyString& ownerName, double initialBalance) {
    // if (id <= 0)
    //     throw std::invalid_argument("createAccount: id must be positive");
    // if (ownerName.empty())
    //     throw std::invalid_argument("createAccount: owner name must not be empty");
    // if (initialBalance < 0)
    //     throw std::invalid_argument("createAccount: initial balance must be non-negative");
    // if (findAccountIndex(id) != -1)
    //     throw std::invalid_argument("createAccount: account with this id already exists");
    Account account(id, ownerName, initialBalance);
    accounts.push_back(account);
}
```

---

### `findAccount`

```cpp
Account& BankSystem::findAccount(int accountId) {
    int idx = findAccountIndex(accountId);
    // if (idx == -1)
    //     throw std::out_of_range("findAccount: account not found");
    return accounts[idx];
}

const Account& BankSystem::findAccount(int accountId) const {
    int idx = findAccountIndex(accountId);
    // if (idx == -1)
    //     throw std::out_of_range("findAccount: account not found");
    return accounts[idx];
}
```

---

### `transfer`

```cpp
void BankSystem::transfer(int fromId, int toId, double amount) {
    // if (fromId == toId)
    //     throw std::logic_error("transfer: cannot transfer to the same account");
    // if (amount < 0)
    //     throw std::invalid_argument("transfer: amount must be non-negative");
    Account& from = findAccount(fromId);
    Account& to   = findAccount(toId);
    from.recordTransfer(amount, toId,   false);
    to.recordTransfer  (amount, fromId, true);
}
```

---

## `src/Statistics.cpp`

### `averageBalance`

```cpp
double Statistics::averageBalance(const BankSystem& bank) {
    // if (bank.getAccountCount() == 0)
    //     throw std::logic_error("averageBalance: bank has no accounts");
    return totalMoney(bank) / static_cast<double>(bank.getAccountCount());
}
```

---

### `richestAccount`

```cpp
Account Statistics::richestAccount(const BankSystem& bank) {
    // if (bank.getAccountCount() == 0)
    //     throw std::logic_error("richestAccount: bank has no accounts");
    const MyVector<Account>& accounts = bank.getAccounts();
    std::size_t richestIdx = 0;
    for (std::size_t i = 1; i < accounts.size(); ++i) {
        if (accounts[i].getBalance() > accounts[richestIdx].getBalance()) {
            richestIdx = i;
        }
    }
    return accounts[richestIdx];
}
```

---

## `src/FileManager.cpp`

### `load`

```cpp
void FileManager::load(BankSystem& bank, const MyString& filename) {
    std::ifstream in(filename.c_str());
    // if (!in)
    //     throw std::runtime_error("FileManager::load: cannot open file");
    std::size_t count = 0;
    // if (!(in >> count))
    //     throw std::runtime_error("FileManager::load: malformed file");
    for (std::size_t i = 0; i < count; ++i) {
        int         id      = 0;
        std::string owner;
        double      balance = 0.0;
        // if (!(in >> id >> owner >> balance))
        //     throw std::runtime_error("FileManager::load: malformed file");
        bank.createAccount(id, MyString(owner.c_str()), balance);
    }
}
```
