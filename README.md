# Arcade Games

Welcome to the Arcade Games repository, dedicated to creating and showcasing games written in **ARM 32-bit Assembly**. These games are developed using **GNU** and executed on the **Raspberry Pi 3 Model B+**, offering a unique, low-level programming experience.

This collection features retro-style games that highlight the power and creativity of assembly programming, combining nostalgia with educational content to explore the world of low-level development.

## 🏮 Introduction

This repository is all about bringing classic retro-style games to life through the raw power of ARM 32-bit Assembly. Every game in this collection runs in a Raspberry Pi environment, allowing you to experience the craftsmanship behind assembly language while enjoying a nostalgic gaming experience.

These games serve as an educational journey into low-level programming, demonstrating how assembly can be used to create functional, engaging games with minimal resources. It's an excellent resource for developers interested in learning more about assembly programming, particularly for the ARM architecture and the Raspberry Pi environment.

## 🎛️ Prerequisites

Before you start playing or developing with Assembly Games, ensure that you have the following installed on your system:

**To play the games**:

- *GNU Assembler (as)*: Required to assemble the game's assembly code and produce executable files.
- *Raspberry Pi 3 Model B+*: The game is optimized for this model, so ensure you're running this or a similar Raspberry Pi with ARM 64-bit architecture.

**To create or edit games**:

You’ll need the tools mentioned above along with:

- **A code editor or IDE for Assembly programming** (e.g., VSCode with assembly extensions or another editor of your choice).

## 🤝 Could I create my own games?

Absolutely! You can definitely create your own games in the style of those in this repository. While contributions to the repository are limited for now, you’re encouraged to try building your own projects with Assembly programming.

Here’s how you can get started:

*Clone the repository to your local machine*:

```sh
git clone https://github.com/EnzoGuillouche/Assembly-games.git
```

*Write your Assembly code and compile it*. For example:

```sh
as code.s -o code.o
ld code.o -o code
```

*Navigate to the repository folder*:

```sh
cd assembly-games
```

## 🕹️ Usage

To run any of the games in this repository, simply execute the corresponding start file within the game’s directory. The start files automatically compile and run the game on your Raspberry Pi.

*Run the game*:

```sh
./startPi.sh
```

This will start the game, and you can jump straight into the action!

## 🎮 Games

**Completed Games**:

More games will be added to the repository as development progresses. Stay tuned for new releases!

**In Progress**:

**Street-Fighssembly**: A retro-style fighting game inspired by classic '90s arcade games, written in ARM 32-bit Assembly.

## 📚 Resources

Official Repository: Access the source code and documentation.
Raspberry Pi Documentation: Learn about your Raspberry Pi and how to set it up for development.

This repository is all about exploring the world of low-level programming with fun, engaging projects. Whether you’re a seasoned developer or just starting to learn assembly, we hope you enjoy the journey!
