# Pac-ssembly

This project is dedicated to creating a Pac-man game written in x86 16-bit Assembly, developed using NASM and executed with DOSBox. (with some other features).

<img src="https://github.com/user-attachments/assets/61369f2f-bfd1-4150-bde7-1656d9b37402" width="350">

## 🏮 Introduction

This repository showcases the power and creativity of Assembly programming by focusing on retro-style games. Each game is designed to run in a DOS environment, offering a nostalgic and educational journey into low-level programming.

## 🎛️ Prerequisites

To play the game, you'll need:

- NASM (Netwide Assembler): A popular assembler for x86 architecture.
- DOSBox: An x86 emulator with DOS for running 16-bit applications.

To create or edit games, you'll need the prerequisites above and:

- A code editor or IDE for Assembly programming (e.g., VSCode with Assembly extensions).

## Gameplay

<img width="500" src="https://github.com/user-attachments/assets/e69d063a-04f1-4bcc-8c7b-1ef32b0336da" />

The gameplay is quite **similar to the original Pac-man**. You can navigate through the maze, by **using the 4 directions** (_up_, _left_, _right_ and _down_).

| Direction | Key |
| --- | --- |
| Up | Up arrow |
| Left | Left Arrow |
| Right | Right Arrow |
| Down | Down Arrow |

### 2-player mode

In our game, there's a **2-player mode**! The second player **embodies a ghost**, and he **can switch** from a ghost to another. <br>The ghost being controlled is **pointed at by an arrow**.<br>
<img width="100" src="https://github.com/user-attachments/assets/cdb336c7-5012-4c2b-bb26-561e8d42b21f" />
<br><br>
Pac-man's movement's keys remain the same, and we **added 5 keys** for the second player: 4 for movement and another one to switch ghosts.

| Direction | Key |
| --- | --- |
| Up | W |
| Left | A |
| Right | D |
| Down | S |
| Switch | C |
