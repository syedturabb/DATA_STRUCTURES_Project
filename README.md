# 🎮 GameBox - C++ Mini Games Collection

## 📌 Overview
**GameBox** is a console-based C++ project containing three fun mini-games in one program:
1. 🏴 Minesweeper Game  
2. 🐍 Snake & Ladder Game  
3. 🪙 Heads & Tails Game  

It’s a menu-driven application where the player can select any game to play directly from the main menu.

---

## 📂 **Project Structure**
```
DS-Project/
│── g1.cpp   # Minesweeper Game logic
│── g2.cpp   # Snake & Ladder Game logic
│── g3.cpp   # Heads & Tails Game logic
│── main.cpp # Main menu and game launcher
```

---

## 🚀 How to Run

### 1️⃣ Compile the project  
```bash
g++ main.cpp g1.cpp g2.cpp g3.cpp -o gamebox
```

### 2️⃣ Run the program  
```bash
./gamebox
```

---

## 🎯 Game Descriptions

### 1. 🏴 Minesweeper
- A 5x5 grid.
- Players reveal cells and avoid hidden mines.
- Power-ups and defusal kits available.

### 2. 🐍 Snake & Ladder
- Classic board game logic with ladders boosting you forward and snakes pulling you back.
- Uses a **linked list** to represent board cells.

### 3. 🪙 Heads & Tails
- Coin toss style game.
- Player vs computer scoring system.

---

## 🛠 Features
- Multiple games in one executable.
- Randomized gameplay for replayability.
- Clear, interactive console menus.
- Linked list and struct usage in game logic.

---

## 📋 Requirements
- **C++11 or later**
- **GCC/G++ compiler**

