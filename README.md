# Railroad Network Controller (C++)

## Project Overview
This project is a railroad network control system developed in C++. It simulates the management of train stations and routes using a custom **doubly linked list** data structure. Each station is represented as a node, and directional route links connect stations across the network.

The system supports adding and removing stations, building routes, traveling through routes, updating passenger data, clearing routes, and performing deep copies of the network.

This project demonstrates advanced C++ programming concepts including dynamic memory management, pointer manipulation, object-oriented design, copy control, and unit testing.

---

## Purpose / Problem Being Solved
The purpose of this project was to design and implement a data structure capable of managing a railroad network efficiently and safely.

The project solves the challenge of storing and maintaining a dynamic network that can:

- Add stations at the head or tail of the network
- Prevent duplicate station IDs
- Connect stations through directional routes
- Traverse routes and calculate passenger totals
- Remove stations while safely updating connections
- Clear and rebuild routes
- Perform deep copies of network objects
- Avoid memory leaks and invalid memory access

This project also emphasized writing clean, testable, and maintainable C++ code in a Linux environment.

---

## Technologies Used
- C++
- Object-Oriented Programming (OOP)
- Doubly Linked Lists
- Dynamic Memory Management
- Linux Command Line
- Makefile
- Unit Testing
- Valgrind

---

## Project Structure
```text
.
├── MAKEFILE        # Build instructions
├── mytest.cpp      # Unit tests and test driver
├── railroad.cpp    # Railroad class implementation
├── railroad.h      # Class declarations and interfaces
└── README.md       # Project documentation
```

---

## Setup / Installation / Usage Instructions

### 1. Clone the Repository
```bash id="u3l0x8"
git clone https://github.com/Sakar-Ojha/Railroad-network-controller.git
cd Railroad-network-controller
```

### 2. Build the Project
Use the provided Makefile:

```bash id="k6gxuq"
make
```

### 3. Run the Test Program

```bash id="3t9h7s"
./myprogram
```

### 4. Optional: Check for Memory Leaks with Valgrind

```bash id="4ocq4q"
valgrind --leak-check=full ./mytest
```

---

## Key Features / Functionality

### 🚉 Station Management
- Insert new stations at the head or tail
- Prevent duplicate station codes
- Store passenger counts for each station
- Remove stations safely from the network

### 🛤️ Route Management
- Create directional routes (North, South, East, West)
- Preserve route integrity
- Prevent invalid route overwrites
- Clear all existing routes

### 🚆 Route Traversal
- Travel through valid routes
- Calculate total passengers across visited stations
- Detect invalid routes and missing links

### 🧠 Memory-Safe Design
- Proper destructor implementation
- Safe dynamic allocation / deallocation
- Deep copy support with:
  - Copy Constructor
  - Assignment Operator
- Protection against memory leaks and invalid access

### ✅ Testing
- Dedicated test suite in `mytest.cpp`
- Functional and edge-case testing
- Designed for large input sizes

---

## Example Usage

```text
Build the project:
make

Run tests:
./mytest

Check memory:
valgrind --leak-check=full ./mytest
```

The test suite validates insertion, removal, route creation, traversal, copy behavior, and memory safety.

---

## My Role / Contribution
I implemented the core functionality of the railroad controller system based on the provided project specifications.

My contributions included:

- Implementing the doubly linked list structure
- Writing station insertion and removal logic
- Building route creation and traversal systems
- Managing passenger updates
- Implementing deep copy behavior
- Writing automated unit tests
- Debugging pointer and memory issues
- Verifying correctness in a Linux environment

---

## Reflection / Challenges / Lessons Learned
One of the biggest challenges in this project was correctly managing pointers while modifying the linked list and route connections without causing memory errors.

Through this project, I learned:

- How doubly linked lists work internally
- How to safely use dynamic memory in C++
- How copy constructors and assignment operators should perform deep copies
- How to debug segmentation faults and logic bugs
- How automated tests improve code reliability
- How tools like Valgrind help detect memory leaks

This project significantly improved my confidence with low-level C++ programming and data structures.

---

## Future Improvements
Possible future enhancements include:

- Graphical visualization of the railroad network
- File import/export for station data
- Route optimization algorithms
- Search and shortest-path features
- Real-time scheduling simulation
- Performance benchmarking for large networks

---

## Repository Description
C++ railroad network controller using doubly linked lists, route traversal, deep copy semantics, unit testing, and memory-safe design.

---
