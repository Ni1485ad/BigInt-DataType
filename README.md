# BigInt-DataType

# 1024-bit Number Handling in C++  

## Overview  
The **BigInt** project is a C++ implementation for handling **arbitrarily large numbers (up to 1024 bits)**, supporting:  
- **Binary & Decimal conversions**  
- **Arithmetic operations (Addition, Subtraction, Multiplication)**  
- **Two's complement representation**  
- **Overflow detection**  

This implementation processes numbers as **binary vectors**, making it efficient for large numerical computations.  

---

##  Features  
✔ **Convert large numbers to binary representation (up to 1024 bits)**  
✔ **Perform addition, subtraction, and multiplication using binary operations**  
✔ **Handle two's complement for negative numbers**  
✔ **Convert binary back to decimal for human-readable output**  
✔ **Detect overflow when exceeding 1024 bits**  
✔ **File handling support (Reads numbers from `data.txt`)**  

---


---

## 🔢 How It Works  
### **Binary Conversion**
- Converts a decimal string into **binary representation**.  
- Uses **two's complement** for negative numbers.  
- Stores binary values in a **vector<int>**.  

### **Arithmetic Operations**
- **Addition (`binAdd`)** – Uses bitwise operations for binary sum.  
- **Subtraction (`binSub`)** – Computes the **two’s complement** of the second number and adds it.  
- **Multiplication (`binMult`)** – Implements **binary shift and add** technique.  

### **Overflow Detection**
- If the binary size **exceeds 1024 bits**, an **overflow flag (`of`)** is set.  

---

##  Usage Instructions  

### **1️⃣ Compilation**  
Compile the program using `g++`:  
```sh
g++ BigInt.cpp -o bigint

### **Running the program**
    ./bigint

Future Enhancements
🔹 Division & Modulo operations
🔹 Modular exponentiation for cryptographic applications
🔹 Optimization using bitwise shifts
🔹 Support for numbers beyond 1024 bits