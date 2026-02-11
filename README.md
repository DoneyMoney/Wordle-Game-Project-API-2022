# Wordle Game Project - API 2022

This repository contains the final individual project for the **"Algorithms and Principles of Computer Science" (API)** course at **Politecnico di Milano** (A.Y. 2021/2022). 

**Final Grade: 30 / 30**

---

## 🎮 Game Explanation
The system implements a game inspired by **Wordle**, where the objective is to guess a secret word of length $k$ through a series of attempts. After each attempt, the system provides feedback for each character using specific symbols:

* **`+` (Correct)**: The character is in the correct position.
* **`|` (Misplaced)**: The character is present in the secret word but in a different position.
* **`/` (Absent)**: The character is not present in the secret word.

The challenge lies in efficiently filtering the dictionary of admissible words to identify those that remain "compatible" with the constraints learned from previous attempts.

---

## 🚀 Technical Implementation
The project is implemented in **C11** using only standard libraries to ensure maximum performance and low-level control over memory.

### Hybrid Data Structure: BST + Linked List
To handle tens of thousands of words under strict time and memory constraints (128MB), a custom hybrid data structure was designed:

* **Binary Search Tree (BST)**: Every word in the dictionary is stored in a BST node to allow efficient lexicographical sorting and searching.
* **Dynamic Linked List**: Each node contains a `next` pointer used to maintain a list of words that are currently compatible with the game's constraints.
* **Optimized Pruning**: Instead of re-scanning the entire dictionary, the system traverses the linked list and removes incompatible nodes as new constraints are discovered, significantly reducing the search space.

### Data Structure Snippet
```c
typedef struct tagTree {
    char *key;           // The word string
    struct tagTree *padre;
    struct tagTree *left;
    struct tagTree *right;
    struct tagTree *next; // Pointer to the next compatible word in the list
} tree;
```

## 🛠 Supported Commands
The system processes a stream of commands from standard input to manage matches and dictionary updates:

* **`+nuova_partita`**: Starts a new match by reading the secret word and the maximum number of attempts.
* **`+stampa_filtrate`**: Outputs all words currently compatible with the learned constraints, sorted lexicographically.
* **`+inserisci_inizio` / `+inserisci_fine`**: Allows for dynamic dictionary expansion, adding new admissible words even during an active match.

## 📊 Development & Profiling Tools
The implementation was rigorously profiled to ensure zero memory leaks and optimal execution time under strict constraints:

* **Memory Integrity**: Valgrind, Address-Sanitizer (ASan).
* **Performance Profiling**: Callgrind, Massif-Visualizer.
* **Debugging & Compilation**: GDB, GCC.
* **IDE**: CLion.
