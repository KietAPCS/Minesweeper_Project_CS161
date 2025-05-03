# Minesweeper_Project_CS161

## Overview

This project is a console-based implementation of the classic Minesweeper game, developed using C++. It features a graphical user interface rendered directly in the console, providing a fully interactive and engaging experience. The game includes multiple difficulty levels, save/load functionality, and a high-score tracking system.

## Features

- **Graphical Console Interface**: Custom rendering of the game board and menus using console graphics.
- **Multiple Difficulty Levels**: Choose between Easy (9x9, 10 bombs), Medium (16x16, 40 bombs), and Hard (24x24, 99 bombs).
- **Save and Load**: Save your progress and resume the game later.
- **High Scores**: Tracks the fastest times for each difficulty level.
- **Keyboard Controls**: Navigate and interact with the game using intuitive keyboard inputs.
- **Customizable Console**: Adjusts the console size and appearance for optimal gameplay.

## Gameplay Instructions

1. **Navigation**:
   - Use the arrow keys to move the cursor.
   - Press `Z` to open a cell.
   - Press `X` to place or remove a flag.
   - Press `ESC` to save the game or exit.
2. **Objective**:
   - Open all cells without bombs to win.
   - Use flags to mark cells you suspect contain bombs.
3. **Game States**:
   - Win: Successfully open all non-bomb cells.
   - Lose: Open a cell containing a bomb.

## How to Run

1. **Prerequisites**:
   - A Windows operating system.
   - A C++ compiler (e.g., MinGW or Visual Studio).
2. **Setup**:
   - Clone or download the project files.
   - Open the project in your preferred C++ IDE or compile it using a terminal.
3. **Compilation**:
   - Compile all `.cpp` files together, ensuring the necessary headers are included.
   - Example command (using g++):
     ```
     g++ Main.cpp Console.cpp Functions.cpp -o Minesweeper -lwinmm
     ```
4. **Run the Game**:
   - Execute the compiled binary.
   - Ensure the console is in fullscreen mode for the best experience.

## File Structure

- **Main.cpp**: Entry point of the application, handles game flow.
- **Console.cpp / Console.h**: Functions for managing console graphics and input.
- **Functions.cpp / Functions.h**: Core game logic and helper functions.
- **Graphic.h**: Additional graphical utilities for rendering.
- **README.md**: Project documentation.

## Developer Information

- **Author**: Phan Tuan Kiet
- **Contact**: drawyouryouth@gmail.com
- **University**: VNU HCM - University of Science (HCMUS)
- **Class**: K23 - Advanced Program in Computer Science (APCS)

## Acknowledgments

This project was developed as part of the Advanced Program in Computer Science at VNU HCM. Special thanks to the instructors and peers who provided guidance and support.

## Notes

- Ensure your console is set to fullscreen (F11) before starting the game.
- If you encounter any issues, restart the game or adjust your console settings.
