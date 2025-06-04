# Assembly Games

This repository is dedicated to creating games written in **x86 16-bit Assembly**, developed using **NASM** and executed with **DOSBox**.

---

## 🏮 Introduction

This repository showcases the power and creativity of Assembly programming by focusing on retro-style games. Each game is designed to run in a DOS environment, offering a nostalgic and educational journey into low-level programming.

---

## 🎛️ Prerequisites

To **play the game**, you'll need:

*NASM (Netwide Assembler)*: A popular assembler for x86 architecture.

*DOSBox*: An x86 emulator with DOS for running 16-bit applications.

To **create or edit games**, you'll need the prerequisites above and:

*A code editor or IDE* for Assembly programming (e.g., VSCode with Assembly extensions).

---

## 🤝 Could I create my own games?

You can absolutely try to create some games like ours, though contributions to this repository are limited for now.
But you can build some on your own:

Clone this repository to your local machine:

```bash
git clone https://github.com/EnzoGuillouche/Assembly-games.git
```

Install NASM:

*On Linux*:

```shell
sudo apt-get install nasm
```

*On macOS*:

```shell
brew install nasm
```

*On Windows*, download the installer from [NASM's official site](https://www.nasm.us).

Install DOSBox:

Download the installer from [DOSBox's official site](https://www.dosbox.com).

For macOS, make sure the DOSBox executable is located in your Desktop directory.
For Windows, follow the steps given by both installers (DOSBox and NASM).

On *Raspberry Pi*, you just have to type this command to install both NASM and DOSBox:

```shell
sudo apt install dosbox nasm -y
```

Navigate to the repository folder:

```bash
cd assembly-games
```

---

## 🕹️ Usage

In each game folder, there will be `start` files.
These files will compile and run the game on DOSBox automatically, you just have to execute the right file depending on your architecture.

*On Linux*:

```bash
./startLin.bash
```

*On macOS*:

```bash
./startMac.sh
```

*On Windows*:

```bash
./startWin.cmd
```

And *On Raspberry Pi*:

```bash
./startPi.sh
```

---

## 🎮 Games

### Completed Games

...

### In Progress

[**Street Fighssembly**](https://github.com/EnzoGuillouche/Assembly-games/tree/main/Games/Street-Fighssembly): A Street Fighter demake.

[**Pac-ssembly**](https://github.com/EnzoGuillouche/Assembly-games/tree/main/Games/Pac-ssembly): An arcade Pac-Man.

---

## Acknowledgments

The **NASM and DOSBox communities** for providing essential tools. As well as all the online documentation for Assembly programming language.
