# 📇 Connect Track Pro

![C](https://img.shields.io/badge/C-Programming-A8B9CC.svg?logo=c)
![Makefile](https://img.shields.io/badge/Build-Make-007396.svg?logo=gnu)

**Connect Track Pro** is a high-performance, modular command-line application written in C. It serves as a unified personal management tool, allowing users to seamlessly track contacts, maintain private diary entries, set up notifications, and execute rapid searches.

## ✨ Core Architecture
The project is strictly modular, dividing logic into scalable header (`.h`) and source (`.c`) components:
* `contact_manager`: Handles CRUD operations for user contacts.
* `diary_manager`: Manages timestamped, private daily entries.
* `notifications`: A time-aware alert system for important events.
* `search_manager`: An optimized search engine to traverse contacts and logs.
* `ui`: Handles console formatting, menus, and user inputs cleanly.
* `utility`: Shared helper functions for memory management and string parsing.

## 🛠️ Tech Stack
* **Language:** C (C99/C11 standards)
* **Build System:** GNU Make
* **Architecture:** Modular Header/Source separation

## 🚀 Build & Run
1. Ensure you have `gcc` and `make` installed on your system.
2. Clone the repository and navigate to the project root.
3. **Build the project:**
   ```bash
   make
